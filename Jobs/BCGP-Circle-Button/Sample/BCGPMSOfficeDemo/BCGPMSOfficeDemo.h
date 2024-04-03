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
// BCGPMSOfficeDemo.h : main header file for the BCGPMSOFFICEDEMO application
//

#if !defined(AFX_BCGPMSOFFICEDEMO_H__DA1F57AE_43B2_4716_86A5_3F386644D3D2__INCLUDED_)
#define AFX_BCGPMSOFFICEDEMO_H__DA1F57AE_43B2_4716_86A5_3F386644D3D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoApp:
// See BCGPMSOfficeDemo.cpp for the implementation of this class
//

class CBCGPMSOfficeDemoApp : public CBCGPWinApp
{
public:
	CBCGPMSOfficeDemoApp();

	BOOL						m_bShowFloaty;
	BOOL						m_bShowToolTips;
	BOOL						m_bShowToolTipDescr;
	BOOL						m_bShowKeyTips;
	BOOL						m_bDontShowPaneCloseMessage;
	BOOL						m_bIsRTL;

	CList<COLORREF, COLORREF>	m_lstCustomColors;
	COLORREF					m_clrCustomDef;
	COLORREF					m_clrCustom;

	CList<COLORREF, COLORREF>	m_lstAppButtonColors;
	COLORREF					m_clrAppButton;
	int							m_nAccentColorIndex;
	int							m_nBackgroundImage;

	CBCGPPageTransitionManager::BCGPPageTransitionEffect	m_PageTransitionEffect;

// Overrides
	virtual void OnBeforeChangeVisualTheme(CBCGPAppOptions& appOptions, CWnd* pMainWnd);
	virtual void OnAfterChangeVisualTheme(CWnd* pMainWnd);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSOfficeDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPMSOfficeDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPMSOfficeDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSOFFICEDEMO_H__DA1F57AE_43B2_4716_86A5_3F386644D3D2__INCLUDED_)
