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
	char* args;

	CC_ENABLECOLOURCONSOLE();

	{
		int i; char* p;
		size_t sumarglen;
		uint16_t argvlens[argc];

		if(argc==1) { args=""; } else {

			for(sumarglen=0, i=1; i<argc; i++) 
				{ argvlens[i]=strlen(argv[i]); sumarglen+=argvlens[i]; }

			args = malloc(sumarglen);

			for(p=args,i=1; i<argc; i++) {
				memcpy(p, argv[i], argvlens[i]);
				p += argvlens[i];
				*p = ' '; p++;
			} p[-1] = '\0';

		}
	}

	printf("%s\n", args);
	
	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
