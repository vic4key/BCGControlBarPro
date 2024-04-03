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
// BackStagePageNew.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "BackStagePageNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int xMargin = 5;
static const int yMargin = 5;

static LPCTSTR lpNames [] =
{
	_T("Blank document"),
	_T("Blog post"),
	_T("Recent templates"),
	_T("Sample templates"),
	_T("My templates"),
	_T("New from existing"),
	_T("Agendas"),
	_T("Business cards"),
	_T("Calendars"),
};

void CNewRibbonGalleryCtrl::OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* /*pIcon*/, COLORREF clrText)
{
	const double dScale = globalData.GetRibbonImageScale ();
	rectIcon.top += (int)(yMargin * dScale);

	m_Icons.DrawEx(pDC, rectIcon, nIconIndex, CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertTop);

	CRect rectText = rectIcon;
	rectText.top += m_Icons.GetImageSize().cy + (int)(yMargin * dScale);
	rectText.DeflateRect((int)(xMargin * dScale), 0);

	COLORREF clrTextOld = (COLORREF)-1;

	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor(clrText);
	}

	pDC->DrawText(lpNames[nIconIndex], rectText, DT_WORDBREAK | DT_CENTER);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(clrTextOld);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageNew dialog

IMPLEMENT_DYNCREATE(CBackStagePageNew, CBCGPDialog)

CBackStagePageNew::CBackStagePageNew(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CBackStagePageNew::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackStagePageNew)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	EnableLayout();

	m_nSelectedTemplate = 0;
}


void CBackStagePageNew::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackStagePageNew)
	DDX_Control(pDX, IDC_PREVIEW, m_wndPreview);
	DDX_Control(pDX, IDC_GALLERY_LOCATION, m_wndGalleryLocation);
	DDX_Control(pDX, IDC_CREATE, m_btnCreate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackStagePageNew, CBCGPDialog)
	//{{AFX_MSG_MAP(CBackStagePageNew)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, OnHighlightRibbonListItem)
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageNew message handlers

BOOL CBackStagePageNew::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	CRect rectGallery;

	m_wndGalleryLocation.GetWindowRect(&rectGallery);
	ScreenToClient(&rectGallery);

	m_wndGallery.Create(rectGallery, this, IDC_GALLERY);

	const double dScale = globalData.GetRibbonImageScale ();

	m_wndGallery.m_Icons.SetImageSize(CSize(64, 64));
	m_wndGallery.m_Icons.Load(IDB_BS_GALLERY_NEW);
	m_wndGallery.m_Icons.SmoothResize (dScale);

	CSize sizeItem((int)(85 * dScale), (int)(115 * dScale));

	m_wndGallery.AddGroup(_T("Home"), sizeItem, 6);
	m_wndGallery.AddGroup(_T("Custom Templates"), sizeItem, 3);

	m_btnCreate.m_bDrawFocus = FALSE;
	m_btnCreate.SetImageAutoScale();
	m_btnCreate.SetImage(IDB_BS_CREATE);
	m_btnCreate.m_bTopImage = TRUE;

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	ASSERT_VALID(pLayout);
	
	pLayout->AddAnchor(IDC_INFO_LABEL, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);

	pLayout->AddAnchor(IDC_SEPARATOR_1, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	pLayout->AddAnchor(IDC_GALLERY, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
	pLayout->AddAnchor(IDC_SEPARATOR_2, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeVert);
	pLayout->AddAnchor(IDC_PREVIEW, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);
	pLayout->AddAnchor(IDC_CREATE, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBackStagePageNew::OnCreate() 
{
	GetParent()->SendMessage(WM_CLOSE);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

void CBackStagePageNew::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnDraw(&dc);
}

void CBackStagePageNew::OnDraw(CDC* pDC)
{
	CFont* pOldFont = pDC->SelectObject(&globalData.fontCaption);
	pDC->SetTextColor(CBCGPVisualManager::GetInstance()->GetRibbonBackstageInfoTextColor());
	pDC->SetBkMode(TRANSPARENT);

	CWnd* pCtrl = GetDlgItem(IDC_INFO_LABEL);
	if (pCtrl != NULL)
	{
		CRect rectLabel;

		pCtrl->GetWindowRect(rectLabel);
		ScreenToClient(rectLabel);

		CString strLabel;
		pCtrl->GetWindowText(strLabel);

		pDC->DrawText(strLabel, rectLabel, DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOCLIP);
	}

	pDC->SelectObject(pOldFont);

	CRect rectPreview;
	m_wndPreview.GetWindowRect(rectPreview);
	ScreenToClient(rectPreview);

	CBCGPVisualManager::GetInstance ()->OnFillRibbonBackstageForm(pDC, this, rectPreview);

	if (m_nSelectedTemplate == 5)
	{
		// "New from existing" doesn't have preview
		return;
	}

	CRect rectLabel = rectPreview;

	pOldFont = pDC->SelectObject(&globalData.fontBold);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(CBCGPVisualManager::GetInstance()->GetRibbonBackstageTextColor());

	CString strName = (m_nSelectedTemplate >= 0) ? lpNames[m_nSelectedTemplate] : _T("");
	
	int nTextHeight = pDC->DrawText(strName, rectLabel, DT_SINGLELINE | DT_END_ELLIPSIS);

	rectPreview.top += nTextHeight + 10;

	rectPreview.right -= 10;
	rectPreview.bottom -= 10;

	pDC->SelectObject(pOldFont);

	if (globalData.IsHighContastMode())
	{
		pDC->Draw3dRect(rectPreview, globalData.clrWindowText, globalData.clrWindowText);
	}
	else
	{
		CBCGPDrawManager dm(*pDC);

		dm.DrawRect(rectPreview, RGB(255, 255, 255), RGB(120, 120, 120));
		dm.DrawShadow(rectPreview, 4, 100, 70);
	}
}

BOOL CBackStagePageNew::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_GALLERY)
	{
		CString str;

		if (m_nSelectedTemplate != 5)
		// New from existing document has a special processing inside OnHighlightRibbonListItem
		{
			OnCreate();
		}

		return TRUE;
	}
	
	return CBCGPDialog::OnCommand(wParam, lParam);
}

LRESULT CBackStagePageNew::OnHighlightRibbonListItem (WPARAM wp, LPARAM /*lp*/)
{
	m_nSelectedTemplate = (int) wp;

	CRect rectPreview;
	m_wndPreview.GetWindowRect(rectPreview);
	ScreenToClient(rectPreview);

	RedrawWindow(rectPreview, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	if (m_wndGallery.IsMouseClicked() && m_nSelectedTemplate == 5)
	{
		MessageBox(_T("New from existing document..."));
	}

	return 0;
}

LRESULT CBackStagePageNew::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if (lp & PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC) wp);
		ASSERT_VALID(pDC);
		
		OnDraw(pDC);
	}
	
	return 0;
}
