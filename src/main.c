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
#include "apitrace.h"
#include "_time.h"


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
	
	//ptracef tfiles = new_tracef( fnum, fnames);

	time_t start, end;

	int status, fnum = index;

	for( int i = 0; i < fnum; i++)
	{
		char cmd[100] = "apitrace dump ";
		strcat( cmd, fnames[i]);
		strcat( cmd, " |grep blob");
		dprintf("cmd = %s\n", cmd);
		system(cmd);
	}

	/*for( int i = 0; i < fnum; i++)
	{
		pid_t cpid = fork();
		start = get_time();
		
		if( cpid < 0){
			eprintf("fork error");
			exit( EXIT_FAILURE);
		}
		else if( cpid == 0){
	
			//execl("/bin/sh", "sh", "apitrace dump ../f.trace/abgr.trace | grep blob", NULL);
			system( "apitrace dump " fnames[i] " | grep blob");
			end = get_time();
			dprintf("All work is complete. It take %lf sec\n", diff_time( start, end));
			exit( 0);
		}
		else{
			waitpid( cpid, &status , 0);
			end = get_time();
			dprintf("All work is complete. It take %lf sec\n", diff_time( start, end));
		}
	}*/
	//statistic( );

	free( fnames);

	return 0;
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
		tmp = getchar();
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
