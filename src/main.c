/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include "debug.h"
#include "file.h"
#include "apitrace.h"
#include "_time.h"
#include "category.h"
#include "md5.h"

/* typedef enum { False, True} Bool;*/
#define ARRAY_SIZE( arr) (sizeof( arr) / sizeof( arr[0]))///< it only work on arrary

void errUsage( void );
void dir_situation( void);
char** dump_name( char** fnames, int fnum, char* dname);
void statistic( char** dump_file, int fnum);
char** creat_blob( char** fnames, int fnum, char* dname);
char*** creat_group( char** dump_file, int fnum, encyclopedia* group);
void bin_dump( char* blob_dir,char* match_file, char* tfile);
void main_md5( char* group_dir);

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
	
	char** cate_dir = ( char**) malloc( sizeof( char*) * group->cate_num);
	char** group_dir = ( char**) malloc( sizeof( char*) * group->cate_num);
	
	for( int i = 0; i < group->cate_num; i++){
		cate_dir[i] = ( char*) malloc( sizeof( char) * MAX_FILE_PATH);
		group_dir[i] = ( char*) malloc( sizeof( char) * MAX_FILE_PATH);
		strcpy( cate_dir[i], group->pcate[i]->category);
	}

	apen_dir_file( dname, cate_dir, group->cate_num, group_dir);

	char* cwd = ret_cwd();
	for( int i = 0; i < group->cate_num; i++){
		mkdir( group_dir[i], 0700);
		for( int j = 0; j < fnum; j++)
			bin_dump( group_dir[i], ret_realpath( filter_file[i][j]), ret_realpath(fnames[j]));
		main_md5( group_dir[i]);
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

void bin_dump( char* blob_dir,char* match_file, char* tfile)
{
	FILE* fp = fopen( match_file, "r");
	
	char buf[300], *p, calls[20], callset[1000], cmd[1500];
	int k = 0;
	lint call;

	memset( callset, '\0', 1000);
	do{
		fgets( buf, 300, fp);
		if( (p = strchr( buf, '\n')) != NULL)
			*p = '\0';

		if( (p = strchr( buf, '\n')) != NULL)
			*p = '\0';
		sscanf( buf, "%lld ", &call);
		sprintf( calls, "%lld", call);
		strcat( callset, calls);
		k++;
		if( k % 6 == 5)
		{
			dprintf("callset = %s\n", callset);
			sprintf( cmd, "cd %s && apitrace dump --calls=%s --blobs %s  && cd -", blob_dir, callset, tfile);
			dprintf("cmd = %s\n", cmd);
			system( cmd);
			memset( buf, '\0', 1000);
		}
		else{
			strcat( callset, ",");
		}
	}while( !feof(fp) );

	fclose( fp);
}

/*char* collect_call( char* tfile)
{
	FILE* fp = fopen( tfile, "r");
	
	char buf[50], *p;
	do{
		fgets( buf, 50, fp);
		if( (p = strchr( buf, '\n')) != NULL){
			*p = '\0';

			dir->pcate[ dir->cate_num++]  = ncate;
			strcpy( ncate->category, buf);
			tmp = ncate->include;
		}
		else{
			if( tmp == NULL){
				ncate->include = new_apiNode( buf + 1);
				ncate->gl_num++;
				tmp = ncate->include;
			}
			else{
				tmp->next = new_apiNode( buf + 1);
			}
		}
	}while( !feof( fp) );

	fclose( fp);
}*/
void main_md5( char* group_dir)
{
	DIR* dir = opendir( group_dir);
	struct dirent* entry;
	
	char dst[200], cmd[500];
	while( (entry = readdir( dir)) != NULL)
	{
		memset( dst, '\0', 200);
		strcpy( dst, group_dir);
		strcat( dst, "/");
		strcat( dst, entry->d_name);
		sprintf( cmd, "md5=$(md5sum %s|awk '{print $1}') && cp %s final/$md5", dst, dst);///<TODO: I create final/ by default, so it need to be auto
		dprintf("cmd = %s\n", cmd);
		system(cmd);
	}
}
