/*  

 This program visualizes electrical currents in YBaCuO crystal using the structured point grid.

*/

#include "main.h"

#define ATOM_LAYERS 9

int main(int argc, char *argv[])
{
	int atomLayerPlotFlag[ATOM_LAYERS] = {1,0,1,0,0,0,0,0,1}; // set 1 to plot the corresponding type layer, 0 if not
	int i;
	const ObjectToRender objToRender = Currents_1D; // choose what to render (see rendering.h)
	int randomGeneratorSeed; // for streamlines

//  Layer identification
//
//	0 - cu2_lower  (lower means below Y layer)
//	1 - o2_lower
//	2 - cu2_upper
//	3 - o2_upper
//	4 - y
//	5 - ba
//	6 - o4
//	7 - o1
//	8 - cu1

	AtomCoordinates *acoord;
	FieldGrid *grid;
	PlotIt *plotter;
	Distances *dist;
	AtomLayers *al[ATOM_LAYERS];  // pointer to different layers
	Currents *curr;
	Currents3D *curr3D;
	AtomParameters *ap;

// pointers to different possible atomic layers

	Cu2Layer *cu2_lower;
	O2Layer *o2_lower;
	Cu2Layer *cu2_upper;
	O2Layer *o2_upper;
	YLayer *y;
	BaLayer *ba;
	O4Layer *o4;
	O1Layer *o1;
	Cu1Layer *cu1;

	if(argc == 1) randomGeneratorSeed = 1024;
	else
		if(argc ==2) randomGeneratorSeed = atoi(argv[1]);
	else
	{
		printf("Program usage : currents [int number]\n");
		exit(0);
	}
	printf("Random number generator seed = %d\n",randomGeneratorSeed);

// make distances object
	dist = new Distances;

//  initialization for testing all layers
//	for(int i=0 ; i<ATOM_LAYERS ; i++) atomLayerPlotFlag[i] = 1;

// make a new atom coordinates object
	acoord = new AtomCoordinates;
// set the reference to the Distances object to be used from all Layer objects
	AtomLayers::SetDistances(dist);
	Bond::SetAtomCoordinates(acoord);

// 	calculate the pointers to different atom layers
	al[0] = cu2_lower = (atomLayerPlotFlag[0] == 1) ? Cu2Layer::New('l') : NULL;
	al[1] = o2_lower = (atomLayerPlotFlag[1] == 1) ? O2Layer::New('l') : NULL;
	al[2] = cu2_upper = (atomLayerPlotFlag[2] == 1) ? Cu2Layer::New('u') : NULL;
	al[3] = o2_upper = (atomLayerPlotFlag[3] == 1) ? O2Layer::New('u') : NULL;
	al[4] = y = (atomLayerPlotFlag[4] == 1) ? YLayer::New() : NULL;
	al[5] = ba = (atomLayerPlotFlag[5] == 1) ? BaLayer::New() : NULL;
	al[6] = o4 = (atomLayerPlotFlag[6] == 1) ? O4Layer::New() : NULL;
	al[7] = o1 = (atomLayerPlotFlag[7] == 1) ? O1Layer::New() : NULL;
	al[8] = cu1 = (atomLayerPlotFlag[8] == 1) ? Cu1Layer::New() : NULL;

// add atom layer objects (coordinates and types) to the AtomCoordinates object
	for(i=0 ; i<ATOM_LAYERS ; i++)
	{
		if(al[i] == NULL) continue;
		acoord->AddLayer(al[i]);
	}

// now distinguish between two cases
// 1) - calculate the curents only in bonds (not in 3D space)
// 2) - calculate the currents in 3D space, without selfconsistency

// calculate currents in CuO2 layers

	bool doWithoutSelfConsistency = false;  // used only in 1DCurrents rendering
	double InitialMagneticField_B = 0.0001; // in gauss 
	double tau = 1.0; 
	double Eo = -1.0; // (Eo - Em) must be negative!
	double Em = 0.0;

// calculate the 1D current case

	if(objToRender == Currents_1D)
	{
		curr = Currents::New(doWithoutSelfConsistency,InitialMagneticField_B);
		curr->SetDistances(dist);
		curr->SetCoordinates(acoord);

		curr->AddLayer(al[0]);  // add Cu2_lower layer coordinates for electrical current CALCULATION
		curr->AddLayer(al[2]);  // add Cu2_upper layer coordinates for electrical current CALCULATION

// set the gauge origin in the symmetry center of the layers included in calculation
// use single gauge origin
		curr->SetGaugeOrigin();
		acoord->TranslateToGaugeOrigin();
// calculate the grid
		grid = FieldGrid::New(*acoord,*dist);
// calculate the bond currents
		curr->CalculateCurrentsInBonds(tau,Eo,Em,doWithoutSelfConsistency);
		curr->CalculateMagneticFieldOnGrid(grid); // calculate the magnetic field

//enum RenderingMethod {VolumeRayCastComposite, VolumeRayCastMIP,
//		VolumeRayCastIsosurfaceFunction,VolumeStreamLines,VolumeStreamLinesWithTubes,
//		HedgeHog};

		plotter = PlotIt::New(*acoord,*grid,*dist,*curr,
								VolumeRayCastMIP,  // rendering.h method
								randomGeneratorSeed
							);
		plotter->Render();

		delete curr;
		delete dist;
		delete acoord;
		delete grid;
		delete plotter;
	}
	else // Currents3D
	{
		if(objToRender == Currents_3D)
		{
			double c[2]; // holds AO coefficients (double zeta)
			double e[2]; // holds AO exponents (double zeta)
			c[0] = 0.6583;
			c[1] = 0.5307;
			e[0] = 5.5454;
			e[1] = 1.9715;
			ap = AtomParameters::New(c,e); // set up an atom parameters object
			ap->SetCoordinates(acoord);

			curr3D = Currents3D::New(InitialMagneticField_B);
			curr3D->SetDistances(dist);
			curr3D->SetCoordinates(acoord);
			curr3D->SetAtomParameters(ap);

			curr3D->AddLayer(al[0]);  // add Cu2_lower layer coordinates for electrical current CALCULATION
			curr3D->AddLayer(al[2]);  // add Cu2_upper layer coordinates for electri

// calculate the grid
			grid = FieldGrid::New(*acoord,*dist);

// calculate the 3D currents
// enum ReadOrWriteFieldToFile {WriteFieldToFile,ReadFieldFromFile};
			ReadOrWriteFieldToFile rw = ReadFieldFromFile;
			curr3D->Calculate(tau,Eo,Em,grid,rw);

// plot the field
// initial points for streamlines are defined in plotit.cpp
			plotter = PlotIt::New(*acoord,*grid,*dist,*curr3D,
									VolumeRayCastIsosurfaceFunction,  // rendering method
									randomGeneratorSeed
                                 );
			plotter->Render();

		delete curr3D;
		delete dist;
		delete acoord;
		delete grid;
		delete plotter;

		}
	}

// Cleanup... Coordinates now are stored in AtomCoordinates

	delete cu2_lower;
	delete o2_lower;
	delete cu2_upper;
	delete o2_upper;
	delete y;
	delete o4;
	delete o1;
	delete cu1;

// plot the whole thing

	return 0;
}
