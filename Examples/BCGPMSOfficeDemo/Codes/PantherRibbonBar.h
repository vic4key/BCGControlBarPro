#pragma once

#include <map>
#include <string>

namespace RibbonStates
{

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

static std::map<resid_t, std::wstring> IDS_STR_MAPPING = {
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

} // RibbonStates