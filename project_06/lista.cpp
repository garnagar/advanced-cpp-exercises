#include "lista.h"
#include <vector>
#include <algorithm>

template <typename T>
void showContainer(T begin, T end) {
  for (auto it = begin; it != end; ++it) {
    std::cout << (*it) << '\n';
  }
}

int main() {
  //creating Lista
  Lista<int> l1;
  l1.push_front(1);
  l1.push_front(2);
  l1.push_front(3);

  //testing iterator by printing first element
  Lista<int>::iterator it;
  it = l1.begin();
  std::cout << "First element (last pushed): " << *it << std::endl;

  //copying to vector
  std::vector<int> v;
  std::copy(l1.begin(),l1.end(),std::back_inserter(v));
  std::cout << "Copied vector: " << '\n';
  showContainer(v.begin(),v.end());

  //finding min element
  std::cout << "Min element: " << *std::min_element(v.begin(),v.end()) << '\n';

}
