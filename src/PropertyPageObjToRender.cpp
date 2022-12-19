// PropertyPageObjToRender.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PropertyPageObjToRender.h"
#include "PropertyPageRegions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PropertyPageObjToRender property page

IMPLEMENT_DYNCREATE(PropertyPageObjToRender, CPropertyPage)

PropertyPageObjToRender::PropertyPageObjToRender() : CPropertyPage(PropertyPageObjToRender::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageObjToRender)
	m_ObjToRender = 0;
	//}}AFX_DATA_INIT
}

PropertyPageObjToRender::~PropertyPageObjToRender()
{
}

void PropertyPageObjToRender::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageObjToRender)
	DDX_Radio(pDX, IDD_PP_RENDER_RADIO_CURR1D, m_ObjToRender);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageObjToRender, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageObjToRender)
	ON_BN_CLICKED(IDD_PP_RENDER_RADIO_CURR3D, OnPpRenderRadioCurr3d)
	ON_BN_CLICKED(IDD_PP_RENDER_RADIO_CURR1D, OnPpRenderRadioCurr1d)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageObjToRender message handlers


void PropertyPageObjToRender::OnPpRenderRadioCurr3d() 
{
	CWnd* pDlgSheet = this->GetParent();
	ASSERT(pDlgSheet->IsKindOf(RUNTIME_CLASS(CPropertySheet)));
	CPropertySheet* ps = DYNAMIC_DOWNCAST(CPropertySheet,pDlgSheet);

	if(is_m_pp_visible)
	{
		m_pp = ps->GetPage(3);
		ps->RemovePage(m_pp);
		is_m_pp_visible = false;
	}
}

void PropertyPageObjToRender::OnPpRenderRadioCurr1d() 
{
	CWnd* pDlgSheet = this->GetParent();
	ASSERT(pDlgSheet->IsKindOf(RUNTIME_CLASS(CPropertySheet)));
	CPropertySheet* ps = DYNAMIC_DOWNCAST(CPropertySheet,pDlgSheet);

	if(!is_m_pp_visible)
	{
		ps->AddPage(m_pp);
		is_m_pp_visible = true;
	}
}
