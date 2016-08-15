#include "file.h"

Bool fexist( char* fname)
{
	static int exist;
	exist = access( fname, F_OK);
	if( exist != -1){
		dprintf("file exist\n");
		return True;
	}
	else{
		printf("file not exist\n");
		return False;
	}
}

Bool mkd( char* dname, mode_t mode )
{
	if( fexist( dname)){///<TODO: we should know the relative or absolute path
		dprintf("dir already exist\n");
		mkdir( dname, mode);
		return False;
	}
	else{
		dprintf("dir not exist\n");
		return True;
	}
}

