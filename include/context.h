#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "debug.h"
#include "constant.h"


typedef long long int lint;///< avoid the overflow

/*typedef struct clink *plink;
typedef struct instr *pinstr;
typedef struct tracef *ptracef;*/

typedef struct context{
	lint call; ///< calls maybe overflow
	char** var;//
	char** val;//
	struct context* next;
}context;

typedef struct instr{
	char name[MAX_INSTR_LENGTH];
	int count;
	int numpara;//
	context* head;
	context* last;
	struct instr* next;
}instr;

typedef struct tfile{
	char name[MAX_FILE_PATH];
	instr* head;
} tfile;

typedef struct folder{
	int fnum;
	tfile* file[ MAX_TRACE_NUM];
}folder;

folder* new_folder( void);

tfile* new_tfile( char* fname);

instr* new_instr( char* insname);

context* new_context( lint call);

instr* init_instr( tfile* tf, char* name, lint call);

folder* load_context( char** fnames, int fnum);

void parse_tfile( FILE* f, tfile* tf);
