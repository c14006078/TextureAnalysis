#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h> ///< define "pid_t"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "constant.h"

#include "debug.h"
#include "file.h"
#include "ipc.h"
#include "context.h"

void main_dump_blob( char** fnames,	int fnum, char* dname, char** dump_file);

void exec_sh( char* cmd);

void statistic( char** file, int fnum);

void main_filter( char** fnames,	int fnum, char* pattern, char** filter_file);
