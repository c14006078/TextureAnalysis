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

void main_dump_blob( char** fnames,	int fnum, char* dname)
{
	int status;

	pid_t cpid = fork();
	syserr( cpid < 0, "fork");
	
	if( cpid == 0){//
		
		pid_t *pids = ( pid_t*) malloc( sizeof( pid_t) * fnum);

		for( int i = 0; i < fnum; i+= PROCESS_NUM )
		{
			dprintf("for i = %d, pid = %d\n", i, pids[i]);

			for( int j = 0; i + j < fnum && j < PROCESS_NUM ; j++){
				pids[i+j] = fork();
				syserr( pids[i+j] < 0, "fork");

				if( pids[i+j] == 0){
					dprintf("prepare to exec_dump_file\n");
				
					char outfile[200];
					
					apen_dir_file( dname, fnames[i+j], outfile);
					//strcat( outfile, ".blob.calls.txt"); ///< string cat can't handle the '.' at begin
					strcat( outfile, "_blob.calls");
					dprintf("outfile = %s\n", outfile);

					char cmd[400];
					sprintf( cmd, "apitrace dump %s | grep blob > %s", fnames[i+j], outfile);
					dprintf("dump cmd = %s\n", cmd);
					exec_sh( cmd);
					dprintf("If u see this, it means exec not exit\n");
				}
			}
			for( int k = 0; k + i < fnum && k < PROCESS_NUM ; k++)
			{
				dprintf("wait for pids[%d] = %d\n", k, (int) pids[i+k]);
				waitpid( pids[i+k], &status, 0);
			}
		}
		dprintf("fork main dump is done\n");
		exit(0);
	}
	else
		waitpid( cpid, &status , 0);
	dprintf("all dump is finish\n");
}

void exec_sh( char* cmd)
{
	int ret = execl( "/bin/sh", "sh", "-c", cmd, NULL);
	syserr( ret == -1, "execl");
	exit( 0);
}
