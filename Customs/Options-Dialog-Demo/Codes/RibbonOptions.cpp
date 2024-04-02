/**
 * @file   RibbonOptions.cpp
 * @author Vic P.
 * @brief  Implementation for RibbonOptions's Data Models
 */

#include "stdafx.h"
#include "RibbonOptions.h"

/**
 * Ribbon Tab Manager
 */

RibbonTabs::RibbonTabs()
{
  m_TabList.clear();
}

RibbonTabs::~RibbonTabs()
{
}

RibbonTabList& RibbonTabs::GetTabList()
{
  return m_TabList;
}

void RibbonTabs::SetTabList(RibbonTabList& tabs)
{
  m_TabList = tabs;
}

Ptr<RibbonTab> RibbonTabs::AddTab(const String& tab)
{
  Ptr<RibbonTab> ptr(new RibbonTab(m_TabList[tab]));
  return ptr;
}

RibbonPanelList* RibbonTabs::GetpPanelList(const String& tab)
{
  auto it = m_TabList.find(tab);
  if (it == m_TabList.end())
  {
    return nullptr;
  }

  return &(it->second);
}
