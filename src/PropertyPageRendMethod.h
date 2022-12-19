#if !defined(AFX_PROPERTYPAGERENDMETHOD_H__45A60397_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
#define AFX_PROPERTYPAGERENDMETHOD_H__45A60397_AB1C_11D3_B1F5_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageRendMethod.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PropertyPageRendMethod dialog

class PropertyPageRendMethod : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageRendMethod)

// Construction
public:
	PropertyPageRendMethod();
	~PropertyPageRendMethod();

	CWnd* m_pVolRayCastIsosurf;
// from Currents for updating the Suggested isosurface value window
	int m_InitialMagnFieldValue;
// keeps the render region for using in 'OnInitDialog'
	int m_RenderRegion;

// Dialog Data
	//{{AFX_DATA(PropertyPageRendMethod)
	enum { IDD = IDD_PP_RENDMETHOD };
	int		m_renderMethod;
	int		m_IsosurfValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageRendMethod)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageRendMethod)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGERENDMETHOD_H__45A60397_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
