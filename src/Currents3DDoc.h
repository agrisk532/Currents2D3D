// Currents3DDoc.h : interface of the CCurrents3DDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTS3DDOC_H__067F8F9D_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
#define AFX_CURRENTS3DDOC_H__067F8F9D_A0BC_11D3_B1F0_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AtomCoordinates;
class Distances;
class AtomLayers;
class Currents;
class Currents3D;
class PlotIt;
class FieldGrid;
class CurrentsBase;
class CTextView;


#define ATOM_LAYERS_3D 9

class CCurrents3DDoc : public CDocument
{
private:
	int m_nAtoms;	// number of atoms along cluster side
	double m_nMagneticField;	// in gauss
	double m_nTau;
	double m_nEo;
	double m_nEm;
	bool m_bDoWithoutSelfConsistency;
	bool m_bCalculatedOK;
	int m_nElectronsRemoved; // +1 for removed, -1 for added
	int m_nIterations; // iterations performed in scf current calculation. From m_pCurr.
	int m_nUnitCellsAlongC;

	void InitializeCurrents3DDoc();

	void ClearCurrents3DView(); // deallocates view heap memory
	void ClearViews(); // clears all views at File->New command

	double m_nIterationRms; // holds the difference in scf currents for printing to a view

protected: // create from serialization only
	CCurrents3DDoc();
	DECLARE_DYNCREATE(CCurrents3DDoc)

// Attributes
public:
	int m_ObjectToRender;
// Operations
public:

	AtomCoordinates *m_pAcoord;
	Distances *m_pDist;
	AtomLayers *m_pAl[ATOM_LAYERS_3D];  // pointer to different layers
	Currents *m_pCurr;
	Currents3D* m_pCurr3D;
	PlotIt* m_pPlotter;
	FieldGrid* m_pGrid;
	CurrentsBase* m_pCurrBase; // used in view->Plot()

// set 1 to plot the corresponding type layer, 0 if not	
	int m_atomLayerPlotFlag[ATOM_LAYERS_3D];

	CurrentsBase* Calculate(); // calculates the 3D currents
	bool GetCalculatedOK() {return m_bCalculatedOK;}

	int GetNumberOfAtomsAlongSide() {return m_nAtoms;}
	void SetNumberOfAtomsAlongSide(int number) {m_nAtoms = number;}

	double GetExtMagnField() {return m_nMagneticField;}
	void SetExtMagnField(double Field) {m_nMagneticField = Field;}

	int GetElectronsRemoved() {return m_nElectronsRemoved;}
	void SetElectronsRemoved(int electrons) {m_nElectronsRemoved = electrons;}

	int GetUnitCellsAlongC() {return m_nUnitCellsAlongC;}
	void SetUnitCellsAlongC(int cells) {m_nUnitCellsAlongC = cells;}

	void InitializeCurrents3DView(); // allocates memory in heap
	void SetDoWithoutSelfConsistency(bool set) {m_bDoWithoutSelfConsistency = set;}
	bool GetDoWithoutSelfConsistency() {return m_bDoWithoutSelfConsistency;}

	int GetIterations() {return m_nIterations;}
	void SetIterations(int iter) {m_nIterations = iter;}

	void SetIterationRms(double rms); // view will retrieve this for displaying

	void Plot(HWND hwnd,int objectToRender,int RenderingMethod,int RandomGeneratorSeed);
//enum RenderingMethod {VolumeRayCastComposite, VolumeRayCastMIP,
//		VolumeRayCastIsosurfaceFunction,VolumeStreamLines,VolumeStreamLinesWithTubes,
//		HedgeHog};


	CTextView* GetTextView();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrents3DDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurrents3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurrents3DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRENTS3DDOC_H__067F8F9D_A0BC_11D3_B1F0_005004567AD4__INCLUDED_)
