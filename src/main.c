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
#include "category.h"


/* typedef enum { False, True} Bool;*/
#define ARRAY_SIZE( arr) (sizeof( arr) / sizeof( arr[0]))///< it only work on arrary

void errUsage( void );
void dir_situation( void);
char** dump_name( char** fnames, int fnum, char* dname);
void statistic( char** dump_file, int fnum);
char** creat_blob( char** fnames, int fnum, char* dname);
char*** creat_group( char** dump_file, int fnum, encyclopedia* group);
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
	
	const int fnum = index;

	//ptracef tfiles = new_tracef( fnum, fnames);

	/**
	 *	dump file:
	 *
	 */
	time_t start, end;
	char** dump_file = creat_blob( fnames, fnum, dname);


	start = get_time();

	main_dump_blob( fnames, fnum, dname, dump_file);

	end = get_time();
	printf("All dump work is complete. It take %lf sec\n", diff_time( start, end));

	/**
	 *
	 *	statistic
	 *
	 */

	statistic( dump_file, fnum);

	encyclopedia* group = cfg_paser( "group.cfg");

	char*** filter_file = creat_group( dump_file, fnum, group);

	char** pattern = ( char**) malloc( sizeof( char*) *group->cate_num);

	folder** fders = ( folder**) malloc( sizeof( folder*) * group->cate_num);

	for( int i = 0; i < group->cate_num; i++){
		pattern[i] = (char* ) malloc( sizeof( char) * MAX_PATTERN_LENGTH);
		create_pattern( group->pcate[i], pattern[i]);
		main_filter( dump_file, fnum, pattern[i], filter_file[i]);
		fders[i] = load_context( filter_file[i], fnum);
	}

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

	printf("dir is exist, are you sure to dump into it? y/n\n");
	
	while( (tmp =getchar()) != '\n' ){

		dprintf("getchar() = %c\n", tmp);

		switch ( tmp){
			case 'y':
				return;
			case 'n':
				errUsage();
			default:
				;
		}
		printf("dir is exist, are you sure to dump into it? y/n\n");
	}
}

char** creat_blob( char** fnames, int fnum, char* dname)
{
	/*Init outfile name*/
	char** outfile = (char **) malloc( sizeof( char*) * fnum);
	for( int i = 0; i < fnum; i++){
		outfile[i] = (char*) malloc( sizeof( char) * MAX_FILE_PATH);
		outfile[i][0] = '\0';
	}
	/*append suffix*/
	apen_dir_file( dname, fnames, fnum, outfile);
	apen_suffix( outfile, "_blob.calls", fnum);	//strcat( outfile, ".blob.calls.txt"); ///< string cat can't handle the '.' at begin

	return outfile;
}

char*** creat_group( char** dump_file, int fnum, encyclopedia* group)
{
	char*** set = (char***) malloc( sizeof(char **) * group->cate_num);

	for( int i = 0; i < group->cate_num; i++)
	{
		set[i] = ( char **) malloc( sizeof( char*) * group->pcate[i]->gl_num);
		char* cate_name = group->pcate[i]->category;
		for( int j = 0; j < fnum; j++)
		{
			set[i][j] = (char *) malloc( sizeof( char) * MAX_FILE_PATH);
			strcpy( set[i][j], dump_file[j]);
			strcat( set[i][j],"_");
			strcat( set[i][j], cate_name);
			strcat( set[i][j],"_match");
		}
	}

	return set;
}
