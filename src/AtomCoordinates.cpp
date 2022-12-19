//////////////////////////////////////////////////////////////////////
// atomCoordinates.cpp: implementation of the atomCoordinates class.
//
//  calculates coordinates of all required atom layers
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtomCoordinates.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AtomCoordinates::AtomCoordinates()
{
	sizeOfAll = 0;
}

AtomCoordinates::~AtomCoordinates() {}

//////////////////////////////////////////////
//  Add a layer to the coordinate dimension
//////////////////////////////////////////////

void AtomCoordinates::AddLayer(AtomLayers *al)
{
// get the number of atoms in the layer
	int layerSize = al->GetSize();
// get the atom type
	char type = al->GetType();
// set the total number of atoms
	this->SetSize(this->GetSize() + layerSize);
	al->calculateCoordinates();
// push the coordinates and atom types into the vectors
	for(int i=0 ; i<layerSize ; i++)
	{
		double cx = al->GetCoordinate(i,0);
		double cy = al->GetCoordinate(i,1);
		double cz = al->GetCoordinate(i,2);
		coordinate_x.push_back(cx); // add atom coordinates
		coordinate_y.push_back(cy);
		coordinate_z.push_back(cz);
		atomType.push_back(type);  // add atom type
		magneticField_x.push_back(0.); // initialize vector containing magnetic field
		magneticField_y.push_back(0.);
		magneticField_z.push_back(0.);
	}

//	delete al;  // remove the layer from memory since coordinates and types were copied

}

//////////////////////////////////////////////
//  Find X coordinate minimum
//////////////////////////////////////////////

double AtomCoordinates::GetXMin()
{
	double minimum = 1e100;

	for(int i=0 ; i<sizeOfAll ; i++)
	{
		if(coordinate_x[i] < minimum) minimum = coordinate_x[i];
	}
	return minimum;
}

//////////////////////////////////////////////
//  Find X coordinate maximum
//////////////////////////////////////////////

double AtomCoordinates::GetXMax()
{
	double maximum = -1e100;

	for(int i=0 ; i<sizeOfAll ; i++)
	{
		if(coordinate_x[i] > maximum) maximum = coordinate_x[i];
	}
	return maximum;
}

//////////////////////////////////////////////
//  Find Y coordinate minimum
//////////////////////////////////////////////

double AtomCoordinates::GetYMin()
{
	double minimum = 1e100;

	for(int i=0 ; i<sizeOfAll ; i++)
	{
		if(coordinate_y[i] < minimum) minimum = coordinate_y[i];
	}
	return minimum;
}

//////////////////////////////////////////////
//  Find Y coordinate maximum
//////////////////////////////////////////////

double AtomCoordinates::GetYMax()
{
	double maximum = -1e100;

	for(int i=0 ; i<sizeOfAll ; i++)
	{
		if(coordinate_y[i] > maximum) maximum = coordinate_y[i];
	}
	return maximum;
}

//////////////////////////////////////////////
//  Find Z coordinate minimum
//////////////////////////////////////////////

double AtomCoordinates::GetZMin()
{
	double minimum = 1e100;

	for(int i=0 ; i<sizeOfAll ; i++)
	{
		if(coordinate_z[i] < minimum) minimum = coordinate_z[i];
	}
	return minimum;
}

//////////////////////////////////////////////
//  Find Z coordinate maximum
//////////////////////////////////////////////

double AtomCoordinates::GetZMax()
{
	double maximum = -1e100;

	for(int i=0 ; i<sizeOfAll ; i++)
	{
		if(coordinate_z[i] > maximum) maximum = coordinate_z[i];
	}
	return maximum;
}

///////////////////////////////////////////////
//
///////////////////////////////////////////////

void AtomCoordinates::TranslateToGaugeOrigin()
{
	for(int i=0 ; i<sizeOfAll ; i++)
	{
		coordinate_x[i] -= gaugeOrigin_x;
		coordinate_y[i] -= gaugeOrigin_y;
		coordinate_z[i] -= gaugeOrigin_z;
	}
}