// Currents3D.h: interface for the Currents3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTS3D_H__143536A2_3E7E_11D3_B193_006008158370__INCLUDED_)
#define AFX_CURRENTS3D_H__143536A2_3E7E_11D3_B193_006008158370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "f2c.h"
#include "fileIO.h"
#include "CurrentsBase.h"

class AtomParameters;
class FieldGrid;

class Currents3D : public CurrentsBase
{
	DECLARE_DYNAMIC(Currents3D);

private:

	CDocument* pDoc; // general. Later in source it will be casted to the appropriate type

	AtomParameters *ap;
	int m_nElectronsRemoved; // doping parameter
	void Calculate3DCurrentsOnGrid(doublecomplex *z, FieldGrid *fg,	ReadOrWriteFieldToFile rw);
	void Current3DFieldInGridPoint(int iZIndex,	// Z coordinate index of the grid point
								  int iYIndex,	// Y coordinate index of the grid point
								  int iXIndex,	// X coordinate index of the grid point
								  FieldGrid *fg, // pointer to FieldGrid object
								  doublecomplex *z, // pointer to eigenvectors
								  float currentDensity[3] // array for storing current density components (x,y,z)
								 );
	char *fn; // file for dumping/reading point data

	FILE *out;
	FILE *in;

// writes the calculated file to disk using vtkStructuredPointsWriter
	void CloseOutFile() {fclose(out);}
	void CloseInFile() {fclose(in);}
	void OpenOutFile();
	void OpenInFile();

public:

	int m_nInitialFieldValueForRendering; 
// reference value for rendering of the field
// 0-255, calculated in the 'Currents3D'

	void SetAtomParameters(AtomParameters *aparm) {ap = aparm;}
	Currents3D(double imf) : CurrentsBase(imf) {}
	static Currents3D *New(double imf) {return new Currents3D(imf);}
	virtual ~Currents3D() {};
	void Calculate(const double tau,// Cu - O coupling
				   const double Eo,	// O energy
				   const double Em,	// Cu energy
				   FieldGrid *fg,	// pointer to the FieldGrid object
					ReadOrWriteFieldToFile rw
				  );
	bool Is3DCurrent() {return true;} // just to make base class polymorphic
	void SetDocument(CDocument* doc) {pDoc = doc;} // set pointer to the document object

	void SetElectronsRemoved(int electrons) {m_nElectronsRemoved = electrons;}
	int GetElectronsRemoved() {return m_nElectronsRemoved;}

};

#endif // !defined(AFX_CURRENTS3D_H__143536A2_3E7E_11D3_B193_006008158370__INCLUDED_)
