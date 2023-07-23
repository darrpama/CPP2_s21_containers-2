#include "s21_map.h"

#include <gtest/gtest.h>

#include <cstring>
#include <map>

template <class KT, class VT>
bool compare(s21::Map<KT, VT> &m1, s21::Map<KT, VT> &m2);

template <class KT, class VT>
bool compareWithStd(s21::Map<KT, VT> &s21_map, std::map<KT, VT> &std_map);

// Constructors
TEST(Map, base_constructor) {
  s21::Map<int, int> s21_map;
  std::map<int, int> std_map;
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, initializer_list) {
  s21::Map<int, char> s21_map{
      std::pair<int, char>{4, 'a'}, std::pair<int, char>{2, 'b'},
      std::pair<int, char>{3, 'c'}, std::pair<int, char>{7, 'd'}};
  std::map<int, char> std_map{
      std::pair<int, char>{4, 'a'}, std::pair<int, char>{2, 'b'},
      std::pair<int, char>{3, 'c'}, std::pair<int, char>{7, 'd'}};
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, copy_constructor) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}, std::pair<int, char>{6, 'f'},
      std::pair<int, char>{8, 'g'}};
  s21::Map<int, char> map2(map);
  ASSERT_TRUE(compare(map, map2));
}

TEST(Map, move_constructor) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}};
  s21::Map<int, char> map2(map);
  s21::Map<int, char> map3(std::move(map));
  ASSERT_FALSE(compare(map, map2));
  ASSERT_TRUE(compare(map2, map3));
}

TEST(Map, move_operator) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}};
  s21::Map<int, char> map2(map);
  s21::Map<int, char> map3 = std::move(map);
  ASSERT_FALSE(compare(map, map2));
  ASSERT_TRUE(compare(map2, map3));
}

TEST(Map, accessor_inserter_element_operator) {
  s21::Map<int, char> s21_map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}};
  std::map<int, char> std_map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'},
      std::pair<int, char>{4, 'e'}};
  s21_map[2] = 'g';
  std_map[2] = 'g';
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, begin) {
  s21::Map<int, char> s21_map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'}};
  std::map<int, char> std_map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'}};
  ASSERT_TRUE((*std_map.begin()).first == s21_map.begin().first());
}

TEST(Map, end) {
  s21::Map<int, char> map{
      std::pair<int, char>{5, 'a'}, std::pair<int, char>{3, 'b'},
      std::pair<int, char>{7, 'c'}, std::pair<int, char>{2, 'd'}};
  ASSERT_TRUE(map.end().getNode() == nullptr);
}

TEST(Map, empty) {
  s21::Map<int, char> s21_map;
  std::map<int, char> std_map;
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, max_size) {
  s21::Map<int, int> s21_map;
  std::map<int, int> std_map;
  EXPECT_TRUE(s21_map.max_size() > std_map.max_size());
  EXPECT_TRUE(s21_map.max_size() <= std::numeric_limits<size_t>::max());
}

// Modifiers
TEST(Map, clear) {
  s21::Map<int, char> s21_map{std::pair<int, char>{5, 'a'},
                              std::pair<int, char>{3, 'b'}};
  s21_map.clear();
  std::map<int, char> std_map{std::pair<int, char>{5, 'a'},
                              std::pair<int, char>{3, 'b'}};
  std_map.clear();
  ASSERT_EQ(std_map.size(), s21_map.size());
  ASSERT_EQ(std_map.empty(), s21_map.empty());
}

TEST(Map, insert_pair) {
  s21::Map<int, int> s21_map;
  s21_map.insert(std::make_pair(3, 10));
  std::map<int, int> std_map;
  std_map.insert(std::make_pair(3, 10));
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, insert_key_value) {
  s21::Map<int, char> s21_map;
  s21_map.insert(3, 'a');
  s21_map.insert(2, 'b');
  std::map<int, char> std_map;
  std_map.insert(std::make_pair(3, 'a'));
  std_map.insert(std::make_pair(2, 'b'));
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, insert_or_assign_key_value) {
  s21::Map<int, char> s21_map;
  s21_map.insert(3, 'a');
  s21_map.insert_or_assign(2, 'c');
  s21_map.insert_or_assign(2, 'G');
  std::map<int, char> std_map;
  std_map.insert(std::make_pair(3, 'a'));
  std_map.insert_or_assign(2, 'c');
  std_map.insert_or_assign(2, 'G');
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, erase_no_child) {
  s21::Map<int, char> s21_map;
  s21_map.insert(7, 'a');
  s21_map.insert(3, 'b');
  s21_map.erase(s21_map.find(3));
  std::map<int, char> std_map;
  std_map.insert(std::make_pair(7, 'a'));
  std_map.insert(std::make_pair(3, 'b'));
  std_map.erase(std_map.find(3));
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, erase_one_child) {
  s21::Map<int, char> s21_map;
  s21_map.insert(7, 'a');
  s21_map.insert(3, 'b');
  s21_map.insert(8, 'c');
  s21_map.insert(2, 'd');
  s21_map.erase(s21_map.find(3));
  std::map<int, char> std_map;
  std_map.insert(std::make_pair(7, 'a'));
  std_map.insert(std::make_pair(3, 'b'));
  std_map.insert(std::make_pair(8, 'c'));
  std_map.insert(std::make_pair(2, 'd'));
  std_map.erase(std_map.find(3));
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, erase_two_child) {
  s21::Map<int, char> s21_map;
  s21_map.insert(7, 'a');
  s21_map.insert(3, 'b');
  s21_map.insert(8, 'c');
  s21_map.insert(2, 'd');
  s21_map.insert(4, 'e');
  s21_map.erase(s21_map.find(3));
  std::map<int, char> std_map;
  std_map.insert(std::make_pair(7, 'a'));
  std_map.insert(std::make_pair(3, 'b'));
  std_map.insert(std::make_pair(8, 'c'));
  std_map.insert(std::make_pair(2, 'd'));
  std_map.insert(std::make_pair(4, 'e'));
  std_map.erase(std_map.find(3));
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, erase_two_child_2) {
  s21::Map<int, char> s21_map;
  s21_map.insert(8, 'a');
  s21_map.insert(4, 'b');
  s21_map.insert(11, 'c');
  s21_map.insert(2, 'd');
  s21_map.insert(6, 'e');
  s21_map.insert(9, 'e');
  s21_map.insert(12, 'e');
  s21_map.insert(1, 'e');
  s21_map.insert(3, 'e');
  s21_map.insert(5, 'e');
  s21_map.insert(7, 'e');
  s21_map.insert(10, 'e');
  s21_map.erase(s21_map.find(4));
  std::map<int, char> std_map;
  std_map.insert(std::make_pair(8, 'a'));
  std_map.insert(std::make_pair(4, 'b'));
  std_map.insert(std::make_pair(11, 'c'));
  std_map.insert(std::make_pair(2, 'd'));
  std_map.insert(std::make_pair(6, 'e'));
  std_map.insert(std::make_pair(9, 'e'));
  std_map.insert(std::make_pair(12, 'e'));
  std_map.insert(std::make_pair(1, 'e'));
  std_map.insert(std::make_pair(3, 'e'));
  std_map.insert(std::make_pair(5, 'e'));
  std_map.insert(std::make_pair(7, 'e'));
  std_map.insert(std::make_pair(10, 'e'));
  std_map.erase(std_map.find(4));
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, merge) {
  s21::Map<int, char> s21_map{{8, 'a'}, {4, 'b'}, {11, 'c'}};
  s21::Map<int, char> s21_map2{{1, 'd'}, {10, 'e'}, {11, 'f'}};
  s21_map.merge(s21_map2);
  std::map<int, char> std_map{{8, 'a'}, {4, 'b'}, {11, 'c'}};
  std::map<int, char> std_map2{{1, 'd'}, {10, 'e'}, {11, 'f'}};
  std_map.merge(std_map2);
  ASSERT_TRUE(compareWithStd(s21_map, std_map));
}

TEST(Map, braces_empty) {
  s21::Map<int, char> s21_map{{8, 'a'}, {4, 'b'}, {11, 'c'}};
  std::map<int, char> std_map{{8, 'a'}, {4, 'b'}, {11, 'c'}};
  EXPECT_EQ(s21_map[0], std_map[0]);
}

TEST(Map, insert_many) {
  s21::Map<int, int> map;
  auto result = map.insert_many(std::make_pair(3, 40), std::make_pair(5, 50),
                                std::make_pair(10, 60), std::make_pair(16, 70));
  ASSERT_EQ(map.size(), 4);
  ASSERT_EQ(map.find(3).second(), 40);
  ASSERT_EQ(map.find(5).second(), 50);
  ASSERT_EQ(map.find(10).second(), 60);
  ASSERT_EQ(map.find(16).second(), 70);
  ASSERT_EQ(result.at(0).first.second(), 40);
  ASSERT_EQ(result.at(1).first.second(), 50);
  ASSERT_EQ(result.at(2).first.second(), 60);
  ASSERT_EQ(result.at(3).first.second(), 70);
  ASSERT_EQ(result.at(0).second, true);
}

TEST(Map, iter_ptr) {
  s21::Map<int, int> map;
  auto it = map.begin();
  ASSERT_TRUE((++it) == map.begin());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <class KT, class VT>
bool compare(s21::Map<KT, VT> &m1, s21::Map<KT, VT> &m2) {
  if (m1.size() != m2.size()) {
    return false;
  }
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  for (; it2 != m2.end(); ++it2, ++it1) {
    if (*it2 != *it1) {
      return false;
    }
  }
  return true;
}

template <class KT, class VT>
bool compareWithStd(s21::Map<KT, VT> &s21_map, std::map<KT, VT> &std_map) {
  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();
  for (; std_it != std_map.end(); ++std_it, ++s21_it) {
    if ((*std_it).first != s21_it.first()) {
      return false;
    }
    if ((*std_it).second != s21_it.second()) {
      return false;
    }
  }
  return true;
}