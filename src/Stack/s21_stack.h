#ifndef CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_

#include "../List/s21_list.h"

namespace s21 {

template <class T, class Container = s21::List<T>>
class Stack {
 public:
  // Aliases declaration
  using container_type = Container;
  using value_type = typename Container::value_type;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  // Stack Member functions
  Stack() : container_() {}
  Stack(std::initializer_list<value_type> const &items) : container_(items) {}
  Stack(const Stack &s) : container_(s.container_) {}
  Stack(Stack &&s) : container_(std::move(s.container_)) {}
  ~Stack() {}

  Stack &operator=(const Stack &s);
  Stack &operator=(Stack &&s);

  // Stack Element access
  const_reference top() { return container_.back(); }

  // Stack Capacity
  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }

  // Stack Modifiers
  void push(const_reference value) { container_.push_back(value); }
  void pop() { return container_.pop_back(); }
  void swap(Stack &other) { container_.swap(other.container_); }

  // Stack bonus
  template <class... Args>
  void insert_many_front(Args &&...args) {
    container_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  Container container_;
};

template <class T, class Container>
Stack<T, Container> &Stack<T, Container>::operator=(
    const Stack<T, Container> &s) {
  container_ = s.container_;
  return *this;
}

template <class T, class Container>
Stack<T, Container> &Stack<T, Container>::operator=(Stack<T, Container> &&s) {
  container_ = std::move(s.container_);
  return *this;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_
