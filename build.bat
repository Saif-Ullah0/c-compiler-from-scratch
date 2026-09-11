@echo off
if not exist build mkdir build

g++ -std=c++14 -Wall -Wextra -Iinclude ^
    src\main.cpp ^
    src\lexer\lexer.cpp ^
    src\lexer\keyword_table.cpp ^
    src\utils\file_io.cpp ^
    -o build\compiler.exe

if %ERRORLEVEL% EQU 0 (
    echo [OK] build\compiler.exe
) else (
    echo [FAIL] exit code %ERRORLEVEL%
)