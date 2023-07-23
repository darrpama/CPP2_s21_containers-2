#ifndef CPP2_S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class T>
class Vector {
  class VectorIterator;
  class VectorConstIterator;

 public:
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector();
  explicit Vector(size_type);
  explicit Vector(std::initializer_list<T> const &);
  Vector(const Vector &);
  Vector(Vector &&) noexcept;
  Vector<T> &operator=(std::initializer_list<value_type> const &);
  Vector<T> &operator=(const Vector<T> &);
  Vector<T> &operator=(Vector<T> &&);
  ~Vector();
  reference at(size_type);
  reference operator[](size_type);
  const_reference front();
  const_reference back();
  iterator data();
  iterator begin();
  iterator end();
  bool empty();
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type);
  size_type capacity() const noexcept;
  void shrink_to_fit();
  void clear() noexcept;
  iterator insert(iterator, const_reference);
  void erase(iterator);
  void push_back(const_reference);
  void pop_back();
  void swap(Vector<T> &);

  template <class... Args>
  iterator insert_many(const_iterator, Args &&...);

  template <class... Args>
  void insert_many_back(Args &&...);

 private:
  size_type size_;
  size_type capacity_;
  iterator storage_;

  void reallocate(size_type capacity, size_type size, const iterator storage);
};

// Default constructor, creates empty vector
template <class T>
Vector<T>::Vector() : size_(0U), capacity_(0U), storage_(nullptr) {}

// Parameterized constructor, creates the vector of size n
template <class T>
Vector<T>::Vector(size_type n)
    : size_(n), capacity_(n), storage_(new T[capacity_]{}) {}

// Initializer list constructor, creates vector initizialized using
// std::initializer_list
template <class T>
Vector<T>::Vector(std::initializer_list<T> const &items) : size_(0) {
  size_type count = items.size();
  capacity_ = count;
  storage_ = new T[capacity_];

  for (const T &item : items) storage_[size_++] = item;
}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector &v)
    : size_(v.size_), capacity_(v.capacity_), storage_(new T[capacity_]) {
  for (size_type i = 0; i < size_; ++i) storage_[i] = v.storage_[i];
}

// Move constructor
template <class T>
Vector<T>::Vector(Vector &&origin) noexcept : Vector() {
  swap(origin);
}

// Assignment operator overload for initializer list constructor
template <class T>
Vector<T> &Vector<T>::operator=(
    std::initializer_list<value_type> const &items) {
  swap(Vector<T>(items));
  return *this;
}

// Assignment operator overload for copy object
template <class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &origin) {
  if (this == &origin) return *this;
  swap(Vector<T>(origin));
  return *this;
}

// Assignment operator overload for moving object
template <class T>
Vector<T> &Vector<T>::operator=(Vector<T> &&origin) {
  if (this == &origin) return *this;
  swap(origin);
  return *this;
}

// Destructor
template <class T>
Vector<T>::~Vector() {
  delete[] storage_;
}

// Access specified element with bounds checking
template <class T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range{"Position is out of range."};
  return storage_[pos];
}

// Access specified element
template <class T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return storage_[pos];
}

// Access the first element
template <class T>
typename Vector<T>::const_reference Vector<T>::front() {
  return storage_[0];
}

// Access the last element
template <class T>
typename Vector<T>::const_reference Vector<T>::back() {
  return storage_[size_ - 1];
}

// Direct access to the underlying array
template <class T>
typename Vector<T>::iterator Vector<T>::data() {
  return storage_;
}

// Returns an iterator to the beginning
template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
  return storage_;
}

// Returns an iterator to the end
template <class T>
typename Vector<T>::iterator Vector<T>::end() {
  return storage_ + size_;
}

// Checks whether the container is empty
template <class T>
bool Vector<T>::empty() {
  return size_ == 0;
}

// Returns the number of elements
template <class T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
  return size_;
}

// Returns the maximum possible number of elements
template <class T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
  return std::numeric_limits<difference_type>::max() / (sizeof(value_type));
}

// Allocate storage of size elements and copies current array elements to a
// newly allocated array
template <class T>
void Vector<T>::reserve(size_type n) {
  if (n > max_size()) throw std::length_error{"too large size"};
  if (n <= capacity_) return;
  s21::Vector<T> tmp;
  tmp.reallocate(n, size_, storage_);
  tmp.swap(*this);
}

// Returns the number of elements that can be held in currently allocated
// storage
template <class T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
  return capacity_;
}

// Reduces memory usage by freeing unused memory
template <class T>
void Vector<T>::shrink_to_fit() {
  s21::Vector<T> tmp;
  tmp.reallocate(size_, size_, storage_);
  tmp.swap(*this);
}

// Clears the contents
template <class T>
void Vector<T>::clear() noexcept {
  for (size_type i = 0; i < size_; ++i) {
    storage_[i].~T();
  }
  size_ = 0;
}

// Inserts elements into concrete pos and returns the iterator that points to
// the new element
template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  s21::Vector<T> tmp(size_ + 1);
  size_type new_element_index = 0;
  iterator ptr = begin();
  size_type i = 0;

  while (ptr <= end()) {
    if (ptr < pos) {
      tmp.storage_[i] = *ptr;
    } else if (ptr == pos) {
      tmp.storage_[i] = value;
      new_element_index = i;
    } else {
      tmp.storage_[i] = *(ptr - 1);
    }
    ptr++;
    ++i;
  }
  tmp.swap(*this);

  return &(storage_[new_element_index]);
}
template <class T>
template <class... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  auto it_pos = const_cast<iterator>(pos);
  for (auto &val : {args...}) {
    it_pos = insert(it_pos, val) + 1;
  }

  return it_pos - 1;
}

template <class T>
template <class... Args>
void Vector<T>::insert_many_back(Args &&...args) {
  for (auto &val : {args...}) {
    push_back(val);
  }
}

// Erases element at pos
template <class T>
void Vector<T>::erase(iterator pos) {
  s21::Vector<T> tmp(size_ - 1);
  iterator ptr = begin();
  size_type i = 0;
  while (ptr < end()) {
    if (ptr < pos) {
      tmp.storage_[i] = *ptr;
    } else {
      tmp.storage_[i] = *(++ptr);
    }
    ptr++;
    ++i;
  }
  tmp.swap(*this);
}

// Adds an element to the end
template <class T>
void Vector<T>::push_back(const_reference value) {
  if (size_ + 1 > capacity_) {
    reserve(capacity_ * 2);  // Increase capacity if needed
  }
  storage_[size_] = value;
  ++size_;
}

// Removes the last element
template <class T>
void Vector<T>::pop_back() {
  storage_[--size_].~T();
}

// Swaps the contents
template <class T>
void Vector<T>::swap(Vector<T> &v) {
  using std::swap;
  swap(size_, v.size_);
  swap(capacity_, v.capacity_);
  swap(storage_, v.storage_);
}

// Helper method
template <class T>
void Vector<T>::reallocate(size_type capacity, size_type size,
                           const iterator storage) {
  storage_ = new T[capacity];
  capacity_ = capacity;
  for (size_type i = 0; i < size; ++i) {
    storage_[i] = storage[i];
  }
  size_ = size;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_
