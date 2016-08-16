#include <stdio.h>
#include "apitrace.h"

int main( int argc, char* argv[])
{
	char* ftrace = argv[1];
	char* outfile = argv[2];
	apitrace_dump_file( ftrace, outfile);

	return 0;
}
