#ifndef _PT4TASKMAKER

#define _PT4TASKMAKER

#include <windows.h>

// ------------------------------------------------------------------------------
// Constructor for the electronic taskbook Programming Taskbook 4.23
// ------------------------------------------------------------------------------
// Header file of the module for creating dynamic libraries
// with C++ task groups
// 
// Copyright (c) 2013-2023 M.E.Abrahamyan
// Electronic taskbook Programming Taskbook Copyright (c) M.E. Abrahamyan,1998-2023
// ------------------------------------------------------------------------------

using namespace std;

#define xCenter 0
#define xLeft 100
#define xRight 200

#define SampleError "#ERROR?"
#define MaxLineCount 50

#define lgPascal       0x0000001 
#define lgPascalABCNET 0x0000401 
#define lgPascalNET    0x0000400
#define lgPascalABCNET_flag 0x0000400 // добавлено в версии 4.14
#define lgVB           0x0000002
#define lgCPP          0x0000004
#define lg1C           0x0000040
#define lgPython       0x0000080 
#define lgPython3      0x1000080 // добавлено в версии 4.14
#define lgPython3_flag 0x1000000 // добавлено в версии 4.14
#define lgCS           0x0000100
#define lgVBNET        0x0000200
#define lgJava         0x0010000 // добавлено в версии 4.11
#define lgRuby         0x0020000 // добавлено в версии 4.12
#define lgWithPointers 0x000003D
#define lgWithObjects  0x0FFFF80 // изменено в версии 4.22
#define lgNET          0x000FF00
#define lgAll          0x0FFFFFF // изменено в версии 4.10
#define lgFS           0x0000800 // добавлено в версии 4.19
#define lgJulia        0x0040000 // добавлено в версии 4.22
#define lgC            0x0000008 // добавлено в версии 4.23
#define lgR            0x0080000 // добавлено в версии 4.25

/// Dynamic Structure Node
struct TNode
{
	int Data;
	TNode* Next;
	TNode* Prev;
	TNode* Left;
	TNode* Right;
	TNode* Parent;
};

/// Dynamic structure node pointer
typedef TNode* PNode;

/// Procedural type used when creating task groups
typedef void(__stdcall* TInitTaskProc)(int);

namespace pt4taskmaker {
/// Adds a new task group with the specified characteristics to the task book
	void CreateGroup(const char* GroupName, const char* GroupDescription,
		const char* GroupAuthor, const char* GroupKey, int TaskCount,
		TInitTaskProc InitTaskProc);

/// Adds a task from another group to the group being created
	void UseTask(const char* GroupName, int TaskNumber);

/// Adds a task from another group to the group being created
	void UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription); // добавлено в версии 4.19

/// Must be specified first when defining a new task
	void CreateTask(const char* SubgroupName);

/// Must be specified first when defining a new task
	void CreateTask();

/// Must be specified first when defining a new task
/// (option for parallel tasker mode)
	void CreateTask(const char* SubgroupName, int* ProcessCount);

/// Must be specified first when defining a new task
/// (option for parallel tasker mode)
	void CreateTask(int* ProcessCount);

/// Allows you to determine the current programming language selected for the taskbook
/// Returns values associated with lgXXX constants
	int CurrentLanguage();

/// Returns a two-letter string describing the current locale
/// (in this version, either "ru" or "en" is returned)
	char* CurrentLocale();

/// Returns the number of the current version of the problem book in the format "d.dd"
/// (for versions less than 4.10, returns "4.00")
	char* CurrentVersion();  // добавлено в версии 4.10

// -----------------------------------------------------------------------------

/// Adds a line to the statement of the task
	void TaskText(const char* S, int X, int Y);

/// Defines all task wording lines
/// (in parameter S separate lines of wording
/// must be separated by the characters \r, \n or a pair \r\n;
/// the start and end spaces in the lines are removed,
/// empty lines are not included in the wording)
	void TaskText(const char* S); // добавлено в версии 4.11

// -----------------------------------------------------------------------------

/// Adds a logical type element with a comment to the input data
	void DataB(const char* Cmt, bool B, int X, int Y);

/// Adds a Boolean element to the input data
	void DataB(bool B, int X, int Y); // добавлено в версии 4.11

/// Adds an integer element with a comment to the input data
	void DataN(const char* Cmt, int N, int X, int Y, int W);

/// Adds an integer element to the input data
	void DataN(int N, int X, int Y, int W); // добавлено в версии 4.11

/// Adds two integer elements with a general comment to the input data
	void DataN2(const char* Cmt, int N1, int N2, int X, int Y, int W);

/// Adds two integer elements to the input data
	void DataN2(int N1, int N2, int X, int Y, int W); // добавлено в версии 4.11

/// Adds three integer elements with a general comment to the input data
	void DataN3(const char* Cmt, int N1, int  N2, int  N3, int X, int Y, int W);

/// Adds three integer elements to the input data
	void DataN3(int N1, int  N2, int  N3, int X, int Y, int W); // добавлено в версии 4.11

/// Adds a real element with a comment to the source data
	void DataR(const char* Cmt, double R, int  X, int Y, int W);

/// Adds a real element to the input data
	void DataR(double R, int  X, int Y, int W); // добавлено в версии 4.11

/// Adds two real elements with a general comment to the input data
	void DataR2(const char* Cmt, double R1, double R2, int X, int Y, int W);

/// Adds two real elements to the input data
	void DataR2(double R1, double R2, int X, int Y, int W); // добавлено в версии 4.11

/// Adds three real elements with a general comment to the input data
	void DataR3(const char* Cmt, double R1, double R2, double R3, int  X, int Y, int W);

/// Adds three real elements to the input data
	void DataR3(double R1, double R2, double R3, int  X, int Y, int W); // добавлено в версии 4.11

/// Adds a character element with a comment to the source data
	void DataC(const char* Cmt, char C, int  X, int Y);

/// Adds a character element to the source data
	void DataC(char C, int  X, int Y); // добавлено в версии 4.11

/// Adds a string element with a comment to the input data
	void DataS(const char* Cmt, const char* S, int X, int Y);

/// Adds a string element to the input data
	void DataS(const char* S, int X, int Y); // добавлено в версии 4.11

/// Adds a PNode element with a comment to the source data
	void DataP(const char* Cmt, int NP, int X, int Y);

/// Adds a PNode type element to the source data
	void DataP(int NP, int X, int Y); // добавлено в версии 4.11

/// Adds a comment to the source data area
	void  DataComment(const char* Cmt, int  X, int Y);

// -----------------------------------------------------------------------------

/// Adds a logical element with a comment to the resulting data
	void ResultB(const char* Cmt, bool B, int X, int Y);

/// Adds a logical element to the resulting data
	void ResultB(bool B, int X, int Y); // добавлено в версии 4.11

/// Adds an integer element with a comment to the resulting data
	void ResultN(const char* Cmt, int N, int X, int Y, int W);

/// Adds an integer element to the resulting data
	void ResultN(int N, int X, int Y, int W); // добавлено в версии 4.11

/// Adds two integer elements with a common comment to the resulting data
	void ResultN2(const char* Cmt, int N1, int N2, int X, int Y, int W);

/// Adds two integer elements to the resulting data
	void ResultN2(int N1, int N2, int X, int Y, int W); // добавлено в версии 4.11

/// Adds three integer elements with a common comment to the resulting data
	void ResultN3(const char* Cmt, int N1, int N2, int N3, int X, int Y, int W);

/// Adds three integer elements to the resulting data
	void ResultN3(int N1, int N2, int N3, int X, int Y, int W); // добавлено в версии 4.11

/// Adds a real element with a comment to the resulting data
	void ResultR(const char* Cmt, double R, int X, int Y, int W);

/// Adds a real element to the resulting data
	void ResultR(double R, int X, int Y, int W); // добавлено в версии 4.11

/// Adds two real elements with a general comment to the resulting data
	void ResultR2(const char* Cmt, double R1, double R2, int X, int Y, int W);

/// Adds two real elements to the resulting data
	void ResultR2(double R1, double R2, int X, int Y, int W); // добавлено в версии 4.11

/// Adds three real elements with a general comment to the resulting data
	void ResultR3(const char* Cmt, double R1, double R2, double R3, int X, int Y, int W);

/// Adds three real elements to the resulting data
	void ResultR3(double R1, double R2, double R3, int X, int Y, int W); // добавлено в версии 4.11

/// Adds a character element with a comment to the resulting data
	void ResultC(const char* Cmt, char C, int X, int Y);

/// Adds a character element to the resulting data
	void ResultC(char C, int X, int Y); // добавлено в версии 4.11

/// Adds a string element with a comment to the resulting data
	void ResultS(const char* Cmt, const char* S, int X, int Y);

/// Adds a string element to the result data
	void ResultS(const char* S, int X, int Y); // добавлено в версии 4.11

/// Adds a PNode element with a comment to the resulting data
	void ResultP(const char* Cmt, int NP, int X, int Y);

/// Adds a PNode element to the resulting data
	void ResultP(int NP, int X, int Y); // добавлено в версии 4.11

/// Adds a comment to the output data pane
	void ResultComment(const char* Cmt, int X, int Y);

// -----------------------------------------------------------------------------

/// Sets the number of decimal places when displaying real numbers
	void SetPrecision(int N);

/// Sets the number of input data, the minimum required
/// to find the correct result data
	void SetRequiredDataCount(int N);

/// Sets the number of tests (from 2 to 9), if successful
/// the completion of which the task will be considered completed
	void SetTestCount(int N);

/// Returns the horizontal coordinate from which the I-th element should be derived from the set,
/// containing N elements, provided that the width of each element is equal to W, and between the elements
/// it is necessary to specify B spaces (elements are numbered from 1)
	int Center(int I, int  N, int  W, int B);

/// Returns a pseudorandom integer lying
/// in the range of M to N inclusive. If the specified
/// range is empty, then returns M.
	int RandomN(int M, int N); // добавлено в версии 4.11

/// Returns a pseudorandom real number lying
/// at half interval [A, B) .If the specified half interval
/// empty, then returns A.
	double RandomR(double A, double B); // добавлено в версии 4.11

/// Returns the sequence number of the current test run
/// (only successful test runs count.) If previously successful
/// there were no launches, then returns 1. If the task has already been completed
/// or run in demo mode, then returns 0.
/// When using previous versions of the taskbook (up to 4.10 inclusive)
/// Returns TRUE on success. Otherwise, returns FALSE
	int CurrentTest(); // добавлено в версии 4.11

/// Displays debugging information in a pop-up dialog
	void ShowInfo(const char *info); // добавлено в версии 4.23

// -----------------------------------------------------------------------------

/// Adds a binary file with integer elements to the input data
	void DataFileN(const char* FileName, int Y, int W);

/// Adds a binary file with real elements to the source data
	void DataFileR(const char* FileName, int Y, int W);

/// Adds a binary file with character elements to the source data
	void DataFileC(const char* FileName, int Y, int W);

/// Adds a binary file with string elements to the source data
	void DataFileS(const char* FileName, int Y, int W);

/// Adds a text file to the input data
	void DataFileT(const char* FileName, int Y1, int Y2);

// -----------------------------------------------------------------------------

/// Adds a binary file with integer elements to the resulting data
	void ResultFileN(const char* FileName, int Y, int W);

/// Adds a binary file with real elements to the resulting data
	void ResultFileR(const char* FileName, int Y, int W);

/// Adds a binary file with character elements to the resulting data
	void ResultFileC(const char* FileName, int Y, int W);

/// Adds a binary file with string elements to the resulting data
	void ResultFileS(const char* FileName, int Y, int W);

/// Adds a text file to the resulting data
	void ResultFileT(const char* FileName, int Y1, int Y2);

// -----------------------------------------------------------------------------

/// Associates the NP number with the P pointer
	void SetPointer(int NP, PNode P);

/// Adds a linear dynamic structure to the input data
	void DataList(int NP, int X, int Y);

/// Adds a linear dynamic structure to the resulting data
	void ResultList(int NP, int X, int Y);

/// Adds a binary tree to the input data
	void DataBinTree(int NP, int X, int Y1, int Y2);

/// Adds a binary tree to the resulting data
	void ResultBinTree(int NP, int X, int Y1, int Y2);

/// Adds a generic tree to the input data
	void DataTree(int NP, int X, int Y1, int Y2);

/// Adds a generic tree to the resulting data
	void ResultTree(int NP, int X, int Y1, int Y2);

/// Displays a pointer with the number NP in the current dynamic structure
	void ShowPointer(int NP);

/// Marks a pointer in the current resulting dynamic structure that requires creation
	void SetNewNode(int NNode);

/// Marks a pointer in the current source dynamic structure that requires deletion
	void SetDisposedNode(int NNode);

// -----------------------------------------------------------------------------

/// Returns the number of sample words for the language corresponding to the current locale
	int WordCount(); //116

/// Returns the number of sample sentences for the language corresponding to the current locale
	int SentenceCount(); //61

/// Returns the number of sample texts for the language corresponding to the current locale
	int TextCount(); //85

/// Returns a pattern word numbered N (numbered from 0) for the language corresponding to the current locale
	char* WordSample(int N);

/// Returns a sample clause with the number N (numbering from 0) for the language corresponding to the current locale
	char* SentenceSample(int N);

/// Returns sample text numbered N (numbering from 0) for the language corresponding to the current locale,
/// between the lines of text there are symbols \r\n, at the end of the text these symbols are absent,
/// the number of lines does not exceed MaxLineCount, one empty line is placed between paragraphs of text
	char* TextSample(int N);

// -----------------------------------------------------------------------------

/// Returns the number of sample English words
	int EnWordCount(); //116

/// Returns the number of sample English sentences
	int EnSentenceCount(); //61

/// Returns the number of English sample texts
	int EnTextCount(); //85

/// Returns an English sample word with the number N (numbering from 0)
	char* EnWordSample(int N);

/// Returns an English sample sentence with the number N (numbering from 0)
	char* EnSentenceSample(int N);

/// Returns the English sample text with the number N (numbering from 0),
/// between the lines of text there are symbols \r\n, at the end of the text these symbols are absent,
/// the number of lines does not exceed MaxLineCount, one empty line is placed between paragraphs of text
	char* EnTextSample(int N);

// -----------------------------------------------------------------------------

/// Adds a comment line to the current task group or subgroup
	void CommentText(const char* S);

/// Adds a comment from another task group (or its subgroup,
/// if its second parameter is not an empty string)
	void UseComment(const char* GroupName, const char* SubgroupName);

/// Adds a comment from another task group
	void UseComment(const char* GroupName);

/// Sets the mode for adding a comment to a subgroup of tasks
	void Subgroup(const char* SubgroupName);

// -----------------------------------------------------------------------------

/// Procedure for displaying dynamic data structures
/// in an "object style" when performing tasks in a PascalABC.NET environment
/// (does not perform any actions when using other media)
	void SetObjectStyle();

// -----------------------------------------------------------------------------

/// Establishes the current process for subsequent transmission of data to it
/// numeric types (when performing a task in parallel mode)
	void SetProcess(int ProcessRank);
}

// -----------------------------------------------------------------------------

/// Procedure for internal use in the development of assignments
	extern "C" void __stdcall activate(const char* DllName);
	extern "C" void __stdcall inittaskgroup();

// -----------------------------------------------------------------------------

#endif
