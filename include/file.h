#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <libgen.h>

#include "debug.h"
#include "constant.h"


//typedef enum { False, True} Bool; ///< we use C99 <stdbool.h>

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
bool fexist( char* fname);

bool mkd( char* dname, mode_t mode);

void apen_dir_file( char* dir, char** file, int n, char** out);///< i fail with strdup
void apen_suffix( char** in, char* str, int n);

char* ret_cwd( void);

char* ret_realpath( char* path);
