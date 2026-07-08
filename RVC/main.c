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

char* sourceFile = NULL;

/// 64 (0 through 63) flags
uint64_t flags = 0;
#define FLAGS_SETTRUE(flag) do { flags |= 1<<(flag); } while(0)
#define FLAGS_GET(flag) ((flags>>(flag))&1)
#define FLAGS_HELP 0

#define ERREXF(msg, ...) \
	do { printf(CC_RED msg CC_NULL, __VA_ARGS__); goto exfiltration; } while(0)

int main(int argc, char* argv[]) {
	char* p; char* b;

	char** argvend;
	char* argdat;

	uint64_t sourceFile_siz;

	uint64_t strsiz;

		CC_ENABLECOLOURCONSOLE();

	argdat = NULL;

	/// TODO
	for(argvend=(argv++)+argc; argv<argvend; argv++) {
		if(strchr("-~", *((p=*argv)+1))) {
			for(b=p+1; *b!='\0'; b++) { }
			argdat = realloc(argdat, strsiz=b-p-1);
			memcpy(argdat, p+2, strsiz);
		} switch(*p) {
			case '-':
				switch(*(++p)) { case 'h':

							helpact:
						FLAGS_SETTRUE(FLAGS_HELP);

					break; case '-':

						if(!strcmp(argdat, "help")) { goto helpact; }
						else { ERREXF("Unrecognised verbose dash argument \"--%s\"\n", argdat); }

					break; 

					default: ERREXF("Unrecognised dash argument \"-%c\"\n", *p); break;
				}
			break; case '~':
				switch(*(++p)) { case 'f':

							fileact:
						argv++; p=*argv;
						strsiz = strlen(p);
						sourceFile = realloc(sourceFile, ++strsiz);
						memcpy(sourceFile, p, strsiz);

					break; case '~':

						if(!strcmp(argdat, "file")) { goto fileact; }
						else { ERREXF("Unrecognised verbose tilde argument \"~~%s\"\n", argdat); }

					break;

					default: ERREXF("Unrecognised tilde argument \"-%c\"\n", *p); break;
				}
			break;
		}
	}

	if(FLAGS_GET(FLAGS_HELP)) {
		printf("NO HELP FOR U THIS YEAR\n");
	} else {
		if(sourceFile) {
				argdat = sourceFile;
			sourceFile = rv_openFile(sourceFile);
			sourceFile = rv_rbufFile(sourceFile, (sourceFile_siz=rv_filesize(sourceFile))+1);
			if(!rv_readFile_batch(sourceFile, sourceFile_siz)) {
				ERREXF("Failed to read \"%s\".\n", argdat);
			}
				free(argdat);
			sourceFile[sourceFile_siz]='\0';
			printf("%s\n", sourceFile);
		} else {
			ERREXF("No ~f filename argument specified.\n", NULL);
		}
	}

exfiltration:
	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
