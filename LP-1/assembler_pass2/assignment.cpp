#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
using namespace std;
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