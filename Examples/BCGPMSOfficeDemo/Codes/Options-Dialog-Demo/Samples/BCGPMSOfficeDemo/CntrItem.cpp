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
// CntrItem.cpp : implementation of the CBCGPMSOfficeDemoCntrItem class
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"

#include "BCGPMSOfficeDemoDoc.h"
#include "BCGPMSOfficeDemoView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoCntrItem implementation

IMPLEMENT_SERIAL(CBCGPMSOfficeDemoCntrItem, CRichEditCntrItem, 0)

CBCGPMSOfficeDemoCntrItem::CBCGPMSOfficeDemoCntrItem(REOBJECT* preo, CBCGPMSOfficeDemoDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	m_uiCategoryID = 0;
}

CBCGPMSOfficeDemoCntrItem::~CBCGPMSOfficeDemoCntrItem()
{
	// TODO: add cleanup code here
	
}

BOOL CBCGPMSOfficeDemoCntrItem::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow)
{
	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, pFrameWnd);
	if (pMainFrame != NULL)
	{
		return pMainFrame->OnShowControlBars (bShow);
	}
	else	// Maybe, SDI frame...
	{
		CBCGPFrameWnd* pFrame = DYNAMIC_DOWNCAST (CBCGPFrameWnd, pFrameWnd);
		if (pFrame != NULL)
		{
			return pFrame->OnShowControlBars (bShow);
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoCntrItem diagnostics

#ifdef _DEBUG
void CBCGPMSOfficeDemoCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CBCGPMSOfficeDemoCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
