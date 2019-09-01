;PLEASE DON'T DELETE THIS NOTE IF YOU REDISTRIBUTE THIS PROGRAM

;This file is a part of Ares, a first person shooter (fps) game
;based on irrlicht engine

;Copyright (C) 2006  Mancuso Raffaele

;This program is free software; you can redistribute it and/or modify
;it under the terms of the GNU General Public License as published by
;the Free Software Foundation; either version 2 of the License, or
;(at your option) any later version.

;This program is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.

;You should have received a copy of the GNU General Public License
;along with this program; if not, write to the Free Software
;Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

;Ares web-site: aresfps.sf.net
;Ares e-mail: ares_support@virgilio.it

; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Ares"
#define MyAppVerName "Arfes 0.2a"
#define MyAppPublisher "Mancuso Raffaele"
#define MyAppURL "aresfps.sourceforge.net"
#define MyAppExeName "ares.exe"
#define MyAppUrlName "ares.url"
#define MyAppEMail   "ares_support@virgilio.it"

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppVerName}
DefaultGroupName={#MyAppVerName}
OutputDir=d:\raffaele\programmi\ares
OutputBaseFilename=ares_setup
Compression=lzma/ultra
SolidCompression=true
InternalCompressLevel=ultra
VersionInfoVersion=0.2.1
VersionInfoCompany=Mancuso Raffaele
VersionInfoDescription=FPS wich use Irrlicht
ShowLanguageDialog=no
LicenseFile=d:\raffaele\programmi\ares\bin\readme\GPL.txt
VersionInfoCopyright=2006
AppID={{DC4ED4F6-F9B9-4BE9-9B43-89C5C4D04F7A}
AppCopyright=Mancuso Raffaele � 2006

[Languages]
Name: english; MessagesFile: compiler:Default.isl

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked

[Files]
Source: bin\*; DestDir: {app}; Flags: ignoreversion recursesubdirs createallsubdirs; Tasks: ; Languages: ; Excludes: install.aresmi
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
Source: bin\install.aresmi; DestDir: {group}; DestName: Level install.aresmi

[INI]
Filename: {app}\{#MyAppUrlName}; Section: InternetShortcut; Key: URL; String: {#MyAppURL}

[Icons]
Name: {group}\{#MyAppName}; Filename: {app}\{#MyAppExeName}; WorkingDir: {app}
Name: {group}\{cm:ProgramOnTheWeb,{#MyAppName}}; Filename: {app}\{#MyAppUrlName}
Name: {group}\{cm:UninstallProgram,{#MyAppName}}; Filename: {uninstallexe}
Name: {userdesktop}\{#MyAppName}; Filename: {app}\{#MyAppExeName}; Tasks: desktopicon; WorkingDir: {app}
Name: {group}\Level editor; Filename: {app}\level editor.exe; WorkingDir: {app}
Name: {group}\Readme; Filename: {app}\readme\readme.htm; WorkingDir: {app}\readme
Name: {group}\Screen-shots; Filename: {app}\image; WorkingDir: {app}\image; Flags: foldershortcut
Name: {group}\User tracks; Filename: {app}\tracks; WorkingDir: {app}; Flags: foldershortcut

[Run]
Filename: {app}\{#MyAppExeName}; Description: {cm:LaunchProgram,{#MyAppName}}; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: {app}\{#MyAppUrlName}

[Registry]
Root: HKCR; Subkey: .aresmi; ValueType: string; ValueData: Ares Install Map; Flags: uninsdeletekey
Root: HKCR; Subkey: Ares Install Map\shell\open\command; ValueType: string; ValueData: """{app}\install level.exe"" ""%1"""; Flags: uninsdeletekey
Root: HKCR; Subkey: Ares Install Map\shell\Open with notepad\command; ValueType: string; ValueData: """notepad.exe"" ""%1"""; Flags: uninsdeletekey