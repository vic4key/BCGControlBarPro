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
// OptionsPage6.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "ShareOptionsPage6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage6 property page

IMPLEMENT_DYNCREATE(CShareOptionsPage6, CBCGPPropertyPage)

CShareOptionsPage6::CShareOptionsPage6() : CBCGPPropertyPage(CShareOptionsPage6::IDD)
{
	//{{AFX_DATA_INIT(CShareOptionsPage6)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CShareOptionsPage6::~CShareOptionsPage6()
{
}

void CShareOptionsPage6::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareOptionsPage6)
	DDX_Control(pDX, IDC_PROP6_BUTTON1, m_btnCreatePDF);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareOptionsPage6, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CShareOptionsPage6)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage6 message handlers

BOOL CShareOptionsPage6::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	m_btnCreatePDF.m_bDrawFocus = FALSE;
	m_btnCreatePDF.SetImage(IDB_BS_CREATEPDFXPS);
	m_btnCreatePDF.SetImageAutoScale();
	m_btnCreatePDF.m_bTopImage = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}