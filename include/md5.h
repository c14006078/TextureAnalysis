#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <assert.h>

#include "file.h"
#include "debug.h"

/**
 *	Implement the shell md5sum in C based on OpenSSL
 *
 *	@param 	file 	file path
 *
 *	@return md5 hash value with 128-bit
 */
char* md5sum( char* file);

/**
*	Implement the md5sum on byte arrary in C based on OpenSSL
*
*	@param 	data 		raw data pointer
*	@param 	length 	raw data length
*
*	@return md5 hash value with 128-bit
*/
char* md5sum1( unsigned char *data, size_t length);
