#include "md5.h"

char* md5sum( char* file)
{
	MD5_CTX ctx;
	MD5_Init( &ctx);

	assert( fexist( file) && "file is not  exist");

	int bytes;
	char tmp[3];
	char* out = ( char*) malloc( sizeof( char) * 33);
	out[33] = '\0';
	memset( tmp, '\0', sizeof( tmp));
	unsigned char buf[1024], md5[16];

	FILE* fp = fopen( file, "rb");
	syserr( !fp, "fopen");

	while( ( bytes = fread( buf, 1, 1024, fp)) != 0){
		MD5_Update( &ctx, buf, bytes);
		dprintf("MD5 bytes = %d\n", bytes);
	}

	MD5_Final( md5, &ctx);

	for( int i = 0; i < 16; i++){
		sprintf( tmp, "%02x", md5[i]);
		strcat( out, tmp);
	}
	fclose( fp);

	return out;
}

char* md5sum1( unsigned char *data, size_t length)
{
	dprintf("length %d, final address = %p\n", (int) length, data + length - 1);
	MD5_CTX ctx;
	MD5_Init( &ctx);

	char tmp[3];
	char* out = ( char*) malloc( sizeof( char) * 33);
	memset( out, '\0', sizeof(char) * 33);
	memset( tmp, '\0', sizeof( tmp));
	unsigned char md5[16];

	int i;
	for( i = 0; i < length; i += 1024){
		MD5_Update( &ctx, data + i, 1024);
		dprintf("data = %p, data + i = %p, i = %d\n", data, data + i, i);
	}
	
	if( i != length){
		int k = 1024 - (length - i + 1024);
		dprintf("data = %p, data + k = %p, i = %d, k = %d\n", data, data + i, i, k);
		MD5_Update( &ctx, data + i -1024, k);
		dprintf("data = %p, data + i - 1024 = %p, i = %d\n", data, data + i, i);
	}

	MD5_Final( md5, &ctx);

	for( int i = 0; i < 16; i++){
		sprintf( tmp, "%02x", md5[i]);
		strcat( out, tmp);
	}

	return out;
}

