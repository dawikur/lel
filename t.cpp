
#include "include/lel.hpp"

struct Callable {
  template <class... T>
  int operator()(T...) {
    return sizeof...(T);
  }
};

int main() {
  using namespace LeL::Placeholders;
  Callable callable;

  auto count = _(callable)._(_x);

  return count(1, 2);
}
