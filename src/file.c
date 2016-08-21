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

bool mkd( char* dname, mode_t mode )
{
	if( fexist( dname)){///<TODO: we should know the relative or absolute path
		dprintf("dir %s already exist\n", dname);
		mkdir( dname, mode);
		return false;
	}
	else{
		dprintf("dir %s not exist\n", dname);
		return true;
	}
}

void apen_dir_file( char* dir, char** file, int n, char** out)
{
	assert( fexist( dir) && "dir not exist");

	for ( int i = 0; i < n; i++){
		strcpy( out[i], dir);
		if( out[i][ strlen( out[i]) - 1] != '/' ) strcat( out[i], "/");
		assert( fexist( file[i]) && "file not exist");
		strcat( out[i], basename( file[i]));
	}
}

void apen_suffix( char** in, char* str, int n)
{
	for ( int i = 0; i < n; i++)
		strcat( in[i], str);
}
