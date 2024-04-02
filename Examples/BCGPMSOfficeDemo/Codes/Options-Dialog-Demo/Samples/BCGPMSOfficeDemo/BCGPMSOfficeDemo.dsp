# Microsoft Developer Studio Project File - Name="BCGPMSOfficeDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPMSOfficeDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMSOfficeDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMSOfficeDemo.mak" CFG="BCGPMSOfficeDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPMSOfficeDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMSOfficeDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMSOfficeDemo - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPMSOfficeDemo - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "BCGPMSOfficeDemo - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPMSOfficeDemoD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPMSOfficeDemo - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPMSOfficeDemo___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPMSOfficeDemo___Win32_ReleaseStatic"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\BinStatic"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\BCGCBPro\Styles" /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes

!ENDIF 

# Begin Target

# Name "BCGPMSOfficeDemo - Win32 Release"
# Name "BCGPMSOfficeDemo - Win32 Debug"
# Name "BCGPMSOfficeDemo - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BackStagePageHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\BackStagePageInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\BackStagePageNew.cpp
# End Source File
# Begin Source File

SOURCE=.\BackStagePageShare.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOfficeDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOfficeDemo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOfficeDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOfficeDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartPane.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardPane.cpp
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBanner.cpp
# End Source File
# Begin Source File

SOURCE=.\GridPane.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourcePage.cpp
# End Source File
# Begin Source File

SOURCE=.\RibbonListButton.cpp
# End Source File
# Begin Source File

SOURCE=.\RibbonTableButton.cpp
# End Source File
# Begin Source File

SOURCE=.\RibbonTooltipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage4.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage5.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage6.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BackStagePageHelp.h
# End Source File
# Begin Source File

SOURCE=.\BackStagePageInfo.h
# End Source File
# Begin Source File

SOURCE=.\BackStagePageNew.h
# End Source File
# Begin Source File

SOURCE=.\BackStagePageShare.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOfficeDemo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOfficeDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOfficeDemoView.h
# End Source File
# Begin Source File

SOURCE=.\ChartPane.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardPane.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\DlgBanner.h
# End Source File
# Begin Source File

SOURCE=.\GridPane.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResourcePage.h
# End Source File
# Begin Source File

SOURCE=.\RibbonListButton.h
# End Source File
# Begin Source File

SOURCE=.\RibbonTableButton.h
# End Source File
# Begin Source File

SOURCE=.\RibbonTooltipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage1.h
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage2.h
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage3.h
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage4.h
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage5.h
# End Source File
# Begin Source File

SOURCE=.\ShareOptionsPage6.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Background1.png
# End Source File
# Begin Source File

SOURCE=.\res\Background2.png
# End Source File
# Begin Source File

SOURCE=.\res\Background3.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Background4.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Background5.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Background6.PNG
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMSOfficeDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMSOfficeDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\BCGPMSOfficeDemo.ribbon.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMSOfficeDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\bs_checkissues.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_create.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_createpdfxps.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_filetypes.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_help_list_16.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_help_list_32.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_manageversions.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_new.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_print.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_printpreview.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_protect.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_publishblog.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_quickprint.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_save_as.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_sendattachment.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_sendfax.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_sendlink.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_sendpdf.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_sendxps.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_share.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_signin.png
# End Source File
# Begin Source File

SOURCE=.\res\bs_watermark.png
# End Source File
# Begin Source File

SOURCE=.\res\bullets.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_backstage_small.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_large_0_0.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_large_1_0.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_large_1_1.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_large_1_2.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_small_0_0.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_small_1_0.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_small_1_1.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_context_small_1_2.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_large_0.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_large_1.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_large_2.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_large_3.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_large_4.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_large_5.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_large_6.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_main_large.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_main_small.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_small_0.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_small_1.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_small_2.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_small_3.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_small_4.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_small_5.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\category_small_6.png
# End Source File
# Begin Source File

SOURCE=.\res\chart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clearall.png
# End Source File
# Begin Source File

SOURCE=.\res\ClipboardItem.png
# End Source File
# Begin Source File

SOURCE=.\res\gridarrows.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_1.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_2.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_3.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_4.png
# End Source File
# Begin Source File

SOURCE=.\res\info.png
# End Source File
# Begin Source File

SOURCE=.\res\layout.png
# End Source File
# Begin Source File

SOURCE=.\res\LayoutMetro.png
# End Source File
# Begin Source File

SOURCE=.\res\logo.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\main.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\multi.png
# End Source File
# Begin Source File

SOURCE=.\res\num.png
# End Source File
# Begin Source File

SOURCE=.\res\options.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_0_0.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_0_0_0.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_0_1.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_0_2.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_0_3.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_0_4.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_0_4_dark.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_1_1.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_1_2_0.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\palette_2_4.png
# End Source File
# Begin Source File

SOURCE=.\res\paste.png
# End Source File
# Begin Source File

SOURCE=.\res\pasteall.png
# End Source File
# Begin Source File

SOURCE=.\res\picture.bmp
# End Source File
# Begin Source File

SOURCE=.\res\position1.png
# End Source File
# Begin Source File

SOURCE=.\res\position2.png
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\ribbon.xml
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\ribbon_bar.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\spell.ico
# End Source File
# Begin Source File

SOURCE=.\res\spell.png
# End Source File
# Begin Source File

SOURCE=.\res\start.rtf
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\status_bar.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGSoft_ribbon\status_group_0.png
# End Source File
# Begin Source File

SOURCE=.\res\table.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ThemeColors.png
# End Source File
# Begin Source File

SOURCE=.\res\ThemeEffects.png
# End Source File
# Begin Source File

SOURCE=.\res\ThemeFonts.png
# End Source File
# Begin Source File

SOURCE=.\res\ThemeThemes.png
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-clipboard.png"
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-fontdlg.png"
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-main.png"
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-paragraph.png"
# End Source File
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Group
# End Target
# End Project
