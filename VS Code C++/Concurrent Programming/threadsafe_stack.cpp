#include "CONCURRENT.h"

struct empty_stack : std::exception {
    const char *what() const noexcept;
};

template <typename T> class threadsafe_stack {
  private:
    std::stack<T> data;
    mutable std::mutex m;

  public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack &other) { //在构造函数体内部拷贝
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_stack &operator=(const threadsafe_stack &) = delete;

    void push(T new_value) {
        std::scoped_lock lock(m);
        data.push(std::move(new_value));
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack(); //试图弹出前检查是否为空栈
        std::shared_ptr<T> const res(
            std::make_shared<T>(data.top())); //改动栈容器前设置返回值
        data.pop();
        return res;
    }

    void pop(T &value) {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw() empty_stack();
        value = data.top();
        data.pop();
    }

    bool empty() const {
        std::scoped_lock lock(m);
        return data.empty();
    }
};