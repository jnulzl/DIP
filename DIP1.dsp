# Microsoft Developer Studio Project File - Name="DIP1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DIP1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DIP1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DIP1.mak" CFG="DIP1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DIP1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DIP1 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DIP1 - Win32 Release"

# PROP BASE Use_MFC 5
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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DIP1 - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "E:\Program Files (x86)\OpenCV\cxcore\include" /I "E:\Program Files (x86)\OpenCV\cv\include" /I "E:\Program Files (x86)\OpenCV\cvaux\include" /I "E:\Program Files (x86)\OpenCV\ml\include" /I "E:\Program Files (x86)\OpenCV\otherlibs\highgui" /I "E:\Program Files (x86)\OpenCV\otherlibs\cvcam\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libfacedetect.lib cfitsio.lib cxcore.lib cv.lib ml.lib cvaux.lib highgui.lib cvcam.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"E:\Program Files (x86)\OpenCV\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "DIP1 - Win32 Release"
# Name "DIP1 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CvDIP.cpp
# End Source File
# Begin Source File

SOURCE=.\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\DIP1.cpp
# End Source File
# Begin Source File

SOURCE=.\DIP1.rc
# End Source File
# Begin Source File

SOURCE=.\DIP1Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\DIP1View.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAdColor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddNoiseRadio.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBrightChange.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHist.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImageArgument.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLinear.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMedianFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMosaic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPower.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTemplateSize.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThre.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTran.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWindowTranslation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgZoom.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDib.cpp
# End Source File
# Begin Source File

SOURCE=.\PinYuLuBoDib.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CvDIP.h
# End Source File
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\DIP1.h
# End Source File
# Begin Source File

SOURCE=.\DIP1Doc.h
# End Source File
# Begin Source File

SOURCE=.\DIP1View.h
# End Source File
# Begin Source File

SOURCE=.\DlgAdColor.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddNoiseRadio.h
# End Source File
# Begin Source File

SOURCE=.\DlgBrightChange.h
# End Source File
# Begin Source File

SOURCE=.\DlgHist.h
# End Source File
# Begin Source File

SOURCE=.\DlgImageArgument.h
# End Source File
# Begin Source File

SOURCE=.\DlgLinear.h
# End Source File
# Begin Source File

SOURCE=.\DlgLog.h
# End Source File
# Begin Source File

SOURCE=.\DlgMedianFilter.h
# End Source File
# Begin Source File

SOURCE=.\DlgMosaic.h
# End Source File
# Begin Source File

SOURCE=.\DlgPower.h
# End Source File
# Begin Source File

SOURCE=.\DlgTemplateSize.h
# End Source File
# Begin Source File

SOURCE=.\DlgThre.h
# End Source File
# Begin Source File

SOURCE=.\DlgTran.h
# End Source File
# Begin Source File

SOURCE=.\DlgWindowTranslation.h
# End Source File
# Begin Source File

SOURCE=.\DlgZoom.h
# End Source File
# Begin Source File

SOURCE=..\DIP1_Ver1\fitsio.h
# End Source File
# Begin Source File

SOURCE=.\function.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceFuc.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyDib.h
# End Source File
# Begin Source File

SOURCE=.\PinYuLuBoDib.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\DIP1.ico
# End Source File
# Begin Source File

SOURCE=.\res\DIP1.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DIP1Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
