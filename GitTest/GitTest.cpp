#include<iostream>
#include<vector>
using namespace std;
enum MyEnum
{
	myINT,
	myFLOAT
};
struct MyStruct
{
	char const* str;
	MyEnum my_enum;
};

class MyClass
{

public:
	enum ElementType
	{
		INTEGER,
		FLOATER
	};
	MyClass(ElementType type)
		:
		_type(type)
	{}
	template<ElementType>
	struct Map;

	template<>struct Map<INTEGER>
	{
		using myType = int;
		static constexpr char const* name = "alex";
		static constexpr MyEnum myEnum = myINT;

	};

	template<>struct Map<FLOATER>
	{
		using myType = float;
		static constexpr char const* name = "kola";
		static constexpr MyEnum myEnum = myFLOAT;
	};

	MyStruct GetDes()
	{
		switch (_type)
		{
		case INTEGER:
			return GenerateDes<INTEGER>();
		case FLOATER:
			return GenerateDes<FLOATER>();
		default:
			break;
		}
	}
	template<ElementType Type>
	MyStruct GenerateDes()
	{
		return{ Map<Type>::name, Map<Type>::myEnum };
	}

	

	ElementType _type;

};


int main()
{
	vector<MyStruct> vMyStruct;
	MyClass mci{ MyClass::ElementType::INTEGER};
	MyClass mcf{ MyClass::ElementType::FLOATER };
	vMyStruct.push_back(mci.GetDes());
	vMyStruct.push_back(mcf.GetDes());
	int stop = 0;
	return 0;
}