#include<iostream>
#include<boost/noncopyable.hpp>

namespace
{
class DontTreadOnMe: private boost::noncopyable
{
public:
    DontTreadOnMe() 
    { 
        std::cout << "defanged!" << std::endl; 
    }
};// DontTreadOnMe
}// unnamed namespace

int main()
{
    DontTreadOnMe object1;
    //DontTreadOnMe object2(object1);
    //object1 = object2;
    return 0;
}// main
