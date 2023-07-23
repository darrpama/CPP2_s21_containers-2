#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"

template <class T>
bool comparisonLists(s21::List<T> &s21_List, std::list<T> &STL_List);
template <class T>
bool comparisonLists(s21::List<T> &s21_List, s21::List<T> &STL_List);

TEST(List, Constructor_default) {
  s21::List<int> s21_test;
  std::list<int> std_test;
  EXPECT_EQ(s21_test.size(), std_test.size());
}

TEST(List, Constructor_param) {
  s21::List<int> s21_test(4);
  std::list<int> std_test(4);
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
  EXPECT_EQ(s21_test.empty(), std_test.empty());
}

TEST(List, Constructor_init) {
  s21::List<char> s21_test{'a', 'b', 'c', 'd'};
  std::list<char> std_test{'a', 'b', 'c', 'd'};
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Constructor_copy) {
  s21::List<char> s21_test{'a', 'b', 'c', 'd'};
  std::list<char> std_test{'a', 'b', 'c', 'd'};
  s21::List<char> s21_test_1(s21_test);
  std::list<char> std_test_1(std_test);
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Constructor_move) {
  s21::List<int> s21_test{1, 3, 4, 5, 6, 7};
  std::list<int> std_test{1, 3, 4, 5, 6, 7};
  s21::List<int> s21_test_1(std::move(s21_test));
  std::list<int> std_test_1(std::move(std_test));
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Operator_copy_assignment) {
  s21::List<int> s21_test_0{1, 3, 4, 5, 6, 7};
  s21::List<int> s21_test(s21_test_0);
  s21::List<int> s21_test_1 = s21_test;
  std::list<int> std_test_0{1, 3, 4, 5, 6, 7};
  std::list<int> std_test(std_test_0);
  std::list<int> std_test_1 = std_test;
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Operator_move_assignment) {
  s21::List<int> s21_test{1, 3, 4, 5, 6, 7};
  s21::List<int> s21_test_1 = std::move(s21_test);
  std::list<int> std_test{1, 3, 4, 5, 6, 7};
  std::list<int> std_test_1 = std::move(std_test);
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Method_front) {
  s21::List<int> s21_test{1, 3, 4, 5, 6, 7};
  std::list<int> std_test{1, 3, 4, 5, 6, 7};
  EXPECT_EQ(s21_test.front(), std_test.front());
}

TEST(List, Method_back) {
  s21::List<std::string> s21_test{"aboba", "asdf", "qwerty"};
  std::list<std::string> std_test{"aboba", "asdf", "qwerty"};
  EXPECT_EQ(s21_test.back(), std_test.back());
}

TEST(List, Method_empty) {
  s21::List<std::string> s21_test{"aboba"};
  s21::List<std::string> s21_test_e;
  std::list<std::string> std_test{"aboba"};
  std::list<std::string> std_test_e;
  EXPECT_EQ(s21_test.empty(), std_test.empty());
  EXPECT_EQ(s21_test_e.empty(), std_test_e.empty());
  s21_test.pop_front();
  std_test.pop_front();
  EXPECT_EQ(s21_test.empty(), std_test.empty());
}

TEST(List, Method_size) {
  s21::List<std::string> s21_test{"aboba", "asdf", "qwerty"};
  std::list<std::string> std_test{"aboba", "asdf", "qwerty"};
  s21_test.pop_back();
  std_test.pop_back();
  EXPECT_EQ(s21_test.empty(), std_test.empty());
}

TEST(List, Method_max_size) {
  s21::List<int> s21_test;
  std::list<int> std_test;
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
}

TEST(List, Method_clear) {
  s21::List<std::string> s21_test{"aboba", "asdf", "qwerty"};
  std::list<std::string> std_test{"aboba", "asdf", "qwerty"};
  s21_test.clear();
  std_test.clear();
  EXPECT_EQ(s21_test.empty(), std_test.empty());
}

TEST(List, Method_insert) {
  s21::List<std::string> s21_test{"aboba", "asdf", "qwerty"};
  std::list<std::string> std_test{"aboba", "asdf", "qwerty"};
  s21_test.insert(s21_test.end(), "true");
  std_test.insert(std_test.end(), "true");
  s21_test.insert(s21_test.begin(), "false");
  std_test.insert(std_test.begin(), "false");
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_erase) {
  s21::List<std::string> s21_test{"aboba", "asdf", "qwerty"};
  std::list<std::string> std_test{"aboba", "asdf", "qwerty"};
  s21_test.erase(s21_test.begin());
  s21_test.erase(--s21_test.end());
  std_test.erase(std_test.begin());
  std_test.erase(--std_test.end());
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_push_back) {
  s21::List<std::string> s21_test;
  std::list<std::string> std_test;
  s21_test.push_back("aboba");
  s21_test.push_back("asdf");
  std_test.push_back("aboba");
  std_test.push_back("asdf");
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_pop_back) {
  s21::List<std::string> s21_test{"aboba", "asdf"};
  std::list<std::string> std_test{"aboba", "asdf"};
  s21_test.pop_back();
  std_test.pop_back();
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
  s21_test.pop_back();
  std_test.pop_back();
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_push_front) {
  s21::List<std::string> s21_test;
  std::list<std::string> std_test;
  s21_test.push_front("aboba");
  s21_test.push_front("asdf");
  std_test.push_front("aboba");
  std_test.push_front("asdf");
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_pop_front) {
  s21::List<std::string> s21_test{"aboba", "asdf"};
  std::list<std::string> std_test{"aboba", "asdf"};
  s21_test.pop_front();
  std_test.pop_front();
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
  s21_test.pop_front();
  std_test.pop_front();
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_swap) {
  s21::List<std::string> s21_test{"aboba", "asdf"};
  s21::List<std::string> s21_test_1{"5432", "2345"};
  std::list<std::string> std_test{"aboba", "asdf"};
  std::list<std::string> std_test_1{"5432", "2345"};
  s21_test.swap(s21_test_1);
  std_test.swap(std_test_1);
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Method_merge) {
  s21::List<int> s21_test{1, 9, -1, 5, 6, 7};
  s21::List<int> s21_test_1{4, 3, 2, -50, -49, -48};
  std::list<int> std_test{1, 9, -1, 5, 6, 7};
  std::list<int> std_test_1{4, 3, 2, -50, -49, -48};
  s21_test.merge(s21_test_1);
  std_test.merge(std_test_1);
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_merge_empty) {
  s21::List<int> s21_test;
  s21::List<int> s21_test_1{4, 3, 2, -50, -49, -48};
  std::list<int> std_test;
  std::list<int> std_test_1{4, 3, 2, -50, -49, -48};
  s21_test.merge(s21_test_1);
  std_test.merge(std_test_1);
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
}

TEST(List, Method_splice) {
  s21::List<int> s21_test{1, 9, -1, 5, 6, 7};
  s21::List<int> s21_test_1{4, 3, 2, -50, -49, -48};
  std::list<int> std_test{1, 9, -1, 5, 6, 7};
  std::list<int> std_test_1{4, 3, 2, -50, -49, -48};
  s21_test.splice(++s21_test.begin(), s21_test_1);
  std_test.splice(++std_test.begin(), std_test_1);
}

TEST(List, Method_reverse) {
  s21::List<int> s21_test{1, 9, -1, 5, 6, 7, 4, 6, -11, 33};
  s21::List<char> s21_test_1;
  std::list<int> std_test{1, 9, -1, 5, 6, 7, 4, 6, -11, 33};
  std::list<char> std_test_1;
  s21_test.reverse();
  s21_test_1.reverse();
  std_test.reverse();
  std_test_1.reverse();
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Method_unique) {
  s21::List<int> s21_test{1, 3, 3, 3, 4, 3, 5, 6, 6, 6};
  s21::List<char> s21_test_1;
  std::list<int> std_test{1, 3, 3, 3, 4, 3, 5, 6, 6, 6};
  std::list<char> std_test_1;
  s21_test.unique();
  s21_test_1.unique();
  std_test.unique();
  std_test_1.unique();
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Method_sort) {
  s21::List<int> s21_test{1, 9, -1, 5, 6, 7, 4, 6, -11, 33};
  s21::List<char> s21_test_1{'y', 'a', 'c', 'b', 66, 44};
  std::list<int> std_test{1, 9, -1, 5, 6, 7, 4, 6, -11, 33};
  std::list<char> std_test_1{'y', 'a', 'c', 'b', 66, 44};
  s21_test.sort();
  s21_test_1.sort();
  std_test.sort();
  std_test_1.sort();
  EXPECT_TRUE(comparisonLists(s21_test, std_test));
  EXPECT_TRUE(comparisonLists(s21_test_1, std_test_1));
}

TEST(List, Iterator) {
  s21::List<int> s21_test{1, 3, 4, 5, 6, 7};
  std::list<int> std_test{1, 3, 4, 5, 6, 7};
  auto s21_it = s21_test.begin();
  auto std_it = std_test.begin();
  ++s21_it;
  ++std_it;
  s21_it--;
  std_it--;
  s21_it++;
  std_it++;
  --std_it;
  --s21_it;
  EXPECT_EQ(*s21_it, *std_it);
}

TEST(List, ConstIterator) {
  const s21::List<int> s21_test{1, 3, 4, 5, 6, 7};
  const std::list<int> std_test{1, 3, 4, 5, 6, 7};
  auto s21_it = s21_test.begin();
  auto std_it = std_test.begin();
  ++s21_it;
  ++std_it;
  s21_it--;
  std_it--;
  s21_it++;
  std_it++;
  --std_it;
  --s21_it;
  EXPECT_EQ(*s21_it, *std_it);
}

TEST(List, Method_insert_many) {
  s21::List<int> s21_test{1, 9, -1, 5};
  s21::List<int> s21_test_1{1, 9, -1, 5};
  auto iter = ++s21_test.begin();
  auto iter1 = ++s21_test_1.begin();
  s21_test.insert_many(iter, 7, 7, 7);
  for (auto i = 0; i < 3; i++) s21_test_1.insert(iter1, 7);
  EXPECT_TRUE(comparisonLists(s21_test, s21_test_1));
}

TEST(List, Method_insert_many_back) {
  s21::List<int> s21_test{1, 9, -1, 5};
  s21::List<int> s21_test_1{1, 9, -1, 5};
  s21_test.insert_many_back(7, 7, 7);
  for (auto i = 0; i < 3; i++) s21_test_1.push_back(7);
  EXPECT_TRUE(comparisonLists(s21_test, s21_test_1));
}

TEST(List, Method_insert_many_front) {
  s21::List<int> s21_test{1, 9, -1, 5};
  s21::List<int> s21_test_1{1, 9, -1, 5};
  s21_test.insert_many_front(7, 7, 7);
  for (auto i = 0; i < 3; i++) s21_test_1.push_front(7);
  EXPECT_TRUE(comparisonLists(s21_test, s21_test_1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <class T>
bool comparisonLists(s21::List<T> &s21_List, std::list<T> &STL_List) {
  if (s21_List.size() != STL_List.size() ||
      s21_List.empty() != STL_List.empty())
    return false;
  auto it1 = s21_List.begin();
  auto it2 = STL_List.begin();
  for (size_t i = 0; i < s21_List.size(); ++i, ++it1, ++it2)
    if (*it1 != *it2) return false;
  return true;
}

template <class T>
bool comparisonLists(s21::List<T> &s21_List, s21::List<T> &STL_List) {
  if (s21_List.size() != STL_List.size() ||
      s21_List.empty() != STL_List.empty())
    return false;
  auto it1 = s21_List.begin();
  auto it2 = STL_List.begin();
  for (size_t i = 0; i < s21_List.size(); ++i, ++it1, ++it2)
    if (*it1 != *it2) return false;
  return true;
}
