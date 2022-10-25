@echo off 

set arg1=%1

if [%arg1%]==[] (
    mingw32-make -f resources/lib/mktyrbo.mk 
    goto commonexit
)

if %arg1%==clean (
    del *.o tyrbo.exe
)

:commonexit
