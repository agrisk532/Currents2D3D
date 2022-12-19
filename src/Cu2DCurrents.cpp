// Cu2DCurrents.cpp: implementation of the Cu2DCurrents class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Currents2D3D.h"
#include "Cu2DCurrents.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cu2DCurrents::Cu2DCurrents()
{
	m_nAtom1Center.x = 0;
	m_nAtom1Center.y = 0;
	m_nAtom2Center.x = 0;
	m_nAtom2Center.y = 0;
	m_nCurrentMagnitude = 0;
	m_nCurrentDirection = 0;
	m_nCuCuDistance = 0; // in pixels
	m_nWidth = 0;
}

Cu2DCurrents::~Cu2DCurrents()
{

}

///////////////////////////////////////////////////////////////////////
// 2D current plotting engine

void Cu2DCurrents::Plot(CDC* pDC)
{
// width of line in pixels
	m_nWidth = fabs(m_nCurrentMagnitude)/m_nMaxCurrentValue*m_nMaxCurrentWidth;
	if(!m_nWidth) return;

	CPen pen;
	CPen* ppenOld;
	pen.CreatePen(PS_SOLID,m_nWidth,RGB(0,0,0));
	ppenOld = pDC->SelectObject(&pen);
	CalculateArrowPoints(); // arrow head point calculation
	pDC->MoveTo(m_nAtom1Center);
	pDC->LineTo(m_nAtom2Center);
	pDC->Polyline(m_ArrowPoints,3);
	pDC->SelectObject(ppenOld);
}

//////////////////////////////////////////////////////////////////////
// Calculate arrow points

void Cu2DCurrents::CalculateArrowPoints()
{
// Arrow center
	m_ArrowPoints[1].x = (m_nAtom1Center.x + m_nAtom2Center.x) / 2;
	m_ArrowPoints[1].y = (m_nAtom1Center.y + m_nAtom2Center.y) / 2;

// distinguish between horizontal and vertical bonds
	if(abs(m_nAtom2Center.y - m_nAtom1Center.y) < 2 ) // in screen pixels
	{
// horizontal bond
		// arrow head calculation factor
//	int offset = m_nArrowFactor * m_nWidth;
		int offsetX = m_nArrowLength*cos(m_nArrowAngle*3.1415926/180);
// offsetY is negative because of the MM_LOENGLISH mapping mode
		int offsetY = - m_nArrowLength*sin(m_nArrowAngle*3.1415926/180);

		if(m_nCurrentDirection)
		{
// positive current (going right)
			m_ArrowPoints[1].x += offsetX / 2.;
// upper part of arrow
			m_ArrowPoints[0].x = m_ArrowPoints[1].x - offsetX;
			m_ArrowPoints[0].y = m_ArrowPoints[1].y - offsetY;
// lower part of arrow
			m_ArrowPoints[2].x = m_ArrowPoints[1].x - offsetX;
			m_ArrowPoints[2].y = m_ArrowPoints[1].y + offsetY;
		}
		else
		{
// negative current (going left)
			m_ArrowPoints[1].x -= offsetX / 2.;
// upper part of arrow
			m_ArrowPoints[0].x = m_ArrowPoints[1].x + offsetX;
			m_ArrowPoints[0].y = m_ArrowPoints[1].y - offsetY;
// lower part of arrow
			m_ArrowPoints[2].x = m_ArrowPoints[1].x + offsetX;
			m_ArrowPoints[2].y = m_ArrowPoints[1].y + offsetY;
		}
	}
	else
		if(abs(m_nAtom2Center.x - m_nAtom1Center.x) < 2 ) // in screen pixels
		{
// vertical bond
			// arrow head calculation factor
//	int offset = m_nArrowFactor * m_nWidth;
		int offsetX = m_nArrowLength*sin(m_nArrowAngle*3.1415926/180);
		int offsetY = - m_nArrowLength*cos(m_nArrowAngle*3.1415926/180);

			if(m_nCurrentDirection)
			{
// positive current (going down)
				m_ArrowPoints[1].y += offsetY / 2.;
// left part of arrow
				m_ArrowPoints[0].x = m_ArrowPoints[1].x - offsetX;
				m_ArrowPoints[0].y = m_ArrowPoints[1].y - offsetY;
// right part of arrow
				m_ArrowPoints[2].x = m_ArrowPoints[1].x + offsetX;
				m_ArrowPoints[2].y = m_ArrowPoints[1].y - offsetY;
			}
			else
			{
// negative current (going up)
				m_ArrowPoints[1].y -= offsetY / 2.;
// left part of arrow
				m_ArrowPoints[0].x = m_ArrowPoints[1].x - offsetX;
				m_ArrowPoints[0].y = m_ArrowPoints[1].y + offsetY;
// right part of arrow
				m_ArrowPoints[2].x = m_ArrowPoints[1].x + offsetX;
				m_ArrowPoints[2].y = m_ArrowPoints[1].y + offsetY;
			}
		}
	else 
	{
		AfxMessageBox("Error in bond assignment Cu2DCurrents::CalculateArrowPoints()",
			MB_OK,0);
		exit(0);
	}
}
