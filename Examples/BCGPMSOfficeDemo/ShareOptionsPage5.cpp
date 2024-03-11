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
// OptionsPage5.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "ShareOptionsPage5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ITEM_WIDTH	globalUtils.ScaleByDPI(275)
#define X_MARGIN	globalUtils.ScaleByDPI(5)
#define Y_MARGIN	globalUtils.ScaleByDPI(2)

static LPCTSTR lpNames [] =
{
	_T("Document\nUses the Word Document format"),
	_T("Word 97-2003 Document\nUses the Word 97 - 2003 Document format"),
	_T("OpenDocument Text\nUses the OpenDocument Text format"),
	_T("Template\nStarting point for new documents"),
	_T("Plain Text\nContains only the text in your document"),
	_T("Rich Text Format\nPreserves test formatting information"),
	_T("Single File Web Page\nWeb page is stored as a single file"),
	_T("Save as Another File Type")
};

void CPage5RibbonGalleryCtrl::OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* /*pIcon*/, COLORREF clrText)
{
	rectIcon.left += X_MARGIN;
	rectIcon.top += Y_MARGIN;

	m_Icons.DrawEx(pDC, rectIcon, nIconIndex, CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertTop);

	CRect rectText = rectIcon;
	rectText.left += m_Icons.GetImageSize().cx;
	rectText.DeflateRect(X_MARGIN, 0);

	COLORREF clrOld = clrText == (COLORREF)-1 ? clrText : pDC->SetTextColor (clrText);

	pDC->DrawText(lpNames[nIconIndex], rectText, DT_WORDBREAK | DT_LEFT);

	if (clrOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrOld);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage5 property page

IMPLEMENT_DYNCREATE(CShareOptionsPage5, CBCGPPropertyPage)

CShareOptionsPage5::CShareOptionsPage5() : CBCGPPropertyPage(CShareOptionsPage5::IDD)
{
	//{{AFX_DATA_INIT(CShareOptionsPage5)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CShareOptionsPage5::~CShareOptionsPage5()
{
}

void CShareOptionsPage5::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareOptionsPage5)
		DDX_Control(pDX, IDC_SHARE5_LOCATION, m_wndGalleryLocation3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareOptionsPage5, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CShareOptionsPage5)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage5 message handlers

BOOL CShareOptionsPage5::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();

	CRect rectGallery;

	m_wndGalleryLocation3.GetWindowRect(&rectGallery);
	ScreenToClient(&rectGallery);

	m_wndGallery3.Create(rectGallery, this, IDC_GALLERY);

	m_wndGallery3.m_Icons.Clear();
	m_wndGallery3.m_Icons.SetImageSize(CSize (32, 32));
	m_wndGallery3.m_Icons.Load(IDB_BS_FILETYPES);
	
	globalUtils.ScaleByDPI(m_wndGallery3.m_Icons);

	const CSize sizeItem(ITEM_WIDTH, 
		max(m_wndGallery3.m_Icons.GetImageSize ().cy + 2 * Y_MARGIN,  3 * globalData.GetTextHeight()));

	m_wndGallery3.AddGroup(_T("Document File Types"), sizeItem, 4);
	m_wndGallery3.AddGroup(_T("Other File Types"), sizeItem, 4);

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor(IDC_GALLERY, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}