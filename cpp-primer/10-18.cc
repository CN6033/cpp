#include<stdexcept>
#include<string>
#include<map>
#include<vector>


namespace CppPrimer
{
    using namespace std;

    int find_names(const string &firstname, 
            const map<string, vector<string> > &family_map, 
            const vector<string> *names){
        map<string, vector<string> >::const_iterator _it = family_map.find(firstname);
        if(_it != family_map.end()){
            names = &(_it->second);
            return 1;
        }else{
            return 0;
        }
    }
}


int main(int argc, char **argv)
{
    using namespace std;

    if (2 != argc){
        throw runtime_error("wrong number of arguments!");
    }

    map<string, vector<string> > family_map;
    const vector<string> *p_names;
    CppPrimer::find_names(argv[1], family_map, p_names);
}
