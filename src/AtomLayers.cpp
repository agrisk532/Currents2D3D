//////////////////////////////////////////////////////////////////////
//
//  AtomLayers.cpp: implementation of the AtomLayers class.
//
//	this is a base class for different atom layers in a cell
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtomLayers.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Distances* AtomLayers::d;  // static variable initialization outside it's definition

AtomLayers::AtomLayers() {}

AtomLayers::~AtomLayers()
{
	delete [] coordinates_x;
	delete [] coordinates_y;
	delete [] coordinates_z;
}

/////////////////////////////////////////////
//  Retrieve the coordinate of atom
/////////////////////////////////////////////

double AtomLayers::GetCoordinate(int number, int xyz)
{
	switch (xyz) {
	case 0: return coordinates_x[number];  // X coordinate ( 0 < number < size )
	case 1: return coordinates_y[number];  // Y coordinate
	case 2: return coordinates_z[number];  // Z coordinate
	default: exit(0);
	}
}

///////////////////////////////////////////////////////
// Allocate coordinate dimensions
///////////////////////////////////////////////////////

void AtomLayers::AllocateCoordinateDimensions()
{
	coordinates_x = new double[size];
	coordinates_y = new double[size];
	coordinates_z = new double[size];
}

