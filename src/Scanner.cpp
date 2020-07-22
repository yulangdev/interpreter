#include "YuLang.h"

typedef enum {
	CT_IDEN		= 0x01,
	CT_NUM		= 0x02,
	CT_STR		= 0x04,
	CT_COMMENT	= 0x08,
	CT_WS		= 0X10,
	CT_LF		= 0X20,
} CHAR_TYPE;

DWORD GetTokenLength( CHAR_TYPE type, PCSTR src );
DWORD GetInteger( PCSTR str );
TYPE GetKeywordType( PCSTR str, DWORD iden_len );
TYPE Get2OperatorType( PCSTR str );
TYPE Get1OperatorType( PCSTR str );

TYPE  gFirstChar[256] = { _UNKNOWN, };
DWORD gRemainingChar[256] = { 0, };

VOID InitScanner( VOID ) {
	for ( DWORD i = 0;   i <= 255; i++ ) gFirstChar[i] = _UNKNOWN;
	for ( DWORD i = 9;   i <= 13;  i++ ) gFirstChar[i] = _WS;
	for ( DWORD i = 32;  i <= 32;  i++ ) gFirstChar[i] = _WS;
	for ( DWORD i = 48;  i <= 57;  i++ ) gFirstChar[i] = _NUM;
	for ( DWORD i = 65;  i <= 90;  i++ ) gFirstChar[i] = _IDEN;
	for ( DWORD i = 97;  i <= 122; i++ ) gFirstChar[i] = _IDEN;

	gFirstChar[ '\0' ] = _DONE;
	gFirstChar[ '\n' ] = _LF;
	gFirstChar[ '\"' ] = _STR;
	gFirstChar[ '#' ] = _COMMENT;
	gFirstChar[ '_' ] = _IDEN;

	for ( DWORD i = 0;   i <= 255; i++ ) gRemainingChar[i] = CT_COMMENT;
	for ( DWORD i = 9;   i <= 13;  i++ ) gRemainingChar[i] |= ( CT_WS );
	for ( DWORD i = 32;  i <= 32;  i++ ) gRemainingChar[i] |= ( CT_WS );
	for ( DWORD i = 32;  i <= 126; i++ ) gRemainingChar[i] |= ( CT_STR );
	for ( DWORD i = 'a'; i <= 'z'; i++ ) gRemainingChar[i] |= ( CT_IDEN );
	for ( DWORD i = 'A'; i <= 'Z'; i++ ) gRemainingChar[i] |= ( CT_IDEN );
	for ( DWORD i = '0'; i <= '9'; i++ ) gRemainingChar[i] |= ( CT_IDEN | CT_NUM );

	gRemainingChar[ '\t' ] |= ( CT_STR );
	gRemainingChar[ '\n' ] = CT_LF;
	gRemainingChar[ '\n' ] &= ( ~CT_COMMENT );
	gRemainingChar[ '\"' ] &= ( ~CT_STR );
	gRemainingChar[ '_' ] |= ( CT_IDEN );
}

VOID Scan( PCSTR input, PTOKEN token ) {
	DWORD line = 1;
	DWORD column = 1;
	DWORD offset = 0;
	while ( input != NULL ) {
		token->offset = offset;
		token->row = line;
		token->col = column;		
		token->str = input;
		token->type = gFirstChar[ *input ];

		BOOL isSet = TRUE;
		switch ( token->type ) {
		case _DONE: return;

		case _LF:
			token->len = GetTokenLength( CT_LF, input );
			line += token->len;
			column = 1 - token->len;
			isSet = FALSE;
			break;

		case _WS:
			token->len = GetTokenLength( CT_WS, input );
			isSet = FALSE;
			break;

		case _COMMENT:
			token->len = GetTokenLength( CT_COMMENT, input );
			break;

		case _STR:
			token->len = GetTokenLength( CT_STR, input +1 ) +2;
			isSet = FALSE;
			break;

		case _NUM:
			token->len = GetTokenLength( CT_NUM, input );
			token->val = GetInteger( input );
			break;

		case _IDEN:
			token->len = GetTokenLength( CT_IDEN, input );
			token->type = GetKeywordType( input, token->len );
			break;

		default:
			token->len = 2;
			token->type = Get2OperatorType( input );
			if ( token->type != _UNKNOWN ) break;
			token->len = 1;
			token->type = Get1OperatorType( input );
		}
		offset += token->len;
		column += token->len;
		input += token->len;
		if ( isSet ) token++;
	}
}

DWORD GetTokenLength( CHAR_TYPE type, PCSTR src ) {
	DWORD i = 0;
	while ( gRemainingChar[ (unsigned char)src[i] ] & type ) i++;
	return i;
}

TYPE GetKeywordType( PCSTR str, DWORD iden_len ) {
	struct t {
		PCSTR str;
		TYPE type;
		DWORD padding;
	} keywords[] = {
		{ "var",		_VAR		},	{ "arr",		_ARR		},
		{ "def",		_DEF		},	{ "return",		_RETURN		},
		{ "while",		_WHILE		},	{ "break",		_BREAK		},	{ "continue",	_CONTINUE	},
		{ "if",			_IF 		},	{ "elif",		_ELIF		},	{ "else",		_ELSE 		},
		{ "print",		_PRINT		},	{ "println",	_PRINTLN	},	{ "rand",		_RAND		},
	};

	for ( DWORD i = 0; i < sizeof( keywords ) / sizeof( struct t ); i++ ) {
		PCSTR keyword = keywords[i].str;
		DWORD j = 0;

		while ( keyword[ j ] != '\0' ) j++;
		if ( j != iden_len ) continue;

		while ( ( j > 0 ) && ( keyword[j-1] == str[j-1] ) ) j--;
		if ( j == 0 ) return keywords[i].type;
	}
	return _IDEN;
}

TYPE Get2OperatorType( PCSTR str ) {
	struct t {
		PCSTR str;
		TYPE type;
		DWORD padding;
	} keyword[] = {
		{ "&&",	_AND				},	{ "||",	_OR					},
		{ "==",	_CE					},	{ "!=",	_CNE				},
		{ "<=",	_CBE				},	{ ">=",	_CAE				},
	};

	for ( DWORD i = 0; i < sizeof( keyword ) / sizeof( struct t ); i++ ) {
		if ( ( keyword[i].str[0] == str[0] ) && ( keyword[i].str[1] == str[1] ) )
			return keyword[i].type;
	}
	return _UNKNOWN;
}

TYPE Get1OperatorType( PCSTR str ) {
	struct t {
		PCSTR str;
		TYPE type;
		DWORD padding;
	} keyword[] = {
		{ "(",	_LPAREN				},	{ ")",	_RPAREN				},
		{ "{",	_LCURLY				},	{ "}",	_RCURLY				},
		{ "[",	_LBRACKET			},	{ "]",	_RBRACKET			},
		{ "+",	_ADD			 	},	{ "-",	_SUB			 	},
		{ "*",	_MUL			 	},	{ "/",	_DIV			 	},
		{ "%",	_MOD		 		},	{ "=",	_ASSIGN				},
		{ "<",	_CB					},	{ ">",	_CA				 	},
		{ ",",	_COMMA				},	{ ";",	_SEMICOLON			},
	};

	for ( DWORD i = 0; i < sizeof( keyword ) / sizeof( struct t ); i++ ) {
		if ( keyword[i].str[0] == str[0] )
			return keyword[i].type;
	}
	return _UNKNOWN;
}

DWORD GetInteger( PCSTR str ) {
	DWORD result = 0;	
	for ( DWORD i = 0; gRemainingChar[ str[i] ] & CT_NUM; i++ )
		result = ( result * 10 ) + ( str[i] - 48 );
	return result;
}
