#if !defined(AFX_PROPERTYPAGEATOMS_H__45A60395_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
#define AFX_PROPERTYPAGEATOMS_H__45A60395_AB1C_11D3_B1F5_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageAtoms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PropertyPageAtoms dialog

class PropertyPageAtoms : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageAtoms)

// Construction
public:
	PropertyPageAtoms();
	~PropertyPageAtoms();

// Dialog Data
	//{{AFX_DATA(PropertyPageAtoms)
	enum { IDD = IDD_PP_ATOMS };
	BOOL	m_Ba;
	BOOL	m_Cu1;
	BOOL	m_Cu2_1;
	BOOL	m_Cu2_2;
	BOOL	m_O1;
	BOOL	m_O2_1;
	BOOL	m_O2_2;
	BOOL	m_O4;
	BOOL	m_Y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageAtoms)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageAtoms)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEATOMS_H__45A60395_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
