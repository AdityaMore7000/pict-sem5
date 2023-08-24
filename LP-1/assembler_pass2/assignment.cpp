#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
using namespace std;
class SymTab{
	public:
	vector<vector<string>> table;
	void print(){
		for(auto i:table){
			for(auto j:i){
				cout<<j<<' ';
			}
			cout<<'\n';
		}
	}
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
	SymTab SYMTAB; 
	fstream lit, sym, input, output;
	sym.open("sym.txt", ios::in);
	string s;
	while(getline(sym,s)){
	int count = 0;
	while(s[count] == ' ')
	count++;
	s = s.substr(count,s.size()-1);
	vector<string> line;
	stringstream ss(s);
	string word;
	while(ss>>word){
		line.push_back(word);
	}
	SYMTAB.table.push_back(line);
	}
	SYMTAB.print();
	return 0;
}