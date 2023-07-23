#ifndef CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_

#include "../List/s21_list.h"

namespace s21 {

template <class T, class Container = s21::List<T>>
class Queue {
 public:
  // Aliases declaration
  using container_type = Container;
  using value_type = typename Container::value_type;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  // Queue Member functions
  Queue() : container_() {}
  Queue(std::initializer_list<value_type> const &items) : container_(items) {}
  Queue(const Queue &s) : container_(s.container_) {}
  Queue(Queue &&s) : container_(std::move(s.container_)) {}
  ~Queue() {}

  Queue &operator=(const Queue &s);
  Queue &operator=(Queue &&s);

  // Queue Element access
  const_reference front() { return container_.front(); }
  const_reference back() { return container_.back(); }
  // Queue Capacity
  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }
  // Queue Modifiers
  void push(const_reference value) { container_.push_back(value); }
  void pop() { return container_.pop_front(); }
  void swap(Queue &other) { container_.swap(other.container_); }
  // Queue bonus
  template <class... Args>
  void insert_many_back(Args &&...args) {
    container_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  Container container_;
};

template <class T, class Container>
Queue<T, Container> &Queue<T, Container>::operator=(
    const Queue<T, Container> &s) {
  container_ = s.container_;
  return *this;
}

template <class T, class Container>
Queue<T, Container> &Queue<T, Container>::operator=(Queue<T, Container> &&s) {
  container_ = std::move(s.container_);
  return *this;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_
