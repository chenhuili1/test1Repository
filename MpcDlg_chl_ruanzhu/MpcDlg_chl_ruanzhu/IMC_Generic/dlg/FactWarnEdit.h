#pragma once


// CFactWarnEdit �Ի���

class CFactWarnEdit : public CDialog
{
	DECLARE_DYNAMIC(CFactWarnEdit)

public:
	CFactWarnEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFactWarnEdit();

	void SetWarnInfo(FACT_WARN * info);
	void GetWarnInfo(FACT_WARN * info);
// �Ի�������
	enum { IDD = IDD_DLG_EDIT_WARN };

protected:
	FACT_WARN m_warnInfo;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyEdit m_edit[2];
	afx_msg void OnBnClickedOk();
};
