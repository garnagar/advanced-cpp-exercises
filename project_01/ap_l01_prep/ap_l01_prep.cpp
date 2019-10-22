#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define RANGE 3 //elment ids can be intagers from 0 to RANGE

struct elment {
  string name;
  int id;
};

vector<elment> v = {{"Anna",0},{"Kerstin",1},{"Britta",2},{"Olle",3},{"Lasse",0},{"Bosse",1}};

void dispElemnets(vector<elment> vec) {
  for(unsigned i = 0; i < vec.size(); ++i) {
    cout << vec.at(i).id << ", ";
    cout << vec.at(i).name << '\n';
  }
}

vector<elment> countSort(vector<elment> vec) {
  vector<int> c(RANGE+1);
  vector<elment> ret(vec.size());
  //histogram
  for(unsigned i = 0; i < vec.size(); ++i) {
    c.at(vec.at(i).id)++;
  }
  //count starting idexses of element ids
  for(unsigned i = 1; i < RANGE+1; ++i) {
    c.at(i) = c.at(i)+c.at(i-1);
  }
  //construct sorted vector
  for(unsigned i = 0; i < vec.size(); ++i) {
    ret.at(c.at(vec.at(i).id)-1) = vec.at(i); //-1 corrects for indexing from 0
    c.at(vec.at(i).id)--;
  }
  return ret;
}

int main() {
  cout << "Unsorted:" << '\n';
  dispElemnets(v);
  cout << '\n';
  cout << "Sorted:" << '\n';
  dispElemnets(countSort(v));
  return 0;
}
