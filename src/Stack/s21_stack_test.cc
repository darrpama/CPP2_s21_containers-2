#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

template <class T>
bool comparisonStacks(s21::Stack<T> &s21_Stack, std::stack<T> &STL_Stack);
template <class T>
bool comparisonStacks(s21::Stack<T> &s21_Stack, s21::Stack<T> &STL_Stack);

TEST(Stack, Constructor_default) {
  s21::Stack<int> s21_test;
  std::stack<int> std_test;
  EXPECT_EQ(s21_test.size(), std_test.size());
}

TEST(Stack, Constructor_init) {
  s21::Stack<char> s21_test{'a', 'b', 'c', 'd'};
  std::stack<char> std_test;
  std_test.push('a');
  std_test.push('b');
  std_test.push('c');
  std_test.push('d');
  EXPECT_TRUE(comparisonStacks(s21_test, std_test));
}

TEST(Stack, Constructor_copy) {
  s21::Stack<char> s21_test{'a', 'b', 'c', 'd'};
  std::stack<char> std_test;
  std_test.push('a');
  std_test.push('b');
  std_test.push('c');
  std_test.push('d');
  s21::Stack<char> s21_test_1(s21_test);
  std::stack<char> std_test_1(std_test);
  EXPECT_TRUE(comparisonStacks(s21_test_1, std_test_1));
}

TEST(Stack, Constructor_move) {
  s21::Stack<char> s21_test{'a', 'b', 'c', 'd'};
  std::stack<char> std_test;
  std_test.push('a');
  std_test.push('b');
  std_test.push('c');
  std_test.push('d');
  s21::Stack<char> s21_test_1(std::move(s21_test));
  std::stack<char> std_test_1(std::move(std_test));
  EXPECT_TRUE(comparisonStacks(s21_test_1, std_test_1));
}

TEST(Stack, Operator_copy_assignment) {
  s21::Stack<int> s21_test_0{1, 3, 4, 5, 6, 7};
  s21::Stack<int> s21_test(s21_test_0);
  s21::Stack<int> s21_test_1 = s21_test;
  std::stack<int> std_test_0;
  std_test_0.push(1);
  std_test_0.push(3);
  std_test_0.push(4);
  std_test_0.push(5);
  std_test_0.push(6);
  std_test_0.push(7);
  std::stack<int> std_test(std_test_0);
  std::stack<int> std_test_1 = std_test;
  EXPECT_TRUE(comparisonStacks(s21_test_1, std_test_1));
}

TEST(Stack, Operator_move_assignment) {
  s21::Stack<int> s21_test{1, 3, 4, 5, 6, 7};
  s21::Stack<int> s21_test_1 = std::move(s21_test);
  std::stack<int> std_test;
  std_test.push(1);
  std_test.push(3);
  std_test.push(4);
  std_test.push(5);
  std_test.push(6);
  std_test.push(7);
  std::stack<int> std_test_1 = std::move(std_test);
  EXPECT_TRUE(comparisonStacks(s21_test_1, std_test_1));
}

TEST(Stack, Method_top) {
  s21::Stack<int> s21_test;
  std::stack<int> std_test;
  std_test.push(1);
  std_test.push(3);
  s21_test.push(1);
  s21_test.push(3);
  EXPECT_EQ(s21_test.top(), std_test.top());
  s21_test.pop();
  std_test.pop();
  EXPECT_EQ(s21_test.top(), std_test.top());
}

TEST(Stack, Method_empty) {
  s21::Stack<int> s21_test;
  std::stack<int> std_test;
  std_test.push(1);
  s21_test.push(1);
  EXPECT_EQ(s21_test.empty(), std_test.empty());
  s21_test.pop();
  std_test.pop();
  EXPECT_EQ(s21_test.empty(), std_test.empty());
}

TEST(Stack, Method_size) {
  s21::Stack<int> s21_test;
  std::stack<int> std_test;
  std_test.push(1);
  std_test.push(3);
  s21_test.push(1);
  s21_test.push(3);
  EXPECT_EQ(s21_test.size(), std_test.size());
  s21_test.pop();
  std_test.pop();
  EXPECT_EQ(s21_test.size(), std_test.size());
}

TEST(Stack, Method_push) {
  s21::Stack<int> s21_test;
  std::stack<int> std_test;
  std_test.push(1);
  std_test.push(3);
  std_test.push(4);
  s21_test.push(1);
  s21_test.push(3);
  s21_test.push(4);
  EXPECT_TRUE(comparisonStacks(s21_test, std_test));
}

TEST(Stack, Method_pop) {
  s21::Stack<int> s21_test;
  std::stack<int> std_test;
  std_test.push(1);
  std_test.push(3);
  std_test.pop();
  std_test.pop();
  s21_test.push(1);
  s21_test.push(3);
  s21_test.pop();
  s21_test.pop();
  EXPECT_TRUE(comparisonStacks(s21_test, std_test));
}

TEST(Stack, Method_swap) {
  s21::Stack<std::string> s21_test{"aboba", "asdf"};
  s21::Stack<std::string> s21_test_1{"5432", "2345"};
  std::stack<std::string> std_test;
  std_test.push("aboba");
  std_test.push("asdf");
  std::stack<std::string> std_test_1;
  std_test_1.push("5432");
  std_test_1.push("2345");
  s21_test.swap(s21_test_1);
  std_test.swap(std_test_1);
  EXPECT_TRUE(comparisonStacks(s21_test, std_test));
  EXPECT_TRUE(comparisonStacks(s21_test_1, std_test_1));
}

TEST(Stack, Method_insert_many_front) {
  s21::Stack<int> s21_test{1, 9, -1, 5};
  s21::Stack<int> s21_test_1{1, 9, -1, 5};
  s21_test.insert_many_front(7, 7, 7);
  for (auto i = 0; i < 3; i++) s21_test_1.push(7);
  EXPECT_TRUE(comparisonStacks(s21_test, s21_test_1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <class T>
bool comparisonStacks(s21::Stack<T> &s21_Stack, std::stack<T> &STL_Stack) {
  if (s21_Stack.size() != STL_Stack.size() ||
      s21_Stack.empty() != STL_Stack.empty())
    return false;
  for (size_t i = 0; i < s21_Stack.size(); ++i) {
    if (s21_Stack.top() != STL_Stack.top()) return false;
    s21_Stack.pop();
    STL_Stack.pop();
  }
  return true;
}

template <class T>
bool comparisonStacks(s21::Stack<T> &s21_Stack, s21::Stack<T> &STL_Stack) {
  if (s21_Stack.size() != STL_Stack.size() ||
      s21_Stack.empty() != STL_Stack.empty())
    return false;
  for (size_t i = 0; i < s21_Stack.size(); ++i) {
    if (s21_Stack.top() != STL_Stack.top()) return false;
    s21_Stack.pop();
    STL_Stack.pop();
  }
  return true;
}
