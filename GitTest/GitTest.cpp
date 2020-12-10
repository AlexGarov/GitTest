#include <iostream>
#include <Windows.h>
#include <vector>
#include <DirectXMath.h>
#include <type_traits>
using namespace std;
using namespace DirectX;

class VerticLayout
{
public:
	enum  ElementType
	{
		Position2,
		Normal,
	};
	class Element
	{
	public:
		
		Element(ElementType type, size_t offset )
			:_type(type),
			offset(offset)
		{		
		}
		size_t GetOffsetAfter()const
		{
			return offset+ SizeOf(_type);
		}
		
		  size_t SizeOf(ElementType type)const
		{
			switch (type)
			{
			case VerticLayout::Position2:
				return sizeof(XMFLOAT2);
				
			case VerticLayout::Normal:
				return  sizeof(XMFLOAT3);
				
			default:
				break;

			}
			return -1;
		}
		size_t GetOffset() const
		{
			return offset;
		}
		ElementType GetType() const noexcept
		{
			return _type;
		}
	private:
		ElementType _type;
		size_t offset;
	};

	template<ElementType type>
	decltype(auto)Append()
	{
		
		_element.push_back({ type, Size() });
		
		
		return *this;
	}
	vector<Element>& GetElement()
	{
		return _element;
	}
	
	size_t Size()
	{	
		
		size_t temp= _element.empty() ? 0u : _element.back().GetOffsetAfter();
		return temp;
	}
	Element GetElementByIndec(int i)
	{
		return _element[i];
	}
	
	template<ElementType Type>
	const Element& Resolve() const noexcept
	{
		for (auto& e : _element)
		{
			if (e.GetType() == Type)
			{
				return e;
			}
		}
		assert("Could not resolve element type" && false);
		return _element.front();
	}
private:
	vector<Element> _element;
	
};

class Vertix
{
	friend class VertexBuffer;
public:
	Vertix(char* pData, VerticLayout& vertexLayout)
		:
		_pData(pData),
		_vertexLayout(vertexLayout)
	{
		assert(pData != nullptr);
	}
	template<VerticLayout::ElementType Type>
	auto& GetAttr()
	{
		const auto& element = _vertexLayout.Resolve<Type>();
		auto pAttribute = _pData + element.GetOffset();
		if constexpr (Type == VerticLayout::Position2)
		{
			return *reinterpret_cast<XMFLOAT2*>(pAttribute);
		}
		else if constexpr (Type == VerticLayout::Normal)
		{
			return *reinterpret_cast<XMFLOAT3*>(pAttribute);
		}
		
		else
		{
			assert("Bad element type" && false);
			return *reinterpret_cast<char*>(pAttribute);
		}
		//return *reinterpret_cast<char*>('e');
	}
	template<typename First>
	void SetBufferByIndex(unsigned int index, First&& first)
	{
		const auto& element = _vertexLayout.GetElementByIndec(index);
		auto pAttribute = _pData + element.GetOffset();

		switch (element.GetType())
		{
		case VerticLayout::Position2:
			SetAttribute<XMFLOAT2>(pAttribute, forward<First>(first));
			break;
		case VerticLayout::Normal:
			SetAttribute<XMFLOAT3>(pAttribute, forward<First>(first));
			break;
		default:
			assert("Do not match");
			break;
		}
	}
	template<typename First, typename ...Rest>
	void SetBufferByIndex(unsigned int index, First&& first, Rest&& ... rest)
	{
		SetBufferByIndex(index,forward< First>(first));
		SetBufferByIndex(index+1,forward< Rest>(rest)...);
	}
	template<typename Dest, typename Src>
	void SetAttribute(char* pAttribute, Src&& val)
	{

		if constexpr (std::is_assignable<Dest, Src>::value)
		{
			*reinterpret_cast<Dest*>(pAttribute) = val;
		}
		else
		{
			assert("Parameter attribute type mismatch" && false);
		}

	}
private:
	char* _pData = nullptr;
	VerticLayout& _vertexLayout;

};
class ConstBuffer
{
public:
	ConstBuffer(const Vertix& v)
		:
		_vertix(v)
	{		
	}
	template<VerticLayout::ElementType Type>
	const auto& GetAttr()const
	{
		return const_cast<Vertix&>(_vertix).GetAttr< Type>();
	}

private:
	Vertix _vertix;
};
class VerticBuffer
{
	
public:
	VerticBuffer()
	{
		int r = 0;
	}
	VerticBuffer( VerticLayout && vl)
		:
		layout(move(vl))
	{		
	}

	VerticBuffer(const VerticBuffer& b)
	{
		int r = 0;
	}
	VerticBuffer& operator=(const VerticBuffer& b)
	{
		return *this;
	}
	template<typename ... T>
	void EmplaceBack(T&& ... arg)
	{
		// get size for our buffer
		
		assert(sizeof ...(T) == layout.GetElement().size() && "size VertexLayout!= buffer");
		_buffer.resize(_buffer.size() + layout.Size());		
		Back().SetBufferByIndex(0u, forward<T>(arg) ...);
		
	}
	Vertix Back()
	{
		return Vertix{ _buffer.data() + _buffer.size() - layout.Size(),layout };
	}
	Vertix Front()
	{
		return Vertix{ _buffer.data(),layout };
	}
	
	Vertix operator [](unsigned int index) 
	{		
		return Vertix{ _buffer.data()+ layout.Size()* index,layout };
	}
	ConstBuffer operator[](unsigned int index) const
	{		
		return const_cast<VerticBuffer&>(*this)[index];
	}
private:
	vector <char> _buffer;
	VerticLayout layout;	
};

int main()
{

		VerticLayout vl;
		vl.Append< VerticLayout::Position2>().Append< VerticLayout::Normal>();
		
			
		VerticBuffer vb(move(vl));
		vb.EmplaceBack(XMFLOAT2{ 1.1f,0.9f}, XMFLOAT3{ 1.3f,0.9f,0.3f });
		vb.EmplaceBack(XMFLOAT2{ 1.3f,0.9f }, XMFLOAT3{ 1.3f,2.9f,0.3f });
		
		auto pos1 = vb[0].GetAttr<VerticLayout::Position2>();
		auto nor1 = vb[0].GetAttr<VerticLayout::Normal>();
		auto pos2 = vb[1].GetAttr<VerticLayout::Position2>();
		auto nor2 = vb[1].GetAttr<VerticLayout::Normal>();

		vb.Back().GetAttr<VerticLayout::Position2>().x = 0.1f;
		auto nor2n = vb[1].GetAttr<VerticLayout::Position2>();
		const VerticBuffer &cvb = vb;
		auto pos = cvb[1].GetAttr<VerticLayout::Position2>();

	
	return 0;
}