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
// OptionsPage4.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "ShareOptionsPage4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage4 property page

IMPLEMENT_DYNCREATE(CShareOptionsPage4, CBCGPPropertyPage)

CShareOptionsPage4::CShareOptionsPage4() : CBCGPPropertyPage(CShareOptionsPage4::IDD)
{
	//{{AFX_DATA_INIT(CShareOptionsPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CShareOptionsPage4::~CShareOptionsPage4()
{
}

void CShareOptionsPage4::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareOptionsPage4)
	DDX_Control(pDX,IDC_PROP4_BUTTON1, m_btnPublishAsBP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareOptionsPage4, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CShareOptionsPage4)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage4 message handlers

BOOL CShareOptionsPage4::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor(IDC_LABEL1_PROP8, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(IDC_LABEL2_PROP10, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	}

	m_btnPublishAsBP.m_bDrawFocus = FALSE;
	m_btnPublishAsBP.SetImage(IDB_BS_PUBLISHBLOG);
	m_btnPublishAsBP.SetImageAutoScale();
	m_btnPublishAsBP.m_bTopImage = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}