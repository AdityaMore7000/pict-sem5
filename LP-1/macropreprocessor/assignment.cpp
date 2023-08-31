#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<vector<string>> ip;
    vector<string> line;
    fstream fin;
    fin.open("input.txt", ios::in);
    string word;
    while(getline(fin, word))
    cout<<word<<'\n';
    cout<<"Program executed successfully...\n";
    return 0;
}
