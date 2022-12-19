// Currents2DDoc.h : interface of the CCurrents2DDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTS2DDOC_H__5B750F32_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
#define AFX_CURRENTS2DDOC_H__5B750F32_85F2_11D3_B1D9_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ATOM_LAYERS 1

class AtomCoordinates;
class Distances;
class AtomLayers;
class Currents;
class Cu2Layer;

class CCurrents2DDoc : public CDocument
{
protected: // create from serialization only
	CCurrents2DDoc();
	DECLARE_DYNCREATE(CCurrents2DDoc)

// Attributes
private:

	int m_nAtoms;	// number of atoms along cluster side
	double m_nCuCuDistance;	// in angstroms
	double m_nMagneticField;	// in gauss
	double m_nTau;
	double m_nEo;
	double m_nEm;
	bool m_bDoWithoutSelfConsistency;
	bool m_bCalculatedOK;
	int m_nElectronsRemoved; // +1 for removed, -1 for added
	int m_nIterations; // iterations performed in scf current calculation. From m_pCurr.

	void InitializeCurrents2DDoc();
//	void ClearCurrents2DView(); // deallocates view heap memory
	void ClearViews(); // clears all views at File->New command

	double m_nIterationRms; // holds the difference in scf currents for printing to a view

public:

	AtomCoordinates *m_pAcoord;
	Distances *m_pDist;
	AtomLayers *m_pAl[ATOM_LAYERS];  // pointer to different layers
	Currents *m_pCurr;
	Cu2Layer *m_pCu2_lower;
	
	int Calculate(); // calculates the 2D currents
	bool GetCalculatedOK() {return m_bCalculatedOK;}

	int GetNumberOfAtomsAlongSide() {return m_nAtoms;}
	void SetNumberOfAtomsAlongSide(int number) {m_nAtoms = number;}

	double GetExtMagnField() {return m_nMagneticField;}
	void SetExtMagnField(double Field) {m_nMagneticField = Field;}

	double GetCuCuDistance() {return m_nCuCuDistance;}
	void SetCuCuDistance(double Distance) {m_nCuCuDistance = Distance;}

	int GetElectronsRemoved() {return m_nElectronsRemoved;}
	void SetElectronsRemoved(int electrons) {m_nElectronsRemoved = electrons;}

	void InitializeCurrents2DView(); // allocates memory in heap
	void SetDoWithoutSelfConsistency(bool set) {m_bDoWithoutSelfConsistency = set;}
	bool GetDoWithoutSelfConsistency() {return m_bDoWithoutSelfConsistency;}

	int GetIterations() {return m_nIterations;}
	void SetIterations(int iter) {m_nIterations = iter;}

	void SetIterationRms(double rms); // view will retrieve this for displaying



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrents2DDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurrents2DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurrents2DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRENTS2DDOC_H__5B750F32_85F2_11D3_B1D9_005004567AD4__INCLUDED_)
