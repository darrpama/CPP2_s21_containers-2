#ifndef CPP2_S21_CONTAINERS_SRC_MAP_NODE_H_
#define CPP2_S21_CONTAINERS_SRC_MAP_NODE_H_

#include <utility>

namespace s21 {

template <typename KT, typename VT = KT>
class Node {
 public:
  KT key;
  VT value;
  Node<KT, VT>* left;
  Node<KT, VT>* right;
  Node<KT, VT>* parent;

  explicit Node(KT& key)
      : key{key}, value{}, left{nullptr}, right{nullptr}, parent{nullptr} {}

  Node(KT& key, VT& value, Node<KT, VT>& parent)
      : key{key},
        value{value},
        left{nullptr},
        right{nullptr},
        parent(&parent) {}

  Node()
      : key(KT{}),
        value(VT{}),
        left{nullptr},
        right{nullptr},
        parent{nullptr} {}

  bool hasNoChild() {
    if (left != nullptr || right != nullptr) {
      return false;
    }
    return true;
  }

  bool hasOneChild() {
    if (left == nullptr && right != nullptr) {
      return true;
    }
    if (left != nullptr && right == nullptr) {
      return true;
    }
    return false;
  }

  bool hasTwoChild() {
    if (left != nullptr && right != nullptr) {
      return true;
    }
    return false;
  }

  // Swaps the contents
  void swap(Node<KT, VT>& other) {
    using std::swap;
    swap(key, other.key);
    swap(value, other.value);
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_MAP_NODE_H_
