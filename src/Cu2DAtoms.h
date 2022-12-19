// Cu2DAtoms.h: interface for the Cu2DAtoms class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CU2DATOMS_H__5D2F9D45_8F74_11D3_B1EC_005004567AD4__INCLUDED_)
#define AFX_CU2DATOMS_H__5D2F9D45_8F74_11D3_B1EC_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cu2DAtomsBase.h"

///////////////////////////////////////////////////////////////
// This class keeps information about 2D Cu atoms

class Cu2DAtoms : public Cu2DAtomsBase
{

protected:

	int m_nCoordX;	// window coordinates of the upper left corner of the bounding rectangle
	int m_nCoordY;
	int m_nSerialNumber; // ID of the object

public:

	Cu2DAtoms();
	virtual ~Cu2DAtoms();
	void SetCoordX(int cx) {m_nCoordX = cx;}	// window coordinates in pixels
	void SetCoordY(int cy) {m_nCoordY = cy;}
	int GetCoordX() {return m_nCoordX;}
	int GetCoordY() {return m_nCoordY;}
	bool IsMouseOver(POINT point);
	void Plot(CDC* pDC);
	void GetCenter(CPoint* point);	// returns the center of atom in CPoint point
	void SetSerialNumber(int number) {m_nSerialNumber = number;}

};

#endif // !defined(AFX_CU2DATOMS_H__5D2F9D45_8F74_11D3_B1EC_005004567AD4__INCLUDED_)
