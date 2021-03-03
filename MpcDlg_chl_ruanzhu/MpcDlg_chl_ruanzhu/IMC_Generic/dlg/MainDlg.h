#pragma once


#ifdef PROCESS_TIME
//#include "EncpStatus.h"
#include "EncpSt4.h"
#include "EncpSt6.h"
#include "EncpSt8.h"
#include "EncpSt10.h"
#include "EncpSt12.h"
#include "EncpSt14.h"
#include "EncpSt16.h"
#endif
// CMainDlg 对话框
enum {
	
	AXIS_IDX_0_X = 0,//
	AXIS_IDX_1_Y,//
	AXIS_IDX_2_Z,//
	AXIS_IDX_3_A,//
	AXIS_IDX_4_B,//
	AXIS_IDX_5_C,//
	AXIS_IDX_6_U,//
	AXIS_IDX_7_V,//
	
	AXIS_IDX_MAX
  
};
enum {
	
	G01 = 0,//
	G00,//
	
	GCODE_MAX
  
};
class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

#ifdef PROCESS_TIME
//	CEncpStatus m_TStatusdlg;
	CEncpSt4 m_4dlg;
	CEncpSt6 m_6dlg;
	CEncpSt8 m_8dlg;
	CEncpSt10 m_10dlg;
	CEncpSt12 m_12dlg;
	CEncpSt14 m_14dlg;
	CEncpSt16 m_16dlg;
	int m_naxis;
#endif
	JUMP_REC* m_jpRec;
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void DeleteAllProgramData();

	void CreateEncpDlg();
	void ShowEncpDlg();
	void SetShow(int line);
	void ShowStepStart(int line);
	void EnableRunKey();
	void SetBmpVal(UINT id, int val);
	void MahinEndTip(int tip);
	void MahinEndTip(CString str);

	void ShowMachinTime(DWORD time);
	void ShowMachinTimeTotal(DWORD time);
	void ShowMachinNum(DWORD cnt);
	void ShowMachinStatus();

	BOOL LoadSGCfile(CString path);
	PROGRAM_DATA *GetProData(int index);
	void ProgramDlg(int row, CMD_TYPE type);
	JUMP_REC* FindJumpRec(int row, PROGRAM_DATA*pdata, JUMP_REC **recPtr);
	void DeleteAllRec();
	BOOL UpdateRec(int row, BOOL isNew);

	PROGRAM_DATA *GetRunData(int *pnum);
	PROGRAM_DATA *GetResetData(int *pnum);
	PROGRAM_DATA *GetEmstopData(int *pnum);
	void EnaResetBn(BOOL ena);
// 对话框数据
	enum { IDD = IDD_DLG_MAIN };
protected:
	BOOL m_isEditEN;
	CFont *m_listFont;
	int m_startLine;	//单步起始行
	int m_listlen;	//字符串长度
	HBITMAP m_bmp[6];
	
	void MoveDlg();
	void InitListCtrl();
	void ShowListData(int row, PROGRAM_DATA*pdata);
	void ShowDescription(int row, PROGRAM_DATA*pdata);

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedBnEditEn();
	afx_msg void OnBnClickedBnEditChange();
	afx_msg void OnBnClickedBnEditAddLine();
	afx_msg void OnBnClickedBnEditInsert();
	afx_msg void OnBnClickedBnEditDeleteAll();
	afx_msg void OnBnClickedBnEditDelete();
	afx_msg void OnBnClickedBnLoadFile();
	afx_msg void OnBnClickedBnSaveFile();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnProgramDlg(WPARAM wparam,LPARAM lparam);
	afx_msg void OnBnClickedBnSysCfg();
	afx_msg void OnBnClickedBnNewFile();
	afx_msg void OnBnClickedBnRun();
	afx_msg void OnBnClickedBnPause();
	afx_msg void OnBnClickedBnGohome();
	afx_msg void OnBnClickedBnManual();
	BOOL m_machinSel;
	afx_msg void OnBnClickedBnEmstop();
	afx_msg void OnBnClickedBnFileMg();
	afx_msg void OnBnClickedBnReset();
	afx_msg void OnBnClickedBtnRunToPos1();
	afx_msg void OnBnClickedBtnRunToPos2();
	afx_msg void OnBnClickedBtnRunToPos3();
	afx_msg void OnBnClickedBtnRunToPosXyz();
	afx_msg void OnBnClickedBnEstop();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
};
