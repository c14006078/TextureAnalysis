#include "context.h"

folder* new_folder( void)
{
	folder* fder = ( folder*) malloc( sizeof( folder));

	fder->fnum = 0;
	for( int i = 0; i < MAX_TRACE_NUM; i++) fder->file[i] = NULL;

	return fder;
}

tfile* new_tfile( char* fname)
{
	tfile* file = ( tfile*) malloc( sizeof( tfile));

	strcpy( file->name, fname); file->head = NULL;

	return file;
}

instr* new_instr( char* insname)
{
	instr* inst = ( instr*) malloc( sizeof( instr));

	strcpy( inst->name, insname); inst->count = 0;
	inst->numpara = 0; inst->head = NULL;
	inst->last = NULL;inst->next = NULL;

	return inst;
}

context* new_context( lint call)
{
	context* cnt = ( context*) malloc ( sizeof( context));

	cnt->call = call; cnt->var = NULL; cnt->val = NULL;
	cnt->next = NULL;

	return cnt;
}
