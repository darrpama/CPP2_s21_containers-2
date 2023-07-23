#ifndef CPP2_S21_CONTAINERS_SRC_MAP_BINARY_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_MAP_BINARY_TREE_H_

#include <stack>
#include <string>
#include <utility>

#include "Node.h"

namespace s21 {

template <typename KT, typename VT = KT>
class BTree {
 public:
  class iterator;
  class const_iterator;

  using node_type = Node<KT, VT>;

  BTree();
  iterator insert(KT, VT);
  node_type* getRoot();
  VT* search(const KT&);
  iterator searchNode(const KT&);
  void removeNode(node_type*, KT);
  void destroy(node_type*);
  iterator begin() const;
  iterator end() const;

 private:
  node_type* root;

  void updateParent(node_type* node, node_type* successor);
  iterator insert(node_type*, KT, VT);
};

template <typename KT, typename VT>
BTree<KT, VT>::BTree() : root(nullptr) {}

template <typename KT, typename VT>
typename BTree<KT, VT>::iterator BTree<KT, VT>::insert(KT key, VT value) {
  return insert(root, key, value);
}

template <typename KT, typename VT>
typename BTree<KT, VT>::node_type* BTree<KT, VT>::getRoot() {
  return root;
}

template <typename KT, typename VT>
VT* BTree<KT, VT>::search(const KT& key) {
  node_type* current = root;
  while (current) {
    if (current->key == key) {
      return &current->value;
    }
    if (std::less<KT>{}(key, current->key)) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return nullptr;
}

template <typename KT, typename VT>
typename BTree<KT, VT>::iterator BTree<KT, VT>::searchNode(const KT& key) {
  node_type* current = root;
  while (current) {
    if (current->key == key) {
      return iterator(current);
    }
    if (std::less<KT>{}(key, current->key)) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return iterator(nullptr);
}

template <typename KT, typename VT>
void BTree<KT, VT>::removeNode(node_type* node, KT key) {
  if (node == nullptr) {
    return;
  }
  // Сase 1
  if (node->hasNoChild()) {
    if (node->key != key) {
      auto dNode = searchNode(key).getNode();
      node->swap(*dNode);
    }
    updateParent(node, nullptr);
    delete node;
    return;
  }
  // Сase 2
  if (node->hasOneChild()) {
    node_type* successor = (node->left != nullptr) ? node->left : node->right;
    removeNode(successor, key);
  }
  // Сase 3
  if (node->hasTwoChild()) {
    if (node->key > key) {
      removeNode(node->left, key);
    } else {
      removeNode(node->right, key);
    }
  }
}

template <typename KT, typename VT>
void BTree<KT, VT>::destroy(node_type* node) {
  if (!node) {
    return;
  }
  destroy(node->left);
  destroy(node->right);

  delete node;
}

template <typename KT, typename VT>
typename BTree<KT, VT>::iterator BTree<KT, VT>::begin() const {
  if (root == nullptr) {
    return iterator(root);
  }
  node_type* current = root;
  while (current->left) {
    current = current->left;
  }
  return iterator(current);
}

template <typename KT, typename VT>
typename BTree<KT, VT>::iterator BTree<KT, VT>::end() const {
  return iterator(nullptr);
}

template <typename KT, typename VT>
void BTree<KT, VT>::updateParent(node_type* node, node_type* successor) {
  (node->key == node->parent->left->key) ? node->parent->left = successor
                                         : node->parent->right = successor;
}

template <typename KT, typename VT>
typename BTree<KT, VT>::iterator BTree<KT, VT>::insert(node_type* node, KT key,
                                                       VT value) {
  if (root == nullptr) {
    root = new node_type(key, value, *node);
    return iterator(root);
  }
  if (std::less<KT>{}(key, node->key)) {  // <
    if (node->left == nullptr) {
      node->left = new node_type(key, value, *node);
      return iterator(node->left);
    } else {
      return insert(node->left, key, value);
    }
  } else {  // >=
    if (node->right == nullptr) {
      node->right = new node_type(key, value, *node);
      return iterator(node->right);
    } else {
      return insert(node->right, key, value);
    }
  }
}

// ITERATORS
template <typename KT, typename VT>
class BTree<KT, VT>::iterator {
 public:
  explicit iterator(Node<KT, VT>* node) : current(nullptr) {
    if (node) {
      current = node;
    }
  }

  iterator& operator++() {
    if (!current) {
      return *this;
    }
    if (current->right) {
      current = current->right;
      while (current->left) {
        current = current->left;
      }
      return *this;
    }
    Node<KT, VT>* prev = current;
    current = current->parent;
    while (current && current->right == prev) {
      prev = current;
      current = current->parent;
    }
    return *this;
  }

  VT& operator*() const { return current->value; }

  bool operator==(const iterator& other) const {
    return current == other.current;
  }

  bool operator!=(const iterator& other) const { return !(*this == other); }

  node_type* getNode() { return current; }
  KT& first() { return current->key; }
  VT& second() { return current->value; }

 private:
  node_type* current;
};

template <typename KT, typename VT>
class BTree<KT, VT>::const_iterator {
 public:
  explicit const_iterator(Node<KT, VT>* node) : current(nullptr) {
    if (node) {
      current = node;
    }
  }

  const_iterator& operator++() {
    if (!current) {
      return *this;
    }
    if (current->right) {
      current = current->right;
      while (current->left) {
        current = current->left;
      }
      return *this;
    }
    Node<KT, VT>* prev = current;
    current = current->parent;
    while (current && current->right == prev) {
      prev = current;
      current = current->parent;
    }
    return *this;
  }

  VT& operator*() const { return current->value; }

  bool operator==(const iterator& other) const {
    return current == other.current;
  }

  bool operator!=(const iterator& other) const { return !(*this == other); }

  node_type* getNode() { return current; }
  KT& first() { return current->key; }
  VT& second() { return current->value; }

 private:
  node_type* current;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_MAP_BINARY_TREE_H_
