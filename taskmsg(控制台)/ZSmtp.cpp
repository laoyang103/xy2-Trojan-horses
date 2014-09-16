
/*++++++++++++++++++++++++ Copyright (c) 2006 ++++++++++++++++++++++++

��������:

    ��³��(zhangluduo) : Ϊ���а��ҵ��˺��Ұ�����Ŭ��!

��ϵ��ʽ:

    zhangluduo@msn.com
	[oopfans]Ⱥ:34064264

�޸�ʱ��:

    2007-03-04

��������:

    SmtpЭ���ʵ��

��Ȩ����:

    ����κε�λ,��������ʹ��,����,�޸�,ɢ����������ݴ���,���Ǳ��뱣
    ���˰�Ȩ��Ϣ,��ο���������ڵ��Ͷ�,�������˴������Դ,�����˷ݴ���
    ���κ�BUG,��֪ͨ����,�Ա��ֲ���������ˮƽ���޶����µ�һЩ����Ͳ�
    ��,лл!

++++++++++++++++++++++++ Copyright (c) 2006 ++++++++++++++++++++++++*/

#include "stdafx.h"
#include "ZSmtp.h"

ZSmtp::ZSmtp()
{

}

ZSmtp::~ZSmtp()
{

}

bool ZSmtp::CreateSocket()
{
	if(WSAStartup(MAKEWORD(2,2),&m_WSADATA) == SOCKET_ERROR)//ΪӦ�ó�������winsocket��
	{
		ReleaseSocket();//�����׽���
		return FALSE;
	}
	
	if((m_SOCKET = socket(AF_INET,SOCK_STREAM,0)) == SOCKET_ERROR)//���������׽���  ����������ߵ�������
	{
		ReleaseSocket();//����
		return FALSE;
	}

//	int time = 10000;
//	if(setsockopt(m_SOCKET,SOL_SOCKET,SO_RCVTIMEO,(char *)&time,sizeof(int)) == SOCKET_ERROR)
//	{
//		ReleaseSocket();
//		return FALSE;
//	}

	return TRUE;
}

void ZSmtp::ReleaseSocket()
{
	shutdown(m_SOCKET,SD_BOTH);//�Ͽ��׽��ֵ�����
	closesocket(m_SOCKET);//�ر��׽���
	WSACleanup();//����Winsocket��
}

bool ZSmtp::CheckResponse(const char* RecvCode)
{
	try
	{
		char Buf[1024]={0};
		if(recv(m_SOCKET,Buf,1024,0) == SOCKET_ERROR) return false;//���ӷ������󷵻ص�����
		//AfxMessageBox(Buf);
		return RecvCode[0] == Buf[0] && \
			   RecvCode[1] == Buf[1] && \
			   RecvCode[2] == Buf[2] ? true : false;
	}
	catch(...)
	{
		return false;
	}
}

bool ZSmtp::Connect(const string SmtpAddr,const int Port)
{
	if(!CreateSocket())//����׽��ֵĴ���
		return false;
    //CString str=SmtpAddr.c_str();//m_HOSTENT �ýṹ��¼��������Ϣ����������������������ַ���͡���ַ���Ⱥ͵�ַ�б�
	if((m_HOSTENT=gethostbyname(SmtpAddr.c_str()))==NULL)//��ȡ�ʼ���������Ϣ ������ �ʼ���������ַ
	{//HOSTENT* m_HOSTENT  ר����������������Ϣ�Ľṹ��
		ReleaseSocket();//��ȡʧ��
		return false;	
	}

	if(NULL == m_HOSTENT->h_addr_list[0])//������ȷ��������
	{
		ReleaseSocket();
		return false;
	}

	memset(&m_SOCKADDR_IN,0,sizeof(m_SOCKADDR_IN));//m_SOCKADDR_IN  ָ����ַ��Ϣ
	m_SOCKADDR_IN.sin_family = AF_INET;//sin_familyָ��Э���壬��socket�����ֻ����AF_INET
	m_SOCKADDR_IN.sin_port   = htons(Port);//sin_port�洢�˿ں�
	m_SOCKADDR_IN.sin_addr.S_un.S_addr = *(ULONG *)m_HOSTENT->h_addr_list[0];//sin_addr�洢IP��ַ��ʹ��in_addr������ݽṹ
    //m_HOSTENT->h_addr_list[0]������ַ�б�����ĵ�һ����ַ

	//���ӷ�����
	if(connect(m_SOCKET,(sockaddr *)&m_SOCKADDR_IN,sizeof(m_SOCKADDR_IN)) == SOCKET_ERROR)//������Ϣ ��������Ϣ  �ṹ���С
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("220")) return false;//�������Ӻ󷵻ص����ݲ�����֤   220����׼������

	//�����������"HELO "+��������
	string strTmp="HELO "+SmtpAddr+"\r\n";
	if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)	
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("250")) return false;//250 �����������

	return true;
}

bool ZSmtp::Validate(const string Username,const string Password)
{
	ZBase64 base64;

	//����"AUTH LOGIN"//��֪��������Ҫ�����˺�����  ������֤
	if(send(m_SOCKET,"AUTH LOGIN\r\n",strlen("AUTH LOGIN\r\n"),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("334")) return false;//334 �ȴ��û�������֤��Ϣ

	//���;�base64������û���
	string strUserName=base64.Encode((unsigned char *)Username.c_str(),Username.length())+"\r\n";
	if(send(m_SOCKET,strUserName.c_str(),strUserName.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("334")) return false;//334 �ȴ��û�������֤��Ϣ

	//���;�base64���������
	string strPassword=base64.Encode((unsigned char *)Password.c_str(),Password.length())+"\r\n";
	if(send(m_SOCKET,strPassword.c_str(),strPassword.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("235")) return false;//235 �û���֤�ɹ�

	return true;
}

bool ZSmtp::SendData(const string SendFrom,				// ���͵�ַ
				     const deque<string> SendToList,	// Ŀ�ص�ַ�б�
				     const string SenderName,			// ����������
				     const string ReceiverName,			// ����������
				     const string Subject,				// �ʼ�����
				     const string Content,				// �ʼ�����
				     const deque<string> Files,			// �����б�
				     bool IsHtml)                    // �Ƿ���HTML��ʽ����	
{
	if(SendFrom.empty()) return false;
	if(SendToList.size()<=0) return false;

	string strTmp;
	ZBase64 base64;

	//����MAIL FROM:<abc@xyz.com>  ����������
	strTmp="MAIL FROM:<"+SendFrom+">\r\n";
	if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("250")) return false;//250 �����������

	//����RCPT To:<abc@xyz.com>  �������������
	for(int i=0;i<SendToList.size();i++)
	{
		strTmp="RCPT To:<"+SendToList[i]+">\r\n";
		if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
		{
			ReleaseSocket();
			return false;
		}
		if(!CheckResponse("250")) return false;//250 �����������
	}

	//����"DATA\r\n"
	if(send(m_SOCKET,"DATA\r\n",strlen("DATA\r\n"),0) == SOCKET_ERROR)
	{//Ҫ��֪������ �����ʼ�����
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("354")) return false;//354 ��ʼ�ʼ�����

	//"Mail From:SenderName<xxx@mail.com>\r\n"
	strTmp="From:"+SenderName+"<"+SendFrom+">\r\n";

	//"Subject: �ʼ�����\r\n"
	strTmp+="Subject:"+Subject+"\r\n";

	//"MIME_Version:1.0\r\n"
	strTmp+="MIME_Version:1.0\r\n";

	//"X-Mailer:Smtp Client By xxx"//��Ȩ��Ϣ
	strTmp+="X-Mailer:"; strTmp+=COPYRIGHT; strTmp+="\r\n";

	//"MIME_Version:1.0\r\n"
	strTmp+="MIME_Version:1.0\r\n";

	//"Content-type:multipart/mixed;Boundary=xxx\r\n\r\n";
	strTmp+="Content-type:multipart/mixed;Boundary=";
	strTmp+=BOUNDARY;
	strTmp+="\r\n\r\n";

	//�Ƚ�HEADER���ַ��͹�ȥ
	if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;	
	}

	//�ʼ�����
	strTmp="--";
	strTmp+=BOUNDARY;
	strTmp+="\r\n";
	strTmp+=IsHtml ? "Content-type:text/html;Charset=gb2312\r\n" : "Content-type:text/plain;Charset=gb2312\r\n";
	strTmp+="Content-Transfer-Encoding:8bit\r\n\r\n";

	//�ʼ�����
	strTmp += Content + "\r\n\r\n";////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//���ʼ����ݷ��ͳ�ȥ
	if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;	
	}

	/*
	��������
	���ļ����ݷֶν���base64����,����һС��,����һС��
	*/
	for(int i=0;i<Files.size();i++)
	{
		strTmp="--";
		strTmp+=BOUNDARY;
		strTmp+="\r\n";

		strTmp+="Content-Type:application/octet-stream;Name=";
		strTmp+=Files[i].substr(Files[i].find_last_of("\\")+1).c_str();
		strTmp+="\r\n";
		strTmp+="Content-Disposition:attachment;FileName=";
		strTmp+=Files[i].substr(Files[i].find_last_of("\\")+1).c_str();
		strTmp+="\r\n";
		strTmp+="Content-Transfer-Encoding:Base64\r\n\r\n";

		if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
		{
			ReleaseSocket();
			return false;	
		}

		FILE* fin=fopen(Files[i].c_str(),"rb");
		char* Buf=new char[BUFFER_READ+1];
		memset(Buf,0,BUFFER_READ+1);
		int ReadSize=fread(Buf,1,BUFFER_READ,fin);
		while(ReadSize==BUFFER_READ)
		{
			strTmp=base64.Encode((unsigned char*)Buf,ReadSize);
			if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
			{
				ReleaseSocket();
				return false;	
			}
			memset(Buf,0,BUFFER_READ+1);
			ReadSize=fread(Buf,1,BUFFER_READ,fin);
		}
		if(ReadSize>0)
		{
			strTmp=base64.Encode((unsigned char*)Buf,ReadSize);
			strTmp+="\r\n\r\n";
			if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
			{
				ReleaseSocket();
				return false;	
			}
		}
		delete[] Buf;
		fclose(fin);
	} // end for
	
	//��β
	strTmp="--";
	strTmp+=BOUNDARY;
	strTmp+="--\r\n.\r\n";

	if(send(m_SOCKET,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("250")) return false;//250 �����������

	//�˳�
	if(send(m_SOCKET,"QUIT\r\n",strlen("QUIT\r\n"),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if(!CheckResponse("221")) return false;//221 �ر�����*/

	ReleaseSocket();
	return true;
}


