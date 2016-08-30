#include "apitrace.h"

void main_dump_blob( char** fnames,	int fnum, char** dump_files)
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
					dprintf("prepare to exec_dump_files\n");

					char cmd[500];
					sprintf( cmd, "apitrace dump %s | grep blob | sort -k 2 > %s", fnames[i+j], dump_files[j]);
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
	else{
		printf("\n*****************************************\nI am dumping the trace file for blob calls\n****************************************\n");
		
		time_t time = get_time();	
		do{
			waitpid( cpid, &status , WNOHANG);
			if( get_time() - time == 1 ){///<TODO: printf() after sleep will be suspend, we should overcome it
				putchar('.');
				time = get_time();
			}
		}while( !WIFEXITED( status));

		printf("\n");
	}
	dprintf("all dump is finish\n");
}

/**
 * Use sh to execute the Shell commands.
 *
 * @param cmd command line string
 */

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

void main_filter( char** fnames,	int fnum, char* pattern, char** filter_files)
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
					dprintf("prepare to exec_main_filter\n");

					char cmd[500];
					sprintf( cmd, "cat %s | grep '%s' | sort -k 2 > %s"
						, fnames[i+j], pattern , filter_files[j]);
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
	else{
		printf("\n*****************************************\nI am clustering the GL API referenced by group.cfg\n****************************************\n");
		
		time_t time = get_time();	
		do{
			waitpid( cpid, &status , WNOHANG);
			if( get_time() - time == 1 ){///<TODO: printf() after sleep will be suspend, we should overcome it
				putchar('.');
				time = get_time();
			}
		}while( !WIFEXITED( status));

		printf("\n");
	}
	dprintf("all dump is finish\n");
}
/*
void main_dump_bin( char** fnames,	int fnum, char* callset, char** filter_file)
{
	int status;
	char* cwd = ret_cwd();
	
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

					char cmd[1000];
					sprintf( cmd, "apitrace dump %s -calls=%s --blobs", fnames[i+j], callset);
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
	else{
		printf("\n*****************************************\n\
					I am dumping the specify character Blob (binary file)\n\
					****************************************\n");
		
		pid_t ret_pid;
		while( (ret_pid = waitpid( cpid, &status , WNOHANG)) > 0){
			sleep( 1);
			printf(".");
		}
	}
	dprintf("all dump is finish\n");
}*/
