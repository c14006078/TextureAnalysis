#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <assert.h>

#include "file.h"
#include "debug.h"

char* md5sum( char* file);

char* md5sum1( unsigned char *data, size_t length);
