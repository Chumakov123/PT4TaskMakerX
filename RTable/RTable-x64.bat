"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/bin/g++.exe" ^
-std=c++14 -m64 -fdata-sections -ffunction-sections -s -Os ^
-shared pt4taskmaker.cpp pt4taskmakerX.cpp ^
PTDB.cpp ^
RTable.cpp ^
-o xPT4RTable.dll ^
pt4taskmaker.def ^
-Wl,--enable-stdcall-fixup,--gc-sections