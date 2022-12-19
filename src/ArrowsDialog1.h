#if !defined(AFX_ARROWSDIALOG1_H__439646B5_967F_11D3_B1ED_005004567AD4__INCLUDED_)
#define AFX_ARROWSDIALOG1_H__439646B5_967F_11D3_B1ED_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArrowsDialog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ArrowsDialog dialog

class ArrowsDialog : public CDialog
{
// Construction
public:
	ArrowsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ArrowsDialog)
	enum { IDD = IDD_ARROWS };
	double	m_nArrowsAngle;
	double	m_nArrowsLength;
	UINT	m_nArrowsWidth;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArrowsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ArrowsDialog)
	afx_msg void OnButtonArrowsOk();
	afx_msg void OnButtonArrowsCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARROWSDIALOG1_H__439646B5_967F_11D3_B1ED_005004567AD4__INCLUDED_)
