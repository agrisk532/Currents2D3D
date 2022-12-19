// Cu2Layer.h: interface for the Cu2Layer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CU2LAYER_H)
#define _CU2LAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomLayers.h"

class Cu2Layer : public AtomLayers  
{
private:
	char whichLayer;   // 'u' for upper, 'l' for lower (with respect to Y atoms)
public:
	Cu2Layer(char,Distances*);
	virtual ~Cu2Layer();
	static Cu2Layer *New(char c,Distances* dst) {return new Cu2Layer(c,dst);};
	int calculateNumberOfAtoms();
	void calculateCoordinates();
};

#endif // !defined(_CU2LAYER_H)
