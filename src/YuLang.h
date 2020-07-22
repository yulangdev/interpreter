#pragma once

#define NULL				0
#define TRUE				1
#define FALSE				0

typedef	int					BOOL,	*PBOOL;
typedef	char				CHAR,	*PCHAR;
typedef wchar_t				WCHAR,	*PWCHAR;
typedef int					INT,	*PINT;
typedef long				LONG,	*PLONG;
typedef float				FLOAT,	*PFLOAT;

typedef	unsigned char		BYTE,	*PBYTE;
typedef	unsigned short		WORD,	*PWORD;
typedef	unsigned long		DWORD,	*PDWORD;
typedef	unsigned long long	QWORD,	*PQWORD;
typedef	void				VOID,	*PVOID;

typedef const char*			PCSTR;

typedef enum _TYPE {
	_UNKNOWN,	_DONE,			_ROOT,		_NOP,		_ERROR,

	/* International Functions */
	_PRINT,		_PRINTLN,		_RAND,

	/* Special Chacter */
	_ASSIGN,	_COMMA,			_SEMICOLON,
	_LPAREN,	_RPAREN,		_ARGUMENT,
	_LCURLY,	_RCURLY,
	_LBRACKET,	_RBRACKET,		_INDEX,
	_LF,		_WS,

	/* Token Type */
	_IDEN,		_NUM,			_STR,		_COMMENT,

	/* Keywords */
	_DEF,		_RETURN,
	_WHILE,		_CONTINUE,		_BREAK,
	_IF,		_ELIF,			_ELSE,
	_END,
	_ARR,

	/* Binary Operator */
	_ADD,	_SUB,	_MUL,	_DIV,	_MOD,
	_CA,	_CB,	_CE,	_CNE,	_CAE,	_CBE,
	_AND,	_OR,

	/* Unary Operator */
	_SUB_UNARY,

	/* Description */
	_DEF_BEGIN,		_DEF_END,
	_WHILE_BEGIN,	_WHILE_END,
	_IF_BEGIN,		_ELIF_BEGIN,	_ELSE_BEGIN,	_IF_END,
	_ASSIGN_BEGIN,	_ASSIGN_END,
	_INDEX_BEGIN,	_INDEX_END,		_INDEX_SEP,
	_CALL_BEGIN,	_CALL_END,		_CALL_SEP,
	_PRINT_BEGIN,	_PRINT_END,
	_RETURN_BEGIN,	_RETURN_END,

	/* Instructor */
	_GMOV,		_MOV,			
	_GVAR,		_GVAL,
	_VAR,		_VAL,
	_GAVAR,		_GAVAL,
	_AVAR,		_AVAL,
	_CALL,

	_PUSH,		_POP,		
	_PUSH_EBP,	_POP_EBP,	
	_SAV_ESP,	_RST_ESP,	_INC_ESP,
	_DEC_OSP,
	_JMP,		_JZ,		_JNZ,
} TYPE;

typedef enum _ERROR {
	E_OK,
	E_ENTRY,
	E_REDEFINE,
	E_INTER,
	E_STRAY,	// 안쓰는 문자 스캐너에서 발생
	E_COMMA,
	E_LPAREN,
	E_RPAREN,
	E_LCURLY,
	E_RCURLY,	
	E_LBRACKET,	
	E_RBRACKET,
	E_ASSIGN,
	E_TOKEN,
	E_IDEN,
	E_NUM,
	E_EXPR,
	E_FUNC,
	E_FEW_ARG,
	E_MANY_ARG,
	E_DECL,
	E_ELIF,
	E_ELSE,
	E_BREAK,
	E_CONTINUE,
	E_RETURN,
	E_RTN_VAL,
	E_PROC_RTN,
	E_ARRAY,
	E_COUNT,
} ERROR;

typedef struct _CODE {
	TYPE type;
	union {
		INT val;
		struct _CODE *addr;
	};

	DWORD len;
	PCSTR str;

	DWORD idx;
	BOOL  breakPoint;
} CODE, *PCODE, **PPCODE;

typedef struct _TOKEN {
	TYPE type;
	union {
		INT val;
		struct _CODE *addr;
	};

	DWORD len;
	PCSTR str;

	DWORD row;
	DWORD col;
	DWORD offset;

	ERROR err;
	PCSTR msg;

	DWORD cnt;
	DWORD frmSize;

	struct _TOKEN *ref;

	struct _TOKEN *parent;
	struct _TOKEN *prev;
	struct _TOKEN *next;
	
	struct _TOKEN *params;
	struct _TOKEN *expr;
	struct _TOKEN *stmts;
} TOKEN, *PTOKEN, **PPTOKEN;

/* Global Variables */
extern const DWORD CODES_SIZE;
extern const DWORD OS_SIZE;
extern const DWORD SS_SIZE;
extern const DWORD DS_SIZE;

extern DWORD OSP;
extern DWORD EBP;
extern DWORD ESP;
extern INT OS[];
extern INT SS[];
extern INT DS[];

extern TOKEN tokens[];
extern CODE  codes[];

extern PCODE prevCode;

/* Extern Functions */
VOID   YuInit();
VOID   YuTokenize( PCSTR src, PTOKEN token );
PTOKEN YuBuild( PCSTR src );
PCODE  YuRun();
PCODE  YuContinue();
PCODE  YuStepOver();

/* ETC */
PCSTR GetTypeName( TYPE type );
PCSTR GetErrorMessage( PTOKEN token );
