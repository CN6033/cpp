#include<string>
#include<set>
#include<vector>
#include<algorithm>
#include<iostream>

namespace CppPrimer
{
class ReadBook{
public:
    //Use the C++ keyword explicit for constructors with one argument.
    ReadBook(){}

    virtual ~ReadBook(){}

    std::string AddToReadBook(const std::string &book){
        this->to_read_book.push_back(book);
        return book;
    }

    std::string AddReadedBook(const std::string &book){
        this->readed_book.insert(book);
        return book;
    }

    std::string RemoveToReadBook(const std::string &book){
        std::vector<std::string>::iterator it = std::find(this->to_read_book.begin(), this->to_read_book.end(), book);
        if(it != this->to_read_book.end()){
            this->to_read_book.erase(it);
        }
        return book;
    }

    std::string RemoveReadedBook(const std::string &book){
        std::set<std::string>::iterator it = this->readed_book.find(book);
        if(it != this->readed_book.end()){
            this->readed_book.erase(it);
        }
        return book;
    }

    void Output(){
        std::cout << "*****ToReadBook*****" <<std::endl;
        for(std::vector<std::string>::iterator it = this->to_read_book.begin(); 
                it != this->to_read_book.end(); ++it){
            std::cout << *it << std::endl;
        }
        std::cout << "*****Readed Book*****"<< std::endl;
        for(std::set<std::string>::iterator it = this->readed_book.begin(); 
                it != this->readed_book.end(); ++it){
            std::cout << *it << std::endl;
        }
    }

private:
    std::vector<std::string> to_read_book;
    std::set<std::string> readed_book;
};
}


int main(int argc, char **argv){
    CppPrimer::ReadBook read_book;
    read_book.AddToReadBook("C++ Primer");
    read_book.AddToReadBook("Effective C++");
    read_book.AddToReadBook("More Effective C++");
    read_book.AddReadedBook("Head first Python");
    read_book.Output();
    read_book.AddReadedBook(read_book.RemoveToReadBook("C++ Primer"));
    read_book.Output();
    read_book.AddToReadBook(read_book.RemoveReadedBook("C++ Primer"));
    read_book.Output();
}
