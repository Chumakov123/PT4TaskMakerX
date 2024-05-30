#include "pt4.h"
using namespace std;

#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

#include "linqcpp.h"

struct DataB
{
    string art, cat, country;
    operator string()
    {
        ostringstream os;
        os << "{ art = " << art << ", cat = " << cat
            << ", country = " << country << " }";
        return os.str();
    }
};

istream& operator>>(istream& is, DataB& p)
{
    return is >> p.country >> p.art >> p.cat;
}

struct DataC
{
    int code, discount;
    string shop;
    operator string()
    {
        ostringstream os;
        os << "{ code = " << code << ", discount = " << discount
            << ", shop = " << shop << " }";
        return os.str();
    }
};

istream& operator>>(istream& is, DataC& p)
{
    return is >> p.discount >> p.code >> p.shop;
}

struct DataD
{
    string art, shop;
    int price;
    operator string()
    {
        ostringstream os;
        os << "{ art = " << art << ", shop = " << shop
            << ", price = " << price << " }";
        return os.str();
    }
};

istream& operator>>(istream& is, DataD& p)
{
    return is >> p.art >> p.price >> p.shop;
}

struct DataE
{
    int code;
    string art, shop;
    operator string()
    {
        ostringstream os;
        os << "{ code = " << code << ", art = " << art
            << ", shop = " << shop << " }";
        return os.str();
    }
};

istream& operator>>(istream& is, DataE& p)
{
    return is >> p.code >> p.art >> p.shop;
}

void Solve()
{
    Task("STL7Mix98");
    ifstream f1;
    string name1;
    pt >> name1;
    f1.open(name1.c_str());
    vector<DataB> VB((istream_iterator<DataB>(f1)), istream_iterator<DataB>());
    f1.close();
    ShowLine(VB.begin(), VB.end(), "VB: ");
    pt >> name1;
    f1.open(name1.c_str());
    vector<DataC> VC((istream_iterator<DataC>(f1)), istream_iterator<DataC>());
    f1.close();
    ShowLine(VC.begin(), VC.end(), "VC: ");
    pt >> name1;
    f1.open(name1.c_str());
    vector<DataD> VD((istream_iterator<DataD>(f1)), istream_iterator<DataD>());
    f1.close();
    ShowLine(VD.begin(), VD.end(), "VD: ");
    pt >> name1;
    f1.open(name1.c_str());
    vector<DataE> VE((istream_iterator<DataE>(f1)), istream_iterator<DataE>());
    f1.close();
    ShowLine(VE.begin(), VE.end(), "VE: ");
    string name2;
    pt >> name2;

    ofstream f2(name2.c_str());
    //Решение с использованием linqcpp.h
    auto discounts = make_seq(VE).Join(VB, 
            [](auto e1) {return e1.art; }, 
            [](auto e2) {return e2.art; },
            [](auto e1, auto e2) {return make_tuple(e1.code, e1.art, e1.shop, e2.cat); })
        .Join(VD,
            [](auto e1) { return get<1>(e1) + get<2>(e1);},
            [](auto e2) { return e2.art + e2.shop;},
            [](auto e1, auto e2) {return make_tuple(get<0>(e1), get<1>(e1), get<2>(e1), get<3>(e1), e2.price);})
        .GroupJoin(VC,
            [](auto e1) { return to_string(get<0>(e1))+get<2>(e1);},
            [](auto e2) { return to_string(e2.code) + e2.shop;},
            [](auto e1, auto ee2) { return make_tuple(
                get<3>(e1) + " " + get<2>(e1), //e1.cat + " " + e1.shop
                Select(ee2, [](auto e) { return e.discount; })
                .FirstOrDefault() * get<4>(e1) / 100); });
    auto cats = make_seq(VB).GroupBy([](auto e){ return e.cat; }).Select([](auto e) {return e.first;});
    auto shops = make_seq(VE).GroupBy([](auto e){ return e.shop; }).Select([](auto e) {return e.first;});;
    
    auto r = cats
        .SelectMany([&](auto e1) {
            return shops.Select([&](auto e2) { return e1 + " " + e2; });
        })
        .OrderBy([](auto e1, auto e2) { return e1 < e2; })
        .GroupJoin(discounts, 
            [](auto e1) { return e1; },
            [](auto e2) { return get<0>(e2); }, // e2.cat_shop
            [](auto e1, auto ee2) { return e1 + " " + 
                to_string(make_seq(ee2).Select([](auto e) { return get<1>(e); }).DefaultIfEmpty(-1).Sum()); }); 

    for (const auto& item : r) {
         f2 << item << endl;
    }
    f2.close();
}
