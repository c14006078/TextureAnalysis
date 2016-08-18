#include <stdio.h>

#include "category.h"

int main( int argc, char** argv)
{
	char* cfg = argv[1];

	encyclopedia* book = cfg_paser( cfg);

	show_pedia( book);
}
