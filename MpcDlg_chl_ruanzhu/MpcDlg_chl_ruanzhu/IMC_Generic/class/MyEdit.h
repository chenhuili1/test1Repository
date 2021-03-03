
#ifndef _MY_EDIT_H_
#define _MY_EDIT_H_

#pragma once

	enum{
		EDIT_INT,
		EDIT_FLOAT,
		EDIT_STRING
	};

// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

//	void OnMoveSip();//�ƶ����뷨����ʾ
	void SetFloatFlag(BOOL flag);
	void SetHideFlag(BOOL flag);
	//{{AFX_VIRTUAL(CMyEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
protected:
	BOOL m_isFloat;	//�Ƿ�ת��Ϊ��������
	BOOL m_isHide;	//�Ƿ�ʧȥ���������
	int m_start;
	int m_end;
#if defined(WINCE)
	void OnShowSip(BOOL show);
#endif
	void Change2Float();

	DECLARE_MESSAGE_MAP()
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#endif
