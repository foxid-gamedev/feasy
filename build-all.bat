@ECHO OFF
REM Build Everything

ECHO "Building everything..."


PUSHD engine
CALL build.bat
move /Y *.obj ..\bin-int\
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)


PUSHD sandbox
CALL build.bat
move /Y *.obj ..\bin-int\
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "All assemblies built successfully."