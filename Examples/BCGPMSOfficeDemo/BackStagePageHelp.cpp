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
// BackStagePageHelp.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpmsofficedemo.h"
#include "BackStagePageHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBackStageListBox, CBCGPListBox)

CBackStageListBox::CBackStageListBox()
{
	m_bVisualManagerStyle = TRUE;
}

void CBackStageListBox::OnClickItem(int nClickedItem)
{
	CString strURL;

	switch (nClickedItem)
	{
	case 1:
		strURL = _T("http://www.bcgsoft.com/devarea.htm");
		break;

	case 2:
		strURL = _T("http://www.bcgsoft.com/bcgcontrolbarpro.htm");
		break;

	case 3:
		strURL = _T("http://www.bcgsoft.com/contact.htm");
		break;

	case 5:
		AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_TOOLS_OPTIONS);
		break;

	case 6:
		strURL = _T("http://www.bcgsoft.com/news.htm");
		break;
	}

	GetParent()->SendMessage(WM_CLOSE);

	if (!strURL.IsEmpty())
	{
		CWaitCursor wait;
		::ShellExecute (NULL, NULL, strURL, NULL, NULL, NULL);
	}
}

BOOL CBackStageListBox::OnReturnKey()
{
	OnClickItem(GetCurSel());
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageHelp dialog

IMPLEMENT_DYNCREATE(CBackStagePageHelp, CBCGPDialog)

CBackStagePageHelp::CBackStagePageHelp(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CBackStagePageHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackStagePageHelp)
	m_strVersion = _T("");
	m_strYear = _T("");
	//}}AFX_DATA_INIT
	
	EnableLayout();

	m_strVersion.Format (_T("%d.%d"), _BCGCBPRO_VERSION_MAJOR, _BCGCBPRO_VERSION_MINOR);

	CString strCurrDate = _T(__DATE__);
	m_strYear.Format (_T("1998-%s"), (LPCTSTR)strCurrDate.Right (4));

	m_nListMode = -1;
	m_nInitialListWidth = 0;
}


void CBackStagePageHelp::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackStagePageHelp)
	DDX_Control(pDX, IDC_URL, m_wndURL);
	DDX_Control(pDX, IDC_MAIL, m_wndMail);
	DDX_Control(pDX, IDC_LOGO_PLACE_HOLDER, m_wndLogo);
	DDX_Control(pDX, IDC_CAPTION_HOLDER, m_wndCaption);
	DDX_Control(pDX, IDC_HELP_LIST, m_wndList);
	DDX_Text(pDX, IDC_VERSION, m_strVersion);
	DDX_Text(pDX, IDC_YEAR, m_strYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackStagePageHelp, CBCGPDialog)
	//{{AFX_MSG_MAP(CBackStagePageHelp)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageHelp message handlers

BOOL CBackStagePageHelp::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	m_Logo.Load(IDB_LOGO);
	m_Logo.SetSingleImage();
	globalUtils.ScaleByDPI(m_Logo);

	ResetList();

	m_wndURL.m_nAlignStyle = CBCGPButton::ALIGN_LEFT;
	m_wndMail.m_nAlignStyle = CBCGPButton::ALIGN_LEFT;

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor(IDC_HELP_LIST, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
		pLayout->AddAnchor(IDC_SEPARATOR_4, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeVert);
		pLayout->AddAnchor(IDC_LOGO_PLACE_HOLDER, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_CAPTION_HOLDER, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_SEPARATOR_1, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_LABEL_1, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_VERSION, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_LABEL_2, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_YEAR, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_LABEL_3, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_LABEL_4, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_URL, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_LABEL_5, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDC_MAIL, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

static LPCTSTR szItems[] =
{
	_T("BCGControlBar Pro for MFC Help"),
	_T("Getting Started"),
	_T("Contact Us"),
	_T("Options"),
	_T("Check for Updates")
};

static LPCTSTR szDescriptions[] =
{
	_T("Get help using our product."),
	_T("See what's new and find resources to help you learn the basics quickly."),
	_T("Let us know if you need help or how we can make our product better."),
	_T("Customize language, display and other product settings."),
	_T("Get the latest updates available for the product.")
};

void CBackStagePageHelp::ResetList()
{
	int nCurSel = m_wndList.GetCurSel();

	m_wndList.CleanUp();

	CRect rectList;
	m_wndList.GetClientRect(rectList);

	if (m_nInitialListWidth == 0)
	{
		m_nInitialListWidth = rectList.Width();
		m_nListMode = 0;
	}

	CBCGPWinApp::BCGP_VISUAL_THEME theme = theApp.GetVisualTheme();

	BOOL bIsOffice2013Look = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY);
	BOOL bIsOffice2016Look = (theme >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL && theme <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_WHITE);

	BOOL bIsVertMargin = bIsOffice2013Look || bIsOffice2016Look ? FALSE : TRUE;

	switch (m_nListMode)
	{
	case 0:
		m_wndList.SetImageList (IDB_BS_HELP_LIST_16, 16, bIsVertMargin ? 2 : 0, TRUE);
		break;

	case 1:
	case 2:
		m_wndList.SetImageList (IDB_BS_HELP_LIST_32, 32, bIsVertMargin ? 4 : 0, TRUE);
		break;
	}

	m_wndList.EnableItemDescription(m_nListMode > 1);

	m_wndList.AddCaption (_T("Support"));

	m_wndList.AddString (szItems[0]);
	m_wndList.SetItemImage (1, 0);

	m_wndList.AddString (szItems[1]);
	m_wndList.SetItemImage (2, 1);

	m_wndList.AddString (szItems[2]);
	m_wndList.SetItemImage (3, 2);

	m_wndList.AddCaption (_T("Tools"));

	m_wndList.AddString (szItems[3]);
	m_wndList.SetItemImage (5, 3);

	m_wndList.AddString (szItems[4]);
	m_wndList.SetItemImage (6, 4);

	if (m_nListMode > 1)
	{
		m_wndList.SetItemDescription(1, szDescriptions[0]);
		m_wndList.SetItemDescription(2, szDescriptions[1]);
		m_wndList.SetItemDescription(3, szDescriptions[2]);
		m_wndList.SetItemDescription(5, szDescriptions[3]);
		m_wndList.SetItemDescription(6, szDescriptions[4]);
	}
	else
	{
		m_wndList.SetItemToolTip(1, szItems[0], szDescriptions[0]);
		m_wndList.SetItemToolTip(2, szItems[1], szDescriptions[1]);
		m_wndList.SetItemToolTip(3, szItems[2], szDescriptions[2]);
		m_wndList.SetItemToolTip(5, szItems[3], szDescriptions[3]);
		m_wndList.SetItemToolTip(6, szItems[4], szDescriptions[4]);
	}

	m_wndList.SetCurSel(nCurSel);
}

void CBackStagePageHelp::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnDraw(&dc);
}

void CBackStagePageHelp::OnDraw(CDC* pDC)
{
	CRect rectLogo;

	m_wndLogo.GetWindowRect(rectLogo);
	ScreenToClient(rectLogo);

	m_Logo.DrawEx(pDC, rectLogo, 0);
	
	CFont* pOldFont = pDC->SelectObject(&globalData.fontCaption);
	pDC->SetTextColor(CBCGPVisualManager::GetInstance()->GetRibbonBackstageInfoTextColor());
	pDC->SetBkMode(TRANSPARENT);

	CRect rectLabel;

	m_wndCaption.GetWindowRect(rectLabel);
	ScreenToClient(rectLabel);

	CString strLabel = _T("About BCGPMSOfficeDemo");

	pDC->DrawText(strLabel, rectLabel, DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOCLIP);

	pDC->SelectObject(pOldFont);
}

void CBackStagePageHelp::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDialog::OnSize(nType, cx, cy);

	if (m_wndList.GetSafeHwnd() == NULL)
	{
		return;
	}
	
	int nListMode = 1;

	CRect rectList;
	m_wndList.GetClientRect(rectList);

	if (m_nInitialListWidth == 0)
	{
		m_nInitialListWidth = rectList.Width();
		m_nListMode = 0;

		return;
	}

	if (rectList.Width() < m_nInitialListWidth * 3 / 2)
	{
		nListMode = 0;
	}
	else if (rectList.Width() < m_nInitialListWidth * 2)
	{
		nListMode = 1;
	}
	else
	{
		nListMode = 2;
	}

	if (m_nListMode != nListMode)
	{
		m_nListMode = nListMode;
		ResetList();
	}
}

LRESULT CBackStagePageHelp::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if (lp & PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC) wp);
		ASSERT_VALID(pDC);

		OnDraw(pDC);
	}

	return 0;
}
