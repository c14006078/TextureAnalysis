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

instr* init_instr( tfile* tf, char* name, lint call)
{
	instr* tmp = tf->head, *in;
	if( tmp == NULL)
		in = ( tf->head = new_instr( name));
	else{
		while( tmp->next != NULL)
			tmp = tmp->next;

		in = ( tmp->next = new_instr( name));
	}

	assert( (in != NULL) && "init instr error");
	in->count++;
	in->last = ( in->head = new_context( call));

	return in;
}

/*context* apen_context( context* p, lint call)
{
	context* cnt = ( context*) malloc ( sizeof( context));

	cnt->call = call; cnt->var = NULL; cnt->val = NULL;
	cnt->next = NULL;

	return cnt;
}*/

folder* load_context( char** fnames, int fnum)
{
	folder* fder = new_folder();

	fder->fnum = fnum;
	for( int i = 0; i < fnum; i++)
		fder->file[i] = new_tfile( fnames[ i]);

	FILE** fs = ( FILE**) malloc( sizeof( FILE*));
	for( int i = 0; i < fder->fnum; i++)
		fs[i] = fopen( fnames[i], "r");

	for( int i = 0; i < fder->fnum; i++)
	{
		parse_tfile( fs[i], fder->file[i]);
		fclose( fs[i]);
	}

	return fder;
}

void parse_tfile( FILE* f, tfile* tf)
{
	instr* plast = tf->head;
	char buf[400], *p, instrname[ MAX_INSTR_LENGTH];
	
	lint call;
	
	do{
		memset( instrname, '\0', sizeof( instrname));
		fgets( buf, 400, f);
		if( (p = strchr( buf, '\n')) != NULL)///< it work with extendition
			p = '\0';

		sscanf( buf, "%lld %[^(]", &call, &instrname);

		if( plast == NULL)
			plast = (tf->head = init_instr( tf, instrname, call));
		else{
			if( strcmp( plast->name, instrname) == 0){//same
				plast->last = (plast->last->next = new_context( call));
				plast->count++;
			}
			/*else if( instrcmp( instr, file->head)){//TODO: If we don't use the sort we shall implement it
					
			}*/
			else
				plast = init_instr( tf, instrname, call);
		}
	}while( !feof(f));
}
