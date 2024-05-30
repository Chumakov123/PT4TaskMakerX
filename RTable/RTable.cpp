#include "PTDB.h"
#include "pt4taskmakerX.h"
#include "linqcpp.h"

using namespace pt4taskmakerX;

DefineGroupName;

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

void __stdcall inittaskgroup() {
	pt::NewGroup("Data frame processing in R", "M. E. Abramyan, 2024", "GroupKeyHere");
}

const char* topic1 = "Databases (countries)";
const char* topic = "Databases (students)";

DefineTask(Task21) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries (Страны) и строка {S} \= название одной
    из стран. Для получения таблицы следует вызвать функцию GetCountries.
    Каждая страна имеет поля Name (Название, строковое поле), Capital 
    (Столица, строковое поле), WorldPart (часть света, строковое поле), 
    Population (Население, целочисленное поле).
    Вывести описание страны {S}, используя функцию PutCountryData.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n = pt::Random(0, (int)a.size() - 1);
    pt::Data("Filename = ", name.c_str(), "S = ", a[n].Name().c_str());
    pt::Res("", a[n].ToString().c_str());
}
DefineTask(Task22) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries (Страны) и строка {Cap} \= название столицы одной 
    из стран. Для получения таблицы следует вызвать функцию GetCountries.
    Каждая страна имеет поля Name (Название, строковое поле), Capital 
    (Столица, строковое поле), WorldPart (часть света, строковое поле), 
    Population (Население, целочисленное поле). Найти страну со столицей {Cap} 
    и вывести ее описание, используя функцию PutCountryData.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n = pt::Random(0, (int)a.size() - 1);
    pt::Data("Filename = ", name.c_str(), "Cap = ", a[n].Capital().c_str());
    pt::Res("", a[n].ToString().c_str());
}
DefineTask(Task23) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries и целое число {N}.
    Найти все страны, население которых не превосходит {N}.
    Вывести количество найденных стран и их описания.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n = pt::Random(50000.0, 500000.0);
    pt::Data("Filename = ", name.c_str(), "N = ", n);
    auto b = Select(Where(a, [n](const Country& c) {return c.Population() <= n;}),
        [](const Country& c) {return c.ToString();});
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Task24) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries, строка {WPart} и целое число {N}.
    Найти все страны с населением, большим {N}, расположенные в части 
    света {WPart}. Вывести количество найденных стран и их описания.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    auto s = a[pt::Random(0, (int)a.size() - 1)].Continent();
    int n = pt::Random(500000.0, 5000000.0);
    pt::Data("Filename = ", name.c_str(), "WPart = ", s.c_str(), "N = ", n);

    auto b = Select(Where(a, [s, n](const Country& e) {
        return e.Population() > n && e.Continent() == s;
    }), [](const Country& e) { return e.ToString(); });

    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Task25) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries, строка {WPart} и целые числа {N}_1 и {N}_2 ({N}_1~<~{N}_2).
    Найти все страны, расположенные в части света {WPart} и имеющие численность
    населения между {N}_1 и {N}_2 включительно. Вывести количество найденных стран
    и их описания, отсортировав описания по возрастанию численности населения.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    auto s = a[pt::Random(0, (int)a.size() - 1)].Continent();
    int n1 = pt::Random(500000.0, 1000000.0);
    int n2 = pt::Random((double)n1, 5000000.0);
    pt::Data("Filename = ", name.c_str(), "WPart = ", s.c_str());
    pt::Data("N_1 = ", n1, "N_2 = ", n2);

    auto b = Select(OrderBy(Where(a, [s, n1, n2](const Country& e) {
        return e.Population() >= n1 && e.Population() <= n2 && e.Continent() == s;
    }), [](const Country& e1, const Country& e2) {
        return e1.Population() < e2.Population();
    }), [](const Country& e) {
        return e.ToString();
    });

    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Task26) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries и целое число {N}.
    Найти все страны, названия столиц которых имеют длину {N} символов.
    Вывести количество найденных стран и их описания, отсортировав описания
    по частям света в алфавитном порядке, а в пределах одной части света \=
    по названиям столиц (тоже в алфавитном порядке).)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n1 = Random(4, 12);
    pt::Data("Filename = ", name.c_str(), "N = ", n1);
    auto b = Select(ThenBy(OrderBy(Where(a, [n1](const Country& c) {return c.Capital().size() == n1;}),
        [](const Country& c1, const Country& c2) {return c1.Capital() < c2.Capital();}),
        [](const Country& c1, const Country& c2) {return c1.Continent() < c2.Continent();}),
        [](const Country& c) {return c.ToString();}
    );
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Task27) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries и целые числа {N}_1 и {N}_2 ({N}_1~<~{N}_2).
    Найти все страны с численностью населения между {N}_1 и {N}_2 включительно
    и сгруппировать найденные страны по частям света.
    Перебирая части света в алфавитном порядке, вывести для каждой 
    из них название и количество {K} найденных стран.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n1 = pt::Random(500000.0, 5000000.0);
    int n2 = pt::Random((double)n1, 50000000.0);
    pt::Data("Filename = ", name.c_str(), "N_1 = ", n1, "N_2 = ", n2);

    auto b = GroupBy(OrderBy(Where(a, [n1, n2](const Country& e) {return e.Population() >= n1 && e.Population() <= n2;}),
        [](const Country& e1, const Country& e2) {return e1.Continent() < e2.Continent();}),
        [](const Country& e) {return e.Continent();}
    );
    pt::SetWidth(2);
    for (const auto& e : b) {
        pt::Res("", e.first.c_str(), "K = ", (int)e.second.size());
    }
}
DefineTask(Task28) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries и целые числа {N}_1 и {N}_2 ({N}_1~<~{N}_2).
    Сгруппировать страны по частям света и для каждой части света найти
    суммарную численность населения для стран с численностью населения
    между {N}_1 и {N}_2 включительно. Для каждой части света вывести
    ее название и найденную суммарную численность {S}, отсортировав части света
    по убыванию суммарной численности (для некоторых частей света
    суммарная численность может быть равна~0).)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n1 = pt::Random(500000.0, 5000000.0);
    int n2 = pt::Random((double)n1, 50000000.0);
    pt::Data("Filename = ", name.c_str(), "N_1 = ", n1, "N_2 = ", n2);

    auto groups = GroupBy(a, [](const Country& e) {return e.Continent();});
    vector<pair<string, int>> res;
    for (auto group : groups) {
        int sum = 0;
        for (auto e : group.second) {
            if ((e.Population() >= n1) && (e.Population() <= n2)) {
                sum += e.Population();
            }
        }
        res.push_back({group.first, sum});
    }
    sort(res.begin(), res.end(), 
        [](const pair<string,int>& e1, const pair<string,int>& e2) {
            return e1.second > e2.second;
        });

    pt::SetWidth(9);
    for (const auto& e : res) {
        pt::Res("", e.first.c_str(), "S = ", e.second);
    }
}
DefineTask(Task29) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries и целые числа {N}_1 и {N}_2 ({N}_1~<~{N}_2).
    Сгруппировать страны по частям света и для каждой части света найти все страны
    с численностью населения между {N}_1 и {N}_2 включительно.
    Перебирая части света в алфавитном порядке, вывести для каждой из них
    название и среднее значение населения {A} найденных стран.
    Если требуемые страны для какой-либо части света отсутствуют,
    то в качестве {A} вывести~0.0.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n1 = pt::Random(500000.0, 5000000.0);
    int n2 = pt::Random((double)n1, 50000000.0);
    if (pt::CurrentTest() == 3) {
        n1 = pt::Random(500000.0, 700000.0);
        n2 = pt::Random(700000.0, 800000.0);
    }
    pt::Data("Filename = ", name.c_str(), "N_1 = ", n1, "N_2 = ", n2);
    auto groups = GroupBy(OrderBy(a, [](const Country& c1, const Country& c2) {return c1.Continent() < c2.Continent();}),
        [](const Country& c) {return c.Continent();});
    for (auto group : groups) {
        double average = Average(Select(Where(group.second, [n1,n2](const Country& c) {return (c.Population() >= n1)&&(c.Population() <= n2);}),
            [](const Country& c) { return c.Population();}));
        pt::Res("", group.first.c_str(), "A = ", average);
    }
}
DefineTask(Task30) {
    pt::NewTask(topic1,
    R"(Дан файл с таблицей Countries и целое число {N}.
    Сгруппировать страны по частям света и для каждой части света найти
    {N} стран с минимальным населением (или все страны, если в этой части света
    имеется менее {N} стран). Вывести описания найденных стран, отсортировав их
    по названию частей света в алфавитном порядке, а в пределах 
    одной части света \= по возрастанию численности.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetCountries(name);
    pt::DataText(name.c_str(), 0);
    int n1 = pt::Random(2, 12);
    pt::Data("Filename = ", name.c_str(), "N = ", n1);

    auto groups = GroupBy(OrderBy(a, [](const Country& c1, const Country& c2) {return c1.Continent() < c2.Continent();}),
        [](const Country& c) {return c.Continent();});
    pt::SetWidth(9);
    for (auto group : groups) {
        group.second = Take(OrderBy(group.second, 
            [](const Country& c1, const Country& c2) {
                return c1.Population() < c2.Population();
            }), n1);
        pt::Res(Select(group.second, [](const Country& e) {return e.ToString();}));
    }
}
DefineTask(Taska01) {
    pt::NewTask(topic, 
    R"(Дан файл с таблицей Students (Ученики) и целое число {H}.
    Для получения таблицы следует вызвать функцию GetStudents.
    Каждый ученик имеет поля Name (Фамилия, строковое поле), Gender 
    (Пол, перечисление со значениями Male и Female, Height (Рост, 
    целочисленное поле), Class (Класс, целочисленное поле), DevClub 
    (член клуба программистов DevClub, логическое поле). 
    Найти всех учеников, имеющих рост выше {H} см.
    Вывести количество найденных учеников и их описания, 
    используя функцию PutStudentCountAndData.)");
    int h = pt::Random(150, 210);
    if (pt::CurrentTest() <= 2)
	h = pt::Random(170, 180);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::Data("Filename = ", name.c_str(), "H = ", h);
    a = Where(a, [h](const Student& s) {return s.Height() > h;});
    auto b = Select(a, [](const Student& s) { return s.ToString(); });
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska02) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students (Ученики) и целое число {H}.
    Для получения таблицы следует вызвать функцию GetStudents.
    Каждый ученик имеет поля Name (Фамилия, строковое поле), Gender 
    (Пол, перечисление со значениями Male и Female, Height (Рост, 
    целочисленное поле), Class (Класс, целочисленное поле), DevClub 
    (член клуба программистов DevClub, логическое поле). 
    Найти всех девочек, имеющих рост ниже {H} см.
    Вывести количество найденных учеников и их описания, 
    используя функцию PutStudentCountAndData.)");
    int h = pt::Random(150, 210);
    if (pt::CurrentTest() <= 2)
	h = pt::Random(180, 190);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::Data("Filename = ", name.c_str(), "H = ", h);
    auto b = Select(Where(a, [h](const Student& e) {
        return e.Height() < h && e.Gender() == Fem;
    }), [](const Student& e) {
        return e.ToString();
    });
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska03) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С}_1 и {C}_2 ({С}_1~\l~{C}_2).
    Найти всех учеников, которые учатся в классах от {С}_1 до {C}_2 включительно.
    Вывести количество найденных учеников и их описания.)");
    int c1 = pt::Random(5, 11);
    int c2 = pt::Random(c1, 11);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C_1 = ", c1, "C_2 = ", c2);
    pt::SetWidth(0);
    auto b = Select(Where(a, [c1, c2](const Student& e) {
        return e.Cls() >= c1 && e.Cls() <= c2;
    }), [](const Student& e) {
        return e.ToString();
    });
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska04) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С}_1 и {C}_2 ({С}_1~\l~{C}_2).
    Найти всех учеников, которые учатся в классах от {С}_1 до {C}_2 включительно
    и при этом являются членами клуба программистов.
    Вывести количество найденных учеников и их описания.)");
    int c1 = pt::Random(5, 11);
    int c2 = pt::Random(c1, 11);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C_1 = ", c1, "C_2 = ", c2);
    pt::SetWidth(0);
    auto b = Select(Where(a, [c1, c2](const Student& e) {
        return e.Cls() >= c1 && e.Cls() <= c2 && e.InSunSchool();
    }), [](const Student& e) {
        return e.ToString();
    });
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska05) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С} и {H}.
    Вывести количество учеников класса {C}, рост которых больше {H} см.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1, h;
    int num = pt::Random(1, 10);
    int res = -1;
    while (res != num) {
        c1 = pt::Random(5, 11);
        h = pt::Random(150, 180);
        res = Select(Where(a, [c1, h](const Student& e) {
            return e.Cls() == c1 && e.Height() > h;
        }), [](const Student& e) {
            return e.ToString();
        }).size();
    }
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C = ", c1, "H = ", h);
    pt::SetWidth(2);
    pt::Res("", res);
}
DefineTask(Taska06) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С}_1, {H}_1, {C}_2, {H}_2.
    Ответить на два вопроса:
    1) верно ли, что у \Iнекоторых\i учеников класса {C}_1 рост \Iбольше\i {H}_1 см,
    2) верно ли, что у \Iвсех\i учеников класса {C}_2 рост \Iменьше\i {H}_2 см?
    В качестве ответа на каждый вопрос вывести логическое значение \t или \f.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1, c2, h1, h2;
    bool b1 = pt::Random(0, 1) == 0;
    bool b2 = pt::Random(0, 1) == 0;
    bool res1 = !b1;
    bool res2 = !b2;
    while (res1 != b1 || res2 != b2) {
        c1 = pt::Random(5, 11);
        c2 = pt::Random(5, 11);
        h1 = pt::Random(150, 210);
        h2 = pt::Random(150, 210);
        res1 = Any(Where(a, [c1, h1](const Student& e) { return e.Cls() == c1; }), [h1](const Student& e) { return e.Height() > h1; });
        res2 = All(Where(a, [c2, h2](const Student& e) { return e.Cls() == c2; }), [h2](const Student& e) { return e.Height() < h2; });
    }
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str());
    pt::Data("C_1 = ", c1, "H_1 = ", h1);
    pt::Data("C_2 = ", c2, "H_2 = ", h2);
    pt::Res("Ответ на вопрос 1: ", res1, "Ответ на вопрос 2: ", res2);
    pt::SetTestCount(9);
}
DefineTask(Taska07) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С}_1, {H}_1, {C}_2, {H}_2.
    Вывести два вещественных числа:
    {A}_1 \= средний рост учеников класса {C}_1, рост которых \Iбольше\i {H}_1 см,
    {A}_2 \= средний рост учеников класса {C}_2, рост которых \Iменьше\i {H}_2 см.
    Известно, что числа {A}_1 и {A}_2 существуют.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1, c2, h1, h2;
    double res1 = 0.0;
    double res2 = 0.0;
    while (res1 == 0.0 || res2 == 0.0) {
        c1 = pt::Random(5, 11);
        c2 = pt::Random(5, 11);
        h1 = pt::Random(150, 210);
        h2 = pt::Random(150, 210);
        res1 = Average(Select(Where(a, 
            [c1, h1](const Student& e) { 
                return e.Cls() == c1 && e.Height() > h1; 
            }), 
            [](const Student& e) { 
                return e.Height(); 
            }));
        res2 = Average(Select(Where(a, 
            [c2, h2](const Student& e) { 
                return e.Cls() == c2 && e.Height() < h2; 
            }), 
            [](const Student& e) {
                return e.Height(); 
            }));
    }
    pt::SetWidth(3);
    pt::Data("Filename = ", name.c_str());
    pt::Data("C_1 = ", c1, "H_1 = ", h1);
    pt::Data("C_2 = ", c2, "H_2 = ", h2);
    pt::Res("A_1 = ", res1, "A_2 = ", res2);
    pt::SetTestCount(9);
}
DefineTask(Taska08) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С}_1, {H}_1, {C}_2, {H}_2.
    Вывести два вещественных числа:
    {A}_1 \= средний рост учеников класса {C}_1, рост которых \Iбольше\i {H}_1 см,
    {A}_2 \= средний рост учеников класса {C}_2, рост которых \Iменьше\i {H}_2 см.
    Если требуемые учащиеся отсутствуют, то в качестве результата вывести 0.0.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1, c2, h1, h2;
    int b1 = pt::Random(0, 1);
    int b2 = pt::Random(0, 1);
    double res1 = -1.0;
    double res2 = -1.0;
    while ((sign(res1) != sign(b1))||(sign(res2) != sign(b2))) {
        c1 = pt::Random(5, 11);
        c2 = pt::Random(5, 11);
        h1 = pt::Random(150, 210);
        h2 = pt::Random(150, 210);
        res1 = Average(Select(Where(a, 
            [c1, h1](const Student& e) { 
                return e.Cls() == c1 && e.Height() > h1; 
            }), 
            [](const Student& e) { return e.Height(); }));
        res2 = Average(Select(Where(a, 
            [c2, h2](const Student& e) { 
                return e.Cls() == c2 && e.Height() < h2; 
            }), 
            [](const Student& e) { return e.Height(); }));
    }
    pt::SetWidth(3);
    pt::Data("Filename = ", name.c_str());
    pt::Data("C_1 = ", c1, "H_1 = ", h1);
    pt::Data("C_2 = ", c2, "H_2 = ", h2);
    pt::Res("A_1 = ", res1, "A_2 = ", res2);
    pt::SetTestCount(9);
}
DefineTask(Taska09) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С}_1, {C}_2.
    Вывести два целых числа:
    {A}_1 \= максимальный рост среди учеников класса {C}_1,
    {A}_2 \= минимальный рост среди учеников класса {C}_2.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1, c2;
    int res1 = -1;
    int res2 = -1;
    c1 = pt::Random(5, 11);
    c2 = pt::Random(5, 11);
    res1 = Max(Select(Where(a, 
        [c1](const Student& e) { 
            return e.Cls() == c1; 
        }), 
        [](const Student& e) { 
            return e.Height(); 
        }));
    res2 = Min(Select(Where(a, 
        [c2](const Student& e) { 
            return e.Cls() == c2; 
        }), 
        [](const Student& e) { return e.Height(); }));
    pt::SetWidth(3);
    pt::Data("Filename = ", name.c_str());
    pt::Data("C_1 = ", c1, "C_2 = ", c2);
    pt::Res("A_1 = ", res1, "A_2 = ", res2);
    pt::SetTestCount(9);
}
DefineTask(Taska10) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {C}_1, {H}_1, {C}_2, {H}_2.
    Вывести два целых числа:
    {A}_1 \= минимальный рост среди учеников класса {C}_1, рост которых \Iбольше\i {H}_1 см,
    {A}_2 \= максимальный рост среди учеников класса {C}_2, рост которых \Iменьше\i {H}_2 см.
    Если требуемые учащиеся отсутствуют, то в качестве результата вывести 0.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1, c2, h1, h2;
    int b1 = pt::Random(0, 2);
    int b2 = pt::Random(0, 2);
    switch (pt::CurrentTest()) {
        case 4: b1 = 0; break;
        case 6: b2 = 0; break;
    }
    int res1 = -1;
    int res2 = -1;
    while (sign(res1) != sign(b1) || sign(res2) != sign(b2)) {
        c1 = pt::Random(5, 11);
        c2 = pt::Random(5, 11);
        h1 = pt::Random(150, 210);
        h2 = pt::Random(150, 210);
        res1 = Min(Select(Where(a,
            [c1, h1](const Student& e) {
                return e.Cls() == c1 && e.Height() > h1;
            }),
            [](const Student& e) { return e.Height(); }));
        res2 = Max(Select(Where(a,
            [c2, h2](const Student& e) {
                return e.Cls() == c2 && e.Height() < h2;
            }),
            [](const Student& e) { return e.Height(); }));
    }
    pt::SetWidth(3);
    pt::Data("Filename = ", name.c_str());
    pt::Data("C_1 = ", c1, "H_1 = ", h1);
    pt::Data("C_2 = ", c2, "H_2 = ", h2);
    pt::Res("A_1 = ", res1, "A_2 = ", res2);
    pt::SetTestCount(9);
}
DefineTask(Taska11) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целое число {С}.
    Найти всех учеников, которые учатся в классе {С},
    и отсортировать их в порядке возрастания роста.
    Вывести количество найденных учеников и их описания.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1 = pt::Random(5, 11);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C = ", c1);
    a = Where(a, [c1](const Student& s) {return s.Cls() == c1;});
    a = OrderBy(a, [](const Student& s1, const Student& s2) {
        return s1.Height() < s2.Height();
    });
    auto b = Select(a, [](const Student& s) {return s.ToString();});
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska12) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целое число {C}.
    Найти всех мальчиков, которые учатся в классе {C},
    и отсортировать их в порядке убывания роста.
    Вывести количество найденных учеников и их описания.)");
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    int c1 = pt::Random(5, 11);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C = ", c1);
    auto b = Select(OrderBy(Where(a, 
        [c1](const Student& e) {
            return e.Cls() == c1 && e.Gender() == Mal;
        }), 
        [](const Student& e1, const Student& e2) { return e1.Height() > e2.Height(); }),
        [](const Student& e) { return e.ToString(); });
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska13) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {C}_1 и {C}_2 ({C}_1~\l~{C}_2).
    Найти всех учеников, которые учатся в классах от {C}_1 до {C}_2 включительно,
    и отсортировать их по возрастанию номера класса,
    а в пределах одного класса \= по убыванию роста.
    Вывести количество найденных учеников и их описания.)");
    int c1 = pt::Random(5, 11);
    int c2 = pt::Random(c1, 11);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C_1 = ", c1, "C_2 = ", c2);
    pt::SetWidth(0);
    auto b = Select(ThenBy(OrderBy(Where(a, 
        [c1, c2](const Student& e) { return e.Cls() >= c1 && e.Cls() <= c2;}), 
        [](const Student& e1, const Student& e2) { return e1.Height() > e2.Height(); }), 
        [](const Student& e1, const Student& e2) { return e1.Cls() < e2.Cls(); }),
        [](const Student& e) { return e.ToString(); });
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska14) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {C}_1 и {C}_2 ({C}_1~\l~{C}_2).
    Найти всех учеников, которые учатся в классах от {C}_1 до {C}_2 включительно
    и кроме этого являются членами клуба программистов,
    и отсортировать их по убыванию номера класса,
    а в пределах одного класса \= по фамилиям в алфавитном порядке.
    Вывести количество найденных учеников и их описания.)");
    int c1 = pt::Random(5, 11);
    int c2 = pt::Random(c1, 11);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C_1 = ", c1, "C_2 = ", c2);
    pt::SetWidth(0);
    auto b = Select(ThenBy(OrderBy(Where(a, 
        [c1, c2](const Student& e) { return e.Cls() >= c1 && e.Cls() <= c2 && e.InSunSchool();}), 
        [](const Student& e1, const Student& e2) { return e1.Name() < e2.Name(); }), 
        [](const Student& e1, const Student& e2) { return e1.Cls() > e2.Cls(); }),
        [](const Student& e) { return e.ToString(); });
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska15) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {C} и {K}.
    Найти {K} самых высоких учеников, которые учатся в классе {C},
    и отсортировать их по убыванию роста.
    Вывести количество найденных учеников и их описания.
    Если имеется менее {K} требуемых учеников, то вывести их всех.)");
    int c1 = pt::Random(5, 11);
    int k = pt::Random(2, 6);
    if (pt::CurrentTest() == 3)
        k = pt::Random(7, 10);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C = ", c1, "K = ", k);
    pt::SetWidth(0);
    auto b = Select(Take(OrderBy(Where(a, 
        [c1](const Student& e) { return e.Cls() == c1; }),
        [](const Student& e1, const Student& e2) { return e1.Height() > e2.Height(); }), k),
        [](const Student& e) {return e.ToString();});
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska16) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {С} и {K}.
    Найти {K} самых низкорослых учеников, которые учатся в классе {С}
    и кроме этого являются членами клуба программистов,
    и отсортировать их по возрастанию роста.
    Вывести количество найденных учеников и их описания.
    Если имеется менее {K} требуемых учеников, то вывести их всех.)");
    int c1 = pt::Random(5, 11);
    int k = pt::Random(2, 4);
    if (pt::CurrentTest() == 3) {
        k = pt::Random(5, 10);
    }
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C = ", c1, "K = ", k);
    pt::SetWidth(0);
    a = Where(a, [c1](const Student& s) { return (s.Cls() == c1)&&(s.InSunSchool());});
    a = OrderBy(a, [](const Student& s1, const Student& s2) {
        return s1.Height() < s2.Height();
    });
    a = Take(a, k);
    auto b = Select(a, [](const Student& s) {return s.ToString();});
    pt::SetWidth(2);
    pt::Res("", (int)b.size());
    pt::Res(b);
}
DefineTask(Taska17) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целое число {С}.
    Сгруппировать всех учеников из класса {С} по длине их имен 
    и вывести для каждой найденной группы связанную с ней длину имени
    и число учеников, имена которых имеют указанную длину.
    Данные упорядочить по убыванию длин имен.)");
    int c = pt::Random(5, 11);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C = ", c);
    pt::SetWidth(0);
    auto b1 = Where(a, [c](const Student& s) {return (s.Cls() == c);});
    auto groups = GroupBy(OrderBy(b1, 
        [](const Student& e1, const Student& e2) { return e1.Name().size() > e2.Name().size();}), 
        [](const Student& e) {return e.Name().size();});
    for (auto group = groups.rbegin(); group != groups.rend(); group++) 
        pt::Res("Длина имени = ", (int)group->first, "Количество учеников = ", (int)group->second.size());
}

DefineTask(Taska18) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {C}_1 и {C}_2 ({C}_1~\l~{C}_2).
    Сгруппировать всех учеников, которые учатся в классах от {C}_1 до {C}_2 
    включительно, по начальной букве их имен и вывести для каждой найденной 
    группы связанную с ней букву и число учеников, имена которых начинаются 
    с указанной буквы. Данные упорядочить в алфавитном порядке букв.)");
    int c1 = pt::Random(5, 9);
    int c2 = pt::Random(c1, 11);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::SetWidth(2);
    pt::Data("Filename = ", name.c_str(), "C_1 = ", c1, "C_2 = ", c2);
    pt::SetWidth(0);
    auto b1 = Where(a, [c1,c2](const Student& s) {return (s.Cls() >= c1 && s.Cls() <= c2);});
    auto groups = GroupBy(OrderBy(b1, 
        [](const Student& e1, const Student& e2) { return e1.Name()[0] < e2.Name()[0];}), 
        [](const Student& e) {return e.Name()[0];});
    for (auto group : groups) 
        pt::Res("Первая буква имени = ", (char)group.first, "Количество учеников = ", (int)group.second.size());
}
DefineTask(Taska19) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {H}_1 и {H}_2 ({H}_1~\l~{H}_2).
    Сгруппировать учеников по полу и для каждого пола выбрать тех учеников,
    рост которых лежит между {H}_1 см и {H}_2 см включительно.
    Вывести вначале количество {K}_{M} выбранных учеников мужского пола,
    а затем \= количество {K}_{F} учеников женского пола.)");
    int h1 = pt::Random(150, 180);
    int h2 = pt::Random(h1, 210);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::Data("Filename = ", name.c_str(), "H_1 = ", h1, "H_2 = ", h2);
    a = Where(a, [h1,h2](const Student& s) { return (s.Height() >= h1) && (s.Height() <= h2);});
    auto groups = GroupBy(a, [](const Student& s) {return s.Gender();});
    pt::SetWidth(2);
    pt::Res("K_M = ", (int)groups[Mal].second.size());
    pt::Res("K_F = ", (int)groups[Fem].second.size());
}
DefineTask(Taska20) {
    pt::NewTask(topic,
    R"(Дан файл с таблицей Students и целые числа {H}_1 и {H}_2 ({H}_1~\l~{H}_2).
    Cгруппировать учеников по классам и для каждого класса выбрать тех учеников,
    рост которых лежит между {H}_1 см и {H}_2 см включительно.
    Перебирая классы в порядке возрастания, вывести для каждого класса
    его значение и средний рост выбранных учеников из этого класса.
    Если требуемые учащиеся в каком-либо классе отсутствуют,
    то в качестве {H} вывести 0.0.)");
    int h1 = pt::Random(150, 180);
    int h2 = pt::Random(h1, 210);
    string name = pt::RandomName(4) + ".tst";
    auto a = GetStudents(name);
    pt::DataText(name.c_str(), 0);
    pt::Data("Filename = ", name.c_str(), "H_1 = ", h1, "H_2 = ", h2);
    auto groups = GroupBy(OrderBy(a, 
        [](const Student& e1, const Student& e2) { return e1.Cls() < e2.Cls();}), 
        [](const Student& e) {return e.Cls();});
    for (auto group : groups) {
        group.second = Where(group.second, [h1, h2](const Student& e) { return e.Height() >= h1 && e.Height() <= h2; });
        pt::Res("Класс = ", group.first, "Средний рост = ", Average(Select(group.second,[](const Student& e) { return e.Height();})));
    }
}