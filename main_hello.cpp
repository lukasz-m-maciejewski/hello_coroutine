#include <iostream>
#include "coroutine.hpp"

bool isPrime(std::int64_t n) {
  if (n == 2 || n == 3) return true;

  if (n <= 1 || n % 2 == 0 || n % 3 == 0) return false;

  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
  }

  return true;
}

gucicoro::Generator<std::int64_t> getPrimes() {
  std::int64_t num = 0;
  while (true) {
    while (!isPrime(num)) {
      ++num;
    }
    co_yield num;
    ++num;
  }
  co_return 0;
}

int main() {
  gucicoro::Generator<int64_t> primes = getPrimes();
  std::cout << primes.next();
  for (int i = 0; i < 1000000; ++i) {
    std::cout << ", " << primes.next();
  }
  std::cout << '\n';
  return 0;
}
