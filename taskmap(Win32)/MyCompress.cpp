// MyCompress.cpp: implementation of the MyCompress class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "MyCompress.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyCompress::MyCompress()
{

}

MyCompress::~MyCompress()
{

}

int MyCompress::zlib_compress2(void *dest, unsigned long *destLen, 
							   const void *source, unsigned long sourceLen, 
							   int level)
{
	if (sourceLen == 0) {
        return -1;
    }
    {
        int ret = compress2(
            (Bytef*)dest + sizeof(unsigned long),
            (uLongf*)destLen,
            (Bytef*)source,
            (uLong)sourceLen,
            level
            );
        *(unsigned long *)dest = sourceLen;
        *destLen += sizeof(unsigned long);
        return ret;
    }
}

unsigned long MyCompress::zlib_uncompress_size(const void *source, 
											   unsigned long sourceLen)
{
	if (sourceLen > sizeof(unsigned long)) {
        return ((unsigned long *)source)[0];
    } else {
        return 0;
    }
}

int MyCompress::zlib_uncompress(void *dest, unsigned long *destLen, const void *source, 
								unsigned long sourceLen)
{
	if (*(uLongf*)destLen > 0) {
        int ret = uncompress(
            (Bytef*)dest,
            (uLongf*)destLen,
            (Bytef*)source + sizeof(unsigned long),
            (uLong)sourceLen - sizeof(unsigned long)
            );
        return ret;
    } else {
        return -1;
    }
}
