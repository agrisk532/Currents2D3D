; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCurrents3DView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "currents2d3d.h"
LastPage=0

ClassCount=17
Class1=ArrowsDialog
Class2=CChild2DFrame
Class3=CChild3DFrame
Class4=CCurrents2D3DApp
Class5=CAboutDlg
Class6=CCurrents2DDoc
Class7=CCurrents2DView
Class8=CCurrents3DDoc
Class9=CCurrents3DView
Class10=CMainFrame
Class11=Modal3DPropSheet
Class12=PropertyPageAtoms
Class13=PropertyPageObjToRender
Class14=PropertyPageRegions
Class15=PropertyPageRendMethod
Class16=Proppage3DSetupAtoms
Class17=CTextView

ResourceCount=10
Resource1=IDD_PP_OBJTORENDER
Resource2=IDD_ABOUTBOX
Resource3=IDR_CURRENTS2D_GRAYED
Resource4=IDR_CURRENTS3D
Resource5=IDR_MAINFRAME
Resource6=IDR_CURRENTS2D
Resource7=IDD_PP_ATOMS
Resource8=IDD_ARROWS
Resource9=IDD_PP_RENDMETHOD
Resource10=IDD_PP_RENDREGIONS

[CLS:ArrowsDialog]
Type=0
BaseClass=CDialog
HeaderFile=ArrowsDialog1.h
ImplementationFile=ArrowsDialog1.cpp
LastObject=ArrowsDialog

[CLS:CChild2DFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=Child2DFrame.h
ImplementationFile=Child2DFrame.cpp
LastObject=CChild2DFrame

[CLS:CChild3DFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=Child3DFrame.h
ImplementationFile=Child3DFrame.cpp

[CLS:CCurrents2D3DApp]
Type=0
BaseClass=CWinApp
HeaderFile=Currents2D3D.h
ImplementationFile=Currents2D3D.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Currents2D3D.cpp
ImplementationFile=Currents2D3D.cpp

[CLS:CCurrents2DDoc]
Type=0
BaseClass=CDocument
HeaderFile=Currents2DDoc.h
ImplementationFile=Currents2DDoc.cpp

[CLS:CCurrents2DView]
Type=0
BaseClass=CScrollView
HeaderFile=Currents2DView.h
ImplementationFile=Currents2DView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_VIEW_ZOOMTOFIT

[CLS:CCurrents3DDoc]
Type=0
BaseClass=CDocument
HeaderFile=Currents3DDoc.h
ImplementationFile=Currents3DDoc.cpp

[CLS:CCurrents3DView]
Type=0
BaseClass=CScrollView
HeaderFile=Currents3DView.h
ImplementationFile=Currents3DView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_FILE_SAVE

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:Modal3DPropSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=Modal3DPropSheet.h
ImplementationFile=Modal3DPropSheet.cpp

[CLS:PropertyPageAtoms]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropertyPageAtoms.h
ImplementationFile=PropertyPageAtoms.cpp

[CLS:PropertyPageObjToRender]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropertyPageObjToRender.h
ImplementationFile=PropertyPageObjToRender.cpp

[CLS:PropertyPageRegions]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropertyPageRegions.h
ImplementationFile=PropertyPageRegions.cpp

[CLS:PropertyPageRendMethod]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropertyPageRendMethod.h
ImplementationFile=PropertyPageRendMethod.cpp

[CLS:Proppage3DSetupAtoms]
Type=0
BaseClass=CPropertyPage
HeaderFile=Proppage3DSetupAtoms.h
ImplementationFile=Proppage3DSetupAtoms.cpp

[CLS:CTextView]
Type=0
BaseClass=CScrollView
HeaderFile=Textvw.h
ImplementationFile=Textvw.cpp

[DLG:IDD_ARROWS]
Type=1
Class=ArrowsDialog
ControlCount=9
Control1=IDC_STATIC_ARROWS_LENGTH,static,1342308352
Control2=IDC_EDIT_ARROWS_LENGTH,edit,1350631552
Control3=IDC_STATIC_ARROWS_ANGLE,static,1342308352
Control4=IDC_EDIT_ARROWS_ANGLE,edit,1350631552
Control5=IDC_STATIC_ARROWS_WIDTH,static,1342308352
Control6=IDC_EDIT_ARROWS_WIDTH,edit,1350631552
Control7=IDC_SPIN_ARROWS_WIDTH,msctls_updown32,1342177314
Control8=IDC_BUTTON_ARROWS_OK,button,1342242816
Control9=IDC_BUTTON_ARROWS_CANCEL,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDOK,button,1342373889
Control6=IDC_STATIC,static,1342177294

[DLG:IDD_PP_ATOMS]
Type=1
Class=PropertyPageAtoms
ControlCount=9
Control1=IDC_PP_ATOMS_Cu2_1,button,1476460547
Control2=IDC_PP_ATOMS_Cu2_2,button,1476460547
Control3=IDC_PP_ATOMS_O2_1,button,1342242819
Control4=IDC_PP_ATOMS_O2_2,button,1342242819
Control5=IDC_PP_ATOMS_Y,button,1342242819
Control6=IDC_PP__ATOMS_BA,button,1342242819
Control7=IDC_PP_ATOMS_O4,button,1342242819
Control8=IDC_PP_ATOMS_O1,button,1342242819
Control9=IDC_PP_ATOMS_CU1,button,1342242819

[DLG:IDD_PP_OBJTORENDER]
Type=1
Class=PropertyPageObjToRender
ControlCount=2
Control1=IDD_PP_RENDER_RADIO_CURR1D,button,1342308361
Control2=IDD_PP_RENDER_RADIO_CURR3D,button,1342177289

[DLG:IDD_PP_RENDREGIONS]
Type=1
Class=PropertyPageRegions
ControlCount=4
Control1=IDD_RENDREGIONS_ORIGINAL,button,1342308361
Control2=IDD_RENDREGIONS_STRENGTH,button,1342177289
Control3=IDD_RENDREGIONS_WEAKENED,button,1342177289
Control4=IDD_RENDREGIONS_ALL,button,1342177289

[DLG:IDD_PP_RENDMETHOD]
Type=1
Class=PropertyPageRendMethod
ControlCount=9
Control1=IDD_PP_RENDMETHOD_VOLRAYCAST_COMPOSITE,button,1342308361
Control2=IDD_PP_RENDMETHOD_VOLRAYCASTMIP,button,1342177289
Control3=IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF,button,1342177289
Control4=IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_SUGGESTED,static,1342177280
Control5=IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_STATIC,static,1342308352
Control6=IDD_PP_RENDMETHOD_VOLRAYCASTISOSURF_EDIT,edit,1350631552
Control7=IDD_PP_RENDMETHOD_STREAMLINES,button,1342177289
Control8=IDD_PP_RENDMETHOD_STREAMLINESWITHTUBES,button,1342177289
Control9=IDD_PP_RENDMETHOD_HEDGEHOG,button,1342177289

[DLG:IDD_PROPPAGE_IMAGESETUP_ATOMS]
Type=1
Class=Proppage3DSetupAtoms

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_ABOUT
CommandCount=2

[TB:IDR_CURRENTS2D]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_EDIT_COPY
Command3=ID_FILE_PRINT
Command4=ID_TOOLS_ARROWPROPERTIES
CommandCount=4

[TB:IDR_CURRENTS3D]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_TOOLS_IMAGESETUP
CommandCount=3

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_STATUS_BAR
Command4=ID_HHNOTIFICATION
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_CURRENTS3D]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_SAVE
Command4=ID_APP_EXIT
Command5=ID_VIEW_STATUS_BAR
Command6=ID_TOOLS_FONTPROPERTIES3
Command7=ID_TOOLS_IMAGESETUP
Command8=ID_HHNOTIFICATION
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_CURRENTS2D_GRAYED]
Type=1
Class=?
CommandCount=0

[MNU:IDR_CURRENTS2D]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_PRINT
Command3=ID_FILE_PRINT_PREVIEW
Command4=ID_FILE_PRINT_SETUP
Command5=ID_APP_EXIT
Command6=ID_EDIT_COPY
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_VIEW_ZOOMTOFIT
Command10=ID_TOOLS_ARROWPROPERTIES
Command11=ID_TOOLS_FONTPROPERTIES
Command12=ID_HHNOTIFICATION
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDR_CURRENTS2D]
Type=1
Class=?
ControlCount=18
Control1=IDC_STATIC_NMBCUATOMS,static,1342308352
Control2=IDC_EDIT_NMBCUATOMS,edit,1350631552
Control3=IDC_SPIN_NMBCUATOMS,msctls_updown32,1342177330
Control4=IDC_STATIC_EXTMAGNFIELD,static,1342308352
Control5=IDC_EDIT_EXTMAGNFIELD,edit,1350631552
Control6=IDC_STATIC_CUCUDISTANCE,static,1342308352
Control7=IDC_EDIT_CUCUDIST,edit,1350631552
Control8=IDC_BUTTON_CALCANDPLOT,button,1342242816
Control9=IDC_STATIC_ELECTRONS_REMOVED,static,1342308352
Control10=IDC_EDIT_ELECTRONS_REMOVED,edit,1350631552
Control11=IDC_SPIN_ELECTRONS_REMOVED,msctls_updown32,1342177330
Control12=IDC_STATIC_ZOOM_FACTOR,static,1342308352
Control13=IDC_EDIT_ZOOM_FACTOR,edit,1350631552
Control14=IDC_BUTTON_APPLY_ZOOM,button,1342242816
Control15=ID_VIEW_ZOOMTOFIT,button,1342242816
Control16=IDC_STATIC_SCF,button,1342177287
Control17=IDC_CHECK_ISSCF,button,1342246915
Control18=IDC_STATIC,static,1342308353

[DLG:IDR_CURRENTS3D]
Type=1
Class=?
ControlCount=15
Control1=IDC_STATIC_NMBCUATOMS3,static,1342308352
Control2=IDC_EDIT_NMBCUATOMS3,edit,1350631552
Control3=IDC_SPIN_NMBCUATOMS3,msctls_updown32,1342177330
Control4=IDC_STATIC_UNITCELLS_C,static,1342177280
Control5=IDC_EDIT_UNITCELLSC,edit,1350631552
Control6=IDC_SPIN_UNITCELLSC,msctls_updown32,1342177330
Control7=IDC_STATIC_SCF3,button,1342177287
Control8=IDC_CHECK_ISSCF3,button,1342246915
Control9=IDC_STATIC3,static,1342308353
Control10=IDC_BUTTON_CALCANDPLOT3,button,1342242816
Control11=IDC_STATIC_ELECTRONS_REMOVED3,static,1342308352
Control12=IDC_EDIT_ELECTRONS_REMOVED3,edit,1350631552
Control13=IDC_SPIN_ELECTRONS_REMOVED3,msctls_updown32,1342177330
Control14=IDC_STATIC_EXTMAGNFIELD3,static,1342308352
Control15=IDC_EDIT_EXTMAGNFIELD3,edit,1350631552

