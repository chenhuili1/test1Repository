// MpcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "MpcDlg.h"
#include "IMC_GenericDlg.h"
#include "math.h"
#include "Uout.h"
#include "MMSystem.h"
#define DESTX	1.8
#pragma comment(lib,"winmm.lib")
static unsigned long m_num;
// CMpcDlg 对话框

IMPLEMENT_DYNAMIC(CMpcDlg, CDialog)

CMpcDlg::CMpcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMpcDlg::IDD, pParent)
	, m_Xpos(0),IsFileOpen(0),k(0),f(0),rc(),F(),phi(),MpcParm(),ParmSave(),ParmXkf()
{

}

CMpcDlg::~CMpcDlg()
{
}

void CMpcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Xpos);
}


BEGIN_MESSAGE_MAP(CMpcDlg, CDialog)
	//ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMpcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMpcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMpcDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMpcDlg::OnBnClickedButton5)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CMpcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	k=0;f=0;cont=0;f_last=0;v_last=0;flag=0;ckf=0;flag_v=0;stopX=0;k1=0;flag_y0=1;
	Greedledflag = 0;Redledflag = 0;Yellowledflag = 0;
	MpcParm0last =0;
	//flag=1;
	//a=0;
	dlg->RedLedOff();
	dlg->YellowLedOff();
	dlg->GreedLedOff();
	main_GetFphi(F,phi);
	for(int i=0;i<6;i++)
		axis[i]=i;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CMpcDlg::Txtsave(double *parm)
{
 // setlocale(LC_CTYPE,'chs');
  UINT cont;
  for(cont=0;cont<=DATALENGTH-4;cont=cont+4)
  {
	 for(int i=0;i<4;i++)
	 {
		CString temp;
		temp.Format(_T("%lf  "),parm[cont+i]);
		FileWrite.WriteString(temp);
	 }
  FileWrite.WriteString(_T("\n"));
  }

}

// CMpcDlg 消息处理程序
/*
void CMpcDlg::OnTimer(UINT_PTR nIDEvent)
{
	static char Ach[4] = {'X', 'V', 'A', 'B'};
	CString str;
	if(nIDEvent==TIMER_MPC)
	{
		ParmCalculate(MpcParm);
		for(int i=0; i<4; i++)
		{
			str.Format(_T("%c: %lf"), Ach[i],MpcParm[i] );
			SetDlgItemText(IDC_STATIC1 + i, str);
		}
		if(IsFileOpen)
			Txtsave(MpcParm);
	}
}
*/
UINT CMpcDlg::CreateTimer()
{
	//create the timeryte+89+121741  01234 
	// Create a periodic timer
	timeBeginPeriod(1);
	timerID = timeSetEvent(5, 1, TimeProc, (DWORD_PTR)this,TIME_PERIODIC );//TIME_PERIODIC
/*	timeBeginPeriod(2);
	timerID1 = timeSetEvent(50, 2, TimeProc1, (DWORD_PTR)this, TIME_PERIODIC);*/
	return timerID;

}
void CALLBACK CMpcDlg::TimeProc(UINT uID, UINT uMsg, DWORD  dwUser, DWORD  dw1, DWORD  dw2)
{

	CMpcDlg* pdcpackerdlg = (CMpcDlg*)dwUser;
	m_num++;
	pdcpackerdlg->m_number = m_num;
	pdcpackerdlg->MyTimer(1);   //内部设置成switch选择框架
}
void CALLBACK CMpcDlg::TimeProc1(UINT uID, UINT uMsg, DWORD  dwUser, DWORD  dw1, DWORD  dw2)
{

	CMpcDlg* pdcpackerdlg = (CMpcDlg*)dwUser;
	pdcpackerdlg->MyTimer(2);   //内部设置成switch选择框架
}
void CMpcDlg::MyTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	CString str;
	double f_temp;
	double X_status[4],Y_status[4];
	switch (nIDEvent)
	{
		case 1:
		{
					countflag++;

			/**参数读取,计算及赋值**/
					/*位移角度数据读取*/
					ParmCalculate(MpcParm);
/*

					if(abs((MpcParm[0] - X_last) * (1000/5)-X_Speed_last)<abs(f_temp*10*0.005))
					{
						MpcParm[0]=MpcParm[0];
					}
					else
					{
						MpcParm[0] =X_last + (X_Speed_last + f_temp * 0.005) * 0.005;

					}
					*/
					//Xkf(MpcParm[2],a_Y,0.05,xkf);//Y方向(m)
					//MpcParm[2]=xkf[1];


					/*速度计算*/
					//SpeedV[0] = (MpcParm[0] - X_last) * (1000/5); // X方向速度（m/s）
					//X_status[3] = (SpeedV[0] - X_Speed_last) * (1000/5);
					//SpeedV[1] = (MpcParm[2] - Y_last) * (1000/5); // Y方向速度（m/s）
					/*角速度计算*/
					AngleSpeed[0] = (MpcParm[1] - lastAngleRad[0]) * (1000/5);  //X方向角速度 （rad/s）
					//AngleSpeed[1] = (MpcParm[3] - lastAngleRad[1]) * (1000/5);  //Y方向角速度 （rad/s）
					/*上一时刻状态保存*/
					//X_last = MpcParm[0];
					//Y_last = MpcParm[2];
					//X_Speed_last =SpeedV[0];
					lastAngleRad[0] = MpcParm[1];
					//lastAngleRad[1] = MpcParm[3];
					/*X Y 状态参数赋值*/
					X_status[0] = MpcParm[0];
					X_status[1] = MpcParm[1];
					X_status[2] = MpcParm[2];
					X_status[3] = AngleSpeed[0];

					//Y_status[0] = MpcParm[2];
					//Y_status[1] = MpcParm[3];
					//Y_status[2] = SpeedV[1];
					//Y_status[3] = AngleSpeed[1];
					/*停止距离离线计算*/
					stopX=-6.7539*X_status[2]*X_status[2]+2.9649*X_status[2]-0.001;
					if(cont<=DATALENGTH-4)
						{
							for(int i=0; i<4; i++)
							{
								ParmSave[cont+i]=X_status[i];
							}
							//ParmSave[cont+3]=DeltaTickCnt;
							ParmSave[cont+3]=f_temp;
							cont=cont+4;
						}

			/*阈值处理*/
					if(X_status[1]<0.005||X_status[1]>-0.005)
						X_status[1]=0;
					if(abs(X_status[0]-DESTX)<0.002)
						X_status[0]=DESTX;
			/*处理完毕*/

			/*制动控制方案的速度赋值条件*/	
					if((X_status[2])>=0.28&&flag_y0)
					{
						flag_y0=0;
						y0[0]=0;
						y0[2]=X_status[2];
						y0[1]=X_status[1];
						y0[3]=X_status[3];
					}

					//停止控制的阈值处理
					/*if(X_status[0] >= 1)
						{
							
							g_cfg.accel[0] = 1000;
							dlg->m_imc.Jog(0, 0);
							break;
						}*/
					//停止控制的阈值处理结束

			/*循环10次执行一次控制*/	
					if(countflag>=10)
					{
						/*循环10次执行一次控制*/
						if(flag_y0==0)
						{
							if(flag_v<2)
							{
								//if(Greedledflag == 1)
								//{
								//	dlg->GreedLedOff();
								//	Greedledflag =0;
								//}
								//dlg->RedLedOn();
								f_temp=Stop(X_status);
							}
							
						}
						else
						{

							if(Greedledflag == 0)
							{
								//dlg->GreedLedOn();
								Greedledflag = 1;
								Redledflag = 0;
								Yellowledflag = 0;
							}
							//g_cfg.accel[0] = 0.2*1000;
							//while(dlg->m_imc.Jog(0.8, 0));
							f_temp=Move(X_status);
							
						}
						countflag=0;
					}
					
		break;
		}

	}


}

void CMpcDlg::DestroyTimer()
{
	timeKillEvent(timerID);
	timeEndPeriod(1);
	/*timeKillEvent(timerID1);
	timeEndPeriod(2);*/
}
void CMpcDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码


	CreateTimer();
}

void CMpcDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	//KillTimer(TIMER_MPC);
	dlg->YellowLedOff();
	DestroyTimer();
	//if (!isZ) vel = -vel;
	g_cfg.accel[0] = 500;
	dlg->m_imc.Jog(0, 0);

}
void CMpcDlg::FinishRun()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	//KillTimer(TIMER_MPC);
	//DestroyTimer();
	//if (!isZ) vel = -vel;
	g_cfg.accel[0] = 100;
	dlg->m_imc.Jog(0, 0);
}
//返回值计算函数

void CMpcDlg::ParmCalculate(double *Parm)
{
		CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
		double angle0[2],angleRad[2];
		IMC_STATUS status = IMC_OK;
		
		/**获取滴答定时器数据 **/
		IMC_GetParam32(dlg->m_imc.m_handle, ticksLoc, (PVOID)&CurTickCnt, SEL_IFIFO);
		DeltaTickCnt = CurTickCnt -OldTickCnt;
		OldTickCnt = CurTickCnt;

		/**获取六轴数据 **/

		
		//while(dlg->m_imc.GetEncp(m_encp, axis, 5));
		//while(IMC_GetParam32(dlg->m_imc.m_handle, curvelLoc, (PVOID)&Xmove, 0));
		while(IMC_GetParam32(dlg->m_imc.m_handle, encpLoc, (PVOID)&Xmove, 0));
		while(IMC_GetParam32(dlg->m_imc.m_handle, curvelLoc, (PVOID)&XCmove, 0));
		//while(IMC_GetParam32(dlg->m_imc.m_handle, curvelLoc, (PVOID)&Xangle, 3));
		while(IMC_GetParam32(dlg->m_imc.m_handle, encpLoc, (PVOID)&Xangle, 4));

/*
		status = IMC_GetParam32(dlg->m_imc.m_handle, encpvelLoc, (PVOID)&Xmove, 0);
		if(status == 0)
		{
			status = IMC_OK;
		}
		else
		{
			status = IMC_READ_FAIL;
		}
		*/

		//while(IMC_GetParam32(dlg->m_imc.m_handle, encpLoc, (PVOID)&Xangle, 3));
		m_encp[0] = Xmove;
		m_encp[4] = Xangle;
		m_encp[5] = XCmove;
	

		/**编码器原方向（斜向）角度  单位 弧度 **/
		angle0[0]=-m_encp[4]*3.1415926*2.0/(4*5000.0);//上半圆编码器
		//angle0[1]=-m_encp[5]*3.1415926*2.0/(4*5000.0);//下半圆编码器

		/**行进方向角度  单位  弧度**/
		angleRad[0]=atan(0.7071068*(tan(angle0[0])+tan(angle0[1])));//X方向
		//angleRad[1]=atan(0.7071068*(tan(angle0[1])-tan(angle0[0])));//Y方向

					

		//X方向的 位移(m)  角度(rad)
		//(double)((m_encp[5] >> 16)  + (m_encp[5] & 0x0000FFFF)/65535);
		//Parm[2]=(double)((m_encp[5] >> 16)  + (m_encp[5] & 0x0000FFFF)/65535);
		Parm[0]=IMC_ENCP_SHOW(m_encp, 0)/1000;
		Parm[1]=angleRad[0];
		Parm[2]=(double)(1.0*m_encp[5]/g_factcfg.distFac[0])/65535;

		//Y方向的 位移(m)  角度(rad) 
		//Parm[2]=IMC_ENCP_SHOW(m_encp, 1)/1000;
		//Parm[3]=angleRad[1];

}

double CMpcDlg::Move(double *Parm)
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	long vmpc;
		rc[0]=0.5-f;
		rc[1]=0.5+f;
		k=k+1;
		f=main_Getintput_u(F,phi,Parm,rc,k);
		//f=0.2;
		if(f>0)
		{
			g_cfg.accel[0] = f*1000;
			vmpc=(long)(400* IMC_SPEED_FAC(0));//(long)(MpcParm[1]*1000)+
			while(dlg->m_imc.Jog(vmpc, 0));
			
		}
		else
		{
			g_cfg.accel[0] = -f*1000;
			//vmpc=(long)((g_cfg.accel[0] *DeltaTickCnt)* IMC_SPEED_FAC(0));//(long)(MpcParm[1]*1000)+
			while(dlg->m_imc.Jog(0, 0));
			
		}
	return f;

}

double CMpcDlg::Stop(double *Parm)
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
		long vmpc;
		rc[0]=0.2-f;
		rc[1]=0.2+f;
		k1=k1+1;
		f=main_GetstopX(F,phi,Parm,rc,k1,y0);
		//f=-0.2;

		if(f>0)
		{
			g_cfg.accel[0] = f*1000;
			vmpc=(long)(400* IMC_SPEED_FAC(0));//(long)(MpcParm[1]*1000)+
			while(dlg->m_imc.Jog(vmpc, 0));
		}
		else
		{
			g_cfg.accel[0] = -f*1000;
			//vmpc=(long)((g_cfg.accel[0] *DeltaTickCnt)* IMC_SPEED_FAC(0));//(long)(MpcParm[1]*1000)+
			while(dlg->m_imc.Jog(0, 0));
		}


/*	long vmpc;
	if((a<=500)&&flag)
	{
		a=a+25;
		g_cfg.accel[0] = a;
		vmpc=(long)(200* IMC_SPEED_FAC(0));
		//vmpc=(long)((Parm[1]*1000+g_cfg.accel[0] *0.1)* IMC_SPEED_FAC(0));//(long)(MpcParm[1]*1000)+
		dlg->m_imc.Jog(vmpc, 0);
	}
	else
	{
		flag=0;
		a=a-25;
		g_cfg.accel[0] = a;
		if(a<=0)
		{
			a=0;
		}
		dlg->m_imc.Jog(0, 0);
		
	}*/
	return f;

}



void CMpcDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
 /*
	CString str;
 static char Ach[4] = {'X', 'V', 'A', 'B'};
 long t1=GetTickCount();
	for(int i=0; i<4; i++)
	{
		str.Format(_T("%c: %lf"), Ach[i],MpcParm[i] );
		SetDlgItemText(IDC_STATIC1 + i, str);
	}
	ParmCalculate(MpcParm);
	Move(MpcParm);
	if(cont<1596)
	{
		for(int i=0; i<4; i++)
		{
			ParmSave[cont+i]=MpcParm[i];
		}
		cont=cont+4;
	}
	//Sleep(1000);
long	t2=GetTickCount();
			str.Format(_T("t: %ld"), t1 );
			SetDlgItemText(IDC_STATIC1 , str);
			str.Format(_T("t: %ld"), t2 );
			SetDlgItemText(IDC_STATIC1 + 1, str);
			str.Format(_T("t: %ld"), t2-t1 );
			SetDlgItemText(IDC_STATIC1 + 2, str);
	/*		str.Format(_T("t: %ld"), t1 );
			SetDlgItemText(IDC_STATIC1 , str);
			str.Format(_T("t: %ld"), t2 );
			SetDlgItemText(IDC_STATIC1 + 1, str);
			str.Format(_T("t: %ld"), t2-t1 );
			SetDlgItemText(IDC_STATIC1 + 2, str);*/

	Filename="D:\\jtl\\MpcDlg_OutputA\\parm.txt";
	if(FileWrite.Open(Filename,CFile::modeCreate|CFile::modeWrite|CFile::typeText))
		IsFileOpen=TRUE;
	else
		IsFileOpen=FALSE;
	if(IsFileOpen)
		Txtsave(ParmSave);
    FileWrite.Close();
	/*Filename="D:\\jtl\\MpcDlg_OutputA\\parmXkf.txt";
	if(FileWrite.Open(Filename,CFile::modeCreate|CFile::modeWrite|CFile::typeText))
		IsFileOpen=TRUE;
	else
		IsFileOpen=FALSE;
	if(IsFileOpen)
	{
	  UINT cont;
	  for(cont=0;cont<=XKFNUM-2;cont=cont+2)
	  {
		 for(int i=0;i<2;i++)
		 {
			CString temp;
			temp.Format(_T("%0.5lf  "),ParmXkf[cont+i]);
			FileWrite.WriteString(temp);
		 }
	  FileWrite.WriteString(_T("\n"));
	  }
	}
    FileWrite.Close();*/
}

void CMpcDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	PROGRAM_DATA pdata;
	
	//SetTimer(TIMER_MPC, 40, NULL);



	pdata.vel = 1;
	pdata.velRatio = 10;
	pdata.axis = 0;
	UpdateData(TRUE);
	pdata.pos[0] = m_Xpos;
	UpdateData(FALSE);
//	pdata->isWT = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	pdata.InSel = 0;
	dlg->m_imc.PosCtrl(&pdata, 2);
}

void CMpcDlg::OnPaint()
{
 CPaintDC dc(this); // device context for painting
        // TODO: 在此处添加消息处理程序代码
 CRect  rect;
 GetClientRect(&rect);
 CDC  dcMem;
 dcMem.CreateCompatibleDC(&dc);
 CBitmap  bmpBackground;
 bmpBackground.LoadBitmap(IDB_BITMAP5);
 BITMAP  bitmap;
 bmpBackground.GetBitmap(&bitmap);
 CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground); 
 dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
        // 不为绘图消息调用 CDialog::OnPaint()
}