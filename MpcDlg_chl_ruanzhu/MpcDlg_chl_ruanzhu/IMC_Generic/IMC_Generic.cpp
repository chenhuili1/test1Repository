// IMC_Generic.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "IMC_GenericDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMC_GenericApp

BEGIN_MESSAGE_MAP(CIMC_GenericApp, CWinApp)
END_MESSAGE_MAP()


// CIMC_GenericApp ����
CIMC_GenericApp::CIMC_GenericApp()
	: CWinApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CIMC_GenericApp ����
CIMC_GenericApp theApp;

// CIMC_GenericApp ��ʼ��

BOOL CIMC_GenericApp::InitInstance()
{

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
//	_CrtSetBreakAlloc(206);//�����ڴ�й©���
	CIMC_GenericDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

CString CIMC_GenericApp::GetMyMFCDir()
{
	CString path;
	GetModuleFileName(NULL,path.GetBuffer(512),512);//��ȡ��ǰ���������·��������������
	path.ReleaseBuffer();
	int i=path.ReverseFind('\\');
	path=path.Left(i);
	return path;
}