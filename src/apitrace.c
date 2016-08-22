#include "apitrace.h"

void main_dump_blob( char** fnames,	int fnum, char* dname, char** dump_file)
{
	int status;

	pid_t cpid = fork();
	syserr( cpid < 0, "fork");
	
	if( cpid == 0){//
		
		pid_t *pids = ( pid_t*) malloc( sizeof( pid_t) * fnum);

		for( int i = 0; i < fnum; i+= PROCESS_NUM )
		{

			for( int j = 0; i + j < fnum && j < PROCESS_NUM ; j++){
				pids[i+j] = fork();
				syserr( pids[i+j] < 0, "fork");

				if( pids[i+j] == 0){
					dprintf("prepare to exec_dump_file\n");

					char cmd[500];
					sprintf( cmd, "apitrace dump %s | grep blob | sort -k 2 > %s"
						, fnames[i+j], dump_file[j]);
						/*&& sort -k 2 %s > %s&& cat %s | awk '{print $2}'| uniq -c | sort -k 1"
						, fnames[i+j], outfile, outfile, outfile);*/
					dprintf("dump cmd = %s\n", cmd);
					exec_sh( cmd);
					exit( 0);
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
}

void statistic( char** file, int fnum)
{
	char buf[500];
	buf[0] = '\0';
	
	for( int i = 0; i < fnum; i++){
		strcat( buf, file[i]);
		strcat( buf, " ");
	}

	char cmd[ 500];
	sprintf( cmd, "cat %s | tr '(' ' ' | awk '{print $2}'| sort | uniq -c", buf);
	dprintf("system( cmd): %s\n", cmd);
	system( cmd);
}

void main_filter( char** fnames,	int fnum, char* pattern, char** filter_file)
{
	int status;

	pid_t cpid = fork();
	syserr( cpid < 0, "fork");
	
	if( cpid == 0){//
		
		pid_t *pids = ( pid_t*) malloc( sizeof( pid_t) * fnum);

		for( int i = 0; i < fnum; i+= PROCESS_NUM )
		{

			for( int j = 0; i + j < fnum && j < PROCESS_NUM ; j++){
				pids[i+j] = fork();
				syserr( pids[i+j] < 0, "fork");

				if( pids[i+j] == 0){
					dprintf("prepare to exec_dump_file\n");

					char cmd[500];
					sprintf( cmd, "cat %s | grep '%s' | sort -k 2 > %s"
						, fnames[i+j], pattern , filter_file[j]);
					dprintf("match cmd = %s\n", cmd);
					exec_sh( cmd);
					exit( 0);
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
