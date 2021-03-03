// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// IMC_Generic.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


SYSTEM_STATUS_OBJECT  	SysStatusObj;


	CString g_cmdStr[CMD_TOTAL];
	CString g_AxisName[MAX_NAXIS];
	int g_Naxis;	//
	FACT_CFG g_factcfg;
	SYS_CFG g_cfg;
	TEST_VER_INFO g_verinfo;
	FACT_POLAR g_polar;
	FACT_IOMAP_INFO g_iomap;
	FACT_WARN *g_warn;
	int g_warnNum;

#if defined(WINCE)
	BOOL g_isSipShow;//�Ƿ��Ѿ���ʾ���뷨
#endif

	BOOL g_isTestV;

	BOOL g_isUseHWok;	//������Ƿ�ʹ������ȷ����ť����

//����һ������
CFont* MyGetFonts(int height, WCHAR *name, int width)
{
	CFont *fn = new CFont;
	fn->CreateFont(height,            // nHeight ����ĸ߶�
		0,           // nWidth ����Ŀ�ȡ�
		0,           // nEscapement �������б��
		0,           // nOrientation �������б��
		width,//FW_BOLD,     // nWeight ����Ĵ�ϸ��
		FALSE,        // bItalic �����Ƿ�б�塣
		FALSE,       // bUnderline �����Ƿ����»��ߡ�
		0,           // cStrikeOut �����Ƿ���ɾ����
		GB2312_CHARSET,              // nCharSet ����ʹ�õ��ַ�����
		OUT_DEFAULT_PRECIS,        // nOutPrecision ���ѡ����ʵ����塣
		CLIP_DEFAULT_PRECIS,       // nClipPrecision ����ȷ���ü��ľ��ȡ�
		DEFAULT_QUALITY,           // nQuality ��ô����ѡ�����������ϡ�
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily ����־�����Ա�־
		(name == NULL) ? _T("����") : name); //_T("Arial"));             // lpszFac��������ơ�
	return fn;
}
	
	
LONGLONG m_QPart1;
double m_dfFreq;
void StartTimes()
{
	LARGE_INTEGER litmp;
	//��ü�ʱ����ʱ��Ƶ��
	QueryPerformanceFrequency(&litmp);
	m_dfFreq = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);
	m_QPart1 = litmp.QuadPart; //��ʼ��ʱ
}

DWORD GetTimes()
{
	LARGE_INTEGER litmp;
	double dfMinus,dfTime;
	LONGLONG QPart2;
	QueryPerformanceCounter(&litmp);
	QPart2 = litmp.QuadPart; //��ֹ��ʱ
	dfMinus = (double)(QPart2 - m_QPart1);//���������ֵ
	dfTime = dfMinus / m_dfFreq;//��ö�Ӧʱ�䣬��λΪ�� ����Գ�1000000��ȷ��΢�뼶��us��
//	return (DWORD)(dfTime*1000000);//΢��
//	return (DWORD)(dfTime*1000);	//����
	return (DWORD)dfTime;			//��
}

LONGLONG GetTimems()
{
	LARGE_INTEGER litmp;
	double dfMinus,dfTime;
	LONGLONG QPart2;
	QueryPerformanceCounter(&litmp);
	QPart2 = litmp.QuadPart; //��ֹ��ʱ
	dfMinus = (double)(QPart2 - m_QPart1);//���������ֵ
	dfTime = dfMinus / m_dfFreq;//��ö�Ӧʱ�䣬��λΪ�� ����Գ�1000000��ȷ��΢�뼶��us��
//	return (DWORD)(dfTime*1000000);//΢��
	return (DWORD)(dfTime*1000);	//����
//	return (DWORD)dfTime;			//��
}

#if !defined(WINCE)
CString GetMyMFCDir()
{
	CString path;
	GetModuleFileName(NULL,path.GetBuffer(512),512);//��ȡ��ǰ���������·��������������
	path.ReleaseBuffer();
	int i=path.ReverseFind('\\');
	path=path.Left(i);
	return path;//����������'\'
}
#endif

BOOL IsFileDirExist(CString dir)
{//�ж��ļ���Ŀ¼�Ƿ����
	WIN32_FIND_DATA fd; 
	HANDLE hd = INVALID_HANDLE_VALUE; 	
	hd=::FindFirstFile(dir,&fd); 
	if(INVALID_HANDLE_VALUE != hd) 
		return TRUE;
	return FALSE;
}
void DoEvents()
{
	static MSG msg; 
	if( ::PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
	{ 
		if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
		{
		}
		::TranslateMessage( &msg ); 
		::DispatchMessage( &msg ); 
	}
}
//************************************************************************
BOOL SaveCfg()
{//�����û�����
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = CFG_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += CFG_FILE_NAME;
#endif
	pf = _wfopen(str, _T("wb"));
	if(pf == NULL)
		return FALSE;
	File_HEAD head;
	INIT_FILE_HEAD(head, FILE_VERSION);
	head.cnt = 1;
	head.size = sizeof(SYS_CFG);
	fwrite(&head, sizeof(File_HEAD), 1, pf);
	fwrite(&g_cfg, sizeof(SYS_CFG), 1, pf);
	fclose(pf);
	return TRUE;
}
BOOL SaveFactCfg()
{//���泧������
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = FACT_CFG_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += FACT_CFG_FILE_NAME;
#endif
	pf = _wfopen(str, _T("wb"));
	if(pf == NULL)
		return FALSE;
	File_HEAD head;
	INIT_FILE_HEAD(head, FILE_VERSION);
	head.cnt = 1;
	head.size = sizeof(FACT_CFG);
	fwrite(&head, sizeof(File_HEAD), 1, pf);
	fwrite(&g_factcfg, sizeof(FACT_CFG), 1, pf);
	fclose(pf);
	return TRUE;
}
BOOL SaveFactPolar()
{//�������뼫��
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = FACT_POLAR_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += FACT_POLAR_FILE_NAME;
#endif
	pf = _wfopen(str, _T("wb"));
	if(pf == NULL)
		return FALSE;
	File_HEAD head;
	INIT_FILE_HEAD(head, FILE_VERSION);
	head.cnt = 1;
	head.size = sizeof(FACT_POLAR);
	fwrite(&head, sizeof(File_HEAD), 1, pf);
	fwrite(&g_polar, sizeof(FACT_POLAR), 1, pf);
	fclose(pf);
	return TRUE;
}
BOOL SaveIOMap()
{//�������뼫��
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = IOMAP_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += IOMAP_FILE_NAME;
#endif
	pf = _wfopen(str, _T("wb"));
	if(pf == NULL)
		return FALSE;
	File_HEAD head;
	INIT_FILE_HEAD(head, FILE_VERSION);
	head.cnt = 1;
	head.size = sizeof(FACT_IOMAP_INFO);
	fwrite(&head, sizeof(File_HEAD), 1, pf);
	fwrite(&g_iomap, sizeof(FACT_IOMAP_INFO), 1, pf);
	fclose(pf);
	return TRUE;
}
BOOL SaveWarn()
{//�������뼫��
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = WARN_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += WARN_FILE_NAME;
#endif
	pf = _wfopen(str, _T("wb"));
	if(pf == NULL)
		return FALSE;
	File_HEAD head;
	INIT_FILE_HEAD(head, FILE_VERSION);
	head.cnt = g_warnNum;
	head.size = sizeof(FACT_WARN);
	fwrite(&head, sizeof(File_HEAD), 1, pf);
	if(g_warnNum > 0)
		fwrite(g_warn, sizeof(FACT_WARN), head.cnt, pf);
	fclose(pf);
	return TRUE;
}


BOOL ReadCfg()
{//��ȡ�û�����
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = CFG_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += CFG_FILE_NAME;
#endif
	pf = _wfopen(str, _T("rb"));
	if(pf == NULL)
		return FALSE;
	int len;
	File_HEAD head;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1 || head.version != FILE_VERSION){
		fclose(pf);
		return FALSE;
	}
	fread(&g_cfg, head.size, head.cnt, pf);
	fclose(pf);
	return TRUE;
}
BOOL ReadFactCfg()
{//��ȡ��������
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = FACT_CFG_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += FACT_CFG_FILE_NAME;
#endif
	pf = _wfopen(str, _T("rb"));
	if(pf == NULL)
		return FALSE;
	int len;
	File_HEAD head;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1 || head.version != FILE_VERSION){
		fclose(pf);
		return FALSE;
	}
	fread(&g_factcfg, head.size, head.cnt, pf);
	fclose(pf);
	return TRUE;
}
BOOL ReadFactPolar()
{//��ȡ���뼫��
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = FACT_POLAR_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += FACT_POLAR_FILE_NAME;
#endif
	pf = _wfopen(str, _T("rb"));
	if(pf == NULL)
		return FALSE;
	int len;
	File_HEAD head;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1 || head.version != FILE_VERSION){
		fclose(pf);
		return FALSE;
	}
	fread(&g_polar, head.size, head.cnt, pf);
	fclose(pf);
	return TRUE;
}
BOOL ReadIOMap()
{//��ȡ���뼫��
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = IOMAP_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += IOMAP_FILE_NAME;
#endif
	pf = _wfopen(str, _T("rb"));
	if(pf == NULL)
		return FALSE;
	int len;
	File_HEAD head;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1 || head.version != FILE_VERSION){
		fclose(pf);
		return FALSE;
	}
	fread(&g_iomap, head.size, head.cnt, pf);
	fclose(pf);
	return TRUE;
}
BOOL ReadWarn()
{//��ȡ���뼫��
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = WARN_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += WARN_FILE_NAME;
#endif
	pf = _wfopen(str, _T("rb"));
	if(pf == NULL)
		return FALSE;
	int len;
	File_HEAD head;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1 || head.version != FILE_VERSION){
		fclose(pf);
		return FALSE;
	}
	g_warnNum = head.cnt;
	if(g_warnNum > 0){
		g_warn = new FACT_WARN[head.cnt];
		fread(g_warn, head.size, head.cnt, pf);
	}
	fclose(pf);
	return TRUE;
}

BOOL ReadCurFile(WCHAR* path)
{//��ȡ�û�����
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = USE_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += USE_FILE_NAME;
#endif
	pf = _wfopen(str, _T("rb"));
	if(pf == NULL)
		return FALSE;
	int len;
	fread(&len, sizeof(int), 1, pf);
	fread(path, sizeof(WCHAR), len, pf);
	fclose(pf);
	path[len] = 0;
	return TRUE;
}
BOOL SaveCurFile(const WCHAR* path)
{//
	FILE* pf;
	CString str;
#if defined(WINCE)
	str = USE_FILE_NAME;
#else
	str = GetMyMFCDir();
	str += USE_FILE_NAME;
#endif
	pf = _wfopen(str, _T("wb"));
	if(pf == NULL)
		return FALSE;
	int len = wcslen(path);
	fwrite(&len, sizeof(int), 1, pf);
	fwrite(path, sizeof(WCHAR), len, pf);
	fclose(pf);
	return TRUE;
}
