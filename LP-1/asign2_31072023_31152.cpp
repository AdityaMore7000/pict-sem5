#include <bits/stdc++.h>
#include <string.h>
using namespace std;
class Assembler
{
public:
  int LC = 0;
  string instr[200][4];
  string answer[200][3];
  int instr_size = 0;
  map<string, string> condition_codes = {
      {"LT", "(1)"},
      {"LE", "(2)"},
      {"EQ", "(3)"},
      {"GT", "(4)"},
      {"GE", "(5)"},
      {"ANY", "(6)"}};
  map<string, string> reg_table = {
      {"AREG", "(1)"},
      {"BREG", "(2)"},
      {"CREG", "(3)"},
      {"DREG", "(4)"}};
  map<string, string> mn_table = {
      {"STOP", "(IS,00)"},
      {"ADD", "(IS,01)"},
      {"SUB", "(IS,02)"},
      {"MULT", "(IS,03)"},
      {"MOVER", "(IS,04)"},
      {"MOVEM", "(IS,05)"},
      {"COMP", "(IS,06)"},
      {"BC", "(IS,07)"},
      {"DIV", "(IS,08)"},
      {"READ", "(IS,09)"},
      {"PRINT", "(IS,10)"},
      {"START", "(AD,01)"},
      {"END", "(AD,02)"},
      {"ORIGIN", "(AD,03)"},
      {"EQU", "(AD,04)"},
      {"LTORG", "(AD,05)"},
      {"DC", "(DL,01)"},
      {"DS", "(DL,02)"}};
  void readfile()
  {
    fstream file;
    string s, temp = "";
    file.open("input.txt", ios::in);
    int k = 0;
    while (getline(file, s))
    {
      string res[4];
      int count = 0;
      for (int i = 0; i < s.length(); i++)
      {
        if (s[i] == ',' || s[i] == ' ')
        {
          s[i] = '!';
          count++;
        }
      }
      int j = 1;
      if (count == 3)
        j = 0;
      s += "!";
      for (int i = 0; i < s.length(); i++)
      {
        if (s[i] != '!')
        {
          temp += s[i];
        }
        else
        {
          instr[k][j] = temp;
          j++;
          temp = "";
        }
      }
      this->instr_size++;
    k++;
    }
    file.close();
  }
  void writefile()
  {
    fstream file1;
    file1.open("./output.txt", ios::out);
      file1 <<"\t\t"<< this->answer[0][0] << ' ' << this->answer[0][1] << ' ' << this->answer[0][2] << '\n';
    for (int i = 1; i < this->instr_size; i++)
    {
      file1 <<LC+i<<"\t\t"<< this->answer[i][0] << ' ' << this->answer[i][1] << ' ' << this->answer[i][2] << '\n';
    }
    file1.close();
  }
  void assemble(){
    for(int i = 0;i<instr_size;i++){
      answer[i][0] = this->mn_table.at(instr[i][1]);
      if(reg_table.count(instr[i][2]))
      answer[i][1] = this->reg_table.at(instr[i][2]);
      else if(condition_codes.count(instr[i][2]))
      answer[i][1] = this->condition_codes.at(instr[i][2]);
      else{
        // st[st->cnt].add = to_string(LC);
        st[st->cnt].name = this->instr[i][2];
      answer[i][1] = this->condition_codes.at(instr[i][2]);
      }
    }
    LC = stoi(instr[0][2]);
  }
};
class SYMTAB
{
public:
  string name;
  int add;
  int cnt;
  friend class Assembler;
  SYMTAB(){
    name="";
    add=0;
    cnt = 0;
  }
};
class LITTAB
{
public:
  int cnt;
  string name;
  int add;
  friend class Assembler;
  LITTAB(){
    name="";
    add=0;
    cnt = 0;
    }
};
class POOLTAB
{
public:
  int cnt;
  string name;
  int add;
  friend class Assembler;
  POOLTAB(){
    name="";
    add=0;
    cnt = 0;
    }
};
SYMTAB st[20];
LITTAB lt[20];
POOLTAB pt[20];
int main()
{
  Assembler as;
  as.readfile();
  as.assemble();
  as.writefile();
}
