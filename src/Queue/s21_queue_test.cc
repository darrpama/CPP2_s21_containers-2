#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

template <class T>
bool comparisonQueues(s21::Queue<T> &s21_Queue, std::queue<T> &STL_Queue);
template <class T>
bool comparisonQueues(s21::Queue<T> &s21_Queue, s21::Queue<T> &STL_Queue);

TEST(Queue, Constructor_default) {
  s21::Queue<int> s21_test;
  std::queue<int> std_test;
  EXPECT_EQ(s21_test.size(), std_test.size());
}

TEST(Queue, Constructor_init) {
  s21::Queue<char> s21_test{'a', 'b', 'c', 'd'};
  std::queue<char> std_test;
  std_test.push('a');
  std_test.push('b');
  std_test.push('c');
  std_test.push('d');
  EXPECT_TRUE(comparisonQueues(s21_test, std_test));
}

TEST(Queue, Constructor_copy) {
  s21::Queue<char> s21_test{'a', 'b', 'c', 'd'};
  std::queue<char> std_test;
  std_test.push('a');
  std_test.push('b');
  std_test.push('c');
  std_test.push('d');
  s21::Queue<char> s21_test_1(s21_test);
  std::queue<char> std_test_1(std_test);
  EXPECT_TRUE(comparisonQueues(s21_test_1, std_test_1));
}

TEST(Queue, Constructor_move) {
  s21::Queue<char> s21_test{'a', 'b', 'c', 'd'};
  std::queue<char> std_test;
  std_test.push('a');
  std_test.push('b');
  std_test.push('c');
  std_test.push('d');
  s21::Queue<char> s21_test_1(std::move(s21_test));
  std::queue<char> std_test_1(std::move(std_test));
  EXPECT_TRUE(comparisonQueues(s21_test_1, std_test_1));
}

TEST(Queue, Operator_copy_assignment) {
  s21::Queue<int> s21_test_0{1, 3, 4, 5, 6, 7};
  s21::Queue<int> s21_test(s21_test_0);
  s21::Queue<int> s21_test_1 = s21_test;
  std::queue<int> std_test_0;
  std_test_0.push(1);
  std_test_0.push(3);
  std_test_0.push(4);
  std_test_0.push(5);
  std_test_0.push(6);
  std_test_0.push(7);
  std::queue<int> std_test(std_test_0);
  std::queue<int> std_test_1 = std_test;
  EXPECT_TRUE(comparisonQueues(s21_test_1, std_test_1));
}

TEST(Queue, Operator_move_assignment) {
  s21::Queue<int> s21_test{1, 3, 4, 5, 6, 7};
  s21::Queue<int> s21_test_1 = std::move(s21_test);
  std::queue<int> std_test;
  std_test.push(1);
  std_test.push(3);
  std_test.push(4);
  std_test.push(5);
  std_test.push(6);
  std_test.push(7);
  std::queue<int> std_test_1 = std::move(std_test);
  EXPECT_TRUE(comparisonQueues(s21_test_1, std_test_1));
}

TEST(Queue, Method_front) {
  s21::Queue<int> s21_test;
  std::queue<int> std_test;
  std_test.push(1);
  std_test.push(3);
  s21_test.push(1);
  s21_test.push(3);
  EXPECT_EQ(s21_test.front(), std_test.front());
  s21_test.pop();
  std_test.pop();
  EXPECT_EQ(s21_test.front(), std_test.front());
}

TEST(Queue, Method_back) {
  s21::Queue<int> s21_test;
  std::queue<int> std_test;
  std_test.push(1);
  std_test.push(3);
  s21_test.push(1);
  s21_test.push(3);
  EXPECT_EQ(s21_test.back(), std_test.back());
  s21_test.pop();
  std_test.pop();
  EXPECT_EQ(s21_test.back(), std_test.back());
}

TEST(Queue, Method_empty) {
  s21::Queue<int> s21_test;
  std::queue<int> std_test;
  std_test.push(1);
  s21_test.push(1);
  EXPECT_EQ(s21_test.empty(), std_test.empty());
  s21_test.pop();
  std_test.pop();
  EXPECT_EQ(s21_test.empty(), std_test.empty());
}

TEST(Queue, Method_size) {
  s21::Queue<int> s21_test;
  std::queue<int> std_test;
  std_test.push(1);
  std_test.push(3);
  s21_test.push(1);
  s21_test.push(3);
  EXPECT_EQ(s21_test.size(), std_test.size());
  s21_test.pop();
  std_test.pop();
  EXPECT_EQ(s21_test.size(), std_test.size());
}

TEST(Queue, Method_push) {
  s21::Queue<int> s21_test;
  std::queue<int> std_test;
  std_test.push(1);
  std_test.push(3);
  std_test.push(4);
  s21_test.push(1);
  s21_test.push(3);
  s21_test.push(4);
  EXPECT_TRUE(comparisonQueues(s21_test, std_test));
}

TEST(Queue, Method_pop) {
  s21::Queue<int> s21_test;
  std::queue<int> std_test;
  std_test.push(1);
  std_test.push(3);
  std_test.pop();
  std_test.pop();
  s21_test.push(1);
  s21_test.push(3);
  s21_test.pop();
  s21_test.pop();
  EXPECT_TRUE(comparisonQueues(s21_test, std_test));
}

TEST(Queue, Method_swap) {
  s21::Queue<std::string> s21_test{"aboba", "asdf"};
  s21::Queue<std::string> s21_test_1{"5432", "2345"};
  std::queue<std::string> std_test;
  std_test.push("aboba");
  std_test.push("asdf");
  std::queue<std::string> std_test_1;
  std_test_1.push("5432");
  std_test_1.push("2345");
  s21_test.swap(s21_test_1);
  std_test.swap(std_test_1);
  EXPECT_TRUE(comparisonQueues(s21_test, std_test));
  EXPECT_TRUE(comparisonQueues(s21_test_1, std_test_1));
}

TEST(Queue, Method_insert_many_front) {
  s21::Queue<int> s21_test{1, 9, -1, 5};
  s21::Queue<int> s21_test_1{1, 9, -1, 5};
  s21_test.insert_many_back(7, 7, 7);
  for (auto i = 0; i < 3; i++) s21_test_1.push(7);
  EXPECT_TRUE(comparisonQueues(s21_test, s21_test_1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <class T>
bool comparisonQueues(s21::Queue<T> &s21_Queue, std::queue<T> &STL_Queue) {
  if (s21_Queue.size() != STL_Queue.size() ||
      s21_Queue.empty() != STL_Queue.empty())
    return false;
  for (size_t i = 0; i < s21_Queue.size(); ++i) {
    if (s21_Queue.front() != STL_Queue.front()) return false;
    s21_Queue.pop();
    STL_Queue.pop();
  }
  return true;
}

template <class T>
bool comparisonQueues(s21::Queue<T> &s21_Queue, s21::Queue<T> &STL_Queue) {
  if (s21_Queue.size() != STL_Queue.size() ||
      s21_Queue.empty() != STL_Queue.empty())
    return false;
  for (size_t i = 0; i < s21_Queue.size(); ++i) {
    if (s21_Queue.front() != STL_Queue.front()) return false;
    s21_Queue.pop();
    STL_Queue.pop();
  }
  return true;
}
