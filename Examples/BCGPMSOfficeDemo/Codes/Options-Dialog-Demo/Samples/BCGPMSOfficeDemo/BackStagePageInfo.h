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
#if !defined(AFX_BACKSTAGEPAGEINFO_H__EF98B28A_8E86_412F_9E4B_2B7AA2F5A5CB__INCLUDED_)
#define AFX_BACKSTAGEPAGEINFO_H__EF98B28A_8E86_412F_9E4B_2B7AA2F5A5CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackStagePageInfo.h : header file
//

class CGalleryMenuButton : public CBCGPRibbonComboGalleryCtrl
{
	virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState)
	{
		CBCGPMenuButton::OnDraw(pDC, rect, uiState);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageInfo dialog

class CBackStagePageInfo : public CBCGPDialog
{
	DECLARE_DYNCREATE(CBackStagePageInfo)

// Construction
public:
	CBackStagePageInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackStagePageInfo)
	enum { IDD = IDD_FORM_INFO };
	CBCGPButton	m_btnPreview;
	CGalleryMenuButton	m_btnCheckForIssues;
	CBCGPButton	m_btnManageVersions;
	CBCGPButton	m_btnProtect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackStagePageInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnDraw(CDC* pDC);

	// Generated message map functions
	//{{AFX_MSG(CBackStagePageInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnPreview();
	afx_msg void OnCheckForIssue();
	//}}AFX_MSG
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	CString	m_strDocName;
	CString	m_strPath;

	void PreparePreviewBitmap();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGEINFO_H__EF98B28A_8E86_412F_9E4B_2B7AA2F5A5CB__INCLUDED_)
