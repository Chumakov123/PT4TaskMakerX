"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\bin\g++.exe" ^
-std=c++14 -m32 -fdata-sections -ffunction-sections -oS -Og -O2 ^
-shared MyLib.cpp ^
-o MyLib-x86.dll ^
-Wl,--enable-stdcall-fixup,--gc-sections,--strip-all