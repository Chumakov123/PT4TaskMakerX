#include <algorithm>
#include <fstream>
#include "pt4taskmakerX.h"

using namespace pt4taskmakerX;

DefineGroupName;

void __stdcall inittaskgroup() {
  pt::NewGroup("Примеры различных задач", "М. Э. Абрамян, 2017", "qwqfsdf13dfttd");
}

DefineTask(Task1) {
  pt::UseTask("Begin", 1);
}

DefineTask(Task2) {
  pt::UseTask("Begin", 2);
}

DefineTask(Task3) {
  pt::NewTask("Ввод и вывод данных, оператор присваивания",
    R"(Даны стороны прямоугольника~{a} и~{b}.\n
    Найти его площадь {S}~=~{a}\*{b} и периметр {P}~=~2\*({a}\;+\;{b}).)");
  double a = pt::Random(1, 99) / 10,
       b = pt::Random(1, 99) / 10;
  pt::SetWidth(5);
  pt::Data("a = ", a, "b = ", b);
  pt::Res("S = ", a * b, "P = ", 2 * (a + b));
  pt::SetTestCount(3);
}

DefineTask(Task4) {
  pt::NewTask("Двумерные массивы (матрицы): вывод элементов",
    R"(Дана матрица размера~{M}\;\x\;{N} и целое число~{K} (1~\l~{K}~\l~{M}).
    Вывести элементы {K}-й строки данной матрицы.)");
  int m = pt::Random(4, 8),
    n = pt::Random(4, 8),
    k = pt::Random(1, m);
  pt::Data("M = ", m, "N = ", n);
  pt::SetWidth(5);
  for ( int i = 0; i < m; ++i) {
    vector<double> a(n);
    generate(a.begin(), a.end(), [&]() { return pt::Random(-9.99, 9.99); });
    pt::Data(a);
    if (i == k - 1) {
      pt::Res(a);
    }
  }
  pt::SetWidth(0);
  pt::Data("K = ", k);
  pt::SetTestCount(5);
}

DefineTask(Task5) {
  pt::NewTask("Символы и строки: основные операции",
    R"(Дана непустая строка~{S}.
    Вывести ее первый и последний символ.)");
  string s = pt::RandomWord();
  if (pt::CurrentTest() == 3) {
    while (s[0] == s[s.length() - 1]) {
      s = pt::RandomWord();
    }
  }
  pt::Data("S = ", s.c_str());
  pt::Res("Первый символ: ", s[0], "Последний символ: ", s[s.length() - 1]);
  pt::SetTestCount(4);
}

DefineTask(Task6) {
  pt::NewTask("Символьные и строковые файлы",
    R"(Дано целое число~{K} (>\,0) и строковый файл.
    Создать два новых файла: строковый, содержащий первые {K}~символов
    каждой строки исходного файла, и символьный, содержащий {K}-й символ
    каждой строки (если длина строки меньше~{K}, то в строковый файл
    записывается вся строка, а в символьный файл записывается пробел).)");
  string s1 = "1" + pt::RandomName(5) + ".tst",
         s2 = "2" + pt::RandomName(5) + ".tst",
         s3 = "3" + pt::RandomName(5) + ".tst";
  ofstream fs1(s1, ios::binary | ios_base::out),
           fs2(s2, ios::binary | ios_base::out),
           fc3(s3, ios::binary | ios_base::out);
  int k = pt::Random(2, 11),
    n = pt::Random(10, 20),
    jmax = 0;
  for (int i = 1; i < n; ++i) {
    ShortString buf;
    int j = pt::Random(2, 16);
    if (jmax < j)
      jmax = j;
    string s = pt::RandomName(pt::Random(2, 16));
    pt::ConvertToShortString(s, buf);
    fs1.write(buf, 256);
    char c = ' ';
    if (j >= k)
    {
      c = s[k-1];
      buf[0] = (char)k;
    }
    fs2.write(buf, 256);
    fc3.write((char*) &c, 1);
  }
  fs1.close();
  fs2.close();
  fc3.close();
  pt::Data("K = ", k);
  pt::Data("Имя исходного файла: ", s1.c_str(), "Содержимое исходного файла:");
  pt::DataFileString(s1.c_str());
  pt::Data("Имя результирующего строкового файла:  ", s2.c_str());
  pt::Data("Имя результирующего символьного файла: ", s3.c_str());
  pt::ResComm("Содержимое результирующего строкового файла:");
  pt::ResFileString(s2.c_str());
  pt::ResComm("Содержимое результирующего символьного файла:");
  pt::ResFileChar(s3.c_str());
}

DefineTask(Task7) {
  pt::NewTask("Текстовые файлы: основные операции",
    R"(Дан текстовый файл.
    Удалить из него все пустые строки.)");
  string s1 = pt::RandomName(6) + ".tst",
         s2 = pt::RandomName(6) + ".tst",
         s = pt::RandomText();
  ofstream t2(s2.c_str()), t1(s1.c_str());
  t2 << s << endl;
  t2.close();
  const char* s0 = "\r\n\r\n";
  size_t p = s.find(s0);
  while (p != string::npos)
  {
    s.erase(p, 2);
    p = s.find(s0);
  }
  t1 << s << endl;
  t1.close();
  pt::ResText(s1.c_str());
  rename(s2.c_str(), s1.c_str());
  pt::Data("Имя файла", s1.c_str());
  pt::DataText(s1.c_str());
  pt::SetTestCount(3);
}