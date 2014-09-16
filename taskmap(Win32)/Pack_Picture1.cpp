// Pack_Picture1.cpp: implementation of the Pack_Picture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Pack_Picture1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pack_Picture::Pack_Picture()
{

}

Pack_Picture::~Pack_Picture()
{

}

void Pack_Picture::OnPackMap(int left, int top, int bottom, int right)
{
	LPRECT temprect;
	HBITMAP tempmap;

	temprect = new RECT();
	temprect->bottom = bottom;
	temprect->left = left;
	temprect->right = right;
	temprect->top = top;

	tempmap = Copybitmap(temprect);

	Tofile(tempmap,"temp.bmp");
}

HBITMAP Pack_Picture::Copybitmap(LPRECT lprect)
{
	HDC hscrdc, hmemdc; 
	// 屏幕和内存设备描述表
	HBITMAP hbitmap, holdbitmap; 
	// 位图句柄
	int nx, ny, nx2, ny2; 
	// 选定区域坐标
	int nwidth, nheight; 
	// 位图宽度和高度
	int xscrn, yscrn; 
	// 屏幕分辨率

	// 确保选定区域不为空矩形
	if (IsRectEmpty(lprect))
		return NULL;

	//为屏幕创建设备描述表
	hscrdc = CreateDC("display", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hmemdc = CreateCompatibleDC(hscrdc);
	// 获得选定区域坐标
	
	nx = lprect->left;
	ny = lprect->top;
	nx2 = lprect->right;
	ny2 = lprect->bottom;
	// 获得屏幕分辨率
	xscrn = GetDeviceCaps(hscrdc, HORZRES);
	yscrn = GetDeviceCaps(hscrdc, VERTRES);
	//确保选定区域是可见的
	if (nx < 0)
		nx = 0;
	if (ny < 0)
		ny = 0;
	if (nx2 > xscrn)
		nx2 = xscrn;
	if (ny2 > yscrn)
		ny2 = yscrn;

	if(1000 == nx)
	{
		nx = 0;
		nwidth = xscrn;
		nheight = yscrn;
	}

	// 创建一个与屏幕设备描述表兼容的位图
	hbitmap = CreateCompatibleBitmap(hscrdc, nwidth, nheight);

	// 把新位图选到内存设备描述表中
	holdbitmap = (HBITMAP)SelectObject(hmemdc, hbitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hmemdc, 0, 0, nwidth, nheight,hscrdc, nx, ny, SRCCOPY);
	//得到屏幕位图的句柄
	hbitmap = (HBITMAP)SelectObject(hmemdc, holdbitmap);
	
	//清除 
	DeleteDC(hscrdc);
	DeleteDC(hmemdc);
	
	// 返回位图句柄
	return hbitmap;
}

bool Pack_Picture::Tofile(HBITMAP hbitmap, LPSTR lpfilename)
{
	HDC hdc; //设备描述表
		int ibits; 
	WORD wbitcount; 	//当前显示分辨率下每个像素所占字节数
	
		//位图中每个像素所占字节数，定义调色板大小，位图中像素字节大小，位图文件大小 ，写入文件字节数
	DWORD dwpalettesize=0, dwbmbitssize, dwdibsize, dwwritten;

	BITMAP bitmap; //位图属性结构
	BITMAPFILEHEADER bmfhdr; //位图文件头结构
	BITMAPINFOHEADER bi; //位图信息头结构
	LPBITMAPINFOHEADER lpbi; //指向位图信息头结构
	
		//定义文件，分配内存句柄，调色板句柄
	HANDLE fh, hdib, hpal,holdpal=NULL;
	
		//计算位图文件每个像素所占字节数
	hdc = CreateDC("display",NULL,NULL,NULL);
	ibits = GetDeviceCaps(hdc, BITSPIXEL) * GetDeviceCaps(hdc, PLANES);
	DeleteDC(hdc);

		if (ibits <= 1)
			wbitcount = 1;
	else if (ibits <= 4)
			wbitcount = 4;
	else if (ibits <= 8)
			wbitcount = 8;
	else if (ibits <= 16)
			wbitcount = 16;
	else if (ibits <= 24)
			wbitcount = 24;
	else 
			wbitcount = 32;

	//计算调色板大小
		if (wbitcount <= 8)
			dwpalettesize = (1 << wbitcount) * sizeof(RGBQUAD);

	//设置位图信息头结构
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wbitcount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

		dwbmbitssize = ((bitmap.bmWidth * wbitcount+31)/32)* 4 * bitmap.bmHeight ;
	//为位图内容分配内存
		hdib = GlobalAlloc(GHND,dwbmbitssize + dwpalettesize + 
sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);
		*lpbi = bi;
	
	// 处理调色板 
		hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
		{
			hdc = ::GetDC(NULL);
		holdpal = SelectPalette(hdc, (HPALETTE)hpal, false);
			RealizePalette(hdc);
	}
	
		// 获取该调色板下新的像素值
	GetDIBits(hdc, hbitmap, 0, (UINT) bitmap.bmHeight,(LPSTR)lpbi + 
sizeof(BITMAPINFOHEADER)+dwpalettesize,(BITMAPINFO*)lpbi, DIB_RGB_COLORS);
	
	//恢复调色板 
		if (holdpal)
		{
			SelectPalette(hdc, (HPALETTE)holdpal, true);
		RealizePalette(hdc);
			::ReleaseDC(NULL, hdc);
	}

	//创建位图文件 
		fh = CreateFile(lpfilename, GENERIC_WRITE, 0, NULL,
 			CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|
FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
			return false;
	
	// 设置位图文件头
	bmfhdr.bfType = 0x4d42; // "bm"
		dwdibsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ 
dwpalettesize + dwbmbitssize; 
	bmfhdr.bfSize = dwdibsize;
	bmfhdr.bfReserved1 = 0;
	bmfhdr.bfReserved2 = 0;
	bmfhdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + 
(DWORD)sizeof(BITMAPINFOHEADER)+ dwpalettesize;

	// 写入位图文件头
		WriteFile(fh, (LPSTR)&bmfhdr, sizeof(BITMAPFILEHEADER), &dwwritten, NULL);
	
	// 写入位图文件其余内容
		WriteFile(fh, (LPSTR)lpbi, dwdibsize, &dwwritten, NULL);
	//清除 
		GlobalUnlock(hdib);
	GlobalFree(hdib);
		CloseHandle(fh);
	return true;

}