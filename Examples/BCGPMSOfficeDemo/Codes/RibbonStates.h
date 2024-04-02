#pragma once

#include "SingletonT.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#define String std::wstring
#define Pair std::pair
#define List std::vector
#define Dict std::unordered_map
#define Ptr  std::unique_ptr

namespace RibbonStates
{

struct RibbonPanel
{
  String m_Name;
  bool m_Visible;
  int m_Image;

  RibbonPanel() = delete;

  RibbonPanel(const String& name, const bool visible = true, const int image = -1)
  {
    m_Name    = name;
    m_Visible = visible;
    m_Image   = image;
  };

  RibbonPanel(const RibbonPanel& right)
  {
    m_Name    = right.m_Name;
    m_Visible = right.m_Visible;
    m_Image   = right.m_Image;
  };

  const RibbonPanel& operator = (const RibbonPanel& right)
  {
    m_Name    = right.m_Name;
    m_Visible = right.m_Visible;
    m_Image   = right.m_Image;
    return (*this);
  };

  bool operator == (const RibbonPanel& right) const
  {
    return m_Name == right.m_Name;
  };

  bool operator != (const RibbonPanel &right) const
  {
    return !(*this == right);
  }
};

using RibbonPanelList = List<RibbonPanel>;
using RibbonTabList = Dict<String, RibbonPanelList>;

struct RibbonTab
{
  RibbonPanelList& m_Panels;

  RibbonTab(RibbonPanelList& panels) : m_Panels(panels) {}

  void AddPanel(const String& name, const bool visible = true, const int image = -1)
  {
    m_Panels.push_back(RibbonPanel(name, visible, image));
  }
};

/**
 * Ribbon Tab Manager
 */
class RibbonTabs : public SingletonT<RibbonTabs>
{
public:
  friend RibbonTab;

  RibbonTabs();
  virtual ~RibbonTabs();

  /**
   * Gets the tab list.
   * @return The tab list.
   */
  RibbonTabList& GetTabList();

  /**
   * Sets the tab list.
   * @param[in] tabs The tab list.
   */
  void SetTabList(RibbonTabList& tabs);

  /**
   * Adds a tab to tab list.
   * @param[in] tab The tab name.
   */
  Ptr<RibbonTab> AddTab(const String& tab);

  /**
   * Gets a list of panels in the tab.
   * @param[in]  tab The tab name.
   * @return The list of panels in the tab.
   */
  RibbonPanelList* GetpPanelList(const String& tab);

private:
  RibbonTabList m_TabList;
};

}; // namespace RibbonStates