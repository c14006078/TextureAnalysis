#include <stdio.h>
#include "file.h"

int main( int argc, char* argv[])
{
	char* exist = argc > 1 ? argv[1]: NULL;

	if( fexist( exist)) printf("File exist\n");
	else printf("fexist() return false\n");

	char* dir = argc > 2 ? argv[2]: NULL;
	if( mkd( dir, 0700)) printf("Dir create\n");
	else printf("mkd() return false");

	if( isdir( dir)) printf("isdir() is correct!\n");
	else printf("isdir() fault\n");

	return 0;
}
