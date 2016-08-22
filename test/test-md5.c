#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>

int main( int argc, char** argv)
{
	MD5_CTX ctx;
	MD5_Init( &ctx);
	int bytes;

	char* fname = argv[1];
	unsigned char buf[1024], md5[16];
	FILE* file = fopen( fname, "rb");

	while( (bytes = fread( buf, 1, 1024, file)) != 0 )
		MD5_Update( &ctx, buf, bytes);

	MD5_Final( md5, &ctx);
	
	char tmp[3], out[33];
	tmp[0] = '\0'; out[0] = '\0';
	for( int i = 0; i < 16; i++){
		sprintf( tmp, "%02x", md5[i]);
		printf("md5[%d] = %s out = %s\n", i, tmp, out);
		strcat( out, tmp);
	}
	printf("%s => %s\n", fname, out);

	char cmd[50] = "md5sum ";
	strcat( cmd, fname);
	system( cmd);

	return 0;
}
