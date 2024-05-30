"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\bin\g++.exe" ^
-std=c++14 -m64 -fdata-sections -ffunction-sections -s -oS -Og -O2 ^
-shared MyLib.cpp ^
-o MyLib-x64.dll ^
-Wl,--enable-stdcall-fixup,--gc-sections