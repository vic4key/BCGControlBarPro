#pragma once

class CBCGPButton;

class BCGPCircleButton : public CBCGPButton
{
  DECLARE_DYNCREATE(BCGPCircleButton)

public:
  BCGPCircleButton();
  virtual ~BCGPCircleButton();

  virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
  virtual void OnFillBackground(CDC* pDC, const CRect& rectClient);
  virtual void OnDrawBorder(CDC* pDC, CRect& rectClient, UINT uiState);

protected:
  DECLARE_MESSAGE_MAP()
};
