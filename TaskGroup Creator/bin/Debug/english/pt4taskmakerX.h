#ifndef _PT4TASKMAKERX
#define _PT4TASKMAKERX

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include "pt4taskmaker.h"

using ShortString = char[256];

/// Macro to add a task to the list of all group tasks
#define DefineTask(name) \
    void name(); \
    struct name ## _Registrar { \
        name ## _Registrar() { RegisterTaskFunction(name, #name); } \
    } name ## _registrar_instance; \
    void name()

/// Macro to obtain the name of the task group
#define DefineGroupName \
    struct _GroupName { \
        _GroupName() { GetGroupName(__FILE__); } \
    } _groupname_instance;

#define alphabet "0123456789abcdefghijklmnoprstuvwxyz"
#define ErrMes1 "Error: –аздел размером более 5 строк не может содержать файловые данные."
#define ErrMes2 "Error: ѕри наличии файловых данных раздел не может содержать более 5 строк."
#define ErrMes3 "Error:  оличество исходных данных превысило 200."
#define ErrMes4 "Error:  оличество результирующих данных превысило 200."
#define ErrMes5 "Error: ѕри определении задани€ первой должна вызыватьс€ процедура NewTask."
#define ErrMes6 "Error: ѕри определении задани€ не указаны исходные данные."
#define ErrMes7 "Error: ѕри определении задани€ не указаны результирующие данные."

// Functions and variables for internal use

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

// *********************************************************M

namespace pt4taskmakerX
{
	const int OptionUseAddition = 8;        // the group is available only if there is an addition file
	const int OptionHideExamples = 16;      // do not display the section with an example of the correct solution

	/// Adding a task (as a pointer to a function) to the list of tasks.For internal use.
	void RegisterTaskFunction(void (*task)(), const char* taskname);

	/// Obtaining the name of the task group from the name of the file.For internal use.
	void GetGroupName(const char* FilePath);

	/// The procedure with which the definition of a new task should begin.
	/// It should be called in the procedure created by the Definetask macros (Procedurename).
	/// The Topic parameter defines the name of the subgroup and is optional.
	/// The Tasktext parameter contains the formulation of the task;Separate lines
	/// The formulations should be separated by a symbol \\n
	void NewTask(const char* topic, const char* tasktext);

	/// The procedure with which the definition of a new task should begin.
	/// It should be called in the procedure created by the Definetask macros (Procedurename).
	/// The Tasktext parameter contains the formulation of the task;Separate lines
	/// The formulations should be separated by a symbol \\n
	void NewTask(const char* tasktext);

	void Data(const char* s, bool a, int x, int y, int w);
	void Data(const char* s, int a, int x, int y, int w);
	void Data(const char* s, double a, int x, int y, int w);
	void Data(const char* s, char a, int x, int y, int w);
	void Data(const char* s, const char* a, int x, int y, int w);

	/// Adds a comment in the new line of the source data section.
	void DataComm(const char* comm);

	/// Adds a comment in the new line of the source data section.
	inline void Data(const char* comm) {
		DataComm(comm);
	}

	/// Adds data and comments in the new line of the source data section.
	template<typename T>
	void Data(const char* comm, T a) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm, a, 0, yd, wd);
		dep = false;
	}

	/// Adds data and comments in the new line of the source data section.
	template<typename T>
	void Data(const char* comm1, T a1, const char* comm2) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm1, a1, xLeft, yd, wd);
		pt4taskmaker::DataComment(comm2, xRight, yd);
		dep = false;
	}

	/// Adds data and comments in the new line of the source data section.
	template<typename T1, typename T2>
	void Data(const char* comm1, T1 a1, const char* comm2, T2 a2) {
		if (CheckTT()) return;
		if (!dep) dpos = 0;
		++yd;
		DataInternal(comm1, a1, xLeft, yd, wd);
		DataInternal(comm2, a2, xRight, yd, wd);
		dep = false;
	}
	/// Adds data and comments in the new line of the source data section.
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
	/// Adds data and comments in the new line of the source data section.
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

	/// Adds the sequence of logical data to the source data section.
	void Data(const std::vector<bool>& seq);

	/// Adds a sequence of integers to the initial data section.
	void Data(const std::vector<int>& seq);

	/// Adds a sequence of material numbers to the initial data section.
	void Data(const std::vector<double>& seq);

	/// Adds a sequence of characters to the initial data section.
	void Data(const std::vector<char>& seq);

	/// Adds a sequence of lines to the source data section.
	void Data(const std::vector<string>& seq);

	/// Adds a comment in the line of the source data section, starting with the specified POS position
	inline void DataPos(const char* comm, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((dpos < pos) && (yd > 0)) {
				--yd; // остаемс€ на текущей строке
			}
			dpos = pos;
		}
		else {
			ErrorInfo("Error: ѕозици€ исходных данных должна быть больше 0 и меньше 79");
			return;
		}
		dep = true;
		Data(comm);
	}
	/// Adds data and comments in the line of the source data section, starting with the specified POS position
	template<typename T>
	void DataPos(const char* comm, T a, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((dpos < pos) && (yd > 0)) {
				--yd; // остаемс€ на текущей строке
			}
			dpos = pos;
		}
		else {
			ErrorInfo("Error: ѕозици€ исходных данных должна быть больше 0 и меньше 79");
			return;
		}
		dep = true;
		Data(comm, a);
	}
	/// Adds the data sequence to the line of the source data section, starting with the specified POS position
	template<typename Container>
	void DataPos(const Container& seq, int pos) {
		if (CheckTT())
		return;
		int n = seq.size();
		if (n == 0) return;

		if (pos > 0 && pos < 79) {
			if ((dpos < pos) && (yd > 0)) {
				--yd; // остаемс€ на текущей строке
			}
			dpos = pos;
		}
		else {
			ErrorInfo("Error: ѕозици€ исходных данных должна быть больше 0 и меньше 79");
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

	/// Adds a comment in the new line of the results section.
	void ResComm(const char* comm);
	/// Adds a comment in the new line of the results section.
	inline void Res(const char* comm) {
		ResComm(comm);
	}

	/// Adds data and comments in the new line of the results section.
	template<typename T>
	void Res(const char* comm, T a) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm, a, 0, yr, wd);
		rep = false;
	}

	/// Adds data and comments in the new line of the results section.
	template<typename T>
	void Res(const char* comm1, T a1, const char* comm2) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm1, a1, xLeft, yr, wd);
		pt4taskmaker::ResultComment(comm2, xRight, yr);
		rep = false;
	}

	/// Adds data and comments in the new line of the results section.
	template<typename T1, typename T2>
	void Res(const char* comm1, T1 a1, const char* comm2, T2 a2) {
		if (CheckTT()) return;
		if (!rep) rpos = 0;
		++yr;
		ResInternal(comm1, a1, xLeft, yr, wd);
		ResInternal(comm2, a2, xRight, yr, wd);
		rep = false;
	}

	/// Adds data and comments in the new line of the results section.
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

	/// Adds data and comments in the new line of the results section.
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

	/// Adds the sequence of logical data to the results section.
	void Res(const std::vector<bool>& seq);

	/// Adds a sequence of integers to the results section.
	void Res(const std::vector<int>& seq);

	/// Adds a sequence of material numbers to the results section.
	void Res(const std::vector<double>& seq);

	/// Adds a sequence of characters to the results section.
	void Res(const std::vector<char>& seq);

	/// Adds a sequence of lines to the results section.
	void Res(const std::vector<string>& seq);

	/// Adds a comment in the line of the resulting data section, starting with the specified POS position
	inline void ResPos(const char* comm, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((rpos < pos) && (yr > 0)) {
				--yr; // остаемс€ на текущей строке
			}
			rpos = pos;
		}
		else {
			ErrorInfo("Error: ѕозици€ результирующих данных должна быть больше 0 и меньше 79");
			return;
		}
		rep = true;
		Res(comm);
	}
	/// Adds data and comments in the line of the resulting data section, starting with the specified POS position
	template<typename T>
	void ResPos(const char* comm, T a, int pos) {
		if (CheckTT())
		return;
		if (pos > 0 && pos < 79) {
			if ((rpos < pos) && (yr > 0)) {
				--yr; // остаемс€ на текущей строке
			}
			rpos = pos;
		}
		else {
			ErrorInfo("Error: ѕозици€ результирующих данных должна быть больше 0 и меньше 79");
			return;
		}
		rep = true;
		Res(comm, a);
	}
	/// Adds a data sequence to the line of the resulting data section, starting with the specified POS position
	template<typename Container>
	void ResPos(const Container& seq, int pos) {
		if (CheckTT())
		return;
		int n = seq.size();
		if (n == 0) return;

		if (pos > 0 && pos < 79) {
			if ((rpos < pos) && (yr > 0)) {
				--yr; // остаемс€ на текущей строке
			}
			rpos = pos;
		}
		else {
			ErrorInfo("Error: ѕозици€ результирующих данных должна быть больше 0 и меньше 79");
			return;
		}
		rep = true;
		Res((vector<typename Container::value_type>)seq);
	}

	/// Sets the minimum width of the output field for numerical data
	/// (numbers are aligned on the right edge of the output field,
	/// those.If necessary, they are supplemented on the left by spaces).
	/// If N does not lie in the range of 0..10, then the call call is ignored.
	/// By default, the minimum width of the output field is supposed to be equal to 0.
	void SetWidth(int n);

	/// Sets the format for displaying material numbers:
	/// with a fixed point and n fractional signs at n> 0,
	/// with a floating point and n fractional signs at n <0,
	/// with a floating point and 6 fractional signs at n = 0.
	/// If N exceeds 10 by the module, then the call call is ignored.
	/// By default, a format with a fixed point is installed
	/// and 2 fractional signs.
	void SetPrecision(int n);

	/// Sets the number of test launches performed
	/// To check the correctness of the program (from 2 to 10).
	/// By default, the number of test launches is supposed to be 5.
	void SetTestCount(int n);

	/// Sets the minimum required number of elements
	/// initial data that is required to enter for the correct
	/// Solving the problem in the case of the current set of source data.
	/// In the absence of the procedure, it is assumed
	/// that for the correct solution it is necessary to enter all the initial data.
	void SetRequiredDataCount(int n);

	/// Returns the number of current test launch
	/// (launches are numbered from 1).
	int CurrentTest();

	/// Displays debug information in a pop -up dialog box
	void ShowInfo(const char *info);

	/// It generates a random integer in the range from M to N inclusive.
	/// If M> = N, then returns M.
	int Random(int M, int N);

	/// Returns random value in the range from 0 (inclusive) to 1 (not inclusive)
	double Random(); 

	/// Generates an accidental material number on the interval [a, b).
	/// If the interval [a, b) is empty, then it returns A.
	double Random(double A, double B);

	/// Generates an accidental material number on the interval [a, b)
	/// With one fractional sign and random additive of about 1E-7.
	/// If the interval [a, b) is empty, then it returns a, rounded
	/// up to one fractional sign and equipped with an addition of about 1E-7.
	double Random1(double A, double B);

	/// Generates an accidental material number on the interval [a, b)
	/// With two fractional signs and a random additive of about 1E-7.
	/// If the interval [a, b) is empty, then it returns a, rounded
	/// up to two fractional signs and equipped with an addition of about 1E-7.
	double Random2(double A, double B);

	/// Generates a random line of Len length, consisting
	/// Of the numbers and lowercase (i.e., small) Latin letters.
	string RandomName(int len);

	/// Creates a new group with a brief description of Groupdescription,
	/// Information about the author of GroupAuthor, the key of the Groupkey group and a set of optional options united by OR operation.
	/// The name of the group is determined by the name of the library (by discarding the prefix PT4
	/// and possible suffixes _ru or _en).
	/// The group includes tasks determined by the Definetsk macros.
	/// The NEWGROUP procedure should be caused in the InittaskGroup procedure without parameters that
	/// It is necessary to describe in the library with a group of tasks (all letters in the name Inittaskgroup - lowercase).
	void NewGroup(const char* GroupDescription, const char* GroupAuthor, const char* GroupKey, int Options = 0);

	/// Imports the existing task into the created group
	/// From the GroupName group with Tasknumber number.Should be called
	/// In the procedure with a name starting with the TASK text.
	void UseTask(const char* GroupName, int TaskNumber);

	/// Imports the existing task into the created group
	/// From the GroupName group with Tasknumber number.Should be called
	/// In the procedure with a name starting with the TASK text.
	void UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription);

	/// Allows you to determine the current programming language selected for the task
	/// Returns values related to LGXXX constants
	int CurrentLanguage();

	/// Returns a two -letter line with a description of the current location
	/// (In the Danam version, either "ru" or "en") returns
	char* CurrentLocale();

	/// Returns the number of the current version of the task book in "D.DD" format
	/// (for versions less than 4.10, returns "4.00")
	char* CurrentVersion();  // добавлено в версии 4.10

	/// Returns an array of 116 Russian words.
	vector<const char*> GetWords();
	/// Returns an array of 116 English words.
	vector<const char*> GetEnWords();
	/// Returns an array of 61 Russian offers.
	vector<const char*> GetSentences();
	/// Returns an array of 61 English sentences.
	vector<const char*> GetEnSentences();
	/// Returns an array of 85 Russian multi -line texts.
	/// The lines of the text are separated by the \\n symbol.
	/// At the end of the text, the \\n symbol is absent.
	vector<const char*> GetTexts();
	/// Returns an array of 85 English multi -line texts.
	/// The lines of the text are separated by the \\n symbol.
	/// At the end of the text, the \\n symbol is absent.
	vector<const char*> GetEnTexts();

	/// Returns a random Russian word from an array,
	/// included in the designer of training tasks.
	const char* RandomWord();
	/// Returns a random English word from an array,
	/// included in the designer of training tasks.
	const char* RandomEnWord();
	/// Returns a random Russian proposal from the array,
	/// included in the designer of training tasks.
	const char* RandomSentence();
	/// Returns a random English proposal from an array,
	/// included in the designer of training tasks.
	const char* RandomEnSentence();
	/// Returns a random Russian multi -line text from an array,
	/// included in the designer of training tasks.
	/// The lines of the text are separated by the \\n symbol.
	/// At the end of the text, the \\n symbol is absent.
	const char* RandomText();
	/// Returns a random English multi -line text from an array,
	/// included in the designer of training tasks.
	/// The lines of the text are separated by the \\n symbol.
	/// At the end of the text, the \\n symbol is absent.
	const char* RandomEnText();

	/// Adds to the assignment the source file of integers
	/// with the name Filename and displays its contents
	/// In the section of the source data.
	void DataFileInteger(const char* FileName);
	/// Adds to the task the source file of material numbers
	/// with the name Filename and displays its contents
	/// In the section of the source data.
	void DataFileReal(const char* FileName);
	/// Adds the source symbolic file to the task
	/// with the name Filename and displays its contents
	/// In the section of the source data.Symbols must
	/// Store in a file in a single -byte encoding.
	void DataFileChar(const char* FileName);
	/// Adds the source string file to the task
	/// with elements like Shortstring and name Filename
	/// and displays its contents in the source data section.
	/// The length of the file elements should not exceed 70 characters.
	/// Lines should be stored in a file in single -byte coding.
	void DataFileString(const char* FileName);
	/// Adds the source text file to the task
	/// with the name Filename and displays its contents
	/// In the section of the source data.The length of each line
	/// A text file should not exceed 70 characters.
	/// The text should be stored in a file in a single -byte coding.
	void DataText(const char* FileName, int LineCount = 5);

	/// Adds to the task the resulting file of integers
	/// With the name Filename and displays its contents in the results section.
	void ResFileInteger(const char* FileName);
	/// Adds to the task the resulting file of material numbers
	/// With the name Filename and displays its contents in the results section.
	void ResFileReal(const char* FileName);
	/// Adds to the task the resulting symbolic file
	/// With the name Filename and displays its contents in the results section.
	/// Symbols should be stored in a file in single -byte coding.
	void ResFileChar(const char* FileName);
	/// Adds to the task the resulting string file
	/// with elements like Shortstring and name Filename
	/// And displays its contents in the results section.
	/// The length of the file elements should not exceed 70 characters.
	/// Lines should be stored in a file in single -byte coding.
	void ResFileString(const char* FileName);
	/// Adds to the task the resulting text file
	/// With the name Filename and displays its contents in the results section.
	/// The length of each line of the text file should not exceed 70 characters.
	/// The text should be stored in a file in a single -byte coding.
	void ResText(const char* FileName, int LineCount = 5);

	/// Converts the usual line into short (Char [256])
	void ConvertToShortString(string s, ShortString buf);

	/// The procedure that ensures the display of dynamic data structures
	/// In the "Object style" when completing tasks in Pascalabc.net
	/// (when using other environments, it does not perform any action)
	void SetObjectStyle();

	/// Sets the current process for the subsequent transmission of data to it
	/// numerical types (when completing a task in a parallel mode)
	void SetProcess(int ProcessRank);

	/// Returns logical constants in a string performance,
	/// corresponding to the current programming language
	string BoolToString(bool b);

	class pt {
	public:
		/// Additional option for the NEWGROP:
		/// The group is available only if there is a related add -on file.
		static int OptionUseAddition() {
			return pt4taskmakerX::OptionUseAddition;
		}
		/// Additional option for the NEWGROP:
		/// In the tasks of this group, an example of the right solution will not be displayed.
		static int OptionHideExamples() {
			return pt4taskmakerX::OptionHideExamples;
		}

		/// The procedure with which the definition of a new task should begin.
		/// It should be called in the procedure created by the Definetask macros (Procedurename).
		/// The Topic parameter defines the name of the subgroup and is optional.
		/// The Tasktext parameter contains the formulation of the task;Separate lines
		/// The formulations should be separated by a symbol \\n
		static void NewTask(const char* topic, const char* tasktext) {
			pt4taskmakerX::NewTask(topic, tasktext);
		}

		/// The procedure with which the definition of a new task should begin.
		/// It should be called in the procedure created by the Definetask macros (Procedurename).
		/// The Tasktext parameter contains the formulation of the task;Separate lines
		/// The formulations should be separated by a symbol \\n
		static void NewTask(const char* tasktext) {
			pt4taskmakerX::NewTask(tasktext);
		}

		/// Adds a comment in the new line of the source data section.
		static void DataComm(const char* comm) {
			pt4taskmakerX::DataComm(comm);
		}

		/// Adds a comment in the new line of the source data section.
		static void Data(const char* comm) {
			pt4taskmakerX::DataComm(comm);
		}

		/// Adds data and comments in the new line of the source data section.
		template<typename T>
		static void Data(const char* comm, T a) {
			pt4taskmakerX::Data(comm, a);
		}

		/// Adds data and comments in the new line of the source data section.
		template<typename T>
		static void Data(const char* comm1, T a1, const char* comm2) {
			pt4taskmakerX::Data(comm1, a1, comm2);
		}

		/// Adds data and comments in the new line of the source data section.
		template<typename T1, typename T2>
		static void Data(const char* comm1, T1 a1, const char* comm2, T2 a2) {
			pt4taskmakerX::Data(comm1, a1, comm2, a2);
		}

		/// Adds data and comments in the new line of the source data section.
		template<typename T1, typename T2>
		static void Data(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3) {
			pt4taskmakerX::Data(comm1, a1, comm2, a2, comm3);
		}

		/// Adds data and comments in the new line of the source data section.
		template<typename T1, typename T2, typename T3>
		static void Data(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3, T3 a3) {
			pt4taskmakerX::Data(comm1, a1, comm2, a2, comm3, a3);
		}

		/// Adds the sequence of logical data to the source data section.
		static void Data(const std::vector<bool>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Adds a sequence of integers to the initial data section.
		static void Data(const std::vector<int>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Adds a sequence of material numbers to the initial data section.
		static void Data(const std::vector<double>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Adds a sequence of characters to the initial data section.
		static void Data(const std::vector<char>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Adds a sequence of lines to the source data section.
		static void Data(const std::vector<string>& seq) {
			pt4taskmakerX::Data(seq);
		}

		/// Adds a comment in the line of the source data section, starting with the specified POS position
		static void DataPos(const char* comm, int pos) {
			pt4taskmakerX::DataPos(comm, pos);
		}
		/// Adds data and comments in the line of the source data section, starting with the specified POS position
		template<typename T>
		static void DataPos(const char* comm, T a, int pos) {
			pt4taskmakerX::DataPos(comm, a ,pos);
		}
		/// Adds the data sequence to the line of the source data section, starting with the specified POS position
		template<typename Container>
		static void DataPos(const Container& seq, int pos) {
			pt4taskmakerX::DataPos(seq, pos);
		}

		/// Adds a comment in the new line of the results section.
		static void ResComm(const char* comm) {
			pt4taskmakerX::ResComm(comm);
		}

		/// Adds a comment in the new line of the results section.
		static void Res(const char* comm) {
			pt4taskmakerX::ResComm(comm);
		}

		/// Adds data and comments in the new line of the results section.
		template<typename T>
		static void Res(const char* comm, T a) {
			pt4taskmakerX::Res(comm, a);
		}

		/// Adds data and comments in the new line of the results section.
		template<typename T>
		static void Res(const char* comm1, T a1, const char* comm2) {
			pt4taskmakerX::Res(comm1, a1, comm2);
		}

		/// Adds data and comments in the new line of the results section.
		template<typename T1, typename T2>
		static void Res(const char* comm1, T1 a1, const char* comm2, T2 a2) {
			pt4taskmakerX::Res(comm1, a1, comm2, a2);
		}

		/// Adds data and comments in the new line of the results section.
		template<typename T1, typename T2>
		static void Res(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3) {
			pt4taskmakerX::Res(comm1, a1, comm2, a2, comm3);
		}

		/// Adds data and comments in the new line of the results section.
		template<typename T1, typename T2, typename T3>
		static void Res(const char* comm1, T1 a1, const char* comm2, T2 a2, const char* comm3, T3 a3) {
			pt4taskmakerX::Res(comm1, a1, comm2, a2, comm3, a3);
		}

		/// Adds the sequence of logical data to the results section.
		static void Res(const std::vector<bool>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Adds a sequence of integers to the results section.
		static void Res(const std::vector<int>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Adds a sequence of material numbers to the results section.
		static void Res(const std::vector<double>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Adds a sequence of characters to the results section.
		static void Res(const std::vector<char>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Adds a sequence of lines to the results section.
		static void Res(const std::vector<string>& seq) {
			pt4taskmakerX::Res(seq);
		}

		/// Adds a comment in the line of the resulting data section, starting with the specified POS position
		static void ResPos(const char* comm, int pos) {
			pt4taskmakerX::ResPos(comm, pos);
		}
		/// Adds data and comments in the line of the resulting data section, starting with the specified POS position
		template<typename T>
		static void ResPos(const char* comm, T a, int pos) {
			pt4taskmakerX::ResPos(comm, a ,pos);
		}
		/// Adds a data sequence to the line of the resulting data section, starting with the specified POS position
		template<typename Container>
		static void ResPos(const Container& seq, int pos) {
			pt4taskmakerX::ResPos(seq, pos);
		}

		/// Sets the minimum width of the output field for numerical data
		/// (numbers are aligned on the right edge of the output field,
		/// those.If necessary, they are supplemented on the left by spaces).
		/// If N does not lie in the range of 0..10, then the call call is ignored.
		/// By default, the minimum width of the output field is supposed to be equal to 0.
		static void SetWidth(int n) {
			pt4taskmakerX::SetWidth(n);
		}

		/// Sets the format for displaying material numbers:
		/// with a fixed point and n fractional signs at n> 0,
		/// with a floating point and n fractional signs at n <0,
		/// with a floating point and 6 fractional signs at n = 0.
		/// If N exceeds 10 by the module, then the call call is ignored.
		/// By default, a format with a fixed point is installed
		/// and 2 fractional signs.
		static void SetPrecision(int n) {
			pt4taskmakerX::SetPrecision(n);
		}

		/// Sets the number of test launches performed
		/// To check the correctness of the program (from 2 to 10).
		/// By default, the number of test launches is supposed to be 5.
		static void SetTestCount(int n) {
			pt4taskmakerX::SetTestCount(n);
		}

		/// Sets the minimum required number of elements
		/// initial data that is required to enter for the correct
		/// Solving the problem in the case of the current set of source data.
		/// In the absence of the procedure, it is assumed
		/// that for the correct solution it is necessary to enter all the initial data.
		static void SetRequiredDataCount(int n) {
			pt4taskmakerX::SetRequiredDataCount(n);
		}

		/// Returns the number of current test launch
		/// (launches are numbered from 1).
		static int CurrentTest() {
			return pt4taskmakerX::CurrentTest();
		}

		/// It generates a random integer in the range from M to N inclusive.
		/// If M> = N, then returns M.
		static int Random(int M, int N) {
			return pt4taskmakerX::Random(M, N);
		}

		/// Returns random value in the range from 0 (inclusive) to 1 (not inclusive)
		static double Random() {
			return pt4taskmakerX::Random();
		}

		/// Generates an accidental material number on the interval [a, b).
		/// If the interval [a, b) is empty, then it returns A.
		static double Random(double A, double B) {
			return pt4taskmakerX::Random(A, B);
		}

		/// Generates an accidental material number on the interval [a, b)
		/// With one fractional sign and random additive of about 1E-7.
		/// If the interval [a, b) is empty, then it returns a, rounded
		/// up to one fractional sign and equipped with an addition of about 1E-7.
		static double Random1(double A, double B) {
			return pt4taskmakerX::Random1(A, B);
		}

		/// Generates an accidental material number on the interval [a, b)
		/// With two fractional signs and a random additive of about 1E-7.
		/// If the interval [a, b) is empty, then it returns a, rounded
		/// up to two fractional signs and equipped with an addition of about 1E-7.
		static double Random2(double A, double B) {
			return pt4taskmakerX::Random2(A, B);
		}

		/// Generates a random line of Len length, consisting
		/// Of the numbers and lowercase (i.e., small) Latin letters.
		static string RandomName(int len) {
			return pt4taskmakerX::RandomName(len);
		}

		/// Creates a new group with a brief description of Groupdescription,
		/// Information about the author of GroupAuthor, the key of the Groupkey group and a set of optional options united by OR operation.
		/// The name of the group is determined by the name of the library (by discarding the prefix PT4
		/// and possible suffixes _ru or _en).
		/// The group includes tasks determined by the Definetsk macros.
		/// The NEWGROUP procedure should be caused in the InittaskGroup procedure without parameters that
		/// It is necessary to describe in the library with a group of tasks (all letters in the name Inittaskgroup - lowercase).
		static void NewGroup(const char* GroupDescription, const char* GroupAuthor, const char* GroupKey, int Options = 0) {
			pt4taskmakerX::NewGroup(GroupDescription, GroupAuthor, GroupKey, Options);
		}

		/// Imports the existing task into the created group
		/// From the GroupName group with Tasknumber number.Should be called
		/// In the procedure with a name starting with the TASK text.
		static void UseTask(const char* GroupName, int TaskNumber) {
			pt4taskmakerX::UseTask(GroupName, TaskNumber);
		}

		/// Imports the existing task into the created group
		/// From the GroupName group with Tasknumber number.Should be called
		/// In the procedure with a name starting with the TASK text.
		static void UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription) {
			pt4taskmakerX::UseTask(GroupName, TaskNumber, TopicDescription);
		}

		/// Allows you to determine the current programming language selected for the task
		/// Returns values related to LGXXX constants
		static int CurrentLanguage() {
			return pt4taskmakerX::CurrentLanguage();
		}

		/// Returns a two -letter line with a description of the current location
		/// (In the Danam version, either "ru" or "en") returns
		static char* CurrentLocale() {
			return pt4taskmakerX::CurrentLocale();
		}

		/// Returns the number of the current version of the task book in "D.DD" format
		/// (for versions less than 4.10, returns "4.00")
		static char* CurrentVersion() { // добавлено в версии 4.10
			return pt4taskmakerX::CurrentVersion();
		}

		/// Returns an array of 116 Russian words.
		static vector<const char*> GetWords() {
			return pt4taskmakerX::GetWords();
		}
		/// Returns an array of 116 English words.
		static vector<const char*> GetEnWords() {
			return pt4taskmakerX::GetEnWords();
		}
		/// Returns an array of 61 Russian offers.
		static vector<const char*> GetSentences() {
			return pt4taskmakerX::GetSentences();
		}
		/// Returns an array of 61 English sentences.
		static vector<const char*> GetEnSentences() {
			return pt4taskmakerX::GetEnSentences();
		}
		/// Returns an array of 85 Russian multi -line texts.
		/// The lines of the text are separated by the \\n symbol.
		/// At the end of the text, the \\n symbol is absent.
		static vector<const char*> GetTexts() {
			return pt4taskmakerX::GetTexts();
		}
		/// Returns an array of 85 English multi -line texts.
		/// The lines of the text are separated by the \\n symbol.
		/// At the end of the text, the \\n symbol is absent.
		static vector<const char*> GetEnTexts() {
			return pt4taskmakerX::GetEnTexts();
		}

		/// Returns a random Russian word from an array,
		/// included in the designer of training tasks.
		static const char* RandomWord() {
			return pt4taskmakerX::RandomWord();
		}
		/// Returns a random English word from an array,
		/// included in the designer of training tasks.
		static const char* RandomEnWord() {
			return pt4taskmakerX::RandomEnWord();
		}
		/// Returns a random Russian proposal from the array,
		/// included in the designer of training tasks.
		static const char* RandomSentence() {
			return pt4taskmakerX::RandomSentence();
		}
		/// Returns a random English proposal from an array,
		/// included in the designer of training tasks.
		static const char* RandomEnSentence() {
			return pt4taskmakerX::RandomEnSentence();
		}
		/// Returns a random Russian multi -line text from an array,
		/// included in the designer of training tasks.
		/// The lines of the text are separated by the \\n symbol.
		/// At the end of the text, the \\n symbol is absent.
		static const char* RandomText() {
			return pt4taskmakerX::RandomText();
		}
		/// Returns a random English multi -line text from an array,
		/// included in the designer of training tasks.
		/// The lines of the text are separated by the \\n symbol.
		/// At the end of the text, the \\n symbol is absent.
		static const char* RandomEnText() {
			return pt4taskmakerX::RandomEnText();
		}

		/// Adds to the assignment the source file of integers
		/// with the name Filename and displays its contents
		/// In the section of the source data.
		static void DataFileInteger(const char* FileName) {
			pt4taskmakerX::DataFileInteger(FileName);
		}
		/// Adds to the task the source file of material numbers
		/// with the name Filename and displays its contents
		/// In the section of the source data.
		static void DataFileReal(const char* FileName) {
			pt4taskmakerX::DataFileReal(FileName);
		}
		/// Adds the source symbolic file to the task
		/// with the name Filename and displays its contents
		/// In the section of the source data.Symbols must
		/// Store in a file in a single -byte encoding.
		static void DataFileChar(const char* FileName) {
			pt4taskmakerX::DataFileChar(FileName);
		}
		/// Adds the source string file to the task
		/// with elements like Shortstring and name Filename
		/// and displays its contents in the source data section.
		/// The length of the file elements should not exceed 70 characters.
		/// Lines should be stored in a file in single -byte coding.
		static void DataFileString(const char* FileName) {
			pt4taskmakerX::DataFileString(FileName);
		}
		/// Adds the source text file to the task
		/// with the name Filename and displays its contents
		/// In the section of the source data.The length of each line
		/// A text file should not exceed 70 characters.
		/// The text should be stored in a file in a single -byte coding.
		static void DataText(const char* FileName, int LineCount = 5) {
			pt4taskmakerX::DataText(FileName, LineCount);
		}

		/// Adds to the task the resulting file of integers
		/// With the name Filename and displays its contents in the results section.
		static void ResFileInteger(const char* FileName) {
			pt4taskmakerX::ResFileInteger(FileName);
		}
		/// Adds to the task the resulting file of material numbers
		/// With the name Filename and displays its contents in the results section.
		static void ResFileReal(const char* FileName) {
			pt4taskmakerX::ResFileReal(FileName);
		}
		/// Adds to the task the resulting symbolic file
		/// With the name Filename and displays its contents in the results section.
		/// Symbols should be stored in a file in single -byte coding.
		static void ResFileChar(const char* FileName) {
			pt4taskmakerX::ResFileChar(FileName);
		}
		/// Adds to the task the resulting string file
		/// with elements like Shortstring and name Filename
		/// And displays its contents in the results section.
		/// The length of the file elements should not exceed 70 characters.
		/// Lines should be stored in a file in single -byte coding.
		static void ResFileString(const char* FileName) {
			pt4taskmakerX::ResFileString(FileName);
		}
		/// Adds to the task the resulting text file
		/// With the name Filename and displays its contents in the results section.
		/// The length of each line of the text file should not exceed 70 characters.
		/// The text should be stored in a file in a single -byte coding.
		static void ResText(const char* FileName, int LineCount = 5) {
			pt4taskmakerX::ResText(FileName, LineCount);
		}

		/// Converts the usual line into short (Char [256])
		static void ConvertToShortString(string s, ShortString buf) {
			pt4taskmakerX::ConvertToShortString(s, buf);
		}

		/// The procedure that ensures the display of dynamic data structures
		/// In the "Object style" when completing tasks in Pascalabc.net
		/// (when using other environments, it does not perform any action)
		static void SetObjectStyle() {
			pt4taskmakerX::SetObjectStyle();
		}

		/// Sets the current process for the subsequent transmission of data to it
		/// numerical types (when completing a task in a parallel mode)
		static void SetProcess(int ProcessRank) {
			pt4taskmakerX::SetProcess(ProcessRank);
		}

		/// Displays debug information in a pop -up dialog box
		static void ShowInfo(const char *info) {
			pt4taskmakerX::ShowInfo(info);
		}

		/// Returns logical constants in a string performance,
		/// corresponding to the current programming language
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
