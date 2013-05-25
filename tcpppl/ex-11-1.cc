#include<iostream>

struct X
{
    int i;
    X(int);
    X operator+(int);
};

X::X(int _x):i(_x){}

X X::operator+(int a)
{
    this->i += a;
    return *this;
}

struct Y
{
    int i;
    Y(X);
    Y operator+(X);
    operator int const();
};

Y::Y(X _x):i(_x.i){}

Y Y::operator+(X _x)
{
    return Y(this->i + _x.i);
}

Y::operator int const()
{
    return this->i;
}

extern X operator*(X, Y);
extern int f(X);


X operator*(X _x, Y _y)
{
    return X(_x.i * _y.i);
}

int f(X _x)
{
    return 0;
}

X x = 1;
Y y = X(2);
int i = 2;

int main()
{
    using std::cout;
    using std::endl;

    cout << (i + 10) << endl;//OK
    //y + 10;//Invalid: ambiguity, could mean (int)y + 10 or y + X(10)
    //y + 10 * y;//Invalid: ambiguity, could mean y + (10 * (int)y) or y + (X(10) * y)
    x + y + i;
    x * x + i;
    f(7);
    //f(y);//Invalid: no implicit conversion from type Y to X
    y + y;
    106 + y;
}
