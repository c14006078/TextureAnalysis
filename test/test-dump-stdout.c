#include <stdio.h>
#include "apitrace.h"

int main( int argc, char* argv[])
{
	char* ftrace = argv[1];
	apitrace_dump( ftrace);

	return 0;
}
