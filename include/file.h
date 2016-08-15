#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "debug.h"


typedef enum { False, True} Bool;

/**
 *	Check file exist or not.
 *		man 2 access or follow http://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
 *
 *	@param fname file name
 *
 *	@return -1 is not exist
 *
 *		man 2 access
 *		follow http://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
 */
Bool fexist( char* fname);


Bool mkd( char* dname, mode_t mode);
