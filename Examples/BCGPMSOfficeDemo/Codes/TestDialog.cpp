/**
 * @file   TestDialog.cpp
 * @author Vic P.
 * @brief  Implementation for CBCGPCircleButton
 */

#include "stdafx.h"
#include "TestDialog.h"

#include <BCGPDialog.h>
#include <BCGPMessageBox.h>

#define UpdateButtons()\
  m_push_button.SetImageAutoScale();\
  m_push_button.Invalidate();\
  m_circle_button.SetImageAutoScale();\
  m_circle_button.Invalidate();

IMPLEMENT_DYNCREATE(TestDialog, CBCGPDialog)

BEGIN_MESSAGE_MAP(TestDialog, CBCGPDialog)
  ON_COMMAND_RANGE(IDC_CIRCLE_BUTTON, IDC_PUSH_BUTTON_2, OnBnClickedButton)
  ON_BN_CLICKED(IDC_BUTTON_IMAGE, OnBnClickedButtonImage)
  ON_BN_CLICKED(IDC_BUTTON_IMAGE_RIGHT, OnBnClickedButtonImageRight)
END_MESSAGE_MAP()

TestDialog::TestDialog(CWnd* pParent)
  : CBCGPDialog(TestDialog::IDD, pParent)
  , m_button_with_image(FALSE)
  , m_button_right_image(FALSE)
{
  EnableVisualManagerStyle();
}

TestDialog::~TestDialog()
{
}

void TestDialog::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_CIRCLE_BUTTON, m_circle_button);
  DDX_Control(pDX, IDC_CIRCLE_BUTTON_2, m_circle_button_2);
  DDX_Control(pDX, IDC_PUSH_BUTTON, m_push_button);
  DDX_Control(pDX, IDC_PUSH_BUTTON_2, m_push_button_2);
  DDX_Check(pDX, IDC_BUTTON_IMAGE, m_button_with_image);
  DDX_Check(pDX, IDC_BUTTON_IMAGE_RIGHT, m_button_right_image);
}

void TestDialog::OnBnClickedButton(UINT ID)
{
  if (auto pButton = GetDlgItem(ID))
  {
    CString text;
    pButton->GetWindowTextW(text);
    BCGPMessageBox(text);
  }
}

void TestDialog::OnBnClickedButtonImage()
{
  UpdateData();

  if (m_button_with_image)
  {
    m_circle_button.SetImage(IDB_BTN1_32, IDB_BTN1_HOT_32, 0, IDB_BTN1_PRESSED_32);
    m_push_button.SetImage(IDB_BTN1_32, IDB_BTN1_HOT_32, 0, IDB_BTN1_PRESSED_32);
  }
  else
  {
    m_circle_button.SetImage((HBITMAP)NULL);
    m_push_button.SetImage((HBITMAP)NULL);
  }

  UpdateButtons();

  GetDlgItem(IDC_BUTTON_IMAGE_RIGHT)->EnableWindow(m_button_with_image);
}

void TestDialog::OnBnClickedButtonImageRight()
{
  UpdateData();

  m_push_button.m_bRighImage = m_button_right_image;
  m_circle_button.m_bRighImage = m_button_right_image;

  UpdateButtons();
}
