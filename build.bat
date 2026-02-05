@echo off
REM Create output directories
if not exist obj mkdir obj
if not exist bin mkdir bin

REM Compile the project
echo Compiling...
g++ -Wall -Wextra -std=c++11 -c main.cc -o obj/main.o
g++ -Wall -Wextra -std=c++11 -c admin.cc -o obj/admin.o
g++ -Wall -Wextra -std=c++11 -c battery.cc -o obj/battery.o
g++ -Wall -Wextra -std=c++11 -c database.cc -o obj/database.o
g++ -Wall -Wextra -std=c++11 -c driver.cc -o obj/driver.o

if errorlevel 1 (
    echo Compilation failed!
    exit /b 1
)

REM Link
echo Linking...
g++ -o bin/project.exe obj/main.o obj/admin.o obj/battery.o obj/database.o obj/driver.o

if errorlevel 1 (
    echo Linking failed!
    exit /b 1
)

echo Build successful! Run with: .\bin\project.exe
