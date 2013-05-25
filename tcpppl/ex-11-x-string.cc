#include <cstring>
#include <iostream>

class String
{
    struct Srep;            //表示
    Srep *rep;

public:
    class Cref;             //引用char

    class RangeError{ };    //用于异常

    String();
    String(const char*);
    String(const String&);
    String& operator=(const char*);
    String& operator=(const String&);
    String& operator+=(const String&);
    String& operator+=(const char*);
    void Check(int) const;
    char Read(int i) const;
    void Write(int, char);
    Cref operator[](int);
    char operator[](int) const;
    int Size() const;
    const char* c_str();
    virtual ~String();
};

struct String::Srep
{
    char *s;                //到元素的指针
    int sz;                 //字符个数
    int n;                  //引用计数

    Srep(int nsz, const char* p)
    {
        n = 1;
        sz = nsz;
        s = new char[sz + 1];//为结束符增加空间
        strcpy(s, p);
    }

    ~Srep(){ delete[] s;}

    Srep* GetOwnCopy()
    {
        if( 1 == n){
            return this;
        }
        n--;
        return new Srep(sz, s);
    }

    void Assign(int nsz, const char* p)
    {
        if(sz != nsz){
            delete[] s;
            sz = nsz;
            s = new char[sz + 1];
        }
        strcpy(s, p);
    }

private:                    //防止复制
    Srep(const Srep&);  
    Srep& operator=(const Srep&);
};    

class String::Cref          //引用s[i]
{
    friend  class String;
    String &s;
    int i;
    Cref(String& ss, int ii):s(ss), i(ii) { }

public:
    operator char() const { return s.Read(i); }
    
    //Cref在行为上就像是char&，除了向其中写时它将会调用String::GetOwnCopy()
    void operator=(char c) { s.Write(i, c); }
};

String& String::operator+=(const String& str)
{
    return *this += str.rep->s;
}

String& String::operator+=(const char* str)
{
    //写时复制
    rep = rep->GetOwnCopy();
    int size = rep->sz + strlen(str);
    char* s = new char[size + 1];
    strcpy(s, rep->s);
    strcat(s, str);
    rep->Assign(size, s);
    delete s;
    return *this;
}

String operator+(const String& s1, const String& s2)
{
    String str = s1;
    str += s2;
    return str;
}

String operator+(const String& s1, const char* s2)
{
    String str = s1;
    str += s2;
    return str;
}

const char* String::c_str()
{
    return rep->s;
}

void String::Check(int i) const
{
    if(i<0 || i>= rep->sz){
        throw RangeError();
    }
}

int String::Size() const 
{ 
    return rep->sz; 
}

void String::Write(int i, char c)
{
    //写时复制
    rep = rep->GetOwnCopy();
    rep->s[i] = c;
}

char String::Read(int i) const 
{ 
    return rep->s[i]; 
}

String::Cref String::operator[](int i)
{
    Check(i);
    return Cref(*this, i);
}

char String::operator[](int i) const
{
    Check(i);
    return rep->s[i];
}

String::String()
{
    rep = new Srep(0, "");
}

String::~String()
{
    if(--(rep->n) == 0){
        delete rep;
    }
}

String::String(const char*s)
{
    rep = new Srep(strlen(s), s);
}

String::String(const String &s)
{
    s.rep->n++;
    this->rep = s.rep;       //共享表示
}

String& String::operator=(const String& x)
{
    x.rep->n++;
    if(--rep->n == 0){
        delete rep;
    }
    rep = x.rep;
    return *this;
}

String& String::operator=(const char* s)
{
    if(rep->n == 1){
        rep->Assign(strlen(s), s);
    }else{
        rep->n--;
        rep = new Srep(strlen(s), s);
    }
    return *this;
}

int main(void)
{
    using std::cout;
    String str1("Hello, world!");
    String str2("Hello,cpp!");
    String str3 = str1 + str2;
    cout << str1.c_str() << '\n';
    cout << str2.c_str() << '\n';
    cout << str3.c_str() << '\n';
}
