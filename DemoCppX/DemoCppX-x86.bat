"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/bin/g++.exe" ^
-std=c++14 -m32 -fdata-sections -ffunction-sections -s -Os ^
-shared pt4taskmaker.cpp pt4taskmakerX.cpp ^
DemoCppX.cpp ^
-o PT4DemoCppX.dll ^
pt4taskmaker.def ^
-Wl,--enable-stdcall-fixup,--gc-sections