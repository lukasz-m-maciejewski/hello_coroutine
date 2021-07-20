
#include <iostream>

#include "coroutine.hpp"
gucicoro::Generator<int64_t> Fibonacci() {
  int64_t a = 1;
  int64_t b = 1;
  while (true) {
    co_yield a;
    b = a + b;
    a = b - a;
  }
}

int main() {
  gucicoro::Generator<int64_t> fib = Fibonacci();
  std::cout << fib.next();
  for (int i = 0; i < 200; ++i) {
    std::cout << " " << fib.next();
  }
  std::cout << '\n';
  return 0;
}
