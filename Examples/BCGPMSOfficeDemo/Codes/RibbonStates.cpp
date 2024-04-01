#include "stdafx.h"
#include "RibbonStates.h"

namespace RibbonStates
{

CRibbonTabs::CRibbonTabs()
{
  Initialize();
}

CRibbonTabs::~CRibbonTabs()
{
}

RibbonStates::CRibbonTabs::RibbonTabList& CRibbonTabs::GetTabList()
{
  return m_TabList;
}

void CRibbonTabs::SetTabList(RibbonTabList& tabs)
{
  m_TabList = tabs;
}

String CRibbonTabs::GetTabName(eRibbonTabIndex tab) const
{
  String result = L"";

  switch (tab)
  {
  case RIBBON_PATIENT_TAB:
    result = L"Patient Tab";
    break;
  case RIBBON_IMAGES_TAB:
    result = L"Image Tab";
    break;
  case RIBBON_FUSION_TAB:
    result = L"Fusion Tab";
    break;
  default:
    break;
  }

  return result;
}

CRibbonTabs::RibbonPanelList* CRibbonTabs::GetpPanelList(eRibbonTabIndex tab)
{
  auto it = m_TabList.find(tab);

  if (it == m_TabList.end())
  {
    return nullptr;
  }

  return &(it->second);
}

void CRibbonTabs::AddPanel(RibbonPanelList& panels, String name, bool visible)
{
  panels.push_back(RibbonPanel(name, visible));
}

void CRibbonTabs::Initialize()
{
  m_TabList.clear();

  // Patient Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, L"Patient - Patient");
    AddPanel(panels, L"Patient - Patient Model");
    AddPanel(panels, L"Patient - Image Series");
    m_TabList[eRibbonTabIndex::RIBBON_PATIENT_TAB] = panels;
  }
  // Image Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, L"Image - Fiducial Markers");
    AddPanel(panels, L"Image - Patient Origin");
    AddPanel(panels, L"Image - Imaging Center");
    m_TabList[eRibbonTabIndex::RIBBON_IMAGES_TAB] = panels;
  }
  // Fusion Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, L"Fusion - View");
    AddPanel(panels, L"Fusion - Registration");
    AddPanel(panels, L"Fusion - Auto Fiducial Markers");
    m_TabList[eRibbonTabIndex::RIBBON_FUSION_TAB] = panels;
  }
}

}; // namespace RibbonStates