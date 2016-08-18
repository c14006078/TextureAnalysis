#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "debug.h"

#define MAX_NAME_LENGTH 30

typedef struct category *encyclopedia;

typedef struct category{
	char category[ MAX_NAME_LENGTH];
	struct glapi *include;
}category;

typedef struct glapi{
	char name[ MAX_NAME_LENGTH];
	struct glapi* next;
} glapi;

encyclopedia new_pedia( int cn);

glapi* new_apiNode( char* name);

encyclopedia cfg_paser( char* file);

void show_pedia( encyclopedia book, int cn);
