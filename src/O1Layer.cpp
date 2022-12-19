//////////////////////////////////////////////////////////////////////
//
//  O1Layer.cpp: implementation of the O1Layer class.
//
//  calculates the coordinates of O1 atoms in YBaCuO crystal
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "O1Layer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

O1Layer::O1Layer(Distances* dst)
{
	d = dst;
	this->SetSize(this->calculateNumberOfAtoms());
	this->AllocateCoordinateDimensions();
	this->SetType(7); // for rendering
}

O1Layer::~O1Layer() {}

///////////////////////////////////////////
// calculate the total number of O1 atoms
///////////////////////////////////////////
int O1Layer::calculateNumberOfAtoms() 
{
	return (d->Get_cells_z()+1)* 
		 (2*(d->Get_cells_x() + 1)*(d->Get_cells_y() + 1) +
		    d->Get_cells_x() + 1 + d->Get_cells_y() + 1);
}

///////////////////////////////////////////
// calculate O1 atom coordinates
///////////////////////////////////////////
void O1Layer::calculateCoordinates()
{
	int pointer = 0;
	double yDistance = 0;
	double zDistance = 0;

	for(int verticalCell=0 ; verticalCell < d->Get_cells_z() + 1 ; verticalCell++)
	{
		zDistance = d->Get_cell_width_z() * verticalCell;

		yDistance = - d->Get_O1_y() * d->Get_cell_width_y();
		for(int xDirection=0 ; xDirection < d->Get_cells_x()+1 ; xDirection++)
		{
			SetCoordinateX(pointer,xDirection * d->Get_cell_width_x());
			SetCoordinateY(pointer,yDistance);
			SetCoordinateZ(pointer,zDistance);
			pointer++;
		}
		
		for(int yDirection=0 ; yDirection < d->Get_cells_y()+1 ; yDirection++)
		{
			yDistance = yDirection * d->Get_cell_width_y();
			for(int xDirection=0 ; xDirection < d->Get_cells_x()+2 ; xDirection++)
			{
				SetCoordinateX(pointer, d->Get_cell_width_x() * 
								( - d->Get_O1_x() + xDirection));
				SetCoordinateY(pointer,yDistance);
				SetCoordinateZ(pointer,zDistance);
				pointer++;
			}

			yDistance = d->Get_cell_width_y() * (d->Get_O1_y() + yDirection);
			for( xDirection=0 ; xDirection < d->Get_cells_x()+1 ; xDirection++)
			{
				SetCoordinateX(pointer, xDirection * d->Get_cell_width_x());
				SetCoordinateY(pointer,yDistance);
				SetCoordinateZ(pointer,zDistance);
				pointer++;
			}

		}
	}
}
