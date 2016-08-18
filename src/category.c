#include "category.h"

encyclopedia new_pedia( int cn)
{
	dprintf("new_pedia\n");
	encyclopedia dir = ( encyclopedia) malloc( sizeof( category) * cn );
	dir->include = NULL;
	dir->category[0] = '\0';

	return dir;
}

glapi* new_apiNode( char* name)
{
	glapi* api = ( glapi*) malloc( sizeof( glapi));
	strcpy( api->name, name);
	api->next = NULL;

	return api;
}

/*TEMP for one category*/
encyclopedia cfg_paser( char* file)
{
	assert( fexist( file) && "file doesn't exist");
	FILE* f = fopen( file, "r");
	syserr( !f, "fopen");

	int cn = 2, cindex = 0;//, gindex = 0;
	
	encyclopedia dir = new_pedia( cn);
	
	glapi* tmp;	
	encyclopedia ndir = dir;

	dprintf("prepare to while loop\n");
	char buf[50], *p;
	do{
		fgets( buf, 50, f);
		if( (p = strchr( buf, '\n')) != NULL)
			*p = '\0';

		if( buf[0] != '\t'){
			ndir = dir + cindex++;
			strcpy( ndir->category, buf);
			tmp = ndir->include;
		}
		else{
			if( tmp == NULL){
				ndir->include = new_apiNode( buf + 1);
				tmp = ndir->include;
			}
			else{
				tmp->next = new_apiNode( buf + 1);
			}
		}
	}while( !feof(f) );

	fclose( f);

	return dir;
}

void show_pedia( encyclopedia book, int cn)
{
	
	glapi* tmp;
	encyclopedia ndir;

	for( int i = 0; i < cn ; i++){
		
		ndir = book +i;
		tmp = ndir->include;

		printf("Category: %s\n", ndir->category);

		if( tmp == NULL) printf("\tnothing in this category\n");
		while( tmp != NULL)
		{
			printf("\t%s\n", tmp->name);
			tmp = tmp->next;
		}
	}
}
