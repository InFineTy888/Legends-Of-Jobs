# Legends-Of-Jobs

![Language](https://img.shields.io/badge/language-C++-blue)
![GitHub last commit](https://img.shields.io/github/last-commit/InFineTy888/Legends-Of-Jobs)
![GitHub Repo stars](https://img.shields.io/github/stars/InFineTy888/Legends-Of-Jobs)
![Discord](https://img.shields.io/discord/1180895516532416542)
![GitHub License](https://img.shields.io/github/license/InFineTy888/Legends-Of-Jobs)

# Введение

**Legends Of Jobs** — это простая экономическая игра в которой вам нужно зарабатывать монеты и алмазы, работы и уровни, и т.д!

Сейчас это игра доступна только в интерфейсе командной строки, в будующем я сделаю её в графическом интерфейсе!


Игра написана на Debian 12, и если на **Windows** у вас есть проблемы с компиляцией или кодом игры, извените.

## Что нужно для того чтобы запустить нашу игру:

- Сам **C++** :)

- И библиотека **nlohmann json**, для работы с json-файлами

## Установка библиотеки `nlohmann json`

На **Linux** вам нужно ввести:
```
sudo apt install nlohmann-json3-dev
```
Для **Windows** вам нужно:
- **CMake**
- **Vcpkg**

Чтобы установить **CMake**, скачайте его с [официального сайта](https://cmake.org/download/) ( При установке не забудьте поменять опцию, чтобы путь к CMake был добавлен в переменную PATH )

Чтобы установить **vcpkg** вам нужно в командной строке ввести:
```
git clone https://github.com/Microsoft/vcpkg

cd vcpkg

powershell -exec bypass scripts\bootstrap.ps1

vcpkg install sdl2:x86-windows-static sdl2:x64-windows-static
```

## Компоновка файла `main.cpp` на Linux
- Вам потребуется **G++** для этого
  
**Вам нужно ввести:**
```
cd Legends-Of-Jobs
g++ main.cpp -o main
```

**Чтобы запустить игру вам нужно ввести:**
```
./main
```

## Компоновка файла `main.cpp` на Windows
Для выполнения необходимо установить Visual Studio и дополнительную рабочую нагрузку Разработка настольных приложений на C++ или Build Tools командной строки для Visual Studio.

Если вы установили Visual Studio 2017 или более поздней версии в Windows 11 или более поздней версии, откройте меню Пуск и выберите Все приложения. Прокрутите вниз и откройте папку Visual Studio. Выберите элемент Командная строка разработчика для VS, чтобы открыть окно командной строки.

Если вы установили Microsoft Visual C++ Build Tools 2015 в Windows 11 или более поздней версии, откройте меню Пуск и выберите Все приложения. Прокрутите вниз и откройте папку Microsoft Visual C++ Build Tools. Выберите элемент Командная строка Native Tools x86 Visual C++ 2015, чтобы открыть окно командной строки.
```
cd C:\путь-к-папке\Legends-Of-Jobs
cl /c main.cpp
```
Если вы хотите запустить программу `main.exe`, в командной строке введите `main`

## Развлекайтесь!
Меняйте код, информации пользователя, работы, и т.д!

Удачной игры :)
