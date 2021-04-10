#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>
#include <cmath>


//Write functions in this order.  Constructor and destructor will be built as the
//functions it invokes are written

Calc::Calc(char* argvIn)
{
  inFix = new char[strlen(argvIn) + 1];

  strcpy(inFix,argvIn);

  stk = new Stack; 

  if (!CheckTokens())
  {
    cout << "error with tokens" << endl;
    exit(EXIT_FAILURE); 
  }

  if (!CheckParens())
  {
    cout << "error with parens" << endl;
    exit(EXIT_FAILURE); 
  }

  MakeValueTbl();
  Parse();
  DisplayInFix();
}

Calc::~Calc()
{
}

bool Calc::CheckTokens()
{
  for (int i = 0; i < strlen(inFix); i++)
  {
    char ch = inFix[i];
    switch (inFix[i])
    {
      case '(':
        continue;
      case ')':
        continue;
      case '+':
        continue;
      case '-':
        continue;
      case '/':
        continue;
      case '*':
        continue;
    }
    if (ch >= 0 && ch <= 9)
      continue;
    else if (isupper(ch))
      continue;
    else if (ch = '0')
      break;
    else
      return false;
  }

return true;
}

void Calc::MakeValueTbl()
{
  valueTbl = new int[26] ();
  valueIdx = 0;
}

void Calc::Parse()
{
  for (int i = 0; i < strlen(inFix); i++)
  {
    char ch = inFix[i];
    int pos = 0;

    if (ch >= '0' && ch <= '9')
    {
      pos = FindLast(i);

      if (pos == i + 1)
      {
        valueTbl[valueIdx] = inFix[i];
        inFix[i] = valueIdx + 'A';
        valueIdx++;
      }

      else 
      {
        toValueTable(i, pos);
        toLetter(i, pos);
        valueIdx++; 
      }
    }
      
  }
}

int Calc::FindLast(int pos)
{
while (inFix[pos] >= '0' & inFix[pos] <= '9')
  pos++;
return pos;
}


bool Calc::CheckParens()
{
  for (int i = 0; i < strlen(inFix); i++)
  {
    char ch = inFix[i];
    if (ch == '(')
      stk->Push (ch);
    if (ch == ')' && isEmpty() == false)
      stk->Pop();
  }

if(isEmpty())
  return true;
return false;
}

void Calc::DisplayInFix()
{
  cout << inFix << endl;
}


void Calc::toLetter (int first, int last)
{
  int num = last - first;
  int i = 0;
  inFix[first] = valueIdx + 'A';

  while (inFix[first] != 0)
  {
  inFix[first + 1] = inFix[last + i];
  first++;
  i++;
  }

}

void Calc::toValueTable (int first, int last)
{
  int num = last - first;
  int comp[num], total = 0, j = 0;
 

  for (int i = 0; i < num; i++)
  {
    comp[i] = (inFix[first + i] - '0');
  }

  for (int i = num - 1; i >= 0; i--)
  {
    comp[j] = comp[j] * pow (10, i);
    total = total + comp[j];
    j++;
  }
  
  valueTbl[valueIdx] = total;
}

bool Calc::isEmpty()
{
if (stk->IsEmpty())
  return true;
return false;
}
