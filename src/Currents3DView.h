// Currents3DView.h : interface of the CCurrents3DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTS3DVIEW_H__067F8F9F_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
#define AFX_CURRENTS3DVIEW_H__067F8F9F_A0BC_11D3_B1F0_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ATOM_TYPES 9

class vtkRenderer;
class vtkWin32OpenGLRenderWindow;
class vtkPiecewiseFunction;
class vtkColorTransferFunction;
class vtkVolumeProperty;
class vtkVolumeRayCastCompositeFunction;
class vtkVolumeRayCastMIPFunction;
class vtkVolumeRayCastIsosurfaceFunction;
class vtkVolumeRayCastMapper;
class vtkVolume;
class vtkPoints;
class vtkUnstructuredGrid;
class vtkStreamLine;
class vtkPolyDataMapper;
class vtkActor;
class vtkHedgeHog;
class vtkSphereSource;
class vtkCylinderSource;
class vtkElevationFilter;
class vtkLookupTable;
class vtkDataSetMapper;
class vtkTubeFilter;
class vtkRenderWindowInteractor;

class CCurrents3DView : public CScrollView
{
protected: // create from serialization only
	CCurrents3DView();
	DECLARE_DYNCREATE(CCurrents3DView)

// Attributes
public:
	CCurrents3DDoc* GetDocument();
	int m_objToRender;
	int m_renderMethod;
	int m_renderRegion; // what to render - strengthened, weakened or all fields
	int m_nRandomGeneratorSeed; // for streamlines
	bool m_bIs3DCurrent;
	int m_nNumberOfAtoms; // number of atoms in plot
	int m_nNumberOfBonds;
	float m_nIsosurfaceValue;
// used to pass to the property page for isosurface value ranges
	int m_nInitialFieldValueForRendering; 

	vtkRenderer* m_pRenderer;
	vtkWin32OpenGLRenderWindow* m_pRenWin;
	vtkPiecewiseFunction* m_poTFun;
	vtkColorTransferFunction* m_pcTFun;
	vtkVolumeProperty* m_pvolumeProperty;
	vtkVolumeRayCastCompositeFunction* m_pcompositeFunction;
	vtkVolumeRayCastMIPFunction* m_pMIPFunction;
	vtkVolumeRayCastIsosurfaceFunction* m_pvolSurf;
	vtkVolumeRayCastMapper* m_pvolumeMapper;
	vtkVolume* m_pvolume;
	vtkPoints* m_prakePoints;
	vtkUnstructuredGrid* m_pugrid;
	vtkStreamLine* m_pstreamLine;
	vtkPolyDataMapper* m_pstreamsMapper;
	vtkActor* m_plines;
	vtkTubeFilter* m_pstreamTube;
	vtkPolyDataMapper* m_ptubeMapper;
	vtkActor* m_ptubes;
	vtkHedgeHog* m_phedgeHog;
	vtkPolyDataMapper* m_phhMapper;
	vtkActor* m_phhActor;
	vtkSphereSource* m_ps[ATOM_TYPES];
	vtkPolyDataMapper* m_ppdmSpheres[ATOM_TYPES];
	vtkActor* m_patomActor[1000];
	vtkCylinderSource* m_pcyl[4000];
	vtkElevationFilter* m_pcolorIt[1000];
	vtkLookupTable* m_plut[1000];
	vtkDataSetMapper* m_ppdmCyls[4000];
	vtkActor* m_pcylActor[4000];
	vtkRenderWindowInteractor* m_pIren;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrents3DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurrents3DView();
	void WriteStatusBarMessage();
	void PrepareForPlot(AtomCoordinates*,FieldGrid*,Distances*,CurrentsBase*);
	void MakeCylinders(AtomCoordinates*,CurrentsBase*);
	void MakeSpheres(Distances*,AtomCoordinates*);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_bDataInClipboard; // indicates whether there is data in clipboard

// Generated message map functions
protected:
	//{{AFX_MSG(CCurrents3DView)
	afx_msg void OnEditCopy();
	afx_msg void OnToolsImagesetup();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Currents2D3DView.cpp
inline CCurrents3DDoc* CCurrents3DView::GetDocument()
   { return (CCurrents3DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRENTS3DVIEW_H__067F8F9F_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
