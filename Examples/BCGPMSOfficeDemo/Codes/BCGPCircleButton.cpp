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

static const COLORREF clrDefault = (COLORREF)-1;

IMPLEMENT_DYNCREATE(CBCGPCircleButton, CBCGPButton)

BEGIN_MESSAGE_MAP(CBCGPCircleButton, CBCGPButton)
END_MESSAGE_MAP()

CBCGPCircleButton::CBCGPCircleButton() : CBCGPButton()
{
  m_bTransparent = TRUE;
}

CBCGPCircleButton::~CBCGPCircleButton()
{
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

  COLORREF color_normal  = globalData.clrBarHilite;
  COLORREF color_hover   = pVM->GetHighlightedColor(0);
  COLORREF color_pressed = pVM->GetHighlightedColor(1);

  if (dynamic_cast<CBCGPVisualManager2016*>(pVM) != nullptr)
  {
    auto style = CBCGPVisualManager2016::GetStyle();
    if (style == CBCGPVisualManager2016::Style::Office2016_Black)
    {
      //auto m_clrControl = pVM->GetControlFillColor();
      //color_normal = m_clrControl;
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

	// CBCGPVisualManagerVS2012::OnDrawPushButton
	auto style = CBCGPVisualManagerVS2012::GetStyle();
	auto pen_color = style == CBCGPVisualManagerVS2012::Style::VS2012_Dark ?
    globalData.clrBarShadow : globalData.clrBarDkShadow;

  CBCGPDrawManager dm(*pDC);
  dm.DrawEllipse(rectClient, clrDefault, pen_color);
}
