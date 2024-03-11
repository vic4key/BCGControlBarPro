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
// OptionsPage1.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"
#include "ShareOptionsPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage property page

IMPLEMENT_DYNCREATE(CShareOptionsPage1, CBCGPPropertyPage)

CShareOptionsPage1::CShareOptionsPage1() : CBCGPPropertyPage(CShareOptionsPage1::IDD)
{
	//{{AFX_DATA_INIT(CShareOptionsPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CShareOptionsPage1::~CShareOptionsPage1()
{
}

void CShareOptionsPage1::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareOptionsPage1)
	DDX_Control(pDX, IDC_PROP_BUTTON1, m_btnSendAsAttachment);
	DDX_Control(pDX,IDC_PROP_BUTTON2, m_btnSendALink);
	DDX_Control(pDX,IDC_PROP_BUTTON3, m_btnSendAsPDF);
	DDX_Control(pDX,IDC_PROP_BUTTON4, m_btnSendAsXPS);
	DDX_Control(pDX,IDC_PROP_BUTTON5, m_btnSendAsIFax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareOptionsPage1, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CShareOptionsPage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareOptionsPage1 message handlers

BOOL CShareOptionsPage1::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor(IDC_LABEL1_PROP1, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(IDC_LABEL2_PROP2, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(IDC_LABEL2_PROP3, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(IDC_LABEL2_PROP4, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(IDC_LABEL2_PROP5, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	}

	m_btnSendAsAttachment.m_bDrawFocus = FALSE;
	m_btnSendAsAttachment.SetImage(IDB_BS_SENDATTACHMENT);
	m_btnSendAsAttachment.SetImageAutoScale();
	m_btnSendAsAttachment.m_bTopImage = TRUE;

	m_btnSendALink.m_bDrawFocus = FALSE;
    m_btnSendALink.SetImage(IDB_BS_SENDLINK);
	m_btnSendALink.SetImageAutoScale();
	m_btnSendALink.m_bTopImage = TRUE;

	m_btnSendAsPDF.m_bDrawFocus = FALSE;
	m_btnSendAsPDF.SetImage(IDB_BS_SENDPDF);
	m_btnSendAsPDF.SetImageAutoScale();
	m_btnSendAsPDF.m_bTopImage = TRUE;

	m_btnSendAsXPS.m_bDrawFocus = FALSE;
	m_btnSendAsXPS.SetImage(IDB_BS_SENDXPS);
	m_btnSendAsXPS.SetImageAutoScale();
	m_btnSendAsXPS.m_bTopImage = TRUE;

	m_btnSendAsIFax.m_bDrawFocus = FALSE;
	m_btnSendAsIFax.SetImage(IDB_BS_SENDFAX);
	m_btnSendAsIFax.SetImageAutoScale();
	m_btnSendAsIFax.m_bTopImage = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}