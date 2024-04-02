/**
 * @file   TestDialog.h
 * @author Vic P.
 * @brief  Header for CBCGPCircleButton
 */

#pragma once

#include "resource.h"
#include "BCGPCircleButton.h"

class CBCGPDialog;

class TestDialog : public CBCGPDialog
{
  DECLARE_DYNCREATE(TestDialog)

public:
  enum { IDD = IDD_TEST_DIALOG };

  TestDialog(CWnd* pParent = nullptr);
  virtual ~TestDialog();

protected:
  virtual void DoDataExchange(CDataExchange* pDX);

protected:
  afx_msg void OnBnClickedButton(UINT ID);
  afx_msg void OnBnClickedButtonImage();
  afx_msg void OnBnClickedButtonImageTop();
  afx_msg void OnBnClickedButtonImageRight();
  afx_msg void OnBnClickedSampleCircleButton();
  DECLARE_MESSAGE_MAP()

private:
  CBCGPCircleButton m_circle_button;
  CBCGPCircleButton m_circle_button_2;
  CBCGPCircleButton m_sample_circle_button;

  CBCGPButton m_push_button;
  CBCGPButton m_push_button_2;

  BOOL m_button_with_image;
  BOOL m_button_top_image;
  BOOL m_button_right_image;
};
