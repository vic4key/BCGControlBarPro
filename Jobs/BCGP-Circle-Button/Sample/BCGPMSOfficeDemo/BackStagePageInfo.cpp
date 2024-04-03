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
// BackStagePageInfo.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "BackStagePageInfo.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageInfo dialog

IMPLEMENT_DYNCREATE(CBackStagePageInfo, CBCGPDialog)

CBackStagePageInfo::CBackStagePageInfo(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CBackStagePageInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackStagePageInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	EnableLayout();
}
	
void CBackStagePageInfo::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackStagePageInfo)
	DDX_Control(pDX, IDC_PREVIEW, m_btnPreview);
	DDX_Control(pDX, IDC_CHECK_FOR_ISSUE, m_btnCheckForIssues);
	DDX_Control(pDX, IDC_MANAGE_VERSIONS, m_btnManageVersions);
	DDX_Control(pDX, IDC_PROTECT_DOCUMENT, m_btnProtect);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBackStagePageInfo, CBCGPDialog)
	//{{AFX_MSG_MAP(CBackStagePageInfo)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREVIEW, OnPreview)
	ON_BN_CLICKED(IDC_CHECK_FOR_ISSUE, OnCheckForIssue)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageInfo message handlers

BOOL CBackStagePageInfo::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	ASSERT_VALID(pLayout);

	pLayout->AddAnchor(IDC_INFO_LABEL, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);

	pLayout->AddAnchor(IDC_SEPARATOR_1, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	pLayout->AddAnchor(IDC_TEXT1, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	
	pLayout->AddAnchor(IDC_SEPARATOR_2, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	pLayout->AddAnchor(IDC_TEXT2, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);

	pLayout->AddAnchor(IDC_SEPARATOR_3, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	pLayout->AddAnchor(IDC_TEXT3, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);

	pLayout->AddAnchor(IDC_SEPARATOR_4, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeVert);

	pLayout->AddAnchor(IDC_PREVIEW, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);

	m_btnProtect.SetImage(IDB_BS_PROTECT);
	m_btnProtect.SetImageAutoScale();
	m_btnProtect.m_bTopImage = TRUE;
	m_btnProtect.m_bDrawFocus = FALSE;

	m_btnCheckForIssues.SetImage(IDB_BS_CHECKISSUES);
	m_btnCheckForIssues.SetImageAutoScale();
	m_btnCheckForIssues.m_bTopImage = TRUE;
	m_btnCheckForIssues.m_bDrawFocus = FALSE;

	m_btnCheckForIssues.SetIcons(IDB_BS_HELP_LIST_32, 32);
	
	m_btnCheckForIssues.AddString(_T("Inspect Document\nInspect the document for hidden properties or personal information."), 0);
	m_btnCheckForIssues.AddString(_T("Check Accessibility\nCheck the document for content that people with disabilities might find difficult to read."), 1);
	m_btnCheckForIssues.AddString(_T("Check Compatibility\nCheck for features not supported by earlier versions of application."), 2);

	m_btnManageVersions.SetImage(IDB_BS_MANAGEVERSIONS);
	m_btnManageVersions.SetImageAutoScale();
	m_btnManageVersions.m_bTopImage = TRUE;
	m_btnManageVersions.m_bDrawFocus = FALSE;

	CBCGPFrameWnd* pMainFrame = (CBCGPFrameWnd*)AfxGetMainWnd();
	
	CDocument* pDoc = pMainFrame->GetActiveFrame()->GetActiveDocument();
	if (pDoc != NULL)
	{
		m_strDocName = pDoc->GetTitle();
		m_strPath = pDoc->GetPathName();
	}

	PreparePreviewBitmap();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBackStagePageInfo::PreparePreviewBitmap()
{
	CRect rectPreview;
	m_btnPreview.GetClientRect(rectPreview);

	CBitmap& bmpAppPreviw = ((CMainFrame*)AfxGetMainWnd())->GetAppPreview();

	BITMAP bmp;
	bmpAppPreviw.GetBitmap(&bmp);

	double dblScaleRatio = min((double)rectPreview.Width() / bmp.bmWidth, (double)rectPreview.Height() / bmp.bmHeight);

	CSize szDst((int)(bmp.bmWidth * dblScaleRatio), (int)(bmp.bmHeight * dblScaleRatio));

	HBITMAP hBitmap = CBCGPDrawManager::CreateBitmap_24(szDst, NULL);

	{
		CDC dcDst;
		dcDst.CreateCompatibleDC(NULL);

		HBITMAP hBitmapOld = (HBITMAP)dcDst.SelectObject (hBitmap);

		CBCGPDrawManager dm(dcDst);
		int nShadowSize = theApp.m_bIsRTL ? 0 : 5;
		
		szDst.cx -= 2 * nShadowSize;
		szDst.cy -= 2 * nShadowSize;

		CBCGPVisualManager::GetInstance()->OnFillRibbonBackstageForm(&dcDst, this, rectPreview);
		dm.DrawShadow(CRect(CPoint(nShadowSize, nShadowSize), szDst), nShadowSize);

		CDC dcSrc;
		dcSrc.CreateCompatibleDC(&dcDst);

		HBITMAP hBitmapViewOld = (HBITMAP)dcSrc.SelectObject(bmpAppPreviw.GetSafeHandle());

		dcDst.SetStretchBltMode(HALFTONE);

		dcDst.StretchBlt(nShadowSize, nShadowSize, szDst.cx, szDst.cy, &dcSrc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

		dcSrc.SelectObject (hBitmapViewOld);
		dcDst.SelectObject (hBitmapOld);
	}

	m_btnPreview.SetMouseCursorHand();
	m_btnPreview.SetDrawText(FALSE);
	m_btnPreview.m_bDrawFocus = FALSE;
	m_btnPreview.SetImage(hBitmap);
	m_btnPreview.m_bTransparent = TRUE;
	m_btnPreview.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_NOBORDERS;
	m_btnPreview.SizeToContent();

	bmpAppPreviw.DeleteObject();
}

void CBackStagePageInfo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnDraw(&dc);
}

void CBackStagePageInfo::OnDraw(CDC* pDC)
{
	CRect rectLabel;

	GetDlgItem(IDC_INFO_LABEL)->GetWindowRect(rectLabel);
	ScreenToClient(rectLabel);

	CFont* pOldFont = pDC->SelectObject(&globalData.fontCaption);
	pDC->SetTextColor(CBCGPVisualManager::GetInstance()->GetRibbonBackstageInfoTextColor());
	pDC->SetBkMode(TRANSPARENT);
	
	int nTextHeight = pDC->DrawText(m_strDocName, rectLabel, DT_SINGLELINE | DT_END_ELLIPSIS);

	rectLabel.top += nTextHeight + 5;

	pDC->SelectObject(&globalData.fontRegular);

	pDC->DrawText(m_strPath, rectLabel, DT_SINGLELINE | DT_END_ELLIPSIS);

	pDC->SelectObject(pOldFont);
}

LRESULT CBackStagePageInfo::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if (lp & PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC) wp);
		ASSERT_VALID(pDC);
		
		OnDraw(pDC);
	}
	
	return 0;
}

void CBackStagePageInfo::OnPreview() 
{
	GetParent()->SendMessage(WM_CLOSE);
}

void CBackStagePageInfo::OnCheckForIssue() 
{
	int nIndex = m_btnCheckForIssues.GetCurSel();	// Clicked item
	
	CString str;
	str.Format(_T("Check for issue number %d"), nIndex + 1);

	BCGPMessageBox(str);

	m_btnCheckForIssues.SetCurSel(-1);
}
