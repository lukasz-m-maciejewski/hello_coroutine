#include <coroutine>
#include <iostream>

struct MinimalCoro {
  struct promise_type {
    MinimalCoro get_return_object() {
      return {.h_ = std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
  };

  std::coroutine_handle<promise_type> h_;
};

MinimalCoro func() {
 std::clog << "before\n";
 co_await std::suspend_always{};
 std::clog << "after\n";
}

int main() {
  auto mc = func();
  mc.h_.resume();
  mc.h_.resume();
  mc.h_.resume();

  static_cast<void>(mc);

  return 0;
  return 0;
}
