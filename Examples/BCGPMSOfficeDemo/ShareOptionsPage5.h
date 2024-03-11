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
#if !defined(AFX_OPTIONSPAGE5_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_)
#define AFX_OPTIONSPAGE5_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPage5.h : header file
//

class CPage5RibbonGalleryCtrl : public CBCGPRibbonGalleryCtrl
{
	friend class CBackStagePageNew;

public:
	virtual void OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* pIcon, COLORREF clrText);

	CBCGPToolBarImages	m_Icons;
};

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage5 dialog

class CShareOptionsPage5 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CShareOptionsPage5)

// Construction
public:
	CShareOptionsPage5();
	~CShareOptionsPage5();

// Dialog Data
	//{{AFX_DATA(CShareOptionsPage5)
	enum { IDD = IDD_SHARE_PAGE5 };
	CStatic	m_wndGalleryLocation3;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CShareOptionsPage5)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CShareOptionsPage5)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CPage5RibbonGalleryCtrl m_wndGallery3;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSPAGE5_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_)
