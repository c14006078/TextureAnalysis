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

void apen_dir_file( char* dir, char* file, char* out)
{
	assert( fexist( dir) && "dir not exist");

	strcpy( out, dir);
	if( out[ strlen( out) - 1] != '/' )strcat( out, "/");
	assert( fexist( file) && "file not exist");
	strcat( out, basename( file));
}

