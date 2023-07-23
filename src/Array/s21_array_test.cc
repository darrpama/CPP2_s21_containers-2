#include "s21_array.h"

#include <gtest/gtest.h>

#include <array>
#include <cstring>

// Compare s21 array with std array
template <class T, size_t N>
bool compareWithStd(s21::Array<T, N>& s21_arr, std::array<T, N>& std_arr) {
  if (s21_arr.size() != std_arr.size() || s21_arr.empty() != std_arr.empty()) {
    return false;
  }
  auto it1 = s21_arr.begin();
  auto it2 = std_arr.begin();
  for (size_t i = 0; i < s21_arr.size(); ++i, ++it1, ++it2) {
    if (*it1 != *it2) return false;
  }
  return true;
}

// Compare s21 arrays
template <class T, size_t N>
bool compareWithS21(s21::Array<T, N>& array, s21::Array<T, N>& array2) {
  if (array.size() != array2.size() || array.empty() != array2.empty()) {
    return false;
  }

  auto it1 = array.begin();
  auto it2 = array2.begin();

  for (size_t i = 0; i < array.size(); ++i, ++it1, ++it2) {
    if (*it1 != *it2) return false;
  }

  return true;
}

TEST(Array, Constructor_default__init_valid) {
  s21::Array<int, 3> s21_arr;
  std::array<int, 3> std_arr;
  EXPECT_EQ(s21_arr.size(), std_arr.size());
}

TEST(Array, Constructor_default__zero_init) {
  std::array<int, 0> std_arr;
  s21::Array<int, 0> s21_arr;
  EXPECT_EQ(std_arr.size(), s21_arr.size());
}

TEST(Array, Constructor_list__correct) {
  s21::Array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};
  EXPECT_TRUE(s21_arr.size() == std_arr.size());
  EXPECT_TRUE(compareWithStd(s21_arr, std_arr));
}

TEST(Array, Constructor_list__less_items) {
  s21::Array<int, 3> s21_arr{1, 2};
  std::array<int, 3> std_arr{1, 2};
  EXPECT_TRUE(compareWithStd(s21_arr, std_arr));
}

TEST(Array, Constructor_copy__integers) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3> arr2(arr);
  EXPECT_TRUE(compareWithS21(arr2, arr));
}

TEST(Array, Constructor_copy__strings) {
  s21::Array<std::string, 3> arr{"abc", "xyz", "qwe"};
  s21::Array<std::string, 3> arr2(arr);
  EXPECT_TRUE(compareWithS21(arr2, arr));
}

TEST(Array, Constructor_move__integers) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3> arr2(std::move(arr));
  s21::Array<int, 3> test_arr{1, 2, 3};
  EXPECT_TRUE(compareWithS21(arr2, test_arr));
  EXPECT_TRUE(arr2.size() == 3);
}

TEST(Array, Constructor_move__strings) {
  s21::Array<std::string, 3> arr{"abc", "xyz", "qwe"};
  s21::Array<std::string, 3> arr2(std::move(arr));
  s21::Array<std::string, 3> test_arr{"abc", "xyz", "qwe"};
  EXPECT_TRUE(compareWithS21(arr2, test_arr));
  EXPECT_TRUE(arr2.size() == 3);
}

TEST(Array, Assignment_operator_move) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3> arr2 = std::move(arr);
  s21::Array<int, 3> test_arr{1, 2, 3};
  EXPECT_TRUE(compareWithS21(arr2, test_arr));
  EXPECT_TRUE(arr2.size() == 3);
}

TEST(Array, Assignment_operator_copy) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3> arr2 = arr;
  EXPECT_TRUE(compareWithS21(arr2, arr));
  EXPECT_TRUE(arr2.size() == arr.size());
}

TEST(Array, ElementAccess_at) {
  s21::Array<int, 3> s21_arr{1, 2, 3};
  std::array<int, 3> std_arr{1, 2, 3};
  int a = s21_arr.at(2);
  int b = std_arr.at(2);
  EXPECT_EQ(a, b);
}

TEST(Array, ElementAccess_at__exception) {
  s21::Array<int, 3> arr{1, 2, 3};
  EXPECT_THROW((arr.at(3)), std::out_of_range);
}

TEST(Array, ElementAccess_front) {
  s21::Array<int, 3> s21_arr{1, 2, 3};
  std::array<int, 3> std_arr{1, 2, 3};
  int a = s21_arr.front();
  int b = std_arr.front();
  EXPECT_EQ(a, b);
}

TEST(Array, front_empty) {
  s21::Array<int, 0> s21_arr;
  EXPECT_THROW(s21_arr.front(), std::out_of_range);
}

TEST(Array, ElementAccess_back) {
  s21::Array<int, 3> s21_arr{1, 2, 3};
  s21::Array<int, 3> std_arr{1, 2, 3};
  int a = s21_arr.back();
  int b = std_arr.back();
  EXPECT_TRUE(a == b);
}

TEST(Array, back_empty) {
  s21::Array<int, 0> arr;
  EXPECT_THROW(arr.back(), std::out_of_range);
}

TEST(Array, ElementAccess_data) {
  s21::Array<int, 3> s21_arr{1, 2, 3};
  std::array<int, 3> std_arr{1, 2, 3};
  EXPECT_EQ(*(s21_arr.data()), *(std_arr.data()));
}

TEST(Array, Iterator_begin) {
  s21::Array<int, 3> arr{1, 2, 3};
  int* a = arr.begin();
  EXPECT_EQ(*a, 1);
}

TEST(Array, Iterator_end) {
  s21::Array<int, 3> s21_arr{1, 2, 3};
  std::array<int, 3> std_arr{1, 2, 3};
  int* a = s21_arr.end();
  int* b = std_arr.end();
  EXPECT_EQ(*(b - 1), *(a - 1));
}

TEST(Array, Capacity_empty) {
  s21::Array<int, 0> arr;
  s21::Array<int, 2> arr2{1, 2};
  EXPECT_TRUE(arr.empty());
  EXPECT_FALSE(arr2.empty());
}

TEST(Array, Capacity_size) {
  s21::Array<int, 2> s21_arr{1, 2};
  std::array<int, 2> std_arr{1, 2};
  EXPECT_EQ(s21_arr.size(), std_arr.size());

  s21::Array<int, 4> s21_arr2{1, 2};
  std::array<int, 4> std_arr2{1, 2};
  EXPECT_EQ(s21_arr2.size(), std_arr2.size());
}

TEST(Array, Capacity_max_size) {
  s21::Array<int, 10> s21_arr;
  std::array<int, 10> std_arr;
  EXPECT_EQ(s21_arr.max_size(), std_arr.max_size());
}

TEST(Array, Modifier_swap) {
  s21::Array<int, 3> s21_arr{100, 200, 300};
  s21::Array<int, 3> s21_arr2{1000, 2000, 3000};
  s21_arr.swap(s21_arr2);

  std::array<int, 3> std_arr{100, 200, 300};
  std::array<int, 3> std_arr2{1000, 2000, 3000};
  std_arr.swap(std_arr2);
  EXPECT_TRUE(compareWithStd(s21_arr, std_arr));
  EXPECT_TRUE(compareWithStd(s21_arr2, std_arr2));
}

TEST(Array, Modifier_fill) {
  s21::Array<int, 3> s21_arr;
  std::array<int, 3> std_arr;
  s21_arr.fill(7);
  std_arr.fill(7);
  EXPECT_TRUE(compareWithStd(s21_arr, std_arr));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef __APPLE__
  free(__cxxabiv1::__cxa_get_globals());
#endif
  return RUN_ALL_TESTS();
}
