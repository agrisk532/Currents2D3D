#if !defined(AFX_MODAL3DPROPSHEET_H__C294D024_B2D1_11D3_B204_005004567AD4__INCLUDED_)
#define AFX_MODAL3DPROPSHEET_H__C294D024_B2D1_11D3_B204_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modal3DPropSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Modal3DPropSheet

class Modal3DPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(Modal3DPropSheet)

// Construction
public:
	Modal3DPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	PropertyPageAtoms m_PageAtoms;
	PropertyPageObjToRender m_PageObjToRender;
	PropertyPageRendMethod m_PageRenderMethod;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Modal3DPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Modal3DPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(Modal3DPropSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODAL3DPROPSHEET_H__C294D024_B2D1_11D3_B204_005004567AD4__INCLUDED_)
