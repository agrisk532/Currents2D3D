// PropertyPageRendMethod.cpp : implementation file
//

#include "stdafx.h"
#include "rendering.h"
#include "currents2d3d.h"
#include "PropertyPageRendMethod.h"
#include "PropertyPageRegions.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PropertyPageRendMethod property page

IMPLEMENT_DYNCREATE(PropertyPageRendMethod, CPropertyPage)

PropertyPageRendMethod::PropertyPageRendMethod() : CPropertyPage(PropertyPageRendMethod::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageRendMethod)
	m_renderMethod = 0;
	m_IsosurfValue = 0;
	//}}AFX_DATA_INIT
}

PropertyPageRendMethod::~PropertyPageRendMethod()
{
}

void PropertyPageRendMethod::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageRendMethod)
	DDX_Radio(pDX, IDD_PP_RENDMETHOD_VOLRAYCAST_COMPOSITE, m_renderMethod);
	DDX_Text(pDX, IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_EDIT, m_IsosurfValue);
	DDV_MinMaxInt(pDX, m_IsosurfValue, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageRendMethod, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageRendMethod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageRendMethod message handlers
//////////////////////////////////////////////////////////////////

BOOL PropertyPageRendMethod::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	CEdit* edit;
	CStatic* stat;
	edit = (CEdit*)GetDlgItem(IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_EDIT);
	ASSERT_VALID(edit);
	stat = (CStatic*)GetDlgItem(IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_STATIC);
	ASSERT_VALID(stat);

//	edit->EnableWindow(FALSE);
//	stat->EnableWindow(FALSE);
// set this value which will be used by PropertyPageRegions page, to update it
	m_pVolRayCastIsosurf = GetDlgItem(IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_SUGGESTED);
// text for suggested isosurface value to be displayed in the static window
	CString text;
// suggested isosurface value for displaying in the edit window
	CString value;

	if(m_InitialMagnFieldValue == 0)
	{
		text.Format("Suggested isosurface value : Unknown");
		edit->SetWindowText("0");
	}
	else 
	{
		if(m_RenderRegion == APPLIED_FIELD)
		{
			text.Format("Suggested isosurface value : (%d)",m_InitialMagnFieldValue);
//			value.Format("%d",m_InitialMagnFieldValue);
			value.Format("%d",m_IsosurfValue);
			edit->SetWindowText(value);
		}
		else
		if(m_RenderRegion == STRENGTHENED_FIELD)
		{
			text.Format("Suggested isosurface value : (%d - 255)",m_InitialMagnFieldValue+1);
//			value.Format("%d",m_InitialMagnFieldValue+1);
			value.Format("%d",m_IsosurfValue);
			edit->SetWindowText(value);
		}
		else
		if(m_RenderRegion == WEAKENED_FIELD)
		{
			text.Format("Suggested isosurface value : (0 - %d)",m_InitialMagnFieldValue-1);
//			value.Format("%d",m_InitialMagnFieldValue-1);
			value.Format("%d",m_IsosurfValue);
			edit->SetWindowText(value);
		}
		else
		if(m_RenderRegion == ALL_FIELD)
		{
			text.Format("Suggested isosurface value : (0 - %d - 255)",m_InitialMagnFieldValue);
//			value.Format("%d",m_InitialMagnFieldValue);
			value.Format("%d",m_IsosurfValue);
			edit->SetWindowText(value);
		}
	}
	
	m_pVolRayCastIsosurf->SetWindowText(text);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////////////////////////////
//

BOOL PropertyPageRendMethod::OnSetActive() 
{

	CPropertyPage::OnSetActive();
	
	CButton* button;
	button = (CButton*)GetDlgItem(IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF);

	CEdit* edit;
	CStatic* stat;
	edit = (CEdit*)GetDlgItem(IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_EDIT);
	ASSERT_VALID(edit);
	stat = (CStatic*)GetDlgItem(IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_STATIC);
	ASSERT_VALID(stat);

// now find what button is checked in the regions page
	CWnd* pDlgSheet = this->GetParent();
	ASSERT(pDlgSheet->IsKindOf(RUNTIME_CLASS(CPropertySheet)));
	CPropertySheet* ps = DYNAMIC_DOWNCAST(CPropertySheet,pDlgSheet);

// text for suggested isosurface value to be displayed in the static window
		CString text;
// suggested isosurface value for displaying in the edit window
		CString value;

	int showedPages = ps->GetPageCount();
	if(showedPages == 3)
	{
		text.Format("Suggested isosurface value : (0 - %d - 255)",m_InitialMagnFieldValue);
		value.Format("%d",m_InitialMagnFieldValue);
		if(m_IsosurfValue) value.Format("%d",m_IsosurfValue);
		edit->SetWindowText(value);
	}
	else
	{
		CPropertyPage* pp = ps->GetPage(3);
		ASSERT(pp->IsKindOf(RUNTIME_CLASS(PropertyPageRegions)));
		PropertyPageRegions* ppr = DYNAMIC_DOWNCAST(PropertyPageRegions,pp);

		m_RenderRegion = ppr->m_RenderRegion;

		m_pVolRayCastIsosurf = GetDlgItem(IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_SUGGESTED);
	
		if(m_InitialMagnFieldValue == 0)
		{
			text.Format("Suggested isosurface value : Unknown");
			edit->SetWindowText("0");
		}
		else 
		{
			if(m_RenderRegion == APPLIED_FIELD)
			{
				text.Format("Suggested isosurface value : (%d)",m_InitialMagnFieldValue);
				value.Format("%d",m_InitialMagnFieldValue);
				if(m_IsosurfValue) value.Format("%d",m_IsosurfValue);
				edit->SetWindowText(value);
			}
			else
			if(m_RenderRegion == STRENGTHENED_FIELD)
			{
				text.Format("Suggested isosurface value : (%d - 255)",m_InitialMagnFieldValue+1);
				value.Format("%d",m_InitialMagnFieldValue+1);
				if(m_IsosurfValue) value.Format("%d",m_IsosurfValue);
				edit->SetWindowText(value);
			}
			else
			if(m_RenderRegion == WEAKENED_FIELD)
			{
				text.Format("Suggested isosurface value : (0 - %d)",m_InitialMagnFieldValue-1);
				value.Format("%d",m_InitialMagnFieldValue-1);
				if(m_IsosurfValue) value.Format("%d",m_IsosurfValue);
				edit->SetWindowText(value);
			}
			else
			if(m_RenderRegion == ALL_FIELD)
			{
				text.Format("Suggested isosurface value : (0 - %d - 255)",m_InitialMagnFieldValue);
				value.Format("%d",m_InitialMagnFieldValue);
				if(m_IsosurfValue) value.Format("%d",m_IsosurfValue);
				edit->SetWindowText(value);
			}
		}
	}

	m_pVolRayCastIsosurf->SetWindowText(text);

	return TRUE;
}

