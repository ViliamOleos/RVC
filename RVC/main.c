////////////////////////////////////////// DECL //////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char* argv[]) {
	size_t sumarglen;

		CC_ENABLECOLOURCONSOLE();

	for(int i=sumarglen=0; i<argc; i++) {
		sumarglen += strlen(argv[i])+1;
	};
	
	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
