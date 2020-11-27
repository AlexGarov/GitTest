
#include <iostream>
using namespace std;
class A
{
public:
    
    A(int a)
    {
        i = a;
    }
    int i;
};
class B:public A
{
public:
   // using A::A;
   // using A::i;
   /* B(int i):A(i)
    {

    }*/
   
       void Bind()
       {
           cout << " Bind(int i)::B= "<<i<<endl;

       }
       
};
class App
{
public:
    App(int i)
    {
        b = new B(i);
        b->Bind();
    };
    B *b;
};
int main()
{
    App app(8);

    std::cout << "alex 12:31";
}

