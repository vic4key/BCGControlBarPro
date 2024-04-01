#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "SingletonT.h"

using String  = std::wstring;
using resid_t = unsigned int;


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

// Patient Tab
const resid_t IDS_PATIENT_TAB = 101;
const resid_t IDS_PATIENT_MODELS = 102;
const resid_t IDS_DEF_IMAGE_SERIES = 103;
// Image Tab
const resid_t IDS_FIDUCIAL_MARKERS = 201;
const resid_t IDS_PATIENT_ORIGIN = 202;
const resid_t IDS_IMAGING_CENTER = 203;
// Fusion Tab
const resid_t IDS_FUSION_VIEW = 301;
const resid_t IDS_REGISTRATION = 302;
const resid_t IDS_AUTO_FIDUCIAL_MARKER = 303;

static std::unordered_map<resid_t, std::wstring> IDS_STR_MAPPING = {
  // Patient Tab
  { IDS_PATIENT_TAB, L"Patient - Patient" },
  { IDS_PATIENT_MODELS, L"Patient - Patient Model" },
  { IDS_DEF_IMAGE_SERIES, L"Patient - Image Series" },
  // Image Tab
  { IDS_FIDUCIAL_MARKERS, L"Image - Fiducial Markers" },
  { IDS_PATIENT_ORIGIN, L"Image - Patient Origin" },
  { IDS_IMAGING_CENTER, L"Image - Imaging Center" },
  // Fusion Tab
  { IDS_FUSION_VIEW, L"Fusion - View" },
  { IDS_REGISTRATION, L"Fusion - Registration" },
  { IDS_AUTO_FIDUCIAL_MARKER, L"Fusion - Auto Fiducial Markers" },
};

inline std::wstring LoadRCString(const resid_t id)
{
  return IDS_STR_MAPPING[id];
}



namespace RibbonStates
{

static const wchar_t TabPrefix[] = L"RibbonTab_";
static const wchar_t PanelPrefix[] = L"RibbonPanel_";

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

  typedef std::vector<RibbonPanel> RibbonPanelList;
  typedef std::unordered_map<eRibbonTabIndex, RibbonPanelList> RibbonTabList;
  typedef std::unordered_map<eRibbonPanel, String> RibbonPanelMapOfEnumString;
  typedef std::unordered_map<eRibbonPanel, resid_t> RibbonPanelMapOfEnumResource;

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
  String GetTabName(eRibbonTabIndex tab) const;

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
  void AddPanel(RibbonPanelList& panels, eRibbonPanel panel, String name, bool visible = true);
};

}; // namespace RibbonStates