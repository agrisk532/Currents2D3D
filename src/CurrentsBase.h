//////////////////////////////////////////////////////////////////////
// 
// CurrentsBase.h: interface for the CurrentsBase class.
//
// Base class for current(1D,3D) calculations
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTSBASE_H__143536A3_3E7E_11D3_B193_006008158370__INCLUDED_)
#define AFX_CURRENTSBASE_H__143536A3_3E7E_11D3_B193_006008158370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <stdio.h>
//#include "FieldGrid.h"
#include "AtomLayers.h"
#include "Distances.h"
#include "AtomCoordinates.h"
#include "Bond.h"
#include "f2c.h"
#include "math.h"
#include "Constants.h"

#include <vector>

using namespace std;

class CurrentsBase : public CObject
{
	DECLARE_DYNAMIC(CurrentsBase);

protected:

	Distances *d; // pointer to Distances object
	AtomCoordinates* acoord; // pointer to calculated Atomic coordinates object
	double initialMagneticField; // constant magnetic field B along the Z axis 
	Bond* m_pBonds; // dynamic array holding pointers to all allocated Bond objects

	long NumberOfAtoms;  // total number of atoms in the calculation
	int NumberOfLayers; // number of layers involved in calculation. For YBaCuO max is 9
	int NumberOfBonds;  // number of bonds with calculated currents
	vector<int> StartOfLayer; // vector holding locations of different layers in coordinate_x(y,z)
	vector<int> SizeOfLayer;  // vector holding the sizes (number of atoms) of corresponding layers
	vector<Bond*> bonds; // vector holding pointers to Bond objects
	char *occupationMatrix;
	int m_nElectronsRemoved; // doping parameter

	int FindLayerStart(AtomLayers*);
	int FindLayerSize(AtomLayers*);
	void AddBonds(int,int,double,int);
	int GetAtomLayerID(int atomNumber); // for distinguishing the atoms in different layers
	int GetStartIndex(int atomLayerID); // returns the number of the first atom in a layer
	void VectorProduct(double *v1,double *v2,double *v_res);
	double ScalarProduct(double *v1,double *v2);
	double VectorLength(double *v);
	double CosOfAngleBetweenVectors(double *v1,double *v2);
	void FormHamiltonianMatrix(doublecomplex *ap,double tau,double Eo,double Em);

public:

	CurrentsBase(double imf) {NumberOfLayers = 0; NumberOfBonds = 0; NumberOfAtoms = 0;
								initialMagneticField = imf;}
	virtual ~CurrentsBase();

	void SetCoordinates(AtomCoordinates *ac) {acoord = ac;} // set coordinate object for calculations
	void AddLayer(AtomLayers*);
	void SetDistances(Distances *dist) {d = dist;}
	int GetNumberOfBonds() {return NumberOfBonds;}
	int GetBondAtom1(int bond) {return bonds[bond]->GetAtom1();} // add checking for dimensions
	int GetBondAtom2(int bond) {return bonds[bond]->GetAtom2();} // add checking for dimensions
	int GetAcIndex(int atomNumberInCurrents); // returns the number of atom (in atomcoordinates) for the corresponding atom (in currents)
	virtual bool Is3DCurrent() = 0; // just to make class polymorphic
	void SetElectronsRemoved(int electrons) {m_nElectronsRemoved = electrons;}
	int GetElectronsRemoved() {return m_nElectronsRemoved;}
};

#endif // !defined(AFX_CURRENTSBASE_H__143536A3_3E7E_11D3_B193_006008158370__INCLUDED_)
