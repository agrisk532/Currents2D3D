// AtomParameters.cpp: implementation of the AtomParameters class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtomParameters.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AtomParameters::AtomParameters(double coeff[2],double expon[2])
{
	for(int i=0 ; i<2 ; i++)
	{
		c[i] = coeff[i];
		e[i] = expon[i];
	}
	c_Ylm = sqrt(15./(16.*3.1415926));
}

///////////////////////////////////////////////////////////////////////
// returns the value of an atomic orbital of Cu atom
///////////////////////////////////////////////////////////////////////

double AtomParameters::CuAOValue(double center[3],double pointInSpace[3])
{
	double x = pointInSpace[0] - center[0];
	double y = pointInSpace[1] - center[1];
	double z = pointInSpace[2] - center[2];

	double r = sqrt(x*x + y*y + z*z);

	return (c[0]*exp(-e[0]*r) + c[1]*exp(-e[1]*r)) * c_Ylm * (x*x - y*y);
}

///////////////////////////////////////////////////////////////////////
// returns the total value of an atomic orbital centered on 'atom'
///////////////////////////////////////////////////////////////////////

double AtomParameters::GetAOValue(int atom, // returns the value of an atomic orbital centered on 'atom' 
								 double pointInSpace[3] // in a pointInSpace (x,y,z)
								)
{
	double atomCenter[3];

	atomCenter[0] = ac->GetX(atom);
	atomCenter[1] = ac->GetY(atom);
	atomCenter[2] = ac->GetZ(atom);

	return CuAOValue(atomCenter,pointInSpace);
}

////////////////////////////////////////////////////////////////////////////////
// returns the X gradient of an atomic orbital centered on atom, in pointInSpace
// specialized for double zeta Slater orbital
//
// R = (c[0]*exp(-e[0]*r) + c[1]*exp(-e[1]*r))*r*r  -  radial part
//
// Y(x2-y2) = sqrt(15/(16*pi))*(x2-y2)/(r*r)  -  spherical part
//
// psi = R * Y(x2-y2)
//
////////////////////////////////////////////////////////////////////////////////

void AtomParameters::GetAOGradients(int atom, // returns the value of an atomic orbital centered on 'atom' 
	  								 double pointInSpace[3], // in a pointInSpace (x,y,z)
									 double AOGradients[3]  // return array with AO gradients
									 )
{
	double atomCenter[3];

	atomCenter[0] = ac->GetX(atom);
	atomCenter[1] = ac->GetY(atom);
	atomCenter[2] = ac->GetZ(atom);

	double x = pointInSpace[0] - atomCenter[0];
	double y = pointInSpace[1] - atomCenter[1];
	double z = pointInSpace[2] - atomCenter[2];

	double r = sqrt(x*x + y*y + z*z);

	double exponent[2];
	double exponent_dx[2]; // derivatives of exponent with respect to (x,y,z)
	double exponent_dy[2];
	double exponent_dz[2];

	exponent[0] = exp(-e[0]*r); // for the first exponent of the AO
	exponent[1] = exp(-e[1]*r);	// for the second exponent of the AO
	exponent_dx[0] = -c[0]*exponent[0]*x/r;
	exponent_dx[1] = -c[1]*exponent[1]*x/r;
	exponent_dy[0] = -c[0]*exponent[0]*y/r;
	exponent_dy[1] = -c[1]*exponent[1]*y/r;
	exponent_dz[0] = -c[0]*exponent[0]*z/r;
	exponent_dz[1] = -c[1]*exponent[1]*z/r;

	double c0Y = c[0]*c_Ylm;
	double c1Y = c[1]*c_Ylm;

	AOGradients[0] = c0Y*exponent_dx[0]*x*x + c0Y*exponent[0]*2.*x - c0Y*exponent_dx[0]*y*y +
					 c1Y*exponent_dx[1]*x*x + c1Y*exponent[1]*2.*x - c1Y*exponent_dx[1]*y*y;

	AOGradients[1] = c0Y*exponent_dy[0]*x*x - c0Y*exponent[0]*2.*y - c0Y*exponent_dy[0]*y*y +
					 c1Y*exponent_dy[1]*x*x - c1Y*exponent[1]*2.*y - c1Y*exponent_dy[1]*y*y;

	AOGradients[2] = c0Y*exponent_dz[0]*x*x - c0Y*exponent_dz[0]*y*y +
					 c1Y*exponent_dz[1]*x*x - c1Y*exponent_dz[1]*y*y;
}
