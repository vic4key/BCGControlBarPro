#include "stdafx.h"
#include "RibbonStateDlg.h"

IMPLEMENT_DYNAMIC(CRibbonStateDlg, CBCGPDialogP)

BEGIN_MESSAGE_MAP(CRibbonStateDlg, CBCGPDialogP)
END_MESSAGE_MAP()

void CRibbonStateDlg::DoDataExchange(CDataExchange* pDX)
{
  CBCGPDialogP::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TABS, m_RibbonTabs);
  DDX_Control(pDX, IDC_AVAILABLE_PANELS, m_AvailablePanels);
  DDX_Control(pDX, IDC_SELECTED_PANELS, m_SelectedPanels);
}

CRibbonStateDlg::CRibbonStateDlg(CWnd* pParent) : CBCGPDialogP(CRibbonStateDlg::IDD, pParent)
{
  EnableVisualManagerStyle();
}

CRibbonStateDlg::~CRibbonStateDlg()
{
}

BOOL CRibbonStateDlg::OnInitDialog()
{
  __super::OnInitDialog();
  return TRUE;
}
