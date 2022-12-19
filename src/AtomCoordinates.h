//////////////////////////////////////////////////////////////////////
//
// atomCoordinates.h: interface for the atomCoordinates class.
//
//	this class holds coordinate vectors of all atoms in a plot and atom type
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ATOMCOORDINATES_H)
#define _ATOMCOORDINATES_H

#include "AtomLayers.h"
#include <vector>
using namespace std;

class AtomCoordinates
{

private:

	int sizeOfAll; // holds the number of all atoms of all types
	void SetSize(int s) {sizeOfAll = s;}

	vector<double> coordinate_x;  // holds the cartesian coordinates of an atom
	vector<double> coordinate_y;
	vector<double> coordinate_z;
	vector<char> atomType;

	vector<double> magneticField_x;  // holds magnetic field values at atom positions
	vector<double> magneticField_y;  // for 2D current calculation
	vector<double> magneticField_z;

public:

	AtomCoordinates();
	virtual ~AtomCoordinates();
	void AddLayer(AtomLayers*);
	int GetSize() {return sizeOfAll;}
// returns minimal and maximal coordinates (along x,y,z axes) of atoms
	double GetXMin();
	double GetYMin();
	double GetZMin();
	double GetXMax();
	double GetYMax();
	double GetZMax();
// returns atom coordinates
	double GetX(int i) {return coordinate_x[i];} 
	double GetY(int i) {return coordinate_y[i];}
	double GetZ(int i) {return coordinate_z[i];}
	char GetType(int i) {return atomType[i];}

	double gaugeOrigin_x; // gauge origin for magnetic vector potential
	double gaugeOrigin_y;
	double gaugeOrigin_z;
	void TranslateToGaugeOrigin();

	void SetMagneticField_x(int i,double value) {magneticField_x[i] = value;}
	void SetMagneticField_y(int i,double value) {magneticField_y[i] = value;}
	void SetMagneticField_z(int i,double value) {magneticField_z[i] = value;}
	double GetMagneticField_x(int i) {return magneticField_x[i];}
	double GetMagneticField_y(int i) {return magneticField_y[i];}
	double GetMagneticField_z(int i) {return magneticField_z[i];}
};

#endif // !defined(_ATOMCOORDINATES_H)
