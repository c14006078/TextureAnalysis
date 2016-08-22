#include "apitrace.h"

void main_dump_blob( char** fnames,	int fnum, char* dname)
{
	int status;

	pid_t cpid = fork();
	syserr( cpid < 0, "fork");
	
	if( cpid == 0){//
		
		pid_t *pids = ( pid_t*) malloc( sizeof( pid_t) * fnum);

		/*Init outfile name*/
		char** outfile = (char **) malloc( sizeof( char*) * fnum);
		for( int i = 0; i < fnum; i++){
			outfile[i] = (char*) malloc( sizeof( char) * MAX_FILE_PATH);
			outfile[i][0] = '\0';
		}
		/*append suffix*/
		apen_dir_file( dname, fnames, fnum, outfile);
		apen_suffix( outfile, "_blob.calls", fnum);	//strcat( outfile, ".blob.calls.txt"); ///< string cat can't handle the '.' at begin


		for( int i = 0; i < fnum; i+= PROCESS_NUM )
		{

			for( int j = 0; i + j < fnum && j < PROCESS_NUM ; j++){
				pids[i+j] = fork();
				syserr( pids[i+j] < 0, "fork");

				if( pids[i+j] == 0){
					dprintf("prepare to exec_dump_file\n");

					char cmd[500];
					sprintf( cmd, "apitrace dump %s | grep blob | sort -k 2 > %s"
						, fnames[i+j], outfile[j]);
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

/*folder* load_context( char* fnames, int fnum)
{
	folder* fder = new_folder();

	fder->num = fnum;
	for( int i = 0; i < fnum; i++)
		fder->file[i] = new_tfile( fnames[ i]);

	FILE** fs = ( FILE**) malloc( sizeof( FILE*));
	for( int i = 0; i < fder->num; i++)
		fs[i] = fopen( fnames[i], "r");

	for( int i = 0; i < fder->num; i++)
	{
		parse_tfile( fs[i], );


}

parse_tfile( FILE* f, tfile* file)
{
	instr* ilast = file->last;
	char buf[300], *p, instrname[30];
	
	lint call;
	
	do{
		memset( instrname, '\0', sizeof( instrname));
		fgets( buf, 300, f);
		if( (p = strchr( buf, '\n')) != NULL)///< it work with extendition
			p = '\0';

		sscanf( buf, "%lld %[^(]", call, instrname);

		if( ilast == NULL){
			file->head = new_instr( instrname);
			file->last = file->head;
			ilast = file->last;
		}
		else{
			if( strcmp( ilast->name, instrname) == 0){
				//same
			else if( instrcmp( instr, file->head));
				
		

	}while( !feof)
	
Bool instrcmp( char* str, instr)
{
*/
