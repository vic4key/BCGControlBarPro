#pragma once

#include <BCGPDialog.h>
#include "resource.h"

using CBCGPDialogP   = CBCGPDialog;
using CBCGPComboBoxP = CBCGPComboBox;
using CBCGPListBoxP  = CBCGPListBox;

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

protected:
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);

protected:
  DECLARE_MESSAGE_MAP()
};
