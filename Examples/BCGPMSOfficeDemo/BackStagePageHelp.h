#if !defined(AFX_BACKSTAGEPAGEHELP_H__50C3B210_9136_49C0_B9BE_C7196CBF6145__INCLUDED_)
#define AFX_BACKSTAGEPAGEHELP_H__50C3B210_9136_49C0_B9BE_C7196CBF6145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2017 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BackStagePageHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageHelp dialog

class CBackStageListBox : public CBCGPListBox
{
	DECLARE_DYNAMIC(CBackStageListBox)

// Construction
public:
	CBackStageListBox();

	virtual void OnClickItem(int nClickedItem);
	virtual BOOL OnReturnKey();

	virtual BOOL IsBackstagePageSelector() const
	{
		return TRUE;
	}
};

class CBackStagePageHelp : public CBCGPDialog
{
	DECLARE_DYNCREATE(CBackStagePageHelp)

// Construction
public:
	CBackStagePageHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackStagePageHelp)
	enum { IDD = IDD_FORM_HELP };
	CBCGPURLLinkButton	m_wndURL;
	CBCGPURLLinkButton	m_wndMail;
	CStatic	m_wndLogo;
	CStatic	m_wndCaption;
	CBackStageListBox m_wndList;
	CString	m_strVersion;
	CString	m_strYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackStagePageHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ResetList();
	void OnDraw(CDC* pDC);

	// Generated message map functions
	//{{AFX_MSG(CBackStagePageHelp)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPToolBarImages		m_Logo;
	int						m_nListMode;	// 0 - compact, 1 - small, 2 - regular
	int						m_nInitialListWidth;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGEHELP_H__50C3B210_9136_49C0_B9BE_C7196CBF6145__INCLUDED_)
