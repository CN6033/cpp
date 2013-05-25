#include<iostream>
#include<cstddef>

namespace
{
template<class T>class Vector
{
    size_t sz;
    T* ptr;

public:

    explicit Vector(size_t n): sz(n), ptr(new T[n]){}

    T& operator[](size_t index)
    {
        return *(ptr + index);
    }

    size_t size()
    {
        return  sz;
    }

    ~Vector()
    {
        delete[] ptr;
    }
};//class Vector

template<class T> class List
{
public:

    class Link
    {
    public:
        T* x;
        Link* next;

        Link(T* x, Link* n) : x(x), next(n) {}

        ~Link()
        {
            delete next;
        }
    };//class Link

    Link* head;

    List():head(0){}

    ~List()
    {
        delete head;
    }

    void put(T* x){
         head = new Link(x, head);
    }

    T* get(){
        return head->x;
    }
};//class List

template<class T>class Itor
{
public:
    virtual T* first() = 0;
    virtual T* next() = 0;
    virtual ~Itor(){}
};//class Itor

template<class T>class Vector_itor:public Itor<T>
{
    Vector<T>& v;
    size_t index;

public:

    Vector_itor(Vector<T>& vv):v(vv),index(0){}

    T* first()
    {
        return (v.size())? &v[index=0]:0;
    }

    T* next()
    {
        return (++index < v.size())? &v[index]:0;
    }
};//class Vector_itor

template<class T>class List_itor:public Itor<T>
{
    List<T>& list;
    typename List<T>::Link *p;

public:

    List_itor(List<T> &l):list(l), p(list.head){}

    T* first()
    {
        p = list.head;
        return p ? p->x : 0;
    }

    T* next()
    {
        p = p->next;
        return p ? p->x : 0;
    }
};//class List_itor

}// unname namespace


int main()
{
    using namespace std;

    Vector<int> v(5);
    v[0] = 0; v[1] = 1; v[2] = 2; v[3] = 3; v[4] = 4;

    List<int> l;
    l.put(&v[4]); l.put(&v[3]); l.put(&v[2]); l.put(&v[1]); l.put(&v[0]);

    Vector_itor<int> vi(v);
    int* p = vi.first();
    while(p){
        cout << *p << ' ';
        p = vi.next();
    }
    cout << endl;

    List_itor<int> li(l);
    p = li.first();
    while(p){
        cout << *p << ' ';
        p = li.next();
    }
    cout << endl;
    return 0;
}
