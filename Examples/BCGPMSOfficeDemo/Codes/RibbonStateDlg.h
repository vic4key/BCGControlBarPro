#pragma once

#include <BCGPDialog.h>
#include "RibbonStates.h"
#include "resource.h"

using CBCGPDialogP   = CBCGPDialog;
using CBCGPComboBoxP = CBCGPComboBox;
using CBCGPListBoxP  = CBCGPListBox;

using namespace RibbonStates;
using RibbonTabList   = CRibbonTabs::RibbonTabList;
using RibbonPanelList = CRibbonTabs::RibbonPanelList;

class CRibbonStateDlg : public CBCGPDialogP
{
  DECLARE_DYNAMIC(CRibbonStateDlg)

public:
  CRibbonStateDlg(CWnd* pParent = nullptr);
  virtual ~CRibbonStateDlg();

  enum { IDD = IDD_OPTIONS };

private:
  CBCGPComboBoxP m_RibbonTabs;
  CBCGPListBoxP  m_AvailablePanels;
  CBCGPListBoxP  m_SelectedPanels;

  RibbonTabList m_Data;
  RibbonTabList m_BackupData;

  void FillTabList(RibbonTabList& tabs);
  void FillPanelListWithCurrentSelectedTab(bool updateButtons = true);
  void UpdateButtons();

protected:
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();
  virtual void OnCancel();

protected:
  afx_msg void OnSelchangeRibbonTabs();
  afx_msg void OnAdd();
  afx_msg void OnRemove();
  afx_msg void OnReset();
  DECLARE_MESSAGE_MAP()
};
