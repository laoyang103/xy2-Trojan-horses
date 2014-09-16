// MyCompress.h: interface for the MyCompress class.
//
//////////////////////////////////////////////////////////////////////
#include "../zlib/zlib.h"
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "../zlib/zlibd")

#if !defined(AFX_MYCOMPRESS_H__BFE07DDC_07FA_41B5_AD5A_E69EFE96C90F__INCLUDED_)
#define AFX_MYCOMPRESS_H__BFE07DDC_07FA_41B5_AD5A_E69EFE96C90F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MyCompress  
{
public:
	MyCompress();
	virtual ~MyCompress();

	int zlib_compress2(void *dest, unsigned long *destLen, 
		const void *source, unsigned long sourceLen, int level);//Ñ¹ËõÍ¼Æ¬º¯Êý

	unsigned long zlib_uncompress_size(const void *source, unsigned long sourceLen);//·µ»ØÍ¼Æ¬´óÐ¡

	int zlib_uncompress(void *dest, unsigned long *destLen, const void *source, unsigned long sourceLen);

};

#endif // !defined(AFX_MYCOMPRESS_H__BFE07DDC_07FA_41B5_AD5A_E69EFE96C90F__INCLUDED_)
