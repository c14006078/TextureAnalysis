#ifndef CATEGORY_H
#define CATEGORY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "debug.h"
#include "constant.h"

/**
 * @file this file is about 
 *
 */
typedef struct encyclopedia{
	int cate_num;///< category number
	struct category* pcate[ MAX_CATE_NUM];///< category arrary pointer
}encyclopedia;

typedef struct category{
	char category[ MAX_NAME_LENGTH];///< category name
	int gl_num;///< the nuber of glapi class
	struct glapi *include;
}category;

typedef struct glapi{
	char name[ MAX_NAME_LENGTH];///< gl
	struct glapi* next;
} glapi;

/**
 * New the 
 */
encyclopedia* new_pedia( void);

category* new_cateNode( char* name);

glapi* new_apiNode( char* name);

encyclopedia* cfg_paser( char* file);

//int cfg_cate_num( char* file);

void show_pedia( encyclopedia* book);

void create_pattern( category* cate, char* pattern);

#endif ///< #ifndef CATEGORY_H
