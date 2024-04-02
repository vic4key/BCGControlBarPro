#pragma once

#include <BCGPDialog.h>
#include "RibbonStates.h"
#include "resource.h"

using namespace RibbonStates;

class RibbonStateDlg : public CBCGPDialog
{
  DECLARE_DYNAMIC(RibbonStateDlg)

public:
  RibbonStateDlg(CWnd* pParent = nullptr, UINT thePanelImageList16x16 = -1);
  virtual ~RibbonStateDlg();

  enum { IDD = IDD_OPTIONS };

private:
  RibbonTabList m_Data;
  RibbonTabList m_BackupData;

  CBCGPComboBox m_RibbonTabs;
  CBCGPListBox  m_AvailablePanels;
  CBCGPListBox  m_SelectedPanels;
  UINT m_PanelImageList16x16;

  void FillTabList(RibbonTabList& tabs);
  void FillPanelListWithCurrentSelectedTab(const bool toUpdateButtons = true);
  void UpdateButtons();

  using RibbonPanelPtrIterPair = Pair<RibbonPanel*, RibbonPanelList::iterator>;
  using RibbonPanelPtrIterList = List<RibbonPanelPtrIterPair>;
  RibbonPanelPtrIterList m_ListPairSelectedPanels;

  bool GetCurrentSelectedPanel(int& idx, RibbonPanelPtrIterList::iterator& it);

protected:
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();

protected:
  afx_msg void OnSelchangeRibbonTabs();
  afx_msg void OnAdd();
  afx_msg void OnRemove();
  afx_msg void OnReset();
  afx_msg void OnUp();
  afx_msg void OnDown();
  afx_msg void OnLbnSelchangeSelectedPanels();
  DECLARE_MESSAGE_MAP()
};
