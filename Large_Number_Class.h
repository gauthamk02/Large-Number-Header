
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

class LN
{
	string add_string(string & numberA, string & numberB);
	string number;
public:
	LN(char n);
	LN(string & n);
	LN() : number("0") {};
	LN(const char number[]);
	void set_number(string & number);
	string get_number();
	unsigned long long size();
	void operator =(string & n);
	void operator++ ();
	void operator++ (int);
	void operator-- ();
	void operator-- (int);
	LN operator + (LN & n2);
	LN operator - (LN & n2);
	LN operator * (LN & n2);
	LN operator / (LN & n2);
	bool operator < (LN & n2);
	bool operator > (LN & n2);
	operator bool();
	bool reserve (size_t digits);
};

string LN::add_string(string & numberA, string &  numberB)
{
	int carry = 0;      //carry

	string number1 = numberA.size() >= numberB.size() ? numberB : numberA; //setting number1 to the smaller of the two numbers
	reverse(number1.begin(), number1.end()); //reversing the number to align them
	string number2 = numberA.size() >= numberB.size() ? numberA : numberB; //setting number1 to the bigger of the two numbers
	reverse(number2.begin(), number2.end()); //reversing the number to align them

	int minlen = min(number1.size(), number2.size());
	int maxlen = max(number1.size(), number2.size());

	for (int i = 0; i < minlen; i++)
	{
		char x = (number1[i] - 48 + number2[i] - 48 + carry) + 48;
		carry = 0;
		if (x > '9')
		{
			carry = 1;
			x = x - 10;
		}
		number2[i] = x;
	}
	for (int i = minlen; i < maxlen; i++)
	{
		char x = number2[i] + carry;
		carry = 0;
		if (x > '9')
		{
			carry = x - 57;
			x -= 10;
		}
		number2[i] = x;
	}
	if (carry == 1)
	{
		number2.push_back('1');
	}
	reverse(number2.begin(), number2.end());
	return number2;
}

LN::LN(char x)
{
	number = x;
}

LN::LN(const char * number)
{
	this->number = number;
}

LN::LN(string & n)
{
	number = n;
}

void LN::set_number(string & number)
{
	this->number = number;
}

string LN::get_number()
{
	return number;
}

unsigned long long LN::size()
{
	return number.size();
}

void LN:: operator =(string & n)
{
	number = n;
}

void LN::operator++()
{
	size_t lastValue = number.size() - 1;
	if (number[lastValue] < '9')
	{
		number[lastValue] += 1;
	}
	else
	{
		string x = "1";
		number = add_string(number,x);
	}
}

void LN::operator++(int)
{
	size_t lastValue = number.size() - 1;
	if (number[lastValue] < '9')
	{
		number[lastValue] += 1;
	}
	else
	{
		string x = "1";
		number = add_string(number, x);
	}
}

void LN::operator--()
{
	size_t lastvalue = number.size() - 1;
	if(number[lastvalue] > '0')
	{
		number[lastvalue] -= 1;
	}
	else
	{
		number = LN(LN(number) - LN("1")).get_number();
		if (number[0] == '0')
		{
			number.erase(number.begin());
		}
	}
}

void LN::operator--(int)
{
	size_t lastvalue = number.size() - 1;
	if (number[lastvalue] > '0')
	{
		number[lastvalue] -= 1;
	}
	else
	{
		number = LN(LN(number) - LN("1")).get_number();
	}
}

LN LN::operator+(LN &  n2)
{
	return add_string(number, n2.number);
}

LN LN::operator-(LN & n2)
{
	int carry = 0;      //carry
	string number1 = number;
	string number2 = n2.number;
	int n2s = number2.size();
	n2s--;
	for (int i = 0; i < n2s; i++)
	{
		number2[i] = ('9' - number2[i]) + 48;
	}
	number2[n2s] = (('9' + 1) - number2[n2s]) + 48;
	n2s++;
	int n1s = number1.size();
	string temp = add_string(number1, number2);
	if (number1.size() == n2s)
	{
		temp.erase(0, 1);
	}
	else
	{
		int pos = n1s - n2s - 1;
		if (temp[pos] > '0')
		{
			if (temp[pos] > '1')
			{
				temp[pos] -= 1;
			}
			else
			{
				temp[pos] -= 1;
				temp[pos + 1] = '9';
			}
		}
		else
		{
			int i = pos;
			for (; temp[i]<'1'; i--)
			{
				temp[i] = '9';
			}
			temp[i] -= 1;
		}
	}
	if (temp[0] == '0')
	{
		temp.erase(0,1);
	}
	return temp;
}

LN LN::operator * (LN & n2)
{
	string temp = "0";
	for (LN i = string("0"); i < n2; ++i)
	{
		temp = add_string(temp, number);
	}
	return LN(temp);
}

LN LN::operator / (LN & n2)
{
	LN quotient = "0";
	LN num = LN(number);
	while (num >= n2)
	{
		num = num - n2;
		quotient++;
	}
	return quotient;
}

bool LN::operator < (LN & n2)
{
	if (number.size() != n2.number.size())
	{
		return number.size() < n2.number.size() ? true : false;
	}
	else
	{
		int l = number.size();
		for (int i = 0; i < l; i++)
		{
			if (number[i] < n2.number[i]) return true;
			else if (number[i] > n2.number[i])return false;
		}
		return false;
	}
}

bool LN::operator > (LN & n2)
{
	if (number.size() != n2.number.size())
	{
		return number.size() > n2.number.size() ? true : false;
	}
	else
	{
		int l = number.size();
		for (int i = 0; i < l; i++)
		{
			if (number[i] > n2.number[i]) return true;
			else if (number[i] < n2.number[i])return false;
		}
		return false;
	}
}

LN::operator bool()
{
	if (number.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/*bool LN::reserve(size_t digits)
{
	number.reserve(digits);
	return true;
}*/
