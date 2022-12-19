///////////////////////////////////////////////////////////////////////////////////////////////
//
//	AtomLayers.h: interface for the AtomLayers class.
//
//	This is abstract base class for coordinate generation of different atom layers in a cluster
//
///////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(_ATOMLAYERS_H)
#define _ATOMLAYERS_H


#include <stdlib.h>
#include "Distances.h"

class AtomLayers
{
protected:
//  type of atom layer (they are defined in main())
	char type;
// total number of atoms in a layer
	int size;
// reference to the Distance object
	Distances *d;

	double *coordinates_x;  // arrays holding coordinates of atoms
	double *coordinates_y;
	double *coordinates_z;

public:

	AtomLayers();
	virtual ~AtomLayers();
	virtual int calculateNumberOfAtoms() = 0; // pure virtual function
	virtual void calculateCoordinates() = 0;  // pure virtual function
	void SetType(char t) {type = t;}
	char GetType() {return type;}

	double GetCoordinate(int,int);
	int GetSize() {return size;}  // returns the number of atoms in a layer
	void SetSize(int s) {size = s;}
	void AllocateCoordinateDimensions();
	void SetCoordinateX(int number,double value) {coordinates_x[number] = value;}
	void SetCoordinateY(int number,double value) {coordinates_y[number] = value;}
	void SetCoordinateZ(int number,double value) {coordinates_z[number] = value;}
	void SetDistances(Distances *dist) {d = dist;}
};

#endif // !defined(_ATOMLAYERS_H)
