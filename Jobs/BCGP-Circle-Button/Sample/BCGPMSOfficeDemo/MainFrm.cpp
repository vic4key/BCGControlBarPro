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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "OptionsPage.h"
#include "ResourcePage.h"
#include "MainFrm.h"
#include "RibbonTableButton.h"
#include "BCGPMSOfficeDemoDoc.h"
#include "BCGPMSOfficeDemoView.h"
#include "BackStagePageInfo.h"
#include "BackStagePageShare.h"
#include "BackStagePageNew.h"
#include "BackStagePageHelp.h"

#if _MSC_VER < 1500
	#pragma warning (disable : 4706)

	#ifndef _BCGCBPRO_STATIC_
		#ifdef _AFXDLL
			#define COMPILE_MULTIMON_STUBS
		#endif // _AFXDLL
	#endif

	#include "multimon.h"

	#pragma warning (default : 4706)
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int IdStartProgressTimer = 1;
const int IdShowProgressTimer = 2;

const COLORREF clrWatermarkBase = RGB(0, 0, 192);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_WRITE_CLIPBOARD, OnWriteClipboard)
	ON_UPDATE_COMMAND_UI(ID_WRITE_CLIPBOARD, OnUpdateWriteClipboard)
	ON_COMMAND(ID_VIEW_RTL, OnViewRtl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RTL, OnUpdateViewRtl)
	ON_WM_VSCROLL()
	ON_COMMAND(ID_VIEW_APPLOOK_2007_5, OnViewApplookCustomColor)
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
	ON_COMMAND(ID_STATUSBAR_FULL_SCREEN_READING, OnViewFullScreen)
	ON_COMMAND(ID_STATUSBAR_ZOOM, OnZoom)
	ON_COMMAND(ID_STATUSBAR_REFRESH, OnRefresh)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_REFRESH, OnUpdateRefresh)
	ON_COMMAND(ID_STATUSBAR_SPELL, OnSpell)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_COMMAND(ID_STATUSBAR_LINK, OnLink)
	ON_REGISTERED_MESSAGE(BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, OnHighlightRibbonListItem)
	ON_COMMAND(ID_VIEW_MESSAGEBAR, OnViewMessageBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MESSAGEBAR, OnUpdateViewMessageBar)
	ON_COMMAND(ID_VIEW_CHART_PANE, OnViewChartPane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CHART_PANE, OnUpdateViewChartPane)
	ON_COMMAND(ID_VIEW_GRID_PANE, OnViewGridPane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID_PANE, OnUpdateViewGridPane)
	ON_REGISTERED_MESSAGE(BCGM_ON_BEFORE_SHOW_RIBBON_ITEM_MENU, OnShowRibbonItemMenu)
	ON_REGISTERED_MESSAGE(BCGM_ON_BEFORE_RIBBON_BACKSTAGE_VIEW, OnBeforeShowRibbonBackstageView)
	ON_COMMAND(ID_SEARCH_COMMANDS_HELP, OnSearchHelp)
	ON_COMMAND_RANGE(ID_PAGELAYOUT_EFFECTS_ACADEMIC, ID_PAGELAYOUT_THEMES_MORETHEMES, OnDummy)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(IDC_PASTE_ALL, OnClipboardPasteAll)
	ON_COMMAND(IDC_CLEAR_ALL, OnClipboardClearAll)
	ON_COMMAND(IDC_OPTION1, OnClipboardOption1)
	ON_COMMAND(IDC_OPTION2, OnClipboardOption2)
	ON_REGISTERED_MESSAGE(BCGM_ON_BEFORE_SHOW_PALETTE_CONTEXTMENU, OnCustomizeGalleryContextMenu)
	ON_COMMAND(ID_COPY_COLOR, OnCopyColor)
	ON_REGISTERED_MESSAGE(BCGM_ON_CLICK_CAPTIONBAR_HYPERLINK, OnClickCaptionbarHyperlink)
	ON_COMMAND(ID_INPUT_MODE, OnInputMode)
	ON_COMMAND(ID_INPUT_MOUSE, OnInputMouse)
	ON_COMMAND(ID_INPUT_TOUCH, OnInputTouch)
	ON_UPDATE_COMMAND_UI(ID_INPUT_MOUSE, OnUpdateInputMouse)
	ON_UPDATE_COMMAND_UI(ID_INPUT_TOUCH, OnUpdateInputTouch)
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
	ON_REGISTERED_MESSAGE(BCGM_ON_GET_RIBBON_COMMANDS_MENU_CUSTOM_ITEMS, OnGetRibbonCommandsMenuCustomItems)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_rectFill.SetRectEmpty ();
	m_rectSizing.SetRectEmpty ();

	m_nProgressValue = -1;
	m_bInfiniteProgressMode = TRUE;

	CreateDocumentColors ();
	CreateStyleList ();
	CreateThemeList ();

	CBCGPPopupMenu::SetAnimationType (CBCGPPopupMenu::SYSTEM_DEFAULT_ANIMATION);

	m_pLookColor = NULL;

	m_clrHighlighted = (COLORREF)-1;

	theApp.m_clrAppButton = (COLORREF)theApp.GetInt (_T("AppButtonColor"), (COLORREF)-1);
	m_wndRibbonBar.SetGrayDisabledImages();

	m_bIsDarkTheme = (theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK && !globalData.m_bIsWhiteHighContrast) || globalData.m_bIsBlackHighContrast;
}

CMainFrame::~CMainFrame()
{
	for (POSITION pos = m_TooltipImages.GetStartPosition (); pos != NULL;)
	{
		CBCGPToolBarImages* pBmp = NULL;
		UINT uiID;

		m_TooltipImages.GetNextAssoc (pos, uiID, pBmp);
		delete pBmp;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create scrollbar:
	m_wndScrollBar.Create (WS_CHILD | WS_VISIBLE | SBS_VERT, CRect (0, 0, 0, 0), this, 1);
	m_wndScrollBar.SetVisualStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER_FRAME);

	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	};

	if (!CreateStatusBar ())
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!CreateMessageBar ())
	{
		TRACE0("Failed to create message bar\n");
	}

	// Create docking panes:
	if (!m_wndClipboardPane.Create(_T("Clipboard"), this, TRUE, IDD_CLIPBOARD, 
		WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_BCGP_CLOSE | CBRS_FLOAT_MULTI,
		ID_VIEW_TASK_PANE))
	{
		TRACE0("Failed to create clipboard pane\n");
		return -1;
	}

	const CSize sizePane = globalUtils.ScaleByDPI(CSize(320, 250));

	if (!m_wndChartPane.Create (_T("Product Sales"), this, CRect (0, 0, sizePane.cx, sizePane.cy),
		TRUE, 
		ID_VIEW_CHART_PANE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create chart pane\n");
		return -1;		// fail to create
	}

	if (!m_wndGridPane.Create (_T("Sales Report"), this, CRect (0, 0, sizePane.cx, sizePane.cy),
		TRUE, 
		ID_VIEW_GRID_PANE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create chart pane\n");
		return -1;		// fail to create
	}

	m_wndClipboardPane.EnableDocking(CBRS_ALIGN_ANY);
	m_wndChartPane.EnableDocking(CBRS_ALIGN_ANY);
	m_wndGridPane.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndClipboardPane);
	DockControlBar(&m_wndChartPane);
	m_wndGridPane.DockToWindow (&m_wndChartPane, CBRS_ALIGN_TOP);

	EnableDocking (CBRS_ALIGN_ANY);

	EnableFullScreenMode (ID_VIEW_FULLSCREEN);
	EnableFullScreenMainMenu (FALSE);

	OnChangeLayout ();

	// Show progress bar after the short delay:
	SetTimer (IdStartProgressTimer, 500, NULL);

	// Start animation:
	CBCGPRibbonStatusBarPane* pPane = DYNAMIC_DOWNCAST (
		CBCGPRibbonStatusBarPane,
		m_wndStatusBar.FindElement (ID_STATUSBAR_SPELL));

	if (pPane != NULL)
	{
		pPane->StartAnimation (500 /* Frame delay*/, 5000 /* Duration */);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CBCGPFrameWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}

	WNDCLASS wndcls;

	if (GetClassInfo (AfxGetInstanceHandle (), cs.lpszClass, &wndcls))
	{
		HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_MAINFRAME), RT_GROUP_ICON);
		HICON hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));

		// register a very similar WNDCLASS but without CS_HREDRAW and CS_VREDRAW styles:
		cs.lpszClass = AfxRegisterWndClass (CS_DBLCLKS, wndcls.hCursor, wndcls.hbrBackground, hIcon);
	}

	cs.style |= WS_CLIPCHILDREN;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnBeforeChangeVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME theme)
{
	if (IsPrintPreview())
	{
		ClosePrintPreview();
	}

	CBCGPVisualManagerVS2012::m_bThinSlider = TRUE;

	BOOL bIsDarkTheme = (theme == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK && !globalData.m_bIsWhiteHighContrast) || globalData.m_bIsBlackHighContrast;

	BOOL bIsOffice2010Look = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLUE && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_SILVER);
	BOOL bIsOffice2013Look = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY);
	BOOL bIsOffice2016Look = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK);

	m_wndRibbonBar.EnableCommandSearch(bIsOffice2016Look, _T("Tell me what you want to do..."), -1, _T("q"),
		_T("Tell Me (Alt+Q)"), _T("Just start typing here to bring features to your fingertips and get help"));

	CBCGPVisualManager2007::SetCustomColor ((COLORREF)-1);

	m_wndMessageBar.m_clrBarBackground = (COLORREF)-1;
	m_wndMessageBar.m_clrBarText = (COLORREF)-1;

	UpdateMainButtonColor ((COLORREF)-1);

	CBCGPRibbonMainButton* pMainButton = m_wndRibbonBar.GetMainButton();
	ASSERT_VALID(pMainButton);

	m_wndRibbonBar.SetBackstageMode(bIsOffice2010Look || bIsOffice2013Look || bIsOffice2016Look, !bIsOffice2013Look && !bIsOffice2016Look);
	m_wndRibbonBar.EnableBackstagePageCaptions(bIsOffice2013Look || bIsOffice2016Look);
	
	if (theme == CBCGPWinApp::BCGP_VISUAL_THEME_CUSTOM)
	{
		m_pLookColor->SetColor (theApp.m_clrCustom);

		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		CBCGPVisualManager2007::SetCustomColor(theApp.m_clrCustom == (COLORREF)-1 ? theApp.m_clrCustomDef : theApp.m_clrCustom);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));

		theApp.WriteInt (_T("LookColor"), (int)theApp.m_clrCustom);
	}
	else if (bIsOffice2010Look)
	{
		m_wndMessageBar.m_clrBarBackground = RGB(255, 236, 130);
		m_wndMessageBar.m_clrBarText = RGB(0, 0, 0);

		UpdateMainButtonColor (theApp.m_clrAppButton);

		theApp.WriteInt (_T("AppButtonColor"), (int)theApp.m_clrAppButton);
	}
	else if (bIsOffice2013Look || bIsOffice2016Look)
	{
		CBCGPVisualManager2013::SetAccentColor((CBCGPVisualManager2013::AccentColor)theApp.m_nAccentColorIndex);
		
		m_wndMessageBar.m_clrBarBackground = 
			bIsDarkTheme ? RGB(75, 75, 75) : 
			theme == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY ? RGB(255, 223, 132) : 
			RGB(252, 247, 183);

		m_wndMessageBar.m_clrBarText = bIsDarkTheme ? RGB(190, 190, 190) : RGB(0, 0, 0);

		SetBackgroundImage(theme, bIsDarkTheme);

		theApp.WriteInt (_T("AccentColorIndex"), theApp.m_nAccentColorIndex);
	}

	if (m_MemBitmap.GetSafeHandle () != NULL)
	{
		m_MemBitmap.DeleteObject ();
	}

	if (bIsDarkTheme != m_bIsDarkTheme)
	{
		UINT nGalleriesID[] = { ID_WRITE_QUICKSTYLES, ID_PARA_BULLETS, ID_PARA_NUMBERING, ID_PARA_MULTILEVEL, ID_INSERT_SHAPES, ID_PAGELAYOUT_FONTS, ID_STYLECHANGE_FONTS };

		for (int j = 0; j < sizeof(nGalleriesID) / sizeof(UINT); j++)
		{
			CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> arGalleries;
			m_wndRibbonBar.GetElementsByID(nGalleriesID[j], arGalleries);

			for (int i = 0; i < (int)arGalleries.GetSize(); i++)
			{
				CBCGPRibbonPaletteButton* pGallery = DYNAMIC_DOWNCAST(CBCGPRibbonPaletteButton, arGalleries[i]);
				if (pGallery != NULL)
				{
					ASSERT_VALID(pGallery);
					pGallery->GetImages().InvertColors();
				}
			}
		}

		m_bIsDarkTheme = bIsDarkTheme;
	}

	for (int i = 0; i < m_wndStatusBar.GetExCount(); i++)
	{
		CBCGPRibbonButtonsGroup* pGroup = DYNAMIC_DOWNCAST(CBCGPRibbonButtonsGroup, m_wndStatusBar.GetExElement(i));
		if (pGroup != NULL)
		{
			BOOL bSimpleIcons = (bIsOffice2013Look || bIsOffice2016Look) && !globalData.IsHighContastMode();
			if (theme == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL)
			{
				bSimpleIcons = FALSE;
			}

			pGroup->GetImages().Clear();

			pGroup->GetImages().SetImageSize(bSimpleIcons ? CSize(16, 16) : CSize(14, 14));
			pGroup->GetImages().LoadStr(bSimpleIcons ? MAKEINTRESOURCE(IDB_LAYOUT_METRO) : MAKEINTRESOURCE(IDB_LAYOUT));

			globalUtils.ScaleByDPI(pGroup->GetImages());
		}
	}

	m_wndRibbonBar.SetImagesLuminosity(m_bIsDarkTheme ? 1.25 : 1.0);
}

void CMainFrame::OnAfterChangeVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME theme)
{
	// Update backstage view:
	UINT nWaterMarkResID = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK) ? 0 : IDB_BS_WATERMARK;

	CBCGPRibbonBackstageViewPanel* pBackstagePanel = m_wndRibbonBar.GetBackstageViewPanel();
	if (pBackstagePanel != NULL)
	{
		ASSERT_VALID(pBackstagePanel);

		int nViewsCount = pBackstagePanel->GetFormsCount();

		for (int i = 0; i < nViewsCount; i++)
		{
			CBCGPRibbonBackstageViewItemForm* pForm = pBackstagePanel->GetForm(i);
			ASSERT_VALID(pForm);

			pForm->SetWaterMarkImage(nWaterMarkResID, clrWatermarkBase);
		}
	}

	if (((CBCGPMSOfficeDemoView*)GetActiveView ()) != NULL)
	{
		((CBCGPMSOfficeDemoView*)GetActiveView ())->OnChangeVisualTheme();
	}
}

void CMainFrame::OnViewApplookCustomColor() 
{
	theApp.m_clrCustom = m_pLookColor->GetColor ();
	theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_CUSTOM);
}

CBCGPRibbonButton* FindLookColorParent (CBCGPRibbonButton* pParent, UINT nID)
{
	if (pParent->FindSubItemIndexByID (nID) != -1)
	{
		return pParent;
	}

	const CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*>& items = pParent->GetSubItems ();
	for (int i = 0; i < items.GetSize (); i++)
	{
		pParent = DYNAMIC_DOWNCAST(CBCGPRibbonButton, items[i]);
		if (pParent != NULL && pParent->GetSubItems ().GetSize () > 0)
		{
			pParent = FindLookColorParent (pParent, nID);
			if (pParent != NULL)
			{
				break;
			}
		}

		pParent = NULL;
	}

	return pParent;
}

void CMainFrame::UpdateMainButtonColor (COLORREF clr)
{
	if (CBCGPVisualManager::GetInstance()->GetMainButtonColor () != clr)
	{
		CBCGPVisualManager::GetInstance()->SetMainButtonColor (clr);

		if (m_wndRibbonBar.IsBackstageMode ())
		{
			m_wndRibbonBar.GetBackstageCategory ()->OnChangeVisualManager ();
		}
	}
}
//***********************************************************************************
BOOL CMainFrame::CreateRibbonBar ()
{
	int i = 0;

	CBCGPRibbonCustomizationOptions customizationOptions;
	customizationOptions.m_strCustomImagesPath = _T("RibbonIcons.png");
	customizationOptions.m_bAlwaysShowSmallIcons = TRUE;

	m_wndRibbonBar.EnableCustomization(TRUE, &customizationOptions);

	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	if (!m_wndRibbonBar.LoadFromXML (_T("IDR_BCGP_RIBBON_XML")))
	{
		return FALSE;
	}

	//---------------------
	// Setup color buttons:
	//---------------------
	CBCGPRibbonColorButton* pFontColorBtn = DYNAMIC_DOWNCAST(CBCGPRibbonColorButton, m_wndRibbonBar.FindByID(ID_FONT_COLOR));
	ASSERT_VALID(pFontColorBtn);
	
	pFontColorBtn->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pFontColorBtn->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE /* Contiguous Columns*/);
	pFontColorBtn->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);

	CBCGPRibbonColorButton* pParaColorBtn = DYNAMIC_DOWNCAST(CBCGPRibbonColorButton, m_wndRibbonBar.FindByID(ID_PARA_SHADING));
	ASSERT_VALID(pParaColorBtn);

	pParaColorBtn->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pParaColorBtn->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE /* Contiguous Columns*/);
	pParaColorBtn->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);

	CBCGPRibbonColorButton* pPageBackBtn = DYNAMIC_DOWNCAST(CBCGPRibbonColorButton, m_wndRibbonBar.FindByID(ID_PAGELAYOUT_PAGEBACKGROUND_PAGECOLOR));
	ASSERT_VALID(pPageBackBtn);

	pPageBackBtn->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pPageBackBtn->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE /* Contiguous Columns*/);
	pPageBackBtn->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);

	m_pLookColor = DYNAMIC_DOWNCAST(CBCGPRibbonColorButton, m_wndRibbonBar.FindByID(ID_VIEW_APPLOOK_2007_5));
	ASSERT_VALID(m_pLookColor);

	m_pLookColor->AddColorsGroup (_T("Presets"), theApp.m_lstCustomColors);

	theApp.m_clrCustom = (COLORREF)theApp.GetInt (_T("LookColor"), (COLORREF)-1);
	m_pLookColor->SetColor (theApp.m_clrCustom);

	//----------------------------------------------------
	// Replace some ribbon galleries with custom controls:
	//----------------------------------------------------

	// Table gallery:
	CRibbonTableButton galleryTable;
	galleryTable.SetMenu (IDR_INSERT_TABLE_MENU);
	galleryTable.SetPaletteID (ID_FROM_PALETTE_TABLE);
	galleryTable.SetButtonMode ();

	m_wndRibbonBar.ReplaceRibbonElementByID(ID_INSERT_TABLE, galleryTable, FALSE);

	CBCGPRibbonPaletteButton* pQuickStyles = DYNAMIC_DOWNCAST(CBCGPRibbonPaletteButton, m_wndRibbonBar.FindByID(ID_WRITE_QUICKSTYLES));
	if (pQuickStyles != NULL)
	{
		ASSERT_VALID(pQuickStyles);

		for (i = 0; i < (int)m_arStyles.GetSize(); i++)
		{
			pQuickStyles->SetItemToolTip(i, m_arStyles[i]);
		}

		pQuickStyles->EnableItemTextLabels(TRUE);
	}

	// Themes Gallery:
	CBCGPRibbonPaletteButton galleryTheme;

	galleryTheme.AddGroup (_T("Built-In"), IDB_THEME_THEMES, 64);
	galleryTheme.AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_RESETFROMTEMPLATE, _T("&Reset to Theme from Template")));
	galleryTheme.AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_MORETHEMES, _T("More Themes on Microsoft &Office Online...")));
	galleryTheme.AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_BROWSEFORTHEMES, _T("&Browse for Themes..."), 24));
	galleryTheme.AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_SAVECURRENTTHEME, _T("&Save Current Theme..."), 25));
	galleryTheme.SetButtonMode();
	galleryTheme.SetIconsInRow (4);
	galleryTheme.EnableMenuResize ();
	galleryTheme.EnableItemTextLabels();

	for (i = 0; i < (int)m_arThemes.GetSize(); i++)
	{
		galleryTheme.SetItemToolTip(i, m_arThemes[i]);
	}

	m_wndRibbonBar.ReplaceRibbonElementByID(ID_PAGELAYOUT_THEMES, galleryTheme, FALSE);

	// Color Theme Gallery:
	CBCGPRibbonPaletteButton galleryColorTheme;
	
	galleryColorTheme.AddGroup (_T("Built-In"), IDB_THEME_COLORS, 103);
	galleryColorTheme.AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_COLORS_CREATENEWTHEMECOLORS, _T("&Create New Theme Colors...")));
	galleryColorTheme.SetButtonMode();
	galleryColorTheme.SetComboMode(TRUE, TRUE /* Draw check frame around gallery image */);
	galleryColorTheme.EnableMenuResize (TRUE, TRUE);	// Vertical only

	for (i = 0; i < (int)m_arColors.GetSize(); i++)
	{
		galleryColorTheme.SetItemToolTip(i, m_arColors[i]);
	}

	m_wndRibbonBar.ReplaceRibbonElementByID(ID_PAGELAYOUT_COLORS, galleryColorTheme, FALSE);
	m_wndRibbonBar.ReplaceRibbonElementByID(ID_STYLECHANGE_COLORS, galleryColorTheme, FALSE);

	// Fonts Gallery:
	CRibbonListFontButton galleryFonts;
	
	galleryFonts.AddGroup (_T("Built-In"), IDB_THEME_FONTS, 43);
	galleryFonts.AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_FONTS_CREATENEWTHEMEFONTS, _T("&Create New Theme Fonts...")));
	galleryFonts.EnableMenuResize (TRUE, TRUE);	// Vertical only
	galleryFonts.SetButtonMode();
	galleryFonts.SetComboMode();

	galleryFonts.SetItem(0, _T("Calibri"), _T("Calibri"), _T("Calibri"));
	galleryFonts.SetItem(1, _T("Arial"), _T("Arial"), _T("Arial"));
	galleryFonts.SetItem(2, _T("Arial - Times New Roman"), _T("Arial"), _T("Times New Roman"));
	galleryFonts.SetItem(3, _T("Times New Roman - Arial"), _T("Times New Roman"), _T("Arial"));

	m_wndRibbonBar.ReplaceRibbonElementByID(ID_PAGELAYOUT_FONTS, galleryFonts, FALSE);
	m_wndRibbonBar.ReplaceRibbonElementByID(ID_STYLECHANGE_FONTS, galleryFonts, FALSE);

	// Effects Gallery:
	CBCGPRibbonPaletteButton galleryEffects;
	
	galleryEffects.AddGroup (_T("Built-In"), IDB_THEME_EFFECTS, 64);
	galleryEffects.SetIconsInRow (4);
	galleryEffects.EnableMenuResize ();
	galleryEffects.EnableItemTextLabels();
	galleryEffects.SetButtonMode();

	for (i = 0; i < (int)m_arEffects.GetSize(); i++)
	{
		galleryEffects.SetItemToolTip(i, m_arEffects[i]);
	}

	m_wndRibbonBar.ReplaceRibbonElementByID(ID_PAGELAYOUT_EFFECTS, galleryEffects, FALSE);

	// Style Gallery:
	CBCGPRibbonPaletteButton galleryStyle(0, NULL, -1, -1, CSize (0, 0), 0, TRUE);
	galleryStyle.SetButtonMode();
	galleryStyle.SetComboMode();
	galleryStyle.AddGroup (_T(""), (int)m_arStyleSets.GetSize());
	galleryStyle.AddSubItem (new CBCGPRibbonButton (0, _T("&Reset to Quick Styles from Template")));
	galleryStyle.EnableMenuResize (TRUE, TRUE);	// Vertical only
	galleryStyle.EnablMenuSideBar ();

	for (i = 0; i < (int)m_arStyleSets.GetSize(); i++)
	{
		galleryStyle.SetItemToolTip(i, m_arStyleSets[i]);
	}

	m_wndRibbonBar.ReplaceRibbonElementByID(ID_STYLECHANGE_STYLESET, galleryStyle, FALSE);

	// Setup Backstage Views:
	CBCGPRibbonBackstageViewPanel* pBackstagePanel = m_wndRibbonBar.GetBackstageViewPanel();
	if (pBackstagePanel != NULL)
	{
		ASSERT_VALID(pBackstagePanel);

		// Add "Info" page:
		CBCGPRibbonBackstageViewItemForm* pFormInfo = new CBCGPRibbonBackstageViewItemForm (IDD_FORM_INFO, RUNTIME_CLASS(CBackStagePageInfo));
		pFormInfo->SetWaterMarkImage(IDB_BS_WATERMARK, clrWatermarkBase);
		pFormInfo->SetText(_T("Information"));

		pBackstagePanel->AttachViewToItem(4, pFormInfo, FALSE);

		// Add "Recent" page:
		pBackstagePanel->AttachRecentViewToItem(5, BCGP_SHOW_FOLDERS_LIST | BCGP_SHOW_PINS, 
			FALSE, IDB_BS_WATERMARK, clrWatermarkBase);

		// Add "New" page:
		CBCGPRibbonBackstageViewItemForm* pFormNew = new CBCGPRibbonBackstageViewItemForm (IDD_FORM_NEW, RUNTIME_CLASS(CBackStagePageNew));
		pFormNew->SetWaterMarkImage(IDB_BS_WATERMARK, clrWatermarkBase);

		pBackstagePanel->AttachViewToItem(6, pFormNew, FALSE);

		// Add "Print" page:
		pBackstagePanel->AttachPrintPreviewToItem(7, FALSE, IDB_BS_WATERMARK, clrWatermarkBase, 500);

		// Add "Save and Send" page:
		CBCGPRibbonBackstageViewItemPropertySheet* pFormShare = new CBCGPRibbonBackstageViewItemPropertySheet(IDB_BS_SHARE, 32, TRUE /* Icons autoscale */, TRUE /* Page standard headers */);

		pFormShare->AddGroup(_T("Save & Send"));
		pFormShare->AddPage(&m_Page1);
		pFormShare->AddPage(&m_Page2);
		pFormShare->AddPage(&m_Page3);
		pFormShare->AddPage(&m_Page4);
		pFormShare->AddGroup(_T("File Types"));
		pFormShare->AddPage(&m_Page5);
		pFormShare->AddPage(&m_Page6);

		pFormShare->SetWaterMarkImage(IDB_BS_WATERMARK, clrWatermarkBase);
		
		pBackstagePanel->AttachViewToItem(8, pFormShare, FALSE);

		// Add "Help" page:
		CBCGPRibbonBackstageViewItemForm* pFormHelp = new CBCGPRibbonBackstageViewItemForm (IDD_FORM_HELP, RUNTIME_CLASS(CBackStagePageHelp));
		pFormHelp->SetWaterMarkImage(IDB_BS_WATERMARK, clrWatermarkBase);

		pBackstagePanel->AttachViewToItem(9, pFormHelp, FALSE);
	}

	m_wndRibbonBar.EnableToolTips (theApp.m_bShowToolTips, theApp.m_bShowToolTipDescr);
	m_wndRibbonBar.EnableKeyTips (theApp.m_bShowKeyTips);
	m_wndRibbonBar.SetBackstagePageTransitionEffect(theApp.m_bIsRTL ? CBCGPPageTransitionManager::BCGPPageTransitionNone : theApp.m_PageTransitionEffect);

	return TRUE;
}
//***********************************************************************************
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CBCGPFrameWnd::OnGetMinMaxInfo(lpMMI);

	ASSERT (lpMMI != NULL);

	lpMMI->ptMinTrackSize.y = GetSystemMetrics (SM_CXFIXEDFRAME) * 3 +
		GetSystemMetrics (SM_CYCAPTION);

	lpMMI->ptMinTrackSize.x = 
		GetSystemMetrics (SM_CYCAPTION) * 2 +
		GetSystemMetrics (SM_CXFIXEDFRAME) * 2 +
		GetSystemMetrics (SM_CXSIZE) * 3;
}
//***********************************************************************************
CBCGPToolBarImages* CMainFrame::GetTooltipImage (UINT uiID)
{
	if (!theApp.m_bShowToolTipDescr)
	{
		return NULL;
	}

	BOOL bIsOffice2007Look = (theApp.GetVisualTheme() >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLUE && theApp.GetVisualTheme() <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_AQUA) || theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_CUSTOM;
	UINT uiResID = 0;

	switch (uiID)
	{
	case ID_MAIN_BUTTON:
		if (bIsOffice2007Look)
		{
			uiResID = IDB_TOOLTIP_MAIN;
		}
		break;

	case ID_WRITE_CLIPBOARD:
		uiResID = IDB_TOOLTIP_CLIPBOARD;
		break;

	case ID_WRITE_FONT:
		uiResID = IDB_TOOLTIP_FONTDLG;
		break;

	case ID_WRITE_PARAGRAPH:
		uiResID = IDB_TOOLTIP_PARAGRAPH;
		break;
	}

	if (uiResID == 0)
	{
		return NULL;
	}

	CBCGPToolBarImages* pTooltipImage = NULL;

	if (!m_TooltipImages.Lookup(uiID, pTooltipImage))
	{
		pTooltipImage = new CBCGPToolBarImages;
		pTooltipImage->Load(uiResID);
		pTooltipImage->SetSingleImage();

		if (globalData.GetRibbonImageScale() != 1.0 && !pTooltipImage->IsScaled())
		{
			pTooltipImage->SmoothResize(globalData.GetRibbonImageScale());
		}

		m_TooltipImages.SetAt(uiID, pTooltipImage);
	}

	return pTooltipImage;
}
//*****************************************************************************
void CMainFrame::AdjustClientArea ()
{
	if (m_pPrintPreviewFrame != NULL || IsRibbonBackstageView())
	{
		if (m_wndScrollBar.GetSafeHwnd () != NULL &&
			m_wndScrollBar.IsWindowVisible ())
		{
			m_wndScrollBar.ShowWindow (SW_HIDE);
		}

		CBCGPFrameWnd::AdjustClientArea ();
		return;
	}

	CWnd* pChildWnd = GetDlgItem (AFX_IDW_PANE_FIRST);
	if (pChildWnd != NULL)
	{
		CRect rectClientAreaBounds = m_dockManager.GetClientAreaBounds ();

		rectClientAreaBounds.left += m_rectBorder.left;
		rectClientAreaBounds.top  += m_rectBorder.top;
		rectClientAreaBounds.right -= m_rectBorder.right;
		rectClientAreaBounds.bottom -= m_rectBorder.bottom;

		CRect rectScroll = rectClientAreaBounds;
		const int cxScroll = m_wndScrollBar.GetSafeHwnd () != NULL ? ::GetSystemMetrics (SM_CXVSCROLL) : 0;

		rectScroll.left = rectScroll.right - cxScroll;

		if (rectClientAreaBounds.Width () > 100 &&
			rectClientAreaBounds.Height () > 100)
		{
			m_rectFill = rectClientAreaBounds;
			m_rectFill.right -= cxScroll;

			rectClientAreaBounds.DeflateRect (40, 20, 40, 20);
		}
		else
		{
			m_rectFill.SetRectEmpty ();
		}

		rectClientAreaBounds.right -= cxScroll;

		pChildWnd->CalcWindowRect (rectClientAreaBounds);

		if (!pChildWnd->IsKindOf (RUNTIME_CLASS (CSplitterWnd)))
		{
			pChildWnd->ModifyStyle (0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

			if (!m_rectFill.IsRectEmpty ())
			{
				pChildWnd->ModifyStyleEx (WS_EX_CLIENTEDGE, 0);
				pChildWnd->ModifyStyle (0, WS_BORDER);
			}
		}
		else
		{
			pChildWnd->ModifyStyle (0, WS_CLIPSIBLINGS);
		}

		
		if (m_wndScrollBar.GetSafeHwnd () != NULL)
		{
			
			if (!m_wndScrollBar.IsWindowVisible ())
			{
				m_wndScrollBar.ShowWindow (SW_SHOWNOACTIVATE);
			}

			m_wndScrollBar.SetWindowPos (NULL, rectScroll.left, rectScroll.top,
				cxScroll, rectScroll.Height (), SWP_NOZORDER | SWP_NOACTIVATE);
			m_wndScrollBar.RedrawWindow ();
		}

		pChildWnd->SetWindowPos (&wndBottom, rectClientAreaBounds.left, 
										rectClientAreaBounds.top, 
										rectClientAreaBounds.Width (), 
										rectClientAreaBounds.Height (),
										SWP_NOACTIVATE);
	}

	if (!m_rectFill.IsRectEmpty ())
	{
		RedrawWindow (m_rectFill);
	}
}
//***********************************************************************************
void CMainFrame::OnPaint() 
{
	if (m_rectFill.IsRectEmpty ())
	{
		Default ();
		return;
	}

	CPaintDC dc (this); // device context for painting
	OnDrawClientArea(&dc);
}
//*********************************************************************************************************
void CMainFrame::OnDrawClientArea(CDC* pDC)
{
	CRect rectChild;
	rectChild.SetRectEmpty ();

	CWnd* pChildWnd = GetDlgItem (AFX_IDW_PANE_FIRST);
	if (pChildWnd != NULL)
	{
		pChildWnd->GetWindowRect (rectChild);
		ScreenToClient (rectChild);
	}

	CRect rectScreen;

	MONITORINFO mi;
	mi.cbSize = sizeof (MONITORINFO);
	if (GetMonitorInfo (MonitorFromPoint (CPoint (0, 0), MONITOR_DEFAULTTONEAREST),
		&mi))
	{
		rectScreen = mi.rcWork;
	}
	else
	{
		::SystemParametersInfo (SPI_GETWORKAREA, 0, &rectScreen, 0);
	}

	if (m_MemBitmap.GetSafeHandle () != NULL)
	{
		BITMAP bmp;
		m_MemBitmap.GetBitmap (&bmp);

		if (bmp.bmWidth != rectScreen.Width () || bmp.bmHeight != rectScreen.Height ())
		{
			m_MemBitmap.DeleteObject ();
		}
	}

	if (m_MemBitmap.GetSafeHandle () == NULL)
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC (pDC);

		m_MemBitmap.CreateCompatibleBitmap (pDC, rectScreen.Width (), rectScreen.Height ());
		
		CBitmap* pBmpOld = dcMem.SelectObject (&m_MemBitmap);

		CBCGPDrawManager dm (dcMem);

		rectScreen.OffsetRect (-rectScreen.TopLeft ());

		if (globalData.m_nBitsPerPixel <= 8 || globalData.IsHighContastMode ())
		{
			dcMem.FillRect(rectScreen, &globalData.brBarFace);
		}
		else
		{
			switch (theApp.GetVisualTheme())
			{
			case CBCGPWinApp::BCGP_VISUAL_THEME_SCENIC:
			default:
				dm.FillGradient (rectScreen, RGB (197, 207, 223), RGB (219, 228, 241), TRUE);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLUE:
				dm.FillGradient (rectScreen, RGB(102, 139, 188), RGB(164, 194, 234), TRUE);
				break;
				
			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_SILVER:
				dm.FillGradient (rectScreen, RGB (114, 125, 152), RGB (178, 185, 202), TRUE);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLACK:
				dm.FillGradient (rectScreen, RGB ( 56,  56,  56), RGB(79, 79, 79), TRUE);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_AQUA:
				dm.FillGradient (rectScreen, RGB(156, 160, 167), RGB(192, 196, 207), TRUE);
				break;
				
			case CBCGPWinApp::BCGP_VISUAL_THEME_CUSTOM:
				dm.FillGradient (rectScreen, globalData.clrBarDkShadow, globalData.clrBarShadow, TRUE);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLUE:
				dm.FillGradient (rectScreen, RGB (183, 204, 228), RGB (183, 204, 228), TRUE);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_SILVER:
				dm.FillGradient (rectScreen, RGB (205, 209, 214), RGB (205, 209, 214), TRUE);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLACK:
				dm.FillGradient (rectScreen, RGB (111, 111, 111), RGB (111, 111, 111), TRUE);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY:
				dm.DrawRect(rectScreen, RGB(102, 102, 102), (COLORREF)-1);
				break;

			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK:
				dm.DrawRect(rectScreen, RGB(37, 37, 37), (COLORREF)-1);
				break;
				
			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE:
			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_WHITE:
			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_GRAY:
			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY:
			case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL:
				dm.DrawRect(rectScreen, globalData.clrBarFace, (COLORREF)-1);
				break;
			}
		}

		dcMem.SelectObject (pBmpOld);
	}

	CRect rectFill = m_rectFill;

	if (!m_rectSizing.IsRectEmpty ())
	{
		pDC->FillRect (m_rectSizing, &globalData.brBarFace);
		rectFill.right += m_rectSizing.Width ();
	}

	pDC->DrawState (rectFill.TopLeft (), rectFill.Size (), &m_MemBitmap, DSS_NORMAL);
}
//***********************************************************************************
BOOL CMainFrame::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}
//***********************************************************************************
LRESULT CMainFrame::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if (lp & PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC) wp);
		ASSERT_VALID(pDC);

		OnDrawClientArea(pDC);
	}

	return 0;
}
//***********************************************************************************
void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CRect rectOld;
	GetWindowRect (rectOld);

	CRect rectNew = pRect;

	if (rectNew.right > rectOld.right)
	{
		m_rectSizing = rectNew;
		m_rectSizing.left = rectOld.right;

		ScreenToClient (m_rectSizing);
	}
	else
	{
		m_rectSizing.SetRectEmpty ();
	}

	CBCGPFrameWnd::OnSizing(fwSide, pRect);
}
//***********************************************************************************
void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPFrameWnd::OnSize(nType, cx, cy);
	
	if (nType == SIZE_MAXIMIZED || nType == SIZE_RESTORED)
	{
		RedrawWindow (NULL, NULL,
			RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	}

	if (GetActiveView()->GetSafeHwnd() != NULL)
	{
		GetActiveView()->RedrawWindow();
	}
}
//***********************************************************************************
void CMainFrame::CreateDocumentColors ()
{
	typedef struct 
	{
		COLORREF	color;
		TCHAR*		szName;
	} 
	ColorTableEntry;

	int i = 0;
	int nNumColours = 0;

	static ColorTableEntry colorsMain [] = 
	{
		{	RGB (255, 255, 255),	_T("White, Background 1")	},
		{	RGB (0, 0, 0),			_T("Black, Text 1")			},
		{	RGB (238, 236, 225),	_T("Tan, Background 2")		},
		{	RGB (31, 73, 125),		_T("Dark Blue, Text 2")		},
		{	RGB (79, 129, 189),		_T("Blue, Accent 1")		},
		{	RGB (192, 80, 77),		_T("Red, Accent 2")			},
		{	RGB (155, 187, 89),		_T("Olive Green, Accent 3")	},
		{	RGB (128, 100, 162),	_T("Purple, Accent 4")		},
		{	RGB (75, 172, 198),		_T("Aqua, Accent 5")		},
		{	RGB (245, 150, 70),		_T("Orange, Accent 6")		}
	};

	static ColorTableEntry colorsAdditional [] = 
	{
		{	RGB (242, 242, 242),	_T("White, Background 1, Darker 5%")	},
		{	RGB (127, 127, 127),	_T("Black, Text 1, Lighter 50%")		},
		{	RGB (214, 212, 202),	_T("Tan, Background 2, Darker 10%")		},
		{	RGB (210, 218, 229),	_T("Dark Blue, Text 2, Lighter 80%")	},
		{	RGB (217, 228, 240),	_T("Blue, Accent 1, Lighter 80%")		},
		{	RGB (244, 219, 218),	_T("Red, Accent 2, Lighter 80%")		},
		{	RGB (234, 241, 221),	_T("Olive Green, Accent 3, Lighter 80%")},
		{	RGB (229, 223, 235),	_T("Purple, Accent 4, Lighter 80%")		},
		{	RGB (216, 237, 242),	_T("Aqua, Accent 5, Lighter 80%")		},
		{	RGB (255, 234, 218),	_T("Orange, Accent 6, Lighter 80%")		},

		{	RGB (215, 215, 215),	_T("White, Background 1, Darker 15%")	},
		{	RGB (89, 89, 89),		_T("Black, Text 1, Lighter 35%")		},
		{	RGB (177, 176, 167),	_T("Tan, Background 2, Darker 25%")		},
		{	RGB (161, 180, 201),	_T("Dark Blue, Text 2, Lighter 60%")	},
		{	RGB (179, 202, 226),	_T("Blue, Accent 1, Lighter 60%")		},
		{	RGB (233, 184, 182),	_T("Red, Accent 2, Lighter 60%")		},
		{	RGB (213, 226, 188),	_T("Olive Green, Accent 3, Lighter 60%")},
		{	RGB (203, 191, 215),	_T("Purple, Accent 4, Lighter 60%")		},
		{	RGB (176, 220, 231),	_T("Aqua, Accent 5, Lighter 60%")		},
		{	RGB (255, 212, 181),	_T("Orange, Accent 6, Lighter 60%")		},

		{	RGB (190, 190, 190),	_T("White, Background 1, Darker 25%")	},
		{	RGB (65, 65, 65),		_T("Black, Text 1, Lighter 25%")		},
		{	RGB (118, 117, 112),	_T("Tan, Background 2, Darker 35%")		},
		{	RGB (115, 143, 175),	_T("Dark Blue, Text 2, Lighter 40%")	},
		{	RGB (143, 177, 213),	_T("Blue, Accent 1, Lighter 40%")		},
		{	RGB (222, 149, 147),	_T("Red, Accent 2, Lighter 40%")		},
		{	RGB (192, 213, 155),	_T("Olive Green, Accent 3, Lighter 40%")},
		{	RGB (177, 160, 197),	_T("Purple, Accent 4, Lighter 40%")		},
		{	RGB (137, 203, 218),	_T("Aqua, Accent 5, Lighter 40%")		},
		{	RGB (255, 191, 145),	_T("Orange, Accent 6, Lighter 40%")		},

		{	RGB (163, 163, 163),	_T("White, Background 1, Darker 35%")	},
		{	RGB (42, 42, 42),		_T("Black, Text 1, Lighter 15%")		},
		{	RGB (61, 61, 59),		_T("Tan, Background 2, Darker 50%")		},
		{	RGB (20, 57, 92),		_T("Dark Blue, Text 2, Darker 25%")		},
		{	RGB (54, 96, 139),		_T("Blue, Accent 1, Darker 25%")		},
		{	RGB (149, 63, 60),		_T("Red, Accent 2, Darker 25%")			},
		{	RGB (114, 139, 71),		_T("Olive Green, Accent 3, Darker 25%")	},
		{	RGB (97, 76, 119),		_T("Purple, Accent 4, Darker 25%")		},
		{	RGB (41, 128, 146),		_T("Aqua, Accent 5, Darker 25%")		},
		{	RGB (190, 112, 59),		_T("Orange, Accent 6, Darker 25%")		},

		{	RGB (126, 126, 126),	_T("White, Background 1, Darker 50%")	},
		{	RGB (20, 20, 20),		_T("Black, Text 1, Lighter 5%")			},
		{	RGB (29, 29, 28),		_T("Tan, Background 2, Darker 90%")		},
		{	RGB (17, 40, 64),		_T("Dark Blue, Text 2, Darker 50%")		},
		{	RGB (38, 66, 94),		_T("Blue, Accent 1, Darker 50%")		},
		{	RGB (100, 44, 43),		_T("Red, Accent 2, Darker 50%")			},
		{	RGB (77, 93, 49),		_T("Olive Green, Accent 3, Darker 50%")	},
		{	RGB (67, 53, 81),		_T("Purple, Accent 4, Darker 50%")		},
		{	RGB (31, 86, 99),		_T("Aqua, Accent 5, Darker 50%")		},
		{	RGB (126, 77, 42),		_T("Orange, Accent 6, Darker 50%")		},
	};

	static ColorTableEntry colorsStandard [] = 
	{
		{	RGB (200, 15, 18),		_T("Dark Red")		},
		{	RGB (255, 20, 24),		_T("Red")			},
		{	RGB (255, 191, 40),		_T("Orange")		},
		{	RGB (255, 255, 49),		_T("Yellow")		},
		{	RGB (138, 207, 87),		_T("Light Green")	},
		{	RGB (0, 175, 84),		_T("Green")			},
		{	RGB (0, 174, 238),		_T("Light Blue")	},
		{	RGB (0, 111, 189),		_T("Blue")			},
		{	RGB (0, 36, 95),		_T("Black")			},
		{	RGB (114, 50, 157),		_T("Purple")		},
	};

	m_lstMainColors.RemoveAll ();
	nNumColours = sizeof (colorsMain) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstMainColors.AddTail (colorsMain [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsMain [i].color, colorsMain [i].szName);
	};

	m_lstAdditionalColors.RemoveAll ();
	nNumColours = sizeof (colorsAdditional) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstAdditionalColors.AddTail (colorsAdditional [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsAdditional [i].color, colorsAdditional [i].szName);
	};

	m_lstStandardColors.RemoveAll ();
	nNumColours = sizeof (colorsStandard) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstStandardColors.AddTail (colorsStandard [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsStandard [i].color, colorsStandard [i].szName);
	};
}
//***********************************************************************************
void CMainFrame::CreateStyleList ()
{
	m_arStyles.RemoveAll ();
	m_arStyleSets.RemoveAll ();

	m_arStyles.Add( _T("¶ Normal"));
	m_arStyles.Add( _T("¶ No Spacing"));
	m_arStyles.Add( _T("Heading 1"));
	m_arStyles.Add( _T("Heading 2"));
	m_arStyles.Add( _T("Title"));
	m_arStyles.Add( _T("Subtitle"));
	m_arStyles.Add( _T("Subtle Emphasis"));
	m_arStyles.Add( _T("Emphasis"));
	m_arStyles.Add( _T("Intense Emphasis"));
	m_arStyles.Add( _T("Strong"));
	m_arStyles.Add( _T("Quote"));
	m_arStyles.Add( _T("Intense Quote"));
	m_arStyles.Add( _T("Subtle Reference"));
	m_arStyles.Add( _T("Intense Reference"));
	m_arStyles.Add( _T("Book Title"));
	m_arStyles.Add( _T("¶ List Paragraph"));

	m_arStyleSets.Add (_T("Default (Black and White)"));
	m_arStyleSets.Add (_T("Elegant"));
	m_arStyleSets.Add (_T("Fancy"));
	m_arStyleSets.Add (_T("Formal"));
	m_arStyleSets.Add (_T("Manuscript"));
	m_arStyleSets.Add (_T("Modern"));
	m_arStyleSets.Add (_T("Simple"));
	m_arStyleSets.Add (_T("Traditional"));
};
//***********************************************************************************
void CMainFrame::CreateThemeList ()
{
	m_arThemes.RemoveAll ();
	m_arColors.RemoveAll ();
	m_arEffects.RemoveAll ();

	m_arThemes.Add (_T("Office"));
	m_arThemes.Add (_T("Facet"));
	m_arThemes.Add (_T("Integral"));
	m_arThemes.Add (_T("Ion"));
	m_arThemes.Add (_T("Ion Boardroom"));
	m_arThemes.Add (_T("Organic"));
	m_arThemes.Add (_T("Retrospect"));
	m_arThemes.Add (_T("Slice"));
	m_arThemes.Add (_T("Wisp"));
	m_arThemes.Add (_T("Basis"));
	m_arThemes.Add (_T("Berlin"));
	m_arThemes.Add (_T("Circuit"));
	m_arThemes.Add (_T("Dividend"));
	m_arThemes.Add (_T("Frame"));
	m_arThemes.Add (_T("Metropolitan"));
	m_arThemes.Add (_T("Parallax"));
	m_arThemes.Add (_T("Quotable"));
	m_arThemes.Add (_T("Savon"));
	m_arThemes.Add (_T("View"));

	m_arColors.Add (_T("Office"));
	m_arColors.Add (_T("Office 2007 - 2010"));
	m_arColors.Add (_T("Grayscale"));
	m_arColors.Add (_T("Blue Warm"));
	m_arColors.Add (_T("Blue"));
	m_arColors.Add (_T("Blue II"));
	m_arColors.Add (_T("Blue Green"));
	m_arColors.Add (_T("Green"));
	m_arColors.Add (_T("Green Yellow"));
	m_arColors.Add (_T("Yellow"));
	m_arColors.Add (_T("Yellow Orange"));
	m_arColors.Add (_T("Orange"));
	m_arColors.Add (_T("Orange Red"));
	m_arColors.Add (_T("Red Orange"));
	m_arColors.Add (_T("Red"));
	m_arColors.Add (_T("Red Violet"));
	m_arColors.Add (_T("Violet"));
	m_arColors.Add (_T("Violet II"));
	m_arColors.Add (_T("Median"));
	m_arColors.Add (_T("Paper"));
	m_arColors.Add (_T("Marquee"));
	m_arColors.Add (_T("Slipstream"));
	m_arColors.Add (_T("Aspect"));

	m_arEffects.Add (_T("Office"));
	m_arEffects.Add (_T("Office 2007 - 2010"));
	m_arEffects.Add (_T("Subtle Solid"));
	m_arEffects.Add (_T("Banded Edge"));
	m_arEffects.Add (_T("Smokey Glass"));
	m_arEffects.Add (_T("Glow Edge"));
	m_arEffects.Add (_T("Grunge Texture"));
	m_arEffects.Add (_T("Frosted Glass"));
	m_arEffects.Add (_T("Top Shadow"));
	m_arEffects.Add (_T("Inset"));
	m_arEffects.Add (_T("Milk Glass"));
	m_arEffects.Add (_T("Riblet"));
	m_arEffects.Add (_T("Reflection"));
	m_arEffects.Add (_T("Extreme Shadow"));
	m_arEffects.Add (_T("Glossy"));
}
//***********************************************************************************
void CMainFrame::ActivateRibbonContextCategory (UINT uiCategoryID)
{
	if (m_wndRibbonBar.GetHideFlags () == 0)
	{
		m_wndRibbonBar.ActivateContextCategory (uiCategoryID);
	}
}
//***********************************************************************************
void CMainFrame::SetRibbonContextCategory (UINT uiCategoryID)
{
	BOOL bRecalc = m_wndRibbonBar.HideAllContextCategories ();

	if (uiCategoryID != 0)
	{
		m_wndRibbonBar.ShowContextCategories (uiCategoryID);
		bRecalc = TRUE;
	}

	if (bRecalc)
	{
		m_wndRibbonBar.RecalcLayout ();
		m_wndRibbonBar.RedrawWindow ();

		SendMessage (WM_NCPAINT, 0, 0);
	}
}
//******************************************************************************************************************
BOOL CMainFrame::CreateStatusBar ()
{
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;
	}

	if (!m_wndStatusBar.LoadFromXML (_T("IDR_BCGP_RIBBON_XML")))
	{
		return FALSE;
	}

	CBCGPRibbonStatusBarPane* pSpellPane = 
		DYNAMIC_DOWNCAST(CBCGPRibbonStatusBarPane, m_wndStatusBar.FindByID (ID_STATUSBAR_SPELL));
	if (pSpellPane != NULL)
	{
		pSpellPane->SetAnimationList ((UINT) IDB_SPELL, 16, RGB (192, 192, 192));
	}

	return TRUE;
}
//******************************************************************************************************************
BOOL CMainFrame::CreateMessageBar ()
{
	if (!m_wndMessageBar.Create (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 
		this, ID_VIEW_MESSAGEBAR, -1, TRUE))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	m_wndMessageBar.SetButton (_T("Options..."), ID_TOOLS_OPTIONS, CBCGPCaptionBar::ALIGN_LEFT, FALSE);
	m_wndMessageBar.SetButtonToolTip (_T("Click here to see more options"));

	m_wndMessageBar.SetText (_T("Welcome to BCGControlBar Pro demonstration! \aClick here\a to visit BCGSoft Web site."), CBCGPCaptionBar::ALIGN_LEFT);

	m_wndMessageBar.SetBitmap (IDB_INFO, (COLORREF)-1, FALSE, CBCGPCaptionBar::ALIGN_LEFT, TRUE);
	m_wndMessageBar.SetImageToolTip (_T("Important"), _T("Please take a look at BCGPMSOfficeDemo source code to learn how to create advanced user interface in minutes."));

	return TRUE;
}
//******************************************************************************************************************
void CMainFrame::OnTimer(UINT_PTR nIDEvent) 
{
	if (nIDEvent == IdStartProgressTimer)
	{
		ShowProgress ();
		KillTimer (IdStartProgressTimer);
	}

	if (nIDEvent == IdShowProgressTimer)
	{
		m_nProgressValue++;

		if (m_nProgressValue > 100)
		{
			ShowProgress (FALSE);
		}
		else
		{
			CBCGPRibbonProgressBar* pProgress = DYNAMIC_DOWNCAST (
				CBCGPRibbonProgressBar,
				m_wndStatusBar.FindElement (ID_STATUSBAR_PROGRESS));
			ASSERT_VALID (pProgress);

			pProgress->SetPos (m_nProgressValue, TRUE);
		}
	}
}
//******************************************************************************************************************
void CMainFrame::ShowProgress (BOOL bShow)
{
	if (bShow)
	{
		int cxFree = m_wndStatusBar.GetSpace ();
		if (cxFree < 20)
		{
			// Not enough space for progress bar
			return;
		}

		int cxProgress = min (cxFree, 150);

		CBCGPRibbonProgressBar* pProgressBar = 
			new CBCGPRibbonProgressBar (ID_STATUSBAR_PROGRESS, cxProgress);

		pProgressBar->SetInfiniteMode (m_bInfiniteProgressMode);

		m_wndStatusBar.AddDynamicElement (pProgressBar);

		m_nProgressValue = 0;

		SetTimer (IdShowProgressTimer, 10, NULL);
	}
	else
	{
		KillTimer (IdShowProgressTimer);
		m_wndStatusBar.RemoveElement (ID_STATUSBAR_PROGRESS);
		m_nProgressValue = -1;
	}

	m_wndStatusBar.RecalcLayout ();
	m_wndStatusBar.RedrawWindow ();

	CBCGPPopupMenu::UpdateAllShadows ();
}
//******************************************************************************************************************
void CMainFrame::OnZoom()
{
	BCGPMessageBox (_T("Zoom dialog box..."));
}
//******************************************************************************************************************
void CMainFrame::OnRefresh()
{
	m_bInfiniteProgressMode = FALSE;
	ShowProgress ();
}
//******************************************************************************************************************
void CMainFrame::OnUpdateRefresh(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (m_nProgressValue < 0);
}
//******************************************************************************************************************
void CMainFrame::OnSpell()
{
	CBCGPRibbonStatusBarPane* pPane = DYNAMIC_DOWNCAST (
		CBCGPRibbonStatusBarPane,
		m_wndStatusBar.FindElement (ID_STATUSBAR_SPELL));

	if (pPane == NULL)
	{
		return;
	}

	if (pPane->IsAnimation ())
	{
		pPane->StopAnimation ();
	}
	else
	{
		pPane->StartAnimation (	500		/* 1/2 sec, Frame delay */,
								10000	/* 10 sec, animation duration */);
	}
}
//******************************************************************************************************************
BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
{
    CBCGPFrameWnd::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup == NULL)
	{
		return TRUE;
	}

	CBCGPPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	int nPasteIndex = pMenuBar->CommandToIndex (ID_EDIT_PASTE);
    if (nPasteIndex >= 0)
    {
		CBCGPToolbarButton* pExButton = pMenuBar->GetButton (nPasteIndex);
		ASSERT_VALID (pExButton);
		
		CBCGPRibbonPaletteMenuButton palettePaste(pExButton->m_nID, pExButton->GetImage (), pExButton->m_strText);

		InitPastePalette(&palettePaste.GetPalette());
		pMenuBar->ReplaceButton(ID_EDIT_PASTE, palettePaste);
	}

	int nBulletIndex = pMenuBar->CommandToIndex (ID_PARA_BULLETS);
    if (nBulletIndex >= 0)
    {
		CBCGPToolbarButton* pExButton = pMenuBar->GetButton (nBulletIndex);
		ASSERT_VALID (pExButton);

		CBCGPRibbonPaletteMenuButton paletteBullet (
			pExButton->m_nID, pExButton->GetImage (), pExButton->m_strText);

		InitBulletPalette (&paletteBullet.GetPalette ());

		pMenuBar->ReplaceButton (ID_PARA_BULLETS, paletteBullet);
	}

	int nNumIndex = pMenuBar->CommandToIndex (ID_PARA_NUMBERING);
    if (nNumIndex >= 0)
    {
		CBCGPToolbarButton* pExButton = pMenuBar->GetButton (nNumIndex);
		ASSERT_VALID (pExButton);

		CBCGPRibbonPaletteMenuButton paletteNum (
			pExButton->m_nID, pExButton->GetImage (), pExButton->m_strText);

		InitNumberingPalette (&paletteNum.GetPalette ());

		pMenuBar->ReplaceButton (ID_PARA_NUMBERING, paletteNum);
	}

	return TRUE;
}
//******************************************************************************************************************
void CMainFrame::InitPastePalette(CBCGPRibbonPaletteButton* pPalette)
{
	ASSERT_VALID (pPalette);

	pPalette->Clear();
	pPalette->AddGroup (_T("Paste Options:"), IDB_PASTE, 24);

	double dblRatio = m_wndRibbonBar.GetImagesLuminosity();
	if (dblRatio > 1.0)
	{
		pPalette->GetImages().MakeLighter(dblRatio - 1.0);
	}
	
	pPalette->SetItemToolTip (0, _T("Keep Source Formatting"));
	pPalette->SetItemToolTip (1, _T("Merge Formatting"));
	pPalette->SetItemToolTip (2, _T("Keep Text Only"));
	
	pPalette->SelectItem(-1);
}
//******************************************************************************************************************
void CMainFrame::InitBulletPalette (CBCGPRibbonPaletteButton* pPalette)
{
	ASSERT_VALID (pPalette);

	pPalette->SetPaletteID (ID_FROM_PALETTE_BULLET);

	pPalette->AddGroup (_T("Bullets"), IDB_BULLETS, 40);

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PARA_CHANGE_LIST_LEVEL, _T("&Change List Level")));

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PARA_DEFINENEWBULLET, _T("&Define New Bullet...")));

	pPalette->SetIconsInRow (6);

	if (m_bIsDarkTheme)
	{
		pPalette->GetImages().InvertColors();
	}
}
//******************************************************************************************************************
void CMainFrame::InitNumberingPalette (CBCGPRibbonPaletteButton* pPalette)
{
	ASSERT_VALID (pPalette);

	pPalette->SetPaletteID (ID_FROM_PALETTE_NUMBER);

	pPalette->AddGroup (_T("Numbering Library"), IDB_NUM, 76);

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PARA_CHANGE_LIST_LEVEL, _T("&Change List Level")));

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PARA_DEFINENEWNUMBERFORMAT, _T("&Define New Number Format...")));

	pPalette->SetIconsInRow (3);

	if (m_bIsDarkTheme)
	{
		pPalette->GetImages().InvertColors();
	}
}
//******************************************************************************************************************
void CMainFrame::InitMultilevelPalette (CBCGPRibbonPaletteButton* pPalette)
{
	ASSERT_VALID (pPalette);

	pPalette->SetPaletteID (ID_FROM_PALETTE_MULTILEVEL);

	pPalette->AddGroup (_T("List Library"), IDB_MULTI, 76);

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PARA_CHANGE_LIST_LEVEL, _T("&Change List Level")));

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PARA_DEFINENEWMULTILEVELLIST, _T("&Define New Multilevel List")));

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PARA_DEFINENEWLISTSTYLE, _T("Define New List &Style...")));

	pPalette->SetIconsInRow (3);

	if (m_bIsDarkTheme)
	{
		pPalette->GetImages().InvertColors();
	}
}
//******************************************************************************************************************
void CMainFrame::InitPositionPalette (CBCGPRibbonPaletteButton* pPalette)
{
	ASSERT_VALID (pPalette);

	pPalette->SetPaletteID (ID_FROM_PALETTE_POSITION);

	pPalette->AddGroup (_T("In Line with"), IDB_POSITION_1, 37);
	pPalette->AddGroup (_T("With Text Wrapping"), IDB_POSITION_2, 37);

	pPalette->AddSubItem (
		new CBCGPRibbonButton (ID_PAGELAYOUT_MORELAYOUTOPTIONS, _T("&More &Layout Options")));

	pPalette->SetIconsInRow (3);

	if (m_bIsDarkTheme)
	{
		pPalette->GetImages().InvertColors();
	}
}
//******************************************************************************************************************
void CMainFrame::SetBackgroundImage(CBCGPWinApp::BCGP_VISUAL_THEME theme, BOOL bIsDarkTheme)
{
	BOOL bIsOffice2013Look = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY);
	BOOL bIsOffice2016Look = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK);

	if (bIsOffice2013Look || bIsOffice2016Look)
	{
		if (theApp.m_nBackgroundImage != 0)
		{
			CBCGPToolBarImages background;
			background.Load(IDR_RIBBON_BACKGROUND1 + theApp.m_nBackgroundImage - 1);
			
			// Make background image darker for Office 2013/2016 Dark theme:
			if (theme == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY)
			{
				background.AddaptColors(RGB(255, 255, 255), RGB(230, 230, 230));
			}
			else if (theme == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY)
			{
				background.AddaptColors(RGB(255, 255, 255), RGB(120, 120, 120));
			}
			else if (bIsDarkTheme)
			{
				background.AddaptColors(RGB(255, 255, 255), RGB(80, 80, 80));
			}
			
			m_wndRibbonBar.SetBackgroundImage(background);
		}
		else
		{
			m_wndRibbonBar.SetBackgroundImage(0);
		}
	}
}
//******************************************************************************************************************
void CMainFrame::OnToolsOptions ()
{
	ShowOptions (0);
}
//******************************************************************************************************************
LRESULT CMainFrame::OnRibbonCustomize (WPARAM wp, LPARAM /*lp*/)
{
	ShowOptions (wp == 0 /* QAT*/ ? 1 : 2);
	return 1;
}
//******************************************************************************************************************
void CMainFrame::ShowOptions (int nPage)
{
	// Create "Customize QAT" page:
	CBCGPRibbonCustomizeQATPage pageCustomizeQAT (&m_wndRibbonBar);
	pageCustomizeQAT.EnableKeyboradCustomization(FALSE);

	// Add "popular" items:
	CList<UINT, UINT> lstPopular;

	lstPopular.AddTail (ID_FILE_NEW);
	lstPopular.AddTail (ID_FILE_OPEN);
	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_FILE_PRINT_PREVIEW);
	lstPopular.AddTail (ID_FILE_PRINT_DIRECT);
	lstPopular.AddTail (ID_FILE_SEND_EMAIL);

	lstPopular.AddTail (ID_EDIT_UNDO);

	lstPopular.AddTail (ID_PAGELAYOUT_PAGEBACKGROUND_PAGEBORDERS);

	lstPopular.AddTail (ID_TABLE_DRAWTABLE);
	lstPopular.AddTail (ID_INSERT_HYPERLINK);
	lstPopular.AddTail (ID_INSERT_PICTURE);

	pageCustomizeQAT.AddCustomCategory (_T("Popular Commands"), lstPopular);

	// Add hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);

	pageCustomizeQAT.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);

	// Add all commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);

	pageCustomizeQAT.AddCustomCategory (_T("All Commands"), lstAll);

	pageCustomizeQAT.SetControlInfoTip(IDC_BCGBARRES_QAT_COMMANDS_LIST, _T("Quick Access Toolbar\nCommands added to the quick access toolbar are always one click away. Use this list to add, remove, and reorder commands."));
	pageCustomizeQAT.SetControlInfoTip(IDC_BCGBARRES_RESET, _T("Reset Default Settings\nDelete all customizations and reset default settings for this program."), DT_VCENTER);

	// Create "Customize Ribbon" page:
	CBCGPRibbonCustomizeRibbonPage pageCustomizeRibbon(&m_wndRibbonBar);

	pageCustomizeRibbon.AddCustomCategory (_T("Popular Commands"), lstPopular);
	pageCustomizeRibbon.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);
	pageCustomizeRibbon.AddCustomCategory (_T("All Commands"), lstAll);

	pageCustomizeRibbon.SetControlInfoTip(IDD_BCGBAR_RES_LABEL1, _T("Customize the Ribbon\nUse this list to add, remove, rename, and reorder tabs, groups and commands."));
	pageCustomizeRibbon.SetControlInfoTip(IDC_BCGBARRES_RESET, _T("Reset Default Settings\nDelete all customizations and reset default settings for this program."), DT_VCENTER);

	// Create "Options" and "Resources" pages:
	COptionsPage pageOptions;
	CResourcePage pageRes;

	// Create property sheet:
	COptionsPropSheet propSheet (this, nPage);
	propSheet.EnablePageHeader (max (60, globalData.GetTextHeight () * 3));
	propSheet.EnableLayout(TRUE, NULL, TRUE);

	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	propSheet.EnableVisualManagerStyle(TRUE, TRUE);
	propSheet.SetLook (CBCGPPropertySheet::PropSheetLook_List, -1);

	propSheet.AddPage (&pageOptions);
	propSheet.AddPage (&pageCustomizeQAT);
	propSheet.AddPage (&pageCustomizeRibbon);
	propSheet.AddPage (&pageRes);

	if (propSheet.DoModal() != IDOK)
	{
		return;
	}

	m_wndRibbonBar.EnableToolTips (theApp.m_bShowToolTips, theApp.m_bShowToolTipDescr);
	m_wndRibbonBar.EnableKeyTips (theApp.m_bShowKeyTips);
	m_wndRibbonBar.SetBackstagePageTransitionEffect(theApp.m_bIsRTL ? CBCGPPageTransitionManager::BCGPPageTransitionNone : theApp.m_PageTransitionEffect);
}
//******************************************************************************************************************
void CMainFrame::OnWriteClipboard () 
{
	m_wndClipboardPane.ShowControlBar (!m_wndClipboardPane.IsVisible (), FALSE, TRUE);
}
//******************************************************************************************************************
void CMainFrame::OnUpdateWriteClipboard(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pPrintPreviewFrame == NULL);
}
//******************************************************************************************************************
void CMainFrame::OnViewRtl() 
{
	theApp.m_bIsRTL = !theApp.m_bIsRTL;

	m_wndRibbonBar.SetBackstagePageTransitionEffect(theApp.m_bIsRTL ? CBCGPPageTransitionManager::BCGPPageTransitionNone : theApp.m_PageTransitionEffect);

	OnChangeLayout ();

	CRect rectWindow;
	GetWindowRect (rectWindow);
	
	SetWindowPos (NULL,
			-1, -1,
			rectWindow.Width () + 1, rectWindow.Height (),
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
	
	SetWindowPos (NULL,
			-1, -1,
			rectWindow.Width (), rectWindow.Height (),
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);

	m_wndClipboardPane.AdjustControlsLayout();
}
//******************************************************************************************************************
void CMainFrame::OnUpdateViewRtl(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (theApp.m_bIsRTL);
}
//******************************************************************************************************************
void CMainFrame::OnChangeLayout (CWnd* pWnd/* = NULL*/, BOOL bNoLoopOverPopup/* = FALSE*/)
{
	BOOL bTopLevel = FALSE;

	if (pWnd == NULL)
	{
		pWnd = this;
		bTopLevel = TRUE;
	}

	if (pWnd->IsKindOf (RUNTIME_CLASS (CRichEditView)) ||
		pWnd->IsKindOf (RUNTIME_CLASS (CRichEditCtrl)) ||
		pWnd->IsKindOf (RUNTIME_CLASS (CBCGPChartCtrl)))
	{
		return;
	}

	if (theApp.m_bIsRTL)
	{
		pWnd->ModifyStyleEx (0, WS_EX_LAYOUTRTL);
	}
	else
	{
		pWnd->ModifyStyleEx (WS_EX_LAYOUTRTL, 0);
	}

	CWnd* pWndChild = pWnd->GetWindow (GW_CHILD);
	while (pWndChild != NULL)
	{
		OnChangeLayout (pWndChild, TRUE);
		pWndChild = pWndChild->GetNextWindow ();
	}

	if (!bNoLoopOverPopup)
	{
		CWnd* pWndPopup = pWnd->GetWindow (GW_HWNDFIRST);
		while (pWndPopup != NULL)
		{
			if (pWndPopup->IsKindOf (RUNTIME_CLASS (CBCGPMiniFrameWnd)))
			{
				OnChangeLayout (pWndPopup, TRUE);
				pWndPopup->RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
			}
			pWndPopup = pWndPopup->GetNextWindow ();
		}
	}

	if (bTopLevel)
	{
		CBCGPToolBarImages::EnableRTL (theApp.m_bIsRTL);

		CBCGPToolBar::GetImages ()->Mirror ();
		CBCGPMenuImages::CleanUp ();

		theApp.SetVisualTheme(theApp.GetVisualTheme());
	}
}
//******************************************************************************************************************
void CMainFrame::OnLink()
{
	CBCGPRibbonHyperlink* pLink = (CBCGPRibbonHyperlink*) m_wndStatusBar.FindByID (ID_STATUSBAR_LINK);

	if (pLink != NULL)
	{
		pLink->OpenLink ();
	}
}
//******************************************************************************************************************
LRESULT CMainFrame::OnHighlightRibbonListItem (WPARAM wp, LPARAM lp)
{
	int nIndex = (int) wp;

	CBCGPBaseRibbonElement* pElem = (CBCGPBaseRibbonElement*) lp;
	ASSERT_VALID (pElem);

	UINT uiCommand = pElem->GetID ();

	if (nIndex < 0)
	{
		m_wndStatusBar.SetInformation (NULL);
		return 0;
	}

	CString strInfo;

	switch (uiCommand)
	{
	case ID_WRITE_QUICKSTYLES:
		strInfo.Format (_T("Modify document style. Index: %d - %s"), nIndex, (LPCTSTR)m_arStyles [nIndex]);
		break;

	case ID_FONT_FONT:
		{
			CBCGPRibbonFontComboBox* pFontCombo = (CBCGPRibbonFontComboBox*) pElem;
			strInfo.Format (_T("Changing selection font: %s"), (LPCTSTR)pFontCombo->GetItem (nIndex));
		}
		break;

	case ID_FONT_COLOR:
		{
			CBCGPRibbonColorButton* pColorButton = (CBCGPRibbonColorButton*) pElem;
			COLORREF color = pColorButton->GetHighlightedColor ();

			strInfo.Format (_T("Changing selection color: %02X,%02X,%02X"), 
				GetRValue (color), GetGValue (color), GetBValue (color));
		}
		break;

	case ID_INSERT_TABLE:
		{
			strInfo.Format (_T("Insert Table: %d x %d"), 
				CRibbonTableButton::GetColumns (), 
				CRibbonTableButton::GetRows ());
		}
		break;

	case ID_PAGELAYOUT_THEMES:
		{
			strInfo.Format (_T("Changing theme: %d"), nIndex);
		}
		break;

	case ID_VIEW_APPLOOK_2007_5:
		strInfo = _T("Setting custom color");
		break;

	default:
		return 0;
	}

	m_wndStatusBar.SetInformation (strInfo);
	return 0;
}
//******************************************************************************************************************
void CMainFrame::OnViewMessageBar()
{
	ShowControlBar (&m_wndMessageBar,
					!(m_wndMessageBar.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}
//******************************************************************************************************************
void CMainFrame::OnUpdateViewMessageBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_wndMessageBar.IsVisible ());
}
//******************************************************************************************************************
void CMainFrame::OnViewChartPane()
{
	ShowControlBar (&m_wndChartPane,
					!(m_wndChartPane.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}
//******************************************************************************************************************
void CMainFrame::OnUpdateViewChartPane(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_wndChartPane.IsVisible ());
}
//******************************************************************************************************************
void CMainFrame::OnViewGridPane()
{
	ShowControlBar (&m_wndGridPane,
					!(m_wndGridPane.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}
//******************************************************************************************************************
void CMainFrame::OnUpdateViewGridPane(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_wndGridPane.IsVisible ());
}
//******************************************************************************************************************
LRESULT CMainFrame::OnShowRibbonItemMenu(WPARAM /*wp*/, LPARAM lp)
{
	CBCGPBaseRibbonElement* pElem = (CBCGPBaseRibbonElement*) lp;
	ASSERT_VALID (pElem);

	switch (pElem->GetID ())
	{
	case ID_EDIT_UNDO:
		// Fill Undo items list:
		{
			CBCGPRibbonUndoButton* pUndo = DYNAMIC_DOWNCAST (CBCGPRibbonUndoButton, pElem);
			ASSERT_VALID (pUndo);

			pUndo->CleanUpUndoList ();

			pUndo->AddUndoAction (_T("Undo Item 1"));
			pUndo->AddUndoAction (_T("Undo Item 2"));
			pUndo->AddUndoAction (_T("Undo Item 3"));
			pUndo->AddUndoAction (_T("Undo Item 4"));
			pUndo->AddUndoAction (_T("Undo Item 5"));
		}
		break;

	case ID_PARA_BULLETS:
		// Rebuild "Recently used bullets" group:
		{
			CBCGPRibbonPaletteButton* pPaletteButton = DYNAMIC_DOWNCAST (
				CBCGPRibbonPaletteButton, pElem);
			ASSERT_VALID (pPaletteButton);

			pPaletteButton->Clear ();

			// Load all bullets:
			CBCGPToolBarImages imagesAll;
			imagesAll.SetImageSize (CSize (40, 40));
			imagesAll.Load (IDB_BULLETS);
			globalUtils.ScaleByDPI(imagesAll);

			// Create "Recently used bullets" group:
			CBCGPToolBarImages imagesRU;
			imagesRU.SetImageSize (imagesAll.GetImageSize ());

			imagesRU.AddIcon (imagesAll.ExtractIcon (1));
			imagesRU.AddIcon (imagesAll.ExtractIcon (7));

			pPaletteButton->AddGroup (_T("Recently Used Bullets"), imagesRU);

			// Add all bullets group:
			pPaletteButton->AddGroup (_T("Bullets"), imagesAll);

			if (m_bIsDarkTheme)
			{
				pPaletteButton->GetImages().InvertColors();
			}
		}
		break;

	case ID_EDIT_PASTE:
		{
			CBCGPRibbonPaletteButton* pBtnPaste = DYNAMIC_DOWNCAST(CBCGPRibbonPaletteButton, pElem);
			if (pBtnPaste != NULL)
			{
				ASSERT_VALID (pBtnPaste);
				InitPastePalette(pBtnPaste);				
			}
		}
		break;

	case ID_FONT_COLOR:
	case ID_PARA_SHADING:
		// Set document text colors:
		{
			CBCGPRibbonColorButton* pColorBtn = DYNAMIC_DOWNCAST (
				CBCGPRibbonColorButton, pElem);
			ASSERT_VALID (pColorBtn);

			CList<COLORREF,COLORREF> lstColors;

			lstColors.AddTail (RGB (108, 154, 233));
			lstColors.AddTail (RGB (18, 159, 126));
			lstColors.AddTail (RGB (223, 149, 1));
			lstColors.AddTail (RGB (192, 255, 0));

			pColorBtn->SetDocumentColors (_T("Recent Colors"), lstColors);
		}
		break;
	}

	return 0;
}
//******************************************************************************************************************
void CMainFrame::OnDummy (UINT /*id*/)
{
}
//******************************************************************************************************************
void CMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CBCGPFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar->GetSafeHwnd () == m_wndScrollBar.GetSafeHwnd () &&
		(nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK))
	{
		((CBCGPMSOfficeDemoView*)GetActiveView ())->ScrollTo (nPos);
	}
}
//******************************************************************************************************************
void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (IsPrintPreview ());
}
//******************************************************************************************************************
void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview ())
	{
		PostMessage (WM_COMMAND, AFX_ID_PREVIEW_CLOSE);	// Force Print Preview Close
	}
}
//******************************************************************************************************************
void CMainFrame::OnFilePrint ()
{
	if (IsPrintPreview ())
	{
		PostMessage (WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}
//******************************************************************************************************************
void CMainFrame::OnClipboardPasteAll() 
{
	// TODO: Add your control notification handler code here
	
}
//******************************************************************************************************************
void CMainFrame::OnClipboardClearAll() 
{
	// TODO: Add your control notification handler code here
	
}
//******************************************************************************************************************
void CMainFrame::OnClipboardOption1()
{
}
//******************************************************************************************************************
void CMainFrame::OnClipboardOption2()
{
}
//******************************************************************************************************************
LRESULT CMainFrame::OnCustomizeGalleryContextMenu(WPARAM wp, LPARAM lp)
{
	const CBCGPBaseRibbonElement* pHit = (const CBCGPBaseRibbonElement*) lp;
	ASSERT_VALID (pHit);

	CBCGPRibbonPaletteIcon* pIcon = DYNAMIC_DOWNCAST (CBCGPRibbonPaletteIcon, pHit);
	if (pIcon == NULL)
	{
		return 0;
	}

	ASSERT_VALID (pIcon);

	const int nID = pIcon->GetQATID ();
	const int nIndex = pIcon->GetIndex ();

	CMenu* pMenu = CMenu::FromHandle ((HMENU) wp);
	ASSERT_VALID (pMenu);

	if (nID == ID_WRITE_QUICKSTYLES)
	{
		if (nIndex >= 0 && nIndex < m_arStyles.GetSize ())
		{
			CString strItem;
			strItem.Format (_T("Update %s to M&atch Selection"), (LPCTSTR)m_arStyles [nIndex]);

			pMenu->AppendMenu (MF_STRING, ID_DUMMY, strItem);
		}

		pMenu->AppendMenu (MF_STRING, ID_DUMMY, _T("Modify..."));
		pMenu->AppendMenu (MF_STRING | MF_DISABLED, ID_DUMMY, _T("Select All (Not Currently Used)"));
	}
	else if (nID == ID_FONT_COLOR || 
			nID == ID_FONT_TEXTHIGHLIGHT || 
			nID == ID_PAGELAYOUT_PAGEBACKGROUND_PAGECOLOR ||
			nID == ID_PARA_SHADING)
	{
		CBCGPRibbonColorButton* pColorPicker = DYNAMIC_DOWNCAST (CBCGPRibbonColorButton, pIcon->GetOwner ());
		if (pColorPicker != NULL)
		{
			ASSERT_VALID (pColorPicker);

			if ((m_clrHighlighted = pColorPicker->GetHighlightedColor ()) != (COLORREF)-1)
			{
				pMenu->AppendMenu (MF_STRING, ID_COPY_COLOR, _T("Copy Highlighted Color to Clipboard"));
			}
		}
	}

	return 0;
}
//******************************************************************************************************************
void CMainFrame::OnCopyColor()
{
	if (m_clrHighlighted == (COLORREF)-1)
	{
		return;
	}

#ifdef _UNICODE
	#define _TCF_TEXT	CF_UNICODETEXT
#else
	#define _TCF_TEXT	CF_TEXT
#endif

	if (OpenClipboard ())
	{
		EmptyClipboard ();

		CString strText;
		strText.Format (_T("RGB (%d, %d, %d) "),
			GetRValue (m_clrHighlighted),
			GetGValue (m_clrHighlighted),
			GetBValue (m_clrHighlighted));

		HGLOBAL hClipbuffer = ::GlobalAlloc (GMEM_DDESHARE, (strText.GetLength () + 1) * sizeof (TCHAR));
		LPTSTR lpszBuffer = (LPTSTR) GlobalLock (hClipbuffer);

		lstrcpy (lpszBuffer, (LPCTSTR) strText);

		::GlobalUnlock (hClipbuffer);
		::SetClipboardData (_TCF_TEXT, hClipbuffer);

		CloseClipboard();
	}
}
//******************************************************************************************************************
LRESULT CMainFrame::OnClickCaptionbarHyperlink(WPARAM, LPARAM)
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
	return 0;
}
//******************************************************************************************************************
void CMainFrame::OnViewFullScreen() 
{
	ShowFullScreen ();
}
//******************************************************************************************************************
void CMainFrame::OnInputMode() 
{
	 // Empty handler for enabling menu
}
//******************************************************************************************************************
void CMainFrame::OnInputMouse() 
{
	SetInputMode(BCGP_MOUSE_INPUT);
}
//******************************************************************************************************************
void CMainFrame::OnInputTouch() 
{
	SetInputMode(BCGP_TOUCH_INPUT);
}
//******************************************************************************************************************
void CMainFrame::OnUpdateInputMouse(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetInputMode() == BCGP_MOUSE_INPUT);
}
//******************************************************************************************************************
void CMainFrame::OnUpdateInputTouch(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetInputMode() == BCGP_TOUCH_INPUT);
}
//******************************************************************************************************************
LRESULT CMainFrame::OnBeforeShowRibbonBackstageView(WPARAM, LPARAM)
{
	theApp.CreateScreenshot(m_bmpAppPreview);
	return 0;
}
//******************************************************************************************************************
void CMainFrame::OnSysColorChange()
{
	CBCGPFrameWnd::OnSysColorChange();
	
	if (m_MemBitmap.GetSafeHandle () != NULL)
	{
		m_MemBitmap.DeleteObject ();
	}

	SetBackgroundImage(theApp.GetVisualTheme(), m_bIsDarkTheme);
}
//******************************************************************************************************************
LRESULT CMainFrame::OnGetRibbonCommandsMenuCustomItems(WPARAM /*wp*/, LPARAM lp)
{
	CBCGPRibbonCommandsMenuCustomItems* pItems = (CBCGPRibbonCommandsMenuCustomItems*)lp;
	ASSERT(pItems != NULL);

	CString strHelpItem;
	strHelpItem.Format(_T("Get Help on \"%s...\""), (LPCTSTR)pItems->m_strInput);

	HICON hIcon = m_wndRibbonBar.ExportImageToIcon(ID_APP_ABOUT, FALSE);
	pItems->m_arCustomItems.Add(new CBCGPRibbonButton(ID_SEARCH_COMMANDS_HELP, hIcon, strHelpItem, TRUE, TRUE));

	return 0;
}
//******************************************************************************************************************
void CMainFrame::OnSearchHelp()
{
	BCGPMessageBox(_T("Display help information here..."));
}
