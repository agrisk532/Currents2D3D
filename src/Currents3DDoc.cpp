// Currents3DDoc.cpp : implementation of the CCurrents3DDoc class
//

#include "stdafx.h"
#include "Currents2D3D.h"

#include "PlotIt.h"
#include "Distances.h"
#include "AtomLayers.h"
#include "AtomCoordinates.h"
#include "FieldGrid.h"
#include "Cu1Layer.h"
#include "Cu2Layer.h"
#include "BaLayer.h"
#include "O1Layer.h"
#include "O2Layer.h"
#include "O4Layer.h"
#include "YLayer.h"
#include "Currents.h"
#include "Currents3D.h"
#include "Constants.h"
#include "rendering.h"
#include "AtomParameters.h"
#include "fileIO.h"
#include "Textvw.h"

#include "Currents3DDoc.h"
#include "Currents3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrents2D3DDoc

IMPLEMENT_DYNCREATE(CCurrents3DDoc, CDocument)

BEGIN_MESSAGE_MAP(CCurrents3DDoc, CDocument)
	//{{AFX_MSG_MAP(CCurrents3DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurrents3DDoc construction/destruction

CCurrents3DDoc::CCurrents3DDoc()
{
	// TODO: add one-time construction code here
	m_nAtoms = 0;
	m_nMagneticField = 0.;	// in gauss
	m_nTau = 1.;
	m_nEo = -1.;
	m_nEm = 0.;
	m_bDoWithoutSelfConsistency = true;
	m_bCalculatedOK = false;
	m_nElectronsRemoved = 0;
	m_ObjectToRender = Currents_1D;
	m_nUnitCellsAlongC = 1;

	m_pAcoord = NULL;
	m_pDist = NULL;
	for(int i=0 ; i<ATOM_LAYERS_3D ; i++) m_pAl[i] = NULL;  // pointer to different layers
	m_pCurr = NULL;
	m_pCurr3D = NULL;
// default settings for atom plotting
	m_atomLayerPlotFlag[0] = 1;
	m_atomLayerPlotFlag[1] = 0;
	m_atomLayerPlotFlag[2] = 1;
	m_atomLayerPlotFlag[3] = 0;
	m_atomLayerPlotFlag[4] = 0;
	m_atomLayerPlotFlag[5] = 0;
	m_atomLayerPlotFlag[6] = 0;
	m_atomLayerPlotFlag[7] = 0;
	m_atomLayerPlotFlag[8] = 1;
}

/////////////////////////////////////////////////////////////////////////////
CCurrents3DDoc::~CCurrents3DDoc()
{
	if(m_pDist)
	{
		delete m_pDist;
		m_pDist = NULL;
	}
	if(m_pAcoord)
	{
		delete m_pAcoord;
		m_pAcoord = NULL;
	}
	if(m_pCurr)
	{
		delete m_pCurr;
		m_pCurr = NULL;
	}
	if(m_pCurr3D)
	{
		delete m_pCurr3D;
		m_pCurr3D = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
//
BOOL CCurrents3DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
// clear all views
	ClearViews();
	m_bCalculatedOK = false;
//	m_bDoWithoutSelfConsistency = true;
	InitializeCurrents3DDoc();
		return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//  Document initialization routine

void CCurrents3DDoc::InitializeCurrents3DDoc()
{
	if(m_pDist)
	{
		delete m_pDist;
		m_pDist = NULL;
	}
	if(m_pAcoord)
	{
		delete m_pAcoord;
		m_pAcoord = NULL;
	}
	if(m_pCurr)
	{
		delete m_pCurr;
		m_pCurr = NULL;
	}
	if(m_pCurr3D)
	{
		delete m_pCurr3D;
		m_pCurr3D = NULL;
	}
}	


/////////////////////////////////////////////////////////////////////////////
// CCurrents3DDoc serialization

void CCurrents3DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nAtoms;
//		ar << m_nCuCuDistance;
		ar << m_nMagneticField;
		ar << m_nElectronsRemoved;
//		ar << m_ObjectToRender;
//		for(int i=0; i<ATOM_LAYERS_3D; i++)
//			ar << m_atomLayerPlotFlag[i];
	}
	else
	{
		// TODO: add loading code here
		ar >> m_nAtoms;
//		ar << m_nCuCuDistance;
		ar >> m_nMagneticField;
		ar >> m_nElectronsRemoved;
//		ar >> m_ObjectToRender;
//		for(int i=0; i<ATOM_LAYERS_3D; i++)
//			ar >> m_atomLayerPlotFlag[i];
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCurrents3DDoc diagnostics

#ifdef _DEBUG
void CCurrents3DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCurrents3DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurrents3DDoc commands

CurrentsBase* CCurrents3DDoc::Calculate() // returns pointer to the m_pCurr or m_pCurr3D
{
	int i;
//	const ObjectToRender objToRender = Currents_1D; // choose what to render (see rendering.h)
	int randomGeneratorSeed; // for streamlines

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

	AtomParameters *ap;

// pointers to different possible atomic layers

	Cu2Layer *cu2_lower;
	O2Layer *o2_lower;
	Cu2Layer *cu2_upper;
	O2Layer *o2_upper;
	YLayer *y;
	BaLayer *ba;
	O4Layer *o4;
	O1Layer *o1;
	Cu1Layer *cu1;

// for streamline initial positions
	randomGeneratorSeed = 1024;

// make distances object
	m_pDist = new Distances;
	m_pDist->Set_cells_x(m_nAtoms-1);
	m_pDist->Set_cells_y(m_nAtoms-1);
	m_pDist->Set_cells_z(m_nUnitCellsAlongC);

//  initialization for testing all layers
//	for(int i=0 ; i<ATOM_LAYERS ; i++) atomLayerPlotFlag[i] = 1;

// make a new atom coordinates object
	m_pAcoord = new AtomCoordinates;
// set the reference to the Distances object to be used from all Layer objects
//	AtomLayers::SetDistances(m_pDist);
//	Bond::SetAtomCoordinates(m_pAcoord);

// 	calculate the pointers to different atom layers
	m_pAl[0] = cu2_lower = (m_atomLayerPlotFlag[0] == 1) ? Cu2Layer::New('l',m_pDist) : NULL;
	m_pAl[1] = o2_lower = (m_atomLayerPlotFlag[1] == 1) ? O2Layer::New('l',m_pDist) : NULL;
	m_pAl[2] = cu2_upper = (m_atomLayerPlotFlag[2] == 1) ? Cu2Layer::New('u',m_pDist) : NULL;
	m_pAl[3] = o2_upper = (m_atomLayerPlotFlag[3] == 1) ? O2Layer::New('u',m_pDist) : NULL;
	m_pAl[4] = y = (m_atomLayerPlotFlag[4] == 1) ? YLayer::New(m_pDist) : NULL;
	m_pAl[5] = ba = (m_atomLayerPlotFlag[5] == 1) ? BaLayer::New(m_pDist) : NULL;
	m_pAl[6] = o4 = (m_atomLayerPlotFlag[6] == 1) ? O4Layer::New(m_pDist) : NULL;
	m_pAl[7] = o1 = (m_atomLayerPlotFlag[7] == 1) ? O1Layer::New(m_pDist) : NULL;
	m_pAl[8] = cu1 = (m_atomLayerPlotFlag[8] == 1) ? Cu1Layer::New(m_pDist) : NULL;

// add atom layer objects (coordinates and types) to the AtomCoordinates object
	for(i=0 ; i<ATOM_LAYERS_3D ; i++)
	{
		if(m_pAl[i] == NULL) continue;
		m_pAcoord->AddLayer(m_pAl[i]);
	}

// now distinguish between two cases
// 1) - calculate the curents only in bonds (not in 3D space)
// 2) - calculate the currents in 3D space, without selfconsistency

// calculate currents in CuO2 layers

//	bool doWithoutSelfConsistency = true;  // used only in 1DCurrents rendering

// calculate the 1D current case

	if(m_ObjectToRender == Currents_1D)
	{
		m_pCurr = Currents::New(m_bDoWithoutSelfConsistency,m_nMagneticField);
		m_pCurr->SetDistances(m_pDist);
		m_pCurr->SetCoordinates(m_pAcoord);

		m_pCurr->AddLayer(m_pAl[0]);  // add Cu2_lower layer coordinates for electrical current CALCULATION
		m_pCurr->AddLayer(m_pAl[2]);  // add Cu2_upper layer coordinates for electrical current CALCULATION

// set the gauge origin in the symmetry center of the layers included in calculation
// use single gauge origin
		m_pCurr->SetGaugeOrigin();
		m_pAcoord->TranslateToGaugeOrigin();
		m_pCurr->SetElectronsRemoved(m_nElectronsRemoved);
		m_pCurr->SetDocument(this); // for getting back iteration intermediate results
// calculate the grid
		m_pGrid = FieldGrid::New(*m_pAcoord,*m_pDist);

		int gridDimension = m_pGrid->GetGridDimensionX()*m_pGrid->GetGridDimensionY()*
							m_pGrid->GetGridDimensionZ();

		CTextView* tv = GetTextView();
		tv->AddLine("YBaCuO crystal 3D superconducting ground currents");
		tv->AddLine(" ");

		CString line;
		line.Format("Points in the grid : %d ",gridDimension);
		tv->AddLine(line);

// calculate the bond currents
		m_nIterations = m_pCurr->CalculateCurrentsInBonds(m_nTau,m_nEo,m_nEm,m_bDoWithoutSelfConsistency);
		if(m_nIterations == -1) // not achieved self consistency
		{
			return NULL;
		}
		m_pCurr->CalculateMagneticFieldOnGrid(m_pGrid); // calculate the magnetic field
		m_bCalculatedOK = true;

		return m_pCurrBase = m_pCurr;
	}

	else // Currents3D
	if(m_ObjectToRender == Currents_3D)
	{
		double c[2]; // holds AO coefficients (double zeta)
		double e[2]; // holds AO exponents (double zeta)
		c[0] = 0.6583;
		c[1] = 0.5307;
		e[0] = 5.5454;
		e[1] = 1.9715;
		ap = AtomParameters::New(c,e); // set up an atom parameters object
		ap->SetCoordinates(m_pAcoord);

		CTextView* tv = GetTextView();
		tv->AddLine("YBaCuO crystal 3D superconducting ground currents");
		tv->AddLine(" ");
		tv->AddLine("Double zeta basis set for Cu(x2-y2) orbitals");

		CString line;
		line.Format("AO coefficients : %f %f",c[0],c[1]);
		tv->AddLine(line);
		line.Format("AO exponents : %f %f",e[0],e[1]);
		tv->AddLine(line);

		m_pCurr3D = Currents3D::New(m_nMagneticField);
		m_pCurr3D->SetDistances(m_pDist);
		m_pCurr3D->SetCoordinates(m_pAcoord);
		m_pCurr3D->SetAtomParameters(ap);

		m_pCurr3D->AddLayer(m_pAl[0]);  // add Cu2_lower layer coordinates for electrical current CALCULATION
		m_pCurr3D->AddLayer(m_pAl[2]);  // add Cu2_upper layer coordinates for electri

		m_pCurr3D->SetElectronsRemoved(m_nElectronsRemoved);
		m_pCurr3D->SetDocument(this); // for getting back iteration intermediate results
// calculate the grid
		m_pGrid = FieldGrid::New(*m_pAcoord,*m_pDist);
		int gridDimension = m_pGrid->GetGridDimensionX()*m_pGrid->GetGridDimensionY()*
							m_pGrid->GetGridDimensionZ();

		line.Format("Points in the grid : %d ",gridDimension);
		tv->AddLine(line);

// calculate the 3D currents
// enum ReadOrWriteFieldToFile {WriteFieldToFile,ReadFieldFromFile};
		ReadOrWriteFieldToFile rw = WriteFieldToFile;
		m_pCurr3D->Calculate(m_nTau,m_nEo,m_nEm,m_pGrid,rw);
		m_bCalculatedOK = true;
		m_nIterations = 1;

		return m_pCurrBase = m_pCurr3D;
	}
}

//////////////////////////////////////////////////////////////////////////
// view initialization (only once after document created)
void CCurrents3DDoc::InitializeCurrents3DView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CCurrents3DView)))
		{
			CCurrents3DView* pV = (CCurrents3DView*) pView;
			pV->PrepareForPlot(m_pAcoord,m_pGrid,m_pDist,m_pCurrBase);
		}
		else
			continue;
	}
}

//////////////////////////////////////////////////////////////////////////
//  clears all views at File->New command and when user changes numbers on rebar
void CCurrents3DDoc::ClearViews()
{

	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CCurrents3DView)))
		{
			CCurrents3DView* pV = (CCurrents3DView*) pView;

			if(pV->m_pRenderer)
			{
				pV->m_pRenderer->Delete();
				pV->m_pRenderer = NULL;
			}
			if(pV->m_pRenWin)
			{
				pV->m_pRenWin->Delete();
				pV->m_pRenWin = NULL;
			}
			if(pV->m_poTFun)
			{
				pV->m_poTFun->Delete();
				pV->m_poTFun = NULL;
			}
			if(pV->m_pcTFun)
			{
				pV->m_pcTFun->Delete();
				pV->m_pcTFun = NULL;
			}
			if(pV->m_pvolumeProperty)
			{
				pV->m_pvolumeProperty->Delete();
				pV->m_pvolumeProperty = NULL;
			}
			if(pV->m_pcompositeFunction)
			{
				pV->m_pcompositeFunction->Delete();
				pV->m_pcompositeFunction = NULL;
			}
			if(pV->m_pMIPFunction)
			{
				pV->m_pMIPFunction->Delete();
				pV->m_pMIPFunction = NULL;
			}
			if(pV->m_pvolSurf)
			{
				pV->m_pvolSurf->Delete();
				pV->m_pvolSurf = NULL;
			}
			if(pV->m_pvolumeMapper)
			{
				pV->m_pvolumeMapper->Delete();
				pV->m_pvolumeMapper = NULL;
			}
			if(pV->m_pvolume)
			{
				pV->m_pvolume->Delete();
				pV->m_pvolume = NULL;
			}
			if(pV->m_prakePoints)
			{
				pV->m_prakePoints->Delete();
				pV->m_prakePoints = NULL;
			}
			if(pV->m_pugrid)
			{
				pV->m_pugrid->Delete();
				pV->m_pugrid = NULL;
			}
			if(pV->m_pstreamLine)
			{
				pV->m_pstreamLine->Delete();
				pV->m_pstreamLine = NULL;
			}
			if(pV->m_pstreamsMapper)
			{
				pV->m_pstreamsMapper->Delete();
				pV->m_pstreamsMapper = NULL;
			}
			if(pV->m_plines)
			{
				pV->m_plines->Delete();
				pV->m_plines= NULL;
			}
			if(pV->m_pstreamTube)
			{
				pV->m_pstreamTube->Delete();
				pV->m_pstreamTube = NULL;
			}
			if(pV->m_ptubeMapper)
			{
				pV->m_ptubeMapper->Delete();
				pV->m_ptubeMapper = NULL;
			}
			if(pV->m_ptubes)
			{
				pV->m_ptubes->Delete();
				pV->m_ptubes = NULL;
			}
			if(pV->m_phedgeHog)
			{
				pV->m_phedgeHog->Delete();
				pV->m_phedgeHog = NULL;
			}
			if(pV->m_phhMapper)
			{
				pV->m_phhMapper->Delete();
				pV->m_phhMapper = NULL;
			}
			if(pV->m_phhActor)
			{
				pV->m_phhActor->Delete();
				pV->m_phhActor = NULL;
			}
			if(pV->m_pIren)
			{
				pV->m_pIren->Delete();
				pV->m_pIren = NULL;
			}

			for(int i=0; i<ATOM_TYPES; i++)
			{
				if(pV->m_ps[i])
				{
					pV->m_ps[i]->Delete();
					pV->m_ps[i] = NULL;
				}
				if(pV->m_ppdmSpheres[i])
				{
					pV->m_ppdmSpheres[i]->Delete();
					pV->m_ppdmSpheres[i] = NULL;
				}
			}

			for(i=0; i<1000; i++)
			{
				if(pV->m_patomActor[i])
				{
					pV->m_patomActor[i]->Delete();
					pV->m_patomActor[i] = NULL;
				}
				if(pV->m_pcolorIt[i])
				{
					pV->m_pcolorIt[i]->Delete();
					pV->m_pcolorIt[i] = NULL;
				}
				if(pV->m_plut[i])
				{
					pV->m_plut[i]->Delete();
					pV->m_plut[i] = NULL;
				}
			}

			for(i=0; i<4000; i++)
			{
				if(pV->m_pcyl[i])
				{
					pV->m_pcyl[i]->Delete();
					pV->m_pcyl[i] = NULL;
				}
				if(pV->m_ppdmCyls[i])
				{
					pV->m_ppdmCyls[i]->Delete();
					pV->m_ppdmCyls[i] = NULL;
				}
				if(pV->m_pcylActor[i])
				{
					pV->m_pcylActor[i]->Delete();
					pV->m_pcylActor[i] = NULL;
				}
			}
		}
		else
		if(pView->IsKindOf(RUNTIME_CLASS(CTextView)))
		{
			CTextView* pV = (CTextView*) pView;
			pV->Delete();
		}
	}
}

///////////////////////////////////////////////////////////////////////
//
CTextView* CCurrents3DDoc::GetTextView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CTextView)))
		{
			return (CTextView*) pView;
		}
	}
}
