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
// ChartPane.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpmsofficedemo.h"
#include "ChartPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartPane

CChartPane::CChartPane()
{
}

CChartPane::~CChartPane()
{
}


BEGIN_MESSAGE_MAP(CChartPane, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CChartPane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


#define YEARS_NUM 5

/////////////////////////////////////////////////////////////////////////////
// CChartPane message handlers

int CChartPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndChart.Create(CRect(0, 0, 0, 0), this, 1);
	
	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);
	
	pChart->SetColors(CBCGPChartTheme::CT_FLAT_2016_4, TRUE /* Visual Manager colors */);

	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS);
	pChart->GetPlotAreaFormat().m_outlineFormat.m_dblWidth = 0;
	
	pChart->SetChartType(BCGPChartColumn, BCGP_CT_STACKED);

	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->ShowChartTitle(FALSE);
	
	COleDateTime now = COleDateTime::GetCurrentTime();
	
	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("A"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("B"));
	CBCGPChartSeries* pSeries3 = pChart->CreateSeries(_T("C"));

	BCGPChartFormatSeries style = pSeries1->GetSeriesFormat();
	style.m_shadowType.m_bDisplayShadow = TRUE;
	
	pSeries1->SetSeriesFormat(style);
	pSeries2->SetSeriesFormat(style);
	pSeries3->SetSeriesFormat(style);

	for (int i = YEARS_NUM - 1; i >= 0; i--)
	{
		CString strLabel;
		strLabel.Format(_T("%d"), now.GetYear() - i - 1);

		pSeries1->AddDataPoint(strLabel, 8.0 * (YEARS_NUM - i));
		pSeries2->AddDataPoint(strLabel, 10.0 * (YEARS_NUM - i));
		pSeries3->AddDataPoint(strLabel, 12.0 * (YEARS_NUM - i));
	}
	
	pChart->StartAnimation(1.5, CBCGPAnimationManager::BCGPANIMATION_ParabolicFromAcceleration);

	return 0;
}

void CChartPane::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	if (m_wndChart.GetSafeHwnd() != NULL)
	{
		m_wndChart.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

void CChartPane::OnPressCloseButton()
{
	if (!theApp.m_bDontShowPaneCloseMessage)
	{
		BCGPMessageBox(
			_T("You can show the Chart pane again by checking \"Chart Pane\" check box in the Ribbon tab \"View\"."),
			MB_OK, _T("Don't show this message again"), &theApp.m_bDontShowPaneCloseMessage);
	}

	CBCGPDockingControlBar::OnPressCloseButton();
}
