#ifndef _PT4TASKMAKERX
#define _PT4TASKMAKERX

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include "pt4taskmaker.h"

using ShortString = char[256];

/// макрос для добавления задания в список всех заданий группы
#define DefineTask(name) \
    void name(); \
    struct name ## _Registrar { \
        name ## _Registrar() { RegisterTaskFunction(name, #name); } \
    } name ## _registrar_instance; \
    void name()

/// макрос для получения названия группы заданий
#define DefineGroupName \
    struct _GroupName { \
        _GroupName() { GetGroupName(__FILE__); } \
    } _groupname_instance;

#define alphabet "0123456789abcdefghijklmnoprstuvwxyz"
#define ErrMes1 "Error: Раздел размером более 5 строк не может содержать файловые данные."
#define ErrMes2 "Error: При наличии файловых данных раздел не может содержать более 5 строк."
#define ErrMes3 "Error: Количество исходных данных превысило 200."
#define ErrMes4 "Error: Количество результирующих данных превысило 200."
#define ErrMes5 "Error: При определении задания первой должна вызываться процедура NewTask."
#define ErrMes6 "Error: При определении задания не указаны исходные данные."
#define ErrMes7 "Error: При определении задания не указаны результирующие данные."

//Функции и переменные для внутреннего использования

extern int yd, yr, ye, nd, nr, pr, wd, dpos, rpos;
extern bool nt, ut, fd, fr, dep, rep;

bool CheckTT();
template<typename T>
void DataInternal(const char* s, T a, int x, int y, int w);
template<typename T>
void ResInternal(const char* s, T a, int x, int y, int w);
void ErrorInfo(const string& s);
int winteger(int w, int x);
int wreal(int w, double x);

//*********************************************

namespace pt4taskmakerX
{
	const int OptionUseAddition = 8;        // группа доступна только при наличии файла дополнений
	const int OptionHideExamples = 16;      // не отображать раздел с примером верного решения

	/// Добавление задания (как указатель на функцию) в список заданий. Для внутреннего использования.
	void RegisterTaskFunction(void (*task)(), const char* taskname);

	/// Получение названия группы заданий из названия файла. Для внутреннего использования.
	void GetGroupName(const char* FilePath);

	/// Процедура, с которой должно начинаться определение нового задания.
	/// Должна вызываться в процедуре, созданной макросом DefineTask(procedurename).
	/// Параметр topic определяет имя подгруппы и является необязательным.
	/// Параметр tasktext содержит формулировку задания; отдельные строки
	/// формулировки должны разделяться символом \\n
	void NewTask(const char* topic, const char* tasktext);

	/// Процедура, с которой должно начинаться определение нового задания.
	/// Должна вызываться в процедуре, созданной макросом DefineTask(procedurename).
	/// Параметр tasktext содержит формулировку задания; отдельные строки
	/// формулировки должны разделяться символом \\n
	void NewTask(const char* tasktext);

	void Data(const char* s, bool a, int x, int y, int w);
    void Data(const char* s, int a, int x, int y, int w);
    void Data(const char* s, double a, int x, int y, int w);
    void Data(const char* s, char a, int x, int y, int w);
    void Data(const char* s, const char* a, int x, int y, int w);

	/// Добавляет комментарий в новой строке раздела исходных даннных.
	void DataComm(const char* comm);

	/// Добавляет комментарий в новой строке раздела исходных даннных.
	inline void Data(const char* comm) {
		DataComm(comm);
	}

	/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
	template<typename T>
	void Data(const char* comm, T a) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm, a, 0, yd, wd);
		dep = false;
	}

	/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
	template<typename T>
	void Data(const char* comm1, T a1, const char* comm2) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm1, a1, xLeft, yd, wd);
		pt4taskmaker::DataComment(comm2, xRight, yd);
		dep = false;
	}

	/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
	template<typename T1, typename T2>
	void Data(const char* comm1, T1 a1, const char* comm2, T2 a2) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm1, a1, xLeft, yd, wd);
		DataInternal(comm2, a2, xRight, yd, wd);
		dep = false;
	}
	/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
	template<typename T1, typename T2>
	void Data(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm1, a1, xLeft, yd, wd);
		DataInternal(comm2, a2, 0, yd, wd);
		pt4taskmaker::DataComment(comm3, xRight, yd);
		dep = false;
	}
	/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
	template<typename T1, typename T2, typename T3>
	void Data(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3, T3 a3) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm1, a1, xLeft, yd, wd);
		DataInternal(comm2, a2, 0, yd, wd);
		DataInternal(comm3, a3, xRight, yd, wd);
		dep = false;
	}

	/// Добавляет последовательность логических данных в раздел исходных данных.
	void Data(const std::vector<bool>& seq);

	/// Добавляет последовательность целых чисел в раздел исходных данных.
	void Data(const std::vector<int>& seq);

	/// Добавляет последовательность вещественных чисел в раздел исходных данных.
	void Data(const std::vector<double>& seq);

	/// Добавляет последовательность символов в раздел исходных данных.
	void Data(const std::vector<char>& seq);

	/// Добавляет последовательность строк в раздел исходных данных.
	void Data(const std::vector<string>& seq);

	/// Добавляет комментарий в строке раздела исходных данных, начиная с указанной позиции pos
	inline void DataPos(const char* comm, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((dpos < pos) && (yd > 0)) {
				--yd; // остаемся на текущей строке
			}
			dpos = pos;
		}
		else {
			ErrorInfo("Error: Позиция исходных данных должна быть больше 0 и меньше 79");
			return;
		}
		dep = true;
		Data(comm);
	}
	/// Добавляет данные и комментарии в строке раздела исходных данных, начиная с указанной позиции pos
	template<typename T>
	void DataPos(const char* comm, T a, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((dpos < pos) && (yd > 0)) {
				--yd; // остаемся на текущей строке
			}
			dpos = pos;
		}
		else {
			ErrorInfo("Error: Позиция исходных данных должна быть больше 0 и меньше 79");
			return;
		}
		dep = true;
		Data(comm, a);
	}
	/// Добавляет последовательность данных в строке раздела исходных данных, начиная с указанной позиции pos
	template<typename Container>
	void DataPos(const Container& seq, int pos) {
		if (CheckTT())
		return;
		int n = seq.size();
		if (n == 0) return;

		if (pos > 0 && pos < 79) {
			if ((dpos < pos) && (yd > 0)) {
				--yd; // остаемся на текущей строке
			}
			dpos = pos;
		}
		else {
			ErrorInfo("Error: Позиция исходных данных должна быть больше 0 и меньше 79");
			return;
		}
		dep = true;
		Data((vector<typename Container::value_type>)seq);
	}

	void Res(const char* s, bool a, int x, int y, int w);
    void Res(const char* s, int a, int x, int y, int w);
    void Res(const char* s, double a, int x, int y, int w);
    void Res(const char* s, char a, int x, int y, int w);
    void Res(const char* s, const char* a, int x, int y, int w);

	/// Добавляет комментарий в новой строке раздела результатов.
	void ResComm(const char* comm);
	/// Добавляет комментарий в новой строке раздела результатов.
	inline void Res(const char* comm) {
		ResComm(comm);
	}

	/// Добавляет данные и комментарии в новой строке раздела результатов.
	template<typename T>
	void Res(const char* comm, T a) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm, a, 0, yr, wd);
		rep = false;
	}

	/// Добавляет данные и комментарии в новой строке раздела результатов.
	template<typename T>
	void Res(const char* comm1, T a1, const char* comm2) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm1, a1, xLeft, yr, wd);
		pt4taskmaker::ResultComment(comm2, xRight, yr);
		rep = false;
	}

	/// Добавляет данные и комментарии в новой строке раздела результатов.
	template<typename T1, typename T2>
	void Res(const char* comm1, T1 a1, const char* comm2, T2 a2) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm1, a1, xLeft, yr, wd);
		ResInternal(comm2, a2, xRight, yr, wd);
		rep = false;
	}

	/// Добавляет данные и комментарии в новой строке раздела результатов.
	template<typename T1, typename T2>
	void Res(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm1, a1, xLeft, yr, wd);
		ResInternal(comm2, a2, 0, yr, wd);
		pt4taskmaker::ResultComment(comm3, xRight, yr);
		rep = false;
	}

	/// Добавляет данные и комментарии в новой строке раздела результатов.
	template<typename T1, typename T2, typename T3>
	void Res(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3, T3 a3) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm1, a1, xLeft, yr, wd);
		ResInternal(comm2, a2, 0, yd, wd);
		ResInternal(comm3, a3, xRight, yr, wd);
		rep = false;
	}

	/// Добавляет последовательность логических данных в раздел результатов.
	void Res(const std::vector<bool>& seq);

	/// Добавляет последовательность целых чисел в раздел результатов.
	void Res(const std::vector<int>& seq);

	/// Добавляет последовательность вещественных чисел в раздел результатов.
	void Res(const std::vector<double>& seq);

	/// Добавляет последовательность символов в раздел результатов.
	void Res(const std::vector<char>& seq);

	/// Добавляет последовательность строк в раздел результатов.
	void Res(const std::vector<string>& seq);
	
	/// Добавляет комментарий в строке раздела результирующих данных, начиная с указанной позиции pos
	inline void ResPos(const char* comm, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((rpos < pos) && (yr > 0)) {
				--yr; // остаемся на текущей строке
			}
			rpos = pos;
		}
		else {
			ErrorInfo("Error: Позиция результирующих данных должна быть больше 0 и меньше 79");
			return;
		}
		rep = true;
		Res(comm);
	}
	/// Добавляет данные и комментарии в строке раздела результирующих данных, начиная с указанной позиции pos
	template<typename T>
	void ResPos(const char* comm, T a, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((rpos < pos) && (yr > 0)) {
				--yr; // остаемся на текущей строке
			}
			rpos = pos;
		}
		else {
			ErrorInfo("Error: Позиция результирующих данных должна быть больше 0 и меньше 79");
			return;
		}
		rep = true;
		Res(comm, a);
	}
	/// Добавляет последовательность данных в строке раздела результирующих данных, начиная с указанной позиции pos
	template<typename Container>
	void ResPos(const Container& seq, int pos) {
		if (CheckTT())
		return;
		int n = seq.size();
		if (n == 0) return;

		if (pos > 0 && pos < 79) {
			if ((rpos < pos) && (yr > 0)) {
				--yr; // остаемся на текущей строке
			}
			rpos = pos;
		}
		else {
			ErrorInfo("Error: Позиция результирующих данных должна быть больше 0 и меньше 79");
			return;
		}
		rep = true;
		Res((vector<typename Container::value_type>)seq);
	}

	/// Задает минимальную ширину поля вывода для числовых данных
	/// (числа выравниваются по правому краю поля вывода, 
	/// т.е. при необходимости дополняются слева пробелами).
	/// Если n не лежит в диапазоне 0..10, то вызов процедуры игнорируется.
	/// По умолчанию минимальная ширина поля вывода полагается равной 0.
	void SetWidth(int n);

	/// Задает формат отображения вещественных чисел: 
	/// с фиксированной точкой и n дробными знаками при n > 0,
	/// с плавающей точкой и n дробными знаками при n < 0,
	/// с плавающей точкой и 6 дробными знаками при n = 0.
	/// Если n по модулю превосходит 10, то вызов процедуры игнорируется.
	/// По умолчанию устанавливается формат с фиксированной точкой
	/// и 2 дробными знаками.
	void SetPrecision(int n);

	/// Задает количество тестовых запусков, выполняемых
	/// для проверки правильности программы (от 2 до 10). 
	/// По умолчанию число тестовых запусков полагается равным 5.
	void SetTestCount(int n);

	/// Задает минимально необходимое количество элементов 
	/// исходных данных, которое требуется ввести для правильного
	/// решения задачи в случае текущего набора исходных данных. 
	/// При отсутствии процедуры предполагается,
	/// что для правильного решения надо ввести все исходные данные.
	void SetRequiredDataCount(int n);

	/// Возвращает номер текущего тестового запуска 
	/// (запуски нумеруются от 1).
	int CurrentTest();

	/// Выводит отладочную информацию во всплывающем диалоговом окне
	void ShowInfo(const char *info);

	/// Генерирует случайное целое число в диапазоне от M до N включительно.
	/// Если M >= N, то возвращает M.
	int Random(int M, int N);

	/// Возращает случайное значение в диапазоне от 0 (включительно) до 1 (не включительно)
	double Random(); 

	/// Генерирует случайное вещественное число на промежутке [A, B).
	/// Если промежуток [A, B) пуст, то возвращает A.
	double Random(double A, double B);

	/// Генерирует случайное вещественное число на промежутке [A, B)
	/// с одним дробным знаком и случайной добавкой порядка 1e-7.
	/// Если промежуток [A, B) пуст, то возвращает A, округленное
	/// до одного дробного знака и снабженное добавкой порядка 1e-7.
	double Random1(double A, double B);

	/// Генерирует случайное вещественное число на промежутке [A, B)
	/// с двумя дробными знаками и случайной добавкой порядка 1e-7.
	/// Если промежуток [A, B) пуст, то возвращает A, округленное
	/// до двух дробных знаков и снабженное добавкой порядка 1e-7.
	double Random2(double A, double B);

	/// Генерирует случайную строку длины len, состоящую
	/// из цифр и строчных (т.е. маленьких) латинских букв.
	string RandomName(int len);

	/// Создает новую группу с кратким описанием GroupDescription,
	/// информацией об авторе GroupAuthor, ключом группы GroupKey и набором необязательных опций, объединяемых операцией or.
	/// Имя группы определяется по имени библиотеки (путем отбрасывания префикса PT4
	/// и возможных суффиксов _ru или _en). 
	/// В группу включаются задания, определенные макросом DefineTask.
	/// Процедура NewGroup должна быть вызвана в процедуре inittaskgroup без параметров, которую
	/// необходимо описать в библиотеке с группой заданий (все буквы в имени inittaskgroup - строчные).
	void NewGroup(const char* GroupDescription, const char* GroupAuthor, const char* GroupKey, int Options = 0);
	
	/// Импортирует в создаваемую группу существующее задание
	/// из группы GroupName с номером TaskNumber. Должна вызываться
	/// в процедуре с именем, начинающемся с текста Task.
	void UseTask(const char* GroupName, int TaskNumber);

	/// Импортирует в создаваемую группу существующее задание
	/// из группы GroupName с номером TaskNumber. Должна вызываться
	/// в процедуре с именем, начинающемся с текста Task.
	void UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription);

	/// Позволяет определить текущий язык программирования, выбранный для задачника
	/// Возвращает значения, связанные с константами lgXXX
	int CurrentLanguage();

	/// Возвращает двухбуквенную строку с описанием текущей локали
	/// (в даной версии возвращается либо "ru", либо "en")
	char* CurrentLocale();

	/// Возвращает номер текущей версии задачника в формате "d.dd"
	/// (для версий, меньших 4.10, возвращает "4.00")
	char* CurrentVersion();  // добавлено в версии 4.10

	/// Возвращает массив из 116 русских слов.
	vector<const char*> GetWords();
	/// Возвращает массив из 116 английских слов.
	vector<const char*> GetEnWords();
	/// Возвращает массив из 61 русского предложения.
	vector<const char*> GetSentences();
	/// Возвращает массив из 61 английского предложения.
	vector<const char*> GetEnSentences();
	/// Возвращает массив из 85 русских многострочных текстов.
	/// Строки текста разделяются символом \\n.
	/// В конце текста символ \\n отсутствует.
	vector<const char*> GetTexts();
	/// Возвращает массив из 85 английских многострочных текстов.
	/// Строки текста разделяются символом \\n.
	/// В конце текста символ \\n отсутствует.
	vector<const char*> GetEnTexts();

	/// Возвращает случайное русское слово из массива, 
	/// входящего в конструктор учебных заданий.
	const char* RandomWord();
	/// Возвращает случайное английское слово из массива, 
	/// входящего в конструктор учебных заданий.
	const char* RandomEnWord();
	/// Возвращает случайное русское предложение из массива, 
	/// входящего в конструктор учебных заданий.
	const char* RandomSentence();
	/// Возвращает случайное английское предложение из массива, 
	/// входящего в конструктор учебных заданий.
	const char* RandomEnSentence();
	/// Возвращает случайный русский многострочный текст из массива, 
	/// входящего в конструктор учебных заданий.
	/// Строки текста разделяются символом \\n.
	/// В конце текста символ \\n отсутствует.
	const char* RandomText();
	/// Возвращает случайный английский многострочный текст из массива, 
	/// входящего в конструктор учебных заданий.
	/// Строки текста разделяются символом \\n.
	/// В конце текста символ \\n отсутствует.
	const char* RandomEnText();

	/// Добавляет в задание исходный файл целых чисел
	/// с именем FileName и отображает его содержимое
	/// в разделе исходных данных.
	void DataFileInteger(const char* FileName);
	/// Добавляет в задание исходный файл вещественных чисел
	/// с именем FileName и отображает его содержимое
	/// в разделе исходных данных.
	void DataFileReal(const char* FileName);
	/// Добавляет в задание исходный символьный файл
	/// с именем FileName и отображает его содержимое
	/// в разделе исходных данных. Символы должны
	/// храниться в файле в однобайтной кодировке.
	void DataFileChar(const char* FileName);
	/// Добавляет в задание исходный строковый файл
	/// с элементами типа ShortString и именем FileName 
	/// и отображает его содержимое в разделе исходных данных.
	/// Длина элементов файла не должна превосходить 70 символов.
	/// Строки должны храниться в файле в однобайтной кодировке.
	void DataFileString(const char* FileName);
	/// Добавляет в задание исходный текстовый файл
	/// с именем FileName и отображает его содержимое
	/// в разделе исходных данных. Длина каждой строки
	/// текстового файла не должна превосходить 70 символов.
	/// Текст должен храниться в файле в однобайтной кодировке.
	void DataText(const char* FileName, int LineCount = 5);

	/// Добавляет в задание результирующий файл целых чисел
	/// с именем FileName и отображает его содержимое в разделе результатов.
	void ResFileInteger(const char* FileName);
	/// Добавляет в задание результирующий файл вещественных чисел
	/// с именем FileName и отображает его содержимое в разделе результатов.
	void ResFileReal(const char* FileName);
	/// Добавляет в задание результирующий символьный файл
	/// с именем FileName и отображает его содержимое в разделе результатов.
	/// Символы должны храниться в файле в однобайтной кодировке.
	void ResFileChar(const char* FileName);
	/// Добавляет в задание результирующий строковый файл
	/// с элементами типа ShortString и именем FileName 
	/// и отображает его содержимое в разделе результатов.
	/// Длина элементов файла не должна превосходить 70 символов.
	/// Строки должны храниться в файле в однобайтной кодировке.
	void ResFileString(const char* FileName);
	/// Добавляет в задание результирующий текстовый файл
	/// с именем FileName и отображает его содержимое в разделе результатов. 
	/// Длина каждой строки текстового файла не должна превосходить 70 символов.
	/// Текст должен храниться в файле в однобайтной кодировке.
	void ResText(const char* FileName, int LineCount = 5);

	/// Конвертирует обычную строку в короткую (char[256])
	void ConvertToShortString(string s, ShortString buf);

	/// Процедура, обеспечивающая отображение динамических структур данных
	/// в "объектном стиле" при выполнении заданий в среде PascalABC.NET
	/// (при использовании других сред не выполняет никаких действий)
	void SetObjectStyle();

	/// Устанавливает текущий процесс для последующей передачи ему данных 
	/// числовых типов (при выполнении задания в параллельном режиме)
	void SetProcess(int ProcessRank);

	/// Возвращает логические константы в строковом представлении,
	/// соответствующем текущему языку программирования
	string BoolToString(bool b);

	class pt {
	public:
		/// Дополнительная опция для процедуры NewGroup: 
		/// группа доступна только при наличии связанного с ней файла дополнений.
		static int OptionUseAddition() {
			return pt4taskmakerX::OptionUseAddition;
		}
		/// Дополнительная опция для процедуры NewGroup: 
		/// в заданиях данной группы не будет отображаться пример верного решения.
		static int OptionHideExamples() {
			return pt4taskmakerX::OptionHideExamples;
		}

		/// Процедура, с которой должно начинаться определение нового задания.
		/// Должна вызываться в процедуре, созданной макросом DefineTask(procedurename).
		/// Параметр topic определяет имя подгруппы и является необязательным.
		/// Параметр tasktext содержит формулировку задания; отдельные строки
		/// формулировки должны разделяться символом \\n
		static void NewTask(const char* topic, const char* tasktext) {
			pt4taskmakerX::NewTask(topic, tasktext);
		}

		/// Процедура, с которой должно начинаться определение нового задания.
		/// Должна вызываться в процедуре, созданной макросом DefineTask(procedurename).
		/// Параметр tasktext содержит формулировку задания; отдельные строки
		/// формулировки должны разделяться символом \\n
		static void NewTask(const char* tasktext) {
			pt4taskmakerX::NewTask(tasktext);
		}

		/// Добавляет комментарий в новой строке раздела исходных даннных.
		static void DataComm(const char* comm) {
			pt4taskmakerX::DataComm(comm);
		}

		/// Добавляет комментарий в новой строке раздела исходных даннных.
		static void Data(const char* comm) {
			pt4taskmakerX::DataComm(comm);
		}

		/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
		template<typename T>
		static void Data(const char* comm, T a) {
			pt4taskmakerX::Data(comm, a);
		}

		/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
		template<typename T>
		static void Data(const char* comm1, T a1, const char* comm2) {
			pt4taskmakerX::Data(comm1, a1, comm2);
		}

		/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
		template<typename T1, typename T2>
		static void Data(const char* comm1, T1 a1, const char* comm2, T2 a2) {
			pt4taskmakerX::Data(comm1, a1, comm2, a2);
		}

		/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
		template<typename T1, typename T2>
		static void Data(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3) {
			pt4taskmakerX::Data(comm1, a1, comm2, a2, comm3);
		}

		/// Добавляет данные и комментарии в новой строке раздела исходных даннных.
		template<typename T1, typename T2, typename T3>
		static void Data(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3, T3 a3) {
			pt4taskmakerX::Data(comm1, a1, comm2, a2, comm3, a3);
		}

		/// Добавляет последовательность логических данных в раздел исходных данных.
		static void Data(const std::vector<bool>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Добавляет последовательность целых чисел в раздел исходных данных.
		static void Data(const std::vector<int>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Добавляет последовательность вещественных чисел в раздел исходных данных.
		static void Data(const std::vector<double>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Добавляет последовательность символов в раздел исходных данных.
		static void Data(const std::vector<char>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Добавляет последовательность строк в раздел исходных данных.
		static void Data(const std::vector<string>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Добавляет комментарий в строке раздела исходных данных, начиная с указанной позиции pos
		static void DataPos(const char* comm, int pos) {
			pt4taskmakerX::DataPos(comm, pos);
		}
		/// Добавляет данные и комментарии в строке раздела исходных данных, начиная с указанной позиции pos
		template<typename T>
		static void DataPos(const char* comm, T a, int pos) {
			pt4taskmakerX::DataPos(comm, a ,pos);
		}
		/// Добавляет последовательность данных в строке раздела исходных данных, начиная с указанной позиции pos
		template<typename Container>
		static void DataPos(const Container& seq, int pos) {
			pt4taskmakerX::DataPos(seq, pos);
		}

		/// Добавляет комментарий в новой строке раздела результатов.
		static void ResComm(const char* comm) {
			pt4taskmakerX::ResComm(comm);
		}

		/// Добавляет комментарий в новой строке раздела результатов.
		static void Res(const char* comm) {
			pt4taskmakerX::ResComm(comm);
		}

		/// Добавляет данные и комментарии в новой строке раздела результатов.
		template<typename T>
		static void Res(const char* comm, T a) {
			pt4taskmakerX::Res(comm, a);
		}

		/// Добавляет данные и комментарии в новой строке раздела результатов.
		template<typename T>
		static void Res(const char* comm1, T a1, const char* comm2) {
			pt4taskmakerX::Res(comm1, a1, comm2);
		}

		/// Добавляет данные и комментарии в новой строке раздела результатов.
		template<typename T1, typename T2>
		static void Res(const char* comm1, T1 a1, const char* comm2, T2 a2) {
			pt4taskmakerX::Res(comm1, a1, comm2, a2);
		}

		/// Добавляет данные и комментарии в новой строке раздела результатов.
		template<typename T1, typename T2>
		static void Res(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3) {
			pt4taskmakerX::Res(comm1, a1, comm2, a2, comm3);
		}

		/// Добавляет данные и комментарии в новой строке раздела результатов.
		template<typename T1, typename T2, typename T3>
		static void Res(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3, T3 a3) {
			pt4taskmakerX::Res(comm1, a1, comm2, a2, comm3, a3);
		}

		/// Добавляет последовательность логических данных в раздел результатов.
		static void Res(const std::vector<bool>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Добавляет последовательность целых чисел в раздел результатов.
		static void Res(const std::vector<int>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Добавляет последовательность вещественных чисел в раздел результатов.
		static void Res(const std::vector<double>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Добавляет последовательность символов в раздел результатов.
		static void Res(const std::vector<char>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Добавляет последовательность строк в раздел результатов.
		static void Res(const std::vector<string>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Добавляет комментарий в строке раздела результирующих данных, начиная с указанной позиции pos
		static void ResPos(const char* comm, int pos) {
			pt4taskmakerX::ResPos(comm, pos);
		}
		/// Добавляет данные и комментарии в строке раздела результирующих данных, начиная с указанной позиции pos
		template<typename T>
		static void ResPos(const char* comm, T a, int pos) {
			pt4taskmakerX::ResPos(comm, a ,pos);
		}
		/// Добавляет последовательность данных в строке раздела результирующих данных, начиная с указанной позиции pos
		template<typename Container>
		static void ResPos(const Container& seq, int pos) {
			pt4taskmakerX::ResPos(seq, pos);
		}

		/// Задает минимальную ширину поля вывода для числовых данных
		/// (числа выравниваются по правому краю поля вывода, 
		/// т.е. при необходимости дополняются слева пробелами).
		/// Если n не лежит в диапазоне 0..10, то вызов процедуры игнорируется.
		/// По умолчанию минимальная ширина поля вывода полагается равной 0.
		static void SetWidth(int n) {
			pt4taskmakerX::SetWidth(n);
		}

		/// Задает формат отображения вещественных чисел: 
		/// с фиксированной точкой и n дробными знаками при n > 0,
		/// с плавающей точкой и n дробными знаками при n < 0,
		/// с плавающей точкой и 6 дробными знаками при n = 0.
		/// Если n по модулю превосходит 10, то вызов процедуры игнорируется.
		/// По умолчанию устанавливается формат с фиксированной точкой
		/// и 2 дробными знаками.
		static void SetPrecision(int n) {
			pt4taskmakerX::SetPrecision(n);
		}

		/// Задает количество тестовых запусков, выполняемых
		/// для проверки правильности программы (от 2 до 10). 
		/// По умолчанию число тестовых запусков полагается равным 5.
		static void SetTestCount(int n) {
			pt4taskmakerX::SetTestCount(n);
		}

		/// Задает минимально необходимое количество элементов 
		/// исходных данных, которое требуется ввести для правильного
		/// решения задачи в случае текущего набора исходных данных. 
		/// При отсутствии процедуры предполагается,
		/// что для правильного решения надо ввести все исходные данные.
		static void SetRequiredDataCount(int n) {
			pt4taskmakerX::SetRequiredDataCount(n);
		}

		/// Возвращает номер текущего тестового запуска 
		/// (запуски нумеруются от 1).
		static int CurrentTest() {
			return pt4taskmakerX::CurrentTest();
		}

		/// Генерирует случайное целое число в диапазоне от M до N включительно.
		/// Если M >= N, то возвращает M.
		static int Random(int M, int N) {
			return pt4taskmakerX::Random(M, N);
		}

		/// Возращает случайное значение в диапазоне от 0 (включительно) до 1 (не включительно)
		static double Random() {
			return pt4taskmakerX::Random();
		}

		/// Генерирует случайное вещественное число на промежутке [A, B).
		/// Если промежуток [A, B) пуст, то возвращает A.
		static double Random(double A, double B) {
			return pt4taskmakerX::Random(A, B);
		}

		/// Генерирует случайное вещественное число на промежутке [A, B)
		/// с одним дробным знаком и случайной добавкой порядка 1e-7.
		/// Если промежуток [A, B) пуст, то возвращает A, округленное
		/// до одного дробного знака и снабженное добавкой порядка 1e-7.
		static double Random1(double A, double B) {
			return pt4taskmakerX::Random1(A, B);
		}

		/// Генерирует случайное вещественное число на промежутке [A, B)
		/// с двумя дробными знаками и случайной добавкой порядка 1e-7.
		/// Если промежуток [A, B) пуст, то возвращает A, округленное
		/// до двух дробных знаков и снабженное добавкой порядка 1e-7.
		static double Random2(double A, double B) {
			return pt4taskmakerX::Random2(A, B);
		}

		/// Генерирует случайную строку длины len, состоящую
		/// из цифр и строчных (т.е. маленьких) латинских букв.
		static string RandomName(int len) {
			return pt4taskmakerX::RandomName(len);
		}

		/// Создает новую группу с кратким описанием GroupDescription,
		/// информацией об авторе GroupAuthor, ключом группы GroupKey и набором необязательных опций, объединяемых операцией or.
		/// Имя группы определяется по имени библиотеки (путем отбрасывания префикса PT4
		/// и возможных суффиксов _ru или _en). 
		/// В группу включаются задания, определенные макросом DefineTask.
		/// Процедура NewGroup должна быть вызвана в процедуре inittaskgroup без параметров, которую
		/// необходимо описать в библиотеке с группой заданий (все буквы в имени inittaskgroup - строчные).
		static void NewGroup(const char* GroupDescription, const char* GroupAuthor, const char* GroupKey, int Options = 0) {
			pt4taskmakerX::NewGroup(GroupDescription, GroupAuthor, GroupKey, Options);
		}

		/// Импортирует в создаваемую группу существующее задание
		/// из группы GroupName с номером TaskNumber. Должна вызываться
		/// в процедуре с именем, начинающемся с текста Task.
		static void UseTask(const char* GroupName, int TaskNumber) {
			pt4taskmakerX::UseTask(GroupName, TaskNumber);
		}

		/// Импортирует в создаваемую группу существующее задание
		/// из группы GroupName с номером TaskNumber. Должна вызываться
		/// в процедуре с именем, начинающемся с текста Task.
		static void UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription) {
			pt4taskmakerX::UseTask(GroupName, TaskNumber, TopicDescription);
		}

		/// Позволяет определить текущий язык программирования, выбранный для задачника
		/// Возвращает значения, связанные с константами lgXXX
		static int CurrentLanguage() {
			return pt4taskmakerX::CurrentLanguage();
		}

		/// Возвращает двухбуквенную строку с описанием текущей локали
		/// (в даной версии возвращается либо "ru", либо "en")
		static char* CurrentLocale() {
			return pt4taskmakerX::CurrentLocale();
		}

		/// Возвращает номер текущей версии задачника в формате "d.dd"
		/// (для версий, меньших 4.10, возвращает "4.00")
		static char* CurrentVersion() { // добавлено в версии 4.10
			return pt4taskmakerX::CurrentVersion();
		}

		/// Возвращает массив из 116 русских слов.
		static vector<const char*> GetWords() {
			return pt4taskmakerX::GetWords();
		}
		/// Возвращает массив из 116 английских слов.
		static vector<const char*> GetEnWords() {
			return pt4taskmakerX::GetEnWords();
		}
		/// Возвращает массив из 61 русского предложения.
		static vector<const char*> GetSentences() {
			return pt4taskmakerX::GetSentences();
		}
		/// Возвращает массив из 61 английского предложения.
		static vector<const char*> GetEnSentences() {
			return pt4taskmakerX::GetEnSentences();
		}
		/// Возвращает массив из 85 русских многострочных текстов.
		/// Строки текста разделяются символом \\n.
		/// В конце текста символ \\n отсутствует.
		static vector<const char*> GetTexts() {
			return pt4taskmakerX::GetTexts();
		}
		/// Возвращает массив из 85 английских многострочных текстов.
		/// Строки текста разделяются символом \\n.
		/// В конце текста символ \\n отсутствует.
		static vector<const char*> GetEnTexts() {
			return pt4taskmakerX::GetEnTexts();
		}

		/// Возвращает случайное русское слово из массива, 
		/// входящего в конструктор учебных заданий.
		static const char* RandomWord() {
			return pt4taskmakerX::RandomWord();
		}
		/// Возвращает случайное английское слово из массива, 
		/// входящего в конструктор учебных заданий.
		static const char* RandomEnWord() {
			return pt4taskmakerX::RandomEnWord();
		}
		/// Возвращает случайное русское предложение из массива, 
		/// входящего в конструктор учебных заданий.
		static const char* RandomSentence() {
			return pt4taskmakerX::RandomSentence();
		}
		/// Возвращает случайное английское предложение из массива, 
		/// входящего в конструктор учебных заданий.
		static const char* RandomEnSentence() {
			return pt4taskmakerX::RandomEnSentence();
		}
		/// Возвращает случайный русский многострочный текст из массива, 
		/// входящего в конструктор учебных заданий.
		/// Строки текста разделяются символом \\n.
		/// В конце текста символ \\n отсутствует.
		static const char* RandomText() {
			return pt4taskmakerX::RandomText();
		}
		/// Возвращает случайный английский многострочный текст из массива, 
		/// входящего в конструктор учебных заданий.
		/// Строки текста разделяются символом \\n.
		/// В конце текста символ \\n отсутствует.
		static const char* RandomEnText() {
			return pt4taskmakerX::RandomEnText();
		}

		/// Добавляет в задание исходный файл целых чисел
		/// с именем FileName и отображает его содержимое
		/// в разделе исходных данных.
		static void DataFileInteger(const char* FileName) {
			pt4taskmakerX::DataFileInteger(FileName);
		}
		/// Добавляет в задание исходный файл вещественных чисел
		/// с именем FileName и отображает его содержимое
		/// в разделе исходных данных.
		static void DataFileReal(const char* FileName) {
			pt4taskmakerX::DataFileReal(FileName);
		}
		/// Добавляет в задание исходный символьный файл
		/// с именем FileName и отображает его содержимое
		/// в разделе исходных данных. Символы должны
		/// храниться в файле в однобайтной кодировке.
		static void DataFileChar(const char* FileName) {
			pt4taskmakerX::DataFileChar(FileName);
		}
		/// Добавляет в задание исходный строковый файл
		/// с элементами типа ShortString и именем FileName 
		/// и отображает его содержимое в разделе исходных данных.
		/// Длина элементов файла не должна превосходить 70 символов.
		/// Строки должны храниться в файле в однобайтной кодировке.
		static void DataFileString(const char* FileName) {
			pt4taskmakerX::DataFileString(FileName);
		}
		/// Добавляет в задание исходный текстовый файл
		/// с именем FileName и отображает его содержимое
		/// в разделе исходных данных. Длина каждой строки
		/// текстового файла не должна превосходить 70 символов.
		/// Текст должен храниться в файле в однобайтной кодировке.
		static void DataText(const char* FileName, int LineCount = 5) {
			pt4taskmakerX::DataText(FileName, LineCount);
		}

		/// Добавляет в задание результирующий файл целых чисел
		/// с именем FileName и отображает его содержимое в разделе результатов.
		static void ResFileInteger(const char* FileName) {
			pt4taskmakerX::ResFileInteger(FileName);
		}
		/// Добавляет в задание результирующий файл вещественных чисел
		/// с именем FileName и отображает его содержимое в разделе результатов.
		static void ResFileReal(const char* FileName) {
			pt4taskmakerX::ResFileReal(FileName);
		}
		/// Добавляет в задание результирующий символьный файл
		/// с именем FileName и отображает его содержимое в разделе результатов.
		/// Символы должны храниться в файле в однобайтной кодировке.
		static void ResFileChar(const char* FileName) {
			pt4taskmakerX::ResFileChar(FileName);
		}
		/// Добавляет в задание результирующий строковый файл
		/// с элементами типа ShortString и именем FileName 
		/// и отображает его содержимое в разделе результатов.
		/// Длина элементов файла не должна превосходить 70 символов.
		/// Строки должны храниться в файле в однобайтной кодировке.
		static void ResFileString(const char* FileName) {
			pt4taskmakerX::ResFileString(FileName);
		}
		/// Добавляет в задание результирующий текстовый файл
		/// с именем FileName и отображает его содержимое в разделе результатов. 
		/// Длина каждой строки текстового файла не должна превосходить 70 символов.
		/// Текст должен храниться в файле в однобайтной кодировке.
		static void ResText(const char* FileName, int LineCount = 5) {
			pt4taskmakerX::ResText(FileName, LineCount);
		}
		
		/// Конвертирует обычную строку в короткую (char[256])
		static void ConvertToShortString(string s, ShortString buf) {
			pt4taskmakerX::ConvertToShortString(s, buf);
		}

		/// Процедура, обеспечивающая отображение динамических структур данных
		/// в "объектном стиле" при выполнении заданий в среде PascalABC.NET
		/// (при использовании других сред не выполняет никаких действий)
		static void SetObjectStyle() {
			pt4taskmakerX::SetObjectStyle();
		}

		/// Устанавливает текущий процесс для последующей передачи ему данных 
		/// числовых типов (при выполнении задания в параллельном режиме)
		static void SetProcess(int ProcessRank) {
			pt4taskmakerX::SetProcess(ProcessRank);
		}

		/// Выводит отладочную информацию во всплывающем диалоговом окне
		static void ShowInfo(const char *info) {
			pt4taskmakerX::ShowInfo(info);
		}

		/// Возвращает логические константы в строковом представлении,
		/// соответствующем текущему языку программирования
		static string BoolToString(bool b) {
			return pt4taskmakerX::BoolToString(b);
		}
	};
}

template<typename T>
void DataInternal(const char* s, T a, int x, int y, int w) {
    if ((y > 5) && fd) {
        ErrorInfo(ErrMes2);
        return;
    }
    ++nd;
    if (nd > 200) {
        ErrorInfo(ErrMes3);
        return;
    }
    pt4taskmakerX::Data(s, a, x + dpos, y, w);
}

template<typename T>
void ResInternal(const char* s, T a, int x, int y, int w) {
	if ((y > 5) && fr) {
		ErrorInfo(ErrMes2);
		return;
	}
	++nr;
	if (nr > 200) {
		ErrorInfo(ErrMes4);
		return;
	}
    pt4taskmakerX::Res(s, a, x + rpos, y, w);
}
#endif // _PT4TASKMAKERX
