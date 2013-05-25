
template<class T>
T* dcast<T *>(void* p)
{
}

class A
{
public:
    virtual ~A(){}
};

class B:public A
{
};

int main()
{
    B* pb = new B();
    A* pa = dcast<A*>(pb);
}