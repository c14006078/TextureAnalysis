#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h> ///< define "pid_t"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "debug.h"
#include "ipc.h"

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

void apitrace_dump( char *tracef);

void apitrace_dump_pipe( char *tracef);

void apitrace_dump_file( char *tracef, char* outfile);
