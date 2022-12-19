// Currents3DView.cpp : implementation of the CCurrents3DView class
//

#include "stdafx.h"

#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMIPFunction.h"
#include "vtkVolumeRayCastIsosurfaceFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkVolume.h"
#include "vtkPoints.h"
#include "vtkUnstructuredGrid.h"
#include "vtkStreamLine.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkTubeFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkHedgeHog.h"
#include "vtkSphereSource.h"
#include "vtkElevationFilter.h"
#include "vtkLookupTable.h"
#include "vtkCylinderSource.h"
#include "vtkDataSetMapper.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkWindowToImageFilter.h"
#include "vtkBMPWriter.h"
#include "vtkWindow.h"

#include "Currents2D3D.h"
#include "FieldGrid.h"
#include "AtomCoordinates.h"
#include "Currents3DDoc.h"
#include "Currents3DView.h"
#include "MainFrm.h"
#include "Currents.h"
#include "Currents3D.h"
#include "Child3DFrame.h"

#include "PropertyPageAtoms.h"
#include "PropertyPageObjToRender.h"
#include "PropertyPageRendMethod.h"
#include "PropertyPageRegions.h"

#include "rendering.h"

#include <afxole.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrents3DView

IMPLEMENT_DYNCREATE(CCurrents3DView, CScrollView)

BEGIN_MESSAGE_MAP(CCurrents3DView, CScrollView)
	//{{AFX_MSG_MAP(CCurrents3DView)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_TOOLS_IMAGESETUP, OnToolsImagesetup)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurrents2D3DView construction/destruction

CCurrents3DView::CCurrents3DView()
{
//	m_objToRender = Currents_3D;
	m_renderMethod = VolumeRayCastComposite;
	m_renderRegion = APPLIED_FIELD;
	m_nRandomGeneratorSeed = 1024;
	m_bIs3DCurrent = false;
	m_nNumberOfAtoms = 0;
	m_nNumberOfBonds = 0;
	m_nIsosurfaceValue = 0.;
	m_nInitialFieldValueForRendering = 0;

	m_pRenderer = NULL;
	m_pRenWin = NULL;
	m_poTFun = NULL;
	m_pcTFun = NULL;
	m_pvolumeProperty = NULL;
	m_pcompositeFunction = NULL;
	m_pMIPFunction = NULL;
	m_pvolSurf = NULL;
	m_pvolumeMapper = NULL;
	m_pvolume = NULL;
	m_prakePoints = NULL;
	m_pugrid = NULL;
	m_pstreamLine = NULL;
	m_pstreamsMapper = NULL;
	m_plines = NULL;
	m_pstreamTube = NULL;
	m_ptubeMapper = NULL;
	m_ptubes = NULL;
	m_phedgeHog = NULL;
	m_phhMapper = NULL;
	m_phhActor = NULL;
	m_pIren = NULL;
	for(int i=0; i<ATOM_TYPES; i++)
	{
		m_ps[i] = NULL;
		m_ppdmSpheres[i] = NULL;
	}
	for( i=0; i<1000; i++)
	{
		m_patomActor[i] = NULL;
		m_pcolorIt[i] = NULL;
		m_plut[i] = NULL;
	}
	for( i=0; i<4000; i++)
	{
		m_pcyl[i] = NULL;
		m_ppdmCyls[i] = NULL;
		m_pcylActor[i] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
//

CCurrents3DView::~CCurrents3DView()
{
	if(m_pRenderer) m_pRenderer->Delete();
	if(m_pRenWin) m_pRenWin->Delete();
	if(m_poTFun) m_poTFun->Delete();
	if(m_pcTFun) m_pcTFun->Delete();
	if(m_pvolumeProperty) m_pvolumeProperty->Delete();
	if(m_pcompositeFunction) m_pcompositeFunction->Delete();
	if(m_pMIPFunction) m_pMIPFunction->Delete();
	if(m_pvolSurf) m_pvolSurf->Delete();
	if(m_pvolumeMapper) m_pvolumeMapper->Delete();
	if(m_pvolume) m_pvolume->Delete();
	if(m_prakePoints) m_prakePoints->Delete();
	if(m_pugrid) m_pugrid->Delete();
	if(m_pstreamLine) m_pstreamLine->Delete();
	if(m_pstreamsMapper) m_pstreamsMapper->Delete();
	if(m_plines) m_plines->Delete();
	if(m_pstreamTube) m_pstreamTube->Delete();
	if(m_ptubeMapper) m_ptubeMapper->Delete();
	if(m_ptubes) m_ptubes->Delete();
	if(m_phedgeHog) m_phedgeHog->Delete();
	if(m_phhMapper) m_phhMapper->Delete();
	if(m_phhActor) m_phhActor->Delete();
	if(m_pIren) m_pIren->Delete();

	for(int i=0; i<ATOM_TYPES; i++)
	{
		if(m_ps[i]) m_ps[i]->Delete();
		if(m_ppdmSpheres[i]) m_ppdmSpheres[i]->Delete();
	}

	for(i=0; i<1000; i++)
	{
		if(m_patomActor[i]) m_patomActor[i]->Delete();
		if(m_pcolorIt[i]) m_pcolorIt[i]->Delete();
		if(m_plut[i]) m_plut[i]->Delete();
	}

	for(i=0; i<4000; i++)
	{
		if(m_pcyl[i]) m_pcyl[i]->Delete();
		if(m_ppdmCyls[i]) m_ppdmCyls[i]->Delete();
		if(m_pcylActor[i]) m_pcylActor[i]->Delete();
	}
}

/////////////////////////////////////////////////////////////////////
//

BOOL CCurrents3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCurrents3DView drawing

void CCurrents3DView::OnDraw(CDC* pDC)
{

	CCurrents3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

// finds out the logical size of the view and writes it to the member variable
// when I put pDC->GetClipBox(&rect), copying to clipboard doesn't work

	if(pDoc->GetCalculatedOK())	// document has data for plotting
	{
//		m_objToRender = Currents_3D;
//		m_renderMethod = VolumeRayCastMIP;
//		m_nRandomGeneratorSeed = 1024; // for streamlines
//		PrepareForPlot(pDoc->m_pAcoord,pDoc->m_pGrid,pDoc->m_pDist,pDoc->m_pCurrBase);

		CRect rect;
		this->GetClientRect(&rect);
		m_pRenWin->SetSize(rect.right,rect.bottom);
		m_pRenWin->Render();

		WriteStatusBarMessage(); // writes number of scf iterations performed
	}
}
/////////////////////////////////////////////////////////////////////////////
//
void CCurrents3DView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CCurrents3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle("Cu-Cu bond currents,applied magnetic field,VolRayCastComposite rendering");

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	OleInitialize(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CCurrents3DView printing

BOOL CCurrents3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCurrents3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCurrents3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCurrents3DView diagnostics

#ifdef _DEBUG
void CCurrents3DView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCurrents3DView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

///////////////////////////////////////////////////////////////////////////
//
CCurrents3DDoc* CCurrents3DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurrents3DDoc)));
	return (CCurrents3DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurrents2D3DView message handlers

void CCurrents3DView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
//	SetScrollSizes(MM_TEXT,GetViewSize());
	CScrollView::OnUpdate(pSender,lHint,pHint);
}

////////////////////////////////////////////////////////////////////
//
void CCurrents3DView::WriteStatusBarMessage()
{
	CCurrents3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->GetCalculatedOK())
	{
		CStatusBar* sb;
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		CString msg;
		msg.Format("Done in %d iterations. Use the left mouse button to rotate the object and the right to zoom...",pDoc->GetIterations());
		sb = (CStatusBar*) pFrame->GetMessageBar();
		sb->SetWindowText(msg);
	}
}

//////////////////////////////////////////////////////////////////////////
// Copies the currents view to the clipboard using OLE
void CCurrents3DView::OnEditCopy() 
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


///////////////////////////////////////////////////////////////////////////////
//

void CCurrents3DView::PrepareForPlot(AtomCoordinates* ac, FieldGrid* fg, Distances* d,
						CurrentsBase* calculatedCurrents)
{
	if(m_pRenderer) m_pRenderer->Delete();
	if(m_pRenWin) m_pRenWin->Delete();
	if(m_pIren) m_pIren->Delete();

	m_pRenderer = vtkRenderer::New();
	m_pRenWin = vtkWin32OpenGLRenderWindow::New();
	HWND hwnd = GetSafeHwnd();
		m_pRenWin->AddRenderer(m_pRenderer);
		m_pRenWin->SetParentId(hwnd);
//		m_pRenWin->SwapBuffersOn();

	m_pIren = vtkRenderWindowInteractor::New();
	m_pIren->SetRenderWindow(m_pRenWin);

//	obtain run time type information (RTTI) about the calculatedCurrents object
	m_bIs3DCurrent = false;  // Currents_1D
	if(calculatedCurrents->IsKindOf(RUNTIME_CLASS(Currents3D)))
	{
		m_bIs3DCurrent = true; // Currents3D
		Currents3D* c3D;
		if(c3D = DYNAMIC_DOWNCAST(Currents3D,calculatedCurrents))
			m_nInitialFieldValueForRendering = c3D->m_nInitialFieldValueForRendering;
	}
	else
	if(calculatedCurrents->IsKindOf(RUNTIME_CLASS(Currents)))
	{
		m_bIs3DCurrent = false; // Currents1D
		Currents* c;
		if(c = DYNAMIC_DOWNCAST(Currents,calculatedCurrents))
			m_nInitialFieldValueForRendering = c->m_nInitialFieldValueForRendering;
	}
	else
		AfxMessageBox("Error in CCurrents3DView::PrepareForPlot");

	m_nNumberOfAtoms = ac->GetSize();  // number of atoms in a plot

// set the document title according to selected rendering options
	CString docTitle;
//	docTitle = GetDocument()->GetTitle();
// volume SCALAR rendering
	if(m_renderMethod == VolumeRayCastComposite || m_renderMethod == VolumeRayCastMIP ||
		m_renderMethod == VolumeRayCastIsosurfaceFunction)
	{
		fg->GetStructuredPoints()->GetPointData()->SetScalars(fg->GetDataScalars());
//		fg.GetDataScalars()->Delete();

// create a transfer function mapping scalar value to opacity

		m_poTFun = vtkPiecewiseFunction::New();
			m_poTFun->AddSegment(0,0.0,255,1.0);

// get the reference value (initial field value) from the Currents3D

// create color transfer functions

		m_pcTFun = vtkColorTransferFunction::New();
		if(!m_bIs3DCurrent) // for bond current produced magnetic field
		{
			if(this->m_renderRegion == ALL_FIELD)
			{
				docTitle += "Cu-Cu bond currents,resulting magnetic field,";

				m_pcTFun->AddBlueSegment(0,1.0,max(m_nInitialFieldValueForRendering-1,0)/2,1.0);
				m_pcTFun->AddBlueSegment(max(m_nInitialFieldValueForRendering-1,0)/2,1.0,
					max(m_nInitialFieldValueForRendering-1,0),0.0);
				m_pcTFun->AddBlueSegment(max(m_nInitialFieldValueForRendering-1,0),0.0,255,0.0);

				m_pcTFun->AddGreenSegment(max(m_nInitialFieldValueForRendering-1,0),0.0,
					m_nInitialFieldValueForRendering,1.0);
				m_pcTFun->AddGreenSegment(m_nInitialFieldValueForRendering,1.0,
					m_nInitialFieldValueForRendering+1,0.0);
				m_pcTFun->AddGreenSegment(m_nInitialFieldValueForRendering+1,0.0,255,0.0);

				m_pcTFun->AddRedSegment(0,0.0,m_nInitialFieldValueForRendering+1,0.0);
				m_pcTFun->AddRedSegment(m_nInitialFieldValueForRendering+1,0.0,
							(255+m_nInitialFieldValueForRendering+1)/2,1.0);
				m_pcTFun->AddRedSegment((255+m_nInitialFieldValueForRendering+1)/2,1.0,
							255,0.0);

			}
			else
			if(this->m_renderRegion == STRENGTHENED_FIELD)
			{
				docTitle += "Cu-Cu bond currents,strengthened magnetic field,";

				m_pcTFun->AddRedSegment(0,0.0,m_nInitialFieldValueForRendering,0.0);
				m_pcTFun->AddGreenSegment(0,0.0,m_nInitialFieldValueForRendering,0.0);
				m_pcTFun->AddBlueSegment(0,0.0,m_nInitialFieldValueForRendering,0.0);

				m_pcTFun->AddRedSegment(m_nInitialFieldValueForRendering+1,0.9,255,1.0);
				m_pcTFun->AddGreenSegment(m_nInitialFieldValueForRendering+1,0.0,255,0.0);
				m_pcTFun->AddBlueSegment(m_nInitialFieldValueForRendering+1,0.0,255,0.0);
			}
			else
			if(this->m_renderRegion == WEAKENED_FIELD)
			{
				docTitle += "Cu-Cu bond currents,weakened magnetic field,";

				m_pcTFun->AddBlueSegment(0,1.0,max(m_nInitialFieldValueForRendering-1,0),1.0);
				m_pcTFun->AddGreenSegment(0,0.0,m_nInitialFieldValueForRendering-1,0.0);
				m_pcTFun->AddRedSegment(0,0.0,m_nInitialFieldValueForRendering-1,0.0);

				m_pcTFun->AddRedSegment(m_nInitialFieldValueForRendering,0.0,255,0.0);
				m_pcTFun->AddGreenSegment(m_nInitialFieldValueForRendering,0.0,255,0.0);
				m_pcTFun->AddBlueSegment(m_nInitialFieldValueForRendering,0.0,255,0.0);

			}
			else
			if(this->m_renderRegion == APPLIED_FIELD)
			{
				docTitle += "Cu-Cu bond currents,applied magnetic field,";

				m_pcTFun->AddRedSegment(0,0.0,max(m_nInitialFieldValueForRendering-1,0),0.0);
				m_pcTFun->AddGreenSegment(0,0.0,max(m_nInitialFieldValueForRendering-1,0),0.0);
				m_pcTFun->AddBlueSegment(0,0.0,max(m_nInitialFieldValueForRendering-1,0),0.0);

				m_pcTFun->AddGreenSegment(m_nInitialFieldValueForRendering,1.0,
										m_nInitialFieldValueForRendering,1.0);

				m_pcTFun->AddRedSegment(m_nInitialFieldValueForRendering+1,0.0,255,0.0);
				m_pcTFun->AddGreenSegment(m_nInitialFieldValueForRendering+1,0.0,255,0.0);
				m_pcTFun->AddBlueSegment(m_nInitialFieldValueForRendering+1,0.0,255,0.0);
			}
		}
		else // for pure 3D currents
		{
// only for 3D currents to make them gray
			m_pcTFun->AddRedSegment(0,0.8,255,1.0);   
			m_pcTFun->AddGreenSegment(0,0.8,255,1.0);
			m_pcTFun->AddBlueSegment(0,0.8,255,1.0);

			docTitle += "3D electric currents,";
		}
// Create a property for the volume and set the transfer functions.
// Turn shading on and use trilinear interpolation
		m_pvolumeProperty = vtkVolumeProperty::New();
			m_pvolumeProperty->SetColor(m_pcTFun);
// use opacity only for 3D currents. For 1D it doesn't look good
			if(m_bIs3DCurrent)	m_pvolumeProperty->SetScalarOpacity(m_poTFun);
			m_pvolumeProperty->SetInterpolationTypeToLinear();
			m_pvolumeProperty->ShadeOn();

// Create a ray function - this is a compositing ray function
		if(m_renderMethod == VolumeRayCastComposite)
		{
			m_pcompositeFunction = vtkVolumeRayCastCompositeFunction::New();
			docTitle += "VolRayCastComposite rendering";

		}

		else
		if (m_renderMethod == VolumeRayCastMIP)
		{
			m_pMIPFunction = vtkVolumeRayCastMIPFunction::New();

			docTitle += "VolRayCastMIP rendering";
		}

		else
		if (m_renderMethod == VolumeRayCastIsosurfaceFunction)
		{
			m_pvolSurf = vtkVolumeRayCastIsosurfaceFunction::New();
// m_nIsosurfaceValue is read from the PropertyPageRendMethod
			m_pvolSurf->SetIsoValue(m_nIsosurfaceValue);

			CString temp;
			temp.Format("VolRayCastIsosurface rendering");
			docTitle += temp;
		}

// Create the volume mapper and set the ray function and scalar input
		m_pvolumeMapper = vtkVolumeRayCastMapper::New();
			m_pvolumeMapper->SetScalarInput(fg->GetStructuredPoints());
		if(m_renderMethod == VolumeRayCastComposite) 
			m_pvolumeMapper->SetVolumeRayCastFunction(m_pcompositeFunction);
		else
		if (m_renderMethod == VolumeRayCastMIP)
			m_pvolumeMapper->SetVolumeRayCastFunction(m_pMIPFunction);
		else
		if (m_renderMethod == VolumeRayCastIsosurfaceFunction)
			m_pvolumeMapper->SetVolumeRayCastFunction(m_pvolSurf);


// Create the volume and set the mapper and property
		m_pvolume = vtkVolume::New();
			m_pvolume->SetVolumeMapper(m_pvolumeMapper);
			m_pvolume->SetVolumeProperty(m_pvolumeProperty);

		m_pRenderer->AddVolume(m_pvolume);
	}
	else
// volume VECTOR rendering
		if(m_renderMethod == VolumeStreamLines ||
			m_renderMethod == VolumeStreamLinesWithTubes)
		{
			fg->GetStructuredPoints()->GetPointData()->SetVectors(fg->GetDataVectors());

			if(!m_bIs3DCurrent) // Current_1D
			{
				docTitle += "Cu-Cu bond currents,volume stream lines ";
				if(m_renderMethod != VolumeStreamLinesWithTubes)
					docTitle += "rendering";
// initial points for streamlines

			m_prakePoints = vtkPoints::New();
				m_prakePoints->SetNumberOfPoints(10);

				for(int i=0 ; i<9 ; i++)
				{
					m_prakePoints->InsertPoint(i,1.5*sin(2.*3.14159/9.*i),1.5*cos(2.*3.14159/9.*i),0.);
				}
				m_pugrid = vtkUnstructuredGrid::New();
					m_pugrid->Allocate(100);
					m_pugrid->SetPoints(m_prakePoints);
//					m_prakePoints->Delete();
				m_pstreamLine = vtkStreamLine::New();
					m_pstreamLine->SetInput(fg->GetStructuredPoints());
					m_pstreamLine->SetSource(m_pugrid);
					m_pstreamLine->SetIntegrationStepLength(0.1);
					m_pstreamLine->SetStepLength(0.05);
					m_pstreamLine->SetMaximumPropagationTime(1.);
					m_pstreamLine->SetIntegrationDirectionToForward();
					m_pstreamLine->VorticityOn();
					m_pstreamLine->Update();
				m_pstreamsMapper = vtkPolyDataMapper::New();
					m_pstreamsMapper->SetInput(m_pstreamLine->GetOutput());
			}
			else // Current_3D
			{
				docTitle += "3D electric currents,volume stream lines ";
				if(m_renderMethod != VolumeStreamLinesWithTubes)
					docTitle += "rendering";

//				vectorTopology = vtkVectorTopology::New();
//					vectorTopology->SetInput(fg.GetStructuredPoints());
//					vectorTopology->SetDistance(0.1);
//				maskPoints = vtkMaskPoints::New();
//					maskPoints->SetInput(vectorTopology->GetOutput());
//					maskPoints->SetOnRatio(2);
//					maskPoints->Print(cout);
				int numberOfRakePoints = 15*d->Get_cells_x()*d->Get_cells_y()*
					d->Get_cells_z();

				m_prakePoints = vtkPoints::New();
					m_prakePoints->SetNumberOfPoints(numberOfRakePoints);
// calculate the number of vertical lines for streamline initialization
// one line along z axis for each bond through it's center

				srand(m_nRandomGeneratorSeed); // for seeding the random generator

				for(int i=0 ; i<numberOfRakePoints ; i++)
				{
					double xc = ac->GetXMin() + rand()*(ac->GetXMax()-ac->GetXMin())/32767.;
					double yc = ac->GetYMin() + rand()*(ac->GetYMax()-ac->GetYMin())/32767.;
					double zc = ac->GetZMin() + rand()*(ac->GetZMax()-ac->GetZMin())/32767.;
					m_prakePoints->InsertPoint(i,xc,yc,zc);
				}

				m_pugrid = vtkUnstructuredGrid::New();
					m_pugrid->Allocate(numberOfRakePoints);
					m_pugrid->SetPoints(m_prakePoints);
//					m_prakePoints->Delete();

				m_pstreamLine = vtkStreamLine::New();
					m_pstreamLine->SetInput(fg->GetStructuredPoints());
					m_pstreamLine->SetSource(m_pugrid);
					m_pstreamLine->SetIntegrationStepLength(0.1);
					m_pstreamLine->SetStepLength(0.05);
					m_pstreamLine->SetMaximumPropagationTime(2.0);
					m_pstreamLine->SetIntegrationDirectionToForward();
					m_pstreamLine->VorticityOn();
					m_pstreamLine->SpeedScalarsOn();
					m_pstreamLine->Update();
//					m_pstreamLine->Print(cout);

				m_pstreamsMapper = vtkPolyDataMapper::New();
					m_pstreamsMapper->SetInput(m_pstreamLine->GetOutput());

			}


			m_plines = vtkActor::New();
				m_plines->SetMapper(m_pstreamsMapper);

			m_pRenderer->AddActor(m_plines);

			if(m_renderMethod == VolumeStreamLinesWithTubes)
			{
				docTitle += "with tubes rendering";
				m_pstreamTube = vtkTubeFilter::New();
					m_pstreamTube->SetInput(m_pstreamLine->GetOutput());
					m_pstreamTube->SetRadius(0.1);
					m_pstreamTube->SetNumberOfSides(6);
					m_pstreamTube->SetVaryRadiusToVaryRadiusByScalar();
				m_ptubeMapper = vtkPolyDataMapper::New();
					m_ptubeMapper->SetInput(m_pstreamTube->GetOutput());
					m_ptubeMapper->SetScalarRange(0,255);
					m_ptubeMapper->SetColorModeToMapScalars(); 
					m_ptubeMapper->ScalarVisibilityOn();
				m_ptubes = vtkActor::New();
					m_ptubes->SetMapper(m_ptubeMapper);
				
				m_pRenderer->AddActor(m_ptubes);
			}
		}
	else
		if(m_renderMethod == HedgeHog)
		{
			if(!m_bIs3DCurrent) // Current_1D
			{
				docTitle += "Cu-Cu bond currents,all magnetic field HedgeHog rendering";
			}
			else
			{
				docTitle += "3D electric currents HedgeHog rendering";
			}

			fg->GetStructuredPoints()->GetPointData()->SetVectors(fg->GetDataVectors());
			m_phedgeHog = vtkHedgeHog::New();
				m_phedgeHog->SetInput(fg->GetStructuredPoints());
				m_phedgeHog->SetScaleFactor(1.e-1);
			m_phhMapper = vtkPolyDataMapper::New();
				m_phhMapper->SetInput(m_phedgeHog->GetOutput());
			m_phhActor = vtkActor::New();
				m_phhActor->SetMapper(m_phhMapper);

			m_pRenderer->AddActor(m_phhActor);
		}

// model atoms as spheres
		MakeSpheres(d,ac);
// model current strength with cylinder diameter and color
		MakeCylinders(ac,calculatedCurrents);
// for speeding up rendering, slowing down rotations/zooms
		m_pRenderer->BackingStoreOn();
// if I put the next statement in the OnDraw() handler, it doesn't work !!!
//		m_pRenWin->Render();
// set the document title
		GetDocument()->SetTitle(docTitle);
}

//////////////////////////////////////////////////////////////////////
// destruction
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////

void CCurrents3DView::MakeSpheres(Distances* d, AtomCoordinates* ac)
{
	for( int i=0 ; i<ATOM_TYPES ; i++)
	{
		m_ps[i] = vtkSphereSource::New();
			m_ps[i]->SetThetaResolution(10);
			m_ps[i]->SetPhiResolution(10);
			m_ps[i]->SetRadius(d->Get_Radius(i));  // Atom sphere radius
			m_ps[i]->SetCenter(0.,0.,0.);
		m_ppdmSpheres[i] = vtkPolyDataMapper::New();
			m_ppdmSpheres[i]->SetInput(m_ps[i]->GetOutput());
	}

// add atoms

	for (i=0; i<m_nNumberOfAtoms ; i++)
	{
		m_patomActor[i] = vtkActor::New();
		m_patomActor[i]->SetMapper(m_ppdmSpheres[ac->GetType(i)]);
		m_patomActor[i]->SetPosition(ac->GetX(i),ac->GetY(i),ac->GetZ(i));
		m_patomActor[i]->GetProperty()->SetColor(d->Get_ColorR(ac->GetType(i)),
											  d->Get_ColorG(ac->GetType(i)),
											  d->Get_ColorB(ac->GetType(i))
											 );
		m_pRenderer->AddActor(m_patomActor[i]);
	}
}
//////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////
void CCurrents3DView::MakeCylinders(AtomCoordinates* ac, CurrentsBase* curr)
{
		const double pi = 3.1415926;
		const double RadToDeg = 180.0/pi;
		double theta;  // rotation angle for alligning cylinder with atoms

		Currents *c; // references to current objects
		Currents3D *c3D;

// dynamic_cast the object to it's type
		if(m_bIs3DCurrent)
			c3D = dynamic_cast<Currents3D*>(curr);
		else
			c = dynamic_cast<Currents*>(curr);
// find number of bonds
		if(m_bIs3DCurrent)
			m_nNumberOfBonds = c3D->GetNumberOfBonds();
		else
			m_nNumberOfBonds = c->GetNumberOfBonds();

	for(int i=0;i<m_nNumberOfBonds;i++)
	{
		m_pcyl[i] = vtkCylinderSource::New();
			m_pcyl[i]->SetResolution(8);
			
		if(!m_bIs3DCurrent) // find the maximum bond current and scale it's diameter to 0.2
		{
			double cr = c->GetBondCurrent(i)*0.2/c->GetMaxCurrent();
			m_pcyl[i]->SetRadius(fabs(cr));
		}
		else
			m_pcyl[i]->SetRadius(0.2);

			double ax = ac->GetX(curr->GetBondAtom2(i))-ac->GetX(curr->GetBondAtom1(i));
			double ay = ac->GetY(curr->GetBondAtom2(i))-ac->GetY(curr->GetBondAtom1(i));
			double az = ac->GetZ(curr->GetBondAtom2(i))-ac->GetZ(curr->GetBondAtom1(i));
			double c0 = (ac->GetX(curr->GetBondAtom2(i))+ac->GetX(curr->GetBondAtom1(i)))/2.;
			double c1 = (ac->GetY(curr->GetBondAtom2(i))+ac->GetY(curr->GetBondAtom1(i)))/2.;
			double c2 = (ac->GetZ(curr->GetBondAtom2(i))+ac->GetZ(curr->GetBondAtom1(i)))/2.;

			double length = sqrt(ax*ax+ay*ay+az*az);
			m_pcyl[i]->SetHeight(length);

		m_pcolorIt[i] = vtkElevationFilter::New();
			m_pcolorIt[i]->SetInput(m_pcyl[i]->GetOutput());
			m_pcolorIt[i]->SetLowPoint(0,-length/2,0);
			m_pcolorIt[i]->SetHighPoint(0,length/2,0);
		m_plut[i] = vtkLookupTable::New();

			if(!m_bIs3DCurrent)
			{
				if(c->GetBondCurrentDirection(i)) m_plut[i]->SetSaturationRange(0,1);
				else m_plut[i]->SetSaturationRange(1,0);
				m_plut[i]->SetHueRange(0,0);  // red coloring
				m_plut[i]->SetValueRange(1,1);
			}
			else // for 3D currents
			{
				m_plut[i]->SetHueRange(0.8,0.8);
				m_plut[i]->SetSaturationRange(0,0); // gray
				m_plut[i]->SetValueRange(0.7,0.7);
			}

		m_ppdmCyls[i] = vtkDataSetMapper::New();
			m_ppdmCyls[i]->SetInput(m_pcolorIt[i]->GetOutput());
			m_ppdmCyls[i]->SetLookupTable(m_plut[i]);
	
		m_pcylActor[i] = vtkActor::New();
			m_pcylActor[i]->SetMapper(m_ppdmCyls[i]);

//  rotate cylinder to allign it with bond atoms

		if(fabs(az)<1.e-3 && fabs(ax)<1.e-3)
		{
			m_pcylActor[i]->SetPosition(c0,c1,c2);
		}
		else if(fabs(az)<1.e-3)
		{
			theta = acos(ay/length)*RadToDeg; 
			m_pcylActor[i]->RotateWXYZ(-theta,0.,0.,ax);
			m_pcylActor[i]->SetPosition(c0,c1,c2);
		}
		else if(fabs(ax)<1.e-3)
		{
			theta = acos(ay/length)*RadToDeg; 
			m_pcylActor[i]->RotateWXYZ(-theta,-az,0.,0.);
			m_pcylActor[i]->SetPosition(c0,c1,c2);
		}
		else
		{
			theta = acos(ay/length)*RadToDeg; 
			m_pcylActor[i]->RotateWXYZ(-theta,-az,0.,ax);
			m_pcylActor[i]->SetPosition(c0,c1,c2);
		}
		m_pRenderer->AddActor(m_pcylActor[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////
//

void CCurrents3DView::OnToolsImagesetup() 
{
//	CPropertySheet dlgPropertySheet(AFX_IDS_APP_TITLE);
	CPropertySheet dlgPropertySheet("Image rendering options");
	PropertyPageAtoms atomsPage;
	PropertyPageObjToRender objToRenderPage;
	PropertyPageRendMethod methodPage;
	PropertyPageRegions regionsPage;

	CCurrents3DDoc* pDoc = GetDocument();
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CCurrents3DDoc)));
	CChild3DFrame* pFrame = (CChild3DFrame*)GetParentFrame();
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CChild3DFrame)));
	CMainFrame* pF = (CMainFrame*) pFrame->GetParentFrame();
	ASSERT(pF->IsKindOf(RUNTIME_CLASS(CMainFrame)));

	dlgPropertySheet.AddPage(&methodPage);
	dlgPropertySheet.AddPage(&atomsPage);
	dlgPropertySheet.AddPage(&objToRenderPage);
	dlgPropertySheet.AddPage(&regionsPage);
	if(m_bIs3DCurrent)
	{
		objToRenderPage.m_pp = &regionsPage;
		objToRenderPage.is_m_pp_visible = false;
		dlgPropertySheet.RemovePage(&regionsPage);
	}

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

	atomsPage.m_Cu2_1 = pDoc->m_atomLayerPlotFlag[0] = 1;
	atomsPage.m_O2_1 = pDoc->m_atomLayerPlotFlag[1];
	atomsPage.m_Cu2_2 = pDoc->m_atomLayerPlotFlag[2] = 1;
	atomsPage.m_O2_2 = pDoc->m_atomLayerPlotFlag[3];
	atomsPage.m_Y = pDoc->m_atomLayerPlotFlag[4];
	atomsPage.m_Ba = pDoc->m_atomLayerPlotFlag[5];
	atomsPage.m_O4 = pDoc->m_atomLayerPlotFlag[6];
	atomsPage.m_O1 = pDoc->m_atomLayerPlotFlag[7];
	atomsPage.m_Cu1 = pDoc->m_atomLayerPlotFlag[8];

	objToRenderPage.m_ObjToRender = pDoc->m_ObjectToRender;
	methodPage.m_renderMethod = m_renderMethod;
	methodPage.m_IsosurfValue = m_nIsosurfaceValue;
// Used for the PropertyPageRendMethod page to show possible isosurface values
	methodPage.m_InitialMagnFieldValue = m_nInitialFieldValueForRendering;

	methodPage.m_RenderRegion = m_renderRegion;
	regionsPage.m_RenderRegion = m_renderRegion;

// disable the Cu2 layer buttons. At present BOTH layers must be included in the calculation

	if(dlgPropertySheet.DoModal() == IDOK)
	{

		CWaitCursor wait;
// set the atom plot flags
		pDoc->m_atomLayerPlotFlag[0] = (atomsPage.m_Cu2_1) ? 1 : 0;
		pDoc->m_atomLayerPlotFlag[1] = (atomsPage.m_O2_1) ? 1 : 0;
		pDoc->m_atomLayerPlotFlag[2] = (atomsPage.m_Cu2_2) ?  1 : 0;
		pDoc->m_atomLayerPlotFlag[3] = (atomsPage.m_O2_2) ? 1 : 0;
		pDoc->m_atomLayerPlotFlag[4] = (atomsPage.m_Y) ? 1 : 0;
		pDoc->m_atomLayerPlotFlag[5] = (atomsPage.m_Ba) ? 1 : 0;
		pDoc->m_atomLayerPlotFlag[6] = (atomsPage.m_O4) ? 1 : 0;
		pDoc->m_atomLayerPlotFlag[7] = (atomsPage.m_O1) ? 1 : 0;
		pDoc->m_atomLayerPlotFlag[8] = (atomsPage.m_Cu1) ? 1 : 0;

		pDoc->m_ObjectToRender = objToRenderPage.m_ObjToRender;
		m_renderMethod = methodPage.m_renderMethod;
		m_nIsosurfaceValue = methodPage.m_IsosurfValue;
		m_renderRegion = regionsPage.m_RenderRegion;

// enable the scf checkbox for Currents_1D and disable for Currents_3D
		CStatic* stat = (CStatic*)pF->m_wndDlgBar3D.GetDlgItem(IDC_STATIC3);
		CButton* btn = (CButton*)pF->m_wndDlgBar3D.GetDlgItem(IDC_CHECK_ISSCF3);

		if(objToRenderPage.m_ObjToRender == Currents_3D)
		{
			stat->EnableWindow(FALSE);
			btn->EnableWindow(FALSE);
		}
		else
		{
			stat->EnableWindow(TRUE);
			btn->EnableWindow(TRUE);
		}
		stat->UpdateWindow();
// perform the calculation and rendering
		pDoc->SetModifiedFlag();

		CString string;
		CEdit* pEd;

// do the following because rebar is on the main frame

		pEd = (CEdit*)pF->m_wndDlgBar3D.GetDlgItem(IDC_EDIT_NMBCUATOMS3);
		pEd->GetWindowText(string);
		int number = atoi(string); // number of atoms along side
		if(number%2 != 0) number++;	// to make NumberOfAtoms even. Otherwise calculation crash.
		char astring[20];
		pEd->SetWindowText(itoa(number,astring,10));
		pEd->UpdateWindow();
		pDoc->SetNumberOfAtomsAlongSide(number);

// limit the number of electrons to be removed / added according to the number of atoms
// According to Larsson's model is one electron per Cu atom
		CSpinButtonCtrl* spin;
		spin = (CSpinButtonCtrl*)pF->m_wndDlgBar3D.GetDlgItem(IDC_SPIN_ELECTRONS_REMOVED3);
// feature of the spin control button makes +-1 as necessity
		spin->SetRange(-2*number*number,2*number*number); // because of 2 CuO layers

		pEd = (CEdit*)pF->m_wndDlgBar3D.GetDlgItem(IDC_EDIT_EXTMAGNFIELD3);
		pEd->GetWindowText(string);
		pDoc->SetExtMagnField(atof(string));

		pEd = (CEdit*)pF->m_wndDlgBar3D.GetDlgItem(IDC_EDIT_ELECTRONS_REMOVED3);
		pEd->GetWindowText(string);
		int er = atoi(string);
		pDoc->SetElectronsRemoved(er);

		pEd = (CEdit*)pF->m_wndDlgBar3D.GetDlgItem(IDC_EDIT_UNITCELLSC);
		pEd->GetWindowText(string);
		pDoc->SetUnitCellsAlongC(atof(string));

		btn = (CButton*)pF->m_wndDlgBar3D.GetDlgItem(IDC_CHECK_ISSCF3);
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

		pF->m_wndStatusBar.SetWindowText("Calculation in progress. Please wait...");


		pDoc->OnNewDocument();
		if(!pDoc->Calculate()) // not achieved scf
		{
			CFrameWnd* fr = this->GetParentFrame();
			ASSERT(fr->IsKindOf(RUNTIME_CLASS(CChild3DFrame)));
			fr->DestroyWindow();
			return;
		}
		pDoc->InitializeCurrents3DView();
	}

	pDoc->UpdateAllViews(NULL);
}

///////////////////////////////////////////////////////////////////////////
//
BOOL CCurrents3DView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CScrollView::OnEraseBkgnd(pDC);
}

////////////////////////////////////////////////////////////////////////////
//		File->Save handler (saves the image in the bmp format)

void CCurrents3DView::OnFileSave() 
{
	CString sFileName;

	static TCHAR szFilter[] = _T("Bitmap Files(*.bmp) |*.bmp|All Files (*.*)|*.*||");
	
	CFileDialog dlg(TRUE,_T("*.bmp"),NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST |
						OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT, szFilter,NULL);

	if( dlg.DoModal() == IDOK)
	{
		sFileName = dlg.GetPathName();

// do the rendering to the memory, otherwise the dialog box which was over the image,
// will also be copied to the bitmap

		int* size = m_pRenWin->GetSize();
		m_pRenWin->SetupMemoryRendering(size[0],size[1],GetDC()->GetSafeHdc());
		m_pRenWin->Render();

		vtkWindowToImageFilter* renSrc = vtkWindowToImageFilter::New();
			renSrc->SetInput(m_pRenderer->GetVTKWindow());

		vtkBMPWriter* writer = vtkBMPWriter::New();
			writer->SetInput(renSrc->GetOutput());
			writer->SetFileName(sFileName.GetBuffer(10));
			writer->Write();

		renSrc->Delete();
		writer->Delete();

		m_pRenWin->ResumeScreenRendering();
	}
}

//////////////////////////////////////////////////////////////////
//		ON_UPDATE_COMMAND_UI  handlers

void CCurrents3DView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	CCurrents3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->GetCalculatedOK())	// document has data for plotting
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}
