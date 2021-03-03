// stdafx.cpp : 只包括标准包含文件的源文件
// IMC_Generic.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

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
	BOOL g_isSipShow;//是否已经显示输入法
#endif

	BOOL g_isTestV;

	BOOL g_isUseHWok;	//编程中是否使用手轮确定按钮控制

//生成一个字体
CFont* MyGetFonts(int height, WCHAR *name, int width)
{
	CFont *fn = new CFont;
	fn->CreateFont(height,            // nHeight 字体的高度
		0,           // nWidth 字体的宽度。
		0,           // nEscapement 字体的倾斜角
		0,           // nOrientation 字体的倾斜角
		width,//FW_BOLD,     // nWeight 字体的粗细。
		FALSE,        // bItalic 字体是否斜体。
		FALSE,       // bUnderline 字体是否有下划线。
		0,           // cStrikeOut 字体是否有删除线
		GB2312_CHARSET,              // nCharSet 字体使用的字符集。
		OUT_DEFAULT_PRECIS,        // nOutPrecision 如何选择合适的字体。
		CLIP_DEFAULT_PRECIS,       // nClipPrecision 用来确定裁剪的精度。
		DEFAULT_QUALITY,           // nQuality 怎么样跟选择的字体相符合。
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 间距标志和属性标志
		(name == NULL) ? _T("隶书") : name); //_T("Arial"));             // lpszFac字体的名称。
	return fn;
}
	
	
LONGLONG m_QPart1;
double m_dfFreq;
void StartTimes()
{
	LARGE_INTEGER litmp;
	//获得计时器的时钟频率
	QueryPerformanceFrequency(&litmp);
	m_dfFreq = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);
	m_QPart1 = litmp.QuadPart; //开始计时
}

DWORD GetTimes()
{
	LARGE_INTEGER litmp;
	double dfMinus,dfTime;
	LONGLONG QPart2;
	QueryPerformanceCounter(&litmp);
	QPart2 = litmp.QuadPart; //终止计时
	dfMinus = (double)(QPart2 - m_QPart1);//计算计数器值
	dfTime = dfMinus / m_dfFreq;//获得对应时间，单位为秒 你可以乘1000000精确到微秒级（us）
//	return (DWORD)(dfTime*1000000);//微秒
//	return (DWORD)(dfTime*1000);	//毫秒
	return (DWORD)dfTime;			//秒
}

LONGLONG GetTimems()
{
	LARGE_INTEGER litmp;
	double dfMinus,dfTime;
	LONGLONG QPart2;
	QueryPerformanceCounter(&litmp);
	QPart2 = litmp.QuadPart; //终止计时
	dfMinus = (double)(QPart2 - m_QPart1);//计算计数器值
	dfTime = dfMinus / m_dfFreq;//获得对应时间，单位为秒 你可以乘1000000精确到微秒级（us）
//	return (DWORD)(dfTime*1000000);//微秒
	return (DWORD)(dfTime*1000);	//毫秒
//	return (DWORD)dfTime;			//秒
}

#if !defined(WINCE)
CString GetMyMFCDir()
{
	CString path;
	GetModuleFileName(NULL,path.GetBuffer(512),512);//获取当前程序的完整路径，包括程序名
	path.ReleaseBuffer();
	int i=path.ReverseFind('\\');
	path=path.Left(i);
	return path;//不包括最后的'\'
}
#endif

BOOL IsFileDirExist(CString dir)
{//判断文件或目录是否存在
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
{//保存用户设置
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
{//保存厂家设置
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
{//保存输入极性
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
{//保存输入极性
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
{//保存输入极性
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
{//读取用户设置
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
{//读取厂家设置
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
{//读取输入极性
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
{//读取输入极性
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
{//读取输入极性
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
{//读取用户设置
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
