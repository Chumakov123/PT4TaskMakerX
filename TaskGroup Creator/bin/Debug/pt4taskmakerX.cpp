#include <cmath>
#include <random>
#include <ctime>
#include <cstring>
#include "pt4taskmakerX.h"

char GroupName[100];

string fmt;
int yd, yr, ye, nd, nr, pr, wd, dpos, rpos;
bool nt, ut, fd, fr, dep, rep;

void (*tasks[1000])();
unsigned int taskGroupHash;

int TaskCount = 0;

const string alphabet_str = alphabet;

unsigned int HashString(const char* str, size_t length) {
    unsigned int hash = 5381;
    for (size_t i = 0; i < length; ++i) {
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}

void pt4taskmakerX::RegisterTaskFunction(void (*task)(), const char* taskname) {
	tasks[TaskCount] = task;
	taskGroupHash += HashString(taskname, strlen(taskname));
	++TaskCount;
}

void Show(const string& s) {
	MessageBoxA(nullptr, s.c_str(), "Error", MB_OK | MB_ICONERROR);
}

string ErrorMessage(const string& s) {
	return (s + string(100, ' ')).substr(0, 78);
}

void ErrorInfo(const string& s) {
	pt4taskmaker::TaskText(("\\B" + ErrorMessage(s) + "\\b").c_str(), 0, ye);
	ye = ye + 1;
	if (ye > 5) {
		ye = 0;
	}
}

bool CheckTT() {
	bool result = ut;
	if (!nt) {
		pt4taskmakerX::NewTask("");
		ErrorInfo(ErrMes5);
	}
	return result;
}

int wreal(int w, double x) {
    int result = w;
    if (w == 0) {
        char buffer[100];
        if (fmt[0] == 'f') {
            int precision = std::stoi(fmt.substr(1));
            std::sprintf(buffer, "%.*f", precision, x);
        } else if (fmt[0] == 'e') {
            int exponent = std::stoi(fmt.substr(1));
            std::sprintf(buffer, "%.*e", exponent - 1, x);
        }
        result = strlen(buffer);
        // if (pr <= 0 && x >= 0) {
        //     result += 1;
        // }
    }
    return result;
}

int winteger(int w, int x) {
	int result = w;
	if (w == 0) {
		string x_str = to_string(x);
		result = x_str.length();
	}
	return result;
}


void pt4taskmakerX::NewTask(const char* topic, const char* tasktext) {
	if (nt)
		return;
	pt4taskmaker::CreateTask(topic);
	pt4taskmaker::TaskText(tasktext);
	nt = true;  // вызвана процедура NewTask
	ut = false; // было подключено существующее задание (процедурой UseTask)
	ye = 1;     // текущий номер строки для вывода сообщения об ошибке
	yd = 0;     // текущий номер строки в разделе исходных данных
	yr = 0;     // текущий номер строки в разделе результатов
	nd = 0;     // количество элементов исходных данных
	nr = 0;     // количество элементов результирующих данных
	fd = false; // наличие файловых данных в разделе исходных данных
	fr = false; // наличие файловых данных в разделе результатов
	pr = 2;     // текущая точность вывода вещественных данных
	fmt = "f2"; // текущий формат вывода вещественных данных
	wd = 0;     // текущая ширина поля вывода для чисел
	dpos = 0;	// текущая позиция исходных данных в режиме явного позиционирования
	rpos = 0;	// текущая позиция результирующих данных в режиме явного позиционирования
	dep = false;// включен режим явного позиционирования исходных данных
	rep = false;// включен режим явного позиционирования результирующих данных
}
void pt4taskmakerX::NewTask(const char* tasktext) {
	pt4taskmakerX::NewTask("", tasktext);
}

void pt4taskmakerX::DataComm(const char* comm) {
	if (CheckTT()) return;
	if (!dep) dpos = 0;
	++yd;
	pt4taskmaker::DataComment(comm, 0, yd);
	dep = false;
}

void pt4taskmakerX::Data(const char* s, bool a, int x, int y, int w) {
	pt4taskmaker::DataB(s, a, x, y);
}

void pt4taskmakerX::Data(const char* s, int a, int x, int y, int w) {
	pt4taskmaker::DataN(s, a, x, y, winteger(w, a));
}
void pt4taskmakerX::Data(const char* s, double a, int x, int y, int w) {
	pt4taskmaker::DataR(s, a, x, y, wreal(w, a));
}
void pt4taskmakerX::Data(const char* s, char a, int x, int y, int w) {
	pt4taskmaker::DataC(s, a, x, y);
}
void pt4taskmakerX::Data(const char* s, const char* a, int x, int y, int w) {
	pt4taskmaker::DataS(s, a, x, y);
}

void pt4taskmakerX::Data(const std::vector<bool>& seq) {
	if (CheckTT())
		return;
	int n = seq.size();
    if (n == 0) return;
	if (!dep) dpos = 0;
	++yd;
    int w = 5;
    int wmax = 80 / (w + 2);
    if (n > wmax) n = wmax;

	int i = 0;
    for (auto e : seq) {
        ++i;
        if (i > wmax || (dep && (dpos + i * (w + 2) > 79))) {
            ++yd;
            i = 1;
			dep = false;
			dpos = 0;
        }
		if (!dep) {
        	DataInternal("", e, pt4taskmaker::Center(i, n, w, 2), yd, w);
		}
		else {
			DataInternal("", e, (i - 1) * (w + 2) ,yd, w);
		}
    }
	dep = false;
}
void pt4taskmakerX::Data(const vector<int>& seq) {
	if (CheckTT()) return;
	int n = seq.size();
	if (n == 0) return;
	if (!dep) dpos = 0;
	++yd;
	int w = wd;
	if (w == 0) {
		auto max_length = max_element(seq.begin(), seq.end(), 
            [](int a, int b) { return to_string(a).length() < to_string(b).length(); });
        w = to_string(*max_length).length();
	}
	int wmax = 80 / (w + 2);
	if (n > wmax) n = wmax;

	int i = 0;
	for (auto e : seq) {
		++i;
		if (i > wmax || (dep && (dpos + i * (w + 2) > 79))) {
			++yd;
			i = 1;
			dep = false;
			dpos = 0;
		}
		if (!dep) {
        	DataInternal("", e, pt4taskmaker::Center(i, n, w, 2), yd, w);
		}
		else {
			DataInternal("", e, (i - 1) * (w + 2) ,yd, w);
		}
	}
	dep = false;
}
void pt4taskmakerX::Data(const std::vector<double>& seq) {
	if (CheckTT())
		return;
	int n = seq.size();
	if (n == 0)	return;
	if (!dep) dpos = 0;
	++yd;
	int w = wd;
	if (w == 0) {
		for (double e : seq) {
			int currentW = wreal(0, e);
			w = max(w, currentW);
		}
	}
	int wmax = 80 / (w + 2);
	if (n > wmax)
		n = wmax;
	
	int i = 0;
	for (auto e : seq) {
		++i;
		if (i > wmax || (dep && (dpos + i * (w + 2) > 79))) {
			++yd;
			i = 1;
			dep = false;
			dpos = 0;
		}
		if (!dep) {
        	DataInternal("", e, pt4taskmaker::Center(i, n, w, 2), yd, w);
		}
		else {
			DataInternal("", e, (i - 1) * (w + 2) ,yd, w);
		}
	}
	dep = false;
}
void pt4taskmakerX::Data(const std::vector<char>& seq) {
	if (CheckTT())
		return;
	int n = seq.size();
	if (n == 0) return;
	if (!dep) dpos = 0;
	++yd;
	int w = 3;
	int wmax = 80 / (w + 2);
	if (n > wmax) n = wmax;
	
	int i = 0;
	for (auto e : seq) {
		++i;
		if (i > wmax || (dep && (dpos + i * (w + 2) > 79))) {
			++yd;
			i = 1;
			dep = false;
			dpos = 0;
		}
		if (!dep) {
        	DataInternal("", e, pt4taskmaker::Center(i, n, w, 2), yd, w);
		}
		else {
			DataInternal("", e, (i - 1) * (w + 2) ,yd, w);
		}
	}
	dep = false;
}
void pt4taskmakerX::Data(const std::vector<string>& seq) {
	if (CheckTT())
		return;
	int n = seq.size();
	if (n == 0) return;
	if (!dep) dpos = 0;
	++yd;
	size_t max_length = 0;
    for (auto s : seq) {
        max_length = max(max_length, s.length());
    }
	int w = max_length + 2;
	int wmax = 80 / (w + 2);
    if (n > wmax) n = wmax;

	int i = 0;
    for (auto e : seq) {
        ++i;
        if (i > wmax || (dep && (dpos + i * (w + 2) > 79))) {
            ++yd;
            i = 1;
			dep = false;
			dpos = 0;
        }
		if (!dep) {
        	DataInternal("", e.c_str(), pt4taskmaker::Center(i, n, w, 2), yd, w);
		}
		else {
			DataInternal("", e.c_str(), (i - 1) * (w + 2) ,yd, w);
		}
    }
	dep = false;
}

void pt4taskmakerX::ResComm(const char* comm)
{
	if (CheckTT()) return;
	if (!rep) rpos = 0;
	++yr;
	pt4taskmaker::ResultComment(comm, 0, yr);
	rep = false;
}
void pt4taskmakerX::Res(const char* s, bool a, int x, int y, int w) {
	pt4taskmaker::ResultB(s, a, x, y);
}

void pt4taskmakerX::Res(const char* s, int a, int x, int y, int w) {
	pt4taskmaker::ResultN(s, a, x, y, winteger(w, a));
}
void pt4taskmakerX::Res(const char* s, double a, int x, int y, int w) {
	pt4taskmaker::ResultR(s, a, x, y, wreal(w, a));
}
void pt4taskmakerX::Res(const char* s, char a, int x, int y, int w) {
	pt4taskmaker::ResultC(s, a, x, y);
}
void pt4taskmakerX::Res(const char* s, const char* a, int x, int y, int w) {
	pt4taskmaker::ResultS(s, a, x, y);
}

void pt4taskmakerX::Res(const std::vector<bool>& seq) {
	if (CheckTT())
		return;
	int n = seq.size();
    if (n == 0) return;
	if (!rep) rpos = 0;
	++yr;
    int w = 5;
    int wmax = 80 / (w + 2);
    if (n > wmax) n = wmax;

	int i = 0;
    for (auto e : seq) {
        ++i;
        if (i > wmax || (rep && (rpos + i * (w + 2) > 79))) {
            ++yr;
            i = 1;
			rep = false;
			rpos = 0;
        }
		if (!rep) {
			ResInternal("", e, pt4taskmaker::Center(i, n, w, 2), yr, w);
		}
		else {
			ResInternal("", e, (i - 1) * (w + 2) ,yr, w);
		}
    }
	rep = false;
}
void pt4taskmakerX::Res(const vector<int>& seq) {
	if (CheckTT()) return;
	int n = seq.size();
	if (n == 0) return;
	++yr;
	if (!rep) rpos = 0;
	int w = wd;
	if (w == 0) {
		auto max_length = max_element(seq.begin(), seq.end(), 
            [](int a, int b) { return to_string(a).length() < to_string(b).length(); });
        w = to_string(*max_length).length();
	}
	int wmax = 80 / (w + 2);
	if (n > wmax) n = wmax;

	int i = 0;
	for (auto e : seq) {
		++i;
		if (i > wmax || (rep && (rpos + i * (w + 2) > 79))) {
			++yr;
			i = 1;
			rep = false;
			rpos = 0;
		}
		if (!rep) {
			ResInternal("", e, pt4taskmaker::Center(i, n, w, 2), yr, w);
		}
		else {
			ResInternal("", e, (i - 1) * (w + 2) ,yr, w);
		}
	}
	rep = false;
}
void pt4taskmakerX::Res(const std::vector<double>& seq) {
	if (CheckTT()) return;
	int n = seq.size();
	if (n == 0) return;
	if (!rep) rpos = 0;
	++yr;
	int w = wd;
	if (w == 0) {
		for (double e : seq) {
			int currentW = wreal(0, e);
			w = max(w, currentW);
		}
	}
	int wmax = 80 / (w + 2);
	if (n > wmax) n = wmax;
	
	int i = 0;
	for (auto e : seq) {
		++i;
		if (i > wmax || (rep && (rpos + i * (w + 2) > 79))) {
			++yr;
			i = 1;
			rep = false;
			rpos = 0;
		}
		if (!rep) {
			ResInternal("", e, pt4taskmaker::Center(i, n, w, 2), yr, w);
		}
		else {
			ResInternal("", e, (i - 1) * (w + 2) ,yr, w);
		}
	}
	rep = false;
}
void pt4taskmakerX::Res(const std::vector<char>& seq) {
	if (CheckTT())
		return;
	int n = seq.size();
	if (n == 0) return;
	if (!rep) rpos = 0;
	++yr;
	int w = 3;
	int wmax = 80 / (w + 2);
	if (n > wmax) n = wmax;
	
	int i = 0;
	for (auto e : seq) {
		++i;
		if (i > wmax || (rep && (rpos + i * (w + 2) > 79))) {
			++yr;
			i = 1;
			rep = false;
			rpos = 0;
		}
		if (!rep) {
			ResInternal("", e, pt4taskmaker::Center(i, n, w, 2), yr, w);
		}
		else {
			ResInternal("", e, (i - 1) * (w + 2) ,yr, w);
		}
	}
	rep = false;
}
void pt4taskmakerX::Res(const std::vector<string>& seq) {
	if (CheckTT())
		return;
	int n = seq.size();
	if (n == 0) return;
	if (!rep) rpos = 0;
	++yr;
	size_t max_length = 0;
    for (auto s : seq) {
        max_length = max(max_length, s.length());
    }
	int w = max_length + 2;
	int wmax = 80 / (w + 2);
    if (n > wmax) n = wmax;

	int i = 0;
    for (auto e : seq) {
        ++i;
        if (i > wmax || (rep && (rpos + i * (w + 2) > 79))) {
            ++yr;
            i = 1;
			rep = false;
			rpos = 0;
        }
		if (!rep) {
			ResInternal("", e.c_str(), pt4taskmaker::Center(i, n, w, 2), yr, w);
		}
		else {
			ResInternal("", e.c_str(), (i - 1) * (w + 2) ,yr, w);
		}
    }
	rep = false;
}

void pt4taskmakerX::SetWidth(int n) {
	if ((n >= 0) && (n <= 20)) {
		wd = n;
	}
}
void pt4taskmakerX::SetPrecision(int n) {
	if (CheckTT()) return;
	if (abs(n) > 10) return;
	pr = n;
	if (n < 0) {
		fmt = "e" + to_string(-n);
		n = 0;
	}
	else if (n == 0) {
		fmt = "e6";
	}
	else {
		fmt = 'f' + to_string(n);
	}
	pt4taskmaker::SetPrecision(n);
}
void pt4taskmakerX::SetTestCount(int n) {
	if (CheckTT()) return;
	pt4taskmaker::SetTestCount(n);
}
void pt4taskmakerX::SetRequiredDataCount(int n) {
	if (CheckTT()) return;
	pt4taskmaker::SetRequiredDataCount(n);
}

int pt4taskmakerX::CurrentTest() {
	if (CheckTT()) return 0;
	return pt4taskmaker::CurrentTest();
}

void pt4taskmakerX::ShowInfo(const char *info) {
	pt4taskmaker::ShowInfo(info);
}

int pt4taskmakerX::Random(int M, int N) {
	return pt4taskmaker::RandomN(M, N);
}
double pt4taskmakerX::Random() {
	return (double)rand()/(double)RAND_MAX;
}
double pt4taskmakerX::Random(double A, double B) {
	return pt4taskmaker::RandomR(A, B);
}
double pt4taskmakerX::Random1(double A, double B) {
	return Random(round(A*10), round(B*10))/10 + Random() * 1.0e-7;
}
double pt4taskmakerX::Random2(double A, double B) {
	return Random(round(A*100), round(B*100))/100 + Random() * 1.0e-7;
}

string pt4taskmakerX::RandomName(int len) {
    string result;
	int n = alphabet_str.length();

    for (int i = 0; i < len; ++i) {
		result.push_back(alphabet_str[pt4taskmakerX::Random(0, n - 1)]);
    }

    return result;
}

void pt4taskmakerX::GetGroupName(const char* FilePath) {

	// удаление пути и расширения
	string str(FilePath);
	size_t lastSlash = str.find_last_of("/\\");
	size_t lastDot = str.find_last_of('.');
	string result;

	if (lastDot != std::string::npos && (lastSlash == std::string::npos || lastDot > lastSlash)) {
		result = str.substr(lastSlash + 1, lastDot - lastSlash - 1);
	}
	else {
		result = str.substr(lastSlash + 1);
	}

    // приведение префикса к верхнему регистру
    string prefix = result.substr(0, 3);
    for (size_t i = 0; i < prefix.size(); ++i) {
        if (prefix[i] >= 'a' && prefix[i] <= 'z') {
            prefix[i] -= ('a' - 'A'); 
        }
    }
    if (prefix == "PT4") {
        // удаление префикса PT4
        result.erase(0, 3);
	}

	// удаление суффикса, определяющего язык интерфейса
	size_t underscorePos = result.find('_');
	if (underscorePos != std::string::npos) {
		result.erase(underscorePos);
	}
	strcpy(GroupName, result.c_str());
}

void __stdcall RunTask(int num) {
	bool ut0;
	try {
		if ((num > 0) && (num <= TaskCount)) {
			tasks[num - 1]();
		}
	} catch (const std::exception& e) {
        Show(e.what());
    }
	nt = false;
	ut0 = ut;
	ut = false;

	if (ut0) return;
	if (nd == 0 && !fd) {
        Show(ErrMes6);
    }
    if (nr == 0 && !fr) {
        Show(ErrMes7);
    }
}

string GenerateGroupKey() {
	taskGroupHash += HashString(GroupName, strlen(GroupName));
	string res = "GK";
	res += to_string(taskGroupHash);
    return res;
}

void pt4taskmakerX::NewGroup(const char* GroupDescription, const char* GroupAuthor, const char* GroupKey, int Options)
{
	if (TaskCount == 0) {
		string name = GroupName;
		Show("Группа" + name + " не содержит заданий.");
		return;
	}
	if (TaskCount > 999) {
		string name = GroupName;
		Show("Группа" + name + " содержит более 999 заданий.");
		return;
	}
	//string GroupKey = GenerateGroupKey();
	string GK = GroupKey;
	if ((Options & OptionUseAddition) == OptionUseAddition)
		GK += "#UseAddition#";
	if ((Options & OptionHideExamples) == OptionHideExamples)
		GK += "#HideExamples#";
	pt4taskmaker::CreateGroup(GroupName, GroupDescription, GroupAuthor,
		GK.c_str(), TaskCount, RunTask);
}

void pt4taskmakerX::UseTask(const char* GroupName, int TaskNumber) {
	if (ut) return;
	pt4taskmaker::UseTask(GroupName, TaskNumber);
	ut = true;
}
void pt4taskmakerX::UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription) {
	if (ut) return;
	pt4taskmaker::UseTask(GroupName, TaskNumber, TopicDescription);
	ut = true;
}

int pt4taskmakerX::CurrentLanguage() {
	return pt4taskmaker::CurrentLanguage();
}

char* pt4taskmakerX::CurrentLocale() {
	return pt4taskmaker::CurrentLocale();
}

char* pt4taskmakerX::CurrentVersion() { // добавлено в версии 4.10
	return pt4taskmaker::CurrentVersion();
}

vector<const char*> pt4taskmakerX::GetWords() {
	vector<const char*> result;
	int n = pt4taskmaker::WordCount();
	for ( int i = 0; i < n; ++i) {
		result.push_back(pt4taskmaker::WordSample(i));
	}
	return result;
}
const char* pt4taskmakerX::RandomWord() {
	return pt4taskmaker::WordSample(pt4taskmaker::RandomN(0, pt4taskmaker::WordCount() -1));
}
vector<const char*> pt4taskmakerX::GetEnWords() {
	vector<const char*> result;
	int n = pt4taskmaker::EnWordCount();
	for ( int i = 0; i < n; ++i) {
		result.push_back(pt4taskmaker::EnWordSample(i));
	}
	return result;
}
const char* pt4taskmakerX::RandomEnWord() {
	return pt4taskmaker::EnWordSample(pt4taskmaker::RandomN(0, pt4taskmaker::EnWordCount() -1));
}
vector<const char*> pt4taskmakerX::GetSentences() {
	vector<const char*> result;
	int n = pt4taskmaker::SentenceCount();
	for ( int i = 0; i < n; ++i) {
		result.push_back(pt4taskmaker::SentenceSample(i));
	}
	return result;
}
const char* pt4taskmakerX::RandomSentence() {
	return pt4taskmaker::SentenceSample(pt4taskmaker::RandomN(0, pt4taskmaker::SentenceCount() -1));
}
vector<const char*> pt4taskmakerX::GetEnSentences() {
	vector<const char*> result;
	int n = pt4taskmaker::EnSentenceCount();
	for ( int i = 0; i < n; ++i) {
		result.push_back(pt4taskmaker::EnSentenceSample(i));
	}
	return result;
}
const char* pt4taskmakerX::RandomEnSentence() {
	return pt4taskmaker::EnSentenceSample(pt4taskmaker::RandomN(0, pt4taskmaker::EnSentenceCount() -1));
}
vector<const char*> pt4taskmakerX::GetTexts() {
	vector<const char*> result;
	int n = pt4taskmaker::TextCount();
	for ( int i = 0; i < n; ++i) {
		result.push_back(pt4taskmaker::TextSample(i));
	}
	return result;
}
const char* pt4taskmakerX::RandomText() {
	return pt4taskmaker::TextSample(pt4taskmaker::RandomN(0, pt4taskmaker::TextCount() -1));
}
vector<const char*> pt4taskmakerX::GetEnTexts() {
	vector<const char*> result;
	int n = pt4taskmaker::EnTextCount();
	for ( int i = 0; i < n; ++i) {
		result.push_back(pt4taskmaker::EnTextSample(i));
	}
	return result;
}
const char* pt4taskmakerX::RandomEnText() {
	return pt4taskmaker::EnTextSample(pt4taskmaker::RandomN(0, pt4taskmaker::EnTextCount() -1));
}

void pt4taskmakerX::DataFileInteger(const char* FileName) {
	if (CheckTT()) return;
	++yd;
	dep = false;
	dpos = 0;
	if (yd > 5) {
		DataComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	size_t w = 0;
	try {
        FILE* file = std::fopen(FileName, "rb");
        if (file != nullptr) {
            int a;
            while (std::fread(&a, sizeof(int), 1, file) == 1) {
                char buffer[100];
                std::sprintf(buffer, "%d", a);
                size_t len = std::strlen(buffer);
                if (len > w) {
                    w = len;
                }
            }
            std::fclose(file);
		}
	} catch (const std::exception& ex) {
		string fname(FileName);
        DataComm(("\\B"+ErrorMessage("FileError("+ fname +"): ") + ex.what()).c_str());
        return;
	}
	fd = true;
	pt4taskmaker::DataFileN(FileName, yd, w + 2);
}
void pt4taskmakerX::DataFileReal(const char* FileName) {
	if (CheckTT()) return;
	++yd;
	dep = false;
	dpos = 0;
	if (yd > 5) {
		DataComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	int w = 0;
	try {
		FILE* file = std::fopen(FileName, "rb");
		if (file != nullptr) {
			double a;
			while (std::fread(&a, sizeof(double), 1, file) == 1) {
				int s = wreal(0, a);
				if (s > w) {
					w = s;
				}
			}
			std::fclose(file);
		}
	} catch (const std::exception& ex) {
		string fname(FileName);
        DataComm(("\\B"+ErrorMessage("FileError("+ fname +"): ") + ex.what()).c_str());
        return;
	}
	fd = true;
	pt4taskmaker::DataFileR(FileName, yd, w + 2);
}
void pt4taskmakerX::DataFileChar(const char* FileName) {
	if (CheckTT()) return;
	++yd;
	dep = false;
	dpos = 0;
	if (yd > 5) {
		DataComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	fd = true;
	pt4taskmaker::DataFileC(FileName, yd, 5);
}
void pt4taskmakerX::DataFileString(const char* FileName) {
	if (CheckTT()) return;
	++yd;
	dep = false;
	dpos = 0;
	if (yd > 5) {
		DataComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	size_t w = 0;
	try {
		FILE* file = std::fopen(FileName, "rb");
		if (file != nullptr) {
			ShortString a;
			while (std::fread(&a, sizeof(ShortString), 1, file) == 1) {
				size_t len = std::strlen(a);
				if (len > w)
					w = len;
			}
			std::fclose(file);
		}
	} catch (const std::exception& ex) {
		string fname(FileName);
        DataComm(("\\B"+ErrorMessage("FileError("+ fname +"): ") + ex.what()).c_str());
        return;
	}
	fd = true;
    pt4taskmaker::DataFileS(FileName, yd, w + 4);
}
void pt4taskmakerX::DataText(const char* FileName, int LineCount) {
	if (CheckTT()) return;
	dep = false;
	dpos = 0;
	if (LineCount > 0) {
		++yd;
		if (yd > 5) {
			DataComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
			return;
		}
		fd = true;
		int yd2 = yd + LineCount - 1;
		if (yd2 > 5) {
			yd2 = 5;
		}
		pt4taskmaker::DataFileT(FileName, yd, yd2);
		yd = yd2;
	}
	else {
		pt4taskmaker::DataFileT(FileName, 0, 0);
	}

}
void pt4taskmakerX::ResFileInteger(const char* FileName) {
	if (CheckTT()) return;
	++yr;
	rep = false;
	rpos = 0;
	if (yr > 5) {
		ResComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	size_t w = 0;
	try {
		FILE* file = std::fopen(FileName, "rb");
		if (file != nullptr) {
			int a;
			while (std::fread(&a, sizeof(int), 1, file) == 1) {
				std::string s = std::to_string(a);
				size_t len = s.length();
				if (len > w)
					w = len;
			}
			std::fclose(file);
		}
	} catch (const std::exception& ex) {
		string fname(FileName);
        ResComm(("\\B"+ErrorMessage("FileError("+ fname +"): ") + ex.what()).c_str());
        return;
	}
	fr = true;
	pt4taskmaker::ResultFileN(FileName, yr, w + 2);
}
void pt4taskmakerX::ResFileReal(const char* FileName) {
	if (CheckTT()) return;
	ResComm(fmt.c_str());
	++yr;
	rep = false;
	rpos = 0;
	if (yr > 5) {
		ResComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	int w = 0;
	try {
		FILE* file = std::fopen(FileName, "rb");
		if (file != nullptr) {
			double a;
			while (std::fread(&a, sizeof(double), 1, file) == 1) {
				int s = wreal(0, a);
				if (s > w) {
					w = s;
				}
			}
			std::fclose(file);
		}
	} catch (const std::exception& ex) {
		string fname(FileName);
        ResComm(("\\B"+ErrorMessage("FileError("+ fname +"): ") + ex.what()).c_str());
        return;
	}
	fr = true;
	pt4taskmaker::ResultFileR(FileName, yr, w + 2);
}
void pt4taskmakerX::ResFileChar(const char* FileName) {
	if (CheckTT()) return;
	++yr;
	rep = false;
	rpos = 0;
	if (yr > 5) {
		ResComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	fr = true;
	pt4taskmaker::ResultFileC(FileName, yr, 5);
}
void pt4taskmakerX::ResFileString(const char* FileName) {
	if (CheckTT()) return;
	++yr;
	rep = false;
	rpos = 0;
	if (yr > 5) {
		ResComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
		return;
	}
	size_t w = 0;
	try {
		FILE* file = std::fopen(FileName, "rb");
		if (file != nullptr) {
			ShortString a;
			while (std::fread(&a, sizeof(ShortString), 1, file) == 1) {
				size_t len = std::strlen(a);
				if (len > w)
					w = len;
			}
			std::fclose(file);
		}
	} catch (const std::exception& ex) {
		string fname(FileName);
        ResComm(("\\B"+ErrorMessage("FileError("+ fname +"): ") + ex.what()).c_str());
        return;
	}
	fr = true;
    pt4taskmaker::ResultFileS(FileName, yr, w + 4);
}
void pt4taskmakerX::ResText(const char* FileName, int LineCount) {
	if (CheckTT()) return;
	rep = false;
	rpos = 0;
	if (LineCount > 0) {
		++yr;
		if (yr > 5) {
			ResComm(("\\B"+ErrorMessage(ErrMes1)+"\b").c_str());
			return;
		}
		fr = true;
		int yr2 = yr + LineCount - 1;
		if (yr2 > 5) {
			yr2 = 5;
		}
		pt4taskmaker::ResultFileT(FileName, yr, yr2);
		yr = yr2;
	}
	else {
		pt4taskmaker::ResultFileT(FileName, 0, 0);
	}

}

void pt4taskmakerX::ConvertToShortString(string s, ShortString buf)
{
	buf[0] = (char)s.length();
	for (size_t i = 1; i <= s.length(); i++)
		buf[i] = s[i-1];
}

string pt4taskmakerX::BoolToString(bool b) {
	auto lang = pt4taskmaker::CurrentLanguage();
	if ((lang & (lgVB || lgPython || lgPython3 || lgVBNET)) != 0) {
		return b ? "True" : "False";
	}
	else if ((lang & lg1C) != 0) {
		return b ? "Истина" : "Ложь";
	}
	else if ((lang & lgR) != 0) {
		return b ? "TRUE" : "FALSE";
	}
	else {
		return b ? "true" : "false";
	}
}