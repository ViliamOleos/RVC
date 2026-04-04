////////////////////////////////////////// DECL //////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>

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
	char* mainfile;

	CC_ENABLECOLOURCONSOLE();

	mainfile = rv_openFile("main.c");
	printf("File size: %llu\n", rv_filesize(mainfile));


		/*
	DWORD bytesread;

	ReadFile(
		*RVF_HEDER(mainfile),
		mainfile,
		, // max read
		bytesread,
		NULL
	);
		*/

	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
