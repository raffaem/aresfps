@echo off
path "C:\Programmi\WinRAR"
cd "F:\raffaele\programmi\ARES"

mkdir temp
copy ares_setup_script.iss temp
copy dibapi.dll temp
copy backup.bat temp

copy *.sln temp\
copy *.dsw temp\

REM copia della guida
mkdir temp\release\readme
copy release\readme\*.* temp\release\readme\*.*
REM fine copia della guida

REM copia dei file di BestSound
mkdir temp\BestSound
copy "..\BestSound\*.cpp" temp\BestSound
copy "../BestSound/*.hpp" temp\BestSound
copy "../BestSound/*.h" temp\BestSound
copy "../BestSound/*.c" temp\BestSound
copy "../BestSound/*.dsp" temp\BestSound
copy "../BestSound/*.dsw" temp\BestSound
REM fine copia dei file dell'interfaccia

REM copia dei file della libreria
mkdir temp\ares_runtime
copy ares_runtime\*.cpp temp\ares_runtime
copy ares_runtime\res\*.* temp\ares_runtime
copy ares_runtime\*.h temp\ares_runtime
copy ares_runtime\*.hpp temp\ares_runtime
copy ares_runtime\*.rc temp\ares_runtime
copy ares_runtime\*.dsp temp\ares_runtime
copy ares_runtime\*.dsw temp\ares_runtime
copy ares_runtime\*.c temp\ares_runtime
copy ares_runtime\*.sln temp\ares_runtime
copy ares_runtime\*.vcproj temp\ares_runtime
copy ares_runtime\*.dsp temp\ares_runtime
REM fine copia dei file dell'interfaccia

REM copia dei file del gioco
mkdir temp\ares_game
mkdir "temp\ares_game\script exported"
copy ares_game\*.cpp temp\ares_game\
copy ares_game\*.pkg temp\ares_game\
copy ares_game\*.h temp\ares_game\
copy ares_game\*.hpp temp\ares_game\
copy ares_game\*.c temp\ares_game\
copy ares_game\*.dsp temp\ares_game\
copy ares_game\*.dsw temp\ares_game\
copy ares_game\*.sln temp\ares_game\
copy ares_game\*.vcproj temp\ares_game\
copy ares_game\*.dsp temp\ares_game\
copy "ares_game\script exported\*.*" "temp\ares_game\script exported\"
REM fine copia dei file del gioco

REM copia dei file dell'interfaccia
mkdir temp\interfaccia
mkdir temp\interfaccia\res
copy interfaccia\*.cpp temp\interfaccia
copy interfaccia\*.h temp\interfaccia
copy interfaccia\*.bmp temp\interfaccia
copy interfaccia\*.hpp temp\interfaccia
copy interfaccia\*.rc temp\interfaccia
copy interfaccia\*.dsp temp\interfaccia
copy interfaccia\*.dsw temp\interfaccia
copy interfaccia\res\*.* temp\interfaccia\res
REM fine copia dei file dell'interfaccia

REM copia di install level
mkdir "temp\install level"
copy "install level\*.cpp" "temp\install level"
copy "install level\*.h" "temp\install level"
copy "install level\*.hpp" "temp\install level"
copy "install level\*.c" "temp\install level"
copy "install level\*.sln" "temp\install level"
copy "install level\*.vcproj" "temp\install level"
copy "install level\*.dsp" "temp\install level"
copy "install level\*.dsw" "temp\install level"
REM fine copia di install level

REM copia level editor
mkdir "temp\level editor"
mkdir "temp\level editor\res"
mkdir "temp\level editor\hlp"
copy "level editor\*.cpp" "temp\level editor\"
copy "level editor\*.h" "temp\level editor\"
copy "level editor\*.hpp" "temp\level editor\"
copy "level editor\*.c" "temp\level editor\"
copy "level editor\*.dsp" "temp\level editor\"
copy "level editor\*.dsw" "temp\level editor\"
copy "level editor\*.sln" "temp\level editor\"
copy "level editor\*.rc" "temp\level editor\"
copy "level editor\*.vcproj" "temp\level editor\"
copy "level editor\*.dsp" "temp\level editor\"
copy "level editor\hlp\*.*" "temp\level editor\hlp\"
copy "level editor\res\*.*" "temp\level editor\res\"
REM fine

REM copia dei livelli
mkdir temp\bin\livelli
copy bin\livelli\*.aresmap temp\bin\livelli
REM fine

REM copia di pkg installer
mkdir "temp\pkg installer"
copy "pkg installer\*.cpp" "temp\pkg installer\"
copy "pkg installer\*.dsw" "temp\pkg installer\"
REM fine copia di pkg installer

copy *.bat temp

cd "temp"

if exist file.rar erase file.rar

rar a -m5 -s  -t -rr80p file.rar "*.*" -r

REM copia del file in a:\
erase /Q a:\file.rar
copy file.rar a:\

echo Inserisci il secondo floppy e
pause
erase /Q a:\file.rar
copy file.rar a:\

REM elimino il file
erase file.rar
REM ritorno a outlaw children
cd..
REM elimino temp
rd temp /s /q