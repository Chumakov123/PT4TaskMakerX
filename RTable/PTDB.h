#ifndef PTDB_H
#define PTDB_H

#include <string>
#include <vector>

using namespace std;

enum TGender { Mal, Fem };

class Country {
private:
  string _name;
  string _capital;
  int _population;
  string _continent;

public:
  Country(string name, string capital, int population, string continent)
    : _name(name), _capital(capital), _population(population), _continent(continent) {}

  Country() = default;

  string Name() const { return _name; }
  string Capital() const { return _capital; }
  int Population() const { return _population; }
  string Continent() const { return _continent; }
  string ToString() const;
};

class Student {
private:
  string _name;
  TGender _gender;
  int _height, _cls;
  bool _inSunSchool;

public:
  Student(string name, TGender gender, int height, int cls, bool inSunSchool)
    : _name(name), _gender(gender), _height(height), _cls(cls), _inSunSchool(inSunSchool) {}

  Student() = default;
  
  string Name() const { return _name; }
  TGender Gender() const { return _gender; }
  int Height() const { return _height; }
  int Cls() const { return _cls; }
  bool InSunSchool() const { return _inSunSchool; }
  string ToString() const;
};

inline TGender StrToTGender(string& a) {
  if (a == "Male")
    return Mal;
  else
    return Fem;
}

inline bool StrToBoolean(string& a) {
  return (a == "Yes");
}

vector<Country> GetCountries(string &fname);
vector<Student> GetStudents(string &fname);

#endif // PTDB_H