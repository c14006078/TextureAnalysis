/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "debug.h"
#include "file.h"


/* typedef enum { False, True} Bool;*/
#define ARRAY_SIZE( arr) (sizeof( arr) / sizeof( arr[0]))///< it only work on arrary

void errUsage( void );
void dir_situation( void);

/**
 *	./main OUT_DIR TRACEFILE1 TRACEFILE2 ...
 *
 */
char *Usage = "Usage: ./main OUT_DIR TRACEFILE1 TRACEFILE2 ...\n";

int main( int argc, char **argv)
{
	int index = 0;

	if( argc < 2) errUsage();

	char* dname = NULL;
	char** fnames = (char**) malloc( sizeof( char*) * (argc - 2));
	dprintf("argc = %d, trace file num = %d\n",argc,(argc-2));
	
	///< command line parser
	for( int i = 1; i < argc; ++i){
		char *arg = argv[i];

		if ( i == 1 && fexist( arg)){
			dir_situation();
			dname = arg;
		}
		else if ( i == 1){
			dname = arg;
			mkdir( dname, 0700);
		}
			
		if( i > 1 && fexist( argv[i]))
			fnames[index++] = arg;
		else if( i > 1)
			errUsage();
	}


	free( fnames);
}

void errUsage( void)
{
	eprintf( Usage);
	exit(0);
}


void dir_situation( void)
{
	char tmp;
	
	while(1){
		printf("dir is exist, are you sure to dump into it? y/n\n");
		if( tmp = getchar()){
			switch ( tmp){
					case 'y':
						return;
					case 'n':
						errUsage();
					default:
						;
			}
		}
	}
}
