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
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B5F5B178_AB60_4230_BCAE_558139F09CA5__INCLUDED_)
#define AFX_MAINFRM_H__B5F5B178_AB60_4230_BCAE_558139F09CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFrameWnd CBCGPFrameWnd

#include "ClipboardPane.h"
#include "GridPane.h"
#include "ChartPane.h"
#include "RibbonListButton.h"
#include "ShareOptionsPage1.h"
#include "ShareOptionsPage2.h"
#include "ShareOptionsPage3.h"
#include "ShareOptionsPage4.h"
#include "ShareOptionsPage5.h"
#include "ShareOptionsPage6.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CBCGPRibbonBar* GetRibbonBar ()
	{
		return &m_wndRibbonBar;
	}

	CBCGPRibbonStatusBar* GetRibbonStatusBar ()
	{
		return &m_wndStatusBar;
	}

	CScrollBar* GetScrollBar ()
	{
		return &m_wndScrollBar;
	}

	CBitmap& GetAppPreview() { return m_bmpAppPreview; }

// Operations
public:
	CBCGPToolBarImages* GetTooltipImage (UINT uiID);
	
	void SetRibbonContextCategory (UINT uiCategoryID);
	void ActivateRibbonContextCategory (UINT uiCategoryID);

	void OnChangeLayout (CWnd* pWnd = NULL, BOOL bNoLoopOverPopup = FALSE);
	void UpdateMainButtonColor (COLORREF clr);

	void OnBeforeChangeVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME theme);
	void OnAfterChangeVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME theme);

protected:
	void InitPastePalette(CBCGPRibbonPaletteButton* pPalette);
	void InitBulletPalette (CBCGPRibbonPaletteButton* pPalette);
	void InitNumberingPalette (CBCGPRibbonPaletteButton* pPalette);
	void InitMultilevelPalette (CBCGPRibbonPaletteButton* pPalette);
	void InitPositionPalette (CBCGPRibbonPaletteButton* pPalette);
	
	void SetBackgroundImage(CBCGPWinApp::BCGP_VISUAL_THEME theme, BOOL bIsDarkTheme);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	virtual void AdjustClientArea ();
	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPRibbonBar			m_wndRibbonBar;	// Ribbon control bar
	CClipboardPane			m_wndClipboardPane;
	CChartPane				m_wndChartPane;
	CGridPane				m_wndGridPane;
	CBCGPRibbonStatusBar	m_wndStatusBar;
	CBCGPCaptionBar			m_wndMessageBar;

	CBCGPToolBarImages		m_PanelImages;	// Ribbon panel images
											// (appear when pane is collapsed)

	CMap<UINT,UINT,CBCGPToolBarImages*,CBCGPToolBarImages*>
							m_TooltipImages;

	void CreateDocumentColors ();
	void CreateStyleList ();
	void CreateThemeList ();

	void ShowProgress (BOOL bShow = TRUE);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnWriteClipboard();
	afx_msg void OnUpdateWriteClipboard(CCmdUI* pCmdUI);
	afx_msg void OnViewRtl();
	afx_msg void OnUpdateViewRtl(CCmdUI* pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnViewApplookCustomColor();
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	afx_msg void OnRefresh();
	afx_msg void OnSpell();
	afx_msg void OnUpdateRefresh(CCmdUI* pCmdUI);
	afx_msg void OnToolsOptions ();
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg void OnLink();
	afx_msg LRESULT OnHighlightRibbonListItem (WPARAM wp, LPARAM lp);
	afx_msg void OnViewMessageBar();
	afx_msg void OnUpdateViewMessageBar(CCmdUI* pCmdUI);
	afx_msg void OnViewChartPane();
	afx_msg void OnUpdateViewChartPane(CCmdUI* pCmdUI);
	afx_msg void OnViewGridPane();
	afx_msg void OnUpdateViewGridPane(CCmdUI* pCmdUI);
	afx_msg LRESULT OnShowRibbonItemMenu(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnBeforeShowRibbonBackstageView(WPARAM wp, LPARAM lp);
	afx_msg void OnDummy(UINT id);	
	afx_msg void OnZoom();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnClipboardPasteAll();
	afx_msg void OnClipboardClearAll();
	afx_msg void OnClipboardOption1();
	afx_msg void OnClipboardOption2();
	afx_msg LRESULT OnCustomizeGalleryContextMenu(WPARAM wp, LPARAM lp);
	afx_msg void OnCopyColor();
	afx_msg LRESULT OnClickCaptionbarHyperlink(WPARAM wp, LPARAM lp);
	afx_msg void OnViewFullScreen();
	afx_msg void OnInputMode();
	afx_msg void OnInputMouse();
	afx_msg void OnInputTouch();
	afx_msg void OnUpdateInputMouse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInputTouch(CCmdUI* pCmdUI);
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnGetRibbonCommandsMenuCustomItems(WPARAM wp, LPARAM lp);
	afx_msg void OnSearchHelp();
	DECLARE_MESSAGE_MAP()

	BOOL CreateRibbonBar ();
	BOOL CreateStatusBar ();
	BOOL CreateMessageBar ();

	void ShowOptions (int nPage);
	void OnDrawClientArea(CDC* pDC);

	CBCGPScrollBar	m_wndScrollBar;

	CRect		m_rectFill;
    CBitmap		m_MemBitmap;
	CRect		m_rectSizing;

	int			m_nProgressValue;
	BOOL		m_bInfiniteProgressMode;

	// Document colors for demo:
	CList<COLORREF,COLORREF> m_lstMainColors;
	CList<COLORREF,COLORREF> m_lstAdditionalColors;
	CList<COLORREF,COLORREF> m_lstStandardColors;

	// Theme names for demo:
	CStringArray	m_arStyles;
	CStringArray	m_arThemes;
	CStringArray	m_arColors;
	CStringArray	m_arEffects;
	CStringArray	m_arStyleSets;

	CBCGPRibbonColorButton* m_pLookColor;

	COLORREF		m_clrHighlighted;

	CShareOptionsPage1		m_Page1;
	CShareOptionsPage2		m_Page2;
	CShareOptionsPage3		m_Page3;
	CShareOptionsPage4		m_Page4;
	CShareOptionsPage5		m_Page5;
	CShareOptionsPage6		m_Page6;

	CBitmap					m_bmpAppPreview;

	BOOL					m_bIsDarkTheme;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B5F5B178_AB60_4230_BCAE_558139F09CA5__INCLUDED_)
