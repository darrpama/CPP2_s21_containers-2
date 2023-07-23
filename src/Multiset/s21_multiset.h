#ifndef CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_

#include <limits>

#include "../Map/BTree.h"

namespace s21 {

template <typename KT>
class Multiset {
  using key_type = KT;
  using value_type = KT;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type = s21::BTree<KT>;
  using iterator = typename tree_type::iterator;
  using const_iterator = const typename tree_type::iterator;
  using size_type = size_t;

 public:
  Multiset();
  explicit Multiset(std::initializer_list<value_type> const &items);
  Multiset(const Multiset &s);
  Multiset(Multiset &&s);
  ~Multiset();

  reference operator=(std::initializer_list<value_type> const &items);
  reference operator=(const Multiset &s);
  reference operator=(Multiset &&s);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(Multiset &other);
  void merge(Multiset &other);

  iterator find(const KT &key);
  bool contains(const KT &key);

 private:
  tree_type tree_;
  size_type size_;
};

// Default constructor
template <typename KT>
Multiset<KT>::Multiset() : tree_(), size_(0) {}

// Constructor for initializer list
template <typename KT>
Multiset<KT>::Multiset(std::initializer_list<value_type> const &items)
    : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item, item);
    size_++;
  }
}

// Copy constructor
template <typename KT>
Multiset<KT>::Multiset(const Multiset &other) : size_(0) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    tree_.insert(it.getNode()->key, *it);
    size_++;
  }
}

// Move constructor
template <typename KT>
Multiset<KT>::Multiset(Multiset &&other) : Multiset() {
  swap(other);
}

// Destructor
template <typename KT>
Multiset<KT>::~Multiset() {
  if (size_ > 0 && tree_.getRoot()) {
    size_ = 0;
    tree_.destroy(tree_.getRoot());
  }
}

// Getter size_
template <typename KT>
typename Multiset<KT>::size_type Multiset<KT>::size() {
  return size_;
}

// Getter maxsize
template <typename KT>
typename Multiset<KT>::size_type Multiset<KT>::max_size() {
  return ((std::numeric_limits<size_type>::max() / 2) - sizeof(BTree<KT>) -
          sizeof(Node<KT>)) /
         sizeof(Node<KT>);
}

template <typename KT>
typename Multiset<KT>::reference Multiset<KT>::operator=(
    std::initializer_list<value_type> const &items) {
  swap(Multiset<KT>(items));
  return *this;
}

template <typename KT>
typename Multiset<KT>::reference Multiset<KT>::operator=(const Multiset &s) {
  if (this == &s) return *this;
  swap(Multiset<KT>(s));
  return *this;
}

template <typename KT>
typename Multiset<KT>::reference Multiset<KT>::operator=(Multiset &&s) {
  if (this == &s) return *this;
  swap(s);
  return *this;
}

// Method to find iterator to specific node
template <typename KT>
typename Multiset<KT>::iterator Multiset<KT>::find(const KT &key) {
  return tree_.searchNode(key);
}

// Returns iterator to begin
template <typename KT>
typename Multiset<KT>::iterator Multiset<KT>::begin() {
  return tree_.begin();
}

// Returns iterator after end node
template <typename KT>
typename Multiset<KT>::iterator Multiset<KT>::end() {
  return tree_.end();
}

// Method to check, is Multiset empty
template <typename KT>
bool Multiset<KT>::empty() {
  return size_ == 0;
}

// Destroy the all Multiset
template <typename KT>
void Multiset<KT>::clear() {
  tree_.destroy(tree_.getRoot());
  size_ = 0;
}

// Insert a new value into multiset
template <typename KT>
std::pair<typename Multiset<KT>::iterator, bool> Multiset<KT>::insert(
    const KT &value) {
  auto it = tree_.insert(value, value);
  size_++;
  return std::pair<iterator, bool>{it, true};
}

// Delete one node by getting iterator
template <typename KT>
void Multiset<KT>::erase(typename Multiset<KT>::iterator pos) {
  auto node = pos.getNode();
  tree_.removeNode(node, node->key);
  size_--;
}

// Swap two multisets
template <typename KT>
void Multiset<KT>::swap(Multiset &other) {
  using std::swap;
  swap(size_, other.size_);
  swap(tree_, other.tree_);
}

// Merge two multisets
template <typename KT>
void Multiset<KT>::merge(Multiset &other) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    insert(it.getNode()->key);
  }
}

// Check is key containing in Multiset
template <typename KT>
bool Multiset<KT>::contains(const KT &key) {
  return (tree_.search(key) != nullptr);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_