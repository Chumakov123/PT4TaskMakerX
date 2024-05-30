#ifndef MYLIB_H
#define MYLIB_H
#define DllExport __declspec(dllexport)

extern "C" {
    DllExport int add(int a, int b);
    DllExport void fstream_use();
    DllExport void sstream_use();
    DllExport void string_use();
    DllExport void vector_use();
    DllExport void map_use();
    DllExport void numeric_use();
    DllExport void functional_use();
    DllExport void algorithm_use();
    DllExport void random_use();
    DllExport void windows_use();
    DllExport void stdexcept_use();
}

#endif // MYLIB_H
