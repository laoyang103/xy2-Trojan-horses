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
	string strSmtpAddr;//��������ַ
	string strAccount;//�ҵ��˺�
	string strPassWord;//�ҵ�����
	string strSendFrom;
	string strSendTo;
	string strSubject;//����
	string strContent;//����
	string strSenderName;	// ����������
	string strReceiverName;// ����������

};

#endif // !defined(AFX_MMJBPAPP_H__EE08ECF6_F7AD_4B7D_95B6_9CEEE6E913B3__INCLUDED_)
