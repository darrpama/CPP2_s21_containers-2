#ifndef CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class T, size_t N>
class Array {
 public:
  // Aliases declaration
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Array Member functions
  Array();
  explicit Array(std::initializer_list<value_type> const &);
  Array(const Array &);
  Array(Array &&) noexcept;
  ~Array();
  Array &operator=(const Array &);
  Array &operator=(Array &&);

  // Array Element access
  reference at(size_type);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Array Iterators
  iterator begin();
  iterator end();

  // Array Capacity
  bool empty();
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Array Modifiers
  void swap(Array &);
  void fill(const_reference);

 private:
  size_type size_;
  iterator data_;
};

// Default constructor, creates empty array
template <class T, size_t N>
Array<T, N>::Array() : size_(N), data_(new T[N]{}) {}

// Initializer list constructor,
// creates Array initizialized using std::initializer_list
template <class T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items)
    : size_(N), data_(new T[N]{}) {
  size_type count = items.size();
  if (count > size_) throw std::length_error{"Too large count"};
  int index = 0;
  for (const T &item : items) {
    data_[index] = item;
    index++;
  }
}

// Copy constructor
template <class T, size_t N>
Array<T, N>::Array(const Array &other) : size_(other.size_), data_(new T[N]{}) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

// Move constructor
template <class T, size_t N>
Array<T, N>::Array(Array &&origin) noexcept : Array() {
  swap(origin);
}

// Assignment operator overload for moving object
template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array<T, N> &&origin) {
  if (this == &origin) return *this;
  swap(origin);
  return *this;
}

// Assignment operator overload for copying object
template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(const Array<T, N> &origin) {
  if (this == &origin) return *this;
  for (size_type i = 0; i < size_; ++i) data_[i] = origin.data_[i];
  return *this;
}

// Destructor
template <class T, size_t N>
Array<T, N>::~Array() {
  delete[] data_;
}

// Access specified element with bounds checking
template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range{"Position is out of range."};
  return data_[pos];
}

// Access specified element
template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

// Access the first element
template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
  if (empty()) throw std::out_of_range{"Position is out of range."};
  return data_[0];
}

// Access the last element
template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
  if (empty()) throw std::out_of_range{"Position is out of range."};
  return data_[size_ - 1];
}

// Direct access to the underlying Array
template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return data_;
}

// Returns an iterator to the beginning
template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
  return data_;
}

// Returns an iterator to the end
template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
  return data_ + size_;
}

// Checks whether the container is empty
template <class T, size_t N>
bool Array<T, N>::empty() {
  return size_ == 0;
}

// Returns the number of elements
template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
  return size_;
}

// Returns the maximum possible number of elements
template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const noexcept {
  return size_;
}

// Swaps the contents
template <class T, size_t N>
void Array<T, N>::swap(s21::Array<T, N> &v) {
  using std::swap;
  swap(size_, v.size_);
  swap(data_, v.data_);
}

// Assigns the given value value to all elements in the container
template <class T, size_t N>
void Array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) data_[i] = value;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
