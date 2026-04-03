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

#define RVF_HEDER(char) (((HFILE*)(char))-1)

char* rv_openFile(const char* path) {
	OFSTRUCT openstruct; 
	HFILE* nufile = malloc(sizeof(HFILE)+1); // HEDER + NULL IN BUF

	*nufile = OpenFile(
		path, &openstruct,
		OF_READ | OF_SHARE_DENY_READ
	); nufile++;
	*(char*)nufile = '\0';

	return((char*)nufile);
}

uint64_t rv_filesize(char* file) {
	DWORD filesiz[2];
	*filesiz = GetFileSize((HANDLE)*RVF_HEDER(file), filesiz+1);
	return(*(uint64_t*)filesiz);
}

////////////////////////////////////////// MAIN //////////////////////////////////////////

int main() {
	char* mainfile;

	CC_ENABLECOLOURCONSOLE();

	mainfile = rv_openFile("a.txt");
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
