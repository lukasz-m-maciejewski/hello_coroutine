#include <coroutine>

namespace gucicoro {

template <typename T>
struct Promise;
template <typename T>
class Generator;

template <typename T>
using Handle = std::coroutine_handle<Promise<T>>;

template <typename T>
struct Promise {
  Promise() : val{T()} {}
  std::suspend_always initial_suspend() noexcept { return {}; }
  std::suspend_always final_suspend() noexcept { return {}; }
  Generator<T> get_return_object();
  void unhandled_exception() { abort(); }
  void return_value(T val) { this->val = val; }
  std::suspend_always yield_value(T val) {
    this->val = val;
    return {};
  }

  T val;
};

template <typename T>
class Generator {
 public:
  explicit Generator(Handle<T> handle) : m_handle(handle) {}
  ~Generator() {
    if (m_handle) {
      m_handle.destroy();
    }
  }
  T next();
  using promise_type = Promise<T>;

 private:
  Handle<T> m_handle;
};

template <typename T>
Generator<T> Promise<T>::get_return_object() {
  return Generator<T>{Handle<T>::from_promise(*this)};
}

template <typename T>
T Generator<T>::next() {
  if (m_handle) {
    m_handle.resume();
    return m_handle.promise().val;
  } else {
    return T();
  }
}

}  // namespace gucicoro
