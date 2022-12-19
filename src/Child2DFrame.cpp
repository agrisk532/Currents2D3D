// Child2DFrame.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Currents2D3D.h"
#include "Currents2DDoc.h"
#include "Currents2DView.h"
#include "Cu2DCurrentsBase.h"
#include "Textvw.h"
#include "MainFrm.h"
#include "resource.h"

#include "Child2DFrame.h"
#include "Child3DFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CChild2DFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChild2DFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChild2DFrame)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_CALCANDPLOT, OnButtonCalcAndPlot)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_ZOOM, OnButtonApplyZoom)
	ON_COMMAND(ID_TOOLS_FONTPROPERTIES, OnToolsFontProperties)
	ON_WM_DESTROY()
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CChild2DFrame::CChild2DFrame()
{
	// TODO: add member initialization code here
	m_pSetFont = 0;
	m_pFont = 0;

}
/////////////////////////////////////////////////////////////////////////////
//
CChild2DFrame::~CChild2DFrame()
{
	if(m_pArrowsDialog)	delete m_pArrowsDialog;
	if(m_pSetFont) delete m_pSetFont;
	if(m_pFont) delete m_pFont;
}
/////////////////////////////////////////////////////////////////////////////
//
int CChild2DFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CCurrents2DDoc* pDoc = (CCurrents2DDoc*)GetActiveDocument();
	CMainFrame* pFrame = (CMainFrame*) GetMDIFrame();

// keeps the number of created 2D frames
	pFrame->m_nNumberOf2DMDIClients++;

	pDoc->SetNumberOfAtomsAlongSide(2);
	pDoc->SetExtMagnField(0.01);
	pDoc->SetCuCuDistance(1.94);
	pDoc->SetElectronsRemoved(0);


// TODO: Remove this if you don't want tool tips
//	pFrame->m_wndToolBar.SetBarStyle(pFrame->m_wndToolBar.GetBarStyle() |
//		CBRS_TOOLTIPS | CBRS_FLYBY);


// Create ArrowsDialog object

	m_pArrowsDialog = new ArrowsDialog();
	if(!m_pArrowsDialog)
	{
		TRACE0("Failed to create ArrowsDialog\n");
		return -1;
	}

// create Font dialog
	m_pSetFont = new CFontDialog(&m_lf,CF_SCREENFONTS);
	if(!m_pSetFont)
		return -1;

// initial fonts
//	m_pFont = new CFont();
//	if(!m_pFont)
//		return -1;

	memset(&m_lf,0,sizeof(LOGFONT));
	lstrcpy(m_lf.lfFaceName,_T("System"));
//	CWindowDC dc(NULL);
//	int cyPixels = dc.GetDeviceCaps(LOGPIXELSY);
//	m_lf.lfHeight = (-1)*MulDiv(10,cyPixels,72);

// create initial font object
	if(!CreateNewFont())
		return -1;

	return 0;
}
////////////////////////////////////////////////////////////////////////////
//

BOOL CChild2DFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CChild2DFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChild2DFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CChild2DFrame::OnButtonCalcAndPlot() 
{

	CWaitCursor wait; // hourglass cursor

	CString string;
	CEdit* pEd;
	CCurrents2DDoc* pDoc = (CCurrents2DDoc*)GetActiveDocument();

	pDoc->OnNewDocument();
// do the following because rebar is on the main frame
	CMainFrame* pFrame = (CMainFrame*) GetMDIFrame();
	
	pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_NMBCUATOMS);
	pEd->GetWindowText(string);
	int number = atoi(string); // number of atoms along side
	if(number%2 != 0) number++;	// to make NumberOfAtoms even. Otherwise calculation crash.
	char astring[20];
	pEd->SetWindowText(itoa(number,astring,10));
	pEd->UpdateWindow();
	pDoc->SetNumberOfAtomsAlongSide(number);

	pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_EXTMAGNFIELD);
	pEd->GetWindowText(string);
	pDoc->SetExtMagnField(atof(string));

	pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_CUCUDIST);
	pEd->GetWindowText(string);
	pDoc->SetCuCuDistance(atof(string));

	pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_ELECTRONS_REMOVED);
	pEd->GetWindowText(string);
	int er = atoi(string);

// limit the number of electrons to be removed / added according to the number of atoms
// According to Larsson's model is one electron per Cu atom
	CSpinButtonCtrl* spin;
	spin = (CSpinButtonCtrl*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_SPIN_ELECTRONS_REMOVED);
// feature of the spin control button makes +-1 as necessity
	spin->SetRange(-number*number,number*number);

	pDoc->SetElectronsRemoved(er);
	CButton *btn;
	btn = (CButton*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_CHECK_ISSCF);
// set self-consistency flag
// from the constructor it is zero (0) - do not self-consistently
	if(btn->GetCheck())
	{
		pDoc->SetDoWithoutSelfConsistency(false);
	}
	else
	{
		pDoc->SetDoWithoutSelfConsistency(true);
	}

	pFrame->m_wndStatusBar.SetWindowText("Calculation in progress. Please wait...");
	
// for some reason this code doesn't change menu in the mainframe

//	CMenu menu;
//	menu.LoadMenu(IDR_CURRENTS2_GRAYED);
//	SetMenu(&menu);

	pDoc->Calculate();
	pDoc->InitializeCurrents2DView();


// send zoom factor to the view for processing
//	pEd = (CEdit*)m_wndDlgBar.GetDlgItem(IDC_EDIT_ZOOM_FACTOR);
//	pEd->GetWindowText(string);

	SendMessage(WM_COMMAND,ID_VIEW_ZOOMTOFIT,0);

//	menu.DestroyMenu();
//	menu.LoadMenu(IDR_CURRENTS2);
//	SetMenu(&menu);
//	menu.Detach();
}

///////////////////////////////////////////////////////////////////////
//
void CChild2DFrame::OnButtonApplyZoom() 
{
	// TODO: Add your control notification handler code here
	// send zoom factor to the view for processing

	CString string;
	CEdit* pEd;
	CCurrents2DDoc* pDoc = (CCurrents2DDoc*)GetActiveDocument();
	CMainFrame* pFrame = (CMainFrame*) GetMDIFrame();

	if(pDoc->GetCalculatedOK())
	{
		pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_ZOOM_FACTOR);
		pEd->GetWindowText(string);
		CCurrents2DView* pView;
		pView = (CCurrents2DView*)GetActiveView();
		ASSERT(pView->IsKindOf(RUNTIME_CLASS(CCurrents2DView)));
		pView->SetZoomFactor(atof(string));
		pView->ApplyZoomFactor();

		pDoc->UpdateAllViews(NULL);
	}
}

////////////////////////////////////////////////////////////////////////
//
BOOL CChild2DFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(370,370), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CTextView), CSize(0,0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	// activate the first view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,0));

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
bool CChild2DFrame::CreateNewFont()
{
// delete previous font
	if(m_pFont) delete m_pFont;
	m_pFont = new CFont();
	if(!m_pFont) return false;

// create font from the LOGFONT structure
	m_pFont->CreateFontIndirect(&m_lf);
// Calculate the font height
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.SelectObject(m_pFont);
	dc.GetTextMetrics(&tm);
	m_cyLineHeight = tm.tmHeight + tm.tmExternalLeading;
// Calculate left margin
	m_cxLeftMargin = tm.tmAveCharWidth * 2;

	return true;
}

///////////////////////////////////////////////////////////////////////////
//	Font dialog box handler

void CChild2DFrame::OnToolsFontProperties() 
{
	// TODO: Add your command handler code here
// display font picker dialog box
	int iRet = m_pSetFont->DoModal();
// ignore when [Cancel] button clicked
	if(iRet != IDOK)
		return;
// rebuild font definition based on dialog selection
	CreateNewFont();
// request WM_PAINT message to redraw the window
	Invalidate();
}

/////////////////////////////////////////////////////////////////////
//

void CChild2DFrame::OnDestroy() 
{
	CMDIChildWnd::OnDestroy();
	CMainFrame* pFrame = (CMainFrame*) GetMDIFrame();
	pFrame->m_nNumberOf2DMDIClients--;
	if(!pFrame->m_nNumberOf2DMDIClients)
	{
	pFrame->m_wndReBar.GetReBarCtrl().ShowBand(0,FALSE);
	pFrame->m_wndReBar.GetReBarCtrl().ShowBand(1,FALSE);
	}

	if(pFrame->m_nNumberOf3DMDIClients)
	{
	pFrame->m_wndReBar.GetReBarCtrl().ShowBand(2,TRUE);
	pFrame->m_wndReBar.GetReBarCtrl().ShowBand(3,TRUE);
	}

	if(!pFrame->m_nNumberOf2DMDIClients && !pFrame->m_nNumberOf3DMDIClients)
	{
// show the MainFrame toolbar
		pFrame->m_wndReBar.GetReBarCtrl().ShowBand(4,TRUE);
		pFrame->m_mainToolBarIsOn = true;
	}
}

///////////////////////////////////////////////////////////////////////
//

void CChild2DFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

// activation of the frame
	if(bActivate == TRUE)
	{
		CCurrents2DDoc* pDoc = (CCurrents2DDoc*)GetActiveDocument();
		CMainFrame* pFrame = (CMainFrame*) GetMDIFrame();

		if(pDeactivateWnd && pDeactivateWnd->IsKindOf(RUNTIME_CLASS(CChild3DFrame)))
		{
			pFrame->m_wndReBar.GetReBarCtrl().ShowBand(2,FALSE);
			pFrame->m_wndReBar.GetReBarCtrl().ShowBand(3,FALSE);
		}
// hide mainframe toolbar if on
		if(pFrame->m_mainToolBarIsOn)
		{
			pFrame->m_wndReBar.GetReBarCtrl().ShowBand(4,FALSE);
			pFrame->m_mainToolBarIsOn = false;
		}
// change dialogbar edit window values
		pFrame->m_wndReBar.GetReBarCtrl().ShowBand(0,TRUE);
		pFrame->m_wndReBar.GetReBarCtrl().ShowBand(1,TRUE);

		CEdit* pEd;
		char astring[20];
		double dNumber;
		int iNumber;

		pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_EXTMAGNFIELD);
		dNumber = pDoc->GetExtMagnField();
		pEd->SetWindowText(_gcvt(dNumber,10,astring));
		pEd->UpdateWindow();

		pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_CUCUDIST);
		dNumber = pDoc->GetCuCuDistance();
		pEd->SetWindowText(_gcvt(dNumber,10,astring));
		pEd->UpdateWindow();

		pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_ELECTRONS_REMOVED);
		iNumber = pDoc->GetElectronsRemoved();
		pEd->SetWindowText(itoa(iNumber,astring,10));
		pEd->UpdateWindow();

		pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_NMBCUATOMS);
		iNumber = pDoc->GetNumberOfAtomsAlongSide();
		pEd->SetWindowText(itoa(iNumber,astring,10));
		pEd->UpdateWindow();

// limit the number of electrons to be removed / added according to the number of atoms
// According to Larsson's model is one electron per Cu atom
		CSpinButtonCtrl* spin;
		spin = (CSpinButtonCtrl*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_SPIN_ELECTRONS_REMOVED);
// feature of the spin control button makes +-1 as necessity
		spin->SetRange(-iNumber*iNumber,iNumber*iNumber);

		CButton *btn;
		btn = (CButton*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_CHECK_ISSCF);
		if(pDoc->GetDoWithoutSelfConsistency())
		{
			btn->SetCheck(0);
		}
		else
		{
			btn->SetCheck(1);
		}

		CCurrents2DView* pView;
		pView = (CCurrents2DView*)GetActiveView();
		ASSERT(pView->IsKindOf(RUNTIME_CLASS(CCurrents2DView)));
		pEd = (CEdit*)pFrame->m_wndDlgBar2D.GetDlgItem(IDC_EDIT_ZOOM_FACTOR);
		dNumber = pView->GetZoomFactor();
		pEd->SetWindowText(_gcvt(dNumber,5,astring));
		pEd->UpdateWindow();
	}
}

