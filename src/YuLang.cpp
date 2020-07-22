#include "YuLang.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const DWORD SOURCE_SIZE = 65536;
const DWORD TOKENS_SIZE = 4096;
const DWORD CODES_SIZE = 4096;

CHAR  source[ SOURCE_SIZE ];
TOKEN tokens[ TOKENS_SIZE ];
CODE  codes[ CODES_SIZE ];
PCODE currentCode = NULL;
PCODE prevCode = NULL;

VOID   InitScanner( VOID );
VOID   Scan( PCSTR pcInput, PTOKEN token );
PTOKEN Parse( PTOKEN token );
PTOKEN GenerateCode( PTOKEN token, PCODE code );
VOID   InitExcutor();
PCODE Execute( PCODE code, PPCODE prevCode );

VOID YuInit() {
	InitScanner();
}

VOID YuTokenize( PCSTR src, PTOKEN token ) {
	Scan( src, token );
}

PTOKEN YuBuild( PCSTR src ) {
	PTOKEN result = NULL;
	
	currentCode = NULL;
	memset( source, 0, sizeof(CHAR) * SOURCE_SIZE );
	memset( tokens, 0, sizeof(TOKEN) * TOKENS_SIZE );
	memset( codes, 0, sizeof(CODE) * CODES_SIZE );

	strcpy_s( source, SOURCE_SIZE, src );

	Scan( source, tokens );
	result = Parse( tokens );
	if ( result->err != E_OK ) return result;

	result = GenerateCode( tokens, codes );
	if ( result->err != E_OK ) return result;

	for ( INT i = 0; i < CODES_SIZE; i++ ) codes[i].idx = i;
	currentCode = codes;
	InitExcutor();

	return tokens;
}

PCODE YuRun() {
	while ( currentCode != NULL && currentCode->type != _DONE )
		currentCode = Execute( currentCode, &prevCode );

	return currentCode;
}

PCODE YuContinue() {
	if ( currentCode == NULL || currentCode->type == _DONE )
		return currentCode;

	do currentCode = Execute( currentCode, &prevCode );
	while ( currentCode != NULL && 
			currentCode->type != _DONE &&
			currentCode->breakPoint == FALSE );

	return currentCode;
}

PCODE YuStepOver() {
	if ( currentCode == NULL || currentCode->type == _DONE )
		return currentCode;

	return currentCode = Execute( currentCode, &prevCode );
}
