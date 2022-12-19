// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Currents2D3D.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_HHNOTIFICATION, OnHhnotification)
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

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_nNumberOf2DMDIClients = 0;
	m_nNumberOf3DMDIClients = 0;
	m_mainToolBarIsOn = false;
}

CMainFrame::~CMainFrame()
{
}

////////////////////////////////////////////////////////////////////////
//

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndReBar.Create(this))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

// create the common controls for rebarControl bands

	if (!m_wndToolBar2D.CreateEx(this) ||
		!m_wndToolBar2D.LoadToolBar(IDR_CURRENTS2D))
	{
		TRACE0("Failed to create toolbar2D\n");
		return -1;      // fail to create
	}
    if (!m_wndDlgBar2D.Create(this, IDR_CURRENTS2D, 
		CBRS_NOALIGN, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
	if (!m_wndToolBar3D.CreateEx(this) ||
		!m_wndToolBar3D.LoadToolBar(IDR_CURRENTS3D))
	{
		TRACE0("Failed to create toolbar3D\n");
		return -1;      // fail to create
	}
    if (!m_wndDlgBar3D.Create(this, IDR_CURRENTS3D, 
		CBRS_NOALIGN, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create mainframe toolbar\n");
		return -1;      // fail to create
	}

	CSpinButtonCtrl* spin;
	spin = (CSpinButtonCtrl*)m_wndDlgBar2D.GetDlgItem(IDC_SPIN_NMBCUATOMS);
	spin->SetBuddy(m_wndDlgBar2D.GetDlgItem(IDC_EDIT_NMBCUATOMS));
	spin->SetBase(10);
	spin->SetRange(2,100);

	spin = (CSpinButtonCtrl*)m_wndDlgBar2D.GetDlgItem(IDC_SPIN_ELECTRONS_REMOVED);
	spin->SetBuddy(m_wndDlgBar2D.GetDlgItem(IDC_EDIT_ELECTRONS_REMOVED));
	spin->SetBase(10);
	spin->SetRange(-8,8); // for 8 Cu atoms (2*2*2)

	spin = (CSpinButtonCtrl*)m_wndDlgBar3D.GetDlgItem(IDC_SPIN_NMBCUATOMS3);
	spin->SetBuddy(m_wndDlgBar3D.GetDlgItem(IDC_EDIT_NMBCUATOMS3));
	spin->SetBase(10);
	spin->SetRange(2,100);

	spin = (CSpinButtonCtrl*)m_wndDlgBar3D.GetDlgItem(IDC_SPIN_ELECTRONS_REMOVED3);
	spin->SetBuddy(m_wndDlgBar3D.GetDlgItem(IDC_EDIT_ELECTRONS_REMOVED3));
	spin->SetBase(10);
	spin->SetRange(-100,100);

// add rebar bands
	if(!m_wndReBar.AddBar(&m_wndToolBar2D))
	{
		TRACE0("Failed to insert band0\n");
		return -1;		// fail to create
	}

	if(!m_wndReBar.AddBar(&m_wndDlgBar2D))
	{
		TRACE0("Failed to insert band1\n");
		return -1;		// fail to create
	}
	if(!m_wndReBar.AddBar(&m_wndToolBar3D))
	{
		TRACE0("Failed to insert band2\n");
		return -1;		// fail to create
	}
	if(!m_wndReBar.AddBar(&m_wndDlgBar3D))
	{
		TRACE0("Failed to insert band3\n");
		return -1;		// fail to create
	}

	if(!m_wndReBar.AddBar(&m_wndToolBar))
	{
		TRACE0("Failed to insert band4\n");
		return -1;		// fail to create
	}


// hide rebar bands

	m_wndReBar.GetReBarCtrl().ShowBand(0,FALSE);
	m_wndReBar.GetReBarCtrl().ShowBand(1,FALSE);
	m_wndReBar.GetReBarCtrl().ShowBand(2,FALSE);
	m_wndReBar.GetReBarCtrl().ShowBand(3,FALSE);
	m_wndReBar.GetReBarCtrl().ShowBand(4,FALSE);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar2D.SetBarStyle(CBRS_TOOLTIPS | CBRS_ALIGN_ANY | CBRS_FLYBY);
	m_wndToolBar3D.SetBarStyle(CBRS_TOOLTIPS | CBRS_ALIGN_ANY | CBRS_FLYBY);
	m_wndToolBar.SetBarStyle(CBRS_TOOLTIPS | CBRS_ALIGN_ANY | CBRS_FLYBY);

	return 0;
}
//////////////////////////////////////////////////////////////////
//

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnHhnotification() 
{
	HtmlHelp(NULL, "Currents2D3D.chm", HH_DISPLAY_TOPIC, 0);
}
