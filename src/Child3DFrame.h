// CChild3DFrame.h : interface of the CChild3DFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILD3DFRAME_H__5B750F30_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
#define AFX_CHILD3DFRAME_H__5B750F30_85F2_11D3_B1D9_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChild3DFrame : public CMDIChildWnd
{
	
protected: // create from serialization only
	CChild3DFrame();
	DECLARE_DYNCREATE(CChild3DFrame)

// Attributes
public:
	CSplitterWnd m_wndSplitter;
	char m_cWindowText[100]; // frame window text
// Operations
public:
	bool CreateNewFont();
	void ActivateExisting3DRebar();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChild3DFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChild3DFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//	CDialogBar* GetDialogBar() {return &m_wndDlgBar;}

protected:  // control bar embedded members
//	CStatusBar		m_wndStatusBar;
//	CToolBar		m_wndToolBar;
//	CDialogBar		m_wndDlgBar;
public:
// variables for fonts
	CFontDialog*	m_pSetFont;
	CFont*			m_pFont;
	LOGFONT			m_lf;
	int				m_cyLineHeight; // height of the text line of the current font
	int				m_cxLeftMargin; // left margin for text output
	CFileDialog*	m_pOpenFile;	// File->Open handler

// Generated message map functions
protected:
	//{{AFX_MSG(CChild3DFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonCalcAndPlot();
	afx_msg void OnToolsFontproperties3();
	afx_msg void OnDestroy();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILD3DFRAME_H__5B750F30_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
