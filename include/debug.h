#ifdef DEBUG 
	//printf("\n****************\n	DEBUG	\n****************\n");
	#define dprintf( ...) printf( "DEBUG: " __VA_ARGS__ )
	#define eprintf( ...) fprintf( stderr, "ERROR: "); fprintf( stderr, __VA_ARGS__ ) ///< "fprintf( stderr, "ERROR: " __VA_ARGS__)" will fail
#else
	#define dprintf( ...) 
	#define eprintf( ...) fprintf( stderr, "ERROR: "); fprintf( stderr, __VA_ARGS__ )
#endif
