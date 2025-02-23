@echo off

cls
g++ -o sort_comparison.exe main.cpp

if %errorlevel% equ 0 (
    echo Compiled successfully
    echo

    echo Запуск программы...
    sort_comparison.exe data/input50000.txt data/input100000.txt data/input500000.txt data/input1000000.txt 
) else (
    echo Compilation error
)

pause