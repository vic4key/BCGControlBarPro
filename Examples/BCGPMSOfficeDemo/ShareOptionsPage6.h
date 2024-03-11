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
#if !defined(AFX_OPTIONSPAGE6_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_)
#define AFX_OPTIONSPAGE6_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPage6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage6 dialog

class CShareOptionsPage6 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CShareOptionsPage6)

// Construction
public:
	CShareOptionsPage6();
	~CShareOptionsPage6();

// Dialog Data
	//{{AFX_DATA(CShareOptionsPage6)
	enum { IDD = IDD_SHARE_PAGE6 };
	CBCGPButton m_btnCreatePDF;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CShareOptionsPage6)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CShareOptionsPage6)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSPAGE6_H__96F3EFAE_4A0A_4875_9000_D4CF5572662F__INCLUDED_)
