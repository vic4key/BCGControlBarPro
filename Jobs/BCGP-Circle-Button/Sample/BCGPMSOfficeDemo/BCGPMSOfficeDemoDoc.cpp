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
// BCGPMSOfficeDemoDoc.cpp : implementation of the CBCGPMSOfficeDemoDoc class
//

#include "stdafx.h"
#include "BCGPMSOfficeDemo.h"

#include "BCGPMSOfficeDemoDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoDoc

IMPLEMENT_DYNCREATE(CBCGPMSOfficeDemoDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CBCGPMSOfficeDemoDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CBCGPMSOfficeDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoDoc construction/destruction

CBCGPMSOfficeDemoDoc::CBCGPMSOfficeDemoDoc()
{
	// TODO: add one-time construction code here

}

CBCGPMSOfficeDemoDoc::~CBCGPMSOfficeDemoDoc()
{
}

BOOL CBCGPMSOfficeDemoDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CBCGPMSOfficeDemoDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CBCGPMSOfficeDemoCntrItem(preo, (CBCGPMSOfficeDemoDoc*) this);
}

void CBCGPMSOfficeDemoDoc::OnFileClose()
{
	if (AfxGetMainWnd()->GetSafeHwnd() != NULL)
	{
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoDoc serialization

void CBCGPMSOfficeDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPMSOfficeDemoDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CBCGPMSOfficeDemoDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOfficeDemoDoc commands
