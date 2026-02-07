Write-Host "Creating output directories..." -ForegroundColor Cyan
if (!(Test-Path obj)) { New-Item -ItemType Directory -Name obj > $null }
if (!(Test-Path bin)) { New-Item -ItemType Directory -Name bin > $null }

Write-Host "Compiling..." -ForegroundColor Cyan
g++ -Wall -Wextra -std=c++11 -c main.cc -o obj/main.o
g++ -Wall -Wextra -std=c++11 -c admin.cc -o obj/admin.o
g++ -Wall -Wextra -std=c++11 -c battery.cc -o obj/battery.o
g++ -Wall -Wextra -std=c++11 -c database.cc -o obj/database.o
g++ -Wall -Wextra -std=c++11 -c driver.cc -o obj/driver.o
g++ -Wall -Wextra -std=c++11 -c menus.cc -o obj/menus.o

Write-Host "Linking..." -ForegroundColor Cyan
g++ -o bin/project.exe obj/main.o obj/admin.o obj/battery.o obj/menus.o obj/database.o obj/driver.o

Write-Host "Build successful! Run with: .\bin\project.exe" -ForegroundColor Green
