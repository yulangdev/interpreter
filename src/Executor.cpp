#include "YuLang.h"

const DWORD OS_SIZE = 100;
const DWORD SS_SIZE = 4096;
const DWORD DS_SIZE = 4096;

DWORD OSP = 0;
DWORD EBP = 0;
DWORD ESP = 0;
INT OS[ OS_SIZE ] = { 0, };
INT SS[ SS_SIZE ] = { 0, };
INT DS[ DS_SIZE ] = { 0, };

void Print( int i );
void Println();
int  Rand( int i );
void ShowErrorMessage( const char* msg, PCODE code );

VOID InitExcutor() {
	OSP = ESP = EBP = 0;
	for ( DWORD i = 0; i < CODES_SIZE; i++ ) OS[i] = DS[i] = SS[i] = 0;
}

PCODE Execute( PCODE code, PPCODE prevCode ) {
	*prevCode = code;

	if ( OS_SIZE <= OSP || SS_SIZE <= ESP ) {
		ShowErrorMessage( "run-time error: stack overflow", code );
		return NULL;
	}

	switch( code->type ) {
	case _GMOV: case _GVAL:
		if ( DS_SIZE <= OS[ OSP -1 ] ) {
			ShowErrorMessage( "run-time error: access violation at address", code );
			return NULL;
		}
		break;

	case _MOV: case _VAL:
		if ( SS_SIZE <= EBP + OS[ OSP -1 ] ) {
			ShowErrorMessage( "run-time error: access violation at address", code );
			return NULL;
		}
		break;

	case _DIV: case _MOD:
		if ( OS[ OSP -1 ] == 0 ) {
			ShowErrorMessage( "run-time error: devide by zero exception", code );
			return NULL;
		}
		break;
	}

	switch ( code->type ) {
	case _PRINT:	Print( OS[ OSP-- -1 ] );							break;
	case _PRINTLN:	Println();											break;
	case _RAND:		OS[ OSP -1 ] = Rand( OS[ OSP -1 ] );				break;

	case _JZ:		if ( OS[ --OSP ] == 0 ) return code->addr;			break;
	case _JNZ:		if ( OS[ --OSP ] != 0 ) return code->addr;			break;
	case _JMP:		return code->addr;									break;

	case _PUSH:		SS[ ESP++ ] = OS[ OSP-- -1 ];						break;
	case _POP:		ESP--;												break;

	case _PUSH_EBP:	SS[ ESP++ ] = EBP;									break;
	case _POP_EBP:	EBP = SS[ EBP-1 ]; ESP--;	 						break;

	case _SAV_ESP:	EBP = ESP;											break;
	case _RST_ESP:	ESP = EBP;											break;
	case _INC_ESP:	ESP += code->val;									break;

	case _CALL:		return (PCODE)code->addr;							break;
	case _RETURN:	return (PCODE)SS[ --ESP ];							break;
	case _DEC_OSP:	OSP--;												break;

	case _GMOV:		DS[ OS[ OSP -1 ] ] = OS[ OSP -2 ];		 OSP -= 2;	break;
	case _MOV:		SS[ EBP + OS[ OSP -1 ] ] = OS[ OSP -2 ]; OSP -= 2;	break;

	case _NUM:		OS[ OSP++ ] = code->val;							break;		
	case _GVAL:		OS[ OSP -1 ] = DS[ OS[ OSP -1 ] ];					break;
	case _VAL:		OS[ OSP -1 ] = SS[ EBP + OS[ OSP -1 ] ];			break;

	case _SUB_UNARY:OS[ OSP -1 ]   = -OS[ OSP -1 ];						break;
	case _ADD:		OS[ OSP-- -2 ] = OS[ OSP -2 ] +  OS[ OSP -1 ];		break;
	case _SUB:		OS[ OSP-- -2 ] = OS[ OSP -2 ] -  OS[ OSP -1 ];		break;
	case _MUL:		OS[ OSP-- -2 ] = OS[ OSP -2 ] *  OS[ OSP -1 ];		break;
	case _DIV:		OS[ OSP-- -2 ] = OS[ OSP -2 ] /  OS[ OSP -1 ];		break;
	case _MOD:		OS[ OSP-- -2 ] = OS[ OSP -2 ] %  OS[ OSP -1 ];		break;
	case _CA:		OS[ OSP-- -2 ] = OS[ OSP -2 ] >  OS[ OSP -1 ];		break;
	case _CB:		OS[ OSP-- -2 ] = OS[ OSP -2 ] <  OS[ OSP -1 ];		break;
	case _CE:		OS[ OSP-- -2 ] = OS[ OSP -2 ] == OS[ OSP -1 ];		break;
	case _CNE:		OS[ OSP-- -2 ] = OS[ OSP -2 ] != OS[ OSP -1 ];		break;
	case _CAE:		OS[ OSP-- -2 ] = OS[ OSP -2 ] >= OS[ OSP -1 ];		break;
	case _CBE:		OS[ OSP-- -2 ] = OS[ OSP -2 ] <= OS[ OSP -1 ];		break;
	case _AND:		OS[ OSP-- -2 ] = OS[ OSP -2 ] && OS[ OSP -1 ];		break;
	case _OR:		OS[ OSP-- -2 ] = OS[ OSP -2 ] || OS[ OSP -1 ];		break;
	}
	
	return ( code->type == _DONE ) ? code : code + 1;
}
