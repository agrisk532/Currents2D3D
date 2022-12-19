//////////////////////////////////////////////////////////////////////
//
// CurrentsBase.cpp: implementation of the CurrentsBase class.
//
//  It is a base class for Currents (1D bond currents and magnetic field)
//  and Currents3D
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurrentsBase.h"

IMPLEMENT_DYNAMIC(CurrentsBase,CObject);

//////////////////////////////////////////////////////////////////////
// Destruction

CurrentsBase::~CurrentsBase()
{
	for(int i=0;i<NumberOfBonds;i++)
	{
		delete bonds[i];
	}
}

//////////////////////////////////////////////////////////////////////
// Add atom layers for CALCULATION
//////////////////////////////////////////////////////////////////////

void CurrentsBase::AddLayer(AtomLayers *al)
{
	int start = FindLayerStart(al); // layer start in the Acoord object (plot object)
	int size = FindLayerSize(al);
	StartOfLayer.push_back(start); // start of layer in AtomCoordinates
	SizeOfLayer.push_back(size);   // size of layer
// els - excluded layer size (if plot layer from acoord occurs before a calculated currents
// layer

	int els = start - NumberOfAtoms; // subtract the number of atoms of the previous added
// layer

	NumberOfLayers++;
	NumberOfAtoms += size;
	AddBonds(start,size,d->Get_cell_width_y(),els);  // in Distances class all is in angstroms
	for(int i=start ; i<start+size ; i++) // assign initial magnetic field values on atoms
	{
		acoord->SetMagneticField_x(i,0.);
		acoord->SetMagneticField_y(i,0.);
		acoord->SetMagneticField_z(i,initialMagneticField);
	}
}

///////////////////////////////////////////////////////////////////////
//  Find atom layer start in the coordinates_x(y,z)
///////////////////////////////////////////////////////////////////////
int CurrentsBase::FindLayerStart(AtomLayers *al)
{
	int size = acoord->GetSize();
	for (int i=0;i<size;i++) 
	{
		if(acoord->GetType(i) != al->GetType()) continue;
		return i;
	}
	printf(" No atom type found in existing layers\n");
	exit(0);
}

///////////////////////////////////////////////////////////////////////
//  Find atom layer size (number of atoms of the same type) in the coordinates_x(y,z)
///////////////////////////////////////////////////////////////////////
int CurrentsBase::FindLayerSize(AtomLayers *al)
{
	return al->GetSize();
}

///////////////////////////////////////////////////////////////////////
//  Add bond information to the layer
///////////////////////////////////////////////////////////////////////
void CurrentsBase::AddBonds(int start,int size,double dist,int els)
{
// check dimension coordinates_x(y,z) for bonded atoms
// start - start of layer in atomCoordinates
// size - size of the layer
// dist - distance limit under which atoms are considered as bonded
// els - excluded layer size (if plot layer from acoord occurs before a calculated currents
// layer


	double d[3];

	for(int i=start;i<start+size;i++)
	{
		for(int j=start;j<i;j++)
		{
			d[0] = acoord->GetX(i)-acoord->GetX(j);
			d[1] = acoord->GetY(i)-acoord->GetY(j);
			d[2] = acoord->GetZ(i)-acoord->GetZ(j);

			if(VectorLength(d) < dist + 0.01)
			{
				bonds.push_back(Bond::New(j,i,acoord,els));
				NumberOfBonds++;
				printf("Bond %d from %d to %d\n",NumberOfBonds,j,i);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////
// returns the start index of the layer
/////////////////////////////////////////////////////////////////

int CurrentsBase::GetStartIndex(int atomLayerID)
{
	return StartOfLayer[atomLayerID];
}

/////////////////////////////////////////////////////////////////
//   returns the ID of the layer (in currents) into which the atom is
//  numbering is according to the layers added for calculation and starts from zero.
/////////////////////////////////////////////////////////////////

int CurrentsBase::GetAtomLayerID(int atomNumber)
{
	int margin = 0;
	for(int i=0 ; i<NumberOfLayers ; i++)
	{
		int size = SizeOfLayer[i];
		margin += size;
		if(atomNumber < margin) return i;
		else
			continue;
	}
	AfxMessageBox("Error in GetAtomLayerID\n");
	exit(0);
}

//////////////////////////////////////////////////////////////////////
//  finds the index of the atomNumberInCurrents in the AtomCoordinates
//////////////////////////////////////////////////////////////////////

int CurrentsBase::GetAcIndex(int atomNumberInCurrents)
{
// find the layer (in currents) in which the atom is
	int layer = GetAtomLayerID(atomNumberInCurrents);
	int atomsBefore = 0; // atoms before the atom in interest (in currents)

	for(int i=0 ; i<layer ; i++) atomsBefore += SizeOfLayer[i];

	return StartOfLayer[layer] + (atomNumberInCurrents - atomsBefore);
}

///////////////////////////////////////////////////////////////
// calculate the vector product of two vectors
// v1[],v2[],v_res[] are double[3] arrays
///////////////////////////////////////////////////////////////

void CurrentsBase::VectorProduct(double *v1,double *v2,double *v_res)
{
	v_res[0] = v1[1]*v2[2] - v1[2]*v2[1];
	v_res[1] = v1[2]*v2[0] - v1[0]*v2[2];
	v_res[2] = v1[0]*v2[1] - v1[1]*v2[0];

	return;
}

///////////////////////////////////////////////////////////////
// calculate the scalar product of two vectors
///////////////////////////////////////////////////////////////

double CurrentsBase::ScalarProduct(double *v1,double *v2)
{
	double product = 0;
	for(int i=0 ; i<3 ; i++)
		product += v1[i]*v2[i];
	return product;
}

///////////////////////////////////////////////////////////////
// calculate the length of the vector
///////////////////////////////////////////////////////////////

double CurrentsBase::VectorLength(double *v)
{
	return sqrt(ScalarProduct(v,v));
}

///////////////////////////////////////////////////////////////
// calculate the cos(angle) between vectors
///////////////////////////////////////////////////////////////

double CurrentsBase::CosOfAngleBetweenVectors(double *v1,double *v2)
{
	return ScalarProduct(v1,v2)/VectorLength(v1)/VectorLength(v2);
}

///////////////////////////////////////////////////////////////////////
// form the Hamiltonian matrix for interaction between Cu atoms
///////////////////////////////////////////////////////////////////////

void CurrentsBase::FormHamiltonianMatrix(doublecomplex *ap,double tau,double Eo,double Em)
{
	for (int j=0 ; j<NumberOfAtoms ; j++) // over all atoms in all included layers
	{
		for(int i=0 ; i<=j ; i++)
		{
			int index = i+j*(j+1)/2; // columnwise packing in a linear array

// diagonal elements are zero - to have degenerated orbitals (Sven's model)
			if(i==j)
			{
				ap[index].r = 0.;
				ap[index].i = 0.;
				continue;
			}
// if atoms are from different layers, element must be zero due to no interaction
// these are IDs of the Currents object layers, not AtomCoordinates object layers
			int index_i = GetAtomLayerID(i);
			int index_j = GetAtomLayerID(j);
			if(GetAtomLayerID(i) != GetAtomLayerID(j))
			{
				ap[index].r = 0.;
				ap[index].i = 0.;
				continue;
			}
// both atoms are from the same layer and with different numbers (nondiagonal element)

			double dst[3];  // in angstroms
			int jpos = GetAcIndex(j);  // returns the index of atom j in acoord
			int ipos = GetAcIndex(i);  // returns the index of atom i in acoord

			dst[0] = acoord->GetX(jpos) - acoord->GetX(ipos);
			dst[1] = acoord->GetY(jpos) - acoord->GetY(ipos);
			dst[2] = acoord->GetZ(jpos) - acoord->GetZ(ipos);
// atoms not nearest neighbours - matrix element is zero
			if(VectorLength(dst) > d->Get_cell_width_y()+0.1)  // in angstroms
			{
				ap[index].r = 0.;
				ap[index].i = 0.;
				continue;
			}
// atoms are nearest neighbours - calculate the element value
			double vectorPotential_j[3]; // vector potential at atom location 1
			double vectorPotential_i[3]; // vector potential at atom location 2

			vectorPotential_j[0] = 0.5*(acoord->GetZ(jpos)*
										acoord->GetMagneticField_y(jpos) -
										acoord->GetY(jpos)*
										acoord->GetMagneticField_z(jpos)
									   );
			vectorPotential_j[1] = 0.5*(acoord->GetX(jpos)*
										acoord->GetMagneticField_z(jpos) -
										acoord->GetZ(jpos)*
										acoord->GetMagneticField_x(jpos)
									   );
			vectorPotential_j[2] = 0.5*(acoord->GetY(jpos)*
										acoord->GetMagneticField_x(jpos) -
										acoord->GetX(jpos)*
										acoord->GetMagneticField_y(jpos)
									   );
			vectorPotential_i[0] = 0.5*(acoord->GetZ(ipos)*
										acoord->GetMagneticField_y(ipos) -
										acoord->GetY(ipos)*
										acoord->GetMagneticField_z(ipos)
									   );
			vectorPotential_i[1] = 0.5*(acoord->GetX(ipos)*
										acoord->GetMagneticField_z(ipos) -
										acoord->GetZ(ipos)*
										acoord->GetMagneticField_x(ipos)
									   );
			vectorPotential_i[2] = 0.5*(acoord->GetY(ipos)*
										acoord->GetMagneticField_x(ipos) -
										acoord->GetX(ipos)*
										acoord->GetMagneticField_y(ipos)
									   );
			double vp[3];
				
			for(int cnt=0 ; cnt<3 ; cnt++)
				vp[cnt] = vectorPotential_j[cnt] - vectorPotential_i[cnt];

			dst[0] = acoord->GetX(jpos) + acoord->GetX(ipos);
			dst[1] = acoord->GetY(jpos) + acoord->GetY(ipos);
			dst[2] = acoord->GetZ(jpos) + acoord->GetZ(ipos);

			double phaseFactor = ScalarProduct(vp,dst)*
									ANGSTROMS_TO_CM*
									ANGSTROMS_TO_CM*
									CHARGE/(2.*PLANCK*SPEED_OF_LIGHT);

			ap[index].r = cos(phaseFactor)*tau*tau/(Eo-Em);
			ap[index].i = -sin(phaseFactor)*tau*tau/(Eo-Em);
//				ap_bak[index].r = ap[index].r;
//				ap_bak[index].i = ap[index].i;
//				printf(" ap[%d %d] = (%g %g)\n",i,j,ap[index].r,ap[index].i);
		}
	}
}

