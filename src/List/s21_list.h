#ifndef CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_

#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace s21 {

template <class T>
class List {
  struct Node;
  class ListIterator;
  class ListConstIterator;

 public:
  // Aliases declaration
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using node = Node;
  using node_ptr = node *;

  // List Member functions
  List();
  explicit List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();

  List &operator=(const List &l);
  List &operator=(List &&l);

  // List Element access
  const_reference front();
  const_reference back();

  // List Iterators
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  // List Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other) noexcept;
  void merge(List &other);
  void splice(const_iterator pos, List &other) noexcept;
  void reverse() noexcept;
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  // Variables
  node_ptr begin_;
  node_ptr end_;
  size_type size_;

  // Methods
  void initList();
  node_ptr createNode(const node_ptr a_prev, const node_ptr a_next,
                      const value_type a_data);
  void deallocate(bool mode);
  void destroyNode(node_ptr node);
  void pushFirstNode(const_reference value);
  iterator sortCheck(iterator current, const iterator &end);
  iterator insertSubList(const_iterator pos, iterator first, iterator last);
  node_ptr mergeSort(node_ptr first);
  node_ptr splitList(node_ptr first);
  node_ptr mergeNodes(node_ptr first, node_ptr second);
  void prevPointerRepair();
};

// Default constructor, creates empty List and "fake" node
template <class T>
List<T>::List() : begin_(nullptr), end_(new Node), size_(0) {
  initList();
}

// Parameterized constructor, creates the List of size n
template <class T>
List<T>::List(size_type n) : List() {
  for (size_type i = 0; i < n; ++i) push_back(value_type{});
}

// Initializer List constructor,
// creates List initizialized using std::initializer_list
template <class T>
List<T>::List(std::initializer_list<value_type> const &items) : List() {
  for (auto i = items.begin(); i < items.end(); ++i) push_back(*i);
}

// Copy constructor
template <class T>
List<T>::List(const List &l) : List() {
  for (auto i = l.begin(); i != l.end(); ++i) push_back(*i);
}

// Move constructor
template <class T>
List<T>::List(List &&l) : begin_(l.begin_), end_(l.end_), size_(l.size_) {
  l.begin_ = l.end_ = nullptr;
  l.size_ = 0;
}

// Destructor
template <class T>
List<T>::~List() {
  deallocate(true);
}

template <class T>
List<T> &List<T>::operator=(const List<T> &l) {
  if (&l == this) return *this;
  clear();
  for (auto i = l.begin(); i != l.end(); ++i) push_back(*i);
  return *this;
}

template <class T>
List<T> &List<T>::operator=(List<T> &&l) {
  if (&l == this) return *this;
  clear();
  begin_ = l.begin_;
  end_ = l.end_;
  size_ = l.size_;
  return *this;
}

// Returns a reference to the first element in the container
template <class T>
typename List<T>::const_reference List<T>::front() {
  if (begin_ == end_) throw std::out_of_range("List is empty");
  return *(begin_->data);
}

// Returns a reference to the last element in the container
template <class T>
typename List<T>::const_reference List<T>::back() {
  if (begin_ == end_) throw std::out_of_range("List is empty");
  return *(end_->prev->data);
}

// Returns an iterator to the beginning
template <class T>
typename List<T>::iterator List<T>::begin() noexcept {
  return iterator(end_->next);
}

// Returns a const iterator to the beginning
template <class T>
typename List<T>::const_iterator List<T>::begin() const noexcept {
  return const_iterator(end_->next);
}

// Returns an iterator to the end (next from the last element)
template <class T>
typename List<T>::iterator List<T>::end() noexcept {
  return iterator(end_);
}

// Returns a const iterator to the end (next from the last element)
template <class T>
typename List<T>::const_iterator List<T>::end() const noexcept {
  return const_iterator(end_);
}

// Checks if the container has no elements
template <class T>
bool List<T>::empty() const noexcept {
  return begin_ == end_;
}

// The number of elements in the container.
template <class T>
typename List<T>::size_type List<T>::size() const noexcept {
  return size_;
}

// Returns the maximum number of elements the container is able to
// hold due to system or library implementation limitations
template <class T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return std::numeric_limits<difference_type>::max() / (sizeof(node));
}

// Clears the contents
template <class T>
void List<T>::clear() {
  deallocate(false);
  initList();
}

// Inserts element into concrete pos and returns the iterator that
// points to the new element.
// Returns iterator that points to the new element
template <class T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  iterator ret_iter;
  if (pos == begin()) {
    push_front(value);
    ret_iter = begin();
  } else {
    node_ptr new_node = createNode(pos.node_->prev, pos.node_, value);
    pos.node_->prev->next = new_node;
    pos.node_->prev = new_node;
    ret_iter = iterator(new_node);
  }
  return ret_iter;
}

// Erases element at pos
template <class T>
void List<T>::erase(iterator pos) {
  if (!pos.node_->data) return;
  if (pos == begin()) {
    pop_front();
  } else if (pos != end()) {
    node_ptr temp = pos.node_->prev;
    temp->next = pos.node_->next;
    pos.node_->next->prev = temp;
    destroyNode(pos.node_);
  }
}

// Adds an element to the end
template <class T>
void List<T>::push_back(const_reference value) {
  if (end_ == begin_) {
    pushFirstNode(value);
  } else {
    node_ptr new_node = createNode(end_->prev, end_, value);
    end_->prev->next = new_node;
    end_->prev = new_node;
  }
}

// Removes the last element
template <class T>
void List<T>::pop_back() {
  if (!end_->prev->data) return;
  node_ptr tmp = end_->prev;
  tmp->prev->next = end_;
  end_->prev = tmp->prev;
  destroyNode(tmp);
  begin_ = end_->next;
}

// Adds an element to the head
template <class T>
void List<T>::push_front(const_reference value) {
  if (end_ == begin_) {
    pushFirstNode(value);
  } else {
    node_ptr new_node = createNode(end_, begin_, value);
    end_->next = new_node;
    begin_->prev = new_node;
    begin_ = new_node;
  }
}

// Removes the first element
template <class T>
void List<T>::pop_front() {
  if (!end_->prev->data) return;
  end_->next = begin_->next;
  begin_->next->prev = end_;
  destroyNode(begin_);
  begin_ = end_->next;
}

// Swaps the contents
template <class T>
void List<T>::swap(List &other) noexcept {
  std::swap(begin_, other.begin_);
  std::swap(end_, other.end_);
  std::swap(size_, other.size_);
}

// Merges two sorted lists into one
template <class T>
void List<T>::merge(List &other) {
  if (&other == this || !other.size_) return;
  if (!size_) {
    swap(other);
    return;
  }
  auto node_ths = begin();
  auto node_oth = other.begin();
  while (node_oth != other.end()) {
    if (*node_ths > *node_oth || node_ths == end()) {
      iterator last_oth = sortCheck(node_oth, other.end());
      node_oth = insertSubList(node_ths, node_oth, last_oth);
    } else {
      ++node_ths;
    }
  }
  size_ += other.size_;
  other.initList();
}

// Transfers elements from one List to another.
template <class T>
void List<T>::splice(const_iterator pos, List &other) noexcept {
  if (&other == this || !other.size_) return;
  auto end = other.end();
  --end;
  insertSubList(pos, other.begin(), end);
  size_ += other.size_;
  other.initList();
}

// Reverses the order of the elements in the container.
template <class T>
void List<T>::reverse() noexcept {
  if (!size_) return;
  auto it = begin();
  for (int sz = size_; sz >= 0; --sz) {
    iterator temp = it;
    ++it;
    std::swap(temp.node_->next, temp.node_->prev);
  }
  begin_ = end_->next;
}

// Removes all consecutive duplicate elements from the container
template <class T>
void List<T>::unique() {
  auto i = begin(), temp = i;
  while (i != --end()) {
    if (*i == *(++i)) erase(temp);
    temp = i;
  }
}

// Merge Sort algorithm based onion brand principle
template <class T>
void List<T>::sort() {
  if (!size_ || size_ == 1) return;
  begin_ = mergeSort(begin().node_);
  prevPointerRepair();
}

// Inserts new elements into the container directly before pos.
// Returns iterator for last inserted element
template <class T>
template <class... Args>
typename List<T>::iterator List<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  auto iter = begin();
  // (); - lambda expression
  // [&] - type of capture (by reference)
  // {}  - body of lambda expression
  // ()  - declares function parameters
  // ... - template parameter pack expansion operator
  ([&] { iter = insert(pos, std::forward<T>(args)); }(), ...);
  return iter;
}

// Appends new elements to the end of the container
template <class T>
template <class... Args>
void List<T>::insert_many_back(Args &&...args) {
  ([&] { push_back(std::forward<T>(args)); }(), ...);
}

// Appends new elements to the top of the container
template <class T>
template <class... Args>
void List<T>::insert_many_front(Args &&...args) {
  ([&] { push_front(std::forward<T>(args)); }(), ...);
}

// Private

// Create connection of empty List nodes from end_ to begin_
template <class T>
void List<T>::initList() {
  end_->next = end_;
  end_->prev = end_;
  begin_ = end_;
  size_ = 0;
}

// Creates new node
template <class T>
typename List<T>::node_ptr List<T>::createNode(const node_ptr a_prev,
                                               const node_ptr a_next,
                                               const value_type a_data) {
  node_ptr new_node = new node;
  new_node->prev = a_prev;
  new_node->next = a_next;
  new_node->data = new value_type;
  *new_node->data = a_data;
  ++size_;
  return new_node;
}

// Deallocator
// mode false - deallocate all non fake nodes,
//      true - fully deallocation
template <class T>
void List<T>::deallocate(bool mode) {
  if (!end_) return;
  for (auto i = ++begin(); i != begin(); ++i) destroyNode(i.node_->prev);
  if (mode) delete end_;
}

// Deallocator for separate node
template <class T>
void List<T>::destroyNode(node_ptr node) {
  delete node->data;
  delete node;
  --size_;
}

// Using when pushing node in empty List
template <class T>
void List<T>::pushFirstNode(const_reference value) {
  node_ptr new_node = createNode(end_, end_, value);
  end_->prev = end_->next = new_node;
  begin_ = new_node;
}

// Checks for descending sequence.
// Return last desc sequence iterator
template <class T>
typename List<T>::iterator List<T>::sortCheck(iterator current,
                                              const iterator &end) {
  auto start_pos = current;
  ++current;
  while (current.node_->next != end.node_ && *start_pos > *(current)) {
    ++current;
  }
  return current;
}

// Inserts sublist between given iterators inclusive into main List
// before given position
// Returns next iterator after last param
template <class T>
typename List<T>::iterator List<T>::insertSubList(const_iterator pos,
                                                  iterator first,
                                                  iterator last) {
  iterator next = last;
  ++next;
  pos.node_->prev->next = first.node_;
  first.node_->prev = pos.node_->prev;
  pos.node_->prev = last.node_;
  last.node_->next = pos.node_;
  if (pos == begin()) begin_ = first.node_;
  return next;
}

// Main sort recursive function (via mergeSort method)
// Returns sorted single-linked List
template <class T>
typename List<T>::node_ptr List<T>::mergeSort(node_ptr first) {
  if (first->next == end_ || first == end_) return first;
  node_ptr second = splitList(first);
  first = mergeSort(first);
  second = mergeSort(second);
  return mergeNodes(first, second);
}

// Divides List to two separate List (first = N / 2, sec = N / 2 + N % 2)
// Returns first node of the second List
template <class T>
typename List<T>::node_ptr List<T>::splitList(node_ptr first) {
  node_ptr second = first;
  while (first->next != end_ && first->next->next != end_) {
    first = first->next->next;
    second = second->next;
  }
  node_ptr sec_begin = second->next;
  second->next = end_;
  return sec_begin;
}

// Recursively merges sublists to single-linked asc ordered List
// Returns merged or existing List
template <class T>
typename List<T>::node_ptr List<T>::mergeNodes(node_ptr first,
                                               node_ptr second) {
  if (first == end_) return second;
  if (second == end_) return first;
  if (*first->data < *second->data) {
    first->next = mergeNodes(first->next, second);
    return first;
  } else {
    second->next = mergeNodes(second->next, first);
    return second;
  }
}

// Repairs prev pointer of the List (makes it double-linked)
template <class T>
void List<T>::prevPointerRepair() {
  for (auto iter = iterator(begin_); iter != end(); ++iter) {
    iter.node_->next->prev = iter.node_;
  }
  end_->next = begin_;
}

// Struct for DL list
template <class T>
struct List<T>::Node {
  Node *prev;
  Node *next;
  T *data;
};

// Iterator
template <class T>
class List<T>::ListIterator {
  friend class List<T>;

 public:
  using value_type = T;
  using reference = const value_type &;
  using node_ptr = Node *;
  ListIterator() : node_(nullptr){};
  explicit ListIterator(node_ptr ptr) : node_(ptr){};
  ListIterator(const ListIterator &other) : node_(other.node_) {}
  ListIterator(const ListConstIterator &other) : node_(other.getNode()) {}
  ListIterator(ListIterator &&other) noexcept : node_(other.node_) {}
  ~ListIterator() { node_ = nullptr; }

  ListIterator &operator=(const ListIterator &other) {
    node_ = other.node_;
    return *this;
  }

  node_ptr getNode() const { return node_; }

  // Gets the element pointed to by the iterator
  reference operator*() const { return *(node_->data); }

  // Two iterators are not equal if they point to different elements
  bool operator!=(const ListIterator &other) { return node_ != other.node_; }

  // Two iterators are equal if they point to the same element
  bool operator==(const ListIterator &other) { return node_ == other.node_; }

  // Moves the iterator forward to the next element
  ListIterator operator++() {
    node_ = node_->next;
    return *this;
  }

  // Original value
  ListIterator operator++(int) {
    ListIterator tmp = *this;
    node_ = node_->next;
    return tmp;
  }

  // Moves the iterator backwards to the previous element
  ListIterator operator--() {
    node_ = node_->prev;
    return *this;
  }

  // Returns original value
  ListIterator operator--(int) {
    ListIterator tmp = *this;
    node_ = node_->prev;
    return tmp;
  }

 private:
  node_ptr node_;
};

// Const iterator
template <class T>
class List<T>::ListConstIterator {
  friend class List<T>;

 public:
  using value_type = T;
  using reference = const value_type &;
  using node_ptr = Node *;

  ListConstIterator() : node_(nullptr){};
  explicit ListConstIterator(node_ptr ptr) : node_(ptr){};
  ListConstIterator(const ListConstIterator &other) : node_(other.node_) {}
  ListConstIterator(const ListIterator &other) : node_(other.getNode()) {}
  ListConstIterator(ListConstIterator &&other) noexcept : node_(other.node_) {
    other.node_ = nullptr;
  }

  ~ListConstIterator() { node_ = nullptr; }

  ListConstIterator &operator=(const ListConstIterator &other) {
    node_ = other.node_;
    return *this;
  }
  ListConstIterator &operator=(ListConstIterator &&other) noexcept {
    node_ = other.node_;
    return *this;
  }
  reference operator*() const { return *(node_->data); }
  bool operator!=(const ListConstIterator &other) {
    return node_ != other.node_;
  }
  bool operator==(const ListConstIterator &other) {
    return node_ == other.node_;
  }
  ListConstIterator operator++() {
    node_ = node_->next;
    return *this;
  }
  ListConstIterator operator++(int) {
    ListConstIterator tmp = *this;
    node_ = node_->next;
    return tmp;
  }
  ListConstIterator operator--() {
    node_ = node_->prev;
    return *this;
  }
  ListConstIterator operator--(int) {
    ListConstIterator tmp = *this;
    node_ = node_->prev;
    return tmp;
  }
  node_ptr getNode() const { return node_; }

 private:
  node_ptr node_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_