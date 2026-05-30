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

/// 64 (0 through 63) flags
uint64_t flags = 0;
#define FLAGS_SETTRUE(flag) do { flags |= 1<<(flag); } while(0)
#define FLAGS_GET(flag) ((flags>>(flag))&1)
#define FLAGS_HELP 0

int main(int argc, char* argv[]) {
	char* p; char* b;
	char** argvend;
	char* argdat;
	uint16_t strsiz;

	argdat = NULL;

		CC_ENABLECOLOURCONSOLE();

	for(argvend=(argv++)+argc; argv<argvend; argv++) {
		switch(*(p=*argv)) {
			case '-':
				switch(*(++p)) {
					case 'h':
						FLAGS_SETTRUE(FLAGS_HELP);
					break; case '-':
						for(b=p; *b!='\0'; b++) { }
						argdat = realloc(argdat, b-p);
						memcpy(argdat, p+1, b-p);

						if(!strcmp(argdat, "help")) {
							FLAGS_SETTRUE(FLAGS_HELP);
						}
					break; default:
						printf(CC_RED"Unrecognised dash argument \"-%c\"\n"CC_NULL, *p);
						goto exfiltration;
					break;
				}
			break; case '~':
				switch(*(++p)) {
					case 'f':
						argv++; p=*argv;
						strsiz = strlen(p);
						argdat = realloc(argdat, strsiz+1);
						memcpy(argdat, p, strsiz+1);
						printf("\targdat = \"%s\"\n", argdat);
					break; case '~':
						for(b=p; *b!='\0'; b++) { }
						argdat = realloc(argdat, b-p);
						memcpy(argdat, p+1, b-p);

						if(!strcmp(argdat, "file")) {
							argv++; p=*argv;
							strsiz = strlen(p);
							argdat = realloc(argdat, strsiz+1);
							memcpy(argdat, p, strsiz+1);
							printf("\targdat = \"%s\"\n", argdat);
						}
					break; default:
						printf(CC_RED"Unrecognised tilde argument \"~%c\"\n"CC_NULL, *p);
						goto exfiltration;
					break;
				}
			break;
		}
	}

	if(FLAGS_GET(FLAGS_HELP)) {
		printf("Hello, World!\n");
	}

exfiltration:
	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
