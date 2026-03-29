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

////////////////////////////////////////// MAIN //////////////////////////////////////////

int main() {
	CC_ENABLECOLOURCONSOLE();

	printf("\e[35mHello, World!\e[0m\n");

	return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
