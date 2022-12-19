// Cu2DCurrents.h: interface for the Cu2DCurrents class.
//
// This class plots arrows for 2D currents
// At present orientation only along x,y axes.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CU2DCURRENTS_H__5D2F9D46_8F74_11D3_B1EC_005004567AD4__INCLUDED_)
#define AFX_CU2DCURRENTS_H__5D2F9D46_8F74_11D3_B1EC_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cu2DCurrentsBase.h"

class Cu2DCurrents : public Cu2DCurrentsBase
{

private:

	int m_nCuCuDistance; // in pixels
	CPoint m_nAtom1Center;	// atom of the bond. In screen x,y coordinates
	CPoint m_nAtom2Center;
	double m_nCurrentMagnitude;
	bool m_nCurrentDirection;
	CPoint m_ArrowPoints[3];	// array of points for arrow ploting (in window coordinates)
	int m_nWidth;	// width of the current rectangle in pixels
	

public:
	Cu2DCurrents();
	virtual ~Cu2DCurrents();
	void SetAtom1Center(CPoint atom) {m_nAtom1Center = atom;}
	void SetAtom2Center(CPoint atom) {m_nAtom2Center = atom;}
	void SetCuCuDistance(int dist) {m_nCuCuDistance = dist;}
	void SetCurrentMagnitude(double current) {m_nCurrentMagnitude = current;}
	void SetCurrentDirection(bool direction) {m_nCurrentDirection = direction;}
	void CalculateArrowPoints();
	void Plot(CDC* pDC);
};

#endif // !defined(AFX_CU2DCURRENTS_H__5D2F9D46_8F74_11D3_B1EC_005004567AD4__INCLUDED_)
