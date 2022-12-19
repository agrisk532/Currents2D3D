// Currents2DView.h : interface of the CCurrents2DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTS2DVIEW_H__5B750F34_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
#define AFX_CURRENTS2DVIEW_H__5B750F34_85F2_11D3_B1D9_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cu2DAtoms;
class Cu2DCurrents;
class CCurrents2DDoc;

class CCurrents2DView : public CScrollView
{
protected: // create from serialization only
	CCurrents2DView();
	DECLARE_DYNCREATE(CCurrents2DView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrents2DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurrents2DView();
	void New(int NumberOfAtoms,int NumberOfBonds);	// allocates heap
	void Initialize();	// fills heap with stuff from doc - Cu2DAtoms, Cu2DCurrents objects
	void Delete(); // deallocates heap
	CSize GetViewSize(); // returns view size in pixels for SetScrollSizes()
	CCurrents2DDoc* GetDocument();
	void CalculateCircles(CDC* pDC);  // separation from plotting necessary because arrows use 
	void PlotCircles(CDC* pDC); // circle information. Circles plotted above arrows
	void PlotArrows(CDC* pDC);
	void SetZoomFactor(double zf) {m_nZoomFactor = zf;}
	double GetZoomFactor() {return m_nZoomFactor;}
	void ApplyZoomFactor();
	CSize GetViewOriginalSize(); // returns size of the drawing at zoom == 1
	int GetDistanceBetweenCuAtomBorders() {return m_nDistanceBetweenCuAtomBorders;}
	void WriteStatusBarMessage();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CCurrents2DDoc* pDoc;
	CRect m_rect; // DC rectangle
	int m_nDistanceBetweenCuAtomBorders; // in pixels
	int m_nNumberOfAtomsAlongSide;
	int m_nNumberOfBonds; // number of bonds
	int m_nDiameterOfCuAtom;	// in screen pixels
	int m_nBorderOfFirstAtomX;	// X coordinate of the right border of the upper left atom
	int m_nBorderOfFirstAtomY;	// Y coordinate of the upper border of the upper left atom
	int m_CenterAtomsAlongX(CRect rect,int length); // returns left border coordinate of the first atom (in pixels)
	int m_CenterAtomsAlongY(CRect rect,int length); // returns upper border coordinate of the first atom
	bool m_IsScrolledX;	// true if picture scrolled along X
	bool m_IsScrolledY;	// true if picture scrolled along Y
	double m_nZoomFactor;

	bool m_bDataInClipboard; // indicates whether there is data in clipboard

	Cu2DAtoms* pCu2DAtoms; // holds pointers to all Cu 2D atom objects
	Cu2DCurrents* p2DBondCurrents; // holds pointers to all 2D currents

	void SetViewRect(CRect rect) {m_rect = rect;}
	CRect GetViewRect() {return m_rect;}

// Generated message map functions
protected:
	//{{AFX_MSG(CCurrents2DView)
	afx_msg void OnViewZoomToFit();
	afx_msg void OnEditCopy();
	afx_msg void OnToolsArrowproperties();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomtofit(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Currents2DView.cpp
inline CCurrents2DDoc* CCurrents2DView::GetDocument()
   { return (CCurrents2DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRENTS2DVIEW_H__5B750F34_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
