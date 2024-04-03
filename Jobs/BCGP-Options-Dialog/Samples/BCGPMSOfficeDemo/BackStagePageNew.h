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
#if !defined(AFX_BACKSTAGEPAGENEW_H__7F83711D_7337_4DEB_B4F8_6EF7E63C547C__INCLUDED_)
#define AFX_BACKSTAGEPAGENEW_H__7F83711D_7337_4DEB_B4F8_6EF7E63C547C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackStagePageNew.h : header file
//

class CNewRibbonGalleryCtrl : public CBCGPRibbonGalleryCtrl
{
	friend class CBackStagePageNew;

//public:
	virtual void OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* pIcon, COLORREF clrText);

	CBCGPToolBarImages	m_Icons;
};

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageNew dialog

class CBackStagePageNew : public CBCGPDialog
{
	DECLARE_DYNCREATE(CBackStagePageNew)

// Construction
public:
	CBackStagePageNew(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackStagePageNew)
	enum { IDD = IDD_FORM_NEW };
	CStatic	m_wndPreview;
	CStatic	m_wndGalleryLocation;
	CBCGPButton	m_btnCreate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackStagePageNew)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnDraw(CDC* pDC);

	// Generated message map functions
	//{{AFX_MSG(CBackStagePageNew)
	virtual BOOL OnInitDialog();
	afx_msg void OnCreate();
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnHighlightRibbonListItem (WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	CNewRibbonGalleryCtrl	m_wndGallery;
	int						m_nSelectedTemplate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGENEW_H__7F83711D_7337_4DEB_B4F8_6EF7E63C547C__INCLUDED_)
