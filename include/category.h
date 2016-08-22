#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "debug.h"
#include "constant.h"

typedef struct encyclopedia{
	int cate_num;
	struct category* pcate[ MAX_CATE_NUM];
}encyclopedia;

typedef struct category{
	char category[ MAX_NAME_LENGTH];
	int gl_num;
	struct glapi *include;
}category;

typedef struct glapi{
	char name[ MAX_NAME_LENGTH];
	struct glapi* next;
} glapi;

encyclopedia* new_pedia( void);

category* new_cateNode( char* name);

glapi* new_apiNode( char* name);

encyclopedia* cfg_paser( char* file);

//int cfg_cate_num( char* file);

void show_pedia( encyclopedia* book);

void create_pattern( category* cate, char* pattern);
