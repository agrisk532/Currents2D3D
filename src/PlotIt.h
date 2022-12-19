////////////////////////////////////////////////////////////
// PlotIt.h: interface for the PlotIt class.
////////////////////////////////////////////////////////////

#if !defined(_PLOTIT_H)
#define _PLOTIT_H

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkSphereSource.h"
#include "vtkCylinderSource.h"
#include "vtkElevationFilter.h"
#include "vtkLookupTable.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMIPFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkVolume.h"
#include "vtkStreamLine.h"
#include "vtkTubeFilter.h"
#include "vtkPoints.h"
#include "vtkVolumeRayCastIsosurfaceFunction.h"
#include "vtkUnstructuredGrid.h"
#include "vtkVectorTopology.h"
#include "vtkGeometryFilter.h"
#include "vtkMaskPoints.h"
#include "vtkHedgeHog.h"
#include "vtkWin32OpenGLRenderWindow.h"

#include "FieldGrid.h"
#include "AtomCoordinates.h"
#include "Distances.h"  // ATOM_TYPES comes from the Distances.h
#include "Currents.h"
#include "Currents3D.h"
#include "rendering.h"
#include <typeinfo>
using namespace std;

//#define ATOM_TYPES 7

class PlotIt
{

private:

	vtkRenderer *renderer;
	vtkRenderWindow *renWin;
	vtkRenderWindowInteractor *iren;
	vtkSphereSource *s[ATOM_TYPES];
	vtkCylinderSource *cyl[1000];  // for electrical current intensity modelling
	vtkPolyDataMapper *pdmSpheres[ATOM_TYPES];
	vtkDataSetMapper *pdmCyls[1000];
	vtkActor *atomActor[1000];
	vtkActor *cylActor[1000];
	vtkElevationFilter *colorIt[1000];
	vtkLookupTable *lut[1000];
	vtkPiecewiseFunction *oTFun;
	vtkColorTransferFunction *cTFun;
	vtkVolumeProperty *volumeProperty;
	vtkVolumeRayCastCompositeFunction *compositeFunction;
	vtkVolumeRayCastMIPFunction *MIPFunction;
	vtkVolumeRayCastMapper *volumeMapper;
	vtkVolume *volume;
	vtkStreamLine *streamLine;
	vtkPolyDataMapper *streamsMapper;
	vtkActor *lines;
	vtkTubeFilter *streamTube;
	vtkPolyDataMapper *tubeMapper;
	vtkActor *tubes;
	vtkPoints *rakePoints;
	vtkVolumeRayCastIsosurfaceFunction *volSurf;
	vtkUnstructuredGrid *ugrid;
	vtkVectorTopology *vectorTopology;
	vtkGeometryFilter *filter;
	vtkMaskPoints *maskPoints;
	vtkHedgeHog *hedgeHog;
	vtkPolyDataMapper *hhMapper;
	vtkActor *hhActor;

	int numberOfAtoms;
	int numberOfBonds;

	int rm; // select between different volume rendering options
						// 0 - composite
						// 1 - maximum intensity
						// 2 - streamlines
	bool Is3DCurrent; // true for 3DCurrents, flase for 1DCurrents (used for dynamic casting)

public:

	PlotIt(HWND,AtomCoordinates&,FieldGrid&,Distances&,CurrentsBase&,
		int renderingMethod,int randomGeneratorSeed);
	virtual ~PlotIt();
	void MakeSpheres(Distances&,AtomCoordinates&);
	void MakeCylinders(AtomCoordinates*,CurrentsBase*);
	void AddActors(AtomCoordinates&,Distances&);
	static PlotIt *New(HWND hwnd,AtomCoordinates &ac,FieldGrid &fg,Distances &d,
		CurrentsBase &cb,int renderingMethod, int seed)
	{ return new PlotIt(hwnd,ac,fg,d,cb,renderingMethod,seed);}
	void Render() {renWin->Render(); /*iren->Start();*/}
};

#endif // !defined(_PLOTIT_H)