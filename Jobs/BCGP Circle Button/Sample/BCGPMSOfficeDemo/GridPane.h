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
// GridPane.h : header file
//

#if !defined(AFX_GRIDPANE_H__DE77AD3F_EA41_454C_8B9D_EB737884B6F8__INCLUDED_)
#define AFX_GRIDPANE_H__DE77AD3F_EA41_454C_8B9D_EB737884B6F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGridPane window

class CGridPane : public CBCGPDockingControlBar
{
// Construction
public:
	CGridPane();

// Attributes
public:
	CBCGPGridCtrl	m_wndGrid;

// Operations
public:
	BOOL AddData (LPCTSTR strPeriod, LPCTSTR strValue, double dDifference, int nYearDelta);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridPane)
	//}}AFX_VIRTUAL

	virtual void OnPressCloseButton ();

// Implementation
public:
	virtual ~CGridPane();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGridPane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPToolBarImages m_imagesArrows;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDPANE_H__DE77AD3F_EA41_454C_8B9D_EB737884B6F8__INCLUDED_)
