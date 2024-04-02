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
#if !defined(AFX_RIBBONLISTBUTTON_H__46553F75_B494_4B85_A707_701639C71BD7__INCLUDED_)
#define AFX_RIBBONLISTBUTTON_H__46553F75_B494_4B85_A707_701639C71BD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RibbonListButton.h : header file
//

class CRibbonListFontButton : public CBCGPRibbonPaletteButton  
{
	DECLARE_DYNCREATE(CRibbonListFontButton)

public:
	virtual ~CRibbonListFontButton();
	void SetItem(int nIndex, const CString& strLabel, const CString& strFont1, const CString& strFont2);

protected:

	virtual CSize GetComboItemTextSize(CDC* pDC, CBCGPRibbonPaletteIcon* pIcon);
	virtual void OnDrawComboItemText(CDC* pDC, CBCGPRibbonPaletteIcon* pIcon, CRect rectText);
	virtual void CopyFrom(const CBCGPBaseRibbonElement& s);

	CSize DrawText(CDC* pDC, CBCGPRibbonPaletteIcon* pIcon, CRect rectText, BOOL bCalcOnly);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONLISTBUTTON_H__46553F75_B494_4B85_A707_701639C71BD7__INCLUDED_)

