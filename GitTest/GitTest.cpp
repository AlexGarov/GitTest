#include<iostream>
#include<vector>
#include<map>
int Plus(int arg1, int arg2)
{
	return arg1 + arg2;
}
int Minus(int arg1, int arg2)
{
	return arg1 - arg2;
}

int main()
{

	std::map<char, int(*)(int, int)> cal;
	cal.insert(std::pair<char, int(*)(int, int)>('+', Plus));
	cal.insert(std::pair<char, int(*)(int, int)>('-', Minus));

	auto it = cal.find('+');
	if (it != cal.end())
		std::cout << it->second(6,8);     
	else std::cout << "str not found\n";


	
	int stop = 0;
	return 0;
}