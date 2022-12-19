//////////////////////////////////////////////////////////////////////
//
// AtomParameters.h: interface for the AtomParameters class.
//
// It contains atom orbital parameters for calculations
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATOMPARAMETERS_H__143536A1_3E7E_11D3_B193_006008158370__INCLUDED_)
#define AFX_ATOMPARAMETERS_H__143536A1_3E7E_11D3_B193_006008158370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomCoordinates.h"

class AtomParameters  
{

private:

	double c[2]; // holds contraction coefficients for double zeta basis
	double e[2]; // holds orbital exponents
	double c_Ylm; // holds the normalization constant for spherical harmonic d(x2-y2)
// returns value of an Cu atomic orital located in 'center', at a point 'pointInSpace'
	double CuAOValue(double center[3],double pointInSpace[3]); 
	AtomCoordinates *ac;

public:

	void SetCoordinates(AtomCoordinates *acoord) {ac = acoord; return;}
	AtomParameters(double coeff[2], double expon[2]);
	static AtomParameters *New(double c[2], double e[2]) {return new AtomParameters(c,e);}
	virtual ~AtomParameters() {};
	double GetAOValue(int atom, // returns the value of an atomic orbital centered on 'atom' 
				double pointCoordinates[3]);	// at a point (x,y,z) in cartesian space

	void GetAOGradients(int atom, // returns the value of an atomic orbital centered on 'atom' 
	  					 double pointInSpace[3], // in a pointInSpace (x,y,z)
						 double AOGradients[3]);  // return array with AO gradients
};

#endif // !defined(AFX_ATOMPARAMETERS_H__143536A1_3E7E_11D3_B193_006008158370__INCLUDED_)
