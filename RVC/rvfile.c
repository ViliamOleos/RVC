#include "rvfile.h"

///////////////////////////////////////// ACTION /////////////////////////////////////////

char* rv_openFile(const char* path) {
	OFSTRUCT openstruct; 
	HFILE* nufile = malloc(sizeof(HFILE)+1); // HEDER + NULL IN BUF

	*nufile = OpenFile(
		path, &openstruct,
		OF_READ | OF_SHARE_EXCLUSIVE
	); nufile++;
	*(char*)nufile = '\0';

	return((char*)nufile);
}

void rv_closeFile(void* file) {
	file = RVF_HEDER(file);
	CloseHandle(*(HANDLE*)file);
	free(file);
}

char* rv_rbufFile(char* file, uint64_t newlen) {
	file = (char*)((HFILE*)realloc( RVF_HEDER(file), sizeof(HFILE)+newlen )+1);
	return(file);
}

char rv_readFile(char* file, uint32_t bytes) {
	DWORD bytesread;
	return(ReadFile(
		(HANDLE)*RVF_HEDER(file),
		file,
		bytes,
		&bytesread,
		NULL
	)); 
}

char rv_readFile_batch(char* file, uint64_t bytes) {
	DWORD bytesread;
	uint64_t times = bytes/(DWORD)-1;

	while(times--) {
		if(!(bytesread = ReadFile(
			(HANDLE)*RVF_HEDER(file),
			file,
			(DWORD)-1,
			&bytesread,
			NULL
		))) {
			return(bytesread);
		}

		file += (DWORD)-1;
	}

	return(ReadFile(
		(HANDLE)*RVF_HEDER(file),
		file,
		bytes%(DWORD)-1,
		&bytesread,
		NULL
	)); 
}

////////////////////////////////////////// DESC //////////////////////////////////////////

uint64_t rv_filesize(char* file) {
	DWORD filesiz[2];
	*filesiz = GetFileSize((HANDLE)*RVF_HEDER(file), filesiz+1);
	return(*(uint64_t*)filesiz);
}

//////////////////////////////////////////////////////////////////////////////////////////
