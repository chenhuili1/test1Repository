#pragma once


// CLogoInfo �Ի���

class CLogoInfo : public CDialog
{
	DECLARE_DYNAMIC(CLogoInfo)

public:
	CLogoInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogoInfo();

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
// �Ի�������
	enum { IDD = IDD_DLG_LOGO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
