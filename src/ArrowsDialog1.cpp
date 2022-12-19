// ArrowsDialog1.cpp : implementation file
//

#include "stdafx.h"
#include "Currents2D3D.h"
#include "ArrowsDialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ArrowsDialog dialog


ArrowsDialog::ArrowsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ArrowsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ArrowsDialog)
	m_nArrowsAngle = 30.0;
	m_nArrowsLength = 0.2;
	m_nArrowsWidth = 10;
	//}}AFX_DATA_INIT
}


void ArrowsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ArrowsDialog)
	DDX_Text(pDX, IDC_EDIT_ARROWS_ANGLE, m_nArrowsAngle);
	DDV_MinMaxDouble(pDX, m_nArrowsAngle, 0., 90.);
	DDX_Text(pDX, IDC_EDIT_ARROWS_LENGTH, m_nArrowsLength);
	DDV_MinMaxDouble(pDX, m_nArrowsLength, 0., 1.);
	DDX_Text(pDX, IDC_EDIT_ARROWS_WIDTH, m_nArrowsWidth);
	DDV_MinMaxUInt(pDX, m_nArrowsWidth, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ArrowsDialog, CDialog)
	//{{AFX_MSG_MAP(ArrowsDialog)
	ON_BN_CLICKED(IDC_BUTTON_ARROWS_OK, OnButtonArrowsOk)
	ON_BN_CLICKED(IDC_BUTTON_ARROWS_CANCEL, OnButtonArrowsCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArrowsDialog message handlers

void ArrowsDialog::OnButtonArrowsOk() 
{
	// TODO: Add your control notification handler code here
	OnOK();

//	EndDialog(IDOK);
}

/////////////////////////////////////////////////////////////////////////////
//
void ArrowsDialog::OnButtonArrowsCancel() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
//	EndDialog(IDCANCEL);
}

/////////////////////////////////////////////////////////////////////////////
//
BOOL ArrowsDialog::OnInitDialog() 
{

	CSpinButtonCtrl* spin = (CSpinButtonCtrl*)this->GetDlgItem(IDC_SPIN_ARROWS_WIDTH);
	spin->SetBuddy(this->GetDlgItem(IDC_EDIT_ARROWS_WIDTH));
	spin->SetBase(10);
	spin->SetRange(2,100);

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
//
