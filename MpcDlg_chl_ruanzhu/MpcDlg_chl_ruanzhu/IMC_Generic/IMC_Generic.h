// IMC_Generic.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

//#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
//#endif

// CIMC_GenericApp:
// �йش����ʵ�֣������ IMC_Generic.cpp
//

class CIMC_GenericApp : public CWinApp
{
public:
	CIMC_GenericApp();
	
	CString GetMyMFCDir();
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIMC_GenericApp theApp;
