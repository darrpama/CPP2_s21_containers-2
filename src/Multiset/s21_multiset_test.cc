#include "s21_multiset.h"

#include <gtest/gtest.h>

#include <cstring>
#include <set>

template <class T>
bool comparisonMultiset(s21::Multiset<T> &s21_multiset,
                        s21::Multiset<T> &s21_multiset2);
template <class T>
bool comparisonMultiset(s21::Multiset<T> &s21_multiset,
                        std::multiset<T> &stl_multiset);

// Constructors
TEST(Multiset, base_constructor_int) {
  s21::Multiset<int> multiset;
  std::multiset<int> stdmultiset;
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_TRUE(multiset.size() == 0);
  ASSERT_TRUE(multiset.begin().getNode() == nullptr);
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
}

TEST(Multiset, base_constructor_char) {
  s21::Multiset<char> multiset;
  std::multiset<char> stdmultiset;
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_TRUE(multiset.size() == 0);
  ASSERT_TRUE(multiset.begin().getNode() == nullptr);
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
}

TEST(Multiset, initializer_list_one_element_char) {
  s21::Multiset<char> multiset{'a'};
  std::multiset<char> stdmultiset{'a'};
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_TRUE(multiset.size() == 1);
  ASSERT_TRUE(multiset.begin().getNode()->key == 'a');
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
  std::multiset<int> multiset2{1};
}

TEST(Multiset, initializer_list_one_element_double) {
  s21::Multiset<double> multiset{1.0};
  std::multiset<double> stdmultiset{1.0};
  std::multiset<double> std_another_multiset{2.0};
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_FALSE(comparisonMultiset(multiset, std_another_multiset));
  ASSERT_TRUE(multiset.size() == 1);
  ASSERT_TRUE(multiset.begin().getNode()->key == 1.0);
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
}

TEST(Multiset, initializer_list_std_pair) {
  s21::Multiset<std::pair<int, int>> multiset{std::make_pair(1, 2)};
  std::multiset<std::pair<int, int>> stdmultiset{std::make_pair(1, 2)};
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_TRUE(multiset.size() == 1);
  ASSERT_TRUE(multiset.begin().getNode()->key.first == 1);
  ASSERT_TRUE(multiset.begin().getNode()->key.second == 2);
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
}

TEST(Multiset, initializer_list_int) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  std::multiset<int> stdmultiset{1, 2, 3, 4};
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_TRUE(multiset.size() == 4);
  ASSERT_TRUE(multiset.begin().getNode()->key == 1);
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
}

TEST(Multiset, initializer_list_char) {
  s21::Multiset<char> multiset{'a', 'b', 'c', 'd'};
  std::multiset<char> stdmultiset{'a', 'b', 'c', 'd'};
  comparisonMultiset(multiset, stdmultiset);
  ASSERT_TRUE(multiset.size() == 4);
  ASSERT_TRUE(multiset.begin().getNode()->key == 'a');
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
}

TEST(Multiset, copy_constructor) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  s21::Multiset<int> copymultiSet(multiset);
  ASSERT_TRUE(comparisonMultiset(multiset, copymultiSet));
}

TEST(Multiset, move_constructor) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  s21::Multiset<int> copymultiSet(multiset);
  s21::Multiset<int> movemultiSet(std::move(multiset));
  ASSERT_TRUE(!comparisonMultiset(multiset, movemultiSet));
  ASSERT_TRUE(comparisonMultiset(movemultiSet, copymultiSet));
}

TEST(Multiset, move_operator) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  s21::Multiset<int> copymultiSet(multiset);
  s21::Multiset<int> movemultiSet = std::move(multiset);
  ASSERT_TRUE(!comparisonMultiset(multiset, movemultiSet));
  ASSERT_TRUE(comparisonMultiset(movemultiSet, copymultiSet));
}

TEST(Multiset, begin) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  std::multiset<int> stdmultiset{1, 2, 3, 4};
  ASSERT_TRUE(*multiset.begin() == *stdmultiset.begin());
  ASSERT_TRUE(multiset.begin().getNode()->key == 1);
}

TEST(Multiset, end) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  std::multiset<int> stdmultiset{1, 2, 3, 4};
  ASSERT_TRUE(multiset.end().getNode() == nullptr);
}

TEST(Multiset, empty) {
  s21::Multiset<int> multiset;
  std::multiset<int> stdmultiset;
  ASSERT_TRUE(multiset.empty() == stdmultiset.empty());
  s21::Multiset<int> multiset2{5};
  s21::Multiset<int> stdmultiset2{5};
  ASSERT_TRUE(multiset2.empty() == stdmultiset2.empty());
}

TEST(Multiset, max_size) {
  s21::Multiset<int> multiset;
  std::multiset<int> stdmultiset;
  ASSERT_TRUE(multiset.max_size() > 0);
  ASSERT_TRUE(multiset.max_size() == 288230376151711742);
}

// Multiset
TEST(Multiset, clear) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  multiset.clear();
  std::multiset<int> stdmultiset{1, 2, 3, 4};
  stdmultiset.clear();
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_TRUE(multiset.size() == 0);
}

TEST(Multiset, insert_pair) {
  s21::Multiset<std::pair<int, int>> multiset;
  multiset.insert(std::make_pair(3, 10));
  ASSERT_TRUE(multiset.contains(std::make_pair(3, 10)) == true);
}

TEST(Multiset, insert_key_value) {
  s21::Multiset<char> multiset;
  multiset.insert('b');
  multiset.insert('a');
  std::multiset<char> stdmultiset;
  stdmultiset.insert('a');
  stdmultiset.insert('b');
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
  ASSERT_TRUE(multiset.contains('a') == true);
  ASSERT_TRUE(multiset.contains('b') == true);
}

TEST(Multiset, insert_key_value_int) {
  s21::Multiset<int> multiset;
  multiset.insert(1);
  multiset.insert(2);
  std::multiset<int> stdmultiset;
  stdmultiset.insert(1);
  stdmultiset.insert(2);
  ASSERT_TRUE(comparisonMultiset(multiset, stdmultiset));
}

TEST(Multiset, erase_no_child) {
  s21::Multiset<int> multiset;
  multiset.insert(7);
  multiset.insert(3);
  multiset.erase(multiset.find(3));
  ASSERT_TRUE(multiset.size() == 1);
  ASSERT_FALSE(multiset.contains(3));
}

TEST(Multiset, erase_one_child) {
  s21::Multiset<int> multiset;
  multiset.insert(7);
  multiset.insert(3);
  multiset.insert(8);
  multiset.insert(2);
  multiset.erase(multiset.find(3));
  ASSERT_TRUE(multiset.size() == 3);
  ASSERT_TRUE(multiset.contains(3) == false);
  ASSERT_TRUE(multiset.find(7).getNode()->left->key == 2);
}

TEST(Multiset, erase_two_child) {
  s21::Multiset<int> multiset;
  multiset.insert(7);
  multiset.insert(3);
  multiset.insert(8);
  multiset.insert(2);
  multiset.insert(4);
  multiset.erase(multiset.find(3));
  ASSERT_TRUE(multiset.size() == 4);
  ASSERT_TRUE(multiset.contains(3) == false);
}

TEST(Multiset, erase_two_child_2) {
  s21::Multiset<int> multiset;
  multiset.insert(8);
  multiset.insert(4);
  multiset.insert(11);
  multiset.insert(2);
  multiset.insert(6);
  multiset.insert(9);
  multiset.insert(12);
  multiset.insert(1);
  multiset.insert(3);
  multiset.insert(5);
  multiset.insert(7);
  multiset.insert(10);
  multiset.erase(multiset.find(4));
  ASSERT_TRUE(multiset.size() == 11);
  ASSERT_TRUE(multiset.contains(4) == false);
}

TEST(Multiset, merge) {
  s21::Multiset<int> multiset{8, 4, 11};
  s21::Multiset<int> multiset1{1, 10, 11};
  multiset.merge(multiset1);
  ASSERT_TRUE(multiset.size() == 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <class T>
bool comparisonMultiset(s21::Multiset<T> &s21_multiset,
                        std::multiset<T> &stl_multiset) {
  if (s21_multiset.empty() == true || stl_multiset.empty() == true) {
    return true;
  }
  if (s21_multiset.size() != stl_multiset.size()) {
    return false;
  }
  auto it1 = s21_multiset.begin();
  auto it2 = stl_multiset.begin();
  for (size_t size = 0; size < s21_multiset.size(); ++size, ++it1, ++it2) {
    if (*it1 != *it2) {
      return false;
    }
  }
  return true;
}

template <class T>
bool comparisonMultiset(s21::Multiset<T> &s21_multiset,
                        s21::Multiset<T> &s21_multiset2) {
  if (s21_multiset.size() != s21_multiset2.size() ||
      s21_multiset.empty() != s21_multiset2.empty()) {
    return false;
  }
  auto it1 = s21_multiset.begin();
  auto it2 = s21_multiset2.begin();
  for (size_t size = 0; size < s21_multiset.size(); ++size, ++it1, ++it2) {
    if (*it1 != *it2) return false;
  }
  return true;
}