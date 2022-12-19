// PropertyPageRegions.cpp : implementation file
//

#include "stdafx.h"
#include "Currents.h"
#include "resource.h"
#include "AtomCoordinates.h"
#include "currents2d3d.h"
#include "Currents3DDoc.h"
#include "MainFrm.h"
#include "Child3DFrame.h"
#include "PropertyPageRegions.h"
#include "PropertyPageRendMethod.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PropertyPageRegions property page

IMPLEMENT_DYNCREATE(PropertyPageRegions, CPropertyPage)

PropertyPageRegions::PropertyPageRegions() : CPropertyPage(PropertyPageRegions::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageRegions)
	m_RenderRegion = 0;
	//}}AFX_DATA_INIT
}

PropertyPageRegions::~PropertyPageRegions()
{
}

void PropertyPageRegions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageRegions)
	DDX_Radio(pDX, IDD_RENDREGIONS_ORIGINAL, m_RenderRegion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageRegions, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageRegions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
//   message handlers

