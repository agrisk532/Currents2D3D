// Modal3DPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "currents2d3d.h"
#include "Modal3DPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Modal3DPropSheet

IMPLEMENT_DYNAMIC(Modal3DPropSheet, CPropertySheet)

Modal3DPropSheet::Modal3DPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_PageAtoms);
	AddPage(&m_PageObjToRender);
	AddPage(&m_PageRenderMethod);
}


Modal3DPropSheet::~Modal3DPropSheet()
{
}


BEGIN_MESSAGE_MAP(Modal3DPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(Modal3DPropSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Modal3DPropSheet message handlers

