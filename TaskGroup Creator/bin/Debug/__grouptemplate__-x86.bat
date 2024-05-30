"__compiler__" ^
-std=c++14 -m32 -fdata-sections -ffunction-sections -s -Os ^
-shared pt4taskmaker.cpp pt4taskmakerX.cpp ^
__grouptemplate__.cpp ^
-o PT4__grouptemplate__.dll ^
pt4taskmaker.def ^
-Wl,--enable-stdcall-fixup,--gc-sections