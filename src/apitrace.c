#include "apitrace.h"

pinstr new_instr( char* instrName)
{
	pinstr hNode = ( pinstr) malloc( sizeof( instr));

	///<*hNode = { .name = instrName, .count = 1, .plink = NULL, .last = NULL};
	hNode->name = instrName; hNode->count = 1; hNode->calls = NULL; hNode->last = NULL; hNode->next = NULL;

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

ptracef new_tracef( int fnum, char** fname)
{
	ptracef tfile = (ptracef) malloc( sizeof( tracef) * fnum);

	for( register int i = 0; i < fnum; ++i)
	{
		tfile[i].name = fname[i];
		tfile[i].p = NULL;
	}

	return tfile;
}


/*void blob_calls_stat
{

}

void trace_analysis()
{
	
}

fill_instr();*/

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





void apitrace_dump_pipe( char *tracef)
{
	pid_t cpid = fork();
	int status;

	fd pi[2];
	pipe( pi);

	if( cpid < 0){
		eprintf( "fork error");
		exit( EXIT_FAILURE);
	}
	else if ( cpid == 0){///< Child proc
		close( pi[ in]);
		dup2( pi[out], STDOUT_FILENO);

		execlp("apitrace", "apitrace", "dump", tracef);///< we can use execl but we should use the absolute path
		exit( 0);
	}
	else{///< Parent proc
		close( pi[ out]);

		waitpid( cpid, &status, 0);
		dprintf("Child complete\n");
	}
}

void apitrace_dump_file( char *tracef, char* outfile)
{
	pid_t cpid = fork();
	int status;

	if( cpid < 0){
		eprintf( "fork error");
		exit( EXIT_FAILURE);
	}
	else if ( cpid == 0){///< Child proc
		
		fd fout = creat( outfile, 0644); ///< == open( "test", O_WRONLY | O_CREAT | O_TRUNC );
		if( fout == -1){ perror("create"); exit( 0);}
		dup2( fout, STDOUT_FILENO);
		close( fout);

		execlp("apitrace", "apitrace", "dump", tracef);///< we can use execl but we should use the absolute path
		exit( 0);
	}
	else{///< Parent proc

		waitpid( cpid, &status, 0);
		dprintf("Child complete\n");
	}
}
