// PropertyPageAtoms.cpp : implementation file
//

#include "stdafx.h"
#include "currents2d3d.h"
#include "PropertyPageAtoms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PropertyPageAtoms property page

IMPLEMENT_DYNCREATE(PropertyPageAtoms, CPropertyPage)

PropertyPageAtoms::PropertyPageAtoms() : CPropertyPage(PropertyPageAtoms::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageAtoms)
	m_Ba = FALSE;
	m_Cu1 = FALSE;
	m_Cu2_1 = TRUE;
	m_Cu2_2 = TRUE;
	m_O1 = FALSE;
	m_O2_1 = FALSE;
	m_O2_2 = FALSE;
	m_O4 = FALSE;
	m_Y = FALSE;
	//}}AFX_DATA_INIT
}

PropertyPageAtoms::~PropertyPageAtoms()
{
}

void PropertyPageAtoms::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageAtoms)
	DDX_Check(pDX, IDC_PP__ATOMS_BA, m_Ba);
	DDX_Check(pDX, IDC_PP_ATOMS_CU1, m_Cu1);
	DDX_Check(pDX, IDC_PP_ATOMS_Cu2_1, m_Cu2_1);
	DDX_Check(pDX, IDC_PP_ATOMS_Cu2_2, m_Cu2_2);
	DDX_Check(pDX, IDC_PP_ATOMS_O1, m_O1);
	DDX_Check(pDX, IDC_PP_ATOMS_O2_1, m_O2_1);
	DDX_Check(pDX, IDC_PP_ATOMS_O2_2, m_O2_2);
	DDX_Check(pDX, IDC_PP_ATOMS_O4, m_O4);
	DDX_Check(pDX, IDC_PP_ATOMS_Y, m_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageAtoms, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageAtoms)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageAtoms message handlers
