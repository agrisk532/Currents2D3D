//////////////////////////////////////////////////////////////////////
//
// FieldGrid.cpp: implementation of the FieldGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FieldGrid.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FieldGrid::FieldGrid(AtomCoordinates &ac, Distances &d)
{
	gridOriginX = 1.5*ac.GetXMin() - 0.5*ac.GetXMax();
	gridOriginY = 1.5*ac.GetYMin() - 0.5*ac.GetYMax();
	gridOriginZ = 1.5*ac.GetZMin() - 0.5*ac.GetZMax();
	gridDimensionX = 2.*(ac.GetXMax() - ac.GetXMin()) / d.Get_gridSpacingX() + 2;
	gridDimensionY = 2.*(ac.GetYMax() - ac.GetYMin()) / d.Get_gridSpacingY() + 2;
	gridDimensionZ = 2.*(ac.GetZMax() - ac.GetZMin()) / d.Get_gridSpacingZ() + 2;
	gridSpacingX = d.Get_gridSpacingX();
	gridSpacingY = d.Get_gridSpacingY();
	gridSpacingZ = d.Get_gridSpacingZ();

// make a structured points grid

	sp = vtkStructuredPoints::New();
		sp->SetDimensions(gridDimensionX,gridDimensionY,gridDimensionZ);
		sp->SetOrigin(gridOriginX,gridOriginY,gridOriginZ);
		sp->SetSpacing(d.Get_gridSpacingX(), d.Get_gridSpacingY(), d.Get_gridSpacingZ());

// allocate arrays for scalars / vectors

	scalars = vtkScalars::New(VTK_UNSIGNED_CHAR,1);
		scalars->SetNumberOfScalars(gridDimensionX*gridDimensionY*gridDimensionZ);
	vectors = vtkVectors::New(VTK_FLOAT);
		vectors->SetNumberOfVectors(gridDimensionX*gridDimensionY*gridDimensionZ);
}

//////////////////////////////////////////////////////////////////////

FieldGrid::~FieldGrid()
{
	sp->Delete();
	scalars->Delete();
	vectors->Delete();
}

//////////////////////////////////////////////////////////////////////
