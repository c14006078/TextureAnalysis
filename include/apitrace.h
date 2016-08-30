#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h> ///< define "pid_t"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "constant.h"

#include "debug.h"
#include "file.h"
#include "context.h"

/**
 * Extract OpenGL calls with blob ( Binary Large Object ) from trace file
 *	then we can classify it and choose what we want.
 *	 texture pixel is belong to blob, but first we extract all of them
 *
 *		IN: 	fnames
 *		OUT:	dump_file
 *
 * @param fnames 		"trace" file path arrary
 * @param fnum 			input file number
 * @param dump_files	"destination" file path arrary
 *
 */
void main_dump_blob( char** fnames,	int fnum, char** dump_files);

/**
 * Use sh to execute the Shell commands.
 *
 *	@param cmd command string
 */
void exec_sh( char* cmd);

/**
 *	output the statistic report.
 */
void statistic( char** file, int fnum);

/**
 * Find the calls matching to the specfy pattern and we can
 *
 * @param fnames 		"blob" file path arrary
 * @param fnum 			file number
 * @param pattern 	Regular Expression to select what we want
 * @param filter_files	"destination" file path arrary
 */
void main_filter( char** fnames, int fnum, char* pattern, char** filter_files);
