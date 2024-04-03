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
// GridPane.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpmsofficedemo.h"
#include "GridPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoldGridItem class - supports bold

class CBoldGridItem: public CBCGPGridItem
{
	DECLARE_DYNCREATE(CBoldGridItem)
		
public:
	CBoldGridItem (BOOL bBold = FALSE) : CBCGPGridItem () 
	{
		m_bBold = bBold;
	}

	CBoldGridItem(const _variant_t& varValue, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
		LPCTSTR lpszValidChars = NULL)
		: CBCGPGridItem (varValue, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars) 
	{
		m_bBold = FALSE;
	}

	void SetBold (BOOL bBold) 
	{
		m_bBold = bBold;
	}

	// Overrides
public:
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual void OnPrintValue (CDC* pDC, CRect rect);
	virtual void SetInPlaceEditFont ();

	// Attributes
protected:
	BOOL m_bBold;
};

IMPLEMENT_DYNCREATE(CBoldGridItem, CBCGPGridItem)

void CBoldGridItem::OnDrawValue (CDC* pDC, CRect rect)
{
	HFONT hfontOld = NULL;

	// Set bold font
	CBCGPGridCtrl* pGrid = GetOwnerList();
	if (m_bBold && pGrid != NULL)
	{
		hfontOld = pGrid->SetBoldFont (pDC);
	}

	// Perform drawing
	CBCGPGridItem::OnDrawValue (pDC, rect);
	
	// Restore font
	if (hfontOld != NULL)
	{
		::SelectObject (pDC->GetSafeHdc (), hfontOld);
	}
}

void CBoldGridItem::OnPrintValue (CDC* pDC, CRect rect)
{
	HFONT hfontOld = NULL;
	
	// Set bold font
	CBCGPGridCtrl* pGrid = GetOwnerList();
	if (m_bBold && pGrid != NULL)
	{
		hfontOld = pGrid->SetBoldFont (pDC);
	}
	
	// Perform printing
	CBCGPGridItem::OnPrintValue (pDC, rect);
	
	// Restore font
	if (hfontOld != NULL)
	{
		::SelectObject (pDC->GetSafeHdc (), hfontOld);
	}
}

void CBoldGridItem::SetInPlaceEditFont ()
{
	CBCGPGridItem::SetInPlaceEditFont ();

	// Set bold font
	CBCGPGridCtrl* pGrid = GetOwnerList();
	if (m_bBold && pGrid != NULL && m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetFont (&pGrid->GetBoldFont(), TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGridPane

CGridPane::CGridPane()
{
}

CGridPane::~CGridPane()
{
}

BEGIN_MESSAGE_MAP(CGridPane, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CGridPane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGridPane message handlers

int CGridPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndGrid.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 1);

	m_wndGrid.SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
	m_wndGrid.SetVisualManagerColorTheme();

	m_wndGrid.InsertColumn (0, _T(""), 0);
	m_wndGrid.InsertColumn (1, _T("Quarter"), 110);
	m_wndGrid.InsertColumn (2, _T("Amount"), 100);
	m_wndGrid.InsertColumn (3, _T("Change"), 100);

	m_imagesArrows.SetImageSize(CSize(16, 16));
	m_imagesArrows.Load(IDB_GRIDARROWS);

	m_wndGrid.SetCustomDataIconSet(&m_imagesArrows, 3, FALSE, CBCGPGridDataStateIconSet::ImagePlacementHorzRight);

	m_wndGrid.SetColumnAlign (0, HDF_RIGHT);
	m_wndGrid.SetColumnAlign (2, HDF_RIGHT);
	m_wndGrid.SetColumnAlign (3, HDF_RIGHT);
	m_wndGrid.SetHeaderAlign (2, HDF_RIGHT);
	m_wndGrid.SetHeaderAlign (3, HDF_RIGHT);
	m_wndGrid.SetColumnLocked (0);

	AddData (_T("I"), _T("$2,554.00"), 0.0021, 2);
	AddData (_T("II"), _T("$2,370.00"), -0.0052, 2);
	AddData (_T("III"), _T("$1,825.00"), -0.027, 2);
	AddData (_T("IV"), _T("$4,778.00"), 0.0912, 2);

	AddData (_T("I"), _T("$3,278.00"), 0.0019, 1);
	AddData (_T("II"), _T("$3,812.00"), -0.0034, 1);
	AddData (_T("III"), _T("$4,303.00"), 0.011, 1);
	AddData (_T("IV"), _T("$5,034.00"), -0.0163, 1);

	CBCGPGridRow* pTotalRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
	
	pTotalRow->ReplaceItem (0, new CBoldGridItem(TRUE));
	pTotalRow->ReplaceItem (2, new CBoldGridItem(TRUE));
	pTotalRow->GetItem (0)->SetValue (_T("Total:"));
	pTotalRow->GetItem (2)->SetValue (_T("$ 27,954.00"));

	m_wndGrid.AddRow (pTotalRow);

	m_wndGrid.MergeRange (CBCGPGridRange (0, 8, 1, 8));
	m_wndGrid.MergeRange (CBCGPGridRange (2, 8, 3, 8));

	m_wndGrid.EnableHeader (TRUE, 0);
	m_wndGrid.EnableColumnAutoSize (TRUE);
	m_wndGrid.SetReadOnly (TRUE);
	m_wndGrid.SetSelectionBorder (FALSE);

	return 0;
}

void CGridPane::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	if (m_wndGrid.GetSafeHwnd() != NULL)
	{
		m_wndGrid.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

BOOL CGridPane::AddData (LPCTSTR strPeriod, LPCTSTR strValue, double dDifference, int nYearDelta)
{
	CBCGPGridRow* pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());

	COleDateTime now = COleDateTime::GetCurrentTime();
	
	CString strQaurter;
	strQaurter.Format (_T("%s %d"), strPeriod, now.GetYear() - nYearDelta);

	pRow->GetItem(1)->SetValue((LPCTSTR)strQaurter);
	pRow->GetItem(2)->SetValue(strValue);

	CBCGPGridPercentItem* pPercItem = new CBCGPGridPercentItem(dDifference);

	pPercItem->SetPrecision(2);
	pPercItem->SetTextColor (dDifference < 0 ? RGB (255, 0, 0) : RGB (0, 127, 0));
	pPercItem->SetDataIcon(dDifference < 0 ? 0 : 100);

	pRow->ReplaceItem (3, pPercItem);

	m_wndGrid.AddRow (pRow);

	return TRUE;
}

void CGridPane::OnPressCloseButton()
{
	if (!theApp.m_bDontShowPaneCloseMessage)
	{
		BCGPMessageBox(
			_T("You can show the Grid pane again by checking \"Grid Pane\" check box in the Ribbon tab \"View\"."),
			MB_OK, _T("Don't show this message again"), &theApp.m_bDontShowPaneCloseMessage);
	}

	CBCGPDockingControlBar::OnPressCloseButton();
}
