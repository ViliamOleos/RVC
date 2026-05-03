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

//////////////////////////////////// ARGV HOMOGENISER ////////////////////////////////////

/// dest is a pointer to string 'cause weird stuff, just didn't bother
void argv_homogeniser(char** dest, int argc, char** argv) {
	int i; char* p;
	uint16_t sumarglen;
	uint16_t argvlens[argc];

	if(argc==1) { *dest=""; } else {

		for(sumarglen=0, i=1; i<argc; i++) { argvlens[i]=strlen(argv[i]); sumarglen+=argvlens[i]+1; }

		*dest = malloc(sumarglen);

		for(p=*dest,i=1; i<argc; i++) {
			memcpy(p, argv[i], argvlens[i]);
			p += argvlens[i];
			*p = ' '; p++;
		} p[-1] = '\0';

	}
}

////////////////////////////////////////// MAIN //////////////////////////////////////////

#define EXFILTRATE(...) \
	printf(__VA_ARGS__); goto exfiltration;

#define IL_FDASHARG() do { \
		while((0<*p)&&(*p<33)) { p++; } /* skip whitespace */ \
		switch(*p) { \
			case '\'': \
				printf("string!\n"); \
			break; \
			 \
			case '\0': \
				printf("oops bye-bye\n"); \
			break; \
			 \
			default: \
				printf("content"); \
			break; \
		} \
	} while(0)

#define IL_DASHARGS() do { \
		p+=2; \
		switch(p[-1]) { \
			case 'f': \
				IL_FDASHARG(); \
			break; \
			 \
			default: \
				EXFILTRATE(CC_RED "Unrecognised dash argument -%c.\n" CC_NULL, p[-1]); \
			break; \
		} \
	} while(0)

int main(int argc, char* argv[]) {
	char* p;
	char* args;

		CC_ENABLECOLOURCONSOLE();

	argv_homogeniser(&args, argc, argv);

	for(p=args; *p!='\0'; p++) {
		switch(*p) {
			case '-':
				IL_DASHARGS();
			break;
		}
	}
	
exfiltration:
	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
