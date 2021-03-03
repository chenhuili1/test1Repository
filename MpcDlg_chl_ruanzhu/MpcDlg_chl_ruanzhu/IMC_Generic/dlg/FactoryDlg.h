#pragma once

#include "FactAxis.h"
#include "FactIOmap.h"
#include "FactInfo.h"
#include "afxwin.h"
#include "FactPolar.h"
#include "FactWarn.h"

// CFactoryDlg 对话框
enum {
	FACT_NULL,
	FACT_AXIS,
	FACT_IOMAP,
	FACT_INFO,
	FAC_POLAR,
	FAC_WARN,
};

class CFactoryDlg : public CDialog
{
	DECLARE_DYNAMIC(CFactoryDlg)

public:
	CFactoryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFactoryDlg();

	CFactAxis m_axisdlg;
	CFactIOmap m_IOmapdlg;
	CFactInfo m_infodlg;
	CFactPolar m_polardlg;
	CFactWarn m_warndlg;

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void ShowDlg(int dlg);
// 对话框数据
	enum { IDD = IDD_DLG_FACT };

protected:
	int m_dlg;
	void MoveDlg();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBnIomap();
	afx_msg void OnBnClickedBnChpwFact();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CMyEdit m_edit[2];
	afx_msg void OnBnClickedBnFactInfo();
	afx_msg void OnBnClickedBnAxisSet();
	afx_msg void OnBnClickedBnInPolar();
	afx_msg void OnBnClickedBnFactWarn();
};
