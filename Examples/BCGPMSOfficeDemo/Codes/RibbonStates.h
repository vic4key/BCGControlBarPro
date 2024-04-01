#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "SingletonT.h"

using String = std::wstring;

#define List std::vector
#define Dict std::unordered_map

enum eRibbonTabIndex
{
  RIBBON_PATIENT_TAB,
  RIBBON_IMAGES_TAB,
  RIBBON_FUSION_TAB,
  RIBBON_NUM_TAB
};

enum eRibbonPanel
{
  // Patient Tab
  PatientPatient,
  PatientPatientModels,
  PatientImageSeries,
  // Image Tab
  ImageFiducialMarkers,
  ImagePatientOrigin,
  ImageImagingCenter,
  // Fusion Tab
  FusionView,
  FusionRegistration,
  FusionAutoFiducialMarker,
  // Count
  PanelCount
};

namespace RibbonStates
{

struct RibbonPanel
{
  eRibbonPanel m_Panel;
  String m_Name;
  bool m_Visible;

  RibbonPanel()
  {
    m_Panel   = eRibbonPanel::PanelCount;
    m_Name    = L"";
    m_Visible = false;
  };

  RibbonPanel(const eRibbonPanel panel, const String& name, bool visible = true)
  {
    m_Panel   = panel;
    m_Name    = name;
    m_Visible = visible;
  };

  RibbonPanel(const RibbonPanel& right)
  {
    m_Panel   = right.m_Panel;
    m_Name    = right.m_Name;
    m_Visible = right.m_Visible;
  };

  const RibbonPanel& operator = (const RibbonPanel& right)
  {
    m_Panel   = right.m_Panel;
    m_Name    = right.m_Name;
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

  typedef List<RibbonPanel> RibbonPanelList;
  typedef Dict<eRibbonTabIndex, RibbonPanelList> RibbonTabList;
  typedef Dict<eRibbonPanel, String> RibbonPanelMapOfEnumString;

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

  /**
   * Gets the tab name.
   * @param[in] tab The tab index.
   * @return The tab name.
   */
  String GetTabName(eRibbonTabIndex tab) const;

private:
  RibbonTabList m_TabList;
  RibbonPanelMapOfEnumString m_PanelMapOfEnumString;

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
   * @param[in] nameID The panel name.
   * @param[in] visible The visible state.
   */
  void AddPanel(RibbonPanelList& panels, eRibbonPanel panel, String name, bool visible = true);
};

}; // namespace RibbonStates