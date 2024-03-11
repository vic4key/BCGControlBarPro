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

  virtual CSize SizeToContent(BOOL bCalcOnly = FALSE);

  virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
  virtual void OnFillBackground(CDC* pDC, const CRect& rectClient);
  virtual void OnDrawBorder(CDC* pDC, CRect& rectClient, UINT uiState);

protected:
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  DECLARE_MESSAGE_MAP()
};
