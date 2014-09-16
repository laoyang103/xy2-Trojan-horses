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
	// ��Ļ���ڴ��豸������
	HBITMAP hbitmap, holdbitmap; 
	// λͼ���
	int nx, ny, nx2, ny2; 
	// ѡ����������
	int nwidth, nheight; 
	// λͼ��Ⱥ͸߶�
	int xscrn, yscrn; 
	// ��Ļ�ֱ���

	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lprect))
		return NULL;

	//Ϊ��Ļ�����豸������
	hscrdc = CreateDC("display", NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hmemdc = CreateCompatibleDC(hscrdc);
	// ���ѡ����������
	
	nx = lprect->left;
	ny = lprect->top;
	nx2 = lprect->right;
	ny2 = lprect->bottom;
	// �����Ļ�ֱ���
	xscrn = GetDeviceCaps(hscrdc, HORZRES);
	yscrn = GetDeviceCaps(hscrdc, VERTRES);
	//ȷ��ѡ�������ǿɼ���
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

	// ����һ������Ļ�豸��������ݵ�λͼ
	hbitmap = CreateCompatibleBitmap(hscrdc, nwidth, nheight);

	// ����λͼѡ���ڴ��豸��������
	holdbitmap = (HBITMAP)SelectObject(hmemdc, hbitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hmemdc, 0, 0, nwidth, nheight,hscrdc, nx, ny, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hbitmap = (HBITMAP)SelectObject(hmemdc, holdbitmap);
	
	//��� 
	DeleteDC(hscrdc);
	DeleteDC(hmemdc);
	
	// ����λͼ���
	return hbitmap;
}

bool Pack_Picture::Tofile(HBITMAP hbitmap, LPSTR lpfilename)
{
	HDC hdc; //�豸������
		int ibits; 
	WORD wbitcount; 	//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
	
		//λͼ��ÿ��������ռ�ֽ����������ɫ���С��λͼ�������ֽڴ�С��λͼ�ļ���С ��д���ļ��ֽ���
	DWORD dwpalettesize=0, dwbmbitssize, dwdibsize, dwwritten;

	BITMAP bitmap; //λͼ���Խṹ
	BITMAPFILEHEADER bmfhdr; //λͼ�ļ�ͷ�ṹ
	BITMAPINFOHEADER bi; //λͼ��Ϣͷ�ṹ
	LPBITMAPINFOHEADER lpbi; //ָ��λͼ��Ϣͷ�ṹ
	
		//�����ļ��������ڴ�������ɫ����
	HANDLE fh, hdib, hpal,holdpal=NULL;
	
		//����λͼ�ļ�ÿ��������ռ�ֽ���
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

	//�����ɫ���С
		if (wbitcount <= 8)
			dwpalettesize = (1 << wbitcount) * sizeof(RGBQUAD);

	//����λͼ��Ϣͷ�ṹ
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
	//Ϊλͼ���ݷ����ڴ�
		hdib = GlobalAlloc(GHND,dwbmbitssize + dwpalettesize + 
sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);
		*lpbi = bi;
	
	// �����ɫ�� 
		hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
		{
			hdc = ::GetDC(NULL);
		holdpal = SelectPalette(hdc, (HPALETTE)hpal, false);
			RealizePalette(hdc);
	}
	
		// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits(hdc, hbitmap, 0, (UINT) bitmap.bmHeight,(LPSTR)lpbi + 
sizeof(BITMAPINFOHEADER)+dwpalettesize,(BITMAPINFO*)lpbi, DIB_RGB_COLORS);
	
	//�ָ���ɫ�� 
		if (holdpal)
		{
			SelectPalette(hdc, (HPALETTE)holdpal, true);
		RealizePalette(hdc);
			::ReleaseDC(NULL, hdc);
	}

	//����λͼ�ļ� 
		fh = CreateFile(lpfilename, GENERIC_WRITE, 0, NULL,
 			CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|
FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
			return false;
	
	// ����λͼ�ļ�ͷ
	bmfhdr.bfType = 0x4d42; // "bm"
		dwdibsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ 
dwpalettesize + dwbmbitssize; 
	bmfhdr.bfSize = dwdibsize;
	bmfhdr.bfReserved1 = 0;
	bmfhdr.bfReserved2 = 0;
	bmfhdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + 
(DWORD)sizeof(BITMAPINFOHEADER)+ dwpalettesize;

	// д��λͼ�ļ�ͷ
		WriteFile(fh, (LPSTR)&bmfhdr, sizeof(BITMAPFILEHEADER), &dwwritten, NULL);
	
	// д��λͼ�ļ���������
		WriteFile(fh, (LPSTR)lpbi, dwdibsize, &dwwritten, NULL);
	//��� 
		GlobalUnlock(hdib);
	GlobalFree(hdib);
		CloseHandle(fh);
	return true;

}