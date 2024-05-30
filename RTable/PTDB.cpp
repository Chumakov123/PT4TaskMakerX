#include <algorithm>
#include <stdexcept>
#include "PTDB.h"

string Country::ToString() const {
  string res;
  res.append(_name);
  res.append(33 - _name.size(), ' ');
  res.append(_capital);
  res.append(20 - _capital.size(), ' ');
  res.append(_continent);
  res.append(9 - _continent.size(), ' ');
  res.append(13 - to_string(_population).size(), ' ');
  res.append(to_string(_population));
  return res;
}

string Student::ToString() const {
  string res;
  res.append(_name);
  res.append(11 - _name.size(), ' ');
  if (_gender == Mal) {
    res.append(" Male   ");
  }
  else {
    res.append(" Female ");
  }
  res.append(to_string(_height));
  res.append(4 - to_string(_height).size(), ' ');
  res.append(2 - to_string(_cls).size(), ' ');
  res.append(to_string(_cls));
  if (_inSunSchool)
    res.append("  TRUE");
  else
    res.append(" FALSE");
  return res.c_str();
}

vector<string> split(const string &s, char delimiter) {
  vector<string> tokens;
  string token;
  size_t start = 0, end = 0;
  while ((end = s.find(delimiter, start)) != string::npos) {
    token = s.substr(start, end - start);
    tokens.push_back(token);
    start = end + 1;
  }
  tokens.push_back(s.substr(start));
  return tokens;
}

vector<Country> GetCountries(string &fname) {
  vector<string> v {
"Abkhazia,Sukhumi,Asia,240705",
"Afghanistan,Kabul,Asia,33369945",
"Albania,Tirana,Europe,2886026",
"Algeria,Algeria,Africa,40375954",
"Andorra,Andorra la Vella,Europe,76098",
"Angola,Luanda,Africa,25830958",
"Antigua and Barbuda,St. John\'s,America,92738",
"Argentina,Buenos Aires,America,43131966",
"Armenia,Yerevan,Asia,2998600",
"Australia,Canberra,Australia,25028000",
"Austria,Vienna,Europe,8579747",
"Azerbaijan,Baku,Asia,9730500",
"Bahamas,Nassau,America,392718",
"Bahrain,Manama,Asia,1316500",
"Bangladesh,Dhaka,Asia,160991563",
"Barbados,Bridgetown,America,285006",
"Belarus,Minsk,Europe,9498400",
"Belgium,Brussels,Europe,11250659",
"Belize,Belmopan,America,360838",
"Benin,Porto Novo,Africa,10315244",
"Bhutan,Thimphu,Asia,784103",
"Bolivia,Sucre,America,11410651",
"Bosnia and Herzegovina,Sarajevo,Europe,3791622",
"Botswana,Gaborone,Africa,2303820",
"Brazil,Brasilia,America,205738331",
"Brunei,Bandar Seri Bagawan,Asia,428874",
"Bulgaria,Sofia,Europe,7202198",
"Burkina Faso,Ouagadougou,Africa,18450494",
"Burundi,Bujumbura,Africa,11552561",
"Cambodia,Phnom Penh,Asia,15827241",
"Cameroon,Yaounde,Africa,23924407",
"Canada,Ottawa,America,34988000",
"Cape Verde,Praia,Africa,526993",
"Central African Republic,Bangui,Africa,4998493",
"Chad,N\'Djamena,Africa,14496739",
"Chile,Santiago,America,18006407",
"China,Beijing,Asia,1379022000",
"Colombia,Santa Fe de Bogota,America,48803000",
"Comoros,Moroni,Africa,806153",
"Costa Rica,San Jose,America,4773130",
"Cote d\'Ivoire,Yamoussoukro,Africa,23254184",
"Croatia,Zagreb,Europe,4190669",
"Cuba,Havana,America,11392889",
"Cyprus,Nicosia,Asia,848319",
"Czech Republic,Prague,Europe,10546120",
"Democratic Republic of Congo,Kinshasa,Africa,79722624",
"Denmark,Copenhagen,Europe,5668743",
"Djibouti,Djibouti,Africa,899598",
"Dominica,Roseau,America,73016",
"Dominican Republic,Santo Domingo,America,10648613",
"East Timor,Dili,Asia,1212107",
"Ecuador,Quito,America,15427000",
"Egypt,Cairo,Africa,91545000",
"El Salvador,San Salvador,America,6146419",
"Equatorial Guinea,Malabo,Africa,845060",
"Eritrea,Asmara,Africa,5351680",
"Estonia,Tallinn,Europe,1315944",
"Ethiopia,Addis Ababa,Africa,92206005",
"Federated States of Micronesia,Palikir,Islands,104966",
"Fiji,Suva,Islands,897537",
"Finland,Helsinki,Europe,5471753",
"France,Paris,Europe,64513242",
"Gabon,Libreville,Africa,1763142",
"Gambia,Banjul,Africa,2054986",
"Georgia,Tbilisi,Asia,3720400",
"Germany,Berlin,Europe,82162000",
"Ghana,Accra,Africa,28033375",
"Greece,Athens,Europe,10846979",
"Grenada,St. George\'s,America,107327",
"Guatemala,Guatemala,America,16176133",
"Guinea,Conakry,Africa,12947122",
"Guinea-Bissau,Bissau,Africa,1888429",
"Guyana,Georgetown,America,801623",
"Haiti,Port-au-Prince,America,10911819",
"Honduras,Tegucigalpa,America,8725111",
"Hungary,Budapest,Europe,9823000",
"Iceland,Reykjavik,Europe,332529",
"India,New Delhi,Asia,1294186000",
"Indonesia,Jakarta,Asia,260581100",
"Iran,Tehran,Asia,79003827",
"Iraq,Baghdad,Asia,37547686",
"Ireland,Dublin,Europe,4635400",
"Israel,Jerusalem,Asia,8522000",
"Italy,Rome,Europe,60665551",
"Jamaica,Kingston,America,2930050",
"Japan,Tokyo,Asia,126960000",
"Jordan,Amman,Asia,6879300",
"Kazakhstan,Astana,Asia,17753200",
"Kenya,Nairobi,Africa,47251449",
"Kiribati,South Tarawa,Islands,114405",
"Kuwait,Kuwait City,Asia,4007146",
"Kyrgyzstan,Bishkek,Asia,6008600",
"Laos,Vientiane,Asia,6693300",
"Latvia,Riga,Europe,1959900",
"Lebanon,Beirut,Asia,5988153",
"Lesotho,Maseru,Africa,2160309",
"Liberia,Monrovia,Africa,4503438",
"Libya,Tripoli,Africa,6330159",
"Liechtenstein,Vaduz,Europe,37622",
"Lithuania,Vilnius,Europe,2869690",
"Luxembourg,Luxembourg,Europe,576249",
"Macedonia,Skopje,Europe,2069172",
"Madagascar,Antananarivo,Africa,24915822",
"Malawi,Lilongwe,Africa,16310431",
"Malaysia,Kuala Lumpur,Asia,31700000",
"Maldives,Male,Asia,341256",
"Mali,Bamako,Africa,18134835",
"Malta,Valletta,Europe,434403",
"Marshall Islands,Majuro,Islands,53069",
"Mauritania,Nouakchott,Africa,3631775",
"Mauritius,Port Louis,Africa,1261208",
"Mexico,Mexico City,America,122273473",
"Moldova,Chisinau,Europe,3553100",
"Monaco,Monaco,Europe,37863",
"Mongolia,Ulaanbaatar,Asia,2966294",
"Montenegro,Podgorica,Europe,622218",
"Morocco,Rabat,Africa,33996000",
"Mozambique,Maputo,Africa,28751362",
"Myanmar,Nay Pyi Taw,Asia,54363426",
"Namibia,Windhoek,Africa,2513981",
"Nepal,Kathmandu,Asia,28850717",
"Netherlands,Amsterdam,Europe,16985621",
"New Zealand,Wellington,Islands,4602900",
"Nicaragua,Managua,America,6198154",
"Niger,Niamey,Africa,20715285",
"Nigeria,Abuja,Africa,186987563",
"North Korea,Pyongyang,Asia,25281327",
"Northern Mariana Islands,Pyongyang,Islands,55389",
"Norway,Oslo,Europe,5275100",
"Oman,Muscat,Asia,4088690",
"Pakistan,Islamabad,Asia,194521264",
"Palau,Melekeok,Islands,21501",
"Panama,Panama,America,3764166",
"Papua New Guinea,Port Moresby,Islands,7776115",
"Paraguay,Asuncion,America,7003404",
"Peru,Lima,America,31488625",
"Philippines,Manila,Asia,102921200",
"Poland,Warsaw,Europe,38437239",
"Portugal,Lisbon,Europe,10374822",
"Qatar,Doha,Asia,2269672",
"Republic of Congo,Brazzaville,Africa,4740992",
"Romania,Bucharest,Europe,19759968",
"Russia,Moscow,Europe,146544710",
"Rwanda,Kigali,Africa,11262564",
"Samoa,Apia,Islands,194523",
"San Marino,San Marino,Europe,31950",
"Sao Tome and Principe,Sao Tome,Africa,194390",
"Saudi Arabia,Riyadh,Asia,32248200",
"Senegal,Dakar,Africa,15589485",
"Serbia,Belgrade,Europe,7114393",
"Seychelles,Victoria,Africa,97026",
"Sierra Leone,Freetown,Africa,6592102",
"Singapore,Singapore,Asia,5469724",
"Slovakia,Bratislava,Europe,5421349",
"Slovenia,Ljubljana,Europe,2086300",
"Solomon Islands,Honiara,Islands,594934",
"Somalia,Mogadishu,Africa,11079013",
"South Africa,Pretoria,Africa,54956900",
"South Korea,Seoul,Asia,51431100",
"South Ossetia,Tskhinval,Asia,53532",
"South Sudan,Juba,Africa,12733427",
"Spain,Madrid,Europe,46423064",
"Sri Lanka,Colombo,Asia,20810816",
"St. Kitts and Nevis,Basseterre,America,56183",
"St. Lucia,Castries,America,186383",
"St. Vincent and the Grenadines,Kingstown,America,109644",
"Sudan,Khartoum,Africa,41175541",
"Suriname,Paramaribo,America,547610",
"Swaziland,Mbabane,Africa,1304063",
"Sweden,Stockholm,Europe,9838480",
"Switzerland,Bern,Europe,8236600",
"Syria,Damascus,Asia,18563595",
"Tajikistan,Dushanbe,Asia,8593600",
"Tanzania,Dodoma,Africa,55155473",
"Thailand,Bangkok,Asia,65323000",
"Togo,Lome,Africa,7496833",
"Tonga,Nuku\'alofa,Islands,106915",
"Trinidad and Tobago,Port of Spain,America,1364973",
"Tunis,Tunisia,Africa,10982754",
"Turkey,Ankara,Asia,78741053",
"Turkmenistan,Ashgabat,Asia,5438670",
"Tuvalu,Funafuti,Islands,9943",
"UAE,Abu Dhabi,Asia,9266971",
"Uganda,Kampala,Africa,40322768",
"Ukraine,Kiev,Europe,42504274",
"United Kingdom,London,Europe,65341183",
"United States of America,Washington,America,324085000",
"Uruguay,Montevideo,America,3415866",
"Uzbekistan,Tashkent,Asia,31807000",
"Vanuatu,Port Vila,Australia,270470",
"Vatican City,Vatican City,Europe,842",
"Venezuela,Caracas,America,31109000",
"Vietnam,Hanoi,Asia,92700000",
"Yemen,Sana\'a,Asia,27477600",
"Zambia,Lusaka,Africa,16717332",
"Zimbabwe,Harare,Africa,15966810"
  };
  FILE *file = fopen(fname.c_str(), "w");
  if (file == nullptr) {
    string error_message = "File " + fname + " not found";
    throw runtime_error(error_message);
  }
  vector<Country> res;
  for (auto line : v)
  {
    fputs((line + '\n').c_str(), file);
    vector<string> words = split(line, ',');
    string name = words[0];
    string capital = words[1];
    string continent = words[2];
    int population = stoi(words[3]);
    continent.erase(std::remove_if(continent.begin(), continent.end(), ::isspace), continent.end());
    res.emplace_back(name, capital, population, continent);
  }
  fclose(file);
  return res;
}

vector<Student> GetStudents(string &fname) {
  vector<string> v {
"Aleksandrov,Male,162,8,Yes",
"Alekseeva,Female,163,7,No",
"Baranov,Male,171,7,Yes",
"Belkin,Male,165,9,Yes",
"Belousova,Female,172,10,No",
"Belyaeva,Female,154,6,No",
"Blinova,Female,155,5,No",
"Bondareva,Female,170,8,No",
"Borisova,Female,161,6,No",
"Bosova,Female,156,6,Yes",
"Chebotarev,Male,170,8,No",
"Chernova,Female,173,10,No",
"Demidov,Male,164,8,Yes",
"Ershov,Male,149,5,No",
"Filippova,Female,155,8,Yes",
"Frolov,Male,156,5,No",
"Govorukhin,Male,191,10,No",
"Grechko,Male,178,10,Yes",
"Grekova,Female,158,5,Yes",
"Ivanov,Male,160,7,Yes",
"Ivanova,Female,157,6,Yes",
"Kolosovsky,Male,178,11,No",
"Komarov,Male,179,10,No",
"Kondratyev,Male,171,10,Yes",
"Kozlov,Male,188,10,Yes",
"Krotov,Male,149,5,Yes",
"Kuznetsova,Female,165,9,No",
"Leonidova,Female,155,5,No",
"Lisitsina,Female,167,11,No",
"Lysenko,Female,172,9,No",
"Marchenko,Male,186,9,No",
"Molchanov,Male,159,7,Yes",
"Orlova,Female,170,10,No",
"Pastukhov,Male,160,6,Yes",
"Petrova,Female,180,10,No",
"Petrovsky,Male,169,7,Yes",
"Petukhov,Male,170,9,Yes",
"Rudenko,Female,152,5,Yes",
"Sergyev,Male,163,6,No",
"Sergyeva,Female,180,11,Yes",
"Sidorov,Male,150,5,No",
"Sinitsin,Male,169,9,No",
"Solovyova,Female,159,6,No",
"Somov,Male,160,5,Yes",
"Sorokina,Female,169,10,Yes",
"Stepanova,Female,151,5,No",
"Timofeev,Male,180,9,Yes",
"Umnov,Male,169,10,Yes",
"Volkova,Female,175,10,Yes",
"Yashin,Male,181,11,Yes",
"Yurieva,Female,164,11,Yes",
"Yusov,Male,165,7,No",
"Zavyalov,Male,162,7,Yes" 
};
  FILE *file = fopen(fname.c_str(), "w");
  if (file == nullptr) {
    string error_message = "File " + fname + " not found";
    throw runtime_error(error_message);
  }
  vector<Student> res;
  for (auto line : v)
  {
    fputs((line + '\n').c_str(), file);
    vector<string> words = split(line, ',');
    string name = words[0];
    int cls = stoi(words[3]);
    int height = stoi(words[2]);
    TGender gender;
    if (words[1] == "Male") {
      gender = Mal;
    } 
    else {
      gender = Fem;
    }  
    bool inSunSchool;
    words[4].erase(std::remove_if(words[4].begin(), words[4].end(), ::isspace), words[4].end());
    if (words[4] == "Yes") {
      inSunSchool = true;
    }
    else {
      inSunSchool = false;
    }
    res.emplace_back(name, gender, height, cls, inSunSchool);
  }
  fclose(file);
  return res;
}