	#ifndef RVFILE_H
#define RVFILE_H

////////////////////////////////////////// DECL //////////////////////////////////////////

#include <stdint.h>

#include <windows.h>

///////////////////////////////////////// MACROS /////////////////////////////////////////

#define RVF_HEDER(char) (((HFILE*)(char))-1)
/************************************ DOCS *************************************
 * Gives You the pointer to the header of an RVfile.                     X003R *
 *******************************************************************************/

////////////////////////////////////////// MAIN //////////////////////////////////////////

char* rv_openFile(const char* path);
/************************************ DOCS *************************************
 * Opens a read-only file exclusively for the compiler process.                *
 * ! Uses Win32 OpenFile under the hood.                                       *
 *                                                                             *
 *                                   RETURN                                    *
 * RVfile [X004R]                                                              *
 *                                                                             *
 *                                   ERRORS                                    *
 * Header is HFILE_ERROR on errors. Use GetLastError() for error code.         *
 *                                                                             *
 *                                    TIPS                                     *
 * Use RVF_HEDER() to get the header's pointer easily. [X003R]           X001R *
 *******************************************************************************/

uint64_t rv_filesize(char* file);
/************************************ DOCS *************************************
 * Tells You the size (in bytes) of an open RVfile.                            *
 * ! Uses Win32 GetFileSize under the hood.                                    *
 *                                                                             *
 *                                   ERRORS                                    *
 * GetLastError() might tell You the whole story(?), but the official tell is  *
 *    the lower 32 bits being INVALID_FILE_SIZE with GetLastError() being set. *
 *                                                                             *
 *                                    TIPS                                     *
 * You can use truncation to get those lower 32 bits.                    X002R *
 *******************************************************************************/

////////////////////////////////////////// META //////////////////////////////////////////

// RVfile
/************************************ DOCS *************************************
 * The way that rvfile stores files. It is a simple char* buffer storing the   *
 *    file data, which also has an HFILE preliminal header accessable through  *
 *    a pointer. To use just create a char pointer and proceed with the other  *
 *    library procedures. For RVfile creation, see rv_openFile(). [X001R]      *
 *                                                                             *
 *       [ HFILE* ] [ char* ]                                                  *
 *                      ^                                                      *
 *                                    TIPS                                     *
 * Access the header through RVF_HEDER. [X003R]                          X004R *
 *******************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////////

	#endif // RVFILE_H
