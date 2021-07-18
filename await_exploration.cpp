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

struct AwaitableType {
  bool await_ready() {
    std::clog << "await_ready\n";
    return false;
  }

  void await_suspend(std::coroutine_handle<> h) {
    static_cast<void>(h);
    std::clog << "await_suspend\n";
  }

  void await_resume() { std::clog << "await_resume\n"; }
};

AwaitableType foo() { return {}; }

MinimalCoro func() {
  std::clog << "before\n";
  auto res = co_await foo();
  std::clog << typeid(res).name() << '\n';
  std::clog << "after\n";
}

int main() {
  auto mc = func();
  std::clog << "res_1\n";
  mc.h_.resume();
  std::clog << "res_2\n";
  mc.h_.resume();
  // mc.h_.resume();

  static_cast<void>(mc);

  return 0;
  return 0;
}
