//////////////////////////////////////////////////////////////////////
//
//  BaLayer.cpp: implementation of the BaLayer class.
//
//  calculates the coordinates of Ba atoms in YBaCuO crystal
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaLayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BaLayer::BaLayer(Distances* dst)
{
	d = dst;
	this->SetSize(this->calculateNumberOfAtoms());
	this->AllocateCoordinateDimensions();
	this->SetType(5);  // for rendering
}

BaLayer::~BaLayer() {}

///////////////////////////////////////////
// calculate the total number of Ba atoms
///////////////////////////////////////////
int BaLayer::calculateNumberOfAtoms() 
{
	return 2*(d->Get_cells_z())*(d->Get_cells_x())*
				(d->Get_cells_y());
}

///////////////////////////////////////////
// calculate Ba atom coordinates
///////////////////////////////////////////
void BaLayer::calculateCoordinates()
{
	int pointer = 0;
	double xDistance = 0;
	double yDistance = 0;
	double zDistance = 0;

	for(int verticalCell=0 ; verticalCell < d->Get_cells_z() ; verticalCell++)
	{
		zDistance = d->Get_cell_width_z()*(d->Get_Ba_z_lower() + verticalCell);
		for(int yDirection=0 ; yDirection < d->Get_cells_y() ; yDirection++)
		{
			yDistance = d->Get_cell_width_y() * (d->Get_Ba_y() + yDirection);
			for(int xDirection=0 ; xDirection < d->Get_cells_x() ; xDirection++)
			{
				SetCoordinateX(pointer, d->Get_cell_width_x() * 
						(d->Get_Ba_x() + xDirection));
				SetCoordinateY(pointer,yDistance);
				SetCoordinateZ(pointer,zDistance);
				pointer++;
			}
		}

		zDistance = d->Get_cell_width_z()*(d->Get_Ba_z_upper() + verticalCell);
		for(yDirection=0 ; yDirection < d->Get_cells_y() ; yDirection++)
		{
			yDistance = d->Get_cell_width_y() * (d->Get_Ba_y() + yDirection);
			for(int xDirection=0 ; xDirection < d->Get_cells_x() ; xDirection++)
			{
				SetCoordinateX(pointer, d->Get_cell_width_x() * 
						(d->Get_Ba_x() + xDirection));
				SetCoordinateY(pointer,yDistance);
				SetCoordinateZ(pointer,zDistance);
				pointer++;
			}
		}
	}
}
