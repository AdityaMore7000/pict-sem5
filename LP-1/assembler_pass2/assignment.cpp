#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
using namespace std;
class SymTab{
	public:
	vector<vector<string>> table;
};
class Pass2{
	public:
	void generate();
};
void Pass2::generate(){
	return;
}
int main()
{
	fstream lit, sym, input, output;
	lit.open("input.txt", ios::in);
	string s = "";
	while (getline(lit, s))
	{
		cout << s << '\n';
	}
	return 0;
}