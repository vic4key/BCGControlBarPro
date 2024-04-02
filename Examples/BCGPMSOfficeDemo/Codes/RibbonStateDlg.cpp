#include "stdafx.h"
#include "RibbonStateDlg.h"

#include <BCGPMessageBox.h>
#include <algorithm>

const String& SelectedTab = L"SelectedTab";

IMPLEMENT_DYNAMIC(RibbonStateDlg, CBCGPDialog)

BEGIN_MESSAGE_MAP(RibbonStateDlg, CBCGPDialog)
  ON_CBN_SELCHANGE(IDC_TABS, OnSelchangeRibbonTabs)
  ON_BN_CLICKED(IDC_ADD, OnAdd)
  ON_BN_CLICKED(IDC_REMOVE, OnRemove)
  ON_BN_CLICKED(IDC_RESET, OnReset)
  ON_BN_CLICKED(IDC_UP, OnUp)
  ON_BN_CLICKED(IDC_DOWN, OnDown)
  ON_LBN_SELCHANGE(IDC_SELECTED_PANELS, OnLbnSelchangeSelectedPanels)
END_MESSAGE_MAP()

void RibbonStateDlg::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TABS, m_RibbonTabs);
  DDX_Control(pDX, IDC_AVAILABLE_PANELS, m_AvailablePanels);
  DDX_Control(pDX, IDC_SELECTED_PANELS,  m_SelectedPanels);
}

RibbonStateDlg::RibbonStateDlg(CWnd* pParent, UINT thePanelImageList)
  : CBCGPDialog(RibbonStateDlg::IDD, pParent), m_PanelImageList16x16(thePanelImageList)
{
  EnableVisualManagerStyle();
}

RibbonStateDlg::~RibbonStateDlg()
{
}

BOOL RibbonStateDlg::OnInitDialog()
{
  __super::OnInitDialog();

  auto& tabs = RibbonTabs::GetpInstance()->GetTabList();
  m_Data = tabs;
  m_BackupData = tabs;

  FillTabList(m_Data);

  FillPanelListWithCurrentSelectedTab();

  m_AvailablePanels.SetImageList(m_PanelImageList16x16, 16);
  m_SelectedPanels.SetImageList(m_PanelImageList16x16, 16);

  return TRUE;
}

void RibbonStateDlg::FillTabList(RibbonTabList& tabs)
{
  UpdateData(TRUE);

  m_RibbonTabs.ResetContent();

  for (auto& tab : tabs)
  {
    int idx = m_RibbonTabs.AddString(tab.first.c_str());
    m_RibbonTabs.SetItemData(idx, reinterpret_cast<DWORD_PTR>(&tab));
  }

  if (m_RibbonTabs.GetCount() > 0)
  {
    m_RibbonTabs.SetCurSel(0);
  }

  UpdateData(FALSE);
}

void RibbonStateDlg::FillPanelListWithCurrentSelectedTab()
{
  UpdateData(TRUE);

  m_AvailablePanels.ResetContent();
  m_SelectedPanels.ResetContent();

  int theTabIndex = m_RibbonTabs.GetCurSel();
  theTabIndex = (theTabIndex == CB_ERR ? 0 : theTabIndex);
  auto pItemData = m_RibbonTabs.GetItemData(theTabIndex);

  auto pRibbonTab = reinterpret_cast<RibbonTabList::value_type*>(pItemData);
  auto pRibbonPanelList = reinterpret_cast<RibbonPanelList*>(&pRibbonTab->second);

  if (pRibbonPanelList != nullptr)
  {
    for (auto iter = pRibbonPanelList->begin(); iter != pRibbonPanelList->end(); iter++)
    {
      auto& panel = *iter;
      auto& thePanelBox = panel.m_Visible ? m_SelectedPanels : m_AvailablePanels;
      int thePanelIndex = thePanelBox.AddString(panel.m_Name.c_str());
      thePanelBox.SetItemImage(thePanelIndex, panel.m_Image);
      thePanelBox.SetItemData(thePanelIndex, reinterpret_cast<DWORD_PTR>(&panel));
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

  UpdateButtons();
}

void RibbonStateDlg::UpdateButtons()
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
    const auto NumVisiblePanels = std::count_if(pRibbonPanelList->cbegin(), pRibbonPanelList->cend(),
      [](const RibbonPanel& panel) -> bool { return panel.m_Visible; });
    pRemoveButton->EnableWindow(NumVisiblePanels > 0);
  }

  if (auto pUpButton = GetDlgItem(IDC_UP))
  {
    int iCurSel = m_SelectedPanels.GetCurSel();
    pUpButton->EnableWindow(!(iCurSel == LB_ERR || iCurSel == 0));
  }

  if (auto pUpButton = GetDlgItem(IDC_DOWN))
  {
    int iCurSel = m_SelectedPanels.GetCurSel();
    pUpButton->EnableWindow(!(iCurSel == LB_ERR || iCurSel == m_SelectedPanels.GetCount() - 1));
  }
}

void RibbonStateDlg::OnOK()
{
  RibbonTabs::GetpInstance()->SetTabList(m_Data);

  __super::OnOK();
}

void RibbonStateDlg::OnSelchangeRibbonTabs()
{
  FillPanelListWithCurrentSelectedTab();
}

void RibbonStateDlg::OnAdd()
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

void RibbonStateDlg::OnRemove()
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

void RibbonStateDlg::OnReset()
{
  if (BCGPMessageBox(L"All your changes will be lost! Do you really want to reset ?",
    MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL)
  {
    return;
  }

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

void RibbonStateDlg::OnUp()
{
}

void RibbonStateDlg::OnDown()
{
}

void RibbonStateDlg::OnLbnSelchangeSelectedPanels()
{
  UpdateButtons();
}
