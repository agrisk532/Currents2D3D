// O4Layer.h: interface for the O4Layer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_O4LAYER_H)
#define _O4LAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomLayers.h"

class O4Layer : public AtomLayers  
{
public:
	O4Layer(Distances*);
	virtual ~O4Layer();
	static O4Layer *New(Distances* dst) {return new O4Layer(dst);}
	int calculateNumberOfAtoms();
	void calculateCoordinates();
};

#endif // !defined(_O4LAYER_H)
