//////////////////////////////////////////////////////////////////////
//
// Currents3D.cpp: implementation of the Currents3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FieldGrid.h"
#include "Currents3D.h"
#include "AtomParameters.h"
#include <stdio.h>


IMPLEMENT_DYNAMIC(Currents3D,CurrentsBase);

//////////////////////////////////////////////////////////////////////////
// The main calculation function. It manages other calculation functions
// Calculate the Cu-Cu bond electrical currents
//////////////////////////////////////////////////////////////////////////

void Currents3D::Calculate(const double tau,			// Cu - O coupling
							const double Eo,			// O energy
							const double Em,			// Cu energy
							FieldGrid *fg,				// pointer to the FieldGrid object
							ReadOrWriteFieldToFile rw	// 
						  )
{
	char jobz = 'V'; // compute eigenvalues and eigenvectors
	char uplo = 'U'; // upper part of matrix packed

	fn = "Curr3D.txt";

	int NumberOfElectrons = NumberOfAtoms - m_nElectronsRemoved;

	doublecomplex *z = new doublecomplex[NumberOfAtoms*NumberOfAtoms];

	occupationMatrix = new char[NumberOfAtoms];
// distinguish between open and close shell cases (even or odd number of atoms in calculation)
	bool openShellCase = (NumberOfElectrons%2 == 0) ? false : true;
	int doublyOccupiedOrbitals = NumberOfElectrons/2;
	for(int i=0;i<NumberOfAtoms;i++) occupationMatrix[i] = 0;
	for(i=0;i<doublyOccupiedOrbitals;i++) occupationMatrix[i] = 2;
	if(openShellCase) occupationMatrix[doublyOccupiedOrbitals] = 1;
	printf("\nOccupation matrix...\n");
	for(i=0;i<NumberOfAtoms;i++) printf("%d\n",occupationMatrix[i]);

// calculation section

	if(rw == WriteFieldToFile)
	{
		doublecomplex *ap = new doublecomplex[NumberOfAtoms*(NumberOfAtoms+1)/2];
		doublereal *w = new doublereal[NumberOfAtoms];
		doublecomplex *work = new doublecomplex[2*NumberOfAtoms-1];
		doublereal *rwork = new doublereal[3*NumberOfAtoms-2];
		integer info;

		FormHamiltonianMatrix(ap,tau,Eo,Em);
// diagonalize the complex matrix
		zhpev_(&jobz,&uplo,&NumberOfAtoms,ap,w,z,&NumberOfAtoms,work,rwork,&info);
		if(info != 0)
		{
			printf("info = %d in ZHPEV (complex matrix diagonalization LAPACK routine)\n \
				Program stopped\n",info);
			exit(0);
		}

		printf("Eigenvalues\n");
		for(i=0;i<NumberOfAtoms;i++) printf("%f\n",w[i]);

		delete [] ap;
		delete [] w;
		delete [] work;
		delete [] rwork;

		OpenOutFile();
	}

	else // for reading
		OpenInFile();

	Calculate3DCurrentsOnGrid(z,fg,rw);  // 3D electrical current field

	if(rw == WriteFieldToFile)
		CloseOutFile();
	else
		CloseInFile();

//	for( i=0;i<NumberOfAtoms;i++)
//	{
//		printf("Eigenvector %d\n\n",i);
//		for(int j=0;j<NumberOfAtoms;j++)
//		{
//			index = i*NumberOfAtoms + j;
//			printf("%f %f\n",z[index].r,z[index].i);
//		}
//	}

	delete [] z;
	delete [] occupationMatrix;
}

////////////////////////////////////////////////////////////////
// calculates the electrical currents in grid points
////////////////////////////////////////////////////////////////

void Currents3D::Calculate3DCurrentsOnGrid(doublecomplex *z, FieldGrid *fg,
										   ReadOrWriteFieldToFile rw)
{
	double scalarMin =  1e100;
	double scalarMax = -1e100;
	float field[3]; // contains the magnetic or electrical current field vector
	int dimX = fg->GetGridDimensionX();
	int dimY = fg->GetGridDimensionY();
	int dimZ = fg->GetGridDimensionZ();
	int dimscal = dimX*dimY*dimZ;
	float *scal = new float[dimscal];
	float *vect = new float[3*dimscal]; // buffer for storing vectors for input/output
	float fieldValue;
	printf("Number of grid points = %d\n",dimscal);

	if(rw == ReadFieldFromFile)
	{
		fread(vect,sizeof(float),3*dimscal,in);
		printf("Read from file done...\n");
	}

// loops over all grid points
	long offset;
	for(long iZIndex=0 ; iZIndex < dimZ ; iZIndex++)
	{
		printf("%f percent done\n",(float)iZIndex/(float)dimZ*100.);
		long ZOffset = iZIndex*fg->GetGridDimensionX()*fg->GetGridDimensionY();
		for(long iYIndex=0 ; iYIndex < dimY ; iYIndex++)
		{
			long YOffset = iYIndex*fg->GetGridDimensionX();
			for(long iXIndex=0 ; iXIndex < dimX ; iXIndex++)
			{
				offset = ZOffset + YOffset + iXIndex;
				if(rw == WriteFieldToFile)
				{
					Current3DFieldInGridPoint(iZIndex,iYIndex,iXIndex,fg,z,field);
//					out.write((char*)field,sizeof(field));
					for(int i=0 ; i<3 ; i++) vect[3*offset+i] = field[i];
				}
				else  // read from file
				{
//					in.read((char*)field,sizeof(field));
					for(int i=0 ; i<3 ; i++) field[i] = vect[3*offset+i];
				}
//				for(int i = 0 ; i<3 ; i++) printf("  %g",field[i]);
//				printf("\n");
				fg->GetDataVectors()->SetVector(offset,field);
				fieldValue = 0.;
				for( int i=0 ; i<3 ; i++) fieldValue += field[i]*field[i];
				fieldValue = sqrt(fieldValue);
				if(fieldValue < scalarMin) scalarMin = fieldValue;
				if(fieldValue > scalarMax) scalarMax = fieldValue;
				scal[offset] = fieldValue;
			}
		}
	}
	fg->SetScalarMin(scalarMin);
	fg->SetScalarMax(scalarMax);
	printf("scalarMin = %g\nscalarMax = %g\n",scalarMin,scalarMax);
	int points = fg->GetStructuredPoints()->GetNumberOfPoints();
	printf("Number of grid points = %d\n",points);

	unsigned char value;
	for(int i=0 ; i<points ; i++)
	{
		value = (scal[i]-scalarMin)/(scalarMax-scalarMin)*255;
//		printf("%d %d\n",i,value);
		fg->GetDataScalars()->SetScalar(i,value);
	}
// now set the reference value for the initial magnetic field
// coloring will be white for it.
// weaker fields in blue, stronger in red
// later it will be read from the 'Currents3DView'

	m_nInitialFieldValueForRendering = 
		(initialMagneticField-scalarMin)/(scalarMax-scalarMin)*255;

	if(rw == WriteFieldToFile) fwrite(vect,sizeof(float),3*dimscal,out);

	delete [] scal;
	delete [] vect;
}

//////////////////////////////////////////////////////////////////////////
// calculate the electrical current in a grid point in 3D space
//////////////////////////////////////////////////////////////////////////

void Currents3D::Current3DFieldInGridPoint(int iZIndex,	// Z coordinate index of the grid point
								  int iYIndex,	// Y coordinate index of the grid point
								  int iXIndex,	// X coordinate index of the grid point
								  FieldGrid *fg, // pointer to FieldGrid object
								  doublecomplex *z, // pointer to eigenvectors
								  float currentDensity[3] // array for storing current density components (x,y,z)
								 )
{
	double pointCoordinates[3]; // in angstroms
	pointCoordinates[0] = fg->GetGridOriginX() + iXIndex * fg->GetGridSpacingX();
	pointCoordinates[1] = fg->GetGridOriginY() + iYIndex * fg->GetGridSpacingY();
	pointCoordinates[2] = fg->GetGridOriginZ() + iZIndex * fg->GetGridSpacingZ();

	for(int i=0 ; i<3 ; i++) currentDensity[i] = 0.;

	for( i=0; i<NumberOfAtoms ; i++)
	{
		int atom1 = GetAcIndex(i); // atom number as in AtomCoordinates
		for(int j = 0 ; j < NumberOfAtoms ; j++)
		{
			int atom2 = GetAcIndex(j); // atom number as in AtomCoordinates
			double bondOrder = 0.;
			for(int k=0;k<NumberOfAtoms;k++)
			{
				bondOrder += 2.*(z[i+k*NumberOfAtoms].i*z[j+k*NumberOfAtoms].r -
								z[i+k*NumberOfAtoms].r*z[j+k*NumberOfAtoms].i)*
								occupationMatrix[k];
			}

			double AOGradients[3];	// holds AO gradients
			double AOValue = ap->GetAOValue(atom1,pointCoordinates);
			ap->GetAOGradients(atom2,pointCoordinates,AOGradients);	// fill AOGradients array

			currentDensity[0] += PLANCK/(2.*ELECTRON_MASS)*bondOrder *
								AOValue * AOGradients[0];

			currentDensity[1] += PLANCK/(2.*ELECTRON_MASS)*bondOrder *
								AOValue * AOGradients[1];

			currentDensity[2] += PLANCK/(2.*ELECTRON_MASS)*bondOrder *
								AOValue * AOGradients[2];
		}
	}
// just for streamTube generation for plotting. If values too small, it crashes...
	for(i=0 ; i<3 ; i++) currentDensity[i] *= 1.e5;
	
	return;
}
///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////

void Currents3D::OpenOutFile()
{
	out = fopen(fn,"wb");
	if(!out) AfxMessageBox("Cannot open Output file\n");
	else printf("Output File opened for writing\n");
}


////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void Currents3D::OpenInFile()
{
	in = fopen(fn,"rb");
	if(!in) AfxMessageBox("Cannot open Input file\n");
	else printf("Input File opened for reading\n");
}

