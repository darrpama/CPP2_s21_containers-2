#include "s21_vector.h"

#include <gtest/gtest.h>

#include <cstring>
#include <vector>

// Constructors
TEST(Vector, Constructor_base) {
  s21::Vector<int> s21_vec;
  std::vector<int> std_vec;
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.data(), std_vec.data());
}

TEST(Vector, Constructor_size_n) {
  s21::Vector<int> vec(2);
  std::vector<int> vec1(2);
  EXPECT_TRUE(vec.capacity() == vec1.capacity());
  EXPECT_TRUE(vec.size() == vec1.size());
}

TEST(Vector, Constructor_items) {
  s21::Vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> vec1{1, 2, 3, 4, 5};
  EXPECT_TRUE(vec.capacity() == vec1.capacity());
  EXPECT_TRUE(vec.size() == vec1.size());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_TRUE(vec1.data()[i] == vec.data()[i]);
  }
}

TEST(Vector, Constructor_copy) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int> vec2(vec);
  std::vector<int> std_vec{1, 2, 3};
  std::vector<int> std_vec2(std_vec);

  EXPECT_TRUE(vec2.capacity() == std_vec2.capacity());
  EXPECT_TRUE(vec2.size() == std_vec2.size());
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE(std_vec2.data()[i] == vec2.data()[i]);
  }
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_TRUE(std_vec2.data()[i] == vec2.data()[i]);
  }
}

TEST(Vector, Constructor_move) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int> vec2(std::move(vec));
  std::vector<int> std_vec{1, 2, 3};
  std::vector<int> std_vec2(std::move(std_vec));

  EXPECT_TRUE(vec2.capacity() == std_vec2.capacity());
  EXPECT_TRUE(vec2.size() == std_vec2.size());
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE(std_vec2.data()[i] == vec2.data()[i]);
  }
  EXPECT_TRUE(vec.data() == std_vec.data());
}

// Overloads
TEST(Vector, OperatorOverload_move) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int> vec2 = std::move(vec);
  std::vector<int> std_vec{1, 2, 3};
  std::vector<int> std_vec2 = std::move(std_vec);

  EXPECT_TRUE(vec2.capacity() == std_vec2.capacity());
  EXPECT_TRUE(vec2.size() == std_vec2.size());
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE(std_vec2.data()[i] == vec2.data()[i]);
  }
  EXPECT_TRUE(vec.data() == std_vec.data());
}

TEST(Vector, OperatorOverload_copy) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int> vec2 = vec;
  std::vector<int> std_vec{1, 2, 3};
  std::vector<int> std_vec2 = std_vec;

  EXPECT_TRUE(vec2.capacity() == std_vec2.capacity());
  EXPECT_TRUE(vec2.size() == std_vec2.size());
  for (size_t i = 0; i < vec2.capacity(); i++) {
    EXPECT_TRUE(std_vec2.data()[i] == vec2.data()[i]);
  }
}

// Element access
TEST(Vector, ElementAccess_at) {
  s21::Vector<int> vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  EXPECT_EQ(vec.at(2), std_vec.at(2));
}

TEST(Vector, ElementAccess_at_operator) {
  s21::Vector<int> vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  EXPECT_EQ(vec[2], std_vec[2]);
}

TEST(Vector, ElementAccess_front) {
  s21::Vector<int> vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  EXPECT_EQ(vec.front(), std_vec.front());
}

TEST(Vector, ElementAccess_back) {
  s21::Vector<int> vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  EXPECT_EQ(vec.back(), std_vec.back());
}

// Iterators
TEST(Vector, Iterator_begin) {
  s21::Vector<int> vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  EXPECT_EQ(*vec.begin(), *std_vec.begin());
}

TEST(Vector, Iterator_end) {
  s21::Vector<int> vec{1, 2, 3};
  int* a = vec.end();
  int* b = vec.begin();
  std::advance(b, 3);
  EXPECT_TRUE(a == b);
}

// Capacity
TEST(Vector, Capacity_empty) {
  s21::Vector<int> vec;
  s21::Vector<int> vec2{1, 2};
  EXPECT_TRUE(vec.empty());
  EXPECT_FALSE(vec2.empty());
}

TEST(Vector, Capacity_size) {
  s21::Vector<int> vec{1, 2};
  std::vector<int> std_vec{1, 2};
  EXPECT_EQ(vec.size(), std_vec.size());
}

TEST(Vector, Capacity_max_size) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;
  EXPECT_EQ(vec.max_size(), std_vec.max_size());
}

TEST(Vector, Capacity_capacity) {
  s21::Vector<int> vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Vector, Capacity_reserve) {
  s21::Vector<int> vec{1, 2, 3};
  vec.reserve(5);
  std::vector<int> std_vec{1, 2, 3};
  std_vec.reserve(5);
  EXPECT_TRUE(vec.size() == std_vec.size());
  EXPECT_TRUE(vec.capacity() == std_vec.capacity());
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_TRUE(vec.data()[i] == std_vec.data()[i]);
  }
}

TEST(Vector, Capacity_shrink_to_fit) {
  s21::Vector<int> vec{1, 2, 3};
  vec.reserve(5);
  std::vector<int> std_vec{1, 2, 3};
  std_vec.reserve(5);
  EXPECT_TRUE(vec.size() == std_vec.size());
  EXPECT_TRUE(vec.capacity() == std_vec.capacity());
  vec.shrink_to_fit();
  std_vec.shrink_to_fit();
  EXPECT_TRUE(vec.capacity() == std_vec.capacity());
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_TRUE(vec.data()[i] == std_vec.data()[i]);
  }
}

// Modifier
TEST(Vector, Modifier_clear) {
  s21::Vector<int> vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  vec.clear();
  std_vec.clear();
  EXPECT_TRUE(vec.size() == std_vec.size());
  EXPECT_TRUE(vec.capacity() == std_vec.capacity());
}

TEST(Vector, Modifier_insert) {
  s21::Vector<int> vec{100, 200, 300};
  std::vector<int> std_vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == std_vec.size());
  s21::Vector<int>::iterator it = vec.insert(vec.begin() + 1, 777);
  std::vector<int>::iterator std_it = std_vec.insert(std_vec.begin() + 1, 777);
  EXPECT_TRUE(vec.size() == std_vec.size());
  EXPECT_TRUE(*it == *std_it);
  EXPECT_TRUE(*(vec.begin() + 1) == *(std_vec.begin() + 1));
}

TEST(Vector, Modifier_erase) {
  s21::Vector<int> vec{100, 200, 300};
  std::vector<int> std_vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == std_vec.size());
  auto iter = vec.begin();
  auto std_iter = std_vec.begin();
  vec.erase(++iter);
  std_vec.erase(++std_iter);
  EXPECT_TRUE(vec.size() == std_vec.size());
  EXPECT_TRUE(vec.data()[0] == std_vec.data()[0]);
  EXPECT_TRUE(vec.data()[1] == std_vec.data()[1]);
}

TEST(Vector, Modifier_push_back) {
  s21::Vector<int> vec{100, 200, 300};
  std::vector<int> std_vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == std_vec.size());
  vec.push_back(777);
  std_vec.push_back(777);
  EXPECT_TRUE(vec.size() == std_vec.size());
  EXPECT_TRUE(vec.data()[0] == std_vec.data()[0]);
  EXPECT_TRUE(vec.data()[1] == std_vec.data()[1]);
  EXPECT_TRUE(vec.data()[2] == std_vec.data()[2]);
  EXPECT_TRUE(vec.data()[3] == std_vec.data()[3]);
}

TEST(Vector, Modifier_pop_back) {
  s21::Vector<int> vec{100, 200, 300};
  std::vector<int> std_vec{100, 200, 300};
  EXPECT_TRUE(vec.size() == std_vec.size());
  vec.pop_back();
  std_vec.pop_back();
  EXPECT_TRUE(vec.size() == std_vec.size());
  EXPECT_TRUE(vec.data()[0] == std_vec.data()[0]);
  EXPECT_TRUE(vec.data()[1] == std_vec.data()[1]);
}

TEST(Vector, Modifier_swap) {
  s21::Vector<int> vec{100, 200, 300};
  s21::Vector<int> vec2{1000, 2000, 3000};
  std::vector<int> std_vec{100, 200, 300};
  std::vector<int> std_vec2{1000, 2000, 3000};
  vec.swap(vec2);
  std_vec.swap(std_vec2);
  EXPECT_TRUE(vec.data()[0] == std_vec.data()[0]);
  EXPECT_TRUE(vec.data()[1] == std_vec.data()[1]);
  EXPECT_TRUE(vec.data()[2] == std_vec.data()[2]);
  EXPECT_TRUE(vec2.data()[0] == std_vec2.data()[0]);
  EXPECT_TRUE(vec2.data()[1] == std_vec2.data()[1]);
  EXPECT_TRUE(vec2.data()[2] == std_vec2.data()[2]);
}

// Bonus
TEST(Vector, insert_many) {
  s21::Vector<int> vec{100, 200, 300};
  s21::Vector<int>::const_iterator it = vec.begin() + 1;
  auto res = vec.insert_many(it, 777, 666, 555);
  EXPECT_TRUE(vec.size() == 6);
  EXPECT_TRUE(*res == 555);
  EXPECT_TRUE(*(vec.begin() + 1) == 777);
}

TEST(Vector, insert_many_back) {
  s21::Vector<int> vec{100, 200, 300};
  vec.insert_many_back(777, 666, 555);
  EXPECT_TRUE(vec.size() == 6);
  EXPECT_TRUE(vec.back() == 555);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
