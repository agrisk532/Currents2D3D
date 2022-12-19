// Proppage3DSetupAtoms.cpp : implementation file
//

#include "stdafx.h"
#include "currents2d3d.h"
#include "Proppage3DSetupAtoms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Proppage3DSetupAtoms property page

IMPLEMENT_DYNCREATE(Proppage3DSetupAtoms, CPropertyPage)

Proppage3DSetupAtoms::Proppage3DSetupAtoms() : CPropertyPage(Proppage3DSetupAtoms::IDD)
{
	//{{AFX_DATA_INIT(Proppage3DSetupAtoms)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Proppage3DSetupAtoms::~Proppage3DSetupAtoms()
{
}

void Proppage3DSetupAtoms::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Proppage3DSetupAtoms)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Proppage3DSetupAtoms, CPropertyPage)
	//{{AFX_MSG_MAP(Proppage3DSetupAtoms)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Proppage3DSetupAtoms message handlers
