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
// OptionsPage3.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "ShareOptionsPage3.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int xMargin = 5;
static const int yMargin = 5;

void CPage3RibbonGalleryCtrl::OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int /*nIconIndex*/, CBCGPRibbonPaletteIcon* /*pIcon*/, COLORREF clrText)
{
	CRect rectText = rectIcon;

	int nMarginX = globalUtils.ScaleByDPI(xMargin);
	int nMarginY = globalUtils.ScaleByDPI(yMargin);

	rectText.DeflateRect(nMarginX, nMarginY);

	COLORREF clrOld = clrText == (COLORREF)-1 ? clrText : pDC->SetTextColor (clrText);

	pDC->DrawText(_T("Browse for a location"), rectText, DT_VCENTER | DT_SINGLELINE);

	if (clrOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrOld);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage3 property page

IMPLEMENT_DYNCREATE(CShareOptionsPage3, CBCGPPropertyPage)

CShareOptionsPage3::CShareOptionsPage3() : CBCGPPropertyPage(CShareOptionsPage3::IDD)
{
	//{{AFX_DATA_INIT(CShareOptionsPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	EnableLayout();
}

CShareOptionsPage3::~CShareOptionsPage3()
{
}

void CShareOptionsPage3::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareOptionsPage3)
	DDX_Control(pDX, IDC_SAVE_AS, m_btnSaveAs);
		DDX_Control(pDX, IDC_SHARE3_LOCATION, m_wndGalleryLocation2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShareOptionsPage3, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CShareOptionsPage3)
	ON_BN_CLICKED(IDC_SAVE_AS, OnSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage3 message handlers

BOOL CShareOptionsPage3::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();

	m_btnSaveAs.m_bDrawFocus = FALSE;
	m_btnSaveAs.SetImage(IDB_BS_SAVE_AS);
	m_btnSaveAs.SetImageAutoScale();
	m_btnSaveAs.m_bTopImage = TRUE;
	
	CRect rectGallery;

	m_wndGalleryLocation2.GetWindowRect(&rectGallery);
	ScreenToClient(&rectGallery);

	m_wndGallery2.Create(rectGallery, this, IDC_GALLERY);
	m_wndGallery2.AddGroup(_T("Locations"), globalUtils.ScaleByDPI(CSize(269, 40)), 1);
	
	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor(IDC_GALLERY, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(IDC_LABEL2_PROP7, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShareOptionsPage3::OnSaveAs() 
{
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_SAVE_AS);
}
