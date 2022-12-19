// Textvw.h : interface of the TextView class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_TEXTVW_H__439646B5_967F_11D3_B1ED_005004567AD4__INCLUDED_)
#define AFX_TEXTVW_H__439646B5_967F_11D3_B1ED_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;

//class CCurrents2DDoc;

class CTextView : public CScrollView
{
protected: // create from serialization only
	CTextView();
	DECLARE_DYNCREATE(CTextView)

// Attributes
public:
//	CCurrents2DDoc* GetDocument()
//			{
//				ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurrents2DDoc)));
//				return (CCurrents2DDoc*) m_pDocument;

//			}

	CDocument* GetDocument()
	{
		return m_pDocument;
	}

public:

	virtual void OnInitialUpdate(); // called first time after construct

	list<CString>lst;
	list<CString>::iterator listIterator;
// Operations
public:

// Implementation
public:
	virtual ~CTextView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw into this view
	void AddLine(CString text) {lst.push_back(text);}		// adds a text line
	void Delete(); // clears list at the file->new command

// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TEXTVW_H__439646B5_967F_11D3_B1ED_005004567AD4__INCLUDED_)
