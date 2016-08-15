#ifdef DEBUG 
	//printf("\n****************\n	DEBUG	\n****************\n");
	#define dprintf( ...) printf( "DEBUG: "__VA_ARGS__)
	#define eprintf( ...) fprintf( stderr, "ERROR: "__VA_ARGS__)
#else
	#define dprintf( ...) 
	#define eprintf( ...) fprintf( stderr, "ERROR: " __VA_ARGS__)
#endif
