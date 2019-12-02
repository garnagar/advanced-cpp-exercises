#include "lista.h"
#include <vector>
#include <algorithm>

template<typename ValueType>
class ListaIterator {

};

template <typename T>
void showContainer(T begin, T end) {
  for (auto it = begin; it != end; ++it) {
    std::cout << (*it) << '\n';
  }
}

int main() {
  //creating Lista
  Lista<int> l1();
  for(int i = 0; i < 10; ++i) {
    l1.push_front(i);
  }

  //testing iterator by printing first element
  Lista<int>::iterator it;
  it = l1.begin();
  std::cout << "First element:" << *it << std::endl;

  //copying to vector
  std::vector<int> v(l1.end()-l1.begin());
  std::copy(l1.begin(),l1.end(),v.begin());
  std::cout << "Copied vector:" << '\n';
  showContainer(v.begin(),v.end());

  //finding min element
  std::cout << "Min element: " << *std::min_element(l1.begin(),l1.end()) << '\n';

}
