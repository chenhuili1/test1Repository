#pragma once
#include "afxcmn.h"


// CMyDebug 对话框

class CMyDebug : public CDialog
{
	DECLARE_DYNAMIC(CMyDebug)

public:
	CMyDebug(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDebug();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	void MyHideWindow();
// 对话框数据
	enum { IDD = IDD_DLG_DEBUG };

protected:
	HBITMAP m_bmp0;
	HBITMAP m_bmp1;
	BOOL m_isHide;
	CImageList* m_pImageList;
	long m_curpos[16];
	long m_encp[16];
	WORD m_err[16];
	WORD m_aio[16];
	WORD m_gin[2];
	WORD m_gout[3];
	WORD m_other[3];
	WORD m_type;	//控制卡类型，分3类，3041E， 40个输出， 48个输出
	DWORD m_errNum;

	WR_MUL_DES m_posDes[16];
	WR_MUL_DES m_encpDes[16];
	WR_MUL_DES m_errDes[16];
	WR_MUL_DES m_aioDes[16];
	WR_MUL_DES m_ginDes[2];
	WR_MUL_DES m_goutDes[3];
	WR_MUL_DES m_OtherDes[3];

	void InitListCtrl();
	void SetNetType(int ver);
	void InitDes();
	void InitVar();
	void UpdateAio();
	void UpdateGin();
	void UpdateGout();

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listctr1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_listctr2;
	afx_msg LRESULT OnStatusTotal(WPARAM wparam,LPARAM lparam);
	afx_msg void OnBnClickedButton1();
};
