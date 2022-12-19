//////////////////////////////////////////////////////////////////////
//
//  O2Layer.cpp: implementation of the O2Layer class.
//
//  calculates the coordinates of O(2) atoms in YBaCuO crystal
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "O2Layer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

O2Layer::O2Layer(char layer, Distances* dst)
{
	d = dst;
	this->SetSize(this->calculateNumberOfAtoms());
	this->AllocateCoordinateDimensions();
	this->whichLayer = layer;
	if(layer == 'l') this->SetType(1); // type for O2_lower is 1
	if(layer == 'u') this->SetType(3); // type for O2_upper is 3
}

O2Layer::~O2Layer() {}

///////////////////////////////////////////
// calculate the total number of Cu atoms
///////////////////////////////////////////
int O2Layer::calculateNumberOfAtoms() 
{
	return (d->Get_cells_z())*
			(2*(d->Get_cells_x() + 1)*(d->Get_cells_y() + 1) +
				d->Get_cells_x() + 1 + d->Get_cells_y() + 1);
}

///////////////////////////////////////////
// calculate Cu atom coordinates
///////////////////////////////////////////
void O2Layer::calculateCoordinates()
{
	int pointer = 0;
	double yDistance = 0;
	double zDistance = 0;

	for(int verticalCell=0 ; verticalCell < d->Get_cells_z() ; verticalCell++)
	{
		if(whichLayer=='l') // lower
			zDistance = d->Get_cell_width_z() * 
						(d->Get_O2_z_lower() + verticalCell);

		if(whichLayer=='u') // upper
			zDistance = d->Get_cell_width_z() * 
						(d->Get_O2_z_upper() + verticalCell);

		yDistance = - d->Get_O2_y() * d->Get_cell_width_y();
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
										( - d->Get_O2_x() + xDirection));
				SetCoordinateY(pointer,yDistance);
				SetCoordinateZ(pointer,zDistance);
				pointer++;
			}

			yDistance = d->Get_cell_width_y() * (d->Get_O2_y() + yDirection);
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
