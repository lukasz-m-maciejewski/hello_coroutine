#include <coroutine>
#include <iostream>

template <typename T>
struct AwaitableType {
  AwaitableType(T future) : m_future{std::move(future)} {}
  bool await_ready() {
    std::clog << "await_ready\n";
    return true;
  }

  void await_suspend(std::coroutine_handle<> h) {
    static_cast<void>(h);
    std::clog << "await_suspend\n";
  }

  typename T::return_type await_resume() {
    std::clog << "await_resume\n";
    return m_future.getResult();
  }

  T m_future;
};

struct ReturnValue {
  using return_type = int;
  return_type getResult() { return value; }
  AwaitableType<ReturnValue> operator co_await() noexcept {
    std::clog << "operator co_await\n";
    return AwaitableType{*this};
  }

  int value;
};

struct MinimalCoro {
  struct promise_type {
    MinimalCoro get_return_object() {
      return {.h_ = std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() {}

    // AwaitableType await_transform(ReturnValue) { return {}; }
  };

  std::coroutine_handle<promise_type> h_;
};

ReturnValue foo(int x) { return {.value = x}; }

MinimalCoro func() {
  std::clog << "before\n";
  int res = co_await foo(42);
  std::clog << typeid(res).name() << '\n';
  std::clog << "we've got: " << res << '\n';
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
