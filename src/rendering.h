// This file sets different rendering options

#if !defined(_RENDERING_H)
#define _RENDERING_H

enum RENDERING_METHOD_ENUM {VolumeRayCastComposite, VolumeRayCastMIP,
		VolumeStreamLines,VolumeStreamLinesWithTubes,
		HedgeHog,VolumeRayCastIsosurfaceFunction};

// RenderingMethod works for both 'ObjectToRender' alternatives

enum OBJECT_TO_RENDER_ENUM {Currents_1D,Currents_3D};

//
// Currents1D - calculate 1D bond currents (with or without selfconsistency),
//                 magnetic field from them in 3D space and render. Can treat any number
//                 of unit cells in x,y,z directions of YBaCuO
// Currents3D - calculate only currents in 3D space, using atomic orbitals, and render
//

enum RENDERING_REGIONS_ENUM {APPLIED_FIELD,STRENGTHENED_FIELD,WEAKENED_FIELD,ALL_FIELD};

// which magnetic field regions to show

#endif // !defined(_RENDERING_H)
