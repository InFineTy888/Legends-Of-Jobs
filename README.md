# Legends-Of-Jobs

![Language](https://img.shields.io/badge/language-C++-blue)
![GitHub last commit](https://img.shields.io/github/last-commit/InFineTy888/Legends-Of-Jobs)
![GitHub Repo stars](https://img.shields.io/github/stars/InFineTy888/Legends-Of-Jobs)
![Discord](https://img.shields.io/discord/1180895516532416542)
![GitHub License](https://img.shields.io/github/license/InFineTy888/Legends-Of-Jobs)

# Introduction

**Legends Of Jobs** is a simple economic game in which you need to earn coins and diamonds, jobs and levels, etc!


Now this game is only available in the CLI, in the future I will make it in the GUI!


The game is written on Debian 12, and if you have problems compiling or coding the game on **Windows**, I'm sorry.

## What you need to run the game:

- **C++** :)

- And **nlohmann json** libraries for working with json-files

## Installing the `lohmann json` library

On **Linux** you need to enter:
```
sudo apt install nlohmann-json3-dev
```
For **Windows** you need:
- **CMake**
- **Vcpkg**

To install **CMake**, download it from the [official website](http://cmake.org/download /) ( During installation, do not forget to change the option so that the path to CMake is added to the PATH variable )

To install **vcpkg** you need to type in the command line:
```
git clone https://github.com/Microsoft/vcpkg

cd vcpkg

powershell -exec bypass scripts\bootstrap.ps1

vcpkg install sdl2:x86-windows-static sdl2:x64-windows-static

vcpkg --triplet nlohmann-json
```
Last but not least, enable the automatic integration of vcpkg packages into all Visual C++ projects:
```
vcpkg integrate install
```

We remove the integration - if it interferes with you.
```
vcpkg integrate remove
```

## File layout `main.cpp ` on Linux
- You will need **G++** for this
  
**You need to enter:**
```
cd Legends-Of-Jobs
g++ main.cpp -o main
```

**To start the game, you need to enter:**
```
./main
```

## File layout `main.cpp ` on Windows
To run, you need to install Visual Studio and the additional workload of Developing desktop applications in C++ or Build command-line Tools for Visual Studio.

If you have installed Visual Studio 2017 or later on Windows 11 or later, open the Start menu and select All Applications. Scroll down and open the Visual Studio folder. Select Developer's Command Prompt for VS to open a command prompt window.

If you have installed Microsoft Visual C++ Build Tools 2015 on Windows 11 or later, open the Start menu and select All Applications. Scroll down and open the Microsoft Visual C++ Build Tools folder. Select Command Prompt Native Tools x86 Visual C++ 2015 to open a command prompt window.
```
cd C:\path-to-folder\Legends-Of-Jobs
cl /c main.cpp
```
If you want to run the program `main.exe`, at the command prompt, type `main`

## Have fun!
Change the code, user information, jobs, etc!

Have a good game :)
