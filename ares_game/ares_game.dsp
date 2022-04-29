# Microsoft Developer Studio Project File - Name="ares_game" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ares_game - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ares_game.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ares_game.mak" CFG="ares_game - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ares_game - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ares_game - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ares_game - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../release/bin/ares_game.exe"

!ELSEIF  "$(CFG)" == "ares_game - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib gdi32.lib newton.lib /nologo /subsystem:console /debug /machine:I386 /out:"../Debug/bin/ares_game.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ares_game - Win32 Release"
# Name "ares_game - Win32 Debug"
# Begin Group "classes"

# PROP Default_Filter ""
# Begin Group "machine_gun"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\machine_gun.cpp
# End Source File
# Begin Source File

SOURCE=.\machine_gun.hpp
# End Source File
# End Group
# Begin Group "shot_gun"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shot_gun.cpp
# End Source File
# Begin Source File

SOURCE=.\shot_gun.hpp
# End Source File
# End Group
# Begin Group "rifle_gun"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\rifle_gun.cpp
# End Source File
# Begin Source File

SOURCE=.\rifle_gun.hpp
# End Source File
# End Group
# Begin Group "punch_gun"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\punch_gun.cpp
# End Source File
# Begin Source File

SOURCE=.\punch_gun.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\classi.cpp
# End Source File
# Begin Source File

SOURCE=.\classi.hpp
# End Source File
# Begin Source File

SOURCE=".\level model.hpp"
# End Source File
# Begin Source File

SOURCE=.\weapon.hpp
# End Source File
# End Group
# Begin Group "global variables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\evar.hpp
# End Source File
# Begin Source File

SOURCE=.\var.hpp
# End Source File
# End Group
# Begin Group "functions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\func.cpp
# End Source File
# Begin Source File

SOURCE=.\func.hpp
# End Source File
# End Group
# Begin Group "sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound.hpp
# End Source File
# End Group
# Begin Group "irrlicht classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\irrlicht class.cpp"
# End Source File
# Begin Source File

SOURCE=".\irrlicht class.hpp"
# End Source File
# End Group
# Begin Group "aresmap & aresm2 loader"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\script.cpp
# End Source File
# Begin Source File

SOURCE=.\script.hpp
# End Source File
# End Group
# Begin Group "lua script"

# PROP Default_Filter ""
# Begin Group "tolua exports"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AresLua.pkg

!IF  "$(CFG)" == "ares_game - Win32 Release"

!ELSEIF  "$(CFG)" == "ares_game - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\tolua_lua.cpp
# End Source File
# Begin Source File

SOURCE=.\tolua_lua.h
# End Source File
# End Group
# Begin Group "exported func"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lua_func.cpp
# End Source File
# Begin Source File

SOURCE=".\script exported\lua_func.hpp"
# End Source File
# End Group
# End Group
# Begin Group "add"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\add.cpp
# End Source File
# Begin Source File

SOURCE=.\add.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ares.cpp
# End Source File
# End Target
# End Project
