#include "stdafx.h"
#include "RibbonStates.h"

namespace RibbonStates
{

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

void CRibbonTabs::Initialize()
{
  m_TabList.clear();

  // Patient Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, eRibbonPanel::PatientPatient, L"Patient - Patient");
    AddPanel(panels, eRibbonPanel::PatientPatientModels, L"Patient - Patient Model");
    AddPanel(panels, eRibbonPanel::PatientImageSeries, L"Patient - Image Series");
    m_TabList[eRibbonTabIndex::RIBBON_PATIENT_TAB] = panels;
  }
  // Image Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, eRibbonPanel::ImageFiducialMarkers, L"Image - Fiducial Markers");
    AddPanel(panels, eRibbonPanel::ImagePatientOrigin, L"Image - Patient Origin");
    AddPanel(panels, eRibbonPanel::ImageImagingCenter, L"Image - Imaging Center");
    m_TabList[eRibbonTabIndex::RIBBON_IMAGES_TAB] = panels;
  }
  // Fusion Tab
  {
    RibbonPanelList panels;
    AddPanel(panels, eRibbonPanel::FusionView, L"Fusion - View");
    AddPanel(panels, eRibbonPanel::FusionRegistration, L"Fusion - Registration");
    AddPanel(panels, eRibbonPanel::FusionAutoFiducialMarker, L"Fusion - Auto Fiducial Markers");
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

  fnInitializePanelMapOfEnumString();
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