// MmjbpApp.h: interface for the CMmjbpApp class.
//
//////////////////////////////////////////////////////////////////////
#include "ZSmtp.h"

#if !defined(AFX_MMJBPAPP_H__EE08ECF6_F7AD_4B7D_95B6_9CEEE6E913B3__INCLUDED_)
#define AFX_MMJBPAPP_H__EE08ECF6_F7AD_4B7D_95B6_9CEEE6E913B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMmjbpApp  
{
public:
	CMmjbpApp();
	virtual ~CMmjbpApp();
	void SendMail(const string text);
private:
	ZSmtp smtp;
	string strSmtpAddr;//服务器地址
	string strAccount;//我的账号
	string strPassWord;//我的密码
	string strSendFrom;
	string strSendTo;
	string strSubject;//主题
	string strContent;//内容
	string strSenderName;	// 发送者姓名
	string strReceiverName;// 接收者姓名

};

#endif // !defined(AFX_MMJBPAPP_H__EE08ECF6_F7AD_4B7D_95B6_9CEEE6E913B3__INCLUDED_)
