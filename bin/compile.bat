@echo off

rem ⚡️ION⚡️ compilation script.
rem Works only for Windows platforms.
rem For Unix-like users, see `bin/compile`.

setlocal enabledelayedexpansion

if "%1" == "" (
  echo Usage bin/compile [app]
  exit /b 1
)

if not exist "exe\" mkdir exe

set "files="
for /f "delims= tokens=* usebackq" %%f in (`dir /a:-d /b/s app\%1\*.c`) do (
  set "files=!files! %%f"
)

if "%compiler%" == "" set compiler=MSVC

if "%compiler%" == "MSVC" (
  cl.exe ^
    /D ARCHITECTURE=X64 /D PLATFORM=WINDOWS ^
    /I src /Foexe\ /Feexe\ ^
    app\%1\%1.c %files:~1%

) else if "%compiler" == "clang" (
  clang.exe ^
    -D ARCHITECTURE=X64 -D PLATFORM=WINDOWS ^
    -I src -o exe\ ^
    %files:~1%
)
