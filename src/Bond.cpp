// Bond.cpp: implementation of the Bond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bond.h"

//AtomCoordinates* Bond::acoord;  // declare the static member of the class

/////////////////////////////////////////////////////////////////////////
// construction
/////////////////////////////////////////////////////////////////////////

Bond::Bond(int at1,int at2,AtomCoordinates* ac, int els)
{
	Atom1 = at1; Atom2 = at2;
	currentMagnitude = 0.; currentDirection = true;
	DifferenceInCurrents = 0.; acoord = ac;
	m_nExcludedLayerSize = els;
}

//////////////////////////////////////////////////////////////////////
//  calculate the bond length
//////////////////////////////////////////////////////////////////////

double Bond::GetLength()
{
	double dx = acoord->GetX(Atom1) - acoord->GetX(Atom2);
	double dy = acoord->GetY(Atom1) - acoord->GetY(Atom2);
	double dz = acoord->GetZ(Atom1) - acoord->GetZ(Atom2);

	return sqrt(dx*dx + dy*dy + dz*dz);
}
