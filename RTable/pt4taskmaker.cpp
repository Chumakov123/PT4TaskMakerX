#include <ctime>
#include <string>
#include "pt4taskmaker.h"

//------------------------------------------------------------------------------
//  онструктор дл€ электронного задачника Programming Taskbook 4.23
//------------------------------------------------------------------------------
// ћодуль дл€ создани€ динамических-библиотек с группами заданий на €зыке C++
//
// Copyright (c) 2013-2023 ћ.Ё.јбрам€н
// Ёлектронный задачник Programming Taskbook Copyright (c) ћ.Ё.јбрам€н,1998-2023
//------------------------------------------------------------------------------


typedef  int    (__stdcall *TNFunc)(void);
typedef  int    (__stdcall *TNFuncN4)(int, int, int, int);
typedef         char*   (__stdcall *TSFunc)(void);
typedef         char* (__stdcall *TSFuncN)(int);
typedef         void    (__stdcall *TProc)(void);
typedef         void    (__stdcall *TProcS)(const char *);  
typedef         void    (__stdcall *TProcSCN2)(const char *, char, int, int);  
typedef         void    (__stdcall *TProcSN)(const char *, int);  
typedef         void    (__stdcall *TProcSN2)(const char *, int, int);    
typedef         void    (__stdcall *TProcSN3)(const char *, int, int, int);    
typedef         void    (__stdcall *TProcSN4)(const char *, int, int, int, int);    
typedef         void    (__stdcall *TProcSN5)(const char *, int, int, int, int, int);      
typedef         void    (__stdcall *TProcSN6)(const char *, int, int, int, int, int, int);        
typedef         void    (__stdcall *TProcSRN3)(const char *, double, int, int, int);    
typedef         void    (__stdcall *TProcSR2N3)(const char *, double, double, int, int, int);    
typedef         void    (__stdcall *TProcSR3N3)(const char *, double, double, double, int, int, int);    
typedef         void    (__stdcall *TProcS2)(const char *, const char *);    
typedef         void    (__stdcall *TProcS2N2)(const char *, const char *, int, int);      
typedef         void    (__stdcall *TProcS4NP)(const char *, const char *, const char *, const char *, int, void *);      
typedef         void    (__stdcall *TProcN)(int);      
typedef         void    (__stdcall *TProcNP)(int, void *);      
typedef         void    (__stdcall *TProcN2)(int, int);        
typedef         void    (__stdcall *TProcN3)(int, int, int);        
typedef         void    (__stdcall *TProcN4)(int, int, int, int);        
typedef         void    (__stdcall *TProcSvN)(const char *, int *);        
typedef         void    (__stdcall *TProcSNS)(const char *, int, const char *);        
typedef         int     (__stdcall *TMsgBox)(int, const char *, const char *, int);        

class  PT4TaskMakerLink {

protected :
                TProcS4NP       creategroup_;
                TProcSN         usetask_;
                TProcS          createtask_;
                TNFunc          currentlanguage_;
                TSFunc          currentlocale_;
                TProcSN2        tasktext_;
                TProcSN3        datab_, resultb_;
                TProcSN4        datan_, resultn_;
                TProcSN5        datan2_, resultn2_;
                TProcSN6        datan3_, resultn3_;
                TProcSRN3       datar_, resultr_;
                TProcSR2N3      datar2_, resultr2_;
                TProcSR3N3      datar3_, resultr3_;
                TProcSCN2       datac_, resultc_;
                TProcS2N2       datas_, results_;
                TProcSN3        datap_, resultp_;
                TProcSN2        datacomment_, resultcomment_;
                TProcN          setprecision_, settestcount_, setrequireddatacount_;
                TNFuncN4        center_;
                TProcSN2        datafilen_, datafiler_, datafilec_, datafiles_, datafilet_;
                TProcSN2        resultfilen_, resultfiler_, resultfilec_, resultfiles_, resultfilet_;
                TProcNP         setpointer_;
                TProcN3         datalist_, resultlist_;
                TProcN4         databintree_, datatree_, resultbintree_, resulttree_;
                TProcN          showpointer_, setnewnode_, setdisposednode_;
                TNFunc          wordcount_, sentencecount_, textcount_;
                TNFunc          enwordcount_, ensentencecount_, entextcount_;
                TSFuncN         wordsample_, sentencesample_, textsample_;
                TSFuncN         enwordsample_, ensentencesample_, entextsample_;
                TProcS          commenttext_;
                TProcS2         usecomment_ ;
                TProcS          subgroup_;
                TProc           setobjectstyle_;
                TProcSvN        createtask2_;
                TProcN          setprocess_;
                TSFunc          currentversion_; // добавлено в версии 4.10
                TNFunc          currenttest_; // добавлено в версии 4.11
                TProcSNS        usetaskex_; // добавлено в версии 4.19
                TMsgBox         msgbox_;
                HMODULE         FHandle, User32Handle ;

private:
        PT4TaskMakerLink(PT4TaskMakerLink&);
        PT4TaskMakerLink & operator=(PT4TaskMakerLink&);
        void ShowError(const char* S1, const char* S2) ;
        
public: 
        PT4TaskMakerLink() {};
        virtual ~PT4TaskMakerLink() { FreeLibrary (FHandle); FreeLibrary (User32Handle); } ;

        inline void CreateGroup(const char*             GroupName, 
                                        const char*             GroupDescription, 
                                        const char*             GroupAuthor,
                                        const char*             GroupKey,
                                        int     TaskCount,
                                        TInitTaskProc   InitTaskProc);

        inline void UseTask(const char* GroupName, int TaskNumber);
        inline void CreateTask(const char* SubgroupName, int*);
        inline void CreateTask(const char* SubgroupName);
        inline void CreateTask(int *);
        inline int CurrentLanguage();
        inline char* CurrentLocale();
        inline char* CurrentVersion();  // добавлено в версии 4.10
        inline void TaskText(const char* S, int X , int Y);
        inline void DataB(const char*  Cmt, bool B, int X, int Y);
        inline void DataN(const char* Cmt, int N, int X, int Y, int W);
        inline void DataN(const char* Cmt, int  N1, int N2, int  X, int  Y, int  W);
        inline void DataN(const char* Cmt, int N1, int  N2, int  N3, int X, int Y, int W);
        inline void DataR(const char* Cmt, double R, int  X, int Y, int W);
        inline void DataR(const char* Cmt, double R1, double R2, int X, int Y, int W);
        inline void DataR(const char* Cmt, double R1, double R2, double R3, int  X, int Y, int W);
        inline void DataC(const char* Cmt,  char C, int  X, int Y);
        inline void DataS(const char* Cmt, const char* S,  int X,  int Y);
        inline void DataP(const char* Cmt, int NP,  int X,  int Y);
        inline void DataComment(const char* Cmt, int  X, int Y);
        inline void ResultB(const char* Cmt, bool  B, int X, int Y);
        inline void ResultN(const char* Cmt, int  N, int X, int Y, int  W);
        inline void ResultN(const char* Cmt, int N1, int N2, int X, int Y, int W);
        inline void ResultN(const char* Cmt, int N1, int N2, int N3, int X, int Y, int W);
        inline void ResultR(const char* Cmt, double R, int X, int Y, int W);
        inline void ResultR(const char* Cmt, double R1, double R2, int X, int Y, int W);
        inline void ResultR(const char* Cmt, double R1, double  R2, double R3, int X, int Y,  int W);
        inline void ResultC(const char* Cmt,  char C, int X, int Y);
        inline void ResultS(const char* Cmt, const char* S, int X, int Y);
        inline void ResultP(const char* Cmt, int NP, int X, int Y);
        inline void ResultComment(const char* Cmt, int X, int Y);
        inline void SetPrecision(int N);
        inline void SetRequiredDataCount(int N);
        inline void SetTestCount(int N);
        inline int  Center(int I, int  N, int  W, int B);
        inline void DataFileN(const char* FileName, int Y, int W);
        inline void DataFileR(const char* FileName, int Y, int W);
        inline void DataFileC(const char* FileName, int Y, int W);
        inline void DataFileS(const char* FileName, int Y, int W);
        inline void DataFileT(const char* FileName, int Y1, int Y2);
        inline void ResultFileN(const char* FileName,  int Y, int W);
        inline void ResultFileR(const char* FileName, int Y, int W);
        inline void ResultFileC(const char* FileName,  int Y, int W);
        inline void ResultFileS(const char* FileName, int Y, int W);
        inline void ResultFileT(const char* FileName, int Y1, int Y2);
        inline void SetPointer(int NP, PNode P);
        inline void DataList(int NP, int X, int Y);
        inline void ResultList(int NP, int X, int Y);
        inline void DataBinTree(int NP, int X, int Y1, int Y2);
        inline void ResultBinTree(int NP, int X, int Y1, int Y2);
        inline void DataTree(int NP,  int X, int Y1, int Y2);
        inline void ResultTree(int NP, int X, int Y1, int Y2);
        inline void ShowPointer( int NP);
        inline void SetNewNode(int NNode);
        inline void SetDisposedNode(int NNode);
        inline int WordCount();     //116
        inline int SentenceCount(); //61
        inline int TextCount();     //85
        inline char* WordSample(int N);
        inline char* SentenceSample(int N);
        inline char* TextSample(int N);
        inline int EnWordCount();     //116
        inline int EnSentenceCount(); //61
        inline int EnTextCount();     //85
        inline char* EnWordSample(int N);
        inline char* EnSentenceSample( int N);
        inline char* EnTextSample(int N);
        inline void CommentText(const char* S);
        inline void UseComment(const char* GroupName,const char* SubgroupName);
        inline void UseComment(const char* GroupName);
        inline void Subgroup(const char* SubgroupName);
        inline void SetObjectStyle();
        inline void activate(const char * DllName);
        inline void SetProcess(int ProcessRank);
        inline int CurrentTest(); // добавлено в версии 4.11
        inline void UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription); // добавлено в версии 4.19
        inline void ShowInfo(const char* info); // добавлено в версии 4.23
};


PT4TaskMakerLink PTLink;


void PT4TaskMakerLink::activate(const char* DllName) {
                
                User32Handle = LoadLibraryA("User32.dll");
                msgbox_ = (TMsgBox) GetProcAddress(User32Handle, "MessageBoxA");
                FHandle = LoadLibraryA(DllName);
                creategroup_ = (TProcS4NP) GetProcAddress(FHandle, "creategroup");
                usetask_ = (TProcSN) GetProcAddress(FHandle, "usetask");
                createtask_ = (TProcS)GetProcAddress(FHandle, "createtask");
                currentlanguage_ =(TNFunc)  GetProcAddress(FHandle, "currentlanguage");
                currentlocale_ = (TSFunc) GetProcAddress(FHandle, "currentlocale");
                tasktext_ =  (TProcSN2) GetProcAddress(FHandle, "tasktext");
                datab_ =(TProcSN3) GetProcAddress(FHandle, "datab");
                datan_ = (TProcSN4) GetProcAddress(FHandle, "datan");
                datan2_ =(TProcSN5) GetProcAddress(FHandle, "datan2");
                datan3_ = (TProcSN6) GetProcAddress(FHandle, "datan3");
                datar_ =(TProcSRN3) GetProcAddress(FHandle, "datar");
                datar2_ = (TProcSR2N3)GetProcAddress(FHandle, "datar2");
                datar3_ = (TProcSR3N3)GetProcAddress(FHandle, "datar3");
                datac_ =(TProcSCN2) GetProcAddress(FHandle, "datac");
                datas_ = (TProcS2N2) GetProcAddress(FHandle, "datas");
                datap_ = (TProcSN3)GetProcAddress(FHandle, "datap");
                datacomment_ = (TProcSN2)GetProcAddress(FHandle, "datacomment");
                resultb_ = (TProcSN3)GetProcAddress(FHandle, "resultb");
                resultn_ =(TProcSN4) GetProcAddress(FHandle, "resultn");
                resultn2_ =(TProcSN5) GetProcAddress(FHandle, "resultn2");
                resultn3_ = (TProcSN6)GetProcAddress(FHandle, "resultn3");
                resultr_ = (TProcSRN3) GetProcAddress(FHandle, "resultr");
                resultr2_ =(TProcSR2N3) GetProcAddress(FHandle, "resultr2");
                resultr3_ = (TProcSR3N3)GetProcAddress(FHandle, "resultr3");
                resultc_ = (TProcSCN2)  GetProcAddress(FHandle, "resultc");
                results_ = (TProcS2N2)  GetProcAddress(FHandle, "results");
                resultp_ = (TProcSN3) GetProcAddress(FHandle, "resultp");
                resultcomment_ = (TProcSN2) GetProcAddress(FHandle, "resultcomment");
                setprecision_ = (TProcN) GetProcAddress(FHandle, "setprecision");
                settestcount_ = (TProcN) GetProcAddress(FHandle, "settestcount");
                setrequireddatacount_ = (TProcN) GetProcAddress(FHandle, "setrequireddatacount");
                center_ = (TNFuncN4) GetProcAddress(FHandle, "center");
                datafilen_ = (TProcSN2) GetProcAddress(FHandle, "datafilen");
                datafiler_ = (TProcSN2) GetProcAddress(FHandle, "datafiler");
                datafilec_ =(TProcSN2) GetProcAddress(FHandle, "datafilec");
                datafiles_ =(TProcSN2) GetProcAddress(FHandle, "datafiles");
                datafilet_ = (TProcSN2)GetProcAddress(FHandle, "datafilet");
                resultfilen_ = (TProcSN2)GetProcAddress(FHandle, "resultfilen");
                resultfiler_ = (TProcSN2)GetProcAddress(FHandle, "resultfiler");
                resultfilec_ = (TProcSN2)GetProcAddress(FHandle, "resultfilec");
                resultfiles_ =(TProcSN2) GetProcAddress(FHandle, "resultfiles");
                resultfilet_ = (TProcSN2)GetProcAddress(FHandle, "resultfilet");
                setpointer_ =(TProcNP) GetProcAddress(FHandle, "setpointer");
                datalist_ =(TProcN3) GetProcAddress(FHandle, "datalist");
                resultlist_ = (TProcN3)GetProcAddress(FHandle, "resultlist");
                databintree_ =(TProcN4) GetProcAddress(FHandle, "databintree");
                datatree_ = (TProcN4) GetProcAddress(FHandle, "datatree");
                resultbintree_ = (TProcN4)GetProcAddress(FHandle, "resultbintree");
                resulttree_ =(TProcN4) GetProcAddress(FHandle, "resulttree");
                showpointer_ =(TProcN) GetProcAddress(FHandle, "showpointer");
                setnewnode_ =(TProcN) GetProcAddress(FHandle, "setnewnode");
                setdisposednode_ = (TProcN)GetProcAddress(FHandle, "setdisposednode");
                wordcount_ =(TNFunc) GetProcAddress(FHandle, "wordcount");
                sentencecount_ =(TNFunc) GetProcAddress(FHandle, "sentencecount");
                textcount_ = (TNFunc)GetProcAddress(FHandle, "textcount");
                wordsample_ =(TSFuncN) GetProcAddress(FHandle, "wordsample");
                sentencesample_ = (TSFuncN)GetProcAddress(FHandle, "sentencesample");
                textsample_ = (TSFuncN)GetProcAddress(FHandle, "textsample");
                enwordcount_ = (TNFunc)GetProcAddress(FHandle, "enwordcount");
                ensentencecount_ = (TNFunc)GetProcAddress(FHandle, "ensentencecount");
                entextcount_ = (TNFunc)GetProcAddress(FHandle, "entextcount");
                enwordsample_ = (TSFuncN) GetProcAddress(FHandle, "enwordsample");
                ensentencesample_ = (TSFuncN)GetProcAddress(FHandle, "ensentencesample");
                entextsample_ =(TSFuncN) GetProcAddress(FHandle, "entextsample");
                commenttext_ =(TProcS) GetProcAddress(FHandle, "commenttext");
                usecomment_ = (TProcS2)GetProcAddress(FHandle, "usecomment");
                subgroup_ = (TProcS) GetProcAddress(FHandle, "subgroup");
                setobjectstyle_ = (TProc) GetProcAddress(FHandle, "setobjectstyle");
                createtask2_ = (TProcSvN) GetProcAddress(FHandle, "createtask2");
                setprocess_ = (TProcN) GetProcAddress(FHandle, "setprocess");
                currentversion_ = (TSFunc) GetProcAddress(FHandle, "currentversion"); // добавлено в версии 4.10
                currenttest_ = (TNFunc) GetProcAddress(FHandle, "curt"); // добавлено в версии 4.11
                usetaskex_ = (TProcSNS) GetProcAddress(FHandle, "usetaskex"); // добавлено в версии 4.19
}

inline void PT4TaskMakerLink::CreateGroup(      const char*             GroupName, 
                                                                        const char*             GroupDescription, 
                                                                        const char*             GroupAuthor,
                                                                        const char*             GroupKey,
                                                                        int     TaskCount,
                                                                        TInitTaskProc   InitTaskProc)
{
        creategroup_(GroupName , GroupDescription , GroupAuthor ,GroupKey , TaskCount, reinterpret_cast<void*>(InitTaskProc));
        srand((unsigned int)time(0)*10000); 
}

inline void PT4TaskMakerLink::UseTask(const char* GroupName, int TaskNumber)
{
  usetask_(GroupName, TaskNumber);
}

inline void PT4TaskMakerLink::UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription)
{
  if (usetaskex_)
    usetaskex_(GroupName, TaskNumber, TopicDescription);
  else
    usetask_(GroupName, TaskNumber);
}

inline void PT4TaskMakerLink::CreateTask(const char* SubgroupName)
{
  createtask_(SubgroupName );
}

inline int PT4TaskMakerLink::CurrentLanguage()
{
        return currentlanguage_();
}

inline char* PT4TaskMakerLink::CurrentLocale()
{
        
  return currentlocale_();
}

inline void PT4TaskMakerLink::TaskText(const char* S, int X, int Y)
{
  tasktext_(S , X, Y);
}


inline void PT4TaskMakerLink::DataB(const char*  Cmt, bool B, int X, int Y)
{
  datab_(Cmt , (int)B, X, Y);
}

inline void PT4TaskMakerLink::DataN(const char* Cmt, int N, int X, int Y, int W)
{
  datan_(Cmt , N, X, Y, W);
}

inline  void PT4TaskMakerLink::DataN(const char* Cmt, int  N1, int N2, int  X, int  Y, int  W)
{
  datan2_(Cmt , N1, N2,  X, Y, W);
}

inline void PT4TaskMakerLink::DataN(const char* Cmt, int N1, int  N2, int  N3, int X, int Y, int W)
{
  datan3_(Cmt , N1, N2, N3, X, Y, W);
}

inline void PT4TaskMakerLink::DataR(const char* Cmt, double R, int  X, int Y, int W)
{
  datar_(Cmt , R, X, Y, W);
}

inline void PT4TaskMakerLink::DataR(const char* Cmt, double R1, double R2, int X, int Y, int W)
{
  datar2_(Cmt , R1, R2, X, Y, W);
}

inline void PT4TaskMakerLink::DataR(const char* Cmt, double R1, double R2, double R3, int  X, int Y, int W)
{
  datar3_(Cmt , R1, R2, R3, X, Y, W);
}

inline void PT4TaskMakerLink::DataC(const char* Cmt,  char C, int  X, int Y)
{
  datac_(Cmt , C, X, Y);
}

inline void PT4TaskMakerLink::DataS(const char* Cmt, const char* S,  int X,  int Y)
{
  datas_(Cmt , S , X, Y);
}

inline void PT4TaskMakerLink::DataP(const char* Cmt, int NP,  int X,  int Y)
{
  datap_ (Cmt , NP, X, Y);
}

inline void PT4TaskMakerLink::DataComment(const char* Cmt, int  X, int Y)
{
  datacomment_(Cmt , X, Y);
}

inline void PT4TaskMakerLink::ResultB(const char* Cmt, bool  B, int X, int Y)
{       
  resultb_(Cmt , B, X, Y);
}

inline void PT4TaskMakerLink::ResultN(const char* Cmt, int  N, int X, int Y, int  W)
{
  resultn_(Cmt , N, X, Y, W);
}

inline void PT4TaskMakerLink::ResultN(const char* Cmt, int N1, int N2, int X, int Y, int W)
{
  resultn2_(Cmt , N1, N2, X, Y, W);
}

inline void PT4TaskMakerLink::ResultN(const char* Cmt, int N1, int N2, int N3, int X, int Y, int W)
{
  resultn3_(Cmt , N1, N2, N3, X, Y, W);
}

inline void PT4TaskMakerLink::ResultR(const char* Cmt, double R, int X, int Y, int W)
{
  resultr_(Cmt , R, X, Y, W);
}

inline void PT4TaskMakerLink::ResultR(const char* Cmt, double R1, double R2, int X, int Y, int W)
{
  resultr2_(Cmt , R1, R2, X, Y, W);
}

inline void PT4TaskMakerLink::ResultR(const char* Cmt, double R1, double  R2, double R3, int X, int Y,  int W)
{
  resultr3_(Cmt , R1, R2, R3, X, Y, W);
}

inline void PT4TaskMakerLink::ResultC(const char* Cmt,  char C, int X, int Y)
{
  resultc_(Cmt , C, X, Y);
}

inline void PT4TaskMakerLink::ResultS(const char* Cmt, const char* S, int X, int Y)
{
        results_(Cmt , S , X, Y);
}

inline void PT4TaskMakerLink::ResultP(const char* Cmt, int NP, int X, int Y)
{
  resultp_(Cmt , NP, X, Y);
}


inline void PT4TaskMakerLink::ResultComment(const char* Cmt, int X, int Y)
{
  resultcomment_(Cmt , X, Y);
}

inline void PT4TaskMakerLink::SetPrecision(int N)
{
  setprecision_(N);
}

inline void PT4TaskMakerLink::SetTestCount(int N)
{
  settestcount_(N);
}

inline void PT4TaskMakerLink::SetRequiredDataCount(int N)
{
  setrequireddatacount_(N);
}

inline int PT4TaskMakerLink::Center(int I, int  N, int  W, int B)
{
  return center_(I, N, W, B);
}

inline void PT4TaskMakerLink::DataFileN(const char* FileName, int Y, int W)
{
  datafilen_(FileName , Y, W);
}

inline void PT4TaskMakerLink::DataFileR(const char* FileName, int Y, int W)
{
  datafiler_(FileName , Y, W);
}

inline void PT4TaskMakerLink::DataFileC(const char* FileName, int Y, int W)
{
  datafilec_(FileName , Y, W);
}

inline void PT4TaskMakerLink::DataFileS(const char* FileName, int Y, int W)
{
  datafiles_(FileName , Y, W);
}

inline void PT4TaskMakerLink::DataFileT(const char* FileName, int Y1, int Y2)
{
  datafilet_(FileName , Y1, Y2);
}

inline void PT4TaskMakerLink::ResultFileN(const char* FileName,  int Y, int W)
{
  resultfilen_(FileName , Y, W);
}

inline void PT4TaskMakerLink::ResultFileR(const char* FileName, int Y, int W)
{
  resultfiler_(FileName , Y, W);
}

inline void PT4TaskMakerLink::ResultFileC(const char* FileName,  int Y, int W)
{
  resultfilec_(FileName , Y, W);
}

inline void PT4TaskMakerLink::ResultFileS(const char* FileName, int Y, int W)
{
  resultfiles_(FileName , Y, W);
}

inline void PT4TaskMakerLink::ResultFileT(const char* FileName, int Y1, int Y2)
{
  resultfilet_(FileName , Y1, Y2);
}

inline void PT4TaskMakerLink::SetPointer(int NP, PNode P)
{
  setpointer_(NP, P);
}

inline void PT4TaskMakerLink::DataList(int NP, int X, int Y)
{
  datalist_(NP, X, Y);
}

inline void PT4TaskMakerLink::ResultList(int NP, int  X, int Y)
{
  resultlist_(NP, X, Y);
}

inline void PT4TaskMakerLink::DataBinTree(int NP, int X, int Y1, int Y2)
{
  databintree_(NP, X, Y1, Y2);
}

inline void PT4TaskMakerLink::ResultBinTree(int NP, int X, int Y1, int  Y2)
{
  resultbintree_(NP, X, Y1, Y2);
}

inline void PT4TaskMakerLink::DataTree(int NP, int X, int Y1, int Y2)
{
  datatree_(NP, X, Y1, Y2);
}

inline void PT4TaskMakerLink::ResultTree(int NP,int X,int  Y1,int  Y2)
{
  resulttree_(NP, X, Y1, Y2);
}

inline void PT4TaskMakerLink::ShowPointer(int NP)
{
  showpointer_(NP);
}

inline void PT4TaskMakerLink::SetNewNode(int NNode)
{
  setnewnode_(NNode);
}

inline void PT4TaskMakerLink::SetDisposedNode(int NNode)
{
  setdisposednode_(NNode);
}

inline int PT4TaskMakerLink::WordCount()
{
  return wordcount_();
}

inline int PT4TaskMakerLink::SentenceCount()
{
  return sentencecount_();
}

inline int PT4TaskMakerLink::TextCount()
{
  return textcount_();
}

inline char* PT4TaskMakerLink::WordSample(int n)
{
  return wordsample_(n);
}


inline char* PT4TaskMakerLink::SentenceSample(int n)
{
  return sentencesample_(n);
}

inline char* PT4TaskMakerLink::TextSample(int n)
{
  return textsample_(n);
}

inline int PT4TaskMakerLink::EnWordCount()
{
  return enwordcount_();
}

inline int PT4TaskMakerLink::EnSentenceCount()
{
  return ensentencecount_();
}

inline int  PT4TaskMakerLink::EnTextCount()
{
  return entextcount_();
}

inline char* PT4TaskMakerLink::EnWordSample(int n)
{
  return enwordsample_(n);
}

inline char* PT4TaskMakerLink::EnSentenceSample(int n)
{
  return ensentencesample_(n);
}

inline char* PT4TaskMakerLink::EnTextSample(int n)
{
  return entextsample_(n);
}

inline void PT4TaskMakerLink::CommentText(const char* S)
{
        commenttext_(S);
}

inline void PT4TaskMakerLink::UseComment(const char* GroupName, const char* SubgroupName)
{
        usecomment_(GroupName, SubgroupName);
}

inline void  PT4TaskMakerLink::UseComment(const char* GroupName)
{
        usecomment_(GroupName , "");
}

inline void  PT4TaskMakerLink::Subgroup(const char* SubgroupName)
{
        subgroup_(SubgroupName);
}

inline void  PT4TaskMakerLink::SetObjectStyle()
{
  setobjectstyle_();
}

inline void PT4TaskMakerLink::ShowError(const char* S1, const char* S2)
{
  string tmpstring(S1);
  tmpstring +="\n is not found in the PT4 library.\nYou should update the Programming Taskbook to ";
  tmpstring += S2;
  tmpstring += " version.";
  msgbox_(0, tmpstring.c_str(), "PT4TaskMaker Error", MB_ICONERROR);
}

inline void PT4TaskMakerLink::ShowInfo(const char* info)
{
  msgbox_(0, info, "PT4TaskMaker Info", MB_ICONINFORMATION);
}

inline void PT4TaskMakerLink::CreateTask(const char* SubgroupName, int* ProcessCount)
{
  if (createtask2_) 
           createtask2_(SubgroupName, ProcessCount);
  else
    ShowError("The CreateTask procedure with ProcessCount parameter", "4.9");
}

inline void PT4TaskMakerLink::CreateTask(int* ProcessCount)
{
        CreateTask("", ProcessCount);
}

inline void PT4TaskMakerLink::SetProcess(int ProcessRank)
{
  if (setprocess_) setprocess_(ProcessRank);
}

inline char* PT4TaskMakerLink::CurrentVersion()
{
  if (currentversion_)
    return currentversion_();
  else
    return const_cast < char*>("4.00");
}

inline int PT4TaskMakerLink::CurrentTest()
{
  if (currenttest_)
    return currenttest_();
  else 
    return 0;
}

void pt4taskmaker::CreateGroup(const char* GroupName, const char* GroupDescription,
  const char* GroupAuthor, const char* GroupKey,
  int TaskCount, TInitTaskProc InitTaskProc)
{
        PTLink.CreateGroup(GroupName,GroupDescription, GroupAuthor, GroupKey, TaskCount, InitTaskProc);
}

void pt4taskmaker::UseTask(const char* GroupName, int TaskNumber)
{
        PTLink.UseTask(GroupName,TaskNumber);
}

void pt4taskmaker::UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription)
{
        PTLink.UseTask(GroupName,TaskNumber,TopicDescription);
}

void pt4taskmaker::CreateTask(const char* SubgroupName)
{
        PTLink.CreateTask(SubgroupName);
}

void pt4taskmaker::CreateTask()
{
        PTLink.CreateTask("");
}

void pt4taskmaker::CreateTask(const char* SubgroupName, int* ProcessCount)
{
        PTLink.CreateTask(SubgroupName, ProcessCount);
}

void pt4taskmaker::CreateTask(int* ProcessCount)
{
        PTLink.CreateTask(ProcessCount);
}

int pt4taskmaker::CurrentLanguage()
{
        return PTLink.CurrentLanguage();
}

char* pt4taskmaker::CurrentLocale(){
        return PTLink.CurrentLocale();
}

char* pt4taskmaker::CurrentVersion()
{
        return PTLink.CurrentVersion();
}

int pt4taskmaker::CurrentTest()
{
        return PTLink.CurrentTest();
}

void pt4taskmaker::TaskText(const char* S, int X , int Y)
{
        PTLink.TaskText(S,X,Y);
}

void pt4taskmaker::TaskText(const char* S)
{
        string S1 = S;
        int p1[205], p2[205];
        int n = -1;
        size_t i = 0;
        size_t l = S1.length();
        while (i < l)
        {
                if (S1[i] != 10 && S1[i] != 13 && (i == 0 || S1[i-1] == 10 || S1[i-1] == 13)
                        && n < 204)
                {
                        while (i < l && S1[i] == ' ')
                                i++;
                        if (i < l && S1[i] != 13 && S1[i] != 10)
                                p1[++n] = i;
                }
                if (i == l)
                        break;
                if (S1[i] != 13 && S1[i] != 10 && (i == l - 1 || S1[i+1] == 13 || S1[i+1] == 10))
                {
                        int k = i;
                        if (S1[k] == ' ')
                        {
                                while (S1[k] == ' ')
                                        k--;
                                if (S1[k] == '\\' && (k == 0 || S1[k-1] != '\\'))
                                        k++;
                        }
                        p2[n] = k - p1[n] + 1;
                        if (n == 204)
                                break;
                }
                i++;
    }
        if (n == -1)
                return;
        switch (n)
        {
        case 0:
                PTLink.TaskText(S1.substr(p1[0], p2[0]).c_str(), 0, 3); break;
        case 1:
                for (int i = 0; i <= n; i++)
                        PTLink.TaskText(S1.substr(p1[i], p2[i]).c_str(), 0, 2*(i+1));
                break;
    case 2: case 3:
        for (int i = 0; i <= n; i++)
            PTLink.TaskText(S1.substr(p1[i], p2[i]).c_str(), 0, i+2);
        break;
    default:
        for (int i = 0; i <= 4; i++)
            PTLink.TaskText(S1.substr(p1[i], p2[i]).c_str(), 0, i+1);
        for (int i = 5; i <= n; i++)
            PTLink.TaskText(S1.substr(p1[i], p2[i]).c_str(), 0, 0);
        break;
    }
}

void pt4taskmaker::DataB(const char* Cmt, bool B, int X, int Y)
{
        PTLink.DataB(Cmt,B,X,Y);
}

void pt4taskmaker::DataB(bool B, int X, int Y)
{
        PTLink.DataB("",B,X,Y);
}

void pt4taskmaker::DataN(const char* Cmt, int N, int X, int Y, int W)
{
        PTLink.DataN(Cmt,N,X,Y,W);
}

void pt4taskmaker::DataN(int N, int X, int Y, int W)
{
        PTLink.DataN("",N,X,Y,W);
}

void pt4taskmaker::DataN2(const char* Cmt, int  N1, int N2, int  X, int  Y, int  W)
{
        PTLink.DataN(Cmt,N1,N2,X,Y,W);
}

void pt4taskmaker::DataN2(int  N1, int N2, int  X, int  Y, int  W)
{
        PTLink.DataN("",N1,N2,X,Y,W);
}

void pt4taskmaker::DataN3(const char* Cmt, int N1, int  N2, int  N3, int X, int Y, int W)
{
        PTLink.DataN(Cmt,N1,N2,N3,X,Y,W);
}

void pt4taskmaker::DataN3(int N1, int  N2, int  N3, int X, int Y, int W)
{
        PTLink.DataN("",N1,N2,N3,X,Y,W);
}

void pt4taskmaker::DataR(const char* Cmt, double R, int  X, int Y, int W)
{
        PTLink.DataR(Cmt,R,X,Y,W);
}

void pt4taskmaker::DataR(double R, int  X, int Y, int W)
{
        PTLink.DataR("",R,X,Y,W);
}

void pt4taskmaker::DataR2(const char* Cmt, double R1, double R2, int X, int Y, int W)
{
        PTLink.DataR(Cmt,R1,R2,X,Y,W);
}

void pt4taskmaker::DataR2(double R1, double R2, int X, int Y, int W)
{
        PTLink.DataR("",R1,R2,X,Y,W);
}

void pt4taskmaker::DataR3(const char* Cmt, double R1, double R2, double R3, int  X, int Y, int W)
{
        PTLink.DataR(Cmt,R1,R2,R3,X,Y,W);
}

void pt4taskmaker::DataR3(double R1, double R2, double R3, int  X, int Y, int W)
{
        PTLink.DataR("",R1,R2,R3,X,Y,W);
}

void pt4taskmaker::DataC(const char* Cmt,  char C, int  X, int Y)
{
        PTLink.DataC(Cmt,C,X,Y);
}

void pt4taskmaker::DataC(char C, int  X, int Y)
{
        PTLink.DataC("",C,X,Y);
}

void pt4taskmaker::DataS(const char* Cmt, const char* S,  int X,  int Y)
{
        PTLink.DataS(Cmt,S,X,Y);
}

void pt4taskmaker::DataS(const char* S,  int X,  int Y)
{
        PTLink.DataS("",S,X,Y);
}

void pt4taskmaker::DataP(const char* Cmt, int NP,  int X,  int Y)
{
        PTLink.DataP(Cmt,NP,X,Y);
}

void pt4taskmaker::DataP(int NP,  int X,  int Y)
{
        PTLink.DataP("",NP,X,Y);
}

void pt4taskmaker::DataComment(const char* Cmt, int  X, int Y)
{
        PTLink.DataComment(Cmt,X,Y);
}

void pt4taskmaker::ResultB(const char* Cmt, bool  B, int X, int Y)
{
        PTLink.ResultB(Cmt,B,X,Y);
}

void pt4taskmaker::ResultB(bool B, int X, int Y)
{
        PTLink.ResultB("",B,X,Y);
}

void pt4taskmaker::ResultN(const char* Cmt, int  N, int X, int Y, int  W)
{
        PTLink.ResultN(Cmt,N,X,Y,W);
}

void pt4taskmaker::ResultN(int N, int X, int Y, int  W)
{
        PTLink.ResultN("",N,X,Y,W);
}

void pt4taskmaker::ResultN2(const char* Cmt, int N1, int N2, int X, int Y, int W)
{
        PTLink.ResultN(Cmt,N1,N2,X,Y,W);
}

void pt4taskmaker::ResultN2(int N1, int N2, int X, int Y, int W)
{
        PTLink.ResultN("",N1,N2,X,Y,W);
}

void pt4taskmaker::ResultN3(const char* Cmt, int N1, int N2, int N3, int X, int Y, int W)
{
        PTLink.ResultN(Cmt,N1,N2,N3,X,Y,W);
}

void pt4taskmaker::ResultN3(int N1, int N2, int N3, int X, int Y, int W)
{
        PTLink.ResultN("",N1,N2,N3,X,Y,W);
}

void pt4taskmaker::ResultR(const char* Cmt, double R, int X, int Y, int W)
{
        PTLink.ResultR(Cmt,R,X,Y,W);
}

void pt4taskmaker::ResultR(double R, int X, int Y, int W)
{
        PTLink.ResultR("",R,X,Y,W);
}

void pt4taskmaker::ResultR2(const char* Cmt, double R1, double R2, int X, int Y, int W)
{
        PTLink.ResultR(Cmt,R1,R2,X,Y,W);
}

void pt4taskmaker::ResultR2(double R1, double R2, int X, int Y, int W)
{
        PTLink.ResultR("",R1,R2,X,Y,W);
}

void pt4taskmaker::ResultR3(const char* Cmt, double R1, double  R2, double R3, int X, int Y,  int W)
{
        PTLink.ResultR(Cmt,R1,R2,R3,X,Y,W);
}

void pt4taskmaker::ResultR3(double R1, double  R2, double R3, int X, int Y,  int W)
{
        PTLink.ResultR("",R1,R2,R3,X,Y,W);
}

void pt4taskmaker::ResultC(const char* Cmt,  char C, int X, int Y)
{
        PTLink.ResultC(Cmt,C,X,Y);
}

void pt4taskmaker::ResultC(char C, int X, int Y)
{
        PTLink.ResultC("",C,X,Y);
}

void pt4taskmaker::ResultS(const char* Cmt, const char* S, int X, int Y)
{
        PTLink.ResultS(Cmt, S, X,Y);
}

void pt4taskmaker::ResultS(const char* S, int X, int Y)
{
        PTLink.ResultS("", S, X,Y);
}

void pt4taskmaker::ResultP(const char* Cmt, int NP, int X, int Y)
{
        PTLink.ResultP(Cmt,NP,X,Y);
}

void pt4taskmaker::ResultP(int NP, int X, int Y)
{
        PTLink.ResultP("",NP,X,Y);
}

void pt4taskmaker::ResultComment(const char* Cmt, int X, int Y)
{
        PTLink.ResultComment(Cmt,X,Y);
}

void pt4taskmaker::SetPrecision(int N)
{
        PTLink.SetPrecision(N);
}

void pt4taskmaker::SetRequiredDataCount(int N)
{
        PTLink.SetRequiredDataCount(N);
}

void pt4taskmaker::SetTestCount(int N)
{
        PTLink.SetTestCount(N);
}

int pt4taskmaker::Center(int I, int  N, int  W, int B)
{
        return PTLink.Center(I,N,W,B);
}

void pt4taskmaker::DataFileN(const char* FileName, int Y, int W)
{
        PTLink.DataFileN(FileName,Y,W);
}

void pt4taskmaker::DataFileR(const char* FileName, int Y, int W)
{
        PTLink.DataFileR(FileName,Y,W);
}

void pt4taskmaker::DataFileC(const char* FileName, int Y, int W)
{
        PTLink.DataFileC(FileName,Y,W);
}

void pt4taskmaker::DataFileS(const char* FileName, int Y, int W)
{
        PTLink.DataFileS(FileName,Y,W);
}


void pt4taskmaker::DataFileT(const char* FileName, int Y1, int Y2)
{
        PTLink.DataFileT(FileName,Y1,Y2);
}

void pt4taskmaker::ResultFileN(const char* FileName,  int Y, int W)
{
        PTLink.ResultFileN(FileName,Y,W);
}

void pt4taskmaker::ResultFileR(const char* FileName, int Y, int W)
{
        PTLink.ResultFileR(FileName, Y,W);
}

void pt4taskmaker::ResultFileC(const char* FileName,  int Y, int W)
{
        PTLink.ResultFileC(FileName,Y,W);
}


void pt4taskmaker::ResultFileS(const char* FileName, int Y, int W)
{
        PTLink.ResultFileS(FileName,Y,W);
}

void pt4taskmaker::ResultFileT(const char* FileName, int Y1, int Y2)
{
        PTLink.ResultFileT(FileName,Y1,Y2);
}

void pt4taskmaker::SetPointer(int NP, PNode P)
{
        PTLink.SetPointer(NP,P);
}

void pt4taskmaker::DataList(int NP, int X, int Y)
{
        PTLink.DataList(NP,X,Y);
}


void pt4taskmaker::ResultList(int NP, int X, int Y)
{
        PTLink.ResultList(NP,X,Y);
}

void pt4taskmaker::DataBinTree(int NP, int X, int Y1, int Y2)
{
        PTLink.DataBinTree(NP,X,Y1,Y2);
}

void pt4taskmaker::ResultBinTree(int NP, int X, int Y1, int Y2)
{
        PTLink.ResultBinTree(NP,X,Y1,Y2);
}

void pt4taskmaker::DataTree(int NP,  int X, int Y1, int Y2)
{
        PTLink.DataTree(NP,X,Y1,Y2);
}

void pt4taskmaker::ResultTree(int NP, int X, int Y1, int Y2)
{
        PTLink.ResultTree(NP,X,Y1,Y2);
}

void pt4taskmaker::ShowPointer( int NP)
{
        PTLink.ShowPointer(NP);
}

void pt4taskmaker::SetNewNode(int NNode)
{
        PTLink.SetNewNode(NNode);
}

void pt4taskmaker::SetDisposedNode(int NNode)
{
        PTLink.SetDisposedNode(NNode);
}

int pt4taskmaker::WordCount()
{
        return PTLink.WordCount();
}

int pt4taskmaker::SentenceCount()
{
        return PTLink.SentenceCount();
}

int pt4taskmaker::TextCount()
{
        return PTLink.TextCount();
}

char* pt4taskmaker::WordSample(int N)
{
        return PTLink.WordSample(N);
}

char* pt4taskmaker::SentenceSample(int N)
{
        return PTLink.SentenceSample(N);
}

char* pt4taskmaker::TextSample(int N)
{
        return PTLink.TextSample(N);
}

int pt4taskmaker::EnWordCount()
{
        return PTLink.EnWordCount();
}

int pt4taskmaker::EnSentenceCount()
{
        return PTLink.EnSentenceCount();
}

int pt4taskmaker::EnTextCount()
{
        return PTLink.EnTextCount();
}

char* pt4taskmaker::EnWordSample(int N)
{
        return PTLink.EnWordSample(N);
}

char* pt4taskmaker::EnSentenceSample( int N)
{
        return PTLink.EnSentenceSample(N);
}

char* pt4taskmaker::EnTextSample(int N)
{
        return PTLink.EnTextSample(N);
}

void pt4taskmaker::CommentText(const char* S)
{
        PTLink.CommentText(S);
}

void pt4taskmaker::UseComment(const char* GroupName,const char* SubgroupName)
{
        PTLink.UseComment(GroupName,SubgroupName);
}

void pt4taskmaker::UseComment(const char* GroupName)
{
        PTLink.UseComment(GroupName);
}

void pt4taskmaker::Subgroup(const char* SubgroupName)
{
        PTLink.Subgroup(SubgroupName);
}

void pt4taskmaker::SetObjectStyle()
{
        PTLink.SetObjectStyle();
}

void __stdcall activate(const char * DllName)
{
        PTLink.activate(DllName);
}

void pt4taskmaker::SetProcess(int ProcessRank)
{
        PTLink.SetProcess(ProcessRank);
}

int pt4taskmaker::RandomN(int M, int N)
{
       if (M >= N)
         return M;
       return M + rand()%(N - M + 1);
}

double pt4taskmaker::RandomR(double A, double B)
{
       if (A >= B)
         return A;
       return rand()/(RAND_MAX+1.0) * (B-A) + A;
}

void pt4taskmaker::ShowInfo(const char* info)
{
       PTLink.ShowInfo(info);
}


