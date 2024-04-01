#include "stdafx.h"
#include "RibbonStateDlg.h"

#include <algorithm>

const CStringP& SelectedTab = L"SelectedTab";

IMPLEMENT_DYNAMIC(CRibbonStateDlg, CBCGPDialogP)

BEGIN_MESSAGE_MAP(CRibbonStateDlg, CBCGPDialogP)
  ON_CBN_SELCHANGE(IDC_TABS, OnSelchangeRibbonTabs)
  ON_BN_CLICKED(IDC_ADD, OnAdd)
  ON_BN_CLICKED(IDC_REMOVE, OnRemove)
  ON_BN_CLICKED(IDC_RESET, OnReset)
END_MESSAGE_MAP()

void CRibbonStateDlg::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TABS, m_RibbonTabs);
  DDX_Control(pDX, IDC_AVAILABLE_PANELS, m_AvailablePanels);
  DDX_Control(pDX, IDC_SELECTED_PANELS,  m_SelectedPanels);
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

  auto& tabs = CRibbonTabs::GetpInstance()->GetTabList();
  m_Data = tabs;
  m_BackupData = tabs;

  FillTabList(m_Data);

  FillPanelListWithCurrentSelectedTab();

  return TRUE;
}

void CRibbonStateDlg::FillTabList(CRibbonTabs::RibbonTabList& tabs)
{
  UpdateData(TRUE);

  m_RibbonTabs.ResetContent();

  for (auto& tab : tabs)
  {
    auto temp = CRibbonTabs::GetpInstance()->GetTabName(tab.first);
    int idx = m_RibbonTabs.AddString(temp.c_str());
    m_RibbonTabs.SetItemData(idx, reinterpret_cast<DWORD_PTR>(&tab));
  }

  if (m_RibbonTabs.GetCount() > 0)
  {
    m_RibbonTabs.SetCurSel(0);
  }

  UpdateData(FALSE);
}

void CRibbonStateDlg::FillPanelListWithCurrentSelectedTab(bool updateButtons)
{
  UpdateData(TRUE);

  m_AvailablePanels.ResetContent();
  m_SelectedPanels.ResetContent();

  int theTabIndex = m_RibbonTabs.GetCurSel();
  theTabIndex = (theTabIndex == CB_ERR ? 0 : theTabIndex);
  auto pItemData = m_RibbonTabs.GetItemData(theTabIndex);

  auto pRibbonTab = reinterpret_cast<CRibbonTabs::RibbonTabList::value_type*>(pItemData);
  auto pRibbonPanelList = reinterpret_cast<RibbonPanelList*>(&pRibbonTab->second);

  if (pRibbonPanelList != nullptr)
  {
    auto& panels = *pRibbonPanelList;
    for (auto& e : panels)
    {
      // for specific cases
      if (!CRibbonTabs::GetpInstance()->IsPanelAvailable(e.m_Panel))
      {
        continue;
      }

      if (e.m_Visible)
      {
        int thePanelIndex = m_SelectedPanels.AddString(e.m_Name.c_str());
        m_SelectedPanels.SetItemData(thePanelIndex, reinterpret_cast<DWORD_PTR>(&e));
      }
      else
      {
        int thePanelIndex = m_AvailablePanels.AddString(e.m_Name.c_str());
        m_AvailablePanels.SetItemData(thePanelIndex, reinterpret_cast<DWORD_PTR>(&e));
      }
    }
  }

  if (m_AvailablePanels.GetCount() > 0)
  {
    m_AvailablePanels.SetCurSel(0);
  }

  if (m_SelectedPanels.GetCount() > 0)
  {
    m_SelectedPanels.SetCurSel(0);
  }

  UpdateData(FALSE);

  if (updateButtons)
  {
    UpdateButtons();
  }
}

void CRibbonStateDlg::UpdateButtons()
{
  UpdateData(TRUE);

  if (auto pAddButton = GetDlgItem(IDC_ADD))
  {
    pAddButton->EnableWindow(m_AvailablePanels.GetCount() > 0);
  }

  if (auto pRemoveButton = GetDlgItem(IDC_REMOVE))
  {
    auto idx = m_RibbonTabs.GetCurSel();
    auto pItemData = m_RibbonTabs.GetItemData(idx);
    auto pRibbonTab = reinterpret_cast<RibbonTabList::value_type*>(pItemData);
    auto pRibbonPanelList = reinterpret_cast<RibbonPanelList*>(&pRibbonTab->second);
    auto& panels = *pRibbonPanelList;
    const auto NumVisiblePanels = std::count_if(panels.cbegin(), panels.cend(),
      [](const RibbonPanel& panel) -> bool { return panel.m_Visible; });
    const bool TabAlwaysVisible = CRibbonTabs::GetpInstance()->IsTabAlwaysVisible(pRibbonTab->first);
    pRemoveButton->EnableWindow(TabAlwaysVisible ? NumVisiblePanels > 1 : m_SelectedPanels.GetCount() > 0);
  }
}

void CRibbonStateDlg::OnOK()
{
  CRibbonTabs::GetpInstance()->SetTabList(m_Data);
  CRibbonTabs::GetpInstance()->Store();

  __super::OnOK();
}

void CRibbonStateDlg::OnCancel()
{
  CRibbonTabs::GetpInstance()->SetTabList(m_BackupData);
  CRibbonTabs::GetpInstance()->Store();

  __super::OnCancel();
}

void CRibbonStateDlg::OnSelchangeRibbonTabs()
{
  FillPanelListWithCurrentSelectedTab();
}

void CRibbonStateDlg::OnAdd()
{
  UpdateData(TRUE);

  int idx = m_AvailablePanels.GetCurSel();
  if (idx == CB_ERR)
  {
    return;
  }

  auto pRibbonPanel = reinterpret_cast<RibbonPanel*>(m_AvailablePanels.GetItemData(idx));
  if (pRibbonPanel != nullptr)
  {
    pRibbonPanel->m_Visible = true;
  }

  UpdateData(FALSE);

  FillPanelListWithCurrentSelectedTab();
}

void CRibbonStateDlg::OnRemove()
{
  UpdateData(TRUE);

  int idx = m_SelectedPanels.GetCurSel();
  if (idx == CB_ERR)
  {
    return;
  }

  auto pRibbonPanel = reinterpret_cast<RibbonPanel*>(m_SelectedPanels.GetItemData(idx));
  if (pRibbonPanel != nullptr)
  {
    pRibbonPanel->m_Visible = false;
  }

  UpdateData(FALSE);

  FillPanelListWithCurrentSelectedTab();
}

void CRibbonStateDlg::OnReset()
{
  UpdateData(TRUE);

  // Remember the previous tab.
  int idxPrev = m_RibbonTabs.GetCurSel();
  idxPrev = (idxPrev == CB_ERR ? 0 : idxPrev);

  // Reset to the default settings.
  m_Data = m_BackupData;
  FillTabList(m_Data);

  // Reselect the previous tab.
  m_RibbonTabs.SetCurSel(idxPrev);

  UpdateData(FALSE);

  FillPanelListWithCurrentSelectedTab();
}