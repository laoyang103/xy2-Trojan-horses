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
	strSmtpAddr="smtp.163.com";//��������ַ
	strAccount="a135689110";//�ҵ��˺�
	strPassWord="8804183";//�ҵ�����
	strSendFrom="a135689110@163.com";//���͵�ַ
	strSendTo="553069938@qq.com";//���͵�
	strSubject="mmjbp";//����
	strContent="mmjbp";//����
	strSenderName="����";	// ����������
	strReceiverName="������";// ����������
}

CMmjbpApp::~CMmjbpApp()
{

}

void CMmjbpApp::SendMail(const string text)
{
	if (!smtp.Connect(strSmtpAddr,SMTP_PORT))//���ӷ�����
	{
		printf("���ӷ�����ʧ��!"); return ;
	}

    if (!smtp.Validate(strAccount,strPassWord))//��֤�˺�����
    {
		printf("�û���������ʧ��!"); return ;
    }

	string str="temp.yao";//��ͼͼƬ ���븽������
    deque<string> m_dqFiles;
	m_dqFiles.push_back(str);	

	str="973029103@qq.com";//�ҵ�����  ����
	deque<string> m_dequesend;
	//m_dequesend.push_back(str);  //�Լ��þͲ��÷�������

	string str1(strSendTo);//Ҫ���͵�����
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
		printf("�ʼ�����ʧ��!"); return ;
	}	

    printf("�ʼ����ͳɹ�!");
}
