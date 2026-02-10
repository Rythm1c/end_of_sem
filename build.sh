#!/bin/bash

# EV Battery Management System - Linux Build Script

echo "Building EV Battery Management System..."

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
    echo "Created build directory"
fi

# Navigate to build directory
cd build

# Run CMake
echo "Running CMake..."
cmake ..

# Build the project
echo "Building project..."
make

# Return to root directory
cd ..

# Check if build was successful
if [ -f "bin/project" ]; then
    echo ""
    echo "=========================================="
    echo "Build successful!"
    echo "Executable location: ./bin/project"
    echo "To run: ./bin/project"
    echo "=========================================="
else
    echo ""
    echo "Build failed. Please check the error messages above."
fi
