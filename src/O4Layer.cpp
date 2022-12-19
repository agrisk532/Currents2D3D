//////////////////////////////////////////////////////////////////////
//
//  O4Layer.cpp: implementation of the O4Layer class.
//
//  calculates the coordinates of O4 atoms in YBaCuO crystal
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "O4Layer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

O4Layer::O4Layer(Distances* dst)
{
	d = dst;
	this->SetSize(this->calculateNumberOfAtoms());
	this->AllocateCoordinateDimensions();
	this->SetType(6); // for rendering
}

O4Layer::~O4Layer() {}

///////////////////////////////////////////
// calculate the total number of O4 atoms
///////////////////////////////////////////
int O4Layer::calculateNumberOfAtoms() 
{
	return (d->Get_cells_z())*
			2*(d->Get_cells_x()+1)*(d->Get_cells_y()+1);
}

///////////////////////////////////////////
// calculate O4 atom coordinates
///////////////////////////////////////////
void O4Layer::calculateCoordinates()
{
	int pointer = 0;
	double xDistance = 0;
	double yDistance = 0;
	double zDistance = 0;

	for(int verticalCell=0 ; verticalCell < d->Get_cells_z() ; verticalCell++)
	{
		zDistance = d->Get_cell_width_z() * 
					(d->Get_O4_z_lower() + verticalCell);
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

		zDistance = d->Get_cell_width_z() * 
					(d->Get_O4_z_upper() + verticalCell);
		for( yDirection=0 ; yDirection < d->Get_cells_y()+1 ; yDirection++)
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
