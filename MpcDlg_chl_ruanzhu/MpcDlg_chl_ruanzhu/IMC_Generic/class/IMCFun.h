#if !defined(AFX_IMCFun_H__1C3C65DD_024B_40C9_AD4D_474A02155525__INCLUDED_)
#define AFX_IMCFun_H__1C3C65DD_024B_40C9_AD4D_474A02155525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIMCFun window

class CIMCFun : public CListBox
{
// Construction
public:
	CIMCFun();
	~CIMCFun();

// Attributes
public:
	NIC_INFO m_cardInfo;
	int m_cardnum;
	int m_Naxis;	//¿ØÖÆ¿¨¿É¿ØÖáÊý
// Operations
public:
	BOOL IsOpen();
	BOOL OpenDev();
	void CloseDev();
	IMC_STATUS GetError(WORD *err, WORD *axis, WORD num);
	IMC_STATUS GetEncp(long *encp, WORD *axis, WORD num);
	IMC_STATUS SetData16(short loc, short data, int sel);
	IMC_STATUS GetData16(short loc, short *data, long axis = 0);
	IMC_STATUS GetParamMul(WR_MUL_DES * des, int num);
	IMC_STATUS GetMoving(short *data);
	IMC_STATUS KeyInPut(short* pdata);
	IMC_STATUS GetOutPut(short* pdata);
	IMC_STATUS GetInPut(short* pdata);
	IMC_STATUS GetAio(short* pdata);

	BOOL IsOfHomed(int axis);
	IMC_STATUS FindHome(IMC16 direction, IMC32 axis);
	IMC_STATUS FindHomeWhirl(IMC16 direction, IMC16 RiseEdge, IMC32 axis, int fifo);
	IMC_STATUS StopFindHome(IMC32 axis);
	IMC_STATUS SetCurHome(IMC32 axis);

	IMC_STATUS HWJogKeyInPut(short* pdata);
	IMC_STATUS HWAxisInPut(short* pdata);
	IMC_STATUS HWRatioInPut(short* pdata);
	IMC_STATUS SetHandWheel(long ratio, WORD axis);
	IMC_STATUS StopHandWheel(WORD axis);
	IMC_STATUS GetHWAxis(WORD *axis);
	IMC_STATUS GetHWRatio(long* ratio);
	IMC_STATUS GetHWOK(BOOL* isOK);
	
	IMC_STATUS SetSteptime();
	IMC_STATUS SetPolar();
	IMC_STATUS SetAccel();
	IMC_STATUS ReEnaAxis();
	IMC_STATUS GetEmstop(short* val);

	void StopFun(BOOL stop);
	void StopDev();//¼±Í£
	void StopReset();//¼±Í£»Ö¸´
	IMC_STATUS Jog(long vel, int axis);
	IMC_STATUS LineMulCtrl(PROGRAM_DATA * pdata, int fifo, BOOL nextIsP);
	IMC_STATUS ArcCtrl(PROGRAM_DATA * pd, int fifo, BOOL nextIsP);
	IMC_STATUS OutPutCtrl(PROGRAM_DATA * pd, int fifo);
	IMC_STATUS OutPutCtrl(int id, int val,  int fifo);
	IMC_STATUS InPutCtrl(PROGRAM_DATA * pd, short* val);
	IMC_STATUS WaitTime(long time, int fifo);
	IMC_STATUS LedCtr(int led, int val, int fifo);
	IMC_STATUS GohomeSynCtrl(PROGRAM_DATA * pdata, int fifo);
	IMC_STATUS GohomeSortCtrl(PROGRAM_DATA * pdata, int fifo);
	IMC_STATUS VelCtrl(PROGRAM_DATA * pdata, int fifo);
	IMC_STATUS PosCtrl(PROGRAM_DATA * pdata, int fifo);
	IMC_STATUS PauseWait(int fifo);
	IMC_STATUS SetPauseStatus(BOOL pause);
	BOOL GetCenter(double *cx, double *cy, double x1, double y1, double x2, double y2, double x3, double y3);
	int GetArcDir(double cx, double cy, double x1, double y1, double x2, double y2, double x3, double y3);
	IMC_STATUS ReadVersion(WORD *ver);

	long GetRealtimeFeedRate();
IMC_HANDLE m_handle;	//Éè±¸¾ä±ú

	
protected:
	
	BOOL m_isStop;
	int m_segId1;
	WR_MUL_DES m_movingdes[MAX_NAXIS];

	void GetCardInfo();
	IMC_STATUS GetData1(WORD loc, WORD *pdata, WORD *axis, WORD num);
	IMC_STATUS GetData2(WORD loc, long *pdata, WORD *axis, WORD num);
	void CIMCFun::CfgPFIFO(IMC_HANDLE handle, int fifo);
	void CIMCFun::IMCConfig(IMC_HANDLE handle, int axis) ;
	void CIMCFun::PreCfgPFIFO(IMC_HANDLE handle, int fifo);
	void CIMCFun::PreCfg(IMC_HANDLE handle);

	IMC_STATUS SetParam16(IMC_HANDLE handle, short loc, short data, long axis, int fifo);
	IMC_STATUS SetParam32(IMC_HANDLE handle, short loc, long data, long axis, int fifo);
	IMC_STATUS SetParam48(IMC_HANDLE handle, short loc, __int64 data, long axis, int fifo);
	IMC_STATUS MapAxis(int fifo, long *axis, int num);
	IMC_STATUS AddLineNWithVel(PFIFOSegInfo* pdata, int sel);
	IMC_STATUS AddArcLineWithVel(PFIFOSegInfo* pdata, int sel);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMCFun_H__1C3C65DD_024B_40C9_AD4D_474A02155525__INCLUDED_)
