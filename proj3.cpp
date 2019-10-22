#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>

#include <cwchar>
#include <locale>
using namespace std;
typedef basic_string<wchar_t> wstring;

static locale l1("es_ES.utf8");

struct modified_whitespace : std::ctype<wchar_t>
{
        bool do_is(mask m, char_type c) const
        {
                if ((m & space) && c == L' ') {
                        return true; // space will be classified as whitespace
                }
                if ((m & space) && c == L',') {
                        return true; // comma will be classified as whitespace
                }
                if ((m & space) && c == L'.') {
                        return true; // point will be classified as whitespace
                }
                if ((m & space) && c == L'-') {
                        return true; // dash will be classified as whitespace
                }
                return ctype::do_is(m, c); // leave the rest to the parent class
        }
};

struct comp
{
        template<typename T>
        bool operator()(const T& l, const T& r) const
        {
                if (l.second != r.second)
                        return l.second < r.second;

                return l.first < r.first;
        }
};

// Read the contents of a textfile using a spanish locale
wstring getFileContent(const char* filename)
{
        wifstream wif(filename);
        wif.imbue(l1);
        wstringstream wss;
        wss << wif.rdbuf();
        return wss.str();
}

// reads the file and returns all the words as a vector
vector<wstring> readFile(const char* filename) {
        vector<wstring> result;
        wstring token;
        wstring fileContent = getFileContent(filename);
        wistringstream resultStream(fileContent);
        modified_whitespace* my_ws = new modified_whitespace;
        resultStream.imbue(locale(resultStream.getloc(), my_ws));
        while (resultStream >> token) {
                result.push_back(token);
        }
        return result;
}

map<wstring,int> countWordsMap(vector<string> const &input){
        map<wstring, int> result;
        for(auto const& i: input) {
                result[i]++;
        }
        return result;
}

unordered_map<wstring,int> countWordsUmap(vector<string> const &input){
        unordered_map<wstring, int> result;
        for(auto const& i: input) {
                result[i]++;
        }
        return result;
}

typedef pair<wstring, int> pairs;
set<pairs> getTopWords(map<wstring,int> unsorted, int numOfWords = 30) {
        // create a empty vector of pairs
        set<pairs, comp> set(unsorted.begin(), unsorted.end());
        set<pairs> result(set.begin(), next(set.begin(), numOfWords))
        return result;
}

int main(){

        // TODO TODO TODO TODO TODO TODO
        // wstring s = L"ohad computer science";
        // wcout.imbue(l1);
        // wcout << s << endl;


        return 0;

}
