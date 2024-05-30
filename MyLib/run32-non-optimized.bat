"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\bin\g++.exe" ^
-std=c++14 -m32 ^
-shared MyLib.cpp ^
-o MyLib-x32-no.dll ^
-Wl,--enable-stdcall-fixup