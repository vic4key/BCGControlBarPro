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
// BackStagePageShare.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "BackStagePageShare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageShare dialog

IMPLEMENT_DYNCREATE(CBackStagePageShare, CBCGPDialog)

CBackStagePageShare::CBackStagePageShare(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CBackStagePageShare::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackStagePageShare)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	EnableLayout();
}


void CBackStagePageShare::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackStagePageShare)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackStagePageShare, CBCGPDialog)
	//{{AFX_MSG_MAP(CBackStagePageShare)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageShare message handlers

BOOL CBackStagePageShare::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	m_wndPropSheet.m_bIsAutoDestroy = FALSE;
	m_wndPropSheet.EnableVisualManagerStyle();
	m_wndPropSheet.EnableLayout();

	CRect rectPropSheet;
	
	GetDlgItem(IDC_PROPSHEET_LOCATION)->GetWindowRect(rectPropSheet);
	ScreenToClient(rectPropSheet);

	m_wndPropSheet.Create(this, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 0);
	m_wndPropSheet.SetWindowPos(NULL, rectPropSheet.left, rectPropSheet.top, rectPropSheet.Width(), rectPropSheet.Height(),
		SWP_NOZORDER);

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	ASSERT_VALID(pLayout);

	pLayout->AddAnchor(IDC_PROPSHEET_LOCATION, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
	pLayout->AddAnchor(m_wndPropSheet.GetSafeHwnd(), CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
