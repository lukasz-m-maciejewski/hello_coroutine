#include "coroutine.hpp"

Generator<std::int64_t> getPrimes()
{
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


int main()
{
    Generator<int64_t> primes = getPrimes();
    for (int i = 0; i < 100; ++i) {
        std::cout << primes.next() << " is prime\n";
    }
    return 0;
}
