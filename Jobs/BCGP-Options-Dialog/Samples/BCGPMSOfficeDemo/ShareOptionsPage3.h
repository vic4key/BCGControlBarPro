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
#if !defined(AFX_OPTIONSPAGE3_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_)
#define AFX_OPTIONSPAGE3_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPage3.h : header file
//

//#include "BackStagePageNew.h"
class CPage3RibbonGalleryCtrl : public CBCGPRibbonGalleryCtrl
{
	friend class CBackStagePageNew;

//public:
	virtual void OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* pIcon, COLORREF clrText);

	CBCGPToolBarImages	m_Icons;
};

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage3 dialog

class CShareOptionsPage3 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CShareOptionsPage3)

// Construction
public:
	CShareOptionsPage3();
	~CShareOptionsPage3();

// Dialog Data
	//{{AFX_DATA(CShareOptionsPage3)
	enum { IDD = IDD_SHARE_PAGE3 };
	CBCGPButton	m_btnSaveAs;
	CStatic	m_wndGalleryLocation2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CShareOptionsPage3)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CShareOptionsPage3)
	afx_msg void OnSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
	CPage3RibbonGalleryCtrl m_wndGallery2;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSPAGE3_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_)
