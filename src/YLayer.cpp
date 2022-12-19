//////////////////////////////////////////////////////////////////////
//
//  YLayer.cpp: implementation of the YLayer class.
//
//  calculates the coordinates of Y atoms in YBaCuO crystal
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YLayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

YLayer::YLayer(Distances* dst)
{
	d = dst;
	this->SetSize(this->calculateNumberOfAtoms());
	this->AllocateCoordinateDimensions();
	this->SetType(4);  // Y atom type is 4 (for rendering)
}

YLayer::~YLayer() {}

///////////////////////////////////////////
// calculate the total number of Y atoms
///////////////////////////////////////////
int YLayer::calculateNumberOfAtoms() 
{
	return (d->Get_cells_z())*(d->Get_cells_x())*
			(d->Get_cells_y());
}

///////////////////////////////////////////
// calculate Y atom coordinates
///////////////////////////////////////////
void YLayer::calculateCoordinates()
{
	int pointer = 0;
	double xDistance = 0;
	double yDistance = 0;
	double zDistance = 0;

	for(int verticalCell=0 ; verticalCell < d->Get_cells_z() ; verticalCell++)
	{
		zDistance = d->Get_cell_width_z() * 
					(d->Get_Y_z() + verticalCell);
		for(int yDirection=0 ; yDirection < d->Get_cells_y() ; yDirection++)
		{
			yDistance = d->Get_cell_width_y() *
						(d->Get_Y_y() + yDirection);
			for(int xDirection=0 ; xDirection < d->Get_cells_x() ; xDirection++)
			{
				SetCoordinateX(pointer, d->Get_cell_width_x() * 
										(d->Get_Y_x() + xDirection));
				SetCoordinateY(pointer,yDistance);
				SetCoordinateZ(pointer,zDistance);
				pointer++;
			}
		}
	}
}
