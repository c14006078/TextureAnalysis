#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h> ///< define "pid_t"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "debug.h"
#include "file.h"
#include "ipc.h"

#define PROCESS_NUM 4

typedef unsigned long long lint;///< avoid the 

typedef struct clink *plink;
typedef struct instr *pinstr;
typedef struct tracef *ptracef;

typedef struct clink{
	lint call; ///< calls maybe overflow
	plink next;
}clink;

typedef struct instr{
	char* name;
	unsigned int count;
	plink calls;
	plink last;
	pinstr next;
}instr;

typedef struct tracef{
	char* name;
	pinstr p;
} tracef;

pinstr new_instr( char* instrName);

pinstr append_instr( pinstr hNode, long call);

ptracef new_tracef( int fnum, char** fname);

void main_dump_blob( char** fnames, int fnum, char* dname);

void exec_sh( char* cmd);
