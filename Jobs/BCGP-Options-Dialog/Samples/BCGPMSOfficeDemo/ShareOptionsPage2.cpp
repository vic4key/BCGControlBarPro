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
// OptionsPage2.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "ShareOptionsPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage2 property page

IMPLEMENT_DYNCREATE(CShareOptionsPage2, CBCGPPropertyPage)

CShareOptionsPage2::CShareOptionsPage2() : CBCGPPropertyPage(CShareOptionsPage2::IDD)
{
	//{{AFX_DATA_INIT(CShareOptionsPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CShareOptionsPage2::~CShareOptionsPage2()
{
}

void CShareOptionsPage2::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareOptionsPage2)
	DDX_Control(pDX, IDC_PROP2_BUTTON1, m_btnSignIn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareOptionsPage2, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CShareOptionsPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage2 message handlers

BOOL CShareOptionsPage2::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor(IDC_LABEL2_PROP6, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	}

	m_btnSignIn.m_bDrawFocus = FALSE;
	m_btnSignIn.SetImage(IDB_BS_SIGNIN);
	m_btnSignIn.SetImageAutoScale();
	m_btnSignIn.m_bTopImage = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}