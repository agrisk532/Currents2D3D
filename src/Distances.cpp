// Distances.cpp: implementation of the Distances class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Distances.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Distances::Distances()
{
	Set_cells_x(1); // must be odd number (number of Cu atoms must be even)
	Set_cells_y(1);
	Set_cells_z(1);
	Set_cell_width_x();
	Set_cell_width_y();
	Set_cell_width_z();
	Set_gridSpacingX();
 	Set_gridSpacingY();
	Set_gridSpacingZ();
	Set_Cu1_x();
	Set_Cu1_y();
	Set_Cu1_z_lower();
	Set_Cu1_z_upper();
	Set_O1_x();
	Set_O1_y();
	Set_O1_z_lower();
	Set_O1_z_upper();
	Set_O4_x();
	Set_O4_y();
	Set_O4_z_lower();
	Set_O4_z_upper();
	Set_Ba_x();
	Set_Ba_y();
	Set_Ba_z_lower();
	Set_Ba_z_upper();
	Set_Cu2_x();
	Set_Cu2_y();
	Set_Cu2_z_lower();
	Set_Cu2_z_upper();
	Set_O2_x();
	Set_O2_y();
	Set_O2_z_lower();
	Set_O2_z_upper();
	Set_Y_x();
	Set_Y_y();
	Set_Y_z();
	Set_Radius(0,0.6);  // Cu2_lower = Cu(2+) radius
	Set_Radius(1,0.6);  // O2_lower = O(2-) radius
	Set_Radius(2,0.6);  // Cu2_upper = Cu(2+) radius
	Set_Radius(3,0.6);  // O2_upper = O(2-) radius
	Set_Radius(4,0.6);  // Y = Y(3+) radius
	Set_Radius(5,0.6);  // Ba = Ba(2+) radius
	Set_Radius(6,0.6);  // O4 = O(2-) radius
	Set_Radius(7,0.6);  // O1 = O(2-) radius
	Set_Radius(8,0.6);  // Cu1 = Cu(2+) radius
	Set_ColorR(0,1.);	// R color of Cu2_lower
	Set_ColorG(0,1.);	// G color of Cu2_lower
	Set_ColorB(0,0.);	// B color of Cu2_lower
	Set_ColorR(1,1.);	// R color of O2_lower
	Set_ColorG(1,0.);	// G color of O2_lower
	Set_ColorB(1,0.);	// B color of O2_lower
	Set_ColorR(2,1.);	// R color of Cu2_upper
	Set_ColorG(2,1.);	// G color of Cu2_upper
	Set_ColorB(2,0.);	// B color of Cu2_upper
	Set_ColorR(3,1.);	// R color of O2_upper
	Set_ColorG(3,0.);	// G color of O2_upper
	Set_ColorB(3,0.);	// B color of O2_upper
	Set_ColorR(4,1.);	// R color of Y
	Set_ColorG(4,1.);	// G color of Y
	Set_ColorB(4,1.);	// B color of Y
	Set_ColorR(5,0.);	// R color of Ba
	Set_ColorG(5,0.1);	// G color of Ba
	Set_ColorB(5,1.);	// B color of Ba
	Set_ColorR(6,1.);	// R color of O4
	Set_ColorG(6,0.);	// G color of O4
	Set_ColorB(6,0.);	// B color of O4
	Set_ColorR(7,1.);	// R color of O1
	Set_ColorG(7,0.);	// G color of O1
	Set_ColorB(7,0.);	// B color of O1
	Set_ColorR(8,1.);	// R color of Cu1
	Set_ColorG(8,1.);	// G color of Cu1
	Set_ColorB(8,0.);	// B color of Cu1
}
