// Cu1Layer.h: interface for the Cu1Layer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CU1LAYER_H)
#define _CU1LAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomLayers.h"

class Cu1Layer : public AtomLayers  
{
public:
	Cu1Layer(Distances*);
	virtual ~Cu1Layer();
	static Cu1Layer *New(Distances* dst) {return new Cu1Layer(dst);}
	int calculateNumberOfAtoms();
	void calculateCoordinates();
};

#endif // !defined(_CU1LAYER_H)
