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
  echo Compiling with MSVC.
  cl.exe ^
    /D ARCHITECTURE=X64 /D PLATFORM=WINDOWS ^
    /I src /Zi /Foexe\ /Feexe\ ^
    app\%1\%1.c %files:~1%

)

if "%compiler%" == "clang" (
  echo Compiling with clang.
  clang.exe ^
    -std=c89 -pedantic -Wall -Werror ^
    -D ARCHITECTURE=X64 -D PLATFORM=WINDOWS ^
    -I src -g3 -o exe\ ^
    %files:~1%
)
