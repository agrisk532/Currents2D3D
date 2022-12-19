// Cu2DAtoms.cpp: implementation of the Cu2DAtoms class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Currents2D3D.h"
#include "Cu2DAtoms.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Cu2DAtoms::Cu2DAtoms()
{
	m_nCoordX = 0;
	m_nCoordY = 0;
	m_nSerialNumber = 0;
}


Cu2DAtoms::~Cu2DAtoms() {}

//////////////////////////////////////////////////////////////////////
// determines wh
bool Cu2DAtoms::IsMouseOver(POINT point)
{
	if(((point.x > m_nCoordX) && (point.x < m_nCoordX + m_nRectangleSize)) &&
	   ((point.y > m_nCoordY) && (point.y < m_nCoordY + m_nRectangleSize)))
			return true;
	else return false;
}

//////////////////////////////////////////////////////////////////////
//
void Cu2DAtoms::Plot(CDC* pDC)
{
	CRect rc;
	rc.SetRect(m_nCoordX,m_nCoordY,m_nCoordX+m_nRectangleSize,m_nCoordY-m_nRectangleSize);
	pDC->Ellipse(rc);
}

//////////////////////////////////////////////////////////////////////
// retuns the window coordinates of Cu atom center 
void Cu2DAtoms::GetCenter(CPoint* point)
{
	point->x = m_nCoordX + m_nRectangleSize / 2;
	point->y = m_nCoordY - m_nRectangleSize / 2;
    return;
}

