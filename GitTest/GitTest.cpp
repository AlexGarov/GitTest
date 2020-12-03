#include <iostream>
using namespace std;
template<int n>
struct F
{
	enum 
	{
		value=n*F<n-1>::value
	};
};
template<>
struct F<1>
{
	enum
	{
		value = 1
	};
};

class A
{
public:
	enum {
		a=8
	};
};
class B
{
public:
	enum {
		a = A::a
	};
};
int main()
{
	
	auto t = B::a;
	cout << F<15>::value << endl;
	return 0;
}