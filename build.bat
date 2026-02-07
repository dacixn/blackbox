@echo off
if exist "%ROOT%\bbx-asm.exe" del "%ROOT%\bbx-asm.exe"
if exist "%ROOT%\bbx.exe" del "%ROOT%\bbx.exe" 

SET ROOT=%CD%
SET SRC=%ROOT%\src

echo Building assembler...
cd "%SRC%\assembler"
cl *.c bcrypt.lib /Fe:"%ROOT%\bbx-asm.exe"
if errorlevel 1 (
    echo Failed to build assembler
    exit /b 1
)

echo Building interpreter...
cd "%SRC%\interpreter"
cl *.c ../assembler/tools.c bcrypt.lib /Fe:"%ROOT%\bbx.exe"
if errorlevel 1 (
    echo Failed to build interpreter
    exit /b 1
)

echo Build complete!
cd "%ROOT%"