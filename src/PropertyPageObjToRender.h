#if !defined(AFX_PROPERTYPAGEOBJTORENDER_H__45A60396_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
#define AFX_PROPERTYPAGEOBJTORENDER_H__45A60396_AB1C_11D3_B1F5_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageObjToRender.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PropertyPageObjToRender dialog

class PropertyPageObjToRender : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageObjToRender)

// Construction
public:
	PropertyPageObjToRender();
	~PropertyPageObjToRender();

	CPropertyPage* m_pp; // points to the regions page in order to remove/add it
	bool is_m_pp_visible;

// Dialog Data
	//{{AFX_DATA(PropertyPageObjToRender)
	enum { IDD = IDD_PP_OBJTORENDER };
	int		m_ObjToRender;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageObjToRender)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageObjToRender)
	afx_msg void OnPpRenderRadioCurr3d();
	afx_msg void OnPpRenderRadioCurr1d();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEOBJTORENDER_H__45A60396_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
