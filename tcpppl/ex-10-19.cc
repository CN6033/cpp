#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<sstream>
#include<algorithm>

using std::map;
using std::string;
using std::vector;
using std::find;
using std::cin;
using std::istream;
using std::istringstream;

namespace TCPPPL
{

int GetWordLines(const vector<string> words, istream &input, map<string, vector<int> > &word_lines_map)
{
    int line_num = 1;
    string line, word;
    while(getline(input, line)){
        istringstream stream(line);
        while(stream >> word){
            //it has to be a const_iterator since words is a const vector<...>
            vector<string>::const_iterator it = find(words.begin(), words.end(), word);
            if(it != words.end()){
                word_lines_map[word].push_back(line_num);
            }
        }
        line_num++;
    }
    return 0;
}
}

int main(int argc, char **argv)
{
    vector<string> words;
    words.push_back("hello");
    words.push_back("cpp");
    words.push_back("world");
    map<string, vector<int> > word_lines_map;

    TCPPPL::GetWordLines(words, cin, word_lines_map);
}
