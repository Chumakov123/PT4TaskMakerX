#include "pt4taskmakerX.h"

using namespace pt4taskmakerX;

DefineGroupName;

DefineTask(Task1)
{
  pt::NewTask(R"(\S�������� �������.\s ������������ ������� (������ 1)
  ������������ ������� (������ 2)
  \P����� ����� ������������ ������� (������ 3))"
  );
  int a = pt::Random(1, 9);
  pt::Data("������ ������� ������: a = ", a);
  pt::Res("������ �������������� ������: 2 * a = ", 2 * a);
  pt::SetTestCount(5);
}

DefineTask(Task2)
{
  pt::UseTask("Begin", 3);
}

void __stdcall inittaskgroup()
{
  pt::NewGroup("�������� ������", "", "qwqfsdf13dfttd");
}
