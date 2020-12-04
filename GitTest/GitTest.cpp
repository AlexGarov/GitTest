#include <iostream>

using namespace std;
void print()
{
}
template<typename T, typename ...Types>
void print(T firstArg, Types ...arg)
{
	cout << firstArg << endl;
	print(arg ...);
}
int main()
{
	int t = 9;
	int* pt = &t;
	print(2, "hgjf", 785.89f,pt ,*pt);
	
	return 0;
}