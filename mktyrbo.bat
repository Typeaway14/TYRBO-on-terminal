@echo off 

set arg1=%1
@REM if [%arg1%]==[] goto make else if %arg1%==clean del *.o tyrbo.exe
@REM if [%arg1%]==[] del *.o tyrbo.exe
if [%arg1%]==[] (
    mingw32-make -f resources/lib/mktyrbo.mk 
    goto commonexit
)

if %arg1%==clean (
    del *.o tyrbo.exe
)

:commonexit