#include<iostream>
#include<vector>
template<char T>
int calculete(int arg1, int arg2);
template<>
int calculete<'+'>(int arg1, int arg2)
{
	return arg1 + arg2;
}
template<>
int calculete<'-'>(int arg1, int arg2)
{
	return arg1 - arg2;
}
template<>
int calculete<'*'>(int arg1, int arg2)
{
	return arg1 * arg2;
}
template<>
int calculete<'/'>(int arg1, int arg2)
{
	return arg1 / arg2;
}

int main()
{
	
	auto i = calculete<'+'>(2, 7);
	int stop = 0;
	return 0;
}