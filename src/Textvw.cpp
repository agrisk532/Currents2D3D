// simpvw.cpp : implementation of the simple view classes
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "Resource.h"
#include "Currents2DDoc.h"
#include "Currents3DDoc.h"
#include "Child2DFrame.h"
#include "Child3DFrame.h"
#include "Textvw.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CScrollView)

BEGIN_MESSAGE_MAP(CTextView, CScrollView)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView construction/destruction

CTextView::CTextView()
{
}

CTextView::~CTextView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

void CTextView::OnDraw(CDC* pDC)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*) AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = pFrame->MDIGetActive();
	CDocument* pDoc = pChild->GetActiveDocument();
	CCurrents2DDoc* pC2D;
	CCurrents3DDoc* pC3D;
	CChild2DFrame* pF2D;
	CChild3DFrame* pF3D;

// perform downcasting

	if(pDoc->IsKindOf(RUNTIME_CLASS(CCurrents2DDoc)))
	{
		pC2D = DYNAMIC_DOWNCAST(CCurrents2DDoc,pDoc);
		pF2D = DYNAMIC_DOWNCAST(CChild2DFrame,pChild);

		if(pC2D->GetCalculatedOK())	// document has data for plotting
		{

			pDC->SelectObject(pF2D->m_pFont);

			int iLine = 0;

			listIterator = lst.begin();
			int length = lst.size();
// for scrolling sizes
			CSize sizeScroll(0,0);

			while(iLine < length)
			{
				CSize size;
				pDC->TextOut(pF2D->m_cxLeftMargin,(iLine+1) * pF2D->m_cyLineHeight,
				*listIterator,listIterator->GetLength());
	
				size = pDC->GetOutputTextExtent(*listIterator);
				if(size.cx > sizeScroll.cx) sizeScroll.cx = size.cx + 2*pF2D->m_cxLeftMargin;
				sizeScroll.cy += size.cy;
	
				listIterator++;
				iLine++;
			}
// add two blank line heights to the cy scroll size
			sizeScroll.cy += 2 * pF2D->m_cyLineHeight;
// Set new scroll sizes
			SetScrollSizes(MM_TEXT, sizeScroll);
		}
	}



	if(pDoc->IsKindOf(RUNTIME_CLASS(CCurrents3DDoc)))
	{
		pC3D = DYNAMIC_DOWNCAST(CCurrents3DDoc,pDoc);
		pF3D = DYNAMIC_DOWNCAST(CChild3DFrame,pChild);

		if(pC3D->GetCalculatedOK())	// document has data for plotting
		{

			pDC->SelectObject(pF3D->m_pFont);

			int iLine = 0;

			listIterator = lst.begin();
			int length = lst.size();
// for scrolling sizes
			CSize sizeScroll(0,0);

			while(iLine < length)
			{
				CSize size;
				pDC->TextOut(pF3D->m_cxLeftMargin,(iLine+1) * pF3D->m_cyLineHeight,
				*listIterator,listIterator->GetLength());

				size = pDC->GetOutputTextExtent(*listIterator);
				if(size.cx > sizeScroll.cx) sizeScroll.cx = size.cx + 2*pF3D->m_cxLeftMargin;
				sizeScroll.cy += size.cy;

				listIterator++;
				iLine++;
			}
// add two blank line heights to the cy scroll size
			sizeScroll.cy += 2 * pF3D->m_cyLineHeight;
// Set new scroll sizes
			SetScrollSizes(MM_TEXT, sizeScroll);
		}
	}
}
/////////////////////////////////////////////////////////////////////////
//
void CTextView::Delete()
{
	lst.clear();
	this->Invalidate(TRUE);
}
/////////////////////////////////////////////////////////////////////////
//
int CTextView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// side-step CView's implementation since we don't want to activate
	//  this view
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

//////////////////////////////////////////////////////////////////////////
//
void CTextView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


