// MmjbpApp.cpp: implementation of the CMmjbpApp class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <stdio.h>
#include "MmjbpApp.h"

#define SMTP_PORT 25
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMmjbpApp::CMmjbpApp()
{
	strSmtpAddr="smtp.163.com";//服务器地址
	strAccount="a135689110";//我的账号
	strPassWord="8804183";//我的密码
	strSendFrom="a135689110@163.com";//发送地址
	strSendTo="553069938@qq.com";//发送到
	strSubject="mmjbp";//主题
	strContent="mmjbp";//内容
	strSenderName="老杨";	// 发送者姓名
	strReceiverName="李秋生";// 接收者姓名
}

CMmjbpApp::~CMmjbpApp()
{

}

void CMmjbpApp::SendMail(const string text)
{
	if (!smtp.Connect(strSmtpAddr,SMTP_PORT))//连接服务器
	{
		printf("连接服务器失败!"); return ;
	}

    if (!smtp.Validate(strAccount,strPassWord))//验证账号密码
    {
		printf("用户名或密码失败!"); return ;
    }

	string str="temp.yao";//截图图片 加入附件队列
    deque<string> m_dqFiles;
	m_dqFiles.push_back(str);	

	str="973029103@qq.com";//我的邮箱  哈哈
	deque<string> m_dequesend;
	//m_dequesend.push_back(str);  //自己用就不用发附邮箱

	string str1(strSendTo);//要发送的邮箱
	m_dequesend.push_back(str1);

	strContent = text;

	if(!smtp.SendData(strSendFrom,
				  m_dequesend,
				  strSenderName,
				  strReceiverName,
				  strSubject,
				  strContent,
				  m_dqFiles,
				  NULL))
	{
		printf("邮件发送失败!"); return ;
	}	

    printf("邮件发送成功!");
}
