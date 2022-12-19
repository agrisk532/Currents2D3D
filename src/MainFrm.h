// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__067F8F99_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
#define AFX_MAINFRM_H__067F8F99_A0BC_11D3_B1F0_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

public:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar; // mainframe toolbar
	CToolBar    m_wndToolBar2D;
	CToolBar    m_wndToolBar3D;
	CDialogBar  m_wndDlgBar2D;
	CDialogBar  m_wndDlgBar3D;

	CReBar m_wndReBar;
	CBitmap m_rebarBitmap;

	REBARBANDINFO m_rbtb2D;
	REBARBANDINFO m_rbtb3D;
	REBARBANDINFO m_rbdb2D;
	REBARBANDINFO m_rbdb3D;

	int m_nNumberOf2DMDIClients;	// used for manipulation with CMainFrame rebars
	int m_nNumberOf3DMDIClients;
	bool m_mainToolBarIsOn;


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHhnotification();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__067F8F99_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
