#include <bits/stdc++.h>
#include <string.h>
using namespace std;
int main()
{
  fstream file;
  string s, temp;
  vector<string> res;
  file.open("./ass2_code.txt", ios::in);
  while (getline(file, s))
  {
    for (int i = 0; i < s.length(); i++)
      if (s[i] == ',')
        s[i] = ' ';
    temp = "";
    for (int i = 0; i < s.length(); i++)
    {
      if (s[i] != ' ' || i != s.length())
      {
        temp += s[i];
      }
      else
      {
        res.push_back(temp);
        temp="";
      }
    }
    for(string i: res) cout<<i<<'\n';
  }
  file.close();
}
