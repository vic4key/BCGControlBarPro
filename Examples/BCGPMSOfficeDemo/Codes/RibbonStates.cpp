#include "stdafx.h"
#include "RibbonStates.h"

namespace RibbonStates
{

RibbonTabs::RibbonTabs()
{
  Initialize();
}

RibbonTabs::~RibbonTabs()
{
}

RibbonStates::RibbonTabs::RibbonTabList& RibbonTabs::GetTabList()
{
  return m_TabList;
}

void RibbonTabs::SetTabList(RibbonTabList& tabs)
{
  m_TabList = tabs;
}

RibbonTabs::RibbonPanelList* RibbonTabs::GetpPanelList(const String& tab)
{
  auto it = m_TabList.find(tab);
  if (it == m_TabList.end())
  {
    return nullptr;
  }

  return &(it->second);
}

void RibbonTabs::AddPanel(RibbonPanelList& panels, String name, bool visible)
{
  panels.push_back(RibbonPanel(name, visible));
}

void RibbonTabs::Initialize()
{
  m_TabList.clear();

  // Patient Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, L"Patient - Patient");
    AddPanel(panels, L"Patient - Patient Model");
    AddPanel(panels, L"Patient - Image Series");
    m_TabList.insert({ L"Patient Tab",  panels });
  }
  // Image Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, L"Image - Fiducial Markers");
    AddPanel(panels, L"Image - Patient Origin");
    AddPanel(panels, L"Image - Imaging Center");
    m_TabList.insert({ L"Image Tab", panels });
  }
  // Fusion Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, L"Fusion - View");
    AddPanel(panels, L"Fusion - Registration");
    AddPanel(panels, L"Fusion - Auto Fiducial Markers");
    m_TabList.insert({ L"Fusion Tab", panels });
  }
}

}; // namespace RibbonStates