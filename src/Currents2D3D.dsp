# Microsoft Developer Studio Project File - Name="Currents2D3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Currents2D3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Currents2D3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Currents2D3D.mak" CFG="Currents2D3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Currents2D3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Currents2D3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Currents2D3D - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "C:\Program Files\HTML Help Workshop" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vtkCommon.lib vtkContrib.lib vtkGraphics0.lib vtkGraphics1.lib vtkGraphics2.lib vtkGraphics3.lib vtkGraphics4.lib vtkImaging.lib vtkJava.lib BLAS.lib LAPACK.lib htmlhelp.lib /nologo /subsystem:windows /machine:I386 /libpath:"c:\vtkbin\lib" /libpath:"C:\Program Files\HTML Help Workshop"

!ELSEIF  "$(CFG)" == "Currents2D3D - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "C:\Program Files\HTML Help Workshop" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib vtkCommon.lib vtkContrib.lib vtkGraphics0.lib vtkGraphics1.lib vtkGraphics2.lib vtkGraphics3.lib vtkGraphics4.lib vtkImaging.lib vtkJava.lib BLAS.lib LAPACK.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"c:\vtkbin\Debug\lib" /libpath:"C:\Program Files\HTML Help Workshop"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Currents2D3D - Win32 Release"
# Name "Currents2D3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ArrowsDialog1.cpp

!IF  "$(CFG)" == "Currents2D3D - Win32 Release"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "Currents2D3D - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AtomCoordinates.cpp
# End Source File
# Begin Source File

SOURCE=.\AtomLayers.cpp
# End Source File
# Begin Source File

SOURCE=.\AtomParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\BaLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Bond.cpp
# End Source File
# Begin Source File

SOURCE=.\Child2DFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Child3DFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Cu1Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\Cu2DAtoms.cpp
# End Source File
# Begin Source File

SOURCE=.\Cu2DAtomsBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Cu2DCurrents.cpp
# End Source File
# Begin Source File

SOURCE=.\Cu2DCurrentsBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Cu2Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\Currents.cpp
# End Source File
# Begin Source File

SOURCE=.\Currents2D3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Currents2D3D.rc
# End Source File
# Begin Source File

SOURCE=.\Currents2DDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Currents2DView.cpp
# End Source File
# Begin Source File

SOURCE=.\Currents3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Currents3DDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Currents3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\CurrentsBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Distances.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\O1Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\O2Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\O4Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageAtoms.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageObjToRender.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageRegions.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageRendMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Currents2D3D - Win32 Release"

# ADD CPP /YX"stdafx.pch"

!ELSEIF  "$(CFG)" == "Currents2D3D - Win32 Debug"

# ADD CPP /Gm /Yc

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Textvw.cpp
# End Source File
# Begin Source File

SOURCE=.\YLayer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ArrowsDialog1.h
# End Source File
# Begin Source File

SOURCE=.\AtomCoordinates.h
# End Source File
# Begin Source File

SOURCE=.\AtomLayers.h
# End Source File
# Begin Source File

SOURCE=.\AtomParameters.h
# End Source File
# Begin Source File

SOURCE=.\BaLayer.h
# End Source File
# Begin Source File

SOURCE=.\Bond.h
# End Source File
# Begin Source File

SOURCE=.\Child2DFrame.h
# End Source File
# Begin Source File

SOURCE=.\Child3DFrame.h
# End Source File
# Begin Source File

SOURCE=.\Constants.h
# End Source File
# Begin Source File

SOURCE=.\Cu1Layer.h
# End Source File
# Begin Source File

SOURCE=.\Cu2DAtoms.h
# End Source File
# Begin Source File

SOURCE=.\Cu2DAtomsBase.h
# End Source File
# Begin Source File

SOURCE=.\Cu2DCurrents.h
# End Source File
# Begin Source File

SOURCE=.\Cu2DCurrentsBase.h
# End Source File
# Begin Source File

SOURCE=.\Cu2Layer.h
# End Source File
# Begin Source File

SOURCE=.\Currents.h
# End Source File
# Begin Source File

SOURCE=.\Currents2D3D.h
# End Source File
# Begin Source File

SOURCE=.\Currents2DDoc.h
# End Source File
# Begin Source File

SOURCE=.\Currents2DView.h
# End Source File
# Begin Source File

SOURCE=.\Currents3D.h
# End Source File
# Begin Source File

SOURCE=.\Currents3DDoc.h
# End Source File
# Begin Source File

SOURCE=.\Currents3DView.h
# End Source File
# Begin Source File

SOURCE=.\CurrentsBase.h
# End Source File
# Begin Source File

SOURCE=.\Distances.h
# End Source File
# Begin Source File

SOURCE=.\FieldGrid.h
# End Source File
# Begin Source File

SOURCE=.\fileIO.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\O1Layer.h
# End Source File
# Begin Source File

SOURCE=.\O2Layer.h
# End Source File
# Begin Source File

SOURCE=.\O4Layer.h
# End Source File
# Begin Source File

SOURCE=.\PlotIt.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageAtoms.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageObjToRender.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageRegions.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageRendMethod.h
# End Source File
# Begin Source File

SOURCE=.\rendering.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Textvw.h
# End Source File
# Begin Source File

SOURCE=.\YLayer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\3d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\agris.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\currents.bmp
# End Source File
# Begin Source File

SOURCE=.\res\currents2D.ico
# End Source File
# Begin Source File

SOURCE=.\res\Currents2D3D.ico
# End Source File
# Begin Source File

SOURCE=.\res\Currents2D3D.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Currents2D3DDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Currents3D.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
