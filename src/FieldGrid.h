//////////////////////////////////////////////////////////////////////
//
// FieldGrid.h: interface for the FieldGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FIELDGRID_H)
#define _FIELDGRID_H

#include "vtkStructuredPoints.h"
#include "vtkScalars.h"
#include "vtkVectors.h"
#include "Distances.h"
#include "AtomCoordinates.h"

class FieldGrid  // structured points dataset
{

private:

	double gridOriginX;  // grid origin (in angstroms)
	double gridOriginY;
	double gridOriginZ;
	int gridDimensionX;  // number of grid points along coordinate axes
	int gridDimensionY;
	int gridDimensionZ;
	double gridSpacingX; // interval between grid points (in angstroms)
	double gridSpacingY;
	double gridSpacingZ;

	double scalarMin; // the max vlaue of scalars associated with data set
	double scalarMax; // the min value of scalars

	vtkStructuredPoints *sp; // vtk data set
	vtkScalars *scalars; // to fill with magnetic field absolute values
	vtkVectors *vectors; // to fill with magnetic field vectors

public:

	FieldGrid(AtomCoordinates&, Distances&);
	virtual ~FieldGrid();

	static FieldGrid *New(AtomCoordinates &ac, Distances &d) {return new FieldGrid(ac,d);}

	double GetGridOriginX() {return gridOriginX;}
	double GetGridOriginY() {return gridOriginY;}
	double GetGridOriginZ() {return gridOriginZ;}
	int GetGridDimensionX() {return gridDimensionX;}
	int GetGridDimensionY() {return gridDimensionY;}
	int GetGridDimensionZ() {return gridDimensionZ;}
	double GetGridSpacingX() {return gridSpacingX;}
	double GetGridSpacingY() {return gridSpacingY;}
	double GetGridSpacingZ() {return gridSpacingZ;}

	double GetScalarMin() {return scalarMin;}
	double GetScalarMax() {return scalarMax;}
	void SetScalarMin(double val) {scalarMin = val;}
	void SetScalarMax(double val) {scalarMax = val;}

	vtkStructuredPoints *GetStructuredPoints() {return sp;}
	vtkScalars *GetDataScalars() {return scalars;}
	vtkVectors *GetDataVectors() {return vectors;}
};

#endif // !defined(_FIELDGRID_H)
