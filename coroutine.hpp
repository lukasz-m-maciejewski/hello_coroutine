#include <coroutine>
#include <iostream>

using namespace std::experimental::coroutines_v1;

template<typename T>
struct Promise;
template<typename T>
class Generator;

template<typename T>
using Handle = std::experimental::coroutines_v1::coroutine_handle<Promise<T>>;

template<typename T>
struct Promise
{
    Promise() : val { T() } {}
    std::experimental::coroutines_v1::suspend_always initial_suspend() { return {}; }
    std::experimental::coroutines_v1::suspend_always final_suspend() { return {}; }
    Generator<T> get_return_object();
    void unhandled_exception() { abort(); }
    void return_value(T val) {
        this->val = val;
    }
    std::experimental::coroutines_v1::suspend_always yield_value(T val) {
        this->val = val;
        return {};
    }

    T val;
};

template<typename T>
class Generator
{
public:
        explicit Generator(Handle<T> handle)
        : m_handle (handle)
    {}
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

template<typename T>
Generator<T> Promise<T>::get_return_object()
{
    return Generator<T> { Handle<T>::from_promise(*this) };
}


template<typename T>
T Generator<T>::next()
{
    if (m_handle) {
        m_handle.resume();
        return m_handle.promise().val;
    } else {
        return T();
    }
}

//End general purpose library
