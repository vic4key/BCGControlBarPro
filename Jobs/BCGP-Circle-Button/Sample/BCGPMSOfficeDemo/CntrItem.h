//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2017 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// CntrItem.h : interface of the CBCGPMSOfficeDemoCntrItem class
//

#if !defined(AFX_CNTRITEM_H__2D1B8BC9_BF1E_49DD_B313_F3626778189D__INCLUDED_)
#define AFX_CNTRITEM_H__2D1B8BC9_BF1E_49DD_B313_F3626778189D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPMSOfficeDemoDoc;
class CBCGPMSOfficeDemoView;

class CBCGPMSOfficeDemoCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CBCGPMSOfficeDemoCntrItem)

// Constructors
public:
	CBCGPMSOfficeDemoCntrItem(REOBJECT* preo = NULL, CBCGPMSOfficeDemoDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CBCGPMSOfficeDemoDoc* GetDocument()
		{ return (CBCGPMSOfficeDemoDoc*)CRichEditCntrItem::GetDocument(); }
	CBCGPMSOfficeDemoView* GetActiveView()
		{ return (CBCGPMSOfficeDemoView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSOfficeDemoCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);

// Implementation
public:
	~CBCGPMSOfficeDemoCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	UINT	m_uiCategoryID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__2D1B8BC9_BF1E_49DD_B313_F3626778189D__INCLUDED_)
