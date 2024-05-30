#include "MyLib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <functional>
#include <algorithm>
#include <random>
#include <windows.h>
#include <stdexcept>

int add(int a, int b) {
    return a + b;
}
void fstream_use(const char* filename) {
    std::ofstream("example.txt") << "Пример использования fstream." << std::endl;
}
void sstream_use(const char* data) {
    std::stringstream ss(data);
    static char buffer[256];
    ss.getline(buffer, 256);
    auto res = buffer;
}
void string_use(const std::string& str, const std::string& substr) {
    size_t pos = str.find(substr);
    auto res = pos;
}
void vector_use() {
    std::vector<int> vec = {10, 20, 30, 40};
    vec.pop_back();
}
void map_use() {
    std::map<int, int> myMap = {{1, 10}, {2, 20}, {3, 30}, {4, 40}};
    myMap.erase(3);
    auto res = myMap;
}
void numeric_use() {
    int numbers[] = {1, 2, 3, 4, 5};
    auto res = std::accumulate(numbers, numbers + 5, 0);
}
void functional_use(int a, int b, std::function<int(int, int)> func) {
    func(a, b);
}
void algorithm_use(int* begin, int* end, int number) {
    auto it = std::find(begin, end, number);
    auto res = it != end;
}
void random_use(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    auto res = dis(gen);
}
void windows_use() {
    MessageBoxA(NULL, "Привет, мир!", "Пример MessageBoxA", MB_OK | MB_ICONINFORMATION);
}
void stdexcept_demo(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Деление на ноль");
    }
    auto res = a / b;
}