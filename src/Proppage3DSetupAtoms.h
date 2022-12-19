#if !defined(AFX_PROPPAGE3DSETUPATOMS_H__45A60394_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
#define AFX_PROPPAGE3DSETUPATOMS_H__45A60394_AB1C_11D3_B1F5_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Proppage3DSetupAtoms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Proppage3DSetupAtoms dialog

class Proppage3DSetupAtoms : public CPropertyPage
{
	DECLARE_DYNCREATE(Proppage3DSetupAtoms)

// Construction
public:
	Proppage3DSetupAtoms();
	~Proppage3DSetupAtoms();

// Dialog Data
	//{{AFX_DATA(Proppage3DSetupAtoms)
	enum { IDD = IDD_PROPPAGE_IMAGESETUP_ATOMS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Proppage3DSetupAtoms)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Proppage3DSetupAtoms)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE3DSETUPATOMS_H__45A60394_AB1C_11D3_B1F5_005004567AD4__INCLUDED_)
