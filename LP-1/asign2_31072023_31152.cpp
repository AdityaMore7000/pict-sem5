#include <bits/stdc++.h>
#include <string.h>
using namespace std;
class Assembler
{
public:
  // int libtab_ptr=0,pooltab_ptr=0;
  // int symIndex=0,litIndex=0;
  map<string, int> SYMTAB;
  vector<int> LITTAB;
  vector<int> POOLTAB;
  int LC = 0;
  string instr[200][4];
  int instr_size = 0;
  map<string, int> condition_codes = {
    {"LT", 1}, 
    {"LE", 2}, 
    {"EQ", 3}, 
    {"GT", 4}, 
    {"GE", 5}, 
    {"ANY", 6}
    };
  map<string, int> reg_table = {
    {"AREG", 1}, 
    {"BREG", 2}, 
    {"CREG", 3}, 
    {"DREG", 4}};
  map<string, string> mn_table = {
      {"STOP", "IS01"},
      {"ADD", "IS02"},
      {"SUB", "IS03"},
      {"MULT", "IS04"},
      {"MOVER", "IS05"},
      {"MOVEM", "IS06"},
      {"COMP", "IS07"},
      {"BC", "IS08"},
      {"DIV", "IS09"},
      {"READ", "IS10"},
      {"PRINT", "IS11"},
      {"START", "AD01"},
      {"END", "AD02"},
      {"ORIGIN", "AD03"},
      {"EQU", "AD04"},
      {"LTORG", "AD05"},
      {"DC", "DL01"},
      {"DS", "DL02"}};
  void readfile()
  {
    fstream file;
    string s, temp = "";
    file.open("input.txt", ios::in);
    while (getline(file, s))
    {
      string res[4];
      for (int i = 0; i < s.length(); i++)
      {
        if (s[i] == ',')
          s[i] = ' ';
      }
      int j = 1;
      if (s.length() == 4)
        j = 0;
      s += "!";
      for (int i = 0; i < s.length(); i++)
      {
        if (s[i] != ' ' && s[i] != '!')
        {
          temp += s[i];
        }
        else
        {
          instr[i][j] = temp;
          j++;
          temp = "";
        }
      }
      this->instr_size++;
      // instr.push_back(res);
    }
    file.close();
  }
};
int main()
{
  Assembler as;
  as.readfile();
  fstream file1;
  file1.open("./output.txt", ios::out);
  for (int i = 0; i < as.instr_size; i++)
  {
    file1 << as.instr[i][0] << ' ' << as.instr[i][1] << ' ' << as.instr[i][2] << ' ' << as.instr[i][3] << '\n';
  }
  file1.close();
  
  // fstream file2;
  // file2.open("./output.txt", ios::app);
  // for (int i = 0; i < as.instr_size; i++)
  // {
  //   file2 << '(' << as.mn_table.at(as.instr[i][0]).substr(0, 2) << ',' << as.mn_table.at(as.instr[i][0]).substr(2, 2) << ')' << '\n';
  // }
}
