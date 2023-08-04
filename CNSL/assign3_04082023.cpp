//============================================================================
// Name        : Assign2_31152_04082023.cpp
// Author      : AdityaMore7000
// Version     :1.0.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
class Hamming{
	string data;
public:
	Hamming(string);
	string convertToAscii();
};
Hamming::Hamming(string data){
	this->data = data;
}
string Hamming::convertToAscii(){
string op = "";
string ip = this->data;
	for(int i = 0;i<ip.length();i++){
		op+=ip[i]+"";
	}
	return op;
}
int main() {
	Hamming h("PICT");
	cout<<h.convertToAscii()<<'\n';
}