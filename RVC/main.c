////////////////////////////////////////// DECL //////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include "rvfile.h"

///////////////////////////////////// COLOUR CONSOLE /////////////////////////////////////

#define CC_ENABLECOLOURCONSOLE() \
do { \
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
} while(0)


////////////////////////////////////////// MAIN //////////////////////////////////////////

int main() {
	char* mainfile; uint64_t mainfile_siz;
	char tempReturn;

		CC_ENABLECOLOURCONSOLE();

	mainfile = rv_openFile("main.c");
	mainfile_siz = rv_filesize(mainfile);

		printf("File size: %llu\n", mainfile_siz);

	mainfile = rv_rbufFile(mainfile, mainfile_siz+1);
	tempReturn = rv_readFile_batch(mainfile, mainfile_siz);
	mainfile[mainfile_siz]='\0';

		printf("%s\n", mainfile);
		printf("\n> %hhu", tempReturn);
	
	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
