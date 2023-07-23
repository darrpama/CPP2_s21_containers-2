#ifndef CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_

#include <limits>

#include "../Map/BTree.h"

namespace s21 {

template <typename KT>
class Set {
  using key_type = KT;
  using value_type = KT;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type = s21::BTree<KT>;
  using iterator = typename tree_type::iterator;
  using const_iterator = const typename tree_type::iterator;
  using size_type = size_t;

 public:
  Set();
  explicit Set(std::initializer_list<value_type> const &);
  Set(const Set &s);
  Set(Set &&s);
  ~Set();
  reference operator=(std::initializer_list<value_type> const &);
  reference operator=(const Set &);
  reference operator=(Set &&);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void erase(const value_type &value);
  void swap(Set &other);
  void merge(Set &other);

  iterator find(const KT &key);
  bool contains(const KT &key);

 private:
  tree_type tree_;
  size_type size_;
};

// Default constructor
template <typename KT>
s21::Set<KT>::Set() : tree_(), size_(0) {}

// Constructor for initializer list
template <typename KT>
s21::Set<KT>::Set(std::initializer_list<value_type> const &items)
    : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item, item);
    size_++;
  }
}

// Copy constructor
template <typename KT>
s21::Set<KT>::Set(const Set &other) : size_(0) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    tree_.insert(it.getNode()->key, *it);
    size_++;
  }
}

// Move constructor
template <typename KT>
s21::Set<KT>::Set(Set &&other) : Set() {
  swap(other);
}

// Destructor
template <typename KT>
s21::Set<KT>::~Set() {
  if (size_ > 0 && tree_.getRoot()) {
    size_ = 0;
    tree_.destroy(tree_.getRoot());
  }
}

// Getter size_
template <typename KT>
typename s21::Set<KT>::size_type s21::Set<KT>::size() {
  return size_;
}

// Getter maxsize
template <typename KT>
typename s21::Set<KT>::size_type s21::Set<KT>::max_size() {
  return ((std::numeric_limits<size_type>::max() / 2) - sizeof(s21::BTree<KT>) -
          sizeof(s21::Node<KT>)) /
         sizeof(s21::Node<KT>);
}

template <typename KT>
typename s21::Set<KT>::reference s21::Set<KT>::operator=(
    std::initializer_list<value_type> const &items) {
  swap(Set<KT>(items));
  return *this;
}

// Assignment operator overload for copy object
template <typename KT>
typename s21::Set<KT>::reference s21::Set<KT>::operator=(const Set &s) {
  if (this == &s) return *this;
  for (auto it = s.tree_.begin(); it != s.tree_.end(); ++it) {
    tree_.insert(it.getNode()->key, *it);
    size_++;
  }
  return *this;
}

template <typename KT>
typename s21::Set<KT>::reference s21::Set<KT>::operator=(Set &&s) {
  if (this == &s) return *this;
  swap(s);
  return *this;
}

// Method to find iterator to specific node
template <typename KT>
typename s21::Set<KT>::iterator s21::Set<KT>::find(const KT &key) {
  return tree_.searchNode(key);
}

// Returns iterator to begin
template <typename KT>
typename s21::Set<KT>::iterator s21::Set<KT>::begin() {
  return tree_.begin();
}

// Returns iterator after end node
template <typename KT>
typename s21::Set<KT>::iterator s21::Set<KT>::end() {
  return tree_.end();
}

// Method to check, is set empty
template <typename KT>
bool s21::Set<KT>::empty() {
  return size_ == 0;
}

// Destroy the all Set
template <typename KT>
void s21::Set<KT>::clear() {
  tree_.destroy(tree_.getRoot());
  size_ = 0;
}

// Insert a new unique value into set
template <typename KT>
std::pair<typename s21::Set<KT>::iterator, bool> s21::Set<KT>::insert(
    const KT &value) {
  if (tree_.search(value) != nullptr) {
    return std::pair<iterator, bool>{nullptr, false};
  }
  auto it = tree_.insert(value, value);
  size_++;
  return std::pair<iterator, bool>{it, true};
}

// Delete one node by getting iterator
template <typename KT>
void s21::Set<KT>::erase(typename s21::Set<KT>::iterator pos) {
  auto node = pos.getNode();
  tree_.removeNode(node, node->key);
  size_--;
}

// Delete one node by getting value
template <typename KT>
void s21::Set<KT>::erase(const typename s21::Set<KT>::value_type &value) {
  auto node = this->find(value).getNode();
  tree_.removeNode(node, node->key);
  size_--;
}

// Swap two sets
template <typename KT>
void s21::Set<KT>::swap(Set &other) {
  using std::swap;
  swap(size_, other.size_);
  swap(tree_, other.tree_);
}

// Merge two sets
template <typename KT>
void s21::Set<KT>::merge(Set &other) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    insert(it.getNode()->key);
  }
}

// Check is key containing in set
template <typename KT>
bool s21::Set<KT>::contains(const KT &key) {
  return (tree_.search(key) != nullptr);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
