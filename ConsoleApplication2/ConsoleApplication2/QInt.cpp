#include "pch.h"
#include "QInt.h"


//tạo vô đối
QInt::QInt() {
	arrayBits = vector< long long>(2,0);
}

//chuyển từ dạng string sang dạng QInt
QInt::QInt(string s, int flag) {
	QInt::arrayBits = vector<long long>(2, 0);
	switch (flag)
	{
	case DEC: {
		if (s[0] == '-') {   //trường hợp số âm, chuyển về bù 2
			*this = towCompelementOf(QInt(s.substr(1), 10).toBinString());
		}
		else {
			int i = 0;
			while (s != "0") 
			{
				int bit = (s[s.size() - 1] - 48) % 2;
				QInt::setBitAt(i, bit);
				s = div2(s);
				i++;
			}
		}
		break;
	}
	case BIN: {
		*this = binStringToQInt(s);
		break;
	}
	case HEX: {
		cout << "still working!!" << endl;
		break;
	}
	}
}

//get vector long long để xử lý khi cần, truy xuất dô từng array[0] hoặc [1]
vector<long long> QInt::getArrayBits() {
	return arrayBits;
}

//lấy kết quả của phép chia s/2.
string QInt::div2(string s) {
	string s1;
	char s2[5];
	int chia = s[0] - 48;
	int i = 1;
	if (s.length() != 1) {
		while (i < s.length()) {
			if (chia < 2) {
				int temp = s[i] - 48;
				chia = chia * 10 + temp;
			}
			else {
				i--;
			}
			s1 = s1 + to_string(chia / 2);
			chia = chia % 2;
			i++;
		}
	}
	else {
		s1 = s1 + to_string(chia / 2);
	}
	return s1;
}

//cái này thêm 1 bit vào cuối thôi, không cần thiết
void QInt::push_bit_back(int bit) {
	*this = *this << 1;
	setBitAt(0, bit);
}

//hiểu rồi, cái này là đưa về đúng vị trí cần bật lên
void QInt::onBitQIntAt(int position) {  
	int tmp = 1;
	if (position > MAX_POSITION_64_BIT)
	{
		position -= (MAX_POSITION_64_BIT + 1);
		tmp = 0;
	}
	QInt::onBitLongLongAt(arrayBits[tmp], position);    //hàm bật bit ở array[0] hoặc [1].
}

//hiểu cái này rồi (dịch dô đúng vị trí rồi or với cái array)
void QInt::onBitLongLongAt(long long &a, int position)   
{
	unsigned long long k = 1;
	a = (k << position) | a;
}

//hiểu rồi, cái này là đưa về đúng vị trí cần tắt bit
void QInt::offBitQIntAt(int position)      
{ 
	int tmp = 1;
	if (position > MAX_POSITION_64_BIT)
	{
		position -= (MAX_POSITION_64_BIT + 1);
		tmp = 0;
	}
	QInt::offBitLongLongAt(arrayBits[tmp], position);
}

//hiểu rồi, dịch k position bit, rồi not nó lại để tất cả các bit còn lại bật lên 1, còn bit tại position bằng 0, sau đó & với a.
//để bit tại position của a bằng 0.
void QInt::offBitLongLongAt(long long &a, int position) {
	unsigned long long k = 1;
	a = a & ~(k << position); 
}

//hiểu rồi, dịch bit 1 của k đến vị trí position, nếu ngay vị trí position của a bằng 1 thì khi & lại thì chắc chắn ra 1 số( có 1 bit 1),
//còn nếu tại vị trí position của a bằng 0 thì khi & lại chắc chắn ra 0, tại vì tất cả các bit xung quanh 1 của k đều bằng 0.Nếu ra số
//thì return 1( bit tại position bằng 1), còn lại thì return 0 (bit đó bằng 0).
bool QInt::getBitLongLongAt(long long &a, int position) {
	unsigned long long k = 1;
	return (k << position) & a;   
}

// hiểu rồi, cái này để đưa về đúng vị trí , sau đó mới lấy giá trị của nó.
bool QInt::getBitAt(int position)       
{
	int tmp = 1;
	if (position > MAX_POSITION_64_BIT)
	{
		position -= (MAX_POSITION_64_BIT + 1);
		tmp = 0;
	}
	return getBitLongLongAt(arrayBits[tmp], position);
}

//hiểu r, hàm này set bit (1 or 0) tại vị trí position.
void QInt::setBitAt(int position, int bit)    
{
	if (bit == 1)  //1 là bật bit
	{
		onBitQIntAt(position);  //hàm bật bit
	}
	else {
		offBitQIntAt(position);  //hàm tắt bit
	}
}


//chưa làm
void QInt::exportBitsOf(string number) {

}

//Dịch phải dịch trái hình như sai
QInt QInt::operator>>(int c) {
	QInt::arrayBits[1] = QInt::arrayBits[1] >> c; //dịch sang phải c bit của array[1] như bình thường. 
	for (int i = 0; i < c; i++) //lấy c bit của array[0] đem sang c bit cuối của array[1]
	{
		QInt::setBitAt(MAX_POSITION_64_BIT - i, getBitAt(-i + MAX_POSITION_64_BIT+c)); // MAX_POSITION_64_BIT - i : vị trí cần set
	}																					//getBitAt(i + 1 + MAX_POSITION_64_BIT): lấy đc giá 
	QInt::arrayBits[0] = QInt::arrayBits[0] >> c;										//trị của bit đó
	return *this;
}

QInt QInt::operator<<(int c) {
	QInt::arrayBits[0] = QInt::arrayBits[0] << c;
	for (int i = 0; i < c; i++) {
		QInt::setBitAt(MAX_POSITION_64_BIT + 1 + i, getBitAt(MAX_POSITION_64_BIT - i));
	}
	QInt::arrayBits[1] = QInt::arrayBits[1] << c;
	return *this;
}


//Phép &, & theo từng phần
QInt QInt::operator&(QInt t) {
	vector< long long> tmp = t.getArrayBits();
	QInt::arrayBits[1] = QInt::arrayBits[1] & tmp[1];
	QInt::arrayBits[0] = QInt::arrayBits[0] & tmp[0];
	return *this;
}

//phép or
QInt QInt::operator|(QInt t) {
	vector< long long> tmp = t.getArrayBits();
	QInt::arrayBits[1] = QInt::arrayBits[1] | tmp[1];
	QInt::arrayBits[0] = QInt::arrayBits[0] | tmp[0];
	return *this;
}

//phép not
QInt QInt::operator~() {
	QInt::arrayBits[1] = ~QInt::arrayBits[1];
	QInt::arrayBits[0] = ~QInt::arrayBits[0];
	return *this;
}

//phép xor
QInt QInt::operator^(QInt t) {
	vector< long long> tmp = t.getArrayBits();
	QInt::arrayBits[1] = QInt::arrayBits[1] ^ tmp[1];
	QInt::arrayBits[0] = QInt::arrayBits[0] ^ tmp[0];
	return *this;
}


//Phép cộng, done
QInt QInt::operator+(QInt t) 
{
	/*int temp = 0;
	QInt result;
	int a, b;
	for (int i = 0; i < 128 ; i++)
	{
		a = this->getBitAt(i);
		b = t.getBitAt(i);
		if (temp == 0)
		{
			if (a != b)
				result.setBitAt(i, 1);
			else
			{
				if (a == 1)
				{
					result.setBitAt(i, 0); temp = 1;
				}
				else
					result.setBitAt(i, 0);
			}
		}
		else
		{
			if (a != b)
				result.setBitAt(i, 0);
			else
			{
				if (a == 1)
				{
					result.setBitAt(i, 1);
				}
				else
				{
					result.setBitAt(i, 1);
					temp = 0;
				}
			}
		}
	}
	return result;*/

	QInt result;
	char temp = '0';
	int a, b;
	for (int i = 0; i < 128; i++)
	{
		a = this->getBitAt(i);
		b = t.getBitAt(i);
		pair<int, char> p = plusBit1(a, b,temp);
		result.setBitAt(i, p.first);
		temp = p.second;
	}
	return result;
}
//Qui ước phép cộng 1 +1, 0+1...
pair<int, char> QInt::plusBit1(int a, int b, char c)
{
	if (c == '0')
	{
		if (a != b)
		{
			return { 1,'0'};
		}
		else
		{
			if (a == 0)
			{
				return { 0,'0'};
			}
			else
			{
				return { 0,'1'};
			}
		}
	}
	else
	{
		if (a != b)
		{
			return { 0,'1'};
		}
		else
		{
			if (a == 0)
			{
				return { 1,'0'};
			}
			else
			{
				return { 1,'1'};
			}
		}
	}
}
//Phép trừ, xong rồi.
QInt QInt::operator-(QInt t)
{
	QInt result;
	t = t.towCompelementOf(t.toBinString());
	return result = *this + t;
}
//phép nhân, xong rồi.
QInt QInt::operator*(QInt t) {
	QInt A = QInt();
	int k = 128;
	int Q1 = 0;
	int temp;
	while (k > 0)
	{
		temp = t.getBitAt(0);
		if (temp == 1 && Q1 == 0)
		{
			A = A - *this;
		}
		if (temp == 0 && Q1 == 1)
		{
			A = A + *this;
		}
		Q1 = t.getBitAt(0);
		t = t >> 1;
		t.setBitAt(127, A.getBitAt(0));
		A = A >> 1;
		k--;
	}
	string s = A.toBinString();
	s = s + t.toBinString();
	QInt result = binStringToQInt(s);
	return result;
}





pair<QInt,QInt> QInt::operator/(QInt t) {      

	QInt A = QInt();
	int n = 128;
	int temp,temp2;
	while (n > 0)
	{
		temp = A.getBitAt(127);
		if (temp == 0)
		{
			A = A << 1;           
			A.setBitAt(0, t.getBitAt(127));
			t = t << 1;
			A = A - *this;
		}
		else
		{
			A = A << 1;
			A.setBitAt(0, t.getBitAt(127));
			t = t << 1;
			A = A + *this;
		}
		temp2 = A.getBitAt(127);
		if (temp2 == 0)
		{
			t.setBitAt(0, 1);
		}
		else
		{
			t.setBitAt(0, 0);
		}
		n--;
	}
	if (A.getBitAt(127) == 1)
	{
		A = A + *this;
	}
	
	return { t,A };  //thương: t, số dư: A
}


//đưa QInt về chuỗi nhị phân
string QInt::toBinString() 
{
	string res = "";
	for (int i = MAX_POSITION_128_BIT; i >= 0; i--)
	{
		res.push_back(getBitAt(i) + 48);
	}
	return res;
}
//chuyển từ hệ 10 chuỗi sang hệ 2 chuỗi.
string QInt::convertDecToBin(string s) {
	return QInt(s, DEC).toBinString();
}

//chuyển về dạng bù 2, đưa vào QInt
QInt QInt::towCompelementOf(string s) {
	string res = "";
	char tmp = '1';
	for (int i = s.size() - 1; i >= 0; i--) { //vừa đảo bit vừa cộng luôn.
		s[i] == '1' ? s[i] = '0' : s[i] = '1';   //đảo ngược bit , đưa về bù 1
		pair<char, char> p = plusBit(s[i], tmp);    //rồi cộng 1, được bù 2
		res += p.first;
		tmp = p.second;
	}
	reverse(res.begin(), res.end());
	return binStringToQInt(res);   //đưa string về QInt
	
}

//Qui ước phép cộng 1+1.. cho phép cộng của 1 số với 1
pair<char, char> QInt::plusBit(char a, char b) {
	if (a != b) {
		return { '1','0' };
	}
	else {
		if (a == '0') {
			return { '0','0' };
		}
		else {
			return { '0','1' };
		}
	}
}

//đưa từ string về QInt
QInt QInt::binStringToQInt(string bit) {
	QInt res = QInt();
	for (int i = 0; i < bit.size(); i++) {
		res.setBitAt(bit.size() - 1 - i, bit[i] - 48);
	}
	return res;
}
