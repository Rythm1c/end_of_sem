@echo off
REM CMake build script for Windows (Batch version)
REM This script configures and builds the project using CMake

echo CMake Build Script
echo.

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Enter build directory
cd build

REM Configure the project
echo Configuring CMake...
cmake ..

if errorlevel 1 (
    echo CMake configuration failed!
    cd ..
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build . --config Release

if errorlevel 1 (
    echo Build failed!
    cd ..
    exit /b 1
)

cd ..

echo.
echo Build successful! Run with: .\bin\project.exe
