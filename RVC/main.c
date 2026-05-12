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

#define CC_NULL "\e[0m"

#define CC_RED "\e[31m"

////////////////////////////////////////// MAIN //////////////////////////////////////////

int main(int argc, char* argv[]) {
	char** argvend;

		CC_ENABLECOLOURCONSOLE();

	for(argvend=argv+argc; argv<argvend; argv++) {
		printf("\"%s\" ", *argv);
	}

	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
