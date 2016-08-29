#include "file.h"

bool fexist( char* fname)
{
	static int exist;
	exist = access( fname, F_OK);
	if( exist != -1){
		dprintf("file %s exist\n", fname);
		return true;
	}
	else{
		dprintf("file %s not exist\n", fname);
		return false;
	}
}

bool isdir( char* dname)
{
	struct stat st;
	if( stat( dname, &st) == 0 && S_ISDIR( st.st_mode)){
		dprintf("%s is a dir\n", dname);
		return true;
	}
	else{
		dprintf("%s isn't a dir\n", dname);
		return false;
	}
}

bool mkd( char* dname, mode_t mode )
{
	if( fexist( dname)){///<TODO: we should know the relative or absolute path
		dprintf("dir %s already exist\n", dname);
		return false;
	}
	else{
		dprintf("dir %s not exist\n", dname);
		mkdir( dname, mode);
		return true;
	}
}

void apen_dir_file( char* dir, char** file, int n, char** out_files)
{
	assert( fexist( dir) && "dir not exist");

	for ( int i = 0; i < n; i++){
		strcpy( out_files[i], dir);
		if( out_files[i][ strlen( out_files[i]) - 1] != '/' ) strcat( out_files[i], "/");
		//assert( fexist( file[i]) && "file not exist");
		strcat( out_files[i], basename( file[i]));
	}
}

void apen_suffix( char** in, int n, char* suffix)
{
	for ( int i = 0; i < n; i++)
		strcat( in[i], suffix);
}

char* ret_cwd( void)
{
	char* cwd = ( char*) malloc( sizeof( char) * MAX_FILE_PATH);

	syserr( !getcwd( cwd, MAX_FILE_PATH), "getcwd");
	return cwd;
}

char* ret_realpath( char* path)
{
	char* real = (char*) malloc( sizeof( char) * MAX_FILE_PATH);

	realpath( path, real);
	dprintf("realpath( %s)  = %s\n", path, real);

	return real;
}
