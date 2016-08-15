#include "file.h"

bool fexist( char* fname)
{
	static int exist;
	exist = access( fname, F_OK);
	if( exist != -1){
		dprintf("file exist\n");
		return true;
	}
	else{
		printf("file not exist\n");
		return false;
	}
}

bool mkd( char* dname, mode_t mode )
{
	if( fexist( dname)){///<TODO: we should know the relative or absolute path
		dprintf("dir already exist\n");
		mkdir( dname, mode);
		return false;
	}
	else{
		dprintf("dir not exist\n");
		return true;
	}
}

