// Currents2D3D.h : main header file for the CURRENTS2D3D application
//

#if !defined(AFX_CURRENTS2D3D_H__067F8F95_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
#define AFX_CURRENTS2D3D_H__067F8F95_A0BC_11D3_B1F0_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCurrents2D3DApp:
// See Currents2D3D.cpp for the implementation of this class
//

class CCurrents2D3DApp : public CWinApp
{
public:
	CCurrents2D3DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrents2D3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCurrents2D3DApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRENTS2D3D_H__067F8F95_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
