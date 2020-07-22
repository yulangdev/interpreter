#include "YuLang.h"

PCODE GenerateStmt( PTOKEN token, PCODE code, PCODE loop, PCODE loopJZ );
PCODE GenerateExpr( PTOKEN token, PCODE code );

PCODE GenerateOP( PCODE code, TYPE opCode );
PCODE GenerateOP( PCODE code, TYPE opCode, INT val );
PCODE GenerateOP( PCODE code, TYPE opCode, PCODE addr );
PCODE GenerateOP( PCODE code, TYPE opCode, PTOKEN token );

PCODE GenerateDef( PTOKEN token, PCODE code, PPCODE entryCode );
PCODE GenerateVAL( PTOKEN token, PCODE code, TYPE opCode );
PCODE GenerateAVAL( PTOKEN token, PCODE code, TYPE opCode );
PCODE GenerateMarkedVAL( PTOKEN token, PCODE code, TYPE opCode );
PCODE GenerateMarkedAVAL( PTOKEN token, PCODE code, TYPE opCode );
PCODE GenerateCall( PTOKEN token, PCODE code, BOOL inExpr );
PCODE GenerateWhile( PTOKEN token, PCODE code, PCODE loop, PCODE loopJZ );
PCODE GenerateIf( PTOKEN token, PCODE code, PCODE loop, PCODE loopJZ );
PCODE GenerateBreak( PCODE code, PCODE loopJZ );
PCODE GenerateContinue( PCODE code, PCODE loopJZ );
PCODE GenerateReturn( PTOKEN token, PCODE code );

PCODE GeneratePrint( PTOKEN token, PCODE code );
PCODE GeneratePrintln( PTOKEN token, PCODE code );
PCODE GenerateRand( PTOKEN token, PCODE code, BOOL inExpr );

PTOKEN GenerateCode( PTOKEN token, PCODE code ) {
	PCODE entryCode = NULL;

	for ( ; token->type != _DONE ; token = token->next ) {
		switch ( token->type ) {
		case _DEF:		code = GenerateDef( token, code, &entryCode );		break;
		case _GVAR:		code = GenerateMarkedVAL( token, code, _GMOV );		break;
		}
	}

	if ( entryCode == NULL ) {
		token->err = E_ENTRY;
		return token;
	}

	code = GenerateOP( code, _NUM, code + 3 );
	code = GenerateOP( code, _PUSH );
	code->len = 4;
	code->str = "main";
	code = GenerateOP( code, _CALL, entryCode );
	code = GenerateOP( code, _DEC_OSP );
	code->type = _DONE;

	return token;
}

PCODE GenerateStmt( PTOKEN token, PCODE code, PCODE loop, PCODE loopJZ ) {
	for ( ; token->type != _END; token = token->next ) {
		switch ( token->type ) {
		case _GVAL:		code = GenerateMarkedVAL( token, code, _GMOV );		break;
		case _VAR:		code = GenerateMarkedVAL( token, code, _MOV );		break;
		case _VAL:		code = GenerateMarkedVAL( token, code, _MOV );		break;
		case _GAVAL:	code = GenerateMarkedAVAL( token, code, _GMOV );	break;
		case _AVAL:		code = GenerateMarkedAVAL( token, code, _MOV );		break;
		case _CALL:		code = GenerateCall( token, code, FALSE );			break;
		case _WHILE:	code = GenerateWhile( token, code, loop, loopJZ );	break;
		case _IF:		code = GenerateIf( token, code, loop, loopJZ );		break;
		case _BREAK:	code = GenerateBreak( code, loopJZ );				break;
		case _CONTINUE:	code = GenerateContinue( code, loop );				break;
		case _RETURN:	code = GenerateReturn( token, code );				break;
		case _PRINT:	code = GeneratePrint( token, code );				break;
		case _PRINTLN:	code = GeneratePrintln( token, code );				break;
		case _RAND:		code = GenerateRand( token, code, FALSE );			break;
		}
	}
	return code;
}

PCODE GenerateDef( PTOKEN token, PCODE code, PPCODE entryCode ) {
	token->addr = code + 1;

	PCODE jumpEnd = code;
	code = GenerateOP( code, _JMP );

	if ( token->len == 4 && 
		token->str[0] == 'm' && token->str[1] == 'a' && 
		token->str[2] == 'i' && token->str[3] == 'n' )
		*entryCode = code;

	code = GenerateOP( code, _DEF_BEGIN, token );
	code = GenerateOP( code, _PUSH_EBP );
	code = GenerateOP( code, _SAV_ESP );
	code = GenerateOP( code, _INC_ESP, token->frmSize );
	code = GenerateStmt( token->stmts, code, NULL, NULL );
	code = GenerateOP( code, _NUM, 0 );
	code = GenerateOP( code, _RST_ESP );
	code = GenerateOP( code, _POP_EBP );
	code = GenerateOP( code, _RETURN );
	code = GenerateOP( code, _DEF_END, token );

	jumpEnd->addr = code;

	return code;
}

PCODE GenerateMarkedVAL( PTOKEN token, PCODE code, TYPE opCode ) {
	code = GenerateOP( code, _ASSIGN_BEGIN );
	code = GenerateVAL( token, code, opCode );
	code = GenerateOP( code, _ASSIGN_END );
	return code;
}

PCODE GenerateMarkedAVAL( PTOKEN token, PCODE code, TYPE opCode ) {
	code = GenerateOP( code, _ASSIGN_BEGIN );
	code = GenerateAVAL( token, code, opCode );
	code = GenerateOP( code, _ASSIGN_END );
	return code;
}

PCODE GenerateVAL( PTOKEN token, PCODE code, TYPE opCode ) {
	code = GenerateExpr( token->stmts, code );
	code = GenerateOP( code, _NUM, token );
	code = GenerateOP( code, opCode, token );
	return code;
}

PCODE GenerateAVAL( PTOKEN token, PCODE code, TYPE opCode ) {
	code = GenerateExpr( token->expr, code );
	
	code = GenerateOP( code, _INDEX_BEGIN );
	for ( PTOKEN index = token->stmts; index != NULL; index = index->next ) {
		code = GenerateExpr( index->stmts, code );
		code = GenerateOP( code, _NUM, index->val );
		code = GenerateOP( code, _MUL );
		code = GenerateOP( code, _INDEX_SEP );
	}

	for ( PTOKEN index = token->stmts; index->next != NULL; index = index->next )
		code = GenerateOP( code, _ADD );

	code = GenerateOP( code, _INDEX_END );
	code = GenerateOP( code, _NUM, token );
	code = GenerateOP( code, _ADD );
	code = GenerateOP( code, opCode, token );

	return code;
}

PCODE GenerateCall( PTOKEN token, PCODE code, BOOL inExpr ) {
	code = GenerateOP( code, _CALL_BEGIN );

	for ( PTOKEN arg = token->stmts; arg != NULL; arg = arg->next ) {
		code = GenerateExpr( arg->stmts, code );
		code = GenerateOP( code, _PUSH );
		code = GenerateOP( code, _CALL_SEP );
	}

	code = GenerateOP( code, _NUM, code + 3 );
	code = GenerateOP( code, _PUSH );
	code->len = token->len;
	code->str = token->str;
	code = GenerateOP( code, _CALL, token->ref->addr );

	for ( PTOKEN arg = token->stmts; arg != NULL; arg = arg->next )
		code = GenerateOP( code, _POP );

	if ( inExpr == FALSE ) code = GenerateOP( code, _DEC_OSP );

	code = GenerateOP( code, _CALL_END );

	return code;
}

PCODE GenerateWhile( PTOKEN token, PCODE code, PCODE loop, PCODE loopJZ ) {
	loop =			code = GenerateOP( code, _WHILE_BEGIN );
	loopJZ =		code = GenerateExpr( token->expr, code );
					code = GenerateOP( code, _JZ );
					code = GenerateStmt( token->stmts, code, loop, loopJZ );
	loopJZ->addr =	code = GenerateOP( code, _JMP, loop );
					code = GenerateOP( code, _WHILE_END );
	return code;
}

PCODE GenerateIf( PTOKEN token, PCODE code, PCODE loop, PCODE loopJZ ) {
	switch ( token->type ) {
	case _IF:	code = GenerateOP( code, _IF_BEGIN );	break;
	case _ELIF: code = GenerateOP( code, _ELIF_BEGIN );	break;
	case _ELSE:	code = GenerateOP( code, _ELSE_BEGIN );
				return GenerateStmt( token->stmts, code, loop, loopJZ );
	default:	return code;
	}		

	PCODE JZ =	code = GenerateExpr( token->expr, code );
				code = GenerateOP( code, _JZ );
	PCODE JMP =	code = GenerateStmt( token->stmts, code, loop, loopJZ );	
	JZ->addr =	code = GenerateOP( code, _JMP );
	JMP->addr =	code = GenerateIf( token->next, code, loop, loopJZ );
				code = GenerateOP( code, _IF_END );
	return code;
}

PCODE GenerateBreak( PCODE code, PCODE loopJZ ) {
	code = GenerateOP( code, _BREAK );
	code = GenerateOP( code, _NUM, 0 );
	code = GenerateOP( code, _JMP, loopJZ );
	return code;
}

PCODE GenerateContinue( PCODE code, PCODE loop ) {
	code = GenerateOP( code, _CONTINUE );
	code = GenerateOP( code, _JMP, loop );
	return code;
}

PCODE GenerateReturn( PTOKEN token, PCODE code ) {
	code = GenerateOP( code, _RETURN_BEGIN );
	code = GenerateExpr( token->stmts, code );
	code = GenerateOP( code, _RST_ESP );
	code = GenerateOP( code, _POP_EBP );
	code = GenerateOP( code, _RETURN );
	code = GenerateOP( code, _RETURN_END );
	return code;
}

PCODE GeneratePrint( PTOKEN token, PCODE code ) {
	code = GenerateOP( code, _PRINT_BEGIN );
	code = GenerateExpr( token->stmts, code );
	code = GenerateOP( code, _NOP, token );
	code = GenerateOP( code, _PRINT_END );
	return code;
}

PCODE GeneratePrintln( PTOKEN token, PCODE code ) {
	return GenerateOP( code, _NOP, token );
}

PCODE GenerateRand( PTOKEN token, PCODE code, BOOL inExpr ) {
	code = GenerateExpr( token->stmts, code );
	code = GenerateOP( code, _NOP, token );
	if ( inExpr == FALSE ) code = GenerateOP( code, _DEC_OSP );
	return code;
}

PCODE GenerateExpr( PTOKEN token, PCODE code ) {
	for ( ; token != NULL; token = token->next ) {
		switch ( token->type ) {
		case _CALL: code = GenerateCall( token, code, TRUE );	break;
		case _GVAL:	code = GenerateVAL( token, code, _GVAL );	break;
		case _VAL:	code = GenerateVAL( token, code, _VAL );	break;
		case _GAVAL:code = GenerateAVAL( token, code, _GVAL );	break;
		case _AVAL: code = GenerateAVAL( token, code, _VAL );	break;
		case _RAND: code = GenerateRand( token, code, TRUE );	break;
		default:	code = GenerateOP( code, _NOP, token );		break;
		}
	}
	return code;
}

PCODE GenerateOP( PCODE code, TYPE opCode ) {
	code->type = opCode;
	return code + 1;
}

PCODE GenerateOP( PCODE code, TYPE opCode, INT val ) { 
	code->type = opCode;
	code->val = val;
	return code + 1;
}

PCODE GenerateOP( PCODE code, TYPE opCode, PCODE addr ) {
	code->type = opCode;
	code->addr = addr;
	return code + 1;
}

PCODE GenerateOP( PCODE code, TYPE opCode, PTOKEN token ) {
	code->len = token->len;
	code->str = token->str;
	code->val = token->val;
	code->type = ( opCode == _NOP ) ? token->type : opCode;
	return code + 1;
}
