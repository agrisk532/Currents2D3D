// Currents2DView.cpp : implementation of the CCurrents2DView class
//

#include "stdafx.h"
#include "Currents2DView.h"
#include "Currents2D3D.h"
#include "Currents2DDoc.h"
#include "MainFrm.h"
#include "Cu2DAtoms.h"
#include "Cu2DCurrentsBase.h"
#include "Cu2DCurrents.h"
#include "Currents.h"
#include "Child2DFrame.h"
#include <stdlib.h>
#include <afxole.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DView

IMPLEMENT_DYNCREATE(CCurrents2DView, CScrollView)

BEGIN_MESSAGE_MAP(CCurrents2DView, CScrollView)
	//{{AFX_MSG_MAP(CCurrents2DView)
	ON_COMMAND(ID_VIEW_ZOOMTOFIT, OnViewZoomToFit)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_TOOLS_ARROWPROPERTIES, OnToolsArrowproperties)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMTOFIT, OnUpdateViewZoomtofit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DView construction/destruction

CCurrents2DView::CCurrents2DView()
{
	// TODO: add construction code here
	m_nDiameterOfCuAtom = 20;
	m_nDistanceBetweenCuAtomBorders = 0; // in pixels
	m_nNumberOfAtomsAlongSide = 2;
	pCu2DAtoms = 0;
	p2DBondCurrents = 0;
	m_bDataInClipboard = false; // no data has been copied to the clipboard
	m_nZoomFactor = 1.;
}

CCurrents2DView::~CCurrents2DView()
{
	if(pCu2DAtoms)
	{
		delete [] pCu2DAtoms;
	}
	if(p2DBondCurrents)
	{
		delete [] p2DBondCurrents;
	}
}

BOOL CCurrents2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// initializes the view
void CCurrents2DView::New(int NumberOfAtoms,int NumberOfBonds)
{
	m_nNumberOfAtomsAlongSide = NumberOfAtoms;
	m_nNumberOfBonds = NumberOfBonds;
	if(!pCu2DAtoms) pCu2DAtoms = new Cu2DAtoms[NumberOfAtoms*NumberOfAtoms];
	else
	{
		AfxMessageBox( "pCu2DAtoms cannot be created in CCurrents2DView::New",MB_OK,0);
		exit(0);
	}
	if(!p2DBondCurrents) p2DBondCurrents = new Cu2DCurrents[NumberOfBonds];
	else
	{
		AfxMessageBox( "Cu2DCurrents cannot be created in CCurrents2DView::New",MB_OK,0);
		exit(0);
	}
}

//////////////////////////////////////////////////////////////////////////////
//  deletes all allocated dimensions from heap
void CCurrents2DView::Delete()
{
	if(pCu2DAtoms)
	{
		delete [] pCu2DAtoms;
		pCu2DAtoms = 0;
	}
	if(p2DBondCurrents)
	{
		delete [] p2DBondCurrents;
		p2DBondCurrents = 0;
	}

}

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DView drawing

void CCurrents2DView::OnDraw(CDC* pDC)
{

//	m_nNumberOfAtomsAlongSide = pDoc->GetNumberOfAtomsAlongSide();
	// TODO: add draw code for native data here
//	int Atoms = pDoc->GetNumberOfAtomsAlongSide();
//	double Field = pDoc->GetExtMagnField();
//	double Dist = pDoc->GetCuCuDistance();

//	test code 
/*
	CString string;
	string.Format("Number of Atoms along side is %d", Atoms);
	pDC->TextOut(12,12,string,string.GetLength());
	string.Format("External magnetic field is %lf Gauss",Field);
	pDC->TextOut(12,36,string,string.GetLength());
	string.Format("Cu - Cu distance is %lf angstrom",Dist);
	pDC->TextOut(12,60,string,string.GetLength());
*/
// finds out the logical size of the view and writes it to the member variable
// when I put pDC->GetClipBox(&rect), copying to clipboard doesn't work
	CRect rect;
	this->GetClientRect(&rect);
	pDC->DPtoLP(&rect);

	this->SetViewRect(rect);

	if(pDoc->GetCalculatedOK())	// document has data for plotting
	{
		CalculateCircles(pDC);
		PlotArrows(pDC);
		PlotCircles(pDC);
		WriteStatusBarMessage(); // writes number of scf iterations performed
	}
}
////////////////////////////////////////////////////////////////////////////
//
void CCurrents2DView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle("Cu-Cu bond 1D electric currents");

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_LOENGLISH, sizeTotal);
	OleInitialize(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DView printing

BOOL CCurrents2DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCurrents2DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCurrents2DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DView diagnostics

#ifdef _DEBUG
void CCurrents2DView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCurrents2DView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCurrents2DDoc* CCurrents2DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurrents2DDoc)));
	return (CCurrents2DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DView message handlers

void CCurrents2DView::CalculateCircles(CDC* pDC)
{
// CCurrents2DView::ApplyZoomFactor(double zoomFactor) must be called before this function

// Retrieve the logical size of the view
	CRect rect;
	rect = this->GetViewRect();

// determine the location of atoms in window. If all atoms can fit in the window,
// center them. Otherwise start drawing at the upper left corner and use scrolling.

// distance of the first Cu atom border from the left border of window
	m_nBorderOfFirstAtomX = m_nDiameterOfCuAtom;
// distance of the first Cu atom border from the upper border of window
	m_nBorderOfFirstAtomY = -m_nDiameterOfCuAtom;

// now center all atoms if possible

	int LengthAlongX = (m_nNumberOfAtomsAlongSide - 1) * m_nDistanceBetweenCuAtomBorders +
						m_nDiameterOfCuAtom;
	int LengthAlongY = LengthAlongX;

	m_IsScrolledX = true;
	m_IsScrolledY = true;

	if(LengthAlongX < rect.right)
	{
// returns the X coordinate of the left border of the first atom
		m_CenterAtomsAlongX(rect,LengthAlongX); 
		m_IsScrolledX = false;
	}

	if(LengthAlongY < -rect.bottom)
	{
// returns the Y coordinate of the upper border of the first atom
		m_CenterAtomsAlongY(rect,LengthAlongY);
		m_IsScrolledY = false;
	}

// Plot atoms. Their order must be the same as in the Cu2Layer object

	int AtomNumber = 0; // for numbering of circles
	for(int i=0 ; i<m_nNumberOfAtomsAlongSide; i++)
	{
		int rowIndex = i*m_nNumberOfAtomsAlongSide;
		int y=m_nBorderOfFirstAtomY-m_nDistanceBetweenCuAtomBorders*i;
		for(int j=0 ; j<m_nNumberOfAtomsAlongSide; j++)
		{
			AtomNumber++;
			int x=m_nBorderOfFirstAtomX+m_nDistanceBetweenCuAtomBorders*j;

			int index = rowIndex+j; 

			pCu2DAtoms[index].SetCoordX(x);
			pCu2DAtoms[index].SetCoordY(y);
			pCu2DAtoms[index].SetSerialNumber(AtomNumber);
		}
	}
// now we calculate and plot arrows, then above plot Cu circles
// arrows use Cu circle information
}

//////////////////////////////////////////////////////////////////
// Plot circles

void CCurrents2DView::PlotCircles(CDC* pDC)
{
	CPen penOutline;
	CPen* ppenOld;

	CBrush brush;
	CBrush* pbrushOld;

	penOutline.CreatePen(PS_SOLID,1,RGB(200,0,0));
	ppenOld = pDC->SelectObject(&penOutline);

	brush.CreateSolidBrush(RGB(200,200,0));
	pbrushOld = pDC->SelectObject(&brush);

// Plot atoms. Their order must be the same as in the Cu2Layer object

	for(int i=0 ; i<m_nNumberOfAtomsAlongSide; i++)
	{
		int rowIndex = i*m_nNumberOfAtomsAlongSide;
		for(int j=0 ; j<m_nNumberOfAtomsAlongSide; j++)
		{
			int index = rowIndex+j; 
			pCu2DAtoms[index].Plot(pDC);
		}
	}
	pDC->SelectObject(ppenOld);
	pDC->SelectObject(pbrushOld);
}

///////////////////////////////////////////////////////////////////
// calculates the left border of the first atom (in pixels)
int CCurrents2DView::m_CenterAtomsAlongX(CRect rect,int length)
{
	int value = (rect.right - length) / 2;
	return (value < m_nDiameterOfCuAtom) ? (m_nBorderOfFirstAtomX = m_nDiameterOfCuAtom) :
										(m_nBorderOfFirstAtomX = value);
}

///////////////////////////////////////////////////////////////////
// calculates the upper border of the first atom (in pixels)
int CCurrents2DView::m_CenterAtomsAlongY(CRect rect,int length)
{
	int value = (-rect.bottom - length) / 2;
	return (value < m_nDiameterOfCuAtom) ? (m_nBorderOfFirstAtomY = -m_nDiameterOfCuAtom) :
										(m_nBorderOfFirstAtomY = -value);
}

///////////////////////////////////////////////////////////////////
//
void CCurrents2DView::PlotArrows(CDC* pDC)
{
	for(int i=0;i<m_nNumberOfBonds;i++)
	{
		CPoint center1;
		CPoint center2;
		pCu2DAtoms[pDoc->m_pCurr->GetBondAtom1(i)].GetCenter(&center1);	// window coordinates
		pCu2DAtoms[pDoc->m_pCurr->GetBondAtom2(i)].GetCenter(&center2);

		p2DBondCurrents[i].SetAtom1Center(center1); // in screen coordinates
		p2DBondCurrents[i].SetAtom2Center(center2);
		p2DBondCurrents[i].SetCurrentMagnitude(pDoc->m_pCurr->GetBondCurrent(i));
		p2DBondCurrents[i].SetCurrentDirection(pDoc->m_pCurr->GetBondCurrentDirection(i));
		p2DBondCurrents[i].SetCuCuDistance(m_nDistanceBetweenCuAtomBorders); // in pixels
		p2DBondCurrents[i].Plot(pDC);
	}
}
///////////////////////////////////////////////////////////////////
//
void CCurrents2DView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_LOENGLISH,GetViewSize());
	CScrollView::OnUpdate(pSender,lHint,pHint);
}
///////////////////////////////////////////////////////////////////
//
CSize CCurrents2DView::GetViewSize()
{
	CSize size;
	size.cx = size.cy = m_nDistanceBetweenCuAtomBorders * m_nNumberOfAtomsAlongSide;
	return size;
}
///////////////////////////////////////////////////////////////////
// size of the picture, at zoom == 1
CSize CCurrents2DView::GetViewOriginalSize()
{
	CSize size;
	size.cx = size.cy = 30 * pDoc->GetCuCuDistance() * m_nNumberOfAtomsAlongSide;
	return size;
}

///////////////////////////////////////////////////////////////////
//

void CCurrents2DView::OnViewZoomToFit() 
{
	// TODO: Add your command handler code here
	if(pDoc->GetCalculatedOK())
	{
// retrieves the logical rectangle for drawing
		CRect rect = this->GetViewRect();		

		CSize size;
		size = GetViewOriginalSize();

		double minSize = (-rect.bottom < rect.right) ? -rect.bottom : rect.right;
		double zoomFactor = minSize/size.cx;
		SetZoomFactor(zoomFactor);
		ApplyZoomFactor();

		pDoc->UpdateAllViews(NULL);

		CChild2DFrame* pCfrm = (CChild2DFrame*) GetParentFrame();
		ASSERT(pCfrm->IsKindOf(RUNTIME_CLASS(CChild2DFrame)));
		CMainFrame* pFrame = (CMainFrame*)pCfrm->GetMDIFrame();
		ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)));

		CEdit* pEd;
		pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_ZOOM_FACTOR);
		char buffer[10];
		pEd->SetWindowText(_gcvt(zoomFactor,5,buffer));
	}
}

///////////////////////////////////////////////////////////////////
// Applies zooming to Cu2D atoms and currents
// must be called prior to CalculateCircles(),PlotCircles(),PlotArrows() !!!

void CCurrents2DView::ApplyZoomFactor()
{
	if(pDoc->GetCalculatedOK())
	{
		CChild2DFrame* pFrame = (CChild2DFrame*)GetParentFrame();
		ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CChild2DFrame)));

// Distance between atoms in window is 30*(distance in angstroms)*zoomFactor
		m_nDistanceBetweenCuAtomBorders = 30 * pDoc->GetCuCuDistance() * m_nZoomFactor;
// m_nDiameterOfCuAtom at zoom(0) is 20 - originally set in the constructor
		m_nDiameterOfCuAtom = 20 * m_nZoomFactor;
		for(int i=0;i<m_nNumberOfAtomsAlongSide*m_nNumberOfAtomsAlongSide;i++)
			pCu2DAtoms[i].m_nRectangleSize = m_nDiameterOfCuAtom;
// Cu2DCurrentsBase static member initialization
		for(i=0;i<m_nNumberOfBonds;i++)
		{
			p2DBondCurrents[i].m_nMaxCurrentWidth = pFrame->m_pArrowsDialog->m_nArrowsWidth; // in screen pixels
			p2DBondCurrents[i].m_nMaxCurrentValue = pDoc->m_pCurr->GetMaxCurrent();

			p2DBondCurrents[i].m_nArrowAngle = pFrame->m_pArrowsDialog->m_nArrowsAngle;
			p2DBondCurrents[i].m_nArrowLength = // in pixels
			pFrame->m_pArrowsDialog->m_nArrowsLength * // fraction from the CuCu distance
			m_nDistanceBetweenCuAtomBorders; // in screen pixels
		}
	}
}
////////////////////////////////////////////////////////////////////
//
void CCurrents2DView::WriteStatusBarMessage()
{
	if(pDoc->GetCalculatedOK())
	{
		CStatusBar* sb;

		CChild2DFrame* pCfrm = (CChild2DFrame*) GetParentFrame();
		ASSERT(pCfrm->IsKindOf(RUNTIME_CLASS(CChild2DFrame)));
		CMainFrame* pFrame = (CMainFrame*)pCfrm->GetMDIFrame();
		ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)));

		CString msg;
		msg.Format("Done in %d iterations",pDoc->GetIterations());
		sb = (CStatusBar*) pFrame->GetMessageBar();
		sb->SetWindowText(msg);
	}
}


//////////////////////////////////////////////////////////////////////////
// Copies the currents view to the clipboard using OLE
void CCurrents2DView::OnEditCopy() 
{
	// TODO: Add your command handler code here

	tagSTGMEDIUM * data;
	CClientDC dcRef( this );
	data = new tagSTGMEDIUM;
	CMetaFileDC * dcMeta;
	dcMeta = new CMetaFileDC();
	COleDataSource* pData = new COleDataSource;
	CRect lmbr;
	GetClientRect(lmbr); // in logical units. lmbr.top = lmbr.left = 0;
	CSize lpSize(lmbr.right,lmbr.bottom);
	dcRef.DPtoHIMETRIC(&lpSize);
	//replace "ImageName" with a description of this image
	lmbr.right = lpSize.cx*1.18; // I still don't understand why 1.18 is necessary!!!
	lmbr.bottom = lpSize.cy*1.18;
	dcMeta->CreateEnhanced(&dcRef, NULL, lmbr,"Currents2D\0Currents\0\0" );
	dcMeta->m_hAttribDC = dcMeta->m_hDC;
	dcMeta->SetMapMode(MM_LOENGLISH);
	//actually draw to the device context
	OnDraw(dcMeta);
	//done drawing
	data->tymed = TYMED_ENHMF;
	data->hEnhMetaFile = dcMeta->CloseEnhanced();
	pData->CacheData( CF_ENHMETAFILE, data );
// flush clipboard before copying
// still First-chance exception in Currents2D.exe (OLE32.DLL): 0xC0000005: Access Violation.
// but program doesn't crash
	if(m_bDataInClipboard) pData->FlushClipboard();
	pData->SetClipboard();
	m_bDataInClipboard = true;

	delete dcMeta;
	delete data;
}

////////////////////////////////////////////////////////////////////////
//

void CCurrents2DView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
// calculate the zoom factor
	OnDraw(pDC);
	CScrollView::OnPrint(pDC, pInfo);
}

////////////////////////////////////////////////////////////////////////
//
void CCurrents2DView::OnToolsArrowproperties() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CChild2DFrame* pFrame = (CChild2DFrame*)GetParentFrame();
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CChild2DFrame)));
	
	int nResult = pFrame->m_pArrowsDialog->DoModal();
	if(nResult == IDOK) // 'OK' button clicked
	{
		for(int i=0;i<m_nNumberOfBonds;i++)
		{
			p2DBondCurrents[i].m_nArrowAngle = pFrame->m_pArrowsDialog->m_nArrowsAngle;
			p2DBondCurrents[i].m_nArrowLength = // in pixels
			pFrame->m_pArrowsDialog->m_nArrowsLength * // fraction from the CuCu distance
			m_nDistanceBetweenCuAtomBorders; // in screen pixels
		}
		if(pDoc->GetCalculatedOK()) SendMessage(WM_COMMAND,ID_VIEW_ZOOMTOFIT,0);
	}
	else // 'Cancel' button clicked
	{
	}
	
}

void CCurrents2DView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class
// restore the 2D rebar

	CScrollView::OnEndPrintPreview(pDC, pInfo, point, pView);	

	CChild2DFrame* pCfrm = (CChild2DFrame*) GetParentFrame();
	ASSERT(pCfrm->IsKindOf(RUNTIME_CLASS(CChild2DFrame)));
	CMainFrame* pFrame = (CMainFrame*)pCfrm->GetMDIFrame();
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)));

	pFrame->ShowControlBar(&pFrame->m_wndToolBar,FALSE,FALSE);
	pFrame->ShowControlBar(&pFrame->m_wndToolBar3D,FALSE,FALSE);
	pFrame->ShowControlBar(&pFrame->m_wndDlgBar3D,FALSE,FALSE);

}

//////////////////////////////////////////////////////////////////
//		ON_UPDATE_COMMAND_UI  handlers

void CCurrents2DView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	if(pDoc->GetCalculatedOK())	// document has data for plotting
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}

void CCurrents2DView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	if(pDoc->GetCalculatedOK())	// document has data for plotting
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}


void CCurrents2DView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	if(pDoc->GetCalculatedOK())	// document has data for plotting
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}

void CCurrents2DView::OnUpdateViewZoomtofit(CCmdUI* pCmdUI) 
{
	if(pDoc->GetCalculatedOK())	// document has data for plotting
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}
