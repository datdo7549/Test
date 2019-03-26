#pragma once


#include <iostream>
#include<vector>
#include<string>

#define MAX_POSITION_64_BIT 63
#define MAX_POSITION_128_BIT 127
#define OCT 8
#define BIN 2
#define DEC 10
#define HEX 16

using namespace std;

class QInt {
private:
	vector<long long> arrayBits;
public:
	//done
	QInt();    //tạo vô đối
	QInt(string, int);     //tạo Qint theo kiểu số int( 10,2,16)


	//done
	vector<long long> getArrayBits();

	//done
	void onBitQIntAt(int position);
	void onBitLongLongAt(long long &, int);
	void offBitQIntAt(int position);
	void offBitLongLongAt(long long &, int);


	//done
	void exportBitsOf(string);
	bool getBitAt(int);
	bool getBitLongLongAt(long long &, int);
	void setBitAt(int, int);
	string toBinString();
	QInt binStringToQInt(string);

	//done
	void push_bit_back(int);
	string div2(string);

	//still working
	QInt operator+(QInt);
	QInt operator-(QInt);
	QInt operator*(QInt);
	pair<QInt,QInt> operator/(QInt);

	//done
	QInt operator>>(int);
	QInt operator<<(int);

	//done
	QInt operator&(QInt);
	QInt operator~();
	QInt operator|(QInt);
	QInt operator^(QInt);

	//done
	string convertDecToBin(string);
	QInt towCompelementOf(string);
	pair<char, char> plusBit(char a, char b);

	//    string convertOcToBin();
	//    string convertHexToBin();

	pair<int, char> plusBit1(int a, int b,char c);
};



