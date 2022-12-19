// Currents2DDoc.cpp : implementation of the CCurrents2DDoc class
//

#include "stdafx.h"
#include "Currents2D3D.h"

#include "Currents2DDoc.h"
#include "Currents2DView.h"
#include "Currents.h"
#include "Distances.h"
#include "Cu2Layer.h"
#include "AtomCoordinates.h"
#include "AtomLayers.h"
#include "Bond.h"
#include "Textvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCurrents2DDoc

IMPLEMENT_DYNCREATE(CCurrents2DDoc, CDocument)

BEGIN_MESSAGE_MAP(CCurrents2DDoc, CDocument)
	//{{AFX_MSG_MAP(CCurrents2DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DDoc construction/destruction

CCurrents2DDoc::CCurrents2DDoc()
{
	// TODO: add one-time construction code here
	m_nAtoms = 0;
	m_nCuCuDistance = 0;	// in angstroms
	m_nMagneticField = 0.;	// in gauss
	m_nTau = 1.;
	m_nEo = -1.;
	m_nEm = 0.;
	m_bDoWithoutSelfConsistency = true;
	m_bCalculatedOK = false;
	m_nElectronsRemoved = 0;

	m_pAcoord = 0;
	m_pDist = 0;
	m_pAl[0] = 0;  // pointer to different layers
	m_pCurr = 0;
	m_pCu2_lower = 0;
}

CCurrents2DDoc::~CCurrents2DDoc()
{
	if(m_pDist)
	{
		delete m_pDist;
		m_pDist = 0;
	}
	if(m_pAcoord)
	{
		delete m_pAcoord;
		m_pAcoord = 0;
	}
	if(m_pCurr)
	{
		delete m_pCurr;
		m_pCurr = 0;
	}
}
//////////////////////////////////////////////////////////////////////////
//
BOOL CCurrents2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
// clear all views
	ClearViews();
//	ClearCurrents2DView();
//	ClearTextView();
	m_bCalculatedOK = false;
	m_bDoWithoutSelfConsistency = true;
	InitializeCurrents2DDoc();
		return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//  Document initialization routine

void CCurrents2DDoc::InitializeCurrents2DDoc()
{
	if(m_pDist)
	{
		delete m_pDist;
		m_pDist = 0;
	}
	if(m_pAcoord)
	{
		delete m_pAcoord;
		m_pAcoord = 0;
	}
	if(m_pCurr)
	{
		delete m_pCurr;
		m_pCurr = 0;
	}
}	
//////////////////////////////////////////////////////////////////////////
// view initialization (only once after document created)
void CCurrents2DDoc::InitializeCurrents2DView()
{
	POSITION pos = GetFirstViewPosition();
	CCurrents2DView* pFirstView = (CCurrents2DView*) GetNextView( pos );
	pFirstView->New(m_nAtoms,m_pCurr->GetNumberOfBonds());
}

//////////////////////////////////////////////////////////////////////////
//
//void CCurrents2DDoc::ClearCurrents2DView()
//{
//	POSITION pos = GetFirstViewPosition();
//	CCurrents2DView* pFirstView = (CCurrents2DView*) GetNextView( pos );
//	pFirstView->Delete();
//}
//
void CCurrents2DDoc::ClearViews()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);

		if(pView->IsKindOf(RUNTIME_CLASS(CCurrents2DView)))
		{
			CCurrents2DView* pView1 = (CCurrents2DView*) pView;
			pView1->Delete();
		}

		if(pView->IsKindOf(RUNTIME_CLASS(CTextView)))
		{
			CTextView* pView1 = (CTextView*) pView;
			pView1->Delete();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DDoc serialization

void CCurrents2DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nAtoms;
//		ar << m_nCuCuDistance;
		ar << m_nMagneticField;
		ar << m_nElectronsRemoved;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_nAtoms;
//		ar >> m_nCuCuDistance;
		ar >> m_nMagneticField;
		ar >> m_nElectronsRemoved;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DDoc diagnostics

#ifdef _DEBUG
void CCurrents2DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCurrents2DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurrents2DDoc commands

#define ATOM_LAYERS 1

int CCurrents2DDoc::Calculate()
{
	int atomLayerPlotFlag[ATOM_LAYERS] = {1}; // set 1 to plot the corresponding type layer, 0 if not

//  Layer identification
//
//	0 - cu2_lower  (lower means below Y layer)
//	1 - o2_lower
//	2 - cu2_upper
//	3 - o2_upper
//	4 - y
//	5 - ba
//	6 - o4
//	7 - o1
//	8 - cu1

// make distances object
	m_pDist = new Distances;
	m_pDist->Set_cells_x(m_nAtoms-1);
	m_pDist->Set_cells_y(m_nAtoms-1);
	m_pDist->Set_cells_z(1);
	m_pDist->Set_cell_width_x(m_nCuCuDistance);
	m_pDist->Set_cell_width_y(m_nCuCuDistance);

//  initialization for testing all layers
//	for(int i=0 ; i<ATOM_LAYERS ; i++) atomLayerPlotFlag[i] = 1;

// make a new atom coordinates object
	m_pAcoord = new AtomCoordinates;
// set the reference to the Distances object to be used from all Layer objects
//	AtomLayers::SetDistances(m_pDist);
//	Bond::SetAtomCoordinates(m_pAcoord);

// 	calculate the pointers to different atom layers
	m_pAl[0] = m_pCu2_lower = (atomLayerPlotFlag[0] == 1) ?
									Cu2Layer::New('l',m_pDist) : NULL;

// add atom layer objects (coordinates and types) to the AtomCoordinates object
	for(int i=0 ; i<ATOM_LAYERS ; i++)
	{
		if(m_pAl[i] == NULL) continue;
		m_pAcoord->AddLayer(m_pAl[i]);
	}


// calculate the 1D current case

	m_pCurr = Currents::New(m_bDoWithoutSelfConsistency,m_nMagneticField);
	m_pCurr->SetDistances(m_pDist);
	m_pCurr->SetCoordinates(m_pAcoord);
	m_pCurr->AddLayer(m_pAl[0]);  // add Cu2_lower layer coordinates for electrical current CALCULATION

// set the gauge origin in the symmetry center of the layers included in calculation
// use single gauge origin
	m_pCurr->SetGaugeOrigin();
	m_pAcoord->TranslateToGaugeOrigin();

// calculate the bond currents
	m_pCurr->SetElectronsRemoved(m_nElectronsRemoved);
	m_pCurr->SetDocument(this); // for getting back iteration intermediate results
	m_pCurr->CalculateCurrentsInBonds(m_nTau,m_nEo,m_nEm,m_bDoWithoutSelfConsistency);
// get number of iterations performed in scf
	m_nIterations = m_pCurr->GetNumberOfIterations();


// Cleanup... Coordinates now are stored in AtomCoordinates

	delete m_pCu2_lower;
	m_bCalculatedOK = true;

	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
void CCurrents2DDoc::SetIterationRms(double rms)
{
	m_nIterationRms = rms;
}
