# EV Battery Management System

## Project Overview

The EV Battery Management System is a command-line application designed to manage electric vehicle (EV) batteries and drivers. This system allows administrators to oversee battery inventory, manage driver accounts, and track battery charge states and health metrics. The application provides a secure login system with role-based access control, allowing administrators to perform management tasks while keeping driver information organized and accessible.

## Features

- **Admin Authentication**: Secure login system for administrators with credentials stored in a database
- **Battery Management**: View and track EV batteries with detailed information including:
  - Battery type and capacity (kWh)
  - State of Charge (SOC) percentage
  - State of Health (SOH) percentage
  - Current status (Charging, Ready, Maintenance, Rented)
- **Driver Management**: Maintain a database of EV drivers with:
  - Driver names and credentials
  - License plate information
  - Account credits for battery rentals
- **User Registration**: Register new administrator accounts
- **Persistent Storage**: All data is saved to text-based database files
- **Color-Coded Interface**: ANSI color support for better readability (yellow headers, purple data)
- **Excel-Style Listing**: Organized table display with uniform column spacing

## Project Structure

```
.
├── main.cc                 # Main application entry point
├── menus.cc               # Menu interface and user interaction
├── admin.cc               # Administrator functionality
├── driver.cc              # Driver management
├── battery.cc             # Battery management
├── database.cc            # Database operations and file I/O
│
├── headers/               # Header files
│   ├── admin.h
│   ├── driver.h
│   ├── battery.h
│   ├── database.h
│   └── menus.h
│
├── data/                  # Database files
│   ├── admins.txt
│   ├── drivers.txt
│   └── batteries.txt
│
├── obj/                   # Compiled object files
├── bin/                   # Compiled executable
├── build/                 # CMake build directory (generated)
├── CMakeLists.txt         # CMake configuration file
├── build.bat              # Windows batch build script
├── build.ps1              # Windows PowerShell build script
└── build.sh               # Linux/macOS shell build script
```

## Prerequisites

- **C++ Compiler**: GCC or Clang (C++11 or later)
- **Windows**: Visual Studio C++ tools or MinGW
- **Linux**: GCC or Clang installed via package manager
- **CMake** (optional but recommended): CMake 3.10 or later for cross-platform builds

## Building the Project

### On Windows

#### Option 1: Using batch script
```cmd
build.bat
```

#### Option 2: Using CMake (Cross-platform)
```cmd
mkdir build
cd build
cmake ..
make
cd ..
```

#### Option 3: Manual compilation with g++
```cmd
g++ -o bin/battery_system main.cc admin.cc driver.cc battery.cc database.cc menus.cc -std=c++11
```

### On Linux/macOS

#### Option 4: Using build.sh script (Recommended)
```bash
chmod +x build.sh
./build.sh
```

The build.sh script will automatically create a build directory, run CMake, and compile the project.

#### Option 5: Using CMake manually
```bash
mkdir build
cd build
cmake ..
make
cd ..
```

#### Option 6: Using g++ directly
```bash
g++ -o bin/battery_system main.cc admin.cc driver.cc battery.cc database.cc menus.cc -std=c++11
```

#### Option 7: Using clang
```bash
clang++ -o bin/battery_system main.cc admin.cc driver.cc battery.cc database.cc menus.cc -std=c++11
```

## Running the Application

### Windows
```cmd
.\bin\project.exe
```

or

```cmd
bin\project.exe
```

### Linux/macOS
```bash
./bin/project
```

### Note on executable names
- If built with CMake or build.sh: executable is named `project`
- If built with direct g++ compilation: name can be customized (e.g., `battery_system`)

## Usage

1. **Main Menu**: Upon startup, you'll see the main menu with options to:
   - Login as an administrator
   - Register a new administrator account
   - Exit the application

2. **Admin Login**: Enter your username and password to access the admin panel

3. **Admin Menu**: Once logged in, you can:
   - List available batteries (view all battery information in table format)
   - List EV drivers (view all registered drivers)
   - Create driver accounts
   - Manage batteries
   - Logout (returns to main menu)

## Database Format

### admins.txt
```
ID Name Password
1 admin1 adminpass1
2 john mypass123
```

### drivers.txt
```
ID Name Password LicensePlate Credits
1 driver1 pass123 ABC-123 50.00
```

### batteries.txt
```
ID Type Capacity SOC SOH Status
1 LG 75.0 100 95 0
```

## Default Credentials

The application comes with a sample admin account:
- **Username**: admin1
- **Password**: adminpass1

## Technical Details

- **Language**: C++
- **Architecture**: Modular design with separate concerns (database, menus, entities)
- **Data Persistence**: Text-based flat file database
- **UI**: Command-line interface with ANSI color support

## Notes

- Make sure the `data/` directory exists before running the application
- All database files (admins.txt, drivers.txt, batteries.txt) should be in the `data/` folder
- Changes made during a session are saved automatically when you exit the application
- Color support may vary depending on the terminal used (recommended: PowerShell 5.1+ on Windows, any terminal on Linux)

## Future Enhancements

- Database encryption for sensitive data
- Advanced search and filter options
- Battery assignment to drivers
- Transaction history and logging
- Graphical user interface
