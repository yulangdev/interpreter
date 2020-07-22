#include "YuLang.h"

PTOKEN ParseStmt( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop );
PTOKEN ParseExpr( PTOKEN parent, PTOKEN token );
PTOKEN ParseTerm( PTOKEN parent, PTOKEN token, DWORD priority );
PTOKEN ParseFactor( PTOKEN parent, PTOKEN token );
DWORD  GetPriority( TYPE eType );

PTOKEN ParseDef( PTOKEN parent, PTOKEN token );
PTOKEN ParseWhile( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop );
PTOKEN ParseIf( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop );

PTOKEN ParseIndex( PTOKEN parent, PTOKEN token );
PTOKEN ParseCondition( PTOKEN parent, PTOKEN token );
PTOKEN ParseBlock( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop );

PTOKEN ParseReturn( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def );
PTOKEN ParseBreak( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN loop );
PTOKEN ParseContinue( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN loop );

PTOKEN ParseVar( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def );
PTOKEN ParseArr( PTOKEN parent, PTOKEN token, PDWORD index, PTOKEN def );
PTOKEN ParseIden( PTOKEN parent, PTOKEN token );
PTOKEN ParseAssign( PTOKEN parent, PTOKEN token );
PTOKEN ParseArrAssign( PTOKEN parent, PTOKEN token );
PTOKEN ParseAVal( PTOKEN parent, PTOKEN token );
PTOKEN ParseCall( PTOKEN parent, PTOKEN token );

PTOKEN ParsePrint( PTOKEN parent, PTOKEN token );
PTOKEN ParseRand( PTOKEN parent, PTOKEN token );

PTOKEN FindDecl( PTOKEN parent, PTOKEN token );
PTOKEN AddStmt( PTOKEN parent, PTOKEN child );

PTOKEN Error( PTOKEN token, ERROR error );
BOOL IsError( PTOKEN token );
BOOL IsNotError( PTOKEN token );
BOOL Is( PTOKEN token, TYPE type );
BOOL IsNot( PTOKEN token, TYPE type );

PTOKEN Parse( PTOKEN token ) {
	DWORD index = 0;
	TOKEN parent = { _ROOT };
	while ( IsNotError( token ) ) {
		switch ( token->type ) {
		case _DEF:		token = ParseDef( &parent, token );						break;
		case _VAR:		token = ParseVar( &parent, token, index++, NULL );		break;
		case _ARR:		token = ParseArr( &parent, token, &index, NULL );		break;
		case _COMMENT:	token = AddStmt( &parent, token );						break;
		case _SEMICOLON:token++;												break;
		case _DONE:		AddStmt( &parent, token ); return token;
		default:		return Error( token, E_TOKEN );
		}
	}
	return token;
}

PTOKEN ParseStmt( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop ) {
	while ( IsNotError( token ) ) {
		switch ( token->type ) {
		case _VAR:		token = ParseVar( parent, token, index++, def );		break;
		case _ARR:		token = ParseArr( parent, token, &index, def );			break;
		case _IDEN:		token = ParseIden( parent, token );						break;
		case _WHILE:	token = ParseWhile( parent, token, index, def, token );	break;
		case _RETURN:	token = ParseReturn( parent, token, index, def );		break;
		case _BREAK:	token = ParseBreak( parent, token, index, loop );		break;
		case _CONTINUE:	token = ParseContinue( parent, token, index, loop );	break;
		case _IF:		token = ParseIf( parent, token, index, def, loop );		break;
		case _PRINT:	token = ParsePrint( parent, token );					break;
		case _PRINTLN:	token = ParsePrint( parent, token );					break;
		case _RAND:		token = ParseRand( parent, token );						break;
		case _COMMENT:	token++;												break;
		case _SEMICOLON:token++;												break;
		case _DONE:		return token;
		case _RCURLY:	return token;
		case _ELIF:		return Error( token, E_ELIF );
		case _ELSE:		return Error( token, E_ELSE );
		default:		return Error( token, E_TOKEN );
		}
	}
	return token;
}

PTOKEN ParseDef( PTOKEN parent, PTOKEN token ) {
	AddStmt( parent, token );
	parent = token++;

	if ( IsNot( token, _IDEN ) ) return Error( token, E_IDEN );
	PTOKEN found = FindDecl( parent, token );
	if ( found != NULL && found->parent == parent->parent )
		return Error( token, E_REDEFINE );

	parent->str = token->str;
	parent->len = token->len;
	token++;
	
	if ( IsNot( token, _LPAREN ) ) return Error( token, E_LPAREN );
	token++;
	while ( token->type == _IDEN ) {
		parent->cnt++;
		token->type = _VAR;
		token = AddStmt( parent, token );
		if ( Is( token, _RPAREN ) ) break;
		if ( IsNot( token, _COMMA ) ) return Error( token, E_COMMA );
		token++;
		if ( IsNot( token, _IDEN ) ) return Error( token, E_IDEN );
	}
	parent->params = parent->stmts;
	parent->stmts = NULL;
	if ( IsNot( token, _RPAREN ) ) return Error( token, E_RPAREN );
	token++;

	INT i = 0;
	for ( PTOKEN temp = parent->params; temp != NULL; temp = temp->next )
		temp->val = parent->cnt * -1 -2 + i++;

	return ParseBlock( parent, token, 0, parent, NULL );
}

PTOKEN ParseVar( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def ) {
	AddStmt( parent, token );
	parent = token++;

	if ( def != NULL && def->frmSize == index ) def->frmSize = index + 1;

	if ( IsNot( token, _IDEN ) ) return Error( token, E_IDEN );
	PTOKEN found = FindDecl( parent, token );
	if ( found != NULL && found->parent == parent->parent )
		return Error( token, E_REDEFINE );

	parent->type = ( parent->parent->type == _ROOT ) ? _GVAR : _VAR;
	parent->val = index;
	parent->str = token->str;
	parent->len = token->len;
	token++;
	
	if ( IsNot( token, _ASSIGN ) ) return Error( token, E_ASSIGN );
	return ParseExpr( parent, token + 1 );
}

PTOKEN ParseArr( PTOKEN parent, PTOKEN token, PDWORD index, PTOKEN def ) {
	AddStmt( parent, token );
	parent = token++;

	if ( IsNot( token, _IDEN ) ) return Error( token, E_IDEN );
	PTOKEN found = FindDecl( parent, token );
	if ( found != NULL && found->parent == parent->parent )
		return Error( token, E_REDEFINE );

	parent->type = ( parent->parent->type == _ROOT ) ? _GAVAR : _AVAR;
	parent->val = *index;
	parent->str = token->str;
	parent->len = token->len;
	token++;

	parent->cnt = 1;
	if ( IsNot( token, _LBRACKET ) ) return Error( token, E_LBRACKET );
	while ( Is( token, _LBRACKET ) ) {
		token->type = _INDEX;
		token++;
		if ( IsNot( token, _NUM ) ) return Error( token, E_NUM );
		if ( token->val < 1 ) token->val = 1;
		parent->cnt *= token->val;
		token = AddStmt( parent, token );
		if ( IsNot( token, _RBRACKET ) ) return Error( token, E_RBRACKET );
		token++;
	}
	*index += parent->cnt;

	if ( def != NULL && def->frmSize < *index ) def->frmSize = *index;

	return token;
}

PTOKEN ParseIden( PTOKEN parent, PTOKEN token ) {
	if ( FindDecl( parent, token ) == NULL ) return Error( token, E_DECL );
	switch ( token->ref->type ) {
	case _DEF:	token->type = _CALL;	return ParseCall( parent, token );
	case _GVAR:	token->type = _GVAL;	return ParseAssign( parent, token );
	case _VAR:	token->type = _VAL;		return ParseAssign( parent, token );
	case _GAVAR:token->type = _GAVAL;	return ParseArrAssign( parent, token );
	case _AVAR:	token->type = _AVAL;	return ParseArrAssign( parent, token );
	}
	return Error( token, E_INTER );
}

PTOKEN ParseWhile( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop ) {
	AddStmt( parent, token );
	parent = token++;
	token = ParseCondition( parent, token );
	if ( IsError( token ) ) return token;
	return ParseBlock( parent, token, index, def, loop );
}

PTOKEN ParseIf( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop ) {
	PTOKEN _parent = parent;

	do {
		AddStmt( _parent, token );
		parent = token++;
		token = ParseCondition( parent, token );
		if ( IsError( token ) ) return token;
		token = ParseBlock( parent, token, index, def, loop );
		if ( IsError( token ) ) return token;
	} while ( Is( token, _ELIF ) );

	if ( Is( token, _ELSE ) ) {
		AddStmt( _parent, token );
		parent = token++;
		token = ParseBlock( parent, token, index, def, loop );
		if ( IsError( token ) ) return token;
	}

	return token;
}

PTOKEN ParseCondition( PTOKEN parent, PTOKEN token ) {
	if ( IsNot( token, _LPAREN ) ) return Error( token, E_LPAREN );
	token++;

	token = ParseExpr( parent, token );
	if ( IsError( token ) ) return token;

	parent->expr = parent->stmts;
	parent->stmts = NULL;
	if ( IsNot( token, _RPAREN ) ) return Error( token, E_RPAREN );

	return token + 1;
}

PTOKEN ParseBlock( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def, PTOKEN loop ) {
	if ( IsNot( token, _LCURLY ) ) return Error( token, E_LCURLY );
	token++;

	token = ParseStmt( parent, token, index, def, loop );
	if ( IsError( token ) ) return token;

	if ( IsNot( token, _RCURLY ) ) return Error( token, E_RCURLY );
	token->type = _END;

	return AddStmt( parent, token );
}

PTOKEN ParseReturn( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN def ) {
	if ( def == NULL ) return Error( token, E_RETURN );
	AddStmt( parent, token );
	parent = token++;

	parent->ref = def;
	token = ParseExpr( parent, token );
	if ( parent->stmts == NULL ) return Error( parent, E_RTN_VAL );

	return token;
}

PTOKEN ParseBreak( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN loop ) {
	if ( loop == NULL ) return Error( token, E_BREAK );
	AddStmt( parent, token );
	parent = token++;

	parent->ref = loop;
	return token;
}

PTOKEN ParseContinue( PTOKEN parent, PTOKEN token, DWORD index, PTOKEN loop ) {
	if ( loop == NULL ) return Error( token, E_CONTINUE );
	AddStmt( parent, token );
	parent = token++;

	parent->ref = loop;
	return token;
}

PTOKEN ParseAssign( PTOKEN parent, PTOKEN token ) {
	AddStmt( parent, token );
	parent = token++;
	
	if ( IsNot( token, _ASSIGN ) ) return Error( token, E_ASSIGN );
	return ParseExpr( parent, token + 1 );
}

PTOKEN ParseArrAssign( PTOKEN parent, PTOKEN token ) {
	AddStmt( parent, token );
	parent = token++;

	token = ParseIndex( parent, token );
	if ( IsError( token ) ) return token;
	
	if ( IsNot( token, _ASSIGN ) ) return Error( token, E_ASSIGN );
	parent->params = parent->stmts;
	parent->stmts = NULL;
	token = ParseExpr( parent, token + 1 );
	parent->expr = parent->stmts;
	parent->stmts = parent->params;
	parent->params = NULL;

	return token;
}

PTOKEN ParseAVal( PTOKEN parent, PTOKEN token ) {
	AddStmt( parent, token );
	parent = token++;

	return ParseIndex( parent, token );
}

PTOKEN ParseIndex( PTOKEN parent, PTOKEN token ) {
	PTOKEN size = parent->ref->stmts;

	DWORD totalSize = 1;
	for ( PTOKEN i = size; i != NULL; i = i->next ) totalSize *= i->val;

	if ( IsNot( token, _LBRACKET ) ) return Error( token, E_LBRACKET );	
	while ( Is( token, _LBRACKET ) ) {
		if ( size == NULL ) return Error( parent, E_ARRAY );
		PTOKEN index = token;
		index->type = _INDEX;
		index->val = totalSize /= size->val;		
		size = size->next;
		token = AddStmt( parent, index );
		token = ParseExpr( index, token );
		if ( IsError( token ) ) return token;
		if ( IsNot( token, _RBRACKET ) ) return Error( token, E_RBRACKET );
		token++;
	}
	if ( size != NULL ) return Error( parent, E_ARRAY );

	return token;
}

PTOKEN ParseCall( PTOKEN parent, PTOKEN token ) {
	AddStmt( parent, token );
	parent = token++;

	if ( IsNot( token, _LPAREN ) ) return Error( token, E_LPAREN );
	do {
		PTOKEN arg = token;
		arg->type = _ARGUMENT;
		token = AddStmt( parent, arg );
		if ( Is( token, _RPAREN ) ) {
			parent->stmts = NULL;
			break;
		}		
		parent->cnt++;
		token = ParseExpr( arg, token );
		if ( IsError( token ) ) return token;
	} while ( Is( token, _COMMA ) );
	if ( IsNot( token, _RPAREN ) ) return Error( token, E_RPAREN );

	if ( parent->cnt < parent->ref->cnt ) return Error( parent, E_FEW_ARG );
	if ( parent->cnt > parent->ref->cnt ) return Error( parent, E_MANY_ARG );

	return token + 1;
}

PTOKEN ParsePrint( PTOKEN parent, PTOKEN token ) {
	AddStmt( parent, token );	
	parent = token++;

	if ( IsNot( token, _LPAREN ) ) return Error( token, E_LPAREN );
	token++;

	token = ParseExpr( parent, token );
	if ( IsError( token ) ) return token;
	if ( IsNot( token, _RPAREN ) ) return Error( token, E_RPAREN );

	return token + 1;
}

PTOKEN ParseRand( PTOKEN parent, PTOKEN token ) {
	AddStmt( parent, token );	
	parent = token++;

	if ( IsNot( token, _LPAREN ) ) return Error( token, E_LPAREN );
	token++;

	token = ParseExpr( parent, token );
	if ( IsError( token ) ) return token;
	if ( IsNot( token, _RPAREN ) ) return Error( token, E_RPAREN );

	return token + 1;
}

PTOKEN ParseExpr( PTOKEN parent, PTOKEN token ) {
	return ParseTerm( parent, token, 1 );
}

PTOKEN ParseTerm( PTOKEN parent, PTOKEN token, DWORD priority ) {
	if ( priority == 7 ) return ParseFactor( parent, token );
	token = ParseTerm( parent, token, priority + 1 );
	if ( IsError( token ) ) return token;
	while ( priority == GetPriority( token->type ) ) {
		PTOKEN temp = token;
		token++;
		token = ParseTerm( parent, token, priority + 1 );
		if ( IsError( token ) ) return token;
		AddStmt( parent, temp );
	}
	return token;
}

PTOKEN ParseFactor( PTOKEN parent, PTOKEN token ) {
	PTOKEN prev = NULL;

	switch ( token->type ) {
	case _ADD: 
		return ParseFactor( parent, token + 1 );

	case _SUB:
		prev = token;
		token = ParseFactor( parent, token + 1 );
		prev->type = _SUB_UNARY;
		prev = AddStmt( parent, prev );
		return token;

	case _LPAREN:
		token = ParseExpr( parent, token + 1 );
		if ( IsError( token ) ) return token;
		if ( IsNot( token, _RPAREN ) ) return Error( token, E_RPAREN );
		return token + 1;

	case _NUM:
		return AddStmt( parent, token );

	case _IDEN:
		if ( FindDecl( parent, token ) == NULL ) return Error( token, E_DECL );
		switch ( token->ref->type ) {
		case _GVAR: token->type = _GVAL;	return AddStmt( parent, token );
		case _VAR:	token->type = _VAL;		return AddStmt( parent, token );
		case _GAVAR:token->type = _GAVAL;	return ParseAVal( parent, token );
		case _AVAR:	token->type = _AVAL;	return ParseAVal( parent, token );
		case _DEF:	token->type = _CALL;	return ParseCall( parent, token );
		default: return Error( token, E_INTER );
		}

	case _RAND:
		return ParseRand( parent, token );
	}
	return token;
}

DWORD GetPriority( TYPE eType ) {
	switch ( eType ) {
	case _MUL:	case _DIV:	case _MOD:				return 6;
	case _ADD:	case _SUB:							return 5;
	case _CA:	case _CAE:	case _CB:	case _CBE:	return 4;
	case _CE:	case _CNE:							return 3;
	case _AND:										return 2;
	case _OR:										return 1;
	default:										return 0;
	}
}

PTOKEN AddStmt( PTOKEN parent, PTOKEN child ) {
	child->parent = parent;
	if ( parent->stmts == NULL ) {
		parent->stmts = child;
		parent->stmts->prev = child;
	} else {
		parent->stmts->prev->next = child;
		parent->stmts->prev = child;
	}
	return child + 1;
}

PTOKEN FindDecl( PTOKEN parent, PTOKEN token ) {
	if ( parent == NULL ) return NULL;

	for ( PTOKEN temp = parent->params; temp != NULL; temp = temp->next ) {
		DWORD i = 0;
		if ( temp->len != token->len ) continue;
		while ( temp->str[i] == token->str[i] && i < temp->len ) i++;
		if ( temp->len == i ) {
			token->ref = temp;
			token->val = token->ref->val;
			return temp;
		}
	}

	for ( PTOKEN temp = parent->stmts; temp != NULL; temp = temp->next ) {
		switch ( temp->type ) {
		case _DEF: case _GVAR: case _VAR: case _GAVAR: case _AVAR: break; 
		default: continue;
		}
		DWORD i = 0;
		if ( temp->len != token->len ) continue;
		while ( temp->str[i] == token->str[i] && i < temp->len ) i++;
		if ( temp->len == i ) {
			token->ref = temp;
			token->val = token->ref->val;
			return temp;
		}
	}

	return FindDecl( parent->parent, token );
}

PTOKEN Error( PTOKEN token, ERROR error ) {
	token->err = error;
	return token;
}

BOOL IsError( PTOKEN token ) {
	return token->err != E_OK;
}

BOOL IsNotError( PTOKEN token ) {
	return token->err == E_OK;
}

BOOL Is( PTOKEN token, TYPE type ) {
	return token->type == type;
}

BOOL IsNot( PTOKEN token, TYPE type ) {
	return token->type != type;
}