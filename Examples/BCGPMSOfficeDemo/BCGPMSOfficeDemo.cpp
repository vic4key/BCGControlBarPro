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
// BCGPMSOfficeDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"

#include "MainFrm.h"
#include "BCGPMSOfficeDemoDoc.h"
#include "BCGPMSOfficeDemoView.h"
#include "RibbonTooltipCtrl.h"
#include "Codes/TestDialog.h"
#include "Codes/RibbonOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoApp

BEGIN_MESSAGE_MAP(CBCGPMSOfficeDemoApp, CBCGPWinApp)
	//{{AFX_MSG_MAP(CBCGPMSOfficeDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CBCGPWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CBCGPWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CBCGPWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoApp construction

CBCGPMSOfficeDemoApp::CBCGPMSOfficeDemoApp()
{
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_BLUE, ID_VIEW_APPLOOK_2007_1);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_BLACK, ID_VIEW_APPLOOK_2007_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_AQUA, ID_VIEW_APPLOOK_2007_3);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_SILVER, ID_VIEW_APPLOOK_2007_4);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_BLUE, ID_VIEW_APPLOOK_2010_1);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_SILVER, ID_VIEW_APPLOOK_2010_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_BLACK, ID_VIEW_APPLOOK_2010_3);
	AddVisualTheme(BCGP_VISUAL_THEME_SCENIC, ID_VIEW_APPLOOK_WIN7);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_WHITE, ID_VIEW_APPLOOK_2013_1);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_GRAY, ID_VIEW_APPLOOK_2013_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY, ID_VIEW_APPLOOK_2013_3);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL, ID_VIEW_APPLOOK_2016_1, TRUE);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2016_WHITE, ID_VIEW_APPLOOK_2016_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY, ID_VIEW_APPLOOK_2016_3);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2016_BLACK, ID_VIEW_APPLOOK_2016_4);
	AddVisualTheme(BCGP_VISUAL_THEME_CUSTOM, ID_VIEW_APPLOOK_2007_5);
	
	m_bShowFloaty = TRUE;
	m_bShowToolTips = TRUE;
	m_bShowKeyTips = TRUE;
	m_bDontShowPaneCloseMessage = FALSE;
	m_bShowToolTipDescr = TRUE;

	// Init custom theme colors:
	m_lstCustomColors.AddTail (RGB (210, 240, 179));
	m_lstCustomColors.AddTail (RGB (151, 192, 234));
	m_lstCustomColors.AddTail (RGB (203, 160, 224));
	m_lstCustomColors.AddTail (RGB (223, 159, 191));
	m_lstCustomColors.AddTail (RGB (243, 224, 185));
	m_lstCustomColors.AddTail (RGB (190, 178, 240));
	m_lstCustomColors.AddTail (RGB (232, 232, 216));
	m_lstCustomColors.AddTail (RGB (247, 218, 214));
	m_lstCustomColors.AddTail (RGB (189, 231, 224));
	m_lstCustomColors.AddTail (RGB (214, 234, 218));

	m_clrCustomDef = RGB (193, 223, 192);
	m_clrCustom = (COLORREF)-1;

	// Init application button custom colors:
	m_clrAppButton = (COLORREF)-1;

	m_nAccentColorIndex = 0;
	m_nBackgroundImage = 1;

	m_lstAppButtonColors.AddTail(RGB(0, 192, 0));
	m_lstAppButtonColors.AddTail(RGB(192, 0, 0));
	m_lstAppButtonColors.AddTail(RGB(0, 0, 192));
	m_lstAppButtonColors.AddTail(RGB(192, 0, 192));
	m_lstAppButtonColors.AddTail(RGB(192, 192, 0));

	m_PageTransitionEffect = CBCGPPageTransitionManager::BCGPPageTransitionNone;

	globalData.m_bUseVisualManagerInBuiltInDialogs = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPMSOfficeDemoApp object

CBCGPMSOfficeDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoApp initialization

BOOL CBCGPMSOfficeDemoApp::InitInstance()
{
	CBCGPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Examples"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings232"));

	// Load options:
	m_bShowFloaty = GetInt (_T("ShowFloaty"), TRUE);
	
	m_bShowToolTips = GetInt (_T("ShowToolTips"), TRUE);
	m_bShowKeyTips = GetInt (_T("ShowKeyTips"), TRUE);
	m_bShowToolTipDescr = GetInt (_T("bShowToolTipDescr"), TRUE);
	m_bIsRTL = GetInt (_T("IsRTL"), FALSE);
	m_nAccentColorIndex = GetInt(_T("AccentColorIndex"), 0);
	m_nBackgroundImage = GetInt(_T("BackgroundImage"), 1);
	m_PageTransitionEffect = (CBCGPPageTransitionManager::BCGPPageTransitionEffect)GetInt(_T("PageTransitionEffect"), 7);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CRibbonTooltipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPMSOfficeDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPMSOfficeDemoView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	GetContextMenuManager()->AddMenu (_T("Context menu"), IDR_CONTEXT_MENU);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);

	CRect rect;
	m_pMainWnd->GetWindowRect (rect);

	m_pMainWnd->SetWindowPos (NULL, -1, -1, rect.Width (), rect.Height (), SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	m_pMainWnd->UpdateWindow();

	if (globalData.m_nBitsPerPixel < 16)
	{
		AfxMessageBox (_T("The current display settings will not allow this application to display itself properly.\r\nPlease change the display color setting to 'Highest (32 bit)' and run this application again"));
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoApp message handlers

int CBCGPMSOfficeDemoApp::ExitInstance() 
{
	// Save options:
	WriteInt (_T("ShowFloaty"), m_bShowFloaty);
	WriteInt (_T("ShowToolTips"), m_bShowToolTips);
	WriteInt (_T("ShowKeyTips"), m_bShowKeyTips);
	WriteInt (_T("bShowToolTipDescr"), m_bShowToolTipDescr);
	WriteInt (_T("IsRTL"), m_bIsRTL);
	WriteInt (_T("AccentColorIndex"), m_nAccentColorIndex);
	WriteInt (_T("BackgroundImage"), m_nBackgroundImage);
	WriteInt(_T("PageTransitionEffect"), m_PageTransitionEffect);

	return CBCGPWinApp::ExitInstance();
}

// App command to run the dialog
void CBCGPMSOfficeDemoApp::OnAppAbout()
{
  //BCGPShowAboutDlg (AFX_IDS_APP_TITLE);

  //TestDialog dialog(m_pMainWnd);
  //dialog.DoModal();

  if (RibbonTabs::Instance().GetTabList().empty())
  {
    if (auto pTab = RibbonTabs::Instance().AddTab(L"Patient Tab"))
    {
      pTab->AddPanel(L"Patient - 0", true, 1);
      pTab->AddPanel(L"Patient - 1", true, 2);
      pTab->AddPanel(L"Patient - 2", true, 3);
      pTab->AddPanel(L"Patient - 3", true, 1);
      pTab->AddPanel(L"Patient - 4", true, 2);
      pTab->AddPanel(L"Patient - 5", true, 3);
    }
    if (auto pTab = RibbonTabs::Instance().AddTab(L"Image Tab"))
    {
      pTab->AddPanel(L"Image - Fiducial Markers", true, 1);
      pTab->AddPanel(L"Image - Patient Origin", false, 2);
      pTab->AddPanel(L"Image - Imaging Center", true, 3);
    }
    if (auto pTab = RibbonTabs::Instance().AddTab(L"Fusion Tab"))
    {
      pTab->AddPanel(L"Fusion - View", false, 1);
      pTab->AddPanel(L"Fusion - Registration", false, 2);
      pTab->AddPanel(L"Fusion - Auto Fiducial Markers", false, 3);
    }
  }

  RibbonOptionsDlg dialog(m_pMainWnd, IDB_BS_HELP_LIST_16);
  dialog.DoModal();
}

void CBCGPMSOfficeDemoApp::OnBeforeChangeVisualTheme(CBCGPAppOptions& appOptions, CWnd* pMainWnd)
{
	CBCGPWinApp::OnBeforeChangeVisualTheme(appOptions, pMainWnd);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, pMainWnd);
	if (pFrame->GetSafeHwnd () != NULL)
	{
		pFrame->OnBeforeChangeVisualTheme(m_ActiveTheme);
	}
}

void CBCGPMSOfficeDemoApp::OnAfterChangeVisualTheme(CWnd* pMainWnd)
{
	CBCGPWinApp::OnAfterChangeVisualTheme(pMainWnd);

	CBCGPDockManager::SetDockMode(BCGP_DT_SMART);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, pMainWnd);
	if (pFrame->GetSafeHwnd () != NULL)
	{
		pFrame->OnAfterChangeVisualTheme(m_ActiveTheme);
	}
}
