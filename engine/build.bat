@echo off
SetLocal EnableDelayedExpansion

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

SET cfilenames=
FOR /R %%f in (*.c *.cpp) do (
    SET cfilenames=!cfilenames! %%f
)

SET assembly=engine
SET compilerFlags=/EHsc /MDd /W4 /WX
SET includes=/Isrc /I%VULKAN_SDK%/Include /I%SDL_SDK%/include 
SET links=/link /LIBPATH:%VULKAN_SDK%/Lib vulkan-1.lib /LIBPATH:%SDL_SDK%/lib/x64 SDL2.lib
SET defines=/D DEBUG /D FEASY_EXPORT /D _CRT_SECURE_NO_WARNINGS

cl %cfilenames% %compilerFlags% %includes% %defines% %links% /DLL /OUT:../bin/%assembly%.dll