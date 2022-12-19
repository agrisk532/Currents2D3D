//////////////////////////////////////////////////////////////////////
//
//  Cu2Layer.cpp: implementation of the Cu2Layer class.
//
//  calculates the coordinates of Cu(2) atoms in YBaCuO crystal
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cu2Layer.h"
#include "Distances.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cu2Layer::Cu2Layer(char layer,Distances* dst)
{
	d = dst;
	this->SetSize(this->calculateNumberOfAtoms());
	this->AllocateCoordinateDimensions();
	this->whichLayer = layer;
	if(layer == 'l') this->SetType(0); // type for Cu2_lower is 0
	if(layer == 'u') this->SetType(2); // type for Cu2_upper is 2
}

Cu2Layer::~Cu2Layer() {}

///////////////////////////////////////////
// calculate the total number of Cu atoms
///////////////////////////////////////////
int Cu2Layer::calculateNumberOfAtoms() 
{
	return (d->Get_cells_z())*(d->Get_cells_x()+1)*
				(d->Get_cells_y()+1);
}

///////////////////////////////////////////
// calculate Cu atom coordinates
///////////////////////////////////////////
void Cu2Layer::calculateCoordinates()
{
	int pointer = 0;
	double xDistance = 0;
	double yDistance = 0;
	double zDistance = 0;

	for(int verticalCell=0 ; verticalCell < d->Get_cells_z() ; verticalCell++)
	{
		if(whichLayer=='l') // lower
			zDistance = d->Get_cell_width_z() *
						(d->Get_Cu2_z_lower() + verticalCell);

		if(whichLayer=='u') // upper
			zDistance = d->Get_cell_width_z() *
						(d->Get_Cu2_z_upper() + verticalCell);

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
