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
#if !defined(AFX_BACKSTAGEPAGESHARE_H__2A4A2BCF_DB95_4047_ACDD_E7769A940797__INCLUDED_)
#define AFX_BACKSTAGEPAGESHARE_H__2A4A2BCF_DB95_4047_ACDD_E7769A940797__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackStagePageShare.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageShare dialog

class CBackStagePageShare : public CBCGPDialog
{
	DECLARE_DYNCREATE(CBackStagePageShare)

// Construction
public:
	CBackStagePageShare(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackStagePageShare)
	enum { IDD = IDD_FORM_SHARE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackStagePageShare)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBackStagePageShare)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGPPropertySheetCtrl	m_wndPropSheet;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGESHARE_H__2A4A2BCF_DB95_4047_ACDD_E7769A940797__INCLUDED_)
