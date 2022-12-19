//////////////////////////////////////////////////////////////////////
//
// Currents.h: interface for the Currents class.
// for calculation of the 1D currents and magnetic field
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTS_H__1C49E494_1FD1_11D3_B16E_006008158370__INCLUDED_)
#define AFX_CURRENTS_H__1C49E494_1FD1_11D3_B16E_006008158370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldGrid.h"
#include "AtomLayers.h"
#include "Distances.h"
#include "AtomCoordinates.h"
#include "Bond.h"
#include "math.h"
#include "f2c.h"
#include "Constants.h"
#include "CurrentsBase.h"
#include "Currents2DDoc.h"
#include "Textvw.h"

class Currents : public CurrentsBase
{
	DECLARE_DYNAMIC(Currents);

private:

	CDocument* pDoc; // general. Later in source it will be casted to the appropriate type
	void CalculateBondCurrents(doublecomplex *z);
	bool doWithoutSelfConsistency; // indicates whether to do selfconsistent or single calculation
	double deltaCurrentLimit; // max difference in current between 2 iterations
	bool ContinueIterations(); // checks the selfconsistency convergence
	void MagneticFieldInGridPoint(long iz,long iy,long ix,FieldGrid *fg,
								float magneticField[3]);
	void CalculateMagneticFieldOnAtoms();
	double CalcDistPointToBond(int atom,int bond); // for SCF current calculations
	double CalcDistPointToBond(double xc,double yc,double zc,int bond);
	int m_nNumberOfIterations; // number of iterations performed in scf

public:

	Currents(bool sc,double imf) : CurrentsBase(imf) {doWithoutSelfConsistency = sc;
	m_nNumberOfIterations = 0;}
	virtual ~Currents() {};
	static Currents *New(bool sc = false,double imf = 0.1) {return new Currents(sc,imf);}
	int CalculateCurrentsInBonds(const double,const double,const double,const bool); // the main calculation function
	void SetGaugeOrigin();  // calculates the gauge origin for magnetic field
	double GetBondCurrent(int bond) {return bonds[bond]->GetCurrentMagnitude();}
	bool GetBondCurrentDirection(int bond) {return bonds[bond]->GetCurrentDirection();}
	double GetMaxCurrent(); // returns the max current in bonds (for PlotIt)
	void CalculateMagneticFieldOnGrid(FieldGrid *fg);
	bool Is3DCurrent() {return false;} // just to make base class polymorphic
	int GetNumberOfIterations() {return m_nNumberOfIterations;}

	void SetDocument(CDocument* doc) {pDoc = doc;} // set pointer to the document object
	CTextView* GetTextPane();

// reference value for rendering of the field
// 0-255, calculated in the 'Currents'
	int m_nInitialFieldValueForRendering;
};

#endif // !defined(AFX_CURRENTS_H__1C49E494_1FD1_11D3_B16E_006008158370__INCLUDED_)
