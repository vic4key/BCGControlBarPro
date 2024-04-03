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
// ClipboardPane.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "ClipboardPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int xMargin = 10;
static const int yMargin = 10;

/////////////////////////////////////////////////////////////////////////////
// CClipboardPane

IMPLEMENT_DYNAMIC(CClipboardPane, CBCGPDialogBar)

CClipboardPane::CClipboardPane()
{
	EnableVisualManagerStyle ();
	EnableLayout();

	//{{AFX_DATA_INIT(CClipboardPane)
	//}}AFX_DATA_INIT

	m_mButtonsFullWidth = 0;

	m_wndItems.SetItemExtraHeight(globalUtils.ScaleByDPI(3));
}

CClipboardPane::~CClipboardPane()
{
}

void CClipboardPane::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipboardPane)
	DDX_Control(pDX, IDC_LABEL, m_wndLabel);
	DDX_Control(pDX, IDC_ITEMS, m_wndItems);
	DDX_Control(pDX, IDC_OPTION1, m_btnOption1);
	DDX_Control(pDX, IDC_OPTION2, m_btnOption2);
	DDX_Control(pDX, IDC_PASTE_ALL, m_btnPasteAll);
	DDX_Control(pDX, IDC_CLEAR_ALL, m_btnClearAll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipboardPane, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CClipboardPane)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipboardPane message handlers


void CClipboardPane::AdjustControlsLayout()
{
	CBCGPDialogBar::AdjustControlsLayout();

	if (m_btnPasteAll.GetSafeHwnd() != NULL)
	{
		CRect rectClient;
		GetClientRect(rectClient);

		if (rectClient.Width() < m_mButtonsFullWidth + 2 * xMargin)
		{
			// Hide buttons text
			CString str1;
			m_btnPasteAll.GetWindowText (str1);

			CString str2;
			m_btnClearAll.GetWindowText (str2);

			if (!str1.IsEmpty () && !str1.IsEmpty ())
			{
				m_btnPasteAll.SetWindowText (_T(""));
				m_btnPasteAll.SetTooltip (str1);

				m_btnClearAll.SetWindowText (_T(""));
				m_btnClearAll.SetTooltip (str2);
			}
		}
		else
		{
			// Show buttons text
			CString str1;
			m_btnPasteAll.GetTooltip (str1);

			CString str2;
			m_btnClearAll.GetTooltip (str2);

			if (!str1.IsEmpty () && !str1.IsEmpty ())
			{
				m_btnPasteAll.SetWindowText (str1);
				m_btnPasteAll.SetTooltip (_T(""));

				m_btnClearAll.SetWindowText (str2);
				m_btnClearAll.SetTooltip (_T(""));
			}
		}

		m_btnPasteAll.SizeToContent ();
		m_btnClearAll.SizeToContent ();

		CRect rectBtn1;
		m_btnPasteAll.GetWindowRect (rectBtn1);
		ScreenToClient (&rectBtn1);

		m_btnPasteAll.SetWindowPos (NULL, xMargin, rectBtn1.top, -1, -1, 
			SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnClearAll.SetWindowPos (NULL, xMargin + rectBtn1.Width () + xMargin, rectBtn1.top, -1, -1,
				SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);

		m_btnPasteAll.RedrawWindow ();
		m_btnPasteAll.RedrawWindow ();
	}
}

LRESULT CClipboardPane::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = CBCGPDialogBar::HandleInitDialog(wParam, lParam);

	m_btnPasteAll.SetImage (IDB_PASTE_ALL);
	m_btnPasteAll.SetImageAutoScale();
	CSize sizePasteAll = m_btnPasteAll.SizeToContent ();

	m_btnClearAll.SetImage (IDB_CLEAR_ALL);
	m_btnClearAll.SetImageAutoScale();
	CSize sizeClearAll = m_btnClearAll.SizeToContent ();

	m_btnOption1.SetCheck (1);

	m_mButtonsFullWidth = sizePasteAll.cx + sizeClearAll.cx + xMargin;

	// Add some summy items to list:
	m_wndItems.EnableItemDescription(TRUE, 1);
	m_wndItems.SetImageList(IDB_CLIPBOARD_ITEM, 16, 2, TRUE);

	int i = m_wndItems.AddString (_T(""));
	m_wndItems.SetItemDescription(i, _T("The quick brown fox jumps over the lazy dog"));
	m_wndItems.SetItemImage(i, 0);

	i = m_wndItems.AddString (_T(""));
	m_wndItems.SetItemDescription(i, _T("Some other text"));
	m_wndItems.SetItemImage(i, 0);

	m_wndItems.SetCurSel (0);

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout ();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor (IDC_LABEL, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor (IDC_ITEMS, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
		pLayout->AddAnchor (IDC_OPTION1, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor (IDC_OPTION2, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeNone);
	}

	return lRes;
}

void CClipboardPane::OnPressCloseButton()
{
	if (!theApp.m_bDontShowPaneCloseMessage)
	{
		BCGPMessageBox(
			_T("You can show the Clipboard pane again by clicking the Launch Button in the Ribbon tab \"Home\", pane \"Clipboard\"."),
			MB_OK, _T("Don't show this message again"), &theApp.m_bDontShowPaneCloseMessage);
	}

	CBCGPDialogBar::OnPressCloseButton();
}

void CClipboardPane::OnRTLChanged (BOOL bIsRTL)
{
	CBCGPDialogBar::OnRTLChanged (bIsRTL);
	RedrawWindow(NULL, NULL, RDW_UPDATENOW | RDW_ALLCHILDREN);
}
