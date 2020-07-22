#include "YuLang.h"
#include <stdio.h>
#include <string.h>

PCSTR GetErrorMessage( PTOKEN token ) {
	const size_t size = 256;
	static char buf[ size ] = { 0, };
	int row = token->row;
	int col = token->col;

	static char str[256] = { 0, };
	str[0] = '\0'; 
	strncpy_s( str, size, token->str, token->len );
	str[ token->len ] = '\0';

	static char str_ref[256] = { 0, };
	str_ref[0] = '\0';
	if ( token->ref != NULL ) {
		strncpy_s( str_ref, size, token->ref->str, token->ref->len );
		str_ref[ token->len ] = '\0';
	}

	switch ( token->err )
	{
	case E_OK:			sprintf_s( buf, size, "%d:%d: ok\r\n", row, col ); break;
	case E_ENTRY:		sprintf_s( buf, size, "error: undefined reference to `main'\r\n" ); break;
	case E_REDEFINE:	sprintf_s( buf, size, "%d:%d: error: redefinition of ¡®%s¡¯\r\n", row, col, str ); break;
	case E_INTER:		sprintf_s( buf, size, "%d:%d: patal: internal error\r\n", row, col ); break;
	case E_STRAY:		sprintf_s( buf, size, "%d:%d: error: error: stray ¡®%s¡¯ in program\r\n", row, col, str ); break;
	case E_COMMA:		sprintf_s( buf, size, "%d:%d: error: expected comma ','\r\n", row, col ); break;
	case E_LPAREN:		sprintf_s( buf, size, "%d:%d: error: expected left paren '('\r\n", row, col ); break;
	case E_RPAREN:		sprintf_s( buf, size, "%d:%d: error: expected right paren ')'\r\n", row, col ); break;
	case E_LCURLY:		sprintf_s( buf, size, "%d:%d: error: expected left curly '{'\r\n", row, col ); break;
	case E_RCURLY:		sprintf_s( buf, size, "%d:%d: error: expected right curly '}'\r\n", row, col ); break;
	case E_LBRACKET:	sprintf_s( buf, size, "%d:%d: error: expected left bracket '['\r\n", row, col ); break;
	case E_RBRACKET:	sprintf_s( buf, size, "%d:%d: error: expected right bracket ']'\r\n", row, col ); break;
	case E_ASSIGN:		sprintf_s( buf, size, "%d:%d: error: expected assign symbol '='\r\n", row, col ); break;
	case E_TOKEN:		sprintf_s( buf, size, "%d:%d: error: unexpected token '%s'\r\n", row, col, str ); break;
	case E_IDEN:		sprintf_s( buf, size, "%d:%d: error: expected identifier\r\n", row, col ); break;
	case E_NUM:			sprintf_s( buf, size, "%d:%d: error: expected a number\r\n", row, col ); break;
	case E_EXPR:		sprintf_s( buf, size, "%d:%d: error: expected expression\r\n", row, col ); break;
	case E_ELIF:		sprintf_s( buf, size, "%d:%d: error: 'elif' without a previous 'if'\r\n", row, col ); break;
	case E_ELSE:		sprintf_s( buf, size, "%d:%d: error: 'else' without a previous 'if'\r\n", row, col ); break;
	case E_DECL:		sprintf_s( buf, size, "%d:%d: error: '%s' not declared (first use here)\r\n", row, col, str ); break;
	case E_BREAK:		sprintf_s( buf, size, "%d:%d: error: break statement not within 'while'\r\n", row, col ); break;
	case E_CONTINUE:	sprintf_s( buf, size, "%d:%d: error: continue statement not within 'while'\r\n", row, col ); break;
	case E_RETURN:		sprintf_s( buf, size, "%d:%d: error: return statement not within 'proc' or 'func'\r\n", row, col ); break;
	case E_RTN_VAL:		sprintf_s( buf, size, "%d:%d: error: 'return' with no value, in function '%s'\r\n", row, col, str_ref ); break;
	case E_COUNT:		sprintf_s( buf, size, "%d:%d: ?: \r\n", row, col ); break;
	case E_FEW_ARG:		sprintf_s( buf, size, "%d:%d: error: too few arguments to function '%s'\r\n", row, col, str ); break;
	case E_MANY_ARG:	sprintf_s( buf, size, "%d:%d: error: too many arguments to function '%s'\r\n", row, col, str ); break;
	case E_ARRAY:		sprintf_s( buf, size, "%d:%d: error: subscripted value is not array '%s'\r\n", row, col, str ); break;
	}
	return buf;
}

PCSTR GetTypeName( TYPE type ) {
	switch ( type ) {
	case _UNKNOWN:			return "<UNKNOWN>";
	case _DONE:				return "<DONE>";
	case _ROOT:				return "<ROOT>";
	case _LPAREN:			return "LEFT_PAREN";
	case _RPAREN:			return "RIGHT_PAREN";
	case _ARGUMENT:			return "ARGUMENT";
	case _LCURLY:			return "LEFT_CURLY";
	case _RCURLY:			return "RIGHT_CURLY";
	case _INDEX:			return "INDEX";
	case _LBRACKET:			return "LBRACKET";
	case _RBRACKET:			return "RBRACKET";
	case _COMMA:			return "COMMA";
	case _SEMICOLON:		return "SEMICOLON";
	case _ADD:				return "ADD";
	case _SUB:				return "SUB";
	case _MUL:				return "MUL";
	case _DIV:				return "DIV";
	case _MOD:				return "MOD";
	case _ASSIGN:			return "ASSIGN";
	case _CB:				return "CB";
	case _CA:				return "CA";
	case _IDEN:				return "IDEN";
	case _NUM:				return "NUM";
	case _STR:				return "STR";
	case _WHILE:			return "WHILE";
	case _BREAK:			return "BREAK";
	case _CONTINUE:			return "CONTINUE";
	case _IF:				return "IF";
	case _ELIF:				return "ELIF";
	case _ELSE:				return "ELSE";
	case _DEF:				return "DEF";
	case _END:				return "<END>";
	case _RETURN:			return "RETURN";
	case _COMMENT:			return "COMMENT";
	case _CE:				return "CE";
	case _CNE:				return "CNE";
	case _CBE:				return "CBE";
	case _CAE:				return "CAE";
	case _AND:				return "AND";
	case _OR:				return "OR";
	case _SUB_UNARY:		return "SUB_UNARY";
	case _PUSH_EBP:			return "PUSH_EBP";
	case _POP_EBP:			return "POP_EBP";
	case _SAV_ESP:			return "SAV_ESP";
	case _RST_ESP:			return "RST_ESP";
	case _PUSH:				return "PUSH";
	case _POP:				return "POP";
	case _JMP:				return "JMP";
	case _JZ:				return "JZ";
	case _JNZ:				return "JNZ";
	case _CALL:				return "CALL";
	case _GMOV:				return "GMOV";
	case _MOV:				return "MOV";
	case _GVAR:				return "GVAR";
	case _GVAL:				return "GVAL";
	case _VAR:				return "VAR";
	case _VAL:				return "VAL";
	case _ARR:				return "ARR";
	case _GAVAR:			return "GAVAR";
	case _GAVAL:			return "GAVAL";
	case _AVAR:				return "AVAR";
	case _AVAL:				return "AVAL";
	case _INC_ESP:			return "INC_ESP";
	case _DEC_OSP:			return "DEC_OSP";
	case _DEF_BEGIN:		return "<<DEF";
	case _DEF_END:			return ">>DEF";
	case _WHILE_BEGIN:		return "<<WHILE";
	case _WHILE_END:		return ">>WHILE";
	case _IF_BEGIN:			return "<<IF";
	case _ELIF_BEGIN:		return "<<ELIF";
	case _ELSE_BEGIN:		return "<<ELSE";
	case _IF_END:			return ">>IF";
	case _ASSIGN_BEGIN:		return "<<ASSIGN";
	case _ASSIGN_END:		return ">>ASSIGN";
	case _INDEX_BEGIN:		return "<<INDEX";
	case _INDEX_END:		return ">>INDEX";
	case _INDEX_SEP:		return "--INDEX";
	case _CALL_BEGIN:		return "<<CALL";
	case _CALL_SEP:			return "--CALL";
	case _CALL_END:			return ">>CALL";
	case _PRINT_BEGIN:		return "<<PRINT";
	case _PRINT_END:		return ">>PRINT";
	case _RETURN_BEGIN:		return "<<RETURN";
	case _RETURN_END:		return ">>RETURN";
	case _PRINT:			return "PRINT";
	case _PRINTLN:			return "PRINTLN";
	case _RAND:				return "RAND";
	default:				return "----------";
	}
}
