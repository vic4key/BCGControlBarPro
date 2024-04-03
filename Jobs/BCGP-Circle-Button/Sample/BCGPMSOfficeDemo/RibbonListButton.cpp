// *******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2017 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
// *******************************************************************************
//
// RibbonListButton.cpp : implementation file
//

#include "stdafx.h"
#include "RibbonListButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct CFontGalleryItem
{
	CFontGalleryItem(const CString& strFont1, const CString& strFont2) :
		m_strName1(strFont1),
		m_strName2(strFont2)
	{
		LOGFONT lf;
		ZeroMemory(&lf, sizeof (LOGFONT));
		
		lstrcpy(lf.lfFaceName, m_strName1);
		
		lf.lfHeight         = -14;
		lf.lfWeight         = FW_BOLD;
		lf.lfCharSet        = DEFAULT_CHARSET;
		lf.lfOutPrecision   = OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
		lf.lfQuality        = DEFAULT_QUALITY;
		lf.lfPitchAndFamily = DEFAULT_PITCH;
		
		m_Font1.CreateFontIndirect(&lf);
		
		lstrcpy(lf.lfFaceName, m_strName2);
		
		lf.lfHeight         = -12;
		lf.lfWeight         = FW_NORMAL;
		
		m_Font2.CreateFontIndirect(&lf);
	}

	CString	m_strName1;
	CFont	m_Font1;

	CString	m_strName2;
	CFont	m_Font2;
};

IMPLEMENT_DYNCREATE (CRibbonListFontButton, CBCGPRibbonPaletteButton)

CRibbonListFontButton::~CRibbonListFontButton()
{
	for (int i = 0; i < m_arUserData.GetSize(); i++)
	{
		CFontGalleryItem* pItem = (CFontGalleryItem*)m_arUserData[i];
		if (pItem != NULL)
		{
			delete pItem;
		}
	}
}

void CRibbonListFontButton::SetItem(int nIndex, const CString& strLabel, const CString& strFont1, const CString& strFont2)
{
	SetItemToolTip(nIndex, strLabel);
	SetItemUserData(nIndex, (DWORD_PTR)new CFontGalleryItem(strFont1, strFont2));
}

CSize CRibbonListFontButton::GetComboItemTextSize(CDC* pDC, CBCGPRibbonPaletteIcon* pIcon)
{
	return DrawText(pDC, pIcon, CRect(0, 0, 0, 0), TRUE);
}

void CRibbonListFontButton::OnDrawComboItemText(CDC* pDC, CBCGPRibbonPaletteIcon* pIcon, CRect rectText)
{
	DrawText(pDC, pIcon, rectText, FALSE);
}

CSize CRibbonListFontButton::DrawText(CDC* pDC, CBCGPRibbonPaletteIcon* pIcon, CRect rectText, BOOL bCalcOnly)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(pIcon);
	
	CFontGalleryItem* pItem = (CFontGalleryItem*)GetItemUserData(pIcon->GetIndex());
	if (pItem == NULL)
	{
		return CSize(0, 0);
	}
	
	CString strLabel = pIcon->GetText();
	if (strLabel.IsEmpty())
	{
		strLabel = GetIconTextLabel(pIcon);
	}

	UINT nDTFlags = DT_TOP | DT_SINGLELINE | DT_LEFT;
	if (bCalcOnly)
	{
		nDTFlags |= DT_CALCRECT;
	}

	CSize size(0, 0);

	CFont* pOldFont = pDC->SelectObject (&globalData.fontBold);
	ASSERT_VALID(pOldFont);
	
	int nHeight = pDC->DrawText(strLabel, rectText, nDTFlags);
	rectText.OffsetRect (0, nHeight);

	size.cy += nHeight;
	size.cx = max(size.cx, rectText.Width());
	
	pDC->SelectObject (&pItem->m_Font1);
	
	nHeight = pDC->DrawText (pItem->m_strName1, rectText, nDTFlags);
	rectText.OffsetRect (0, nHeight);
	
	size.cy += nHeight;
	size.cx = max(size.cx, rectText.Width());

	pDC->SelectObject (&pItem->m_Font2);
	nHeight = pDC->DrawText (pItem->m_strName2, rectText, nDTFlags);
	
	size.cy += nHeight;
	size.cx = max(size.cx, rectText.Width());

	pDC->SelectObject (pOldFont);

	return size;
}

void CRibbonListFontButton::CopyFrom (const CBCGPBaseRibbonElement& s)
{
	ASSERT_VALID(this);
	
	CBCGPRibbonPaletteButton::CopyFrom (s);

	CRibbonListFontButton& src = (CRibbonListFontButton&)s;

	for (int i = 0; i < src.m_arUserData.GetSize(); i++)
	{
		CFontGalleryItem* pSrcItem = (CFontGalleryItem*)src.m_arUserData[i];
		if (pSrcItem != NULL)
		{
			SetItemUserData(i, (DWORD_PTR)new CFontGalleryItem(pSrcItem->m_strName1, pSrcItem->m_strName2));
		}
	}
}
