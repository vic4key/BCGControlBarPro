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
// BCGPMSOfficeDemoView.h : interface of the CBCGPMSOfficeDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPMSOFFICEDEMOVIEW_H__FF480114_EF95_4D26_B3AB_9BFAA19B307D__INCLUDED_)
#define AFX_BCGPMSOFFICEDEMOVIEW_H__FF480114_EF95_4D26_B3AB_9BFAA19B307D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPMSOfficeDemoCntrItem;
struct CCharFormat;

class CBCGPMSOfficeDemoView : public CRichEditView
{
protected: // create from serialization only
	CBCGPMSOfficeDemoView();
	DECLARE_DYNCREATE(CBCGPMSOfficeDemoView)

// Attributes
public:
	CBCGPMSOfficeDemoDoc* GetDocument();
	static BOOL m_bForceReloadBmps;

// Operations
public:
	void ScrollTo (int nPos);
	void OnChangeVisualTheme();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSOfficeDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	virtual void SyncFont ();

// Implementation
public:
	virtual ~CBCGPMSOfficeDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMSOfficeDemoView)
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFontDialog();
	afx_msg void OnParagraphDialog();
	afx_msg void OnStyleDialog();
	afx_msg void OnPagesetupDialog();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditUndo();
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditReplace(CCmdUI* pCmdUI);
	afx_msg void OnPagelayoutIndentLeft();
	afx_msg void OnPagelayoutIndentRight();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnEditPaste();
	afx_msg void OnInsertObject();
	//}}AFX_MSG
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFontColor();
	afx_msg void OnFontname();
	afx_msg void OnFontsize();
	afx_msg void OnEditChange();
	afx_msg void OnInsertPicture();
	afx_msg void OnInsertChart();
	afx_msg void OnInsertTable();
	afx_msg void OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdatePrintLayout(CCmdUI* pCmdUI);
	afx_msg void OnIndentLeft();
	afx_msg void OnIndentRight();
	afx_msg void OnSpaceAfter();
	afx_msg void OnSpaceBefore();
	afx_msg void OnViewRuler();
	afx_msg void OnViewGridLines();
	afx_msg void OnViewProps();
	afx_msg void OnViewDocMap();
	afx_msg void OnUpdateViewRuler(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewGridLines(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewProps(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDocMap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewThumb(CCmdUI* pCmdUI);
	afx_msg void OnInsertBulletFromPalette();
	afx_msg void OnInsertNumberFromPalette();
	afx_msg void OnInsertMultilevelFromPalette();
	afx_msg void OnCharStrikeThrough();
	afx_msg void OnUpdateCharStrikeThrough(CCmdUI* pCmdUI);
	afx_msg void OnInsertTableGallery();
	afx_msg void OnInsertShape ();
	afx_msg void OnQuickStyle ();
	afx_msg void OnPageLayoutTheme ();
	afx_msg void OnENVScroll();
	afx_msg void OnENRequesteResize(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFontGrow();
	afx_msg void OnFontShrink();
	afx_msg void OnZoomSlider();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnGetObject (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	BOOL ShowContextMenu (CPoint pt);

	void GetDefaultFont(CCharFormat& cf);
	BOOL InsertBitmap (UINT uiBmpResID);

	BOOL LoadStartPage();
	void InitFloaty (CBCGPRibbonFloaty* pFloaty);

protected:
	BOOL m_bIsEndOfPrint;

	BOOL m_bViewRuler;
	BOOL m_bViewGridLines;
	BOOL m_bViewProps;
	BOOL m_bViewDocMap;
	BOOL m_bViewThumb;

	CPoint	m_ptMouseDown;
	BOOL	m_bIsFirstLoad;

	BOOL	m_bIsDarkTheme;
	COLORREF m_clrBackground;
};

#ifndef _DEBUG  // debug version in BCGPMSOfficeDemoView.cpp
inline CBCGPMSOfficeDemoDoc* CBCGPMSOfficeDemoView::GetDocument()
   { return (CBCGPMSOfficeDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSOFFICEDEMOVIEW_H__FF480114_EF95_4D26_B3AB_9BFAA19B307D__INCLUDED_)
