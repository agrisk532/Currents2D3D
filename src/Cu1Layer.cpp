//////////////////////////////////////////////////////////////////////
//
//  Cu1Layer.cpp: implementation of the Cu1Layer class.
//
//  calculates the coordinates of Cu(1) atoms in YBaCuO crystal
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cu1Layer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cu1Layer::Cu1Layer(Distances* dst)
{
	d = dst;
	this->SetSize(this->calculateNumberOfAtoms());
	this->AllocateCoordinateDimensions();
	this->SetType(8);  // for rendering
}

Cu1Layer::~Cu1Layer() {}

///////////////////////////////////////////
// calculate the total number of Cu(1) atoms
///////////////////////////////////////////
int Cu1Layer::calculateNumberOfAtoms() 
{
	return (d->Get_cells_z()+1) * (d->Get_cells_x()+1) *
		   (d->Get_cells_y()+1);
}

///////////////////////////////////////////
// calculate Cu(1) atom coordinates
///////////////////////////////////////////
void Cu1Layer::calculateCoordinates()
{
	int pointer = 0;
	double xDistance = 0;
	double yDistance = 0;
	double zDistance = 0;

	for(int verticalCell=0 ; verticalCell < d->Get_cells_z() + 1; verticalCell++)
	{
		zDistance = d->Get_cell_width_z() * verticalCell;
		for(int yDirection=0 ; yDirection < d->Get_cells_y()+1 ; yDirection++)
		{
			yDistance = yDirection * d->Get_cell_width_y();
			for(int xDirection=0 ; xDirection < d->Get_cells_x()+1 ; xDirection++)
			{
				SetCoordinateX(pointer,xDirection * d->Get_cell_width_x());
				SetCoordinateY(pointer,yDistance);
				SetCoordinateZ(pointer,zDistance);
				pointer++;
			}
		}
	}
}
