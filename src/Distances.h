//////////////////////////////////////////////////////////////////////
//
// Distances.h: interface for the Distances class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DISTANCES_H)
#define _DISTANCES_H

#define ATOM_TYPES 9  // it must be 9 even in the case of 1 type.


// exported from DLL class
class Distances  
{

private:

// number of YBaCuO unit cells for plotting in x,y,z directions
	int cells_x;
	int cells_y;
	int cells_z;
// YBaCuO unit cell width in x,y,z directions (in angstroms)
	double cell_width_x;
	double cell_width_y;
	double cell_width_z;
//  Structured points grid spacing along x,y,z axes (in angstroms)
	double gridSpacingX;
	double gridSpacingY;
	double gridSpacingZ;
// Cu(1) layer distances (in the units of unit cell, ie, unit cell = 1,1,1)
	double Cu1_x;				// not in use
	double Cu1_y;				// not in use
	double Cu1_z_lower;			// not in use
	double Cu1_z_upper;			// not in use
// O(1) layer distances
	double O1_x;
	double O1_y;
	double O1_z_lower;			// not in use
	double O1_z_upper;			// not in use
// O(4) layer distances
	double O4_x;				// not in use
	double O4_y;				// not in use
	double O4_z_lower;
	double O4_z_upper;
// Ba layer distances
	double Ba_x;
	double Ba_y;
	double Ba_z_lower;
	double Ba_z_upper;
// Cu(2) layer distances
	double Cu2_x;				// not in use
	double Cu2_y;				// not in use
	double Cu2_z_lower;
	double Cu2_z_upper;
// O(2) layer distances
	double O2_x;
	double O2_y;
	double O2_z_lower;
	double O2_z_upper;
// Y layer distances
	double Y_x;
	double Y_y;
	double Y_z;
// Atom sphere radiuses
	double radius[ATOM_TYPES];
	double colorR[ATOM_TYPES];
	double colorG[ATOM_TYPES];
	double colorB[ATOM_TYPES];

public:

//  construction / destruction

	Distances();
	virtual ~Distances() {};

// YBaCuO distance settings / gettings
// settings according to J.D.Jorgensen, et al, Phys.Rev.B, vol.36,number 7,p.3608(1987)


	void Set_cells_x(int i=1) {cells_x = i;}
	void Set_cells_y(int i=1) {cells_y = i;}
	void Set_cells_z(int i=1) {cells_z = i;}

//	double Set_cell_width_x(double d = 3.8591) {return cell_width_x = d;}
//	double Set_cell_width_x(double d = 3.9195) {return cell_width_x = d;}
//	double Set_cell_width_y(double d = 3.9195) {return cell_width_y = d;}

	double Set_cell_width_x(double d = 4.0000) {return cell_width_x = d;}
	double Set_cell_width_y(double d = 4.0000) {return cell_width_y = d;}
	double Set_cell_width_z(double d = 11.8431) {return cell_width_z = d;}

	double Set_gridSpacingX(double d = 1.0) {return gridSpacingX = d;}
	double Set_gridSpacingY(double d = 1.0) {return gridSpacingY = d;}
	double Set_gridSpacingZ(double d = 1.0) {return gridSpacingZ = d;}
	double Set_Cu1_x(double d = 0.0) {return Cu1_x = d;}	// not in use
	double Set_Cu1_y(double d = 0.0) {return Cu1_y = d;}	// not in use
	double Set_Cu1_z_lower(double d = 0.0) {return Cu1_z_lower = d;}	// not in use
	double Set_Cu1_z_upper(double d = 1.0) {return Cu1_z_upper = d;}	// not in use
	double Set_O1_x(double d = 0.5) {return O1_x = d;}
	double Set_O1_y(double d = 0.5) {return O1_y = d;}
	double Set_O1_z_lower(double d = 0.0) {return O1_z_lower = d;}		// not in use
	double Set_O1_z_upper(double d = 1.0) {return O1_z_upper = d;}		// not in use
	double Set_O4_x(double d = 0.0) {return O4_x = d;}	// not in use
	double Set_O4_y(double d = 0.0) {return O4_y = d;}	// not in use
	double Set_O4_z_lower(double d = 0.1542) {return O4_z_lower = d;}
	double Set_O4_z_upper(double d = 1.0-0.1542) {return O4_z_upper = d;}
	double Set_Ba_x(double d = 0.5) {return Ba_x = d;}
	double Set_Ba_y(double d = 0.5) {return Ba_y = d;}
	double Set_Ba_z_lower(double d = 0.1895) {return Ba_z_lower = d;}
	double Set_Ba_z_upper(double d = 1.0-0.1895) {return Ba_z_upper = d;}
	double Set_Cu2_x(double d = 0.0) {return Cu2_x = d;}	// not in use
	double Set_Cu2_y(double d = 0.0) {return Cu2_y = d;}	// not in use
	double Set_Cu2_z_lower(double d = 0.3574) {return Cu2_z_lower = d;}
	double Set_Cu2_z_upper(double d = 1.0-0.3574) {return Cu2_z_upper = d;}
	double Set_O2_x(double d = 0.5) {return O2_x = d;}
	double Set_O2_y(double d = 0.5) {return O2_y = d;}
	double Set_O2_z_lower(double d = 0.3767) {return O2_z_lower = d;}
	double Set_O2_z_upper(double d = 1.0-0.3767) {return O2_z_upper = d;}
	double Set_Y_x(double d = 0.5) {return Y_x = d;}
	double Set_Y_y(double d = 0.5) {return Y_y = d;}
	double Set_Y_z(double d = 0.5) {return Y_z = d;}
	double Set_Radius(int number, double value = 1.0) {return radius[number] = value;}
	double Set_ColorR(int i, double value = 1.0) {return colorR[i] = value;}
	double Set_ColorG(int i, double value = 1.0) {return colorG[i] = value;}
	double Set_ColorB(int i, double value = 1.0) {return colorB[i] = value;}

	int Get_cells_x() {return cells_x;}
	int Get_cells_y() {return cells_y;}
	int Get_cells_z() {return cells_z;}
	double Get_cell_width_x() {return cell_width_x;}
	double Get_cell_width_y() {return cell_width_y;}
	double Get_cell_width_z() {return cell_width_z;}
	double Get_gridSpacingX() {return gridSpacingX;}
	double Get_gridSpacingY() {return gridSpacingY;}
	double Get_gridSpacingZ() {return gridSpacingZ;}
	double Get_Cu1_x() {return Cu1_x;}
	double Get_Cu1_y() {return Cu1_y;}
	double Get_Cu1_z_lower() {return Cu1_z_lower;}
	double Get_Cu1_z_upper() {return Cu1_z_upper;}
	double Get_O1_x() {return O1_x;}
	double Get_O1_y() {return O1_y;}
	double Get_O1_z_lower() {return O1_z_lower;}
	double Get_O1_z_upper() {return O1_z_upper;}
	double Get_O4_x() {return O4_x;}
	double Get_O4_y() {return O4_y;}
	double Get_O4_z_lower() {return O4_z_lower;}
	double Get_O4_z_upper() {return O4_z_upper;}
	double Get_Ba_x() {return Ba_x;}
	double Get_Ba_y() {return Ba_y;}
	double Get_Ba_z_lower() {return Ba_z_lower;}
	double Get_Ba_z_upper() {return Ba_z_upper;}
	double Get_Cu2_x() {return Cu2_x;}
	double Get_Cu2_y() {return Cu2_y;}
	double Get_Cu2_z_lower() {return Cu2_z_lower;}
	double Get_Cu2_z_upper() {return Cu2_z_upper;}
	double Get_O2_x() {return O2_x;}
	double Get_O2_y() {return O2_y;}
	double Get_O2_z_lower() {return O2_z_lower;}
	double Get_O2_z_upper() {return O2_z_upper;}
	double Get_Y_x() {return Y_x;}
	double Get_Y_y() {return Y_y;}
	double Get_Y_z() {return Y_z;}
	double Get_Radius(int number) {return radius[number];}
	double Get_ColorR(int i) {return colorR[i];}
	double Get_ColorG(int i) {return colorG[i];}
	double Get_ColorB(int i) {return colorB[i];}
};

#endif // !defined(_DISTANCES_H)
