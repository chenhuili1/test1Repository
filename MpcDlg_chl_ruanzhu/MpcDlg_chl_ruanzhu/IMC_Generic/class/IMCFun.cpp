// MyShiJiaoList.cpp : implementation file
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "IMC_GenericDlg.h"
#include "IMCFun.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIMCFun

CIMCFun::CIMCFun()
{
	m_handle = NULL;
	m_Naxis = 4;
	m_cardnum = 0;
	GetCardInfo();
	for(int i=0; i<MAX_NAXIS; i++)
	{
		m_movingdes[i].addr = movingLoc;
		m_movingdes[i].len = 1;
		m_movingdes[i].axis = i;
	}
}

CIMCFun::~CIMCFun()
{
	if(m_handle != NULL)
		IMC_Close(m_handle);
}


/////////////////////////////////////////////////////////////////////////////
// CIMCFun message handlers
BOOL CIMCFun::IsOpen()
{
	return m_handle != NULL;
}
void CIMCFun::CloseDev()
{
	if(m_handle != NULL)
		IMC_Close(m_handle);
	m_handle = NULL;
}
BOOL CIMCFun::OpenDev()
{
	IMC_STATUS status = IMC_OK;

	CloseDev();
/*	NIC_INFO info;
	int cntOfcard;
	status = IMC_FindNetCard(&info, &cntOfcard);
*/
	int devid = g_cfg.devID;
	int NetSel = g_cfg.NetSel;
#if defined(WINCE)
#if (_WIN32_WCE < 0x700)
	status = IMC_Open(&m_handle, NetSel, devid);
#else
	status = IMC_Open(&m_handle, 3, devid);
#endif
#else
	status = IMC_Open(&m_handle, NetSel, devid);
#endif
	if(status == IMC_OK){
		status = IMC_GetParam16(m_handle, naxisLoc, &m_Naxis, 0);
	//	status = SetParam16(m_handle, clearimcLoc, -1, 0, SEL_IFIFO);
		LedCtr(LED_YELLOW, LED_ON, SEL_IFIFO);
		LedCtr(LED_RED, LED_OFF, SEL_IFIFO);
		LedCtr(LED_GREED, LED_OFF, SEL_IFIFO);
		PreCfg(m_handle);
		for(int a=0; a<m_Naxis; a++){
			IMCConfig(m_handle, a);
		}
		PreCfgPFIFO(m_handle, SEL_PFIFO1);
		CfgPFIFO(m_handle, SEL_PFIFO1);
	}
	return status == IMC_OK;
}
void CIMCFun::GetCardInfo()
{
	IMC_FindNetCard(&m_cardInfo, &m_cardnum);
}

IMC_STATUS CIMCFun::SetParam16(IMC_HANDLE handle, short loc, short data, long axis, int fifo)
{
	IMC_STATUS status = IMC_OK;
//	if(axis > VALID_NAXIS) return IMC_INVALID_AXIS;
	do{
		status = IMC_SetParam16(handle, loc, data, axis, fifo);
	}while((status == IMC_FIFO_FULL || status == IMC_TIME_OUT) && !m_isStop);
	return status;
}
IMC_STATUS CIMCFun::SetParam32(IMC_HANDLE handle, short loc, long data, long axis, int fifo)
{
	IMC_STATUS status = IMC_OK;
//	if(axis > VALID_NAXIS) return IMC_INVALID_AXIS;
	do{
		status = IMC_SetParam32(handle, loc, data, axis, fifo);
	}while((status == IMC_FIFO_FULL || status == IMC_TIME_OUT) && !m_isStop);
	return status;
}
IMC_STATUS CIMCFun::SetParam48(IMC_HANDLE handle, short loc, __int64 data, long axis, int fifo)
{
	IMC_STATUS status = IMC_OK;
//	if(axis > VALID_NAXIS) return IMC_INVALID_AXIS;
	do{
		status = IMC_SetParam48(handle, loc, data, axis, fifo);
	}while((status == IMC_FIFO_FULL || status == IMC_TIME_OUT) && !m_isStop);
	return status;
}

/////////////////////////////////////////////////////////////////////////////
//��ȡ����

IMC_STATUS CIMCFun::GetData1(WORD loc, WORD *pdata, WORD *axis, WORD num)
{
	WR_MUL_DES des[16];
	WORD i;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<num; i++)
	{
		des[i].addr = loc;
		des[i].len = 1;
		des[i].axis = axis[i];
	}
	status = IMC_GetMulParam(m_handle, des, num);
	if(status == IMC_OK)
	{
		for(i=0; i<num; i++)
			pdata[i] = des[i].data[0];
	}
	return status;
}
IMC_STATUS CIMCFun::GetData2(WORD loc, long *pdata, WORD *axis, WORD num)
{
	WR_MUL_DES des[16];
	WORD i;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<num; i++)
	{
		des[i].addr = loc;
		des[i].len = 2;
		des[i].axis = axis[i];
	}
	status = IMC_GetMulParam(m_handle, des, num);
	if(status == IMC_OK)
	{
		for(i=0; i<num; i++)
			pdata[i] = (des[i].data[0] & 0xFFFF) | ((des[i].data[1] << 16) & 0xFFFF0000);
	}
	return status;
}
IMC_STATUS CIMCFun::GetParamMul(WR_MUL_DES * des, int num)
{
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	status = IMC_GetMulParam(m_handle, des, num);
	return status;
}
IMC_STATUS CIMCFun::GetError(WORD *err, WORD *axis, WORD num)
{
	return GetData1(errorLoc, err, axis, num);
}
IMC_STATUS CIMCFun::GetEncp(long *encp, WORD *axis, WORD num)
{
	return GetData2(encpLoc, encp, axis, num);
}

IMC_STATUS CIMCFun::SetData16(short loc, short data, int sel)
{
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	return SetParam16(m_handle, loc, data, 0, sel);
}
IMC_STATUS CIMCFun::GetData16(short loc, short *data, long axis)
{
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	return IMC_GetParam16(m_handle, loc, data, axis);
}
IMC_STATUS CIMCFun::GetMoving(short *data)
{
	WORD i;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	status = IMC_GetMulParam(m_handle, m_movingdes, m_Naxis);
	if(status == IMC_OK)
	{
		for(i=0; i<m_Naxis; i++)
		{
			data[i] = m_movingdes[i].data[0];
		}
	}
	return status;
}
IMC_STATUS CIMCFun::KeyInPut(short* pdata)
{
	WR_MUL_DES des[KEY_NUM];
	WORD i, k = 0;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<KEY_NUM; i++)
	{
		if(g_iomap.mapKey[i].bit > 0){
			des[k].addr = g_iomap.mapKey[i].loc;
			des[k].len = 1;
			des[k].axis = g_iomap.mapKey[i].axis;
			k++ ;
		}
	}
	if(k > 0){
		status = IMC_GetMulParam(m_handle, des, k);
		if(status == IMC_OK)
		{
			k=0;
			for(i=0; i<KEY_NUM; i++){
				if(g_iomap.mapKey[i].bit > 0)
					pdata[i] = (des[k++].data[0] & (1 << ((g_iomap.mapKey[i].bit-1)%16))) ? SW_INPUT_OPEN : SW_INPUT_CLOSE;
				else
					pdata[i] = SW_INPUT_OPEN;
			}
		}else{
			for(i=0; i<KEY_NUM; i++)
				pdata[i] = SW_INPUT_OPEN;
		}
	}else{
		for(i=0; i<KEY_NUM; i++){
			pdata[i] = SW_INPUT_OPEN;
		}
	}
	return status;
}
IMC_STATUS CIMCFun::GetInPut(short* pdata)
{
	WR_MUL_DES des[INPUT_NUM];
	WORD i;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<INPUT_NUM; i++)
	{
		des[i].addr = g_iomap.mapI[i].loc;
		des[i].len = 1;
		des[i].axis = g_iomap.mapI[i].axis;
	}
	status = IMC_GetMulParam(m_handle, des, INPUT_NUM);
	if(status == IMC_OK)
	{
		for(i=0; i<INPUT_NUM; i++)
			pdata[i] = (des[i].data[0] & (1 << (g_iomap.mapI[i].bit%16))) ? SW_INPUT_OPEN : SW_INPUT_CLOSE;
	}
	return status;
}
IMC_STATUS CIMCFun::GetOutPut(short* pdata)
{
	WR_MUL_DES des[OUTPUT_NUM];
	WORD i;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<OUTPUT_NUM; i++)
	{
		des[i].addr = g_iomap.mapO[i].loc;
		des[i].len = 1;
		des[i].axis = g_iomap.mapO[i].axis;
	}
	status = IMC_GetMulParam(m_handle, des, OUTPUT_NUM);
	if(status == IMC_OK)
	{
		for(i=0; i<OUTPUT_NUM; i++)
			pdata[i] = (des[i].data[0] & (1 << (g_iomap.mapO[i].bit%16))) ? SW_OUTPUT_ON : SW_OUTPUT_OFF;
	}
	return status;
}
IMC_STATUS CIMCFun::GetAio(short* pdata)
{
	WR_MUL_DES des[16];
	WORD i;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<g_Naxis; i++)
	{
		des[i].addr = aioLoc;
		des[i].len = 1;
		des[i].axis = i;
	}
	status = IMC_GetMulParam(m_handle, des, g_Naxis);
	if(status == IMC_OK)
	{
		for(i=0; i<g_Naxis; i++)
			pdata[i] = des[i].data[0];
	}
	return status;
}
//*************************************************************************
void CIMCFun::PreCfgPFIFO(IMC_HANDLE handle, int fifo)
{
	IMC_STATUS status;
	if(fifo == SEL_PFIFO1){
		status = SetParam16(handle, clrPFIFO1Loc, -1, 0, SEL_IFIFO);	//���PFIFO1����ָ��
		status = SetParam32(handle, pwaittime1Loc, 0, 0, SEL_IFIFO);	//����ȴ�������֮ǰδ��ɵĵȴ�ָ�����������͵�fifo��ָ��
		status = SetParam16(handle, startpath1Loc, -1, 0, SEL_IFIFO);		//���ò岹�˶��ռ�1
	}else if(fifo == SEL_PFIFO2){
		status = SetParam16(handle, clrPFIFO2Loc, -1, 0, SEL_IFIFO);	//���PFIFO2����ָ��
		status = SetParam32(handle, pwaittime2Loc, 0, 0, SEL_IFIFO);	//����ȴ�������֮ǰδ��ɵĵȴ�ָ�����������͵�fifo��ָ��
		status = SetParam16(handle, startpath2Loc, -1, 0, SEL_IFIFO);		//���ò岹�˶��ռ�2
	}
//    status = SetParam16(handle, stopinLoc, 0, 0, SEL_IFIFO);				//�輱ͣ���صļ���Ϊ�͵�ƽ��Ч
}
void CIMCFun::PreCfg(IMC_HANDLE handle)
{
	IMC_STATUS status;
	status = SetParam16(handle, clearimcLoc, -1, 0, SEL_IFIFO);		//
	if(g_polar.stopin)
		status = SetParam16(handle, stopinLoc, 1, 0, SEL_IFIFO);				//�輱ͣ���صļ���Ϊ�ߵ�ƽ��Ч
	else
		status = SetParam16(handle, stopinLoc, 0, 0, SEL_IFIFO);				//�輱ͣ���صļ���Ϊ�͵�ƽ��Ч
/*	short i, data = 0;
	for(i=0; i< 16; i++)
	{
		if(g_polar.gin[i])
			data |= 1 << i;
	}
	status = SetParam16(m_handle, gin1Loc, data, 0, SEL_IFIFO);	//IO
	data = 0;
	for(i=0; i< 16; i++)
	{
		if(g_polar.gin[i + 16])
			data |= 1 << i;
	}
	status = SetParam16(m_handle, gin2Loc, data, 0, SEL_IFIFO);	//IO*/
}
//���ÿ��ƿ�����
void CIMCFun::IMCConfig(IMC_HANDLE handle, int index) 
{//�˺������ÿ��ƿ����������ã����ƿ���һ���ϵ硢����������������иı�����Щ�Ĵ�����ֵ���������������
	// TODO: Add your control notification handler code here
	IMC_STATUS status;
	int axis;
	long acc;
	short data;
	if(handle==NULL) return;
	axis = g_factcfg.g_mapAxis[index];
    status = SetParam16(handle, clearLoc, -1, axis, SEL_IFIFO);		//��������λ��ֵ��״̬,����clear����������ڵ�һ


	if(index == 4||index == 5)
	{
		status = SetParam16(handle, encpctrLoc, (short)0x0004, axis, SEL_IFIFO);	//�����������üĴ���,bit15=1Ϊʹ���ڲ����ⷴ��������ο����ƿ�˵����

		status = SetParam16(handle, runLoc, 0, axis, SEL_IFIFO);			//���и���
		return;
	}

/*		//IMC_SetParamBit( handle, encpctrLoc, 2, 1, axis,SEL_IFIFO);
		//IMC_SetParamBit( handle, encpctrLoc, 2, 1, axis,SEL_IFIFO);
	*/



    status = SetParam16(handle, sethomeLoc, -1, axis, SEL_IFIFO);		//�ѵ�ǰλ����Ϊԭ��
    status = SetParam16(handle, pathabsLoc, -1, axis, SEL_IFIFO);		//���ø�����·���岹������Ϊ��������
    status = SetParam16(handle, steptimeLoc, g_factcfg.steptime[index], axis, SEL_IFIFO);	//������������������ָ�����裬һ���ŷ�Ϊ20���ϣ�����Ϊ100����
    status = SetParam32(handle, accellimLoc, 0x7FFFFFFF, axis, SEL_IFIFO);//���ٶ����ƣ�������������
    status = SetParam32(handle, vellimLoc, 0x7FFFFFFF, axis, SEL_IFIFO);//�ٶ����ƣ�������������
    status = SetParam32(handle, mcsmaxvelLoc, 200000000, axis, SEL_IFIFO);//�㵽���˶�������ٶ�
	acc = g_cfg.accel[index] * IMC_ACCEL_FAC(index);
    status = SetParam32(handle, mcsaccelLoc, acc, axis, SEL_IFIFO);	//������ϵ���ٶ�
    status = SetParam32(handle, mcsdecelLoc, acc, axis, SEL_IFIFO);	//������ϵ���ٶ�

    status = SetParam32(handle, pcsmaxvelLoc, 200000000, axis, SEL_IFIFO);//�㵽���˶�������ٶ�
    status = SetParam32(handle, pcsaccelLoc, acc, axis, SEL_IFIFO);	//������ϵ���ٶ�
    status = SetParam32(handle, pcsdecelLoc, acc, axis, SEL_IFIFO);	//������ϵ���ٶ�

	acc = g_cfg.workVel[index] * IMC_SPEED_FAC(index);
	status = SetParam32(m_handle, highvelLoc, acc, axis, SEL_IFIFO);	//��������ĸ��ٶ�
	status = SetParam32(m_handle, lowvelLoc, acc/6, axis, SEL_IFIFO);	//��������ĵ��ٶ�

	if(g_factcfg.encpctr[index])
		status = SetParam16(handle, encpctrLoc, (short)0x0004, axis, SEL_IFIFO);	//�����������üĴ���,bit15=1Ϊʹ���ڲ����ⷴ��������ο����ƿ�˵����
	else
		status = SetParam16(handle, encpctrLoc, (short)0x8004, axis, SEL_IFIFO);	//�����������üĴ���,bit15=1Ϊʹ���ڲ����ⷴ��������ο����ƿ�˵����
	acc = (long)(g_factcfg.encpfac[index]*65536);
	status = SetParam32(m_handle, encpfactorLoc, acc, axis, SEL_IFIFO);
    status = SetParam16(handle, smoothLoc, g_cfg.smooth[axis], axis, SEL_IFIFO);		//�˶�ƽ������,�����S���߼Ӽ��ٵ�ƽ���̶�
    status = SetParam16(handle, settlewinLoc, 0, axis, SEL_IFIFO);	//��ֹ����,�������ڴ�ֵ��iMC��������ֹ����Ϊ�ŷ���������һ��Ӧ����0
	data = 0x000A;
	if(g_polar.aioP[index])
		data |= (1 << 0);
	if(g_polar.aioN[index])
		data |= (1 << 2);
    status = SetParam16(handle, aioctrLoc, data, axis, SEL_IFIFO);	//��IO���üĴ���
    status = SetParam16(handle, enaLoc, -1, axis, SEL_IFIFO);			//ʹ�ܸ��ᣬ�����Ƿ��������ʹ�ܣ�ena������д�����ֵ,�����������
    status = SetParam16(handle, exitfiltLoc, 0, axis, SEL_IFIFO);		//���������ʱ��error/=0�����᲻�˳�����
    status = SetParam16(handle, stopfiltLoc, -1, axis, SEL_IFIFO);	//�����κδ����ʱ�򣬸���ֹͣ����
    status = SetParam16(handle, runLoc, -1, axis, SEL_IFIFO);			//���и���
    status = SetParam16(handle, swfilterLoc, 409, axis, SEL_IFIFO);			//���и���

}

void CIMCFun::CfgPFIFO(IMC_HANDLE handle, int fifo)
{
	IMC_STATUS status;
	if(handle == NULL) return;
	long acc = g_cfg.locusAcc * IMC_ACCEL_FAC(0);
	if(fifo == SEL_PFIFO1){
		status = SetParam32(handle, pathacc1Loc, acc, 0, fifo);		//·�����ٶ�
		status = SetParam32(handle, feedrate1Loc, 65536, 0, fifo);	//1:1�Ľ�������
		status = SetParam32(handle, segtgvel1Loc, 50000000, 0, fifo);	//���öε������ٶ�
		status = SetParam32(handle, segendvel1Loc, 0, 0, fifo);		//���ö�ĩ���ٶ�
	}else if(fifo == SEL_PFIFO2){
		status = SetParam32(handle, pathacc2Loc, acc, 0, fifo);		//·�����ٶ�
		status = SetParam32(handle, feedrate2Loc, 65536, 0, fifo);	//1:1�Ľ�������
		status = SetParam32(handle, segtgvel2Loc, 50000000, 0, fifo);	//���öε������ٶ�
		status = SetParam32(handle, segendvel2Loc, 0, 0, fifo);		//���ö�ĩ���ٶ�
	}
    status = SetParam16(handle, eventsLoc, 0, 0, fifo);				//��������¼�ָ��,�������֮ǰ���¼�ָ�����ӽ�ȥ���¼�ָ�����ԭ�е��¼�ָ��
}

//�жϵ���Ƿ������λ��
BOOL CIMCFun::IsOfHomed(int axis)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	WR_MUL_DES des[2];
	for(int i=0; i< 2; i++)
	{
		des[i].axis = axis;
		des[i].len = 1;
	}
	des[0].addr = aioLoc;
	des[1].addr = aioctrLoc;
	status = GetParamMul(des, 2);
	if(status == IMC_OK){//aioctr��bit4������ԭ�㼫�ԣ�1���ߵ�ƽ��Ч�� 0���͵�ƽ��Ч
		if(des[1].data[0] & 0x10){//�ߵ�ƽ��Ч
			if(des[0].data[0] & 0x4)//bit2��ԭ��
				return TRUE;
		}else{//�͵�ƽ��Ч
			if((des[0].data[0] & 0x4) == 0)//bit2��ԭ��
				return TRUE;
		}
	}
	return FALSE;
}

IMC_STATUS CIMCFun::FindHome(IMC16 direction, IMC32 axis)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	long acc = g_cfg.homeVel[axis] * IMC_SPEED_FAC(axis);
	status = SetParam32(m_handle, highvelLoc, acc, g_factcfg.g_mapAxis[axis], SEL_IFIFO);	//��������ĸ��ٶ�
	status = SetParam32(m_handle, lowvelLoc, acc/8, g_factcfg.g_mapAxis[axis], SEL_IFIFO);	//��������ĵ��ٶ�
	status = SetParam32(m_handle, homeposLoc, 0, g_factcfg.g_mapAxis[axis], SEL_IFIFO);	//��������ĵ��ٶ�
	if(direction)
		status = IMC_HomeSwitch2(m_handle, direction, 0, 1, g_factcfg.g_mapAxis[axis], SEL_IFIFO);//��������Ч������ֹͣ
	else
		status = IMC_HomeSwitch1(m_handle, direction, 1, 1, g_factcfg.g_mapAxis[axis], SEL_IFIFO);//��������Ч������ֹͣ
	return status;
}
IMC_STATUS CIMCFun::FindHomeWhirl(IMC16 direction, IMC16 RiseEdge, IMC32 axis, int fifo)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	long acc = g_cfg.homeVel[axis] * IMC_SPEED_FAC(axis);
	status = SetParam32(m_handle, highvelLoc, acc, g_factcfg.g_mapAxis[axis], SEL_IFIFO);	//��������ĸ��ٶ�
	status = SetParam32(m_handle, lowvelLoc, acc/8, g_factcfg.g_mapAxis[axis], SEL_IFIFO);	//��������ĵ��ٶ�
	status = SetParam32(m_handle, homeposLoc, 0, g_factcfg.g_mapAxis[axis], fifo);
	status = SetParam16(m_handle, homedLoc, 0, g_factcfg.g_mapAxis[axis], fifo);	
	//���㣺��������Ч�� �㣺�½�����Ч
	status = IMC_HomeSwitch1(m_handle, direction, RiseEdge, 1, g_factcfg.g_mapAxis[axis], fifo);//ֹͣ��ص����
	return status;
}
IMC_STATUS CIMCFun::StopFindHome(IMC32 axis)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	status = SetParam16(m_handle, gohomeLoc, 0, g_factcfg.g_mapAxis[axis], SEL_IFIFO);//
	return status;
}
IMC_STATUS CIMCFun::SetCurHome(IMC32 axis)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	int a = g_factcfg.g_mapAxis[axis];
	StopFindHome(a);
	status = SetParam32(m_handle, homeposLoc, 0, a, SEL_IFIFO);
	status = SetParam16(m_handle, sethomeLoc, -1, a, SEL_IFIFO);//
	return status;
}


IMC_STATUS CIMCFun::SetSteptime()
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	for(int i=0; i<m_Naxis; i++){
		int axis = g_factcfg.g_mapAxis[i];
		status = SetParam16(m_handle, steptimeLoc, g_factcfg.steptime[i], axis, SEL_IFIFO);
		if(g_factcfg.encpctr[i])
			status = SetParam16(m_handle, encpctrLoc, (short)0x0004, axis, SEL_IFIFO);	//�����������üĴ���,bit15=1Ϊʹ���ڲ����ⷴ��������ο����ƿ�˵����
		else
			status = SetParam16(m_handle, encpctrLoc, (short)0x8004, axis, SEL_IFIFO);	//�����������üĴ���,bit15=1Ϊʹ���ڲ����ⷴ��������ο����ƿ�˵����
		long acc = (long)(g_factcfg.encpfac[i]*65536);
		status = SetParam32(m_handle, encpfactorLoc, acc, axis, SEL_IFIFO);//
	}
	return status;
}
IMC_STATUS CIMCFun::SetPolar()
{//��������˵ļ���
	IMC_STATUS status;
	short data, i;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	
	for(i=0; i<m_Naxis; i++){
		data = 0x000A;
		if(g_polar.aioP[i])
			data |= (1 << 0);
		if(g_polar.aioN[i])
			data |= (1 << 2);
		status = SetParam16(m_handle, aioctrLoc, data, i, SEL_IFIFO);	//��IO���üĴ���
	}
	if(g_polar.stopin)
		status = SetParam16(m_handle, stopinLoc, 1, 0, SEL_IFIFO);				//�輱ͣ���صļ���Ϊ�ߵ�ƽ��Ч
	else
		status = SetParam16(m_handle, stopinLoc, 0, 0, SEL_IFIFO);				//�輱ͣ���صļ���Ϊ�͵�ƽ��Ч
/*	data = 0;
	for(i=0; i< 16; i++)
	{
		if(g_polar.gin[i])
			data |= 1 << i;
	}
	status = SetParam16(m_handle, gin1Loc, data, 0, SEL_IFIFO);	//IO
	data = 0;
	for(i=0; i< 16; i++)
	{
		if(g_polar.gin[i + 16])
			data |= 1 << i;
	}
	status = SetParam16(m_handle, gin2Loc, data, 0, SEL_IFIFO);	//IO*/

	return status;
}
IMC_STATUS CIMCFun::SetAccel()
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	for(int i=0; i<m_Naxis; i++){
		int axis = g_factcfg.g_mapAxis[i];
		long acc = (long)(g_cfg.accel[i] * IMC_ACCEL_FAC(i));
		status = SetParam32(m_handle, mcsaccelLoc, acc, axis, SEL_IFIFO);	//������ϵ���ٶ�
		status = SetParam32(m_handle, mcsdecelLoc, acc, axis, SEL_IFIFO);	//������ϵ���ٶ�
		status = SetParam16(m_handle, smoothLoc, g_cfg.smooth[axis], axis, SEL_IFIFO);
	}
	return status;
}

IMC_STATUS CIMCFun::GetEmstop(short* val)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	do{
		status = IMC_GetParamBit(m_handle, stopinLoc, val, 4, 0);
	}while(status != IMC_OK && !m_isStop);
	return status;
}
//��ͣ�����ſ��󣬻ָ����й���
IMC_STATUS CIMCFun::ReEnaAxis()
{
	int i;
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	status = SetParam16(m_handle, emstopLoc, 0, 0, SEL_IFIFO);			//���и���
	for(i=0;i<4; i++)//MAX_NAXIS
	{
		status = SetParam16(m_handle, errorLoc, 0, i, SEL_IFIFO);			//
		status = SetParam16(m_handle, enaLoc, -1, i, SEL_IFIFO);			//ʹ�ܸ��ᣬ�����Ƿ��������ʹ�ܣ�ena������д�����ֵ,�����������
		status = SetParam16(m_handle, runLoc, -1, i, SEL_IFIFO);			//���и���

	}	
	status = SetParam16(m_handle, clrPFIFO1Loc, -1, 0, SEL_IFIFO);	//���PFIFO1����ָ��
	status = SetParam32(m_handle, pwaittime1Loc, 0, 0, SEL_IFIFO);	//����ȴ�������֮ǰδ��ɵĵȴ�ָ�����������͵�fifo��ָ��
	status = SetParam16(m_handle, startpath1Loc, -1, 0, SEL_IFIFO);		//���ò岹�˶��ռ�1��ָ��

	status = SetParam16(m_handle, clrPFIFO2Loc, -1, 0, SEL_IFIFO);	//���PFIFO2����ָ��
	status = SetParam32(m_handle, pwaittime2Loc, 0, 0, SEL_IFIFO);	//����ȴ�������֮ǰδ��ɵĵȴ�ָ�����������͵�fifo��ָ��
	status = SetParam16(m_handle, startpath2Loc, -1, 0, SEL_IFIFO);		//���ò岹�˶��ռ�2
	return status;
}

//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************

void CIMCFun::StopFun(BOOL stop)
{//���ڼ�ͣ
	m_isStop = stop;
}
void CIMCFun::StopDev()
{
	if(!IsOpen()) return ;
	SetParam16(m_handle, emstopLoc, 0x10, 0, SEL_IFIFO);	//���ü�ͣ
	SetParam16(m_handle, clrPFIFO1Loc, -1, 0, SEL_IFIFO);	//���PFIFO1����ָ��
}
void CIMCFun::StopReset()
{
	if(!IsOpen()) return ;
	SetParam16(m_handle, emstopLoc, 0, 0, SEL_IFIFO);	//��ͣ�ָ�
	for(long axis=0; axis<4; axis ++){//g_Naxis
		SetParam16(m_handle, errorLoc, 0, axis, SEL_IFIFO);	//
		SetParam16(m_handle, enaLoc, -1, axis, SEL_IFIFO);			//���и���
		SetParam16(m_handle, runLoc, -1, axis, SEL_IFIFO);			//���и���
	}
	SetParam16(m_handle, startpath1Loc, -1, 0, SEL_IFIFO);		//���ò岹�˶��ռ�1��ָ��
}

IMC_STATUS CIMCFun::MapAxis(int fifo, long *axis, int num)
{
	IMC_STATUS status;
	short segmap_xLoc, i;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(fifo == SEL_PFIFO1)
		segmap_xLoc = segmap_x1Loc;
	else if(fifo == SEL_PFIFO2)
		segmap_xLoc = segmap_x2Loc;
	for(i=0; i<num; i++)
		status = SetParam16(m_handle, segmap_xLoc + i, (short)axis[i], 0, fifo);	//ӳ����
	return status;
}


IMC_STATUS CIMCFun::AddLineNWithVel(PFIFOSegInfo* pdata, int sel)
{
	IMC_STATUS status;
	short cnt = 0;
	do{
		status = IMC_AddLineNWithVel(m_handle, pdata, sel);
		if(status == IMC_OK) break;
		else{
			if(status == IMC_FIFO_FULL)	Sleep(10);
			else if(status == IMC_TIME_OUT){
				if(cnt > 50){//���߶Ͽ�������
					cnt = 0;
				}else cnt ++;
			}
		}
	}while(status != IMC_OK && !m_isStop);
	return status ;
}
IMC_STATUS CIMCFun::AddArcLineWithVel(PFIFOSegInfo* pdata, int sel)
{
	IMC_STATUS status;
	short cnt = 0;
	do{
		status = IMC_AddArcLineWithVel(m_handle, pdata, sel);
		if(status == IMC_OK) break;
		else{
			if(status == IMC_FIFO_FULL)	Sleep(10);
			else if(status == IMC_TIME_OUT){
				if(cnt > 50){//���߶Ͽ�������
					cnt = 0;
				}else cnt ++;
			}
		}
	}while(status != IMC_OK && !m_isStop);
	return status ;
}

BOOL CIMCFun::GetCenter(double *cx, double *cy, double x1, double y1, double x2, double y2, double x3, double y3)
{//http://wenku.baidu.com/link?url=LNtCZY_2HcbGTXHysk4i8yAcDtRNuzLe9AVmN73iNVdEvW0llkjnWPYDh8V4QsB4nGgVILfrMejWw_T7pXLbNKp-Q1ADey8UuVoR6oF69SG
	double u, v,b, k1, k2, y;
	if(x1 == x2) {
		k1 = 0;
		u = 0;
	}else {
		k1 = (y1 - y2)/(x1 - x2);
		u = (x1*x1 - x2*x2 + y1*y1 - y2*y2)/(2*x1 - 2*x2);
	}
	b = 1.0*y1 - k1 * x1;
	if((x3 * k1 + b) == y3) return FALSE;//��ͬһ��ֱ����
	if(x1 == x3) {
		k2 = 0;
		v = 0;
	}else {
		k2 = (y1 - y3)/(x1 - x3);
		v = (x1*x1 - x3*x3 + y1*y1 - y3*y3)/(2*x1 - 2*x3);
	}
	if(k1 == k2) y = 0;
	else y = (u - v)/(k1 - k2);
//	*cx = v - k2* y;
	*cx = u - k1 *y;
	*cy = y;
	return TRUE;
}

struct ARC_COORD{
	double x;
	double y;
};
#define TWOPI 6.283185307179586

int CIMCFun::GetArcDir(double cx, double cy, double x1, double y1, double x2, double y2, double x3, double y3)
{//x1��y1������꣬ x2��y2Բ���ϵĵ����꣬ x3��y3�յ����꣬ cx��cyԲ������
	ARC_COORD p1, p2, p3;
	double theta[3];
	p1.x = x1 -cx;
	p1.y = y1 -cy;
	p2.x = x2 -cx;
	p2.y = y2 -cy;
	p3.x = x3 -cx;
	p3.y = y3 -cy;
	theta[0] = atan2(p1.y, p1.x);
	theta[1] = atan2(p2.y, p2.x);
	theta[2] = atan2(p3.y, p3.x);
	if(theta[0] < 0) theta[0] = theta[0] + TWOPI;
	if(theta[1] < 0) theta[1] = theta[1] + TWOPI;
	if(theta[2] < 0) theta[2] = theta[2] + TWOPI;
	theta[1] = theta[1] - theta[0];
	theta[2] = theta[2] - theta[0];
	if(theta[1] < 0) theta[1] = theta[1] + TWOPI;
	if(theta[2] < 0) theta[2] = theta[2] + TWOPI;
	if(theta[1] < theta[2]) //Բ���ϵĵ�Ƕ�С���յ�Ƕȣ�
		return ARC_DIR_N;
	else
		return ARC_DIR_S;
}




//�㶯
IMC_STATUS CIMCFun::Jog(long vel, int axis)
{
	if(!IsOpen()) return IMC_INVALID_HANDLE;
    long acc = (long)(g_cfg.accel[0] * IMC_ACCEL_FAC(0));
    SetParam32(m_handle, pcsaccelLoc, acc, axis, SEL_IFIFO);
    SetParam32(m_handle, pcsdecelLoc, acc, axis, SEL_IFIFO);
	return SetParam32(m_handle, pcstgvelLoc, vel, g_factcfg.g_mapAxis[axis], SEL_IFIFO);
//	return IMC_MoveVelocity(m_handle, vel, g_factcfg.g_mapAxis[axis], SEL_IFIFO);
}

#define GET_INTER_SPEED(velSel, axis)	(((velSel) == 0) ? ((IMC32)(g_cfg.locusVel*IMC_SPEED_FAC(axis))) : \
							((IMC32)(g_cfg.locusFastVel*IMC_SPEED_FAC(axis))) )

IMC_STATUS CIMCFun::LineMulCtrl(PROGRAM_DATA * pdata, int fifo, BOOL nextIsP)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(pdata->posBit == 0) return IMC_OK;
	PFIFOSegInfo info;
	long i, k=0, cnt, axis[MAX_NAXIS];
	for(i=0; i<g_Naxis; i++){
		if(pdata->posBit & (1<<i))
			axis[k++] = g_factcfg.g_mapAxis[i];
	}
	if(k < 1) return IMC_OK;
	MapAxis(fifo, axis, k);
	cnt = k;
	for(i=0; i<cnt; i++)
	{		
		if(pdata->InSel)
			status = SetParam16(m_handle, pathabsLoc, 0, axis[i], fifo);
		else
			status = SetParam16(m_handle, pathabsLoc, -1, axis[i], fifo);
	}
	info.data.datanum = k;
	info.SegTgVel = GET_INTER_SPEED(pdata->vel, axis[0]);
	info.SegEndVel = nextIsP ? GET_INTER_SPEED(pdata->vel, axis[0]) : 0;
	k = 0;
	for(i=0; i<MAX_NAXIS; i++){
		if(pdata->posBit & (1<<i)){
			info.data.SegEndData[k++] = ((IMC32)(pdata->pos[i] * g_factcfg.distFac[i]));
		}
	}
	long acc = g_cfg.locusAcc * IMC_ACCEL_FAC(axis[0]);
	status = SetParam32(m_handle, pathacc1Loc, acc, axis[0], fifo);		//·�����ٶ�
	long ratio = 65536*(pdata->velRatio+1)/10;
	if(fifo == SEL_PFIFO1){
		status = SetParam32(m_handle, feedrate1Loc, ratio, 0, fifo);
	}else{
		status = SetParam32(m_handle, feedrate2Loc, ratio, 0, fifo);
	}
	status = AddLineNWithVel(&info, fifo);
	for(i=0; i<cnt; i++)
	{		
		status = SetParam16(m_handle, pathabsLoc, -1, axis[i], fifo);
	}
	PauseWait(fifo);
	return status;
}

IMC_STATUS CIMCFun::ArcCtrl(PROGRAM_DATA * pdata, int fifo, BOOL nextIsP)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	PFIFOSegInfo info;
	long axis[MAX_NAXIS],id[MAX_NAXIS], k=0, i;
	for(i=0; i< g_Naxis; i++){
		if(pdata->arcBit & (1<<i)){
			axis[k] = g_factcfg.g_mapAxis[i];
			id[k++] = i;
		}
	}
	for(i=0; i<MAX_NAXIS; i++){
		if(pdata->posBit & (1<<i)){
			axis[k] = g_factcfg.g_mapAxis[i];
			id[k++] = i;
		}
	}
	MapAxis(fifo, axis, k);
	info.data.datanum = 2;

	info.SegTgVel = (IMC32)(g_cfg.locusFastVel*IMC_SPEED_FAC(id[0]));
	info.SegEndVel = GET_INTER_SPEED(pdata->vel, id[0]);
	info.data.SegEndData[0] = ((IMC32)(pdata->arc[0] * g_factcfg.distFac[id[0]]));
	info.data.SegEndData[1] = ((IMC32)(pdata->arc[1] * g_factcfg.distFac[id[1]]));
	status = AddLineNWithVel(&info, fifo);//�ƶ������λ��
	if(status != IMC_OK) return status;
	
	info.SegTgVel = GET_INTER_SPEED(pdata->vel, id[0]);
	info.SegEndVel = nextIsP ? GET_INTER_SPEED(pdata->vel, id[0]) : 0;
	info.data.SegEndData[0] = ((IMC32)(pdata->arc[4] * g_factcfg.distFac[id[0]]));
	info.data.SegEndData[1] = ((IMC32)(pdata->arc[5] * g_factcfg.distFac[id[1]]));
	for(i=2; i<k; i++)
		info.data.SegEndData[i] = ((IMC32)(pdata->pos[id[i]] * g_factcfg.distFac[id[i]]));
	info.data.CenterX = ((IMC32)(pdata->center[0] * g_factcfg.distFac[id[0]]));
	info.data.CenterY = ((IMC32)(pdata->center[1] * g_factcfg.distFac[id[1]]));
	info.data.dir = (pdata->dir & 0xFFFF);
	long acc = g_cfg.locusAcc * IMC_ACCEL_FAC(id[0]);
	status = SetParam32(m_handle, pathacc1Loc, acc, axis[0], fifo);		//·�����ٶ�
	long ratio = 65536*(pdata->velRatio+1)/10;
	if(fifo == SEL_PFIFO1)
		status = SetParam32(m_handle, feedrate1Loc, ratio, 0, fifo);
	else
		status = SetParam32(m_handle, feedrate2Loc, ratio, 0, fifo);
	MapAxis(fifo, axis, k);
	info.data.datanum = k;
	status = AddArcLineWithVel(&info, fifo);

	PauseWait(fifo);
	return status;
}

IMC_STATUS CIMCFun::OutPutCtrl(PROGRAM_DATA * pdata, int fifo)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
#ifdef CHANGE_DATA_0
	int id = pdata->OutputBit;
	int val = pdata->OutputVal;
#else
	int id = (pdata->Output>> 8) & 0xFF;
	int val = pdata->Output & 0xFF;
#endif
	int bit = g_iomap.mapO[id].bit%16;
	do{
		status = IMC_SetParamBit(m_handle, g_iomap.mapO[id].loc, bit, 
			(val== IOVAL_OPEN) ? SW_OUTPUT_ON : SW_OUTPUT_OFF, g_iomap.mapO[id].axis, fifo);
	}while(status != IMC_OK && !m_isStop);
	return status;
}
IMC_STATUS CIMCFun::OutPutCtrl(int id, int val,  int fifo)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	do{
		status = IMC_SetParamBit(m_handle, g_iomap.mapO[id].loc, g_iomap.mapO[id].bit%16, 
			(val== IOVAL_OPEN) ? SW_OUTPUT_ON : SW_OUTPUT_OFF, g_iomap.mapO[id].axis, fifo);
	}while(status != IMC_OK && !m_isStop);
	return status;
}

IMC_STATUS CIMCFun::InPutCtrl(PROGRAM_DATA * pdata, short* val)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
#ifdef CHANGE_DATA_0
	int bit = pdata->InputBit;
#else
	int bit = (pdata->Input>> 8) & 0xFF;
#endif
	do{
		status = IMC_GetParamBit(m_handle, g_iomap.mapI[bit].loc, val, g_iomap.mapI[bit].bit%16, 
			g_iomap.mapI[bit].axis);
	}while(status != IMC_OK && !m_isStop);
	return status;
}

IMC_STATUS CIMCFun::WaitTime(long time, int fifo)
{
	IMC_STATUS status = IMC_OK;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(time > 0){
		do{
			status = IMC_WaitTime(m_handle, time, fifo);
		}while(status != IMC_OK && !m_isStop);
		do{
			status = SetParam16(m_handle, user16b9Loc, 0, 0, fifo);
		}while(status != IMC_OK && !m_isStop);
	}
	return status;
}

IMC_STATUS CIMCFun::LedCtr(int led, int val, int fifo)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(g_iomap.mapLed[led].bit < 1) return IMC_OK;
	status = IMC_SetParamBit(m_handle, g_iomap.mapLed[led].loc, (g_iomap.mapLed[led].bit-1)%16, 
		(val== LED_ON) ? SW_OUTPUT_ON : SW_OUTPUT_OFF, g_iomap.mapLed[led].axis, fifo);
	return status;
}
IMC_STATUS CIMCFun::GohomeSynCtrl(PROGRAM_DATA * pdata, int fifo)
{//ͬ������
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(pdata->homeBit == 0) return IMC_OK;
	PFIFOSegInfo info;
	long i, k=0, axis[MAX_NAXIS];
	for(i=0; i<g_Naxis; i++){
		if(pdata->homeBit & (1<<i))
			axis[k++] = g_factcfg.g_mapAxis[i];
	}
	if(k < 1) return IMC_OK;
	MapAxis(fifo, axis, k);
	info.data.datanum = k;
	info.SegTgVel = GET_INTER_SPEED(pdata->vel, axis[0]);
	info.SegEndVel = 0;
	for(i=0; i<k; i++){
		info.data.SegEndData[i] = 0;
	}
	long ratio = 65536*(pdata->velRatio+1)/10;
	if(fifo == SEL_PFIFO1)
		status = SetParam32(m_handle, feedrate1Loc, ratio, 0, fifo);
	else
		status = SetParam32(m_handle, feedrate2Loc, ratio, 0, fifo);
	status = AddLineNWithVel(&info, fifo);
	PauseWait(fifo);
	return status;
}
IMC_STATUS CIMCFun::GohomeSortCtrl(PROGRAM_DATA * pdata, int fifo)
{//��˳�����
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(pdata->homeBit == 0) return IMC_OK;
	PFIFOSegInfo info;
	long i, k=0, m, n, Axis[MAX_NAXIS], axis[MAX_NAXIS], sort[MAX_NAXIS];
	info.data.datanum = 1;
	info.SegEndVel = 0;
	info.data.SegEndData[0] = 0;
	long ratio = 65536*(pdata->velRatio+1)/10;
	if(fifo == SEL_PFIFO1)
		status = SetParam32(m_handle, feedrate1Loc, ratio, 0, fifo);
	else
		status = SetParam32(m_handle, feedrate2Loc, ratio, 0, fifo);
	for(i=0; i<g_Naxis; i++){
		if(pdata->homeBit & (1<<i)){
			Axis[k] = g_factcfg.g_mapAxis[i];
			sort[k++] = pdata->homeSort[i];
		}
	}
	for(n=0; n<g_Naxis; n++){
		m=0;
		for(i=0; i<k; i++){
			if(sort[i] == n)//���һ���˳����ͬ�����
				axis[m++] = Axis[i];
		}
		if(m>0){
			info.SegTgVel = GET_INTER_SPEED(pdata->vel, axis[0]);
			MapAxis(fifo, axis, m);
			info.data.datanum = m;
			for(i=0; i<m; i++)
				info.data.SegEndData[i] = 0;
			status = AddLineNWithVel(&info, fifo);
		}
	}
	PauseWait(fifo);
	return status;
}
//�����˶�
IMC_STATUS CIMCFun::VelCtrl(PROGRAM_DATA * pdata, int fifo)
{
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	IMC_STATUS status;
	long vel;
	vel = (pdata->vel == 0) ? (g_cfg.workVel[pdata->axis]*IMC_SPEED_FAC(pdata->axis)) : 
		(pdata->vel == 1) ? (g_cfg.fastVel[pdata->axis]*IMC_SPEED_FAC(pdata->axis)) : 0;
	if(pdata->dir) vel = -vel;
	vel = vel * (pdata->velRatio+1)/10;
	do{
		status = IMC_MoveVelocity(m_handle, vel, g_factcfg.g_mapAxis[pdata->axis], fifo);
	}while(status != IMC_OK && !m_isStop);
	PauseWait(fifo);
	return status;
}
//�㵽��
IMC_STATUS CIMCFun::PosCtrl(PROGRAM_DATA * pdata, int fifo)
{
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	IMC_STATUS status;
	long vel, a;
	a = g_factcfg.g_mapAxis[pdata->axis];
	vel = (pdata->vel == 0) ? (g_cfg.workVel[pdata->axis]*IMC_SPEED_FAC(pdata->axis)) : 
								(g_cfg.fastVel[pdata->axis]*IMC_SPEED_FAC(pdata->axis));
	vel = vel * (pdata->velRatio+1)/10;
	do{
		status = SetParam32(m_handle, mcsmaxvelLoc, vel, a, fifo);
	}while(status != IMC_OK && !m_isStop);
	do{
		if(pdata->InSel)
			status = IMC_MoveRelative(m_handle, (IMC32)(pdata->pos[0] * g_factcfg.distFac[pdata->axis]), a, fifo);
		else
			status = IMC_MoveAbsolute(m_handle, (IMC32)(pdata->pos[0] * g_factcfg.distFac[pdata->axis]), a, fifo);
	}while(status != IMC_OK && !m_isStop);
/*	if(pdata->isWT){
		do{
			status = IMC_WaitParam(m_handle, movingLoc, 0, 0, a, fifo);
		}while(status != IMC_OK && !m_isStop);
	}*/
	PauseWait(fifo);
	return status;
}

#define PAUSE_LOC user32b0Loc
IMC_STATUS CIMCFun::SetPauseStatus(BOOL pause)
{
	IMC_STATUS status = IMC_OK;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(pause)
		status = SetParam16(m_handle, PAUSE_LOC, 65535, 0, SEL_IFIFO);
	else
		status = SetParam16(m_handle, PAUSE_LOC, 0, 0, SEL_IFIFO);
	return status;
}
//�岹�˶���ʱ��ʹ�ô˺���
IMC_STATUS CIMCFun::PauseWait(int fifo)
{
	IMC_STATUS status = IMC_OK;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	status = IMC_WaitParam(m_handle, PAUSE_LOC,0, 0, 0, fifo);
	return status;
}

//********************************************************************************************************************
//����
//********************************************************************************************************************
typedef struct HW_Ratio_{
	long bit;
	long data;
}HW_Ratio;

//
IMC_STATUS CIMCFun::HWJogKeyInPut(short* pdata)
{
	WR_MUL_DES des[MAX_NAXIS];
	WORD i, k = 0, m;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<g_Naxis; i++)
	{
		if(g_iomap.mapJogBnZ[i].bit > 0){
			des[k].addr = g_iomap.mapJogBnZ[i].loc;
			des[k].len = 1;
			des[k].axis = g_iomap.mapJogBnZ[i].axis;
			k++ ;
		}
		if(g_iomap.mapJogBnF[i].bit > 0){
			des[k].addr = g_iomap.mapJogBnF[i].loc;
			des[k].len = 1;
			des[k].axis = g_iomap.mapJogBnF[i].axis;
			k++ ;
		}
	}
	if(k > 0){
		status = IMC_GetMulParam(m_handle, des, k);
		if(status == IMC_OK)
		{
			k=0;
			m = 0;
			for(i=0; i<g_Naxis; i++){
				if(g_iomap.mapJogBnZ[i].bit > 0){
					pdata[k] = (des[m].data[0] & (1 << ((g_iomap.mapJogBnZ[i].bit-1)%16))) ? SW_INPUT_OPEN : SW_INPUT_CLOSE;
					m ++;
				}else
					pdata[k] = SW_INPUT_OPEN;
				k++;
				if(g_iomap.mapJogBnF[i].bit > 0){
					pdata[k] = (des[m].data[0] & (1 << ((g_iomap.mapJogBnF[i].bit-1)%16))) ? SW_INPUT_OPEN : SW_INPUT_CLOSE;
					m ++;
				}else
					pdata[k] = SW_INPUT_OPEN;
				k++;
			}
		}
	}else{
		for(i=0; i<g_Naxis*2; i++){
			pdata[i] = SW_INPUT_OPEN;
		}
	}
	return status;
}

//��ȡ�����ź�
IMC_STATUS CIMCFun::HWAxisInPut(short* pdata)
{
	WR_MUL_DES des[MAX_NAXIS];
	WORD i, k = 0;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<g_Naxis; i++)
	{
		if(g_iomap.mapHW[i+4].bit > 0){
			des[k].addr = g_iomap.mapHW[i+4].loc;
			des[k].len = 1;
			des[k].axis = g_iomap.mapHW[i+4].axis;
			k++ ;
		}
	}
	if(k > 0){
		status = IMC_GetMulParam(m_handle, des, k);
		if(status == IMC_OK)
		{
			k=0;
			for(i=0; i<g_Naxis; i++){
				if(g_iomap.mapHW[i+4].bit > 0)
					pdata[i] = (des[k++].data[0] & (1 << ((g_iomap.mapHW[i+4].bit-1)%16))) ? SW_INPUT_OPEN : SW_INPUT_CLOSE;
				else
					pdata[i] = SW_INPUT_OPEN;
			}
		}
	}else{
		for(i=0; i<g_Naxis; i++){
			pdata[i] = SW_INPUT_OPEN;
		}
	}
	return status;
}
//��ȡ�����ź�
IMC_STATUS CIMCFun::HWRatioInPut(short* pdata)
{
	WR_MUL_DES des[3];
	WORD i, k = 0;
	IMC_STATUS status = IMC_OK;
	if(!IsOpen())
		return IMC_INVALID_HANDLE;
	for(i=0; i<3; i++)
	{
		if(g_iomap.mapHW[i].bit > 0){
			des[k].addr = g_iomap.mapHW[i].loc;
			des[k].len = 1;
			des[k].axis = g_iomap.mapHW[i].axis;
			k++ ;
		}
	}
	if(k > 0){
		status = IMC_GetMulParam(m_handle, des, k);
		if(status == IMC_OK)
		{
			for(i=0; i<3; i++){
				if(g_iomap.mapHW[i].bit > 0)
					pdata[i] = (des[i].data[0] & (1 << ((g_iomap.mapHW[i].bit-1)%16))) ? SW_INPUT_OPEN : SW_INPUT_CLOSE;
				else
					pdata[i] = SW_INPUT_OPEN;
			}
		}
	}else{
		for(i=0; i<3; i++){
			pdata[i] = SW_INPUT_OPEN;
		}
	}
	return status;
}
//��������
IMC_STATUS CIMCFun::SetHandWheel(long ratio, WORD axis)
{
	IMC_STATUS status;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(axis > m_Naxis) return IMC_INVALID_PARAM;
	__int64 rt = ratio * 4294967296;
	int a = g_factcfg.g_mapAxis[axis];
	status = SetParam48(m_handle, gearratioLoc, rt, a, SEL_IFIFO);
	status = SetParam16(m_handle, masterLoc, 0, a, SEL_IFIFO);
	status = SetParam16(m_handle, gearsrcLoc, encsvelLoc, a, SEL_IFIFO);
	status = SetParam16(m_handle, engearLoc, -1, a, SEL_IFIFO);
	status = SetParam16(m_handle, smoothLoc, 64, a, SEL_IFIFO);
	return status;
}
//ȡ������
IMC_STATUS CIMCFun::StopHandWheel(WORD axis)
{
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(axis > m_Naxis) return IMC_INVALID_PARAM;
	int a = g_factcfg.g_mapAxis[axis];
	SetParam16(m_handle, smoothLoc, 32, a, SEL_IFIFO);//Ĭ��Ϊ�㵽��
	return SetParam16(m_handle, engearLoc, 0, a, SEL_IFIFO);
}

//��ȡʹ�ܵ��������
IMC_STATUS CIMCFun::GetHWAxis(WORD *axis)
{
	IMC_STATUS status = IMC_OK;
	short data[MAX_NAXIS+4], a;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	status = HWAxisInPut(data);
	for(a=0; a<g_Naxis; a++){
		if(data[a] == SW_INPUT_CLOSE){
			*axis = a;
			return status;
		}
	}
	*axis = MAX_NAXIS;
	return IMC_OTHER_ERROR;
}
//��ȡ���ֱ���
IMC_STATUS CIMCFun::GetHWRatio(long* ratio)
{
	IMC_STATUS status = IMC_OK;
	short data[MAX_NAXIS+4];
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	status = HWRatioInPut(data);
	if(data[0] == SW_INPUT_CLOSE)
		* ratio = 1;
	else if(data[1] == SW_INPUT_CLOSE)
		* ratio = 10;
	else if(data[2] == SW_INPUT_CLOSE)
		* ratio = 100;
	else{
		* ratio = 1;
		status = IMC_OTHER_ERROR;
	}
	return status;
}
//��ȡ����ȷ����ť
IMC_STATUS CIMCFun::GetHWOK(BOOL* isOK)
{
	IMC_STATUS status = IMC_OK;
	short data;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	if(g_iomap.mapHW[3].bit < 1) {
		*isOK = FALSE;
		return status;
	}
	status = GetData16( g_iomap.mapHW[3].loc, &data, g_iomap.mapHW[3].axis);
	if(status == IMC_OK){
		data = (data & (1 << ((g_iomap.mapHW[3].bit-1)%16))) ? SW_INPUT_OPEN : SW_INPUT_CLOSE;
		if(data == SW_INPUT_CLOSE)
			*isOK = TRUE;
		else
			*isOK = FALSE;
	}else *isOK = FALSE;

	return status;
}

//********************************************************************************************************************

IMC_STATUS CIMCFun::ReadVersion(WORD *ver)
{
	IMC_STATUS status = IMC_OK;
	WORD axis = 0;
	if(!IsOpen()) return IMC_INVALID_HANDLE;
	status =  GetData1( hwversionLoc, ver, &axis, 1);
	return status;
}


long CIMCFun::GetRealtimeFeedRate()
{
	long rate=0; //���õ����ƿ��������ʼĴ����е���ֵ

	IMC_STATUS status = IMC_OK;
	
	status = IMC_GetParam32(m_handle, pathvel1Loc, &rate, 0);
	return rate;
}










