// Bond.h: interface for the Bond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOND_H__CD3E4C17_1E51_11D3_B16C_006008158370__INCLUDED_)
#define AFX_BOND_H__CD3E4C17_1E51_11D3_B16C_006008158370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomCoordinates.h"
#include "math.h"

class Bond  
{

private:

//	static AtomCoordinates *acoord;
	AtomCoordinates* acoord;
	int Atom1; // atom 1 in the bond (numbering the same as in the AtomCoordinates class)
	int Atom2; // atom 2 in the bond (numbering the same as in the AtomCoordinates class)
// current is assumed positive when going from atom with smaller number
// to atom with larger number (positive for current from atom1 to atom2)
	bool currentDirection; // true - if from 1 to 2; false - if from 2 to 1
	double currentMagnitude;
	
	bool currentDirection_previous;  // contains the current magnitude and direction of the...
	double currentMagnitude_previous; //  ...previous iteration during the SCF steps

	double DifferenceInCurrents; // difference in currents in two subsequent iterations

	int m_nExcludedLayerSize; // contains the size of the plot only Acoord layer (O2_lower)
// which is not included in the calculation. This is necessary to match the numbering of
// atoms in the acoord object and complex z[] matrix

public:

	Bond(int at1,int at2,AtomCoordinates* ac, int els);
	static Bond *New(int at1,int at2, AtomCoordinates* ac, int ExcludedLayerSize)
	{return new Bond(at1,at2,ac, ExcludedLayerSize);}
	virtual ~Bond() {};
	double GetCurrentMagnitude() {return currentMagnitude;}
	void SetCurrentMagnitude(double val) {currentMagnitude = val;}
	bool GetCurrentDirection() {return currentDirection;}
	void SetCurrentDirection(bool dir) {currentDirection = dir;}
	int GetAtom1() {return Atom1;}
	int GetAtom2() {return Atom2;}
	int GetExcludedLayerSize() {return m_nExcludedLayerSize;}

// set/get the previous SCF iteration currents

	double GetCurrentMagnitude_previous() {return currentMagnitude_previous;}
	void SetCurrentMagnitude_previous(double val) {currentMagnitude_previous = val;}
	bool GetCurrentDirection_previous() {return currentDirection_previous;}
	void SetCurrentDirection_previous(bool dir) {currentDirection_previous = dir;}
	void SetAtomCoordinates(AtomCoordinates *ac) {acoord = ac;}
	double GetLength(); // return the length of the bond
	void SetDifferenceInCurrents(double value) {DifferenceInCurrents = value;}
	double GetDifferenceInCurrents() {return DifferenceInCurrents;}

};

#endif // !defined(AFX_BOND_H__CD3E4C17_1E51_11D3_B16C_006008158370__INCLUDED_)
