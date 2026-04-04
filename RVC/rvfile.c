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

uint64_t rv_filesize(char* file) {
	DWORD filesiz[2];
	*filesiz = GetFileSize((HANDLE)*RVF_HEDER(file), filesiz+1);
	return(*(uint64_t*)filesiz);
}
