#include "category.h"

encyclopedia* new_pedia( void )
{
	dprintf("new_pedia\n");
	encyclopedia* dir = ( encyclopedia*) malloc( sizeof( encyclopedia) );
	dir->cate_num = 0;
	for( int i = 0; i < MAX_CATE_NUM; i++) dir->pcate[i] = NULL;

	return dir;
}

category* new_cateNode( char* name)
{
	category* cate = ( category*) malloc( sizeof( category));
	strcpy( cate->category, name);
	cate->gl_num = 0;
	cate->include = NULL;

	return cate;
}

glapi* new_apiNode( char* name)
{
	glapi* api = ( glapi*) malloc( sizeof( glapi));
	strcpy( api->name, name);
	api->next = NULL;

	return api;
}

/*TEMP for one category*/
encyclopedia* cfg_paser( char* file)
{
	//int cn = cfg_cate_num( file);//, gindex = 0;
	
	//dprintf("cn = %d\n", cn);

	assert( fexist( file) && "file doesn't exist");
	FILE* f = fopen( file, "r");
	syserr( !f, "fopen");

	encyclopedia* dir = new_pedia();
	
	glapi* tmp;	
	category* ncate;

	dprintf("prepare to while loop\n");
	char buf[50], *p;
	do{
		fgets( buf, 50, f);
		if( (p = strchr( buf, '\n')) != NULL)
			*p = '\0';

		if( buf[0] != '\t'){
			ncate = new_cateNode( buf);
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
	}while( !feof(f) );

	fclose( f);

	return dir;
}

/*int cfg_cate_num( char* file)
{
	assert( fexist( file) && "file doesn't exist");
	FILE* f = fopen( file, "r");
	syserr( !f, "fopen");

	int cate_num = 0;
	do{
		fgets( cfg, 50, f);
		if( cfg[0] != '\t')
			cate_num++;
	}while( !feof(f))
	
	close( f);

	return cate_num;
}*/

void show_pedia( encyclopedia* book)
{
	
	glapi* tmp;

	for( int i = 0; i < book->cate_num ; i++){
		
		category* cate = book->pcate[ i];

		tmp = cate->include;
		printf("Category: %s\n", cate->category);

		if( tmp == NULL) printf("\tnothing in this category\n");
		while( tmp != NULL)
		{
			printf("\t%s\n", tmp->name);
			tmp = tmp->next;
		}
	}
}

void create_pattern( category* cate, char* pattern)
{
	glapi* p = cate->include;
	assert( ( p != NULL) && "category include nothing");
	for( int i = 0; p != NULL;  p = p->next, i++)
	{
		if( i == 0) strcat( pattern, p->name);
		else{
			strcat( pattern, "\\|");
			strcat( pattern, p->name);
		}
	}
	dprintf("pattern = %s\n", pattern);
}
