#include "md5.h"

char* md5sum( char* file)
{
	MD5_CTX ctx;
	MD5_Init( &ctx);

	assert( fexist( file) && "file is not  exist");

	int bytes;
	char tmp[3];
	char* out = ( char*) malloc( sizeof( char) * 33);
	memset( tmp, '\0', sizeof( tmp));
	unsigned char buf[1024], md5[16];

	FILE* fp = fopen( file, "rb");
	syserr( fp, "fopen");

	while( ( bytes = fread( buf, 1, 1024, file)) != 0)
		MD5_Update( &ctx, buf, bytes);

	for( int i = 0; i < 16; i++){
		sprintf( tmp, "%02x", md5[i]);
		strcat( out, tmp);
	}
	fclose( file);

	return out;
}
