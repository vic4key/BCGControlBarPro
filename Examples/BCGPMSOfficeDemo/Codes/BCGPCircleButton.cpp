/**
 * @file   BCGPCircleButton.cpp
 * @author Vic P.
 * @brief  Implementation for CBCGPCircleButton
 */

#include "stdafx.h"
#include "BCGPCircleButton.h"

#include <Bcgglobals.h>
#include <BCGPButton.h>
#include <BCGPVisualManager.h>

class CBCGPEllipseEx : public CBCGPRect
{
public:
  CBCGPEllipseEx(const CBCGPRect& rect) : CBCGPRect(rect), m_ellipse(rect) {}
  virtual ~CBCGPEllipseEx() {}

  bool contains(const CPoint& point) const
  {
    if (!this->PtInRect(point))
    {
      return false;
    }

    CPoint center = this->CenterPoint();

    double semi_major_axis = this->Width()  / 2;
    double semi_minor_axis = this->Height() / 2;

    double normalized_x = (point.x - center.x) / semi_major_axis;
    double normalized_y = (point.y - center.y) / semi_minor_axis;

    return bcg_sqr(normalized_x) + bcg_sqr(normalized_y) <= 1.;
  }

private:
  CBCGPEllipse m_ellipse;
};

static const COLORREF clrDefault = (COLORREF)-1;

IMPLEMENT_DYNCREATE(CBCGPCircleButton, CBCGPButton)

BEGIN_MESSAGE_MAP(CBCGPCircleButton, CBCGPButton)
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

CBCGPCircleButton::CBCGPCircleButton() : CBCGPButton()
{
  m_bTransparent = TRUE;
}

CBCGPCircleButton::~CBCGPCircleButton()
{
}

CSize CBCGPCircleButton::SizeToContent(BOOL bCalcOnly)
{
  auto size = __super::SizeToContent(bCalcOnly);

  auto max_size = max(size.cx, size.cy);
  size.cx = max_size;
  size.cy = max_size;

  if (!bCalcOnly)
  {
    SetWindowPos(NULL, -1, -1, size.cx, size.cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
  }

  return size;
}

void CBCGPCircleButton::OnDraw(CDC* pDC, const CRect& rect, UINT uiState)
{
  m_clrText = globalData.clrBarText;
  __super::OnDraw(pDC, rect, uiState);
}

void CBCGPCircleButton::OnFillBackground(CDC* pDC, const CRect& rectClient)
{
  globalData.DrawParentBackground(this, pDC, LPRECT(&rectClient));

  BOOL bPressed = IsPressed();
  BOOL bHighlighted = IsHighlighted();
  BOOL bIsFocused = CWnd::GetFocus() == this;

  auto pVM = CBCGPVisualManager::GetInstance();

  COLORREF color_normal = globalData.clrBarHilite;
  COLORREF color_hover = pVM->GetHighlightedColor(0);
  COLORREF color_pressed = pVM->GetHighlightedColor(1);

  if (dynamic_cast<CBCGPVisualManager2016*>(pVM) != nullptr)
  {
    auto m_Style = CBCGPVisualManager2016::GetStyle();
    if (m_Style == CBCGPVisualManager2016::Style::Office2016_Black)
    {
      // @refer to `CBCGPVisualManagerVS2012.SetupColors.else` (BCGPVisualManagerVS2012.cpp)
      auto m_clrControl = CBCGPDrawManager::ColorMakeDarker(globalData.clrBarFace, .1);
      color_normal = m_clrControl;
    }
  }

  COLORREF color_background = color_normal;

  if (bPressed)
  {
    if (bHighlighted)
    {
      color_background = color_pressed;
    }
  }
  else if (bHighlighted || bIsFocused)
  {
    color_background = color_hover;
  }

  CBCGPDrawManager dm(*pDC);
  dm.DrawEllipse(rectClient, color_background, clrDefault);
}

void CBCGPCircleButton::OnDrawBorder(CDC* pDC, CRect& rectClient, UINT uiState)
{
  UNREFERENCED_PARAMETER(uiState);

  // @refer to CBCGPVisualManagerVS2012::OnDrawPushButton
  auto style = CBCGPVisualManagerVS2012::GetStyle();
  auto pen_color = style == CBCGPVisualManagerVS2012::Style::VS2012_Dark ?
    globalData.clrBarShadow : globalData.clrBarDkShadow;

  CBCGPDrawManager dm(*pDC);
  dm.DrawEllipse(rectClient, clrDefault, pen_color);
}

void CBCGPCircleButton::OnMouseMove(UINT nFlags, CPoint point)
{
  CRect rect;
  GetClientRect(rect);
  CBCGPEllipseEx ellipse(rect);
  __super::OnMouseMove(nFlags, ellipse.contains(point) ? point : CPoint(-1, -1));
}

void CBCGPCircleButton::OnLButtonDown(UINT nFlags, CPoint point)
{
  CRect rect;
  GetClientRect(rect);
  CBCGPEllipseEx ellipse(rect);
  if (ellipse.contains(point))
  {
    __super::OnLButtonDown(nFlags, point);
  }
}

void CBCGPCircleButton::OnLButtonUp(UINT nFlags, CPoint point)
{
  CRect rect;
  GetClientRect(rect);
  CBCGPEllipseEx ellipse(rect);
  if (ellipse.contains(point))
  {
    __super::OnLButtonUp(nFlags, point);
  }
}

void CBCGPCircleButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
  CRect rect;
  GetClientRect(rect);
  CBCGPEllipseEx ellipse(rect);
  if (ellipse.contains(point))
  {
    __super::OnLButtonDblClk(nFlags, point);
  }
}
