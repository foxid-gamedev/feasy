@ECHO OFF
SetLocal EnableDelayedExpansion

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

SET cfilenames=
FOR /R %%f in (*.c *.cpp) do (
    SET cfilenames=!cfilenames! %%f
)

SET assembly=sandbox
SET compilerFlags=/EHsc /W4 /WX
SET includes=/Isrc /I../engine/src
SET links=/link /LIBPATH:../bin/ engine.lib
SET defines=/D DEBUG /D FEASY_IMPORT -D_CRT_SECURE_NO_WARNINGS

cl %cfilenames% %compilerFlags% %includes% %defines% %links% /OUT:../bin/%assembly%.exe