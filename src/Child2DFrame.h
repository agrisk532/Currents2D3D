// CChild2DFrame.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILD2DFRAME_H__5B750F30_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
#define AFX_CHILD2DFRAME_H__5B750F30_85F2_11D3_B1D9_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArrowsDialog1.h"

class CChild2DFrame : public CMDIChildWnd
{
	
protected: // create from serialization only
	CChild2DFrame();
	DECLARE_DYNCREATE(CChild2DFrame)

// Attributes
public:
	ArrowsDialog* m_pArrowsDialog; // prompts for arrow parameters
	CSplitterWnd m_wndSplitter;
// Operations
public:

	bool CreateNewFont();
	void ActivateExisting2DRebar();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChild2DFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChild2DFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//	CDialogBar* GetDialogBar() {return &m_wndDlgBar;}

protected:  // control bar embedded members
//	CStatusBar		m_wndStatusBar;
//	CToolBar		m_wndToolBar;
//	CReBar			m_wndReBar;
//	CDialogBar		m_wndDlgBar;
public:
// variables for fonts
	CFontDialog*	m_pSetFont;
	CFont*			m_pFont;
	LOGFONT			m_lf;
	int				m_cyLineHeight; // height of the text line of the current font
	int				m_cxLeftMargin; // left margin for text output

// Generated message map functions
protected:
	//{{AFX_MSG(CChild2DFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonCalcAndPlot();
	afx_msg void OnButtonApplyZoom();
	afx_msg void OnToolsFontProperties();
	afx_msg void OnDestroy();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILD2DFRAME_H__5B750F30_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
