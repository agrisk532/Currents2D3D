// BaLayer.h: interface for the BaLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BALAYER_H)
#define _BALAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomLayers.h"

class BaLayer : public AtomLayers  
{
public:
	BaLayer(Distances*);
	virtual ~BaLayer();
	static BaLayer *New(Distances* dst) {return new BaLayer(dst);}
	int calculateNumberOfAtoms();
	void calculateCoordinates();
};

#endif // !defined(_BALAYER_H)
