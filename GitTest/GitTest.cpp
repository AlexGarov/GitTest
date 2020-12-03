#include <iostream>
using namespace std;
class A1
{
public:
	A1()
	{
		cout << "A1\n";
	}
	~A1()
	{
		cout << "~A1\n";
	}
};
class A2
{
public:
	A2()
	{
		cout << "A2\n";
	}
	~A2()
	{
		cout << "~A2\n";
	}
};
class B
{
public:
	B()		
	{
		a1;
		cout << "B\n";
	}
	~B()
	{
		cout << "~B\n";
	}
	A1 a1;
};
class C:public B
{
public:
	C()		
	{
		a2;
		cout << "C\n";
	}
	~C()
	{
		cout << "~C\n";
	}
	A2 a2;
};
int main()
{
	C c;
	return 0;
}