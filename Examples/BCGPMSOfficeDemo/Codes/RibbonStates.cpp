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

CStringP CRibbonTabs::GetTabName(eRibbonTabIndex tab) const
{
  CStringP result = L"";

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

void CRibbonTabs::UpdateProSIMSettings()
{
  // TODO: Vic. Temporary. Save settings.
}

CStringP CRibbonTabs::TabEnumToString(eRibbonTabIndex tab, const CStringP& prefix)
{
  CStringP result = prefix;
  result += GetTabName(tab);
  return result;
}

CStringP CRibbonTabs::PanelEnumToString(eRibbonPanel panel, const CStringP& prefix)
{
  CStringP result = prefix;
  result += m_PanelMapOfEnumString[panel];
  return result;
}

RibbonStates::eRibbonPanel CRibbonTabs::PanelStringToEnum(const CStringP& name)
{
  eRibbonPanel result = eRibbonPanel::PanelCount;

  for (auto& e : m_PanelMapOfEnumString)
  {
    if (e.second == name)
    {
      result = e.first;
      break;
    }
  }

  return result;
}

CStringP CRibbonTabs::PanelGetResourceString(eRibbonPanel panel)
{
  CStringP result = L"";
  result = LoadRCString(m_PanelMapOfEnumResource[panel]);
  return result;
}

void CRibbonTabs::AddPanel(RibbonPanelList& panels, eRibbonPanel panel, CStringP name, bool visible)
{
  //name = name.Strip(CStringP::Both);
  panels.push_back(RibbonPanel(panel, name, visible));
}

void CRibbonTabs::AddPanel(RibbonPanelList& panels, eRibbonPanel panel, resid_t nameID, bool visible)
{
  CStringP name;
  name = LoadRCString(nameID);
  AddPanel(panels, panel, name, visible);
}

bool CRibbonTabs::Load()
{
  /*auto fnExtractPanelEnumName = [](CSetting* pSection) -> CStringP
  {
    CStringP result = L"";

    if (pSection == nullptr)
    {
      return result;
    }

    auto name = pSection->GetName();

    if (name.Contains(PanelPrefix))
    {
      result = name.Right(name.Length() - lstrlenW(PanelPrefix));
      result = result.Strip(CStringP::Both);
    }

    return result;
  };

  auto pProSIMSettings = GetpProSIMSettings();
  if (pProSIMSettings == nullptr)
  {
    return false;
  }

  int numTabs = int(eRibbonTabIndex::RIBBON_NUM_TAB);

  for (int i = 0; i < numTabs; i++)
  {
    // for each Tab Section

    auto tab = eRibbonTabIndex(i);

    auto nameTabSection = TabEnumToString(tab);
    auto pTabSection = pProSIMSettings->FindSetting(nameTabSection);
    if (pTabSection == nullptr)
    {
      continue;
    }

    RibbonPanelList panels;

    CLCursor<CSetting> pPanelSectionsC(pTabSection->GetpSettings());
    while (auto pPanelSection = pPanelSectionsC())
    {
      // for each Panel Section

      auto pPanelVisible = pPanelSection->FindSetting(PanelVisibleSetting, true);
      if (pPanelVisible == nullptr)
      {
        continue;
      }

      auto panelEnumName = fnExtractPanelEnumName(pPanelSection);
      if (panelEnumName.Length() == 0)
      {
        continue;
      }

      auto panel = PanelStringToEnum(panelEnumName);
      if (panel == eRibbonPanel::PanelCount)
      {
        continue;
      }

      auto name  = PanelGetResourceString(panel);
      if (name.Length() == 0)
      {
        continue;
      }

      auto visible = pPanelVisible->GetBoolValue();

      // for specific cases
      if (!IsPanelAvailable(panel))
      {
        visible = false;
      }

      // Update visible panel state.
      SetVisible(tab, panel, visible);
    }

    if (!panels.empty())
    {
      std::sort(panels.begin(), panels.end(), [](const RibbonPanel& v1, const RibbonPanel& v2) -> bool
      {
        return int(v1.m_Panel) < int(v2.m_Panel);
      });

      m_TabList[tab] = panels;
    }
  }*/

  return true;
}

void CRibbonTabs::Reload()
{
  Initialize();
  Load();
  //CProSIM::UpdateAllViews(nullptr, UV_ACTIVATE_RIBBON);
}

bool CRibbonTabs::Store()
{
  /*auto pProSIMSettings = GetpProSIMSettings();
  if (pProSIMSettings == nullptr)
  {
    return false;
  }

  for (auto& tab : m_TabList)
  {
    // for each Tab Section

    auto nameTabSection = TabEnumToString(tab.first);
    auto pTabSection = pProSIMSettings->FindSetting(nameTabSection);
    if (pTabSection == nullptr)
    {
      pTabSection = new CSetting(nameTabSection);
      pProSIMSettings->AddSetting(pTabSection);
    }

    for (auto& panel : tab.second)
    {
      // for each Panel Section
      auto sPanelSection = PanelEnumToString(panel.m_Panel);
      auto pPanelSection = pTabSection->FindSetting(sPanelSection);
      if (pPanelSection == nullptr)
      {
        pPanelSection = new CSetting(sPanelSection); 
        pTabSection->AddSetting(pPanelSection);
      }
      auto pVisibleSetting = pPanelSection->FindSetting(PanelVisibleSetting);
      if (pVisibleSetting == nullptr)
      {
        pVisibleSetting = new CSetting(PanelVisibleSetting, panel.m_Visible);
        pPanelSection->AddSetting(pVisibleSetting);
      }
      else
      {
        pVisibleSetting->SetBoolValue(panel.m_Visible);
      }
    }
  }*/

  return true;
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