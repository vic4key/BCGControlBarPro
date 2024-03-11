/**
 * @file   BCGPCircleButton.h
 * @author Vic P.
 * @brief  Header for CBCGPCircleButton
 */

#pragma once

class CBCGPButton;

class CBCGPCircleButton : public CBCGPButton
{
  DECLARE_DYNCREATE(CBCGPCircleButton)

public:
  CBCGPCircleButton();
  virtual ~CBCGPCircleButton();

  virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
  virtual void OnFillBackground(CDC* pDC, const CRect& rectClient);
  virtual void OnDrawBorder(CDC* pDC, CRect& rectClient, UINT uiState);

protected:
  DECLARE_MESSAGE_MAP()
};
