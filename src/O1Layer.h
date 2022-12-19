// O1Layer.h: interface for the O1Layer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_O1LAYER_H)
#define _O1LAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomLayers.h"

class O1Layer : public AtomLayers  
{
public:
	O1Layer(Distances*);
	virtual ~O1Layer();
	int calculateNumberOfAtoms();
	void calculateCoordinates();
	static O1Layer *New(Distances* dst) {return new O1Layer(dst);}
};

#endif // !defined(_O1LAYER_H)
