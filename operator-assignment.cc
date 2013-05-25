#include <iostream>

class A
{
public:
    A(int a)
        :a_(a)
    {
        std::cout << "Constructor" << std::endl;    
    }

    A()
        :a_(0)
    {
        std::cout << "Constructor" << std::endl;
    }

    A(const A& inst)
    {
        this->a_ = inst.a_;
        std::cout << "Copy Constructor" << std::endl;
    }

    /*
       A operator=(const A& inst)
       如果按照这种方式申明函数，函数每次返回时，将调用一次拷贝构造函数。
       对于一般的函数，如果返回一个对象的引用或指针，则有可能造成引用或
       指针指向一个已经被释放了的对象，具体见EC29。但是，对于运算符重载
       成员函数，它返回的是自身对象，而不是其他对象，因为能保证函数调用
       后自身对象仍然存在，所以EC29不适用于这种情况。
     */
    A& operator=(const A& inst)
    {
        this->a_ = inst.Get();
        return *this;
    }

    int Get() const
    {
        return a_;
    }
private:
    int a_;
};

int main()
{
    A a,b,c;
    a = b = c = 1;
}
