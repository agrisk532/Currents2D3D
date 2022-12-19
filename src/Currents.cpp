//////////////////////////////////////////////////////////////////////
// Currents.cpp: implementation of the Currents class.
// For Curents1D calculation
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Currents.h"
#include "Textvw.h"
#include "Currents2D3D.h"
#include "MainFrm.h"
#include "Child2DFrame.h"
#include "Child3DFrame.h"

IMPLEMENT_DYNAMIC(Currents,CurrentsBase);

//////////////////////////////////////////////////////////////////////////
// The main calculation function. It manages other calculation functions
// Calculate the Cu-Cu bond electrical currents
//////////////////////////////////////////////////////////////////////////

int Currents::CalculateCurrentsInBonds(const double tau,			// Cu - O coupling
						 const double Eo,			// O energy
						 const double Em,			// Cu energy
						 const bool doWithoutSelfConsistency	// indicates whether to do selfconsistent or single calculation of currents
						)
{
// returns the number of iterations
	char jobz = 'V'; // compute eigenvalues and eigenvectors
	char uplo = 'U'; // upper part of matrix packed

	int NumberOfElectrons = NumberOfAtoms - m_nElectronsRemoved;

	doublecomplex *ap = new doublecomplex[NumberOfAtoms*(NumberOfAtoms+1)/2];
//	doublecomplex *ap_bak = new doublecomplex[NumberOfAtoms*(NumberOfAtoms+1)/2]; // for test section only
	doublereal *w = new doublereal[NumberOfAtoms];
	doublecomplex *z = new doublecomplex[NumberOfAtoms*NumberOfAtoms];
	doublecomplex *work = new doublecomplex[2*NumberOfAtoms-1];
	doublereal *rwork = new doublereal[3*NumberOfAtoms-2];
	integer info;

	occupationMatrix = new char[NumberOfAtoms];
// distinguish between open and close shell cases (even or odd number of atoms in calculation)

	bool openShellCase = (NumberOfElectrons%2 == 0) ? false : true;
	int doublyOccupiedOrbitals = NumberOfElectrons/2;
	for(int i=0;i<NumberOfAtoms;i++) occupationMatrix[i] = 0;
	for(i=0;i<doublyOccupiedOrbitals;i++) occupationMatrix[i] = 2; // 4 electrons removed
	if(openShellCase) occupationMatrix[doublyOccupiedOrbitals] = 1;
	printf("\nOccupation matrix...\n");
	for(i=0;i<NumberOfAtoms;i++) printf("%d\n",occupationMatrix[i]);
// Output some text info in the text pane view
// distinguish between 2D and 3D cases which use different text view classes
// this is done by operating with base class pointers

	CWinApp* app = AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)app->GetMainWnd();
	CTextView* pTextView = GetTextPane();

	CString buffer;

	if(doWithoutSelfConsistency)
	{
		buffer = "Non-iterative current calculation";
		pTextView->AddLine(buffer);
	}
	else
	{
		buffer = "Iterative current calculation";
		pTextView->AddLine(buffer);
		buffer.Empty();
		buffer = "Rms error between two iterations :";
		pTextView->AddLine(buffer);
	}
//	pDoc->UpdateAllViews(NULL);

// max difference between sums of squared differences (over all bonds)
// of currents in in 2 subsequent iterations
	deltaCurrentLimit = 0.001;

	m_nNumberOfIterations = 1;
	while(m_nNumberOfIterations < 100)
	{
		FormHamiltonianMatrix(ap,tau,Eo,Em);
// diagonalize the complex matrix
		zhpev_(&jobz,&uplo,&NumberOfAtoms,ap,w,z,&NumberOfAtoms,work,rwork,&info);
		if(info != 0)
		{
			CString str;
			str.Format("info = %d in LAPACK _ZHPEV routine. Program stopped\n",info);
			AfxMessageBox(str);
			exit(0);
		}
		CalculateBondCurrents(z);
		if(doWithoutSelfConsistency) break; // do just single calculation without selfconsistency
		if (!ContinueIterations()) break;
		CalculateMagneticFieldOnAtoms();
		m_nNumberOfIterations++;
	}

	if(m_nNumberOfIterations == 100)
	{
		AfxMessageBox("Unable to achieve self consistency!");
		return -1;
	}

//	printf("Eigenvalues\n");
//	for(i=0;i<NumberOfAtoms;i++) printf("%f\n",w[i]);

	pTextView->AddLine(" ");
	buffer.Empty();

	buffer.Format("Eigenvalues :");
	pTextView->AddLine(buffer);
	buffer.Empty();

	for(i=0;i<NumberOfAtoms;i++)
	{
		char buffer[50];
		_gcvt(w[i],7,(char*)buffer);
		pTextView->AddLine(buffer); // adds a line to the end of the string list
	}

	char b[50];
	_gcvt(GetMaxCurrent(),7,b);
	pTextView->AddLine(" ");
	pTextView->AddLine("Maximal current :");
	pTextView->AddLine(b); // adds a line to the end of the string list

	delete [] ap;
	delete [] w;
	delete [] z;
	delete [] work;
	delete [] rwork;
	delete [] occupationMatrix;

	return m_nNumberOfIterations;
}

/////////////////////////////////////////////////////////////////////
// calculate the gauge origin from all layers involved in calculation
/////////////////////////////////////////////////////////////////////

void Currents::SetGaugeOrigin()
{
	double minimumX =  1.e100;
	double maximumX = -1.e100;
	double minimumY =  1.e100;
	double maximumY = -1.e100;
	double minimumZ =  1.e100;
	double maximumZ = -1.e100;

	for(int i=0 ; i<NumberOfLayers ; i++)
	{
		int start = StartOfLayer[i];
		int size = SizeOfLayer[i];

		for(int j=start ; j<start+size ; j++)
		{
			if(acoord->GetX(j) > maximumX) maximumX = acoord->GetX(j);
			if(acoord->GetX(j) < minimumX) minimumX = acoord->GetX(j);
			if(acoord->GetY(j) > maximumY) maximumY = acoord->GetY(j);
			if(acoord->GetY(j) < minimumY) minimumY = acoord->GetY(j);
			if(acoord->GetZ(j) > maximumZ) maximumZ = acoord->GetZ(j);
			if(acoord->GetZ(j) < minimumZ) minimumZ = acoord->GetZ(j);
		}
	}

	acoord->gaugeOrigin_x = (maximumX - minimumX)/2.;
	acoord->gaugeOrigin_y = (maximumY - minimumY)/2.;
	acoord->gaugeOrigin_z = (maximumZ - minimumZ)/2.;
}

/////////////////////////////////////////////////////////////////////
// Calculate the current density and assign it to bond objects
/////////////////////////////////////////////////////////////////////

void Currents::CalculateBondCurrents(doublecomplex *z)
{
	double dampingFactor = 0.;
	double maxDifference = 0.;

	for(int i=0;i<NumberOfBonds;i++)
	{
		int atom1 = bonds[i]->GetAtom1();	// atom1 < atom2 always !
		int atom2 = bonds[i]->GetAtom2();	// atom numbering as in AtomCoordinates class
// atom1 and atom2 must be converted to the same numbering as in z[]!!!!
// all intermediate (only plot) layer sizes must be subtracted!!!!
		atom1 -= bonds[i]->GetExcludedLayerSize();
		atom2 -= bonds[i]->GetExcludedLayerSize();
		bonds[i]->SetCurrentDirection_previous(bonds[i]->GetCurrentDirection());
		bonds[i]->SetCurrentMagnitude_previous(bonds[i]->GetCurrentMagnitude());

		double current = 0.;
// current is assumed positive when going from atom with smaller number
// to atom with larger number (positive for current from atom1 to atom2)
		bonds[i]->SetCurrentDirection(true); 
		for(int j=0;j<NumberOfAtoms;j++)
			current += 2.*(z[atom1+j*NumberOfAtoms].i*z[atom2+j*NumberOfAtoms].r -
						z[atom1+j*NumberOfAtoms].r*z[atom2+j*NumberOfAtoms].i)*
						occupationMatrix[j];
		if(current < 0.) bonds[i]->SetCurrentDirection(false);

//		printf("atoms %d %d current %g\n",atom1,atom2,current);

		double value = PLANCK/(2.*ELECTRON_MASS)*current*(1.0-dampingFactor)+
							dampingFactor*bonds[i]->GetCurrentMagnitude_previous();

		bonds[i]->SetCurrentMagnitude(value);
		double diff = bonds[i]->GetCurrentMagnitude() - bonds[i]->GetCurrentMagnitude_previous();
		bonds[i]->SetDifferenceInCurrents(diff);
//		printf("current difference = %fl\n",diff);
	}
}

////////////////////////////////////////////////////////////////
// calculates the magnetic field in grid points
////////////////////////////////////////////////////////////////

void Currents::CalculateMagneticFieldOnGrid(FieldGrid *fg)
{
	double scalarMin =  1e100;
	double scalarMax = -1e100;
	float field[3]; // contains the magnetic or electrical current field vector
	int dimX = fg->GetGridDimensionX();
	int dimY = fg->GetGridDimensionY();
	int dimZ = fg->GetGridDimensionZ();
	float *scal = new float[dimX*dimY*dimZ];
	float fieldValue;

// loops over all grid points
	long offset;
	for(long iZIndex=0 ; iZIndex < fg->GetGridDimensionZ() ; iZIndex++)
	{
		long ZOffset = iZIndex*fg->GetGridDimensionX()*fg->GetGridDimensionY();
		for(long iYIndex=0 ; iYIndex < fg->GetGridDimensionY() ; iYIndex++)
		{
			long YOffset = iYIndex*fg->GetGridDimensionX();
			for(long iXIndex=0 ; iXIndex < fg->GetGridDimensionX() ; iXIndex++)
			{
				offset = ZOffset + YOffset + iXIndex;
				MagneticFieldInGridPoint(iZIndex,iYIndex,iXIndex,fg,field);
//				for(int i = 0 ; i<3 ; i++) printf("  %g",field[i]);
//				printf("\n");
				fg->GetDataVectors()->SetVector(offset,field);
				fieldValue = 0.;
				for(int i=0 ; i<3 ; i++) fieldValue += field[i]*field[i];
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
	printf("Number of grid points = %d\n",fg->GetGridDimensionX()*fg->GetGridDimensionY()*
		fg->GetGridDimensionZ());
	int points = fg->GetStructuredPoints()->GetNumberOfPoints();
	unsigned char value;
	for(int i=0 ; i<points ; i++)
	{
		value = (scal[i]-scalarMin)/(scalarMax-scalarMin)*255;
//		printf("%d %d\n",i,value);
		fg->GetDataScalars()->SetScalar(i,value);
	}
// reference value for the rendering
	m_nInitialFieldValueForRendering = 
		(initialMagneticField-scalarMin)/(scalarMax-scalarMin)*255;

	delete [] scal;
}

//////////////////////////////////////////////////////////////////////
// Calculate / update magnetic field on atoms
//////////////////////////////////////////////////////////////////////

void Currents::CalculateMagneticFieldOnAtoms()
{
	for(int k=0 ; k<NumberOfLayers ; k++)  // loop over all layers included in curr calculation
	{
		int start = StartOfLayer[k];
		int size = SizeOfLayer[k];

		for(int atom=start ; atom<start+size ; atom++) // numbering as in AtomCoordinates class
		{
			acoord->SetMagneticField_x(atom,0.);
			acoord->SetMagneticField_y(atom,0.);
			acoord->SetMagneticField_z(atom,initialMagneticField);

			for(int bond=0 ; bond<NumberOfBonds ; bond++) // loop over all bonds in calculation
			{
				int bondAtom1 = bonds[bond]->GetAtom1(); // bondAtom1 < bondAtom2 always !
				int bondAtom2 = bonds[bond]->GetAtom2();
				if( atom == bondAtom1 || atom == bondAtom2) continue; // atom in bond

// calculate the magnetic field on atom

// calculate the distance between the atom and the bond
				double distance = CalcDistPointToBond(atom,bond); // in angstroms
// exclude atoms which are on one line with a bond
				if(fabs(distance) < 0.01) continue;

// calculate the field on atom from bond and store components in AtomCoordinates
// field is calculated from the formula B = I*(sin(beta) + sin(alpha)) / distance
// what is the Biot-Savart law application to a linear current fragment
//
// find the angles alpha and beta : actually I calculate not sin(alpha) but cos(90-alpha)
// from the scalar product

				double v1[3]; // vector from bondAtom1 to the atom
				double v2[3]; // vector from bondAtom2 to the atom
				double v12[3]; // vector from bondAtom1 to bondAtom2
				
				v1[0] = acoord->GetX(atom) - acoord->GetX(bondAtom1);
				v1[1] = acoord->GetY(atom) - acoord->GetY(bondAtom1);
				v1[2] = acoord->GetZ(atom) - acoord->GetZ(bondAtom1);
				v2[0] = acoord->GetX(atom) - acoord->GetX(bondAtom2);
				v2[1] = acoord->GetY(atom) - acoord->GetY(bondAtom2);
				v2[2] = acoord->GetZ(atom) - acoord->GetZ(bondAtom2);
				v12[0] = acoord->GetX(bondAtom2) - acoord->GetX(bondAtom1);
				v12[1] = acoord->GetY(bondAtom2) - acoord->GetY(bondAtom1);
				v12[2] = acoord->GetZ(bondAtom2) - acoord->GetZ(bondAtom1);

				double sinAlpha = CosOfAngleBetweenVectors(v1,v12);
				double sinBeta  = CosOfAngleBetweenVectors(v2,v12);

// the magnetic field magnitude

				double MagneticFieldOnAtom = bonds[bond]->GetCurrentMagnitude() /
										(distance * ANGSTROMS_TO_CM * SPEED_OF_LIGHT) *
										fabs(sinAlpha - sinBeta);
// direction of the magnetic field is (B = dl x r)
// TAKE INTO ACCOUNT THE DIRECTION OF CURRENT IN A BOND!

				double MagneticFieldDirection[3];
				VectorProduct(v12,v1,MagneticFieldDirection); // (dl x r)

// normalize field direction

				double length = VectorLength(MagneticFieldDirection);
//				if(bonds[bond].GetCurrentDirection() == false) length = -length;

				for(int i=0 ; i<3 ; i++) MagneticFieldDirection[i] /= length;

				acoord->SetMagneticField_x(atom,acoord->GetMagneticField_x(atom) +
						MagneticFieldDirection[0]*MagneticFieldOnAtom);
				acoord->SetMagneticField_y(atom,acoord->GetMagneticField_y(atom) +
						MagneticFieldDirection[1]*MagneticFieldOnAtom);
				acoord->SetMagneticField_z(atom,acoord->GetMagneticField_z(atom) +
						MagneticFieldDirection[2]*MagneticFieldOnAtom);
			}
		}
	}
}


///////////////////////////////////////////////////////////////
// determine whether to continue the iterations or not
///////////////////////////////////////////////////////////////

bool Currents::ContinueIterations()
{
	double rms = 0.;
	double diff = 0.;

	for(int bond=0 ; bond<NumberOfBonds ; bond++) // loop over all bonds in calculation
	{
		diff = bonds[bond]->GetDifferenceInCurrents();
		rms += diff*diff;
	}

	rms = sqrt(rms);

	CTextView* pTextView = GetTextPane();

	char buffer[50];
	_gcvt(rms,5,(char*)buffer);

	pTextView->AddLine(buffer); // adds a line to the end of the string list
//	pDoc->UpdateAllViews(NULL);

	if(rms > deltaCurrentLimit) return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////
// returns the text pane for printing out text

CTextView* Currents::GetTextPane()
{
	CWinApp* app = AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)app->GetMainWnd();
	CMDIChildWnd* pWnd = pFrame->MDIGetActive();
	CSplitterWnd* pSplitter;

	if(pWnd->IsKindOf(RUNTIME_CLASS(CChild2DFrame)))
	{
		CChild2DFrame* pFrm = (CChild2DFrame*)pWnd;
		pSplitter = (CSplitterWnd*)(&pFrm->m_wndSplitter);
	}

	if(pWnd->IsKindOf(RUNTIME_CLASS(CChild3DFrame)))
	{
		CChild3DFrame* pFrm = (CChild3DFrame*)pWnd;
		pSplitter = (CSplitterWnd*)(&pFrm->m_wndSplitter);
	}

	CTextView* pTextView = (CTextView*) pSplitter->GetPane(0,1);

	return pTextView;
}


/////////////////////////////////////////////////////////////////
// calculate the magnetic field in FieldGrid *fg point ix,iy,iz
// field is returned in the dimension magneticField[3]
/////////////////////////////////////////////////////////////////

void Currents::MagneticFieldInGridPoint(long iz,long iy,long ix,FieldGrid *fg,
										  float magneticField[3])
{
	double FieldValueX = 0.; // magnetic field B value in a point
	double FieldValueY = 0.;
	double FieldValueZ = initialMagneticField;
// point coordinates
	double pointXCoordinate = fg->GetGridOriginX() + ix * fg->GetGridSpacingX();
	double pointYCoordinate = fg->GetGridOriginY() + iy * fg->GetGridSpacingY();
	double pointZCoordinate = fg->GetGridOriginZ() + iz * fg->GetGridSpacingZ();

// calculate magnetic field B in a point

	for(int bond=0 ; bond<NumberOfBonds ; bond++) // loop over all bonds in calculation
	{
		int bondAtom1 = bonds[bond]->GetAtom1(); // bondAtom1 < bondAtom2 always !
		int bondAtom2 = bonds[bond]->GetAtom2();

// calculate the distance between the atom and the bond in angstroms
		double distance = CalcDistPointToBond(pointXCoordinate,
											  pointYCoordinate,
											  pointZCoordinate,
											  bond); 
// exclude atoms which are on one line with a bond
		if(fabs(distance) < 0.01) continue;

// calculate the field in the point from a bond from the formula
// B = I*(sin(beta) + sin(alpha)) / distance
// what is the Biot-Savart law application to a linear current fragment
//
// find the angles alpha and beta : actually I calculate not sin(alpha) but cos(90-alpha)
// from the scalar product

		double v1[3]; // vector from bondAtom1 to the atom
		double v2[3]; // vector from bondAtom2 to the atom
		double v12[3]; // vector from bondAtom1 to bondAtom2
	
		v1[0] = pointXCoordinate - acoord->GetX(bondAtom1);
		v1[1] = pointYCoordinate - acoord->GetY(bondAtom1);
		v1[2] = pointZCoordinate - acoord->GetZ(bondAtom1);
		v2[0] = pointXCoordinate - acoord->GetX(bondAtom2);
		v2[1] = pointYCoordinate - acoord->GetY(bondAtom2);
		v2[2] = pointZCoordinate - acoord->GetZ(bondAtom2);
		v12[0] = acoord->GetX(bondAtom2) - acoord->GetX(bondAtom1);
		v12[1] = acoord->GetY(bondAtom2) - acoord->GetY(bondAtom1);
		v12[2] = acoord->GetZ(bondAtom2) - acoord->GetZ(bondAtom1);

		double sinAlpha = CosOfAngleBetweenVectors(v1,v12);
		double sinBeta  = CosOfAngleBetweenVectors(v2,v12);

// the magnetic field magnitude

		double MagneticFieldInPoint = bonds[bond]->GetCurrentMagnitude() /
								(distance * ANGSTROMS_TO_CM * SPEED_OF_LIGHT) *
								fabs(sinAlpha - sinBeta);
// direction of the magnetic field is (B = dl x r)
// TAKE INTO ACCOUNT THE DIRECTION OF CURRENT IN A BOND!

		double MagneticFieldDirection[3];
		VectorProduct(v12,v1,MagneticFieldDirection); // (dl x r)

// normalize field direction

		double length = VectorLength(MagneticFieldDirection);
//	if(bonds[bond].GetCurrentDirection() == false) length = -length;

		for(int i=0 ; i<3 ; i++) MagneticFieldDirection[i] /= length;

		FieldValueX += MagneticFieldDirection[0]*MagneticFieldInPoint;
		FieldValueY += MagneticFieldDirection[1]*MagneticFieldInPoint;
		FieldValueZ += MagneticFieldDirection[2]*MagneticFieldInPoint;
	}
	magneticField[0] = FieldValueX;
	magneticField[1] = FieldValueY;
	magneticField[2] = FieldValueZ;

	return;
}

///////////////////////////////////////////////////////////////////
// Calculate the distance between the atom and bond
///////////////////////////////////////////////////////////////////

double Currents::CalcDistPointToBond(int atom,int bond)
{
	double bondDirectionVector[3]; // of the bond
	bondDirectionVector[0] = acoord->GetX(bonds[bond]->GetAtom2()) -
									acoord->GetX(bonds[bond]->GetAtom1());
	bondDirectionVector[1] = acoord->GetY(bonds[bond]->GetAtom2()) -
									acoord->GetY(bonds[bond]->GetAtom1());
	bondDirectionVector[2] = acoord->GetZ(bonds[bond]->GetAtom2()) -
									acoord->GetZ(bonds[bond]->GetAtom1());

// vector from the atom to the arbitrary point on a bond (bondAtom1)

	double vect[3];
	vect[0] = acoord->GetX(atom) - acoord->GetX(bonds[bond]->GetAtom1());
	vect[1] = acoord->GetY(atom) - acoord->GetY(bonds[bond]->GetAtom1());
	vect[2] = acoord->GetZ(atom) - acoord->GetZ(bonds[bond]->GetAtom1());

// form the vector product

	double vp[3];
	VectorProduct(bondDirectionVector,vect,vp);

// calculate the distance

	return VectorLength(vp)/VectorLength(bondDirectionVector);
}

////////////////////////////////////////////////////////////////////
// Calculate the distance between the point and bond
////////////////////////////////////////////////////////////////////

double Currents::CalcDistPointToBond(double xc,
									 double yc,
									 double zc,
									 int bond)
{
	double bondDirectionVector[3]; // of the bond
	bondDirectionVector[0] = acoord->GetX(bonds[bond]->GetAtom2()) -
									acoord->GetX(bonds[bond]->GetAtom1());
	bondDirectionVector[1] = acoord->GetY(bonds[bond]->GetAtom2()) -
									acoord->GetY(bonds[bond]->GetAtom1());
	bondDirectionVector[2] = acoord->GetZ(bonds[bond]->GetAtom2()) -
									acoord->GetZ(bonds[bond]->GetAtom1());

// vector from the atom to the arbitrary point on a bond (bondAtom1)

	double vect[3];
	vect[0] = xc - acoord->GetX(bonds[bond]->GetAtom1());
	vect[1] = yc - acoord->GetY(bonds[bond]->GetAtom1());
	vect[2] = zc - acoord->GetZ(bonds[bond]->GetAtom1());

// form the vector product

	double vp[3];
	VectorProduct(bondDirectionVector,vect,vp);

// calculate the distance

	return VectorLength(vp)/VectorLength(bondDirectionVector);
}



/////////////////////////////////////////////////////////////////
//  returns the maximal current (absolute value) in bonds
/////////////////////////////////////////////////////////////////

double Currents::GetMaxCurrent()
{
	double maxCurrent = 0.;
	for(int i=0 ; i<NumberOfBonds ; i++)
	{
		double currentMagnitude = fabs(bonds[i]->GetCurrentMagnitude());
		if(currentMagnitude > maxCurrent) maxCurrent = currentMagnitude;
	}
	return maxCurrent;
}

///////////////////////////////////////////////////////////////////////
// Multiply a matrix by a vector
///////////////////////////////////////////////////////////////////////
/*
void MatXVec(int n,doublecomplex *mat, doublecomplex *vec, doublecomplex *res)
{
	int index;

	for(int i=0 ; i<n ; i++) // matrix row
	{
		res[i].r = 0.0;
		res[i].i = 0.0;

		for(int j=0 ; j<n ; j++)  // matrix column
		{
			index = (i<=j) ? i+(j+1)*j/2 : j+(i+1)*i/2;
			if(i<=j)
			{
				res[i].r += mat[index].r * vec[j].r - mat[index].i * vec[j].i;
				res[i].i += mat[index].i * vec[j].r + mat[index].r * vec[j].i;
			}
			else
			{
				res[i].r += mat[index].r * vec[j].r + mat[index].i * vec[j].i;
				res[i].i += -mat[index].i * vec[j].r + mat[index].r * vec[j].i;
			}

		}
	}
}
*/
