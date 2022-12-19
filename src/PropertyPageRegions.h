#if !defined(AFX_PROPERTYPAGEREGIONS_H__99D3BC87_D00C_11D3_B208_005004567AD4__INCLUDED_)
#define AFX_PROPERTYPAGEREGIONS_H__99D3BC87_D00C_11D3_B208_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageRegions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PropertyPageRegions dialog

class PropertyPageRegions : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageRegions)

// Construction
public:
	PropertyPageRegions();
	~PropertyPageRegions();

// Dialog Data
	//{{AFX_DATA(PropertyPageRegions)
	enum { IDD = IDD_PP_RENDREGIONS };
	int		m_RenderRegion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageRegions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageRegions)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEREGIONS_H__99D3BC87_D00C_11D3_B208_005004567AD4__INCLUDED_)
