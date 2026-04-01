////////////////////////////////////////// DECL //////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>

#include <windows.h>

///////////////////////////////////// COLOUR CONSOLE /////////////////////////////////////

#define CC_ENABLECOLOURCONSOLE() \
{ \
	HANDLE console; DWORD consoleState; \
 \
	console = GetStdHandle(STD_OUTPUT_HANDLE); \
	if(console == INVALID_HANDLE_VALUE) { \
		printf("GetStdHandle dead ;(\n"); \
	} \
 \
	GetConsoleMode(console, &consoleState); \
	consoleState |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; \
	SetConsoleMode(console, consoleState); \
}

////////////////////////////////////////// FILE //////////////////////////////////////////

char* rv_openFile(const char* path) {
	OFSTRUCT openstruct; 
	HFILE* nufile = malloc(sizeof(HFILE)+1); // HEDER + NULL IN BUF

	*nufile = OpenFile(
		path, &openstruct,
		OF_READ | OF_SHARE_DENY_READ
	);
	*(char*)(nufile+1) = '\0';

	return((char*)nufile);
}

////////////////////////////////////////// MAIN //////////////////////////////////////////

int main() {
	char* mainfile;

	CC_ENABLECOLOURCONSOLE();

	mainfile = rv_openFile("main.c");
	printf("Opened file main.c: %X {!=%X}", *(HFILE*)mainfile, HFILE_ERROR);

	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
