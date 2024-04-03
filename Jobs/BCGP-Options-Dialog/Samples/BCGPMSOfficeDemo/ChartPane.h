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
// ChartPane.h : header file
//

#if !defined(AFX_CHARTPANE_H__71E06C9B_9A7B_4A2D_AA1C_F2E76B7DCA9E__INCLUDED_)
#define AFX_CHARTPANE_H__71E06C9B_9A7B_4A2D_AA1C_F2E76B7DCA9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChartPane window

class CChartPane : public CBCGPDockingControlBar
{
// Construction
public:
	CChartPane();

// Attributes
public:
	CBCGPChartCtrl	m_wndChart;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartPane)
	//}}AFX_VIRTUAL

	virtual void OnPressCloseButton();
	virtual BOOL IsTabStop() const { return FALSE; }

// Implementation
public:
	virtual ~CChartPane();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChartPane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTPANE_H__71E06C9B_9A7B_4A2D_AA1C_F2E76B7DCA9E__INCLUDED_)
