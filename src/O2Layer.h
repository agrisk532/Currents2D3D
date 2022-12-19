// O2Layer.h: interface for the O2Layer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_O2LAYER_H)
#define _O2LAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomLayers.h"

class O2Layer : public AtomLayers  
{
private:
	char whichLayer;  // 'u' for upper, 'l' for lower (with respect to Y atoms)
public:
	O2Layer(char,Distances*);
	virtual ~O2Layer();
	static O2Layer *New(char c,Distances* dst) {return new O2Layer(c,dst);};
	int calculateNumberOfAtoms();
	void calculateCoordinates();
};

#endif // !defined(_O2LAYER_H)
