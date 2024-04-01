#pragma once

#include <map>
#include <string>
#include <vector>

#include "SingletonT.h"
#include "PantherRibbonBar.h"

using CStringP = std::wstring;
using resid_t  = unsigned int;

namespace RibbonStates
{

static const wchar_t TabPrefix[] = L"RibbonTab_";
static const wchar_t PanelPrefix[] = L"RibbonPanel_";

struct RibbonPanel
{
  eRibbonPanel m_Panel;
  CStringP m_Name;
  bool m_Visible;

  RibbonPanel()
  {
    m_Panel = eRibbonPanel::PanelCount;
    m_Name  = L"";
    m_Visible = false;
  };

  RibbonPanel(const eRibbonPanel panel, const CStringP& name, bool visible = true)
  {
    m_Panel = panel;
    m_Name  = name;
    m_Visible = visible;
  };

  RibbonPanel(const RibbonPanel& right)
  {
    m_Panel = right.m_Panel;
    m_Name  = right.m_Name;
    m_Visible = right.m_Visible;
  };

  const RibbonPanel& operator = (const RibbonPanel& right)
  {
    m_Panel = right.m_Panel;
    m_Name  = right.m_Name;
    m_Visible = right.m_Visible;
    return (*this);
  };

  bool operator == (const RibbonPanel& right) const
  {
    return ((m_Panel == right.m_Panel) && (m_Name == right.m_Name) && (m_Visible == right.m_Visible));
  };

  bool operator != (const RibbonPanel &right) const
  {
    return (!(*this == right));
  }
};

class CRibbonTabs : public SingletonT<CRibbonTabs>
{
public:
  CRibbonTabs();
  virtual ~CRibbonTabs();

  typedef std::vector<RibbonPanel> RibbonPanelList;
  typedef std::map<eRibbonTabIndex, RibbonPanelList> RibbonTabList;
  typedef std::map<eRibbonPanel, CStringP> RibbonPanelMapOfEnumString;
  typedef std::map<eRibbonPanel, resid_t> RibbonPanelMapOfEnumResource;

  /**
   * Initializes the ribbon states.
   */
  void Initialize();

  /**
   * Loads ribbon states.
   * @return true if succeed otherwise false.
   */
  bool Load();

  /**
   * Reloads ribbon states.
   */
  void Reload();

  /**
   * Stores ribbon states.
   * @return true if succeed otherwise false.
   */
  bool Store();

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
   * Gets the tab name.
   * @param[in] tab The tab index.
   * @return The tab name.
   */
  CStringP GetTabName(eRibbonTabIndex tab) const;

  /**
   * Gets a panel in tab.
   * @param[in] tab The tab index.
   * @param[in] panel The panel index.
   * @return The pointer of the panel.
   */
  RibbonPanel* GetpPanel(eRibbonTabIndex tab, eRibbonPanel panel);

  /**
   * Gets the panel visible state.
   * @param[in] tab The tab index.
   * @param[in] panel The panel index.
   * @return The panel visible state.
   */
  bool IsVisible(eRibbonTabIndex tab, eRibbonPanel panel);

  /**
   * Sets the panel visible state.
   * @param[in] tab The tab index.
   * @param[in] panel The panel index.
   * @param[in] visible The visible state.
   */
  void SetVisible(eRibbonTabIndex tab, eRibbonPanel panel, bool visible);

  /*
  / **
   * Sets a configuration to default section of Ribbon States.
   * @param[in] pConfig The configuration.
   * @return true if succeed otherwise false.
   * /
  bool SetConfig(CSetting* pConfig);

  / **
   * Gets a configuration from default section of Ribbon States.
   * @param[in] name The configuration name.
   * @return The configuration.
   * /
  CSetting* GetConfig(const CStringP& name);

  / **
   * Gets the ProSIM settings.
   * @return The ProSIM settings.
   * /
  CSetting* GetpProSIMSettings();
  */

  /**
   * Check if panel is available or not. 
   * @param[in] panel The panel needs checking.
   * @return the state specify that panel is available or not.
   */
  bool IsPanelAvailable(eRibbonPanel panel);

  /**
   * Check if the panel is hidden by default or not
   * @param[in] panel The panel needs checking.
   * @return the state specify that panel is hidden by default or not.
   */
  bool IsPanelHiddenByDefault(const eRibbonPanel panel);

  /**
   * Check if tab is always available or not.
   * @param[in] tab The rtab index.
   * @return true if the tab is always available otherwise it's not.
   */
  bool IsTabAlwaysVisible(const eRibbonTabIndex tab);

private:
  RibbonTabList m_TabList;

  RibbonPanelMapOfEnumString m_PanelMapOfEnumString;
  RibbonPanelMapOfEnumResource m_PanelMapOfEnumResource;

  /**
   * Initializes a map of pairs Panel Enum - Panel String.
   */
  void InitializePanelMappingList();

  /**
   * Gets a list of panels in the tab.
   * @param[in] tab The tab index.
   * @return The list of panels in the tab.
   */
  RibbonPanelList* GetpPanelList(eRibbonTabIndex tab);

  /**
   * Adds panel to panel list.
   * @param[out] panels The panel list.
   * @param[in] panel The panel index.
   * @param[in] nameID The resource id of the panel name.
   * @param[in] visible The visible state.
   */
  void AddPanel(RibbonPanelList& panels, eRibbonPanel panel, resid_t nameID, bool visible = true);

  /**
   * Adds panel to panel list.
   * @param[out] panels The panel list.
   * @param[in] panel The panel index.
   * @param[in] nameID The panel name.
   * @param[in] visible The visible state.
   */
  void AddPanel(RibbonPanelList& panels, eRibbonPanel panel, CStringP name, bool visible = true);

  /**
   * Converts the tab enumeration to string.
   * @param[in] tab The tab index.
   * @param[in] prefix The prefix.
   * @return The tab enumeration in string with the prefix.
   */
  CStringP TabEnumToString(eRibbonTabIndex tab, const CStringP& prefix = TabPrefix);

  /**
   * Converts the panel enumeration to string.
   * @param[in] panel The panel index.
   * @param[in] prefix The prefix.
   * @return The panel enumeration in string with the prefix.
   */
  CStringP PanelEnumToString(eRibbonPanel panel, const CStringP& prefix = PanelPrefix);

  /**
   * Converts the panel string to enumeration.
   * @param[in] name The panel name.
   * @return The panel enumeration.
   */
  eRibbonPanel PanelStringToEnum(const CStringP& name);

  /**
   * Gets resource string by panel enumeration.
   * @param[in] panel The panel index.
   * @return The resource string.
   */
  CStringP PanelGetResourceString(eRibbonPanel panel);

  /**
   * Updates the ProSIM settings.
   */
  void UpdateProSIMSettings();
};

}; // namespace RibbonStates