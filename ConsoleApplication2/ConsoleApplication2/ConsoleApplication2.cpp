// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <string>
#include <bitset>
#include<vector>
#include"QInt.h"

using namespace std;

#include "pch.h"
#include<string>
#include<vector>
#include<stdio.h>
#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;


struct Kieu4
{
	string Dangso;
	string Sot1;
	string pheptinh;
	string Sot2;
};

struct Kieu3
{
	string Dangso;
	string DangCanChuyenHoacToanTu;
	string Dulieu;
};
void Doc(string s) //lay du lieu tu file
{
	std::ifstream fi;
	fi.open(s, std::ios::in);
	while (!fi.eof())
	{
		Kieu4 a;
		Kieu3 b;
		std::string tmp;
		std::getline(fi, tmp);
		int k = 0;
		for (int j = 0; j < tmp.length(); j++)
		{
			if (tmp[j] == ' ')
			{
				k++;
			}
		}
		if (k == 3)
		{
			int h = 0;
			while (tmp[h] != ' ') h++;
			a.Dangso = tmp.substr(0, h);
			int k = h + 1;
			while (tmp[k] != ' ') k++;
			a.Sot1 = tmp.substr(h + 1, k - h - 1);
			int l = k + 1;
			while (tmp[l] != ' ') l++;
			a.pheptinh = tmp.substr(k + 1, l - k - 1);
			a.Sot2 = tmp.substr(l + 1, tmp.length() - l - 1);
			QInt q1 = QInt(a.Sot1, atoi(a.Dangso.c_str()));
			QInt q2 = QInt(a.Sot2, atoi(a.Dangso.c_str()));
			QInt result;
			QInt sodu;
			if (a.pheptinh == "+")
			{
				result = q1 + q2;
			}
			else if (a.pheptinh == "-")
			{
				result = q1 - q2;
			}
			else if(a.pheptinh=="*")
			{
				result = q1 * q2;
			}
			else if(a.pheptinh=="/")
			{
				pair<QInt, QInt> p = q2 / q1;
				result = p.first;
				sodu = p.second;

			}
			/*else if (a.pheptinh == ">>")
			{

			}
			else if (a.pheptinh == "<<")
			{

			}*/
			cout << result.toBinString();
		}
		if (k == 2)
		{
			int u = 0;
			while (tmp[u] != ' ') u++;
			b.Dangso = tmp.substr(0, u);
			int p = u + 1;
			while (tmp[p] != ' ') p++;
			b.DangCanChuyenHoacToanTu = tmp.substr(u + 1, p - u - 1);
			b.Dulieu = tmp.substr(p + 1, tmp.length() - p - 1);

		}
	}

}
int main(int argc, const char * argv[])
{
	////test convert dec to bin
	
	//cout << q1.toBinString() << endl;
	////    cout << q1.toBinString() << endl;

	QInt q1 = QInt("100", 10);
	QInt q2 = QInt("3", 10);
	//q2 = q2.towCompelementOf(q2.toBinString());
	//cout << q2.toBinString();
	//QInt result = q1 * q2;
	//cout << result.toBinString();
	//cout<<result.toBinString();
	//QInt q3 = QInt("-1142307800", 10);
	//cout << q3.toBinString();
	//cout << q1.toBinString();
	//cout << q5.toBinString();
	//pair<QInt, QInt> p = q2 / q1;       // cái này nghĩa là q1/q2 và chia dưới dạng 2 số nguyên, tuỳ theo bài sẽ chuyển kết quả về số âm sau
	//cout << "thuong: " << endl;
	//QInt dat = p.first;
	//cout << dat.toBinString();
	//cout << endl;
	//QInt phat = p.second;
	//cout << phat.toBinString();
	Doc(argv[1]);
	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
