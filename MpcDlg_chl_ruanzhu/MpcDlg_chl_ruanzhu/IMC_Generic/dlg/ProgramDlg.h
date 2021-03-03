#pragma once

//#include "MyDef.h"
#include "Pg_Goto.h"
#include "Pg_Linkage.h"
#include "Pg_Arc.h"
#include "Pg_Output.h"
#include "Pg_Input.h"
#include "Pg_Gohome.h"
#include "Pg_While.h"
#include "Pg_Tip.h"
#include "Pg_Vel.h"
#include "Pg_Pos.h"
#include "Pg_Wait.h"
#include "Pg_Delay.h"
#include "Pg_GHWhirl.h"

// CProgramDlg 对话框

class CProgramDlg : public CDialog
{
	DECLARE_DYNAMIC(CProgramDlg)

public:
	CProgramDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgramDlg();

	CPg_Goto m_jplpdlg;
	CPg_Linkage m_Linkagedlg;
	CPg_Arc m_Arcdlg;
	CPg_Output m_Outputdlg;
	CPg_Input m_Inputdlg;
	CPg_Gohome m_Gohomedlg;
	CPg_While m_Whiledlg;
	CPg_Tip m_Tipdlg;
	CPg_Vel m_Veldlg;
	CPg_Pos m_Posdlg;
	CPg_Wait m_waitdlg;
	CPg_Delay m_delaydlg;
	CPg_GHWhirl m_whirldlg;
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetType(CMD_TYPE type, PVOID pdata);
	void StopHW();
	void KeyJogMg();
// 对话框数据
	enum { IDD = IDD_DLG_PROGRAM };

protected:
	CMD_TYPE m_oldtype;
	PROGRAM_DATA *m_pdata;
	WORD m_hwaxis;
	long m_hwratio;
	BOOL m_hwOK;
		short Jogdata[MAX_NAXIS*2];
		short sJogdata[MAX_NAXIS*2];

	void MoveDlg();
	void InitCmdBox();
	void SetComBoSel(CMD_TYPE type);
	void ShowCMDDlg(CMD_TYPE type);
	void MyUpdateData(CMD_TYPE type);
	void Jog(BOOL isdown, BOOL isZ, int axis);
	void GetEncpMG();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelendokComboCmd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelendokComboAxis();
	afx_msg void OnCbnSelchangeComboRatio();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
};
