#pragma once

#include "SingletonT.h"

#include <string>
#include <vector>
#include <unordered_map>

#define String std::wstring
#define List std::vector
#define Dict std::unordered_map

namespace RibbonStates
{

struct RibbonPanel
{
  String m_Name;
  bool m_Visible;

  RibbonPanel()
  {
    m_Name    = L"";
    m_Visible = false;
  };

  RibbonPanel(const String& name, const bool visible = true)
  {
    m_Name    = name;
    m_Visible = visible;
  };

  RibbonPanel(const RibbonPanel& right)
  {
    m_Name    = right.m_Name;
    m_Visible = right.m_Visible;
  };

  const RibbonPanel& operator = (const RibbonPanel& right)
  {
    m_Name    = right.m_Name;
    m_Visible = right.m_Visible;
    return (*this);
  };

  bool operator == (const RibbonPanel& right) const
  {
    return (m_Name == right.m_Name) && (m_Visible == right.m_Visible);
  };

  bool operator != (const RibbonPanel &right) const
  {
    return (!(*this == right));
  }
};

class RibbonTabs : public SingletonT<RibbonTabs>
{
public:
  RibbonTabs();
  virtual ~RibbonTabs();

  typedef List<RibbonPanel> RibbonPanelList;
  typedef Dict<String, RibbonPanelList> RibbonTabList;

  /**
   * Initializes the ribbon states.
   */
  void Initialize();

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

private:
  RibbonTabList m_TabList;

  /**
   * Gets a list of panels in the tab.
   * @param[in]  tab The tab name.
   * @return The list of panels in the tab.
   */
  RibbonPanelList* GetpPanelList(const String& tab);

  /**
   * Adds panel to panel list.
   * @param[out] panels The panel list.
   * @param[in]  name The panel name.
   * @param[in]  visible The visible state.
   */
  void AddPanel(RibbonPanelList& panels, String name, bool visible = true);
};

}; // namespace RibbonStates