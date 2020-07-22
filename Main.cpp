#include "Main.h"
#include <stdio.h>
#include <time.h>

using namespace System;
using namespace System::Windows::Forms;

void ShowErrorMessage( const char* msg, PCODE code ) {
	char buf[64] = { 0, };
	sprintf_s( buf, 64, "0x%08X %s\r\n", (unsigned int)code, msg );
	YuLang::Main::mainForm->Print( buf );
	YuLang::Main::mainForm->ShowMessage( msg );
}

void Print( int i ) {
	char buf[32] = { 0, };
	sprintf_s( buf, 32, "%d ", i );
	YuLang::Main::mainForm->Print( buf );
}

void Println() {
	YuLang::Main::mainForm->Print( "\r\n" );
}

int Rand( int i ) {
	if ( i == 0 ) i = 1;
	return rand() % i;
}

[STAThreadAttribute]
void Main(array<String^>^ args) {
	srand((unsigned int)time(0));

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	YuLang::Main form;
	YuLang::Main::mainForm = %form;
	Application::Run(%form);
}