#include <list>
#include <algorithm>
#include <iostream>

namespace TCPPPL
{

template<class T> class Sum
{
public:
    Sum(T i=0)
	    :res(i)
	{
		std::cout << "Constructor " << '\n';
	}
	 
	Sum(const Sum& c)
	{
		res = c.result();
		std::cout << "Copy constructor " << '\n';
	}
	
	Sum& operator= (const Sum& c)
	{
		res = c.result();
		std::cout << "Allign..." << '\n';
		return *this;
	}
	
    void operator()(T x)
    {
	    res += x;
    }

    T result() const 
    {
        return res;
    }
     
private:
	T res;
};

void f(std::list<double>& ld)
{
	using std::for_each;
	using std::cout;
	
	Sum<double> sum;
	/*
	The function object is taken by value. for_each returns the function object.
	template <class InputIterator, class Function>
   		Function for_each (InputIterator first, InputIterator last, Function fn);
	*/
	sum = for_each(ld.begin(), ld.end(), sum);
	cout << sum.result() << '\n';
}

}//namspace TCPPPL

int main()
{
	using namespace TCPPPL;
	std::list<double> scores(10, 100.0);
	f(scores);
}
