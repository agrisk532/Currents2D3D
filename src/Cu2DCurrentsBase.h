// Cu2DCurrentsBase.h: interface for the Cu2DCurrentsBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CU2DCURRENTSBASE_H__5D2F9D47_8F74_11D3_B1EC_005004567AD4__INCLUDED_)
#define AFX_CU2DCURRENTSBASE_H__5D2F9D47_8F74_11D3_B1EC_005004567AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cu2DCurrentsBase  
{
protected:


public:

//	static double m_nMaxCurrentValue;	// contains max current from calculation
//	static int m_nMaxCurrentWidth;		// max width of current bar (in screen pixels)
//	static double m_nArrowAngle;	// for arrow head length calculation
//	static int m_nArrowLength;		// length of arrow in pixels

	double m_nMaxCurrentValue;	// contains max current from calculation
	int m_nMaxCurrentWidth;		// max width of current bar (in screen pixels)
	double m_nArrowAngle;	// for arrow head length calculation
	int m_nArrowLength;		// length of arrow in pixels

	Cu2DCurrentsBase();
	virtual ~Cu2DCurrentsBase();

};

#endif // !defined(AFX_CU2DCURRENTSBASE_H__5D2F9D47_8F74_11D3_B1EC_005004567AD4__INCLUDED_)
