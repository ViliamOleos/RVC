	#ifndef RVFILE_H
#define RVFILE_H

////////////////////////////////////////// DECL //////////////////////////////////////////

#include <stdint.h>
#include <stdlib.h>

#include <windows.h>

///////////////////////////////////////// MACROS /////////////////////////////////////////

#define RVF_HEDER(char) (((HFILE*)(char))-1)
/************************************ DOCS *************************************
 * Gives You the pointer to the header of an RVfile. [X004R]             X003R *
 *******************************************************************************/

////////////////////////////////////////// MAIN //////////////////////////////////////////

char* rv_openFile(const char* path);
/************************************ DOCS *************************************
 * Opens a read-only file exclusively for the compiler process.                *
 * ! Uses Win32 OpenFile under the hood.                                       *
 * Buffer is initialised with a single \0.                                     *
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

char* rv_rbufFile(char* file, uint64_t newlen);
/************************************ DOCS *************************************
 * "Rebuffers" or resizes a buffer of an RVfile by reallocating it.            *
 *                                                                             *
 *                                    ARGS                                     *
 * newlen - new amount of bytes that the RVfile can hold                       *
 *                                                                             *
 *                                   RETURN                                    *
 * RVfile [X004R]                                                        X005R *
 *******************************************************************************/

char rv_readFile(char* file, uint32_t bytes);
/************************************ DOCS *************************************
 * Transfers [bytes] bytes of data from disk to the RVfile buffer specified.   *
 * ! Uses Win32 ReadFile under the hood. To be absolutely honest, just a good  *
 *    wrapper over ReadFile, much more than any of the other functions.        *
 * Specifically compatible with Windows 7.                                     *
 *                                                                             *
 *                                   RETURN                                    *
 * Bool, where false (0) indicates a failure.                                  *
 *                                                                             *
 *                                   ERRORS                                    *
 * As said in RETURN section. Use GetLastError for error code.                 *
 *                                                                             *
 *                                    TIPS                                     *
 * Use rv_filesize() [X002R] and rv_rbufFile() [X005R] in combination to       *
 *    prepare Your RVfile for reading. [X004R]                           X002R *
 *******************************************************************************/

char rv_readFile_batch(char* file, uint64_t bytes);
/************************************ DOCS *************************************
 * Similar to rv_readFile [X002R], but calls ReadFile multiple times in a loop *
 *    , allowing to bypass the usual 32bit restriction.                        *
 *                                                                             *
 *                                   RETURN                                    *
 * Bool, where false (0) indicates a failure.                                  *
 *                                                                             *
 *                                   ERRORS                                    *
 * Mostly the same. Returns if one of the loop calls fail.               X006R *
 *******************************************************************************/

uint64_t rv_filesize(char* file);
/************************************ DOCS *************************************
 * Tells You the size (in bytes) of an open RVfile, to be more exact, the size *
 *    on disk. [X004R]                                                         *
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
