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
// OptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "OptionsPage.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COptionsPropSheet::COptionsPropSheet (CWnd* pWndParent, UINT nSelectedPage) :
		CBCGPPropertySheet (_T("Options"), pWndParent, nSelectedPage)
{
	m_Icons.SetImageSize (CSize (32, 32));
	m_Icons.Load (IDB_OPTIONS);
	globalUtils.ScaleByDPI(m_Icons);

	CBCGPControlRendererParams params((UINT)0, CLR_DEFAULT, 
		CRect (0, 0, 350, 60), CRect (83, 58, 266, 1), 
		CRect (0, 0, 0, 0), CRect (0, 0, 0, 0), FALSE);

	params.m_uiBmpResID = IDB_HEADERPAT_1;
	m_Pat[0].Create (params);
	params.m_uiBmpResID = IDB_HEADERPAT_2;
	m_Pat[1].Create (params);
	params.m_uiBmpResID = IDB_HEADERPAT_3;
	m_Pat[2].Create (params);
	params.m_uiBmpResID = IDB_HEADERPAT_4;
	m_Pat[3].Create (params);
	
	EnableVisualManagerStyle(TRUE, TRUE);
}

BOOL COptionsPropSheet::OnInitDialog() 
{
	if (theApp.m_bIsRTL)
	{
		ModifyStyleEx (0, WS_EX_LAYOUTRTL);
	}

	return CBCGPPropertySheet::OnInitDialog();
}

void COptionsPropSheet::OnDrawPageHeader (CDC* pDC, int nPage, CRect rectHeader)
{
	CSize sizeIcon = m_Icons.GetImageSize ();

	CBCGPControlRenderer* pRenderer = NULL;

	switch (theApp.GetVisualTheme())
	{
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLUE:
		pRenderer = &m_Pat[1];
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLACK:
		pRenderer = &m_Pat[2];
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_AQUA:
		pRenderer = &m_Pat[0];
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_SILVER:
		pRenderer = &m_Pat[3];
		break;
	}

	if (pRenderer != NULL)
	{
		pRenderer->Draw (pDC, rectHeader);
	}

	rectHeader.bottom -= 10;

	CRect rectIcon = rectHeader;
	
	rectIcon.left += 20;
	rectIcon.right = rectIcon.left + sizeIcon.cx;

	CString strText;

	int nIcon = 0;

	switch (nPage)
	{
	case 0:
		strText = _T("General options for working with Demo");
		nIcon = 0;
		break;

	case 1:
		strText = _T("Customize the Quick Access Toolbar");
		nIcon = 1;
		break;

	case 2:
		strText = _T("Customize the Ribbon and keyboard shortcuts");
		nIcon = 1;
		break;

	case 3:
		strText = _T("Contact BCGSoft, find online resources and obtain additional information regarding our products and services");
		nIcon = 2;
		break;
	}

	m_Icons.DrawEx (pDC, rectIcon, nIcon, CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertCenter);

	CRect rectText = rectHeader;
	rectText.left = rectIcon.right + 10;
	rectText.right -= 20;

	CFont* pOldFont = pDC->SelectObject (&globalData.fontBold);
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(CBCGPVisualManager::GetInstance()->GetDlgTextColor(this));

	UINT uiFlags = DT_SINGLELINE | DT_VCENTER;

	CRect rectTextCalc = rectText;
	pDC->DrawText (strText, rectTextCalc, uiFlags | DT_CALCRECT);

	if (rectTextCalc.right > rectText.right)
	{
		rectText.DeflateRect (0, 10);
		uiFlags = DT_WORDBREAK;
	}

	pDC->DrawText (strText, rectText, uiFlags);

	pDC->SelectObject (pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// COptionsPage property page

IMPLEMENT_DYNCREATE(COptionsPage, CBCGPPropertyPage)

COptionsPage::COptionsPage() : CBCGPPropertyPage(COptionsPage::IDD),
	m_wndColor (TRUE),
	m_wndAppButtonColor(TRUE)
{
	//{{AFX_DATA_INIT(COptionsPage)
	m_nColorScheme = -1;
	m_nTooltipStyle = -1;
	m_bShowFloaty = theApp.m_bShowFloaty;
	m_bShowKeyTips = theApp.m_bShowKeyTips;
	m_nAccentColor = theApp.m_nAccentColorIndex + 1;
	m_nBackgroundImage = theApp.m_nBackgroundImage;
	m_nPageTransitionEffect = theApp.m_PageTransitionEffect;
	//}}AFX_DATA_INIT

	if (!theApp.m_bShowToolTips)
	{
		m_nTooltipStyle = 2;
	}
	else
	{
		m_nTooltipStyle = theApp.m_bShowToolTipDescr ? 0 : 1;
	}

	switch (theApp.GetVisualTheme())
	{
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLUE:
		m_nColorScheme = 0;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLACK:
		m_nColorScheme = 1;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_AQUA:
		m_nColorScheme = 2;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_SILVER:
		m_nColorScheme = 3;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_CUSTOM:
		m_nColorScheme = 4;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_SCENIC:
		m_nColorScheme = 5;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLUE:
		m_nColorScheme = 6;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_SILVER:
		m_nColorScheme = 7;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLACK:
		m_nColorScheme = 8;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE:
		m_nColorScheme = 9;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_GRAY:
		m_nColorScheme = 10;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY:
		m_nColorScheme = 11;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL:
		m_nColorScheme = 12;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY:
		m_nColorScheme = 13;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_WHITE:
		m_nColorScheme = 14;
		break;
	case CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK:
		m_nColorScheme = 15;
		break;
	}
}

COptionsPage::~COptionsPage()
{
}

void COptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPage)
	DDX_Control(pDX, IDC_BACKGROUND_IMAGE, m_wndBackgroundImage);
	DDX_Control(pDX, IDC_ACCENT_COLOR, m_wndAccentColor);
	DDX_Control(pDX, IDC_APP_BUTTON_COLOR, m_wndAppButtonColor);
	DDX_Control(pDX, IDC_CUSTOM_COLOR, m_wndColor);
	DDX_Control(pDX, IDC_BANER, m_wndBanner);
	DDX_Control(pDX, IDC_COLOR_SCHEME, m_wndColorScheme);
	DDX_CBIndex(pDX, IDC_COLOR_SCHEME, m_nColorScheme);
	DDX_CBIndex(pDX, IDC_SCREENTIP_STYLE, m_nTooltipStyle);
	DDX_Check(pDX, IDC_SHOW_FLOATY, m_bShowFloaty);
	DDX_Check(pDX, IDC_SHOW_KEY_TIPS, m_bShowKeyTips);
	DDX_CBIndex(pDX, IDC_ACCENT_COLOR, m_nAccentColor);
	DDX_CBIndex(pDX, IDC_BACKGROUND_IMAGE, m_nBackgroundImage);
	DDX_CBIndex(pDX, IDC_PAGE_TRANSITION_EFFECT_LIST, m_nPageTransitionEffect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPage, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(COptionsPage)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COLOR_SCHEME, OnSelchangeColorScheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPage message handlers

void COptionsPage::OnOK() 
{
	UpdateData ();

	theApp.m_bShowFloaty = m_bShowFloaty;

	if (m_nColorScheme == 4)
	{
		theApp.m_clrCustom = m_wndColor.GetColor ();
	}
	else if (m_nColorScheme >= 6 && m_nColorScheme <= 8)
	{
		theApp.m_clrAppButton = m_wndAppButtonColor.GetColor ();
	}
	else if (m_nColorScheme >= 9 && m_nColorScheme <= 15)
	{
		theApp.m_nAccentColorIndex = m_nAccentColor - 1;
		theApp.m_nBackgroundImage = m_nBackgroundImage;
	}

	switch (m_nColorScheme)
	{
	case 0:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLUE);
		break;
	case 1:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLACK);
		break;
	case 2:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_AQUA);
		break;
	case 3:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_SILVER);
		break;
	case 4:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_CUSTOM);
		break;
	case 5:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_SCENIC);
		break;
	case 6:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLUE);
		break;
	case 7:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_SILVER);
		break;
	case 8:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLACK);
		break;
	case 9:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE);
		break;
	case 10:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_GRAY);
		break;
	case 11:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY);
		break;
	case 12:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL);
		break;
	case 13:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY);
		break;
	case 14:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_WHITE);
		break;
	case 15:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK);
		break;
	}
	
	theApp.m_bShowKeyTips = m_bShowKeyTips;

	switch (m_nTooltipStyle)
	{
	case 0:
		theApp.m_bShowToolTips = TRUE;
		theApp.m_bShowToolTipDescr = TRUE;
		break;

	case 1:
		theApp.m_bShowToolTips = TRUE;
		theApp.m_bShowToolTipDescr = FALSE;
		break;

	case 2:
		theApp.m_bShowToolTips = FALSE;
		theApp.m_bShowToolTipDescr = FALSE;
		break;
	}
	
	theApp.m_PageTransitionEffect = (CBCGPPageTransitionManager::BCGPPageTransitionEffect)m_nPageTransitionEffect;

	CBCGPPropertyPage::OnOK();
}

BOOL COptionsPage::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();

	SetControlInfoTip(IDC_SHOW_FLOATY, _T("Show Mini Toolbar on selection\nShow the Mini Toolbar when you select text\n\nThe Mini Toolbar provides quick access to formatting tools."));

	OnSelchangeColorScheme ();
	
	m_wndColor.SetColor (theApp.m_clrCustom);
	m_wndColor.EnableAutomaticButton (_T("&Automatic"), theApp.m_clrCustomDef, TRUE);

	m_wndColor.GetRibbonButton ().SetColumns (10);
	m_wndColor.GetRibbonButton ().SetColorBoxSize (CSize (17, 17));
	m_wndColor.GetRibbonButton ().EnableAutomaticButton (_T("&Automatic"), theApp.m_clrCustomDef, TRUE, _T("Automatic"));
	m_wndColor.GetRibbonButton ().EnableOtherButton (_T("&More Colors..."), _T("More Colors"));
	m_wndColor.GetRibbonButton ().AddColorsGroup (_T("Presets"), theApp.m_lstCustomColors);

	m_wndAppButtonColor.SetColor (theApp.m_clrAppButton);
	m_wndAppButtonColor.EnableAutomaticButton (_T("&Default"), (COLORREF)-1, TRUE);

	m_wndAppButtonColor.GetRibbonButton ().SetColumns (10);
	m_wndAppButtonColor.GetRibbonButton ().SetColorBoxSize (CSize (17, 17));
	m_wndAppButtonColor.GetRibbonButton ().EnableAutomaticButton (_T("&Default"), (COLORREF)-1, TRUE, _T("Default"));
	m_wndAppButtonColor.GetRibbonButton ().EnableOtherButton (_T("&More Colors..."), _T("More Colors"));
	m_wndAppButtonColor.GetRibbonButton ().AddColorsGroup (_T("Presets"), theApp.m_lstAppButtonColors);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsPage::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPPropertyPage::OnSize(nType, cx, cy);
	
	if (m_wndBanner.GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectBanner;
	m_wndBanner.GetWindowRect (rectBanner);

	CRect rectParent;
	GetParent ()->GetWindowRect (rectParent);

	m_wndBanner.SetWindowPos (NULL, -1, -1, 
		rectParent.right - rectBanner.left - 10, rectBanner.Height (),
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COptionsPage::OnSelchangeColorScheme() 
{
	UpdateData ();

	const BOOL bOffice2007CustomColorTheme = (m_nColorScheme == 4);

	m_wndColor.EnableWindow(bOffice2007CustomColorTheme);
	SetControlInfoTip(&m_wndColor, bOffice2007CustomColorTheme ? NULL : _T("Office 2007 Custom\nPlease choose \"Office 2007 Custom\" to enable this control."), DT_VCENTER, TRUE);

	m_wndAppButtonColor.EnableWindow (m_nColorScheme >= 6 && m_nColorScheme <= 8); // Office 2010
	m_wndAccentColor.EnableWindow(m_nColorScheme >= 9 && m_nColorScheme <= 15); // Office 2013/2016
	m_wndBackgroundImage.EnableWindow(m_nColorScheme >= 9 && m_nColorScheme <= 15);	// Office 2013/2016
}
