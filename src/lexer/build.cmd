@echo off
echo Start building... g++ lexer.test.cpp lexer.cpp -o lexer.test.exe
D:\Dev-Cpp\MinGW64\bin\g++ lexer.test.cpp lexer.cpp -o lexer.test.exe -std=gnu++11 -w -I"D:\Dev-Cpp\MinGW64\include" -I"D:\Dev-Cpp\MinGW64\x86_64-w64-mingw32\include" -I"D:\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include" -I"D:\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++" -L"D:\Dev-Cpp\MinGW64\lib" -L"D:\Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib" -O3
echo Build finish!
pause
echo Running...
lexer.test.exe
pause