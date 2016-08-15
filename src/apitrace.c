#include "apitrace.h"

pinstr new_instr( char* instrName)
{
	pinstr hNode = ( pinstr) malloc( sizeof( instr));

	///<*hNode = { .name = instrName, .count = 1, .plink = NULL, .last = NULL};
	hNode->name = instrName; hNode->count = 1; hNode->calls = NULL; hNode->last = NULL;

	return hNode;
}

plink new_clink( long call)
{
	plink cNode = ( plink) malloc ( sizeof( clink));

	cNode->call = 0; cNode->next = NULL;
	return cNode;
}

pinstr append_instr( pinstr hNode, long call)
{
	plink cNode = new_clink( call);
	hNode->count++;
	if( hNode->calls == NULL){
		hNode->calls = cNode;
		hNode->last = cNode;
	}
	else
		hNode->last = cNode;

	return hNode;
}


/*blob_calls_stat
{
	
}*/

void apitrace_dump( char *tracef)
{
	pid_t cpid = fork();
	int status;

	if( cpid < 0){
		eprintf( "fork error");
		exit( EXIT_FAILURE);
	}
	else if ( cpid == 0)///< Child proc
		execlp("apitrace", "apitrace", "dump", tracef);///< we can use execl but we should use the absolute path
	else///< Parent proc
		waitpid( cpid, &status, 0);
		dprintf("Child complete\n");
}
