// YLayer.h: interface for the YLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_YLAYER_H)
#define _YLAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomLayers.h"

class YLayer : public AtomLayers  
{
public:
	YLayer(Distances*);
	virtual ~YLayer();
	static YLayer *New(Distances* dst) {return new YLayer(dst);}
	int calculateNumberOfAtoms();
	void calculateCoordinates();
};

#endif // !defined(_YLAYER_H)
