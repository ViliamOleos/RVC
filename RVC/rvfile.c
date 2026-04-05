#include "rvfile.h"

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

uint64_t rv_filesize(char* file) {
	DWORD filesiz[2];
	*filesiz = GetFileSize((HANDLE)*RVF_HEDER(file), filesiz+1);
	return(*(uint64_t*)filesiz);
}
