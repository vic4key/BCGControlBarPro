#include "stdafx.h"
#include "RibbonStates.h"

namespace RibbonStates
{
  /*CRibbonTabs::RibbonPanelMapOfEnumResource temp_PanelMapOfEnumResource =
  {
    // Patient Tab
    { eRibbonPanel::PatientPatient, m_PanelMapOfEnumResource[eRibbonPanel::PatientPatient] },
    { eRibbonPanel::PatientPatientModels, m_PanelMapOfEnumResource[eRibbonPanel::PatientPatientModels] },
    { eRibbonPanel::PatientImageSeries, m_PanelMapOfEnumResource[eRibbonPanel::PatientImageSeries] },

    // Image Tab
    { eRibbonPanel::ImageFiducialMarkers, m_PanelMapOfEnumResource[eRibbonPanel::ImageFiducialMarkers] },
    { eRibbonPanel::ImagePatientOrigin, m_PanelMapOfEnumResource[eRibbonPanel::ImagePatientOrigin] },
    { eRibbonPanel::ImageImagingCenter, m_PanelMapOfEnumResource[eRibbonPanel::ImageImagingCenter] },

    // Fusion Tab
    { eRibbonPanel::FusionView, m_PanelMapOfEnumResource[eRibbonPanel::FusionView] },
    { eRibbonPanel::FusionRegistration, m_PanelMapOfEnumResource[eRibbonPanel::FusionRegistration] },
    { eRibbonPanel::FusionAutoFiducialMarker, m_PanelMapOfEnumResource[eRibbonPanel::FusionAutoFiducialMarker] },
  }*/

const wchar_t PanelIDSetting[] = L"Panel";
const wchar_t PanelNameSetting[] = L"Name";
const wchar_t PanelVisibleSetting[] = L"Visible";

const wchar_t RibbonStatesSetting[] = L"RibbonStates";

CRibbonTabs::CRibbonTabs()
{
  InitializePanelMappingList();
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

RibbonPanel* CRibbonTabs::GetpPanel(eRibbonTabIndex tab, eRibbonPanel panel)
{
  RibbonPanel* result = nullptr;

  auto pPanelList = GetpPanelList(tab);
  if (pPanelList == nullptr)
  {
    return nullptr;
  }

  auto& panels = *pPanelList;

  for (auto& e : panels)
  {
    if (e.m_Panel == panel)
    {
      result = &e;
      break;
    }
  }

  return result;
}

bool CRibbonTabs::IsVisible(eRibbonTabIndex tab, eRibbonPanel panel)
{
  auto pPanel = GetpPanel(tab, panel);

  if (pPanel == nullptr)
  {
    return false;
  }

  return pPanel->m_Visible;
}

void CRibbonTabs::SetVisible(eRibbonTabIndex tab, eRibbonPanel panel, bool visible)
{
  auto pPanel = GetpPanel(tab, panel);

  if (pPanel == nullptr)
  {
    return;
  }

  pPanel->m_Visible = visible;
}

void CRibbonTabs::AddPanel(RibbonPanelList& panels, eRibbonPanel panel, String name, bool visible)
{
  panels.push_back(RibbonPanel(panel, name, visible));
}

void CRibbonTabs::AddPanel(RibbonPanelList& panels, eRibbonPanel panel, resid_t nameID, bool visible)
{
  String name;
  name = LoadRCString(nameID);
  AddPanel(panels, panel, name, visible);
}

void CRibbonTabs::Initialize()
{
  m_TabList.clear();

  // Patient Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, eRibbonPanel::PatientPatient, m_PanelMapOfEnumResource[eRibbonPanel::PatientPatient]);
    AddPanel(panels, eRibbonPanel::PatientPatientModels, m_PanelMapOfEnumResource[eRibbonPanel::PatientPatientModels]);
    AddPanel(panels, eRibbonPanel::PatientImageSeries, m_PanelMapOfEnumResource[eRibbonPanel::PatientImageSeries]);
    m_TabList[eRibbonTabIndex::RIBBON_PATIENT_TAB] = panels;
  }

  // Image Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, eRibbonPanel::ImageFiducialMarkers, m_PanelMapOfEnumResource[eRibbonPanel::ImageFiducialMarkers]);
    AddPanel(panels, eRibbonPanel::ImagePatientOrigin, m_PanelMapOfEnumResource[eRibbonPanel::ImagePatientOrigin]);
    AddPanel(panels, eRibbonPanel::ImageImagingCenter, m_PanelMapOfEnumResource[eRibbonPanel::ImageImagingCenter]);
    m_TabList[eRibbonTabIndex::RIBBON_IMAGES_TAB] = panels;
  }

  // Fusion Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, eRibbonPanel::FusionView, m_PanelMapOfEnumResource[eRibbonPanel::FusionView]);
    AddPanel(panels, eRibbonPanel::FusionRegistration, m_PanelMapOfEnumResource[eRibbonPanel::FusionRegistration]);
    AddPanel(panels, eRibbonPanel::FusionAutoFiducialMarker, m_PanelMapOfEnumResource[eRibbonPanel::FusionAutoFiducialMarker]);
    m_TabList[eRibbonTabIndex::RIBBON_FUSION_TAB] = panels;
  }

  // Update the hidden by default state of panels
  for (auto& tab : m_TabList)
  {
    for (auto& panel : tab.second)
    {
      if (IsPanelHiddenByDefault(panel.m_Panel))
      {
        panel.m_Visible = false;
      }
    }
  }
}

void CRibbonTabs::InitializePanelMappingList()
{
  auto fnInitializePanelMapOfEnumString = [&]()
  {
    #define Makepair_Stringize_eRibbonPanel(e) m_PanelMapOfEnumString[eRibbonPanel::e] = L#e

    m_PanelMapOfEnumString.clear();

    // Patient Tab
    Makepair_Stringize_eRibbonPanel(PatientPatient);
    Makepair_Stringize_eRibbonPanel(PatientPatientModels);
    Makepair_Stringize_eRibbonPanel(PatientImageSeries);

    // Image Tab
    Makepair_Stringize_eRibbonPanel(ImageFiducialMarkers);
    Makepair_Stringize_eRibbonPanel(ImagePatientOrigin);
    Makepair_Stringize_eRibbonPanel(ImageImagingCenter);

    // Fusion Tab
    Makepair_Stringize_eRibbonPanel(FusionView);
    Makepair_Stringize_eRibbonPanel(FusionRegistration);
    Makepair_Stringize_eRibbonPanel(FusionAutoFiducialMarker);
  };

  auto fnInitializePanelMapOfEnumResource = [&]()
  {
    m_PanelMapOfEnumResource.clear();
    // Patient Tab
    m_PanelMapOfEnumResource[eRibbonPanel::PatientPatient] = IDS_PATIENT_TAB;
    m_PanelMapOfEnumResource[eRibbonPanel::PatientPatientModels] = IDS_PATIENT_MODELS;
    m_PanelMapOfEnumResource[eRibbonPanel::PatientImageSeries] = IDS_DEF_IMAGE_SERIES;
    // Image Tab
    m_PanelMapOfEnumResource[eRibbonPanel::ImageFiducialMarkers] = IDS_FIDUCIAL_MARKERS;
    m_PanelMapOfEnumResource[eRibbonPanel::ImagePatientOrigin] = IDS_PATIENT_ORIGIN;
    m_PanelMapOfEnumResource[eRibbonPanel::ImageImagingCenter] = IDS_IMAGING_CENTER;
    // Fusion Tab
    m_PanelMapOfEnumResource[eRibbonPanel::FusionView] = IDS_FUSION_VIEW;
    m_PanelMapOfEnumResource[eRibbonPanel::FusionRegistration] = IDS_REGISTRATION;
    m_PanelMapOfEnumResource[eRibbonPanel::FusionAutoFiducialMarker] = IDS_AUTO_FIDUCIAL_MARKER;
  };

  fnInitializePanelMapOfEnumString();
  fnInitializePanelMapOfEnumResource();
}

bool CRibbonTabs::IsPanelAvailable(eRibbonPanel panel)
{
  bool result = true;

  UNREFERENCED_PARAMETER(panel);

  return result;
}

bool CRibbonTabs::IsPanelHiddenByDefault(const eRibbonPanel panel)
{
  bool result = false;

  UNREFERENCED_PARAMETER(panel);

  return result;
}

bool CRibbonTabs::IsTabAlwaysVisible(const eRibbonTabIndex tab)
{
  eRibbonTabIndex tabs[] =
  {
    RIBBON_PATIENT_TAB,
    RIBBON_FUSION_TAB,
  };

  return std::find(std::begin(tabs), std::end(tabs), tab) != std::end(tabs);
}

}; // namespace RibbonStates