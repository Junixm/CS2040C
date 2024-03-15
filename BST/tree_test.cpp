#include "tree.h"
#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

TEST(Tree, 1_test_public_constructor) {
  RecordProperty("expression",
    "Check that default construct builds sane tree.");
  Tree<int> tree;
  EXPECT_EQ(tree.size(), 0);
  EXPECT_EQ(tree.root(), nullptr);
  EXPECT_TRUE(tree.empty());
}

TEST(Tree, 2_test_public_insert_single_value) {
  RecordProperty("expression",
    "Check that calling insert with a single value works as expected.");
  Tree<int> tree;
  tree.insert(0);
  EXPECT_EQ(tree.size(), 1);
  EXPECT_FALSE(tree.empty());
  ASSERT_NE(tree.root(), nullptr);
  EXPECT_EQ(tree.root()->element, 0);
  EXPECT_EQ(tree.root()->height, 0);
  EXPECT_EQ(tree.root()->left, nullptr);
  EXPECT_EQ(tree.root()->right, nullptr);
}

TEST(Tree, 3_test_public_size_correct_after_insert) {
  RecordProperty("expression",
    "Check that inserting a value increments size each time.");
  Tree<int> tree;
  tree.insert(2);
  EXPECT_EQ(tree.size(), 1);
  tree.insert(4);
  EXPECT_EQ(tree.size(), 2);
  tree.insert(1);
  EXPECT_EQ(tree.size(), 3);
  tree.insert(0);
  EXPECT_EQ(tree.size(), 4);
  tree.insert(3);
  EXPECT_EQ(tree.size(), 5);
}

class TreeTest :
  public testing::TestWithParam<vector<int>> {
};

template <typename T>
void check_tree_invariant(Node<T> *node, vector<T> &elements) {
  elements.push_back(node->element);
  if (node->left != nullptr) {
    EXPECT_LE(node->left->element, node->element);
    SCOPED_TRACE("Node(" + my_to_string(node->element) + ").left");
    check_tree_invariant(node->left, elements);
  }
  if (node->right != nullptr) {
    EXPECT_GE(node->right->element, node->element);
    SCOPED_TRACE("Node(" + my_to_string(node->element) + ").right");
    check_tree_invariant(node->right, elements);
  }
}

TEST_P(TreeTest, 4_test_public_insert) {
  RecordProperty("expression",
    "Check that tree invariant holds after inserting sample elements, "
    "and that all elements are in the tree.");
  Tree<int> tree;
  for (const auto v : GetParam()) {
    tree.insert(v);
  }
  vector<int> elements;
  ASSERT_NE(tree.root(), nullptr);
  {
    SCOPED_TRACE("Root");
    check_tree_invariant(tree.root(), elements);
  }
  sort(elements.begin(), elements.end());
  vector<int> expected = GetParam();
  sort(expected.begin(), expected.end());
  EXPECT_EQ(elements, expected);
}

template <typename T>
int height_of(Node<T>* node) {
  return node == nullptr ? -1 : node->height;
}

template <typename T>
void check_heights(Node<T> *node) {
  EXPECT_EQ(node->height,
      max(height_of(node->left), height_of(node->right)) + 1);
  if (node->left != nullptr) {
    SCOPED_TRACE("Node(" + my_to_string(node->element) + ").left");
    check_heights(node->left);
  }
  if (node->right != nullptr) {
    SCOPED_TRACE("Node(" + my_to_string(node->element) + ").right");
    check_heights(node->right);
  }
}

TEST_P(TreeTest, 5_test_public_insert_heights) {
  RecordProperty("expression",
    "Check that all heights in the tree are correct after inserting sample "
    "values.");
  Tree<int> tree;
  EXPECT_EQ(tree.height(), -1);
  for (const auto v : GetParam()) {
    tree.insert(v);
    ASSERT_NE(tree.root(), nullptr);
    EXPECT_EQ(tree.height(), tree.root()->height);
  }
  ASSERT_NE(tree.root(), nullptr);
  SCOPED_TRACE("Root");
  check_heights(tree.root());
}

TEST_P(TreeTest, 6_test_public_search_min) {
  RecordProperty("expression",
    "Check that min() returns the minimum value of the inserted values.");
  Tree<int> tree;
  for (const auto v : GetParam()) {
    tree.insert(v);
  }
  const int min_val = *std::min_element(GetParam().begin(), GetParam().end());
  EXPECT_EQ(tree.min(), min_val);
}

TEST_P(TreeTest, 7_test_public_search_max) {
  RecordProperty("expression",
    "Check that max() returns the maximum value of the inserted values.");
  Tree<int> tree;
  for (const auto v : GetParam()) {
    tree.insert(v);
  }
  const int max_val = *std::max_element(GetParam().begin(), GetParam().end());
  EXPECT_EQ(tree.max(), max_val);
}

template <typename T>
void check_balance(Node<T> *node) {
  EXPECT_LE(abs(height_of(node->left) - height_of(node->right)), 1);
  if (node->left != nullptr) {
    SCOPED_TRACE("Node(" + my_to_string(node->element) + ").left");
    check_balance(node->left);
  }
  if (node->right != nullptr) {
    SCOPED_TRACE("Node(" + my_to_string(node->element) + ").right");
    check_balance(node->right);
  }
}

TEST_P(TreeTest, 8_test_public_balance) {
  RecordProperty("expression",
    "Check that all nodes are balanced after inserting sample values.");
  Tree<int> tree;
  for (const auto v : GetParam()) {
    tree.insert(v);
  }
  ASSERT_NE(tree.root(), nullptr);
  SCOPED_TRACE("Root");
  check_balance(tree.root());
}

INSTANTIATE_TEST_CASE_P(PublicTestValues,
                         TreeTest,
                         testing::Values(
                          vector<int>{0, 2, -2, -4, -1},
                          vector<int>{1, 2, 3},
                          vector<int>{1, 0, -1}
                          , vector<int>{1, 2, 3, 4}
                         ));

TEST(Tree, 9_test_public_contains) {
  RecordProperty("expression",
    "Check that contains returns true for all inserted values and false for "
    "values not inserted.");
  Tree<int> tree;
  const vector<int> values{-17, -76, 52, 21, -35, 66, 93, 83, 28, -68, 99, -27,
      -59, 23, 19, 100, 0};
  for (const auto v : values) {
    tree.insert(v);
  }
  for (const auto v : values) {
    EXPECT_TRUE(tree.contains(v));
  }
  EXPECT_FALSE(tree.contains(42));
  EXPECT_FALSE(tree.contains(-1));
}

TEST(Tree, 10_test_public_successor) {
  RecordProperty("expression",
    "Check that successor returns the next largest value in the tree.");
  Tree<int> tree;
  vector<int> values{-17, -76, 52, 21, -35, 66, 93, 83, 28, -68, 99, -27,
      -59, 23, 19, 100, 0};
  for (const auto v : values) {
    tree.insert(v);
  }
  sort(values.begin(), values.end());
  for (int i = 0; i < values.size() - 1; ++i) {
    EXPECT_EQ(tree.successor(values[i]), values[i+1]);
  }
}

TEST(Tree, 11_test_public_pre_order) {
  RecordProperty("expression",
    "Check that pre_order produces pre-order traversal string.");
  Tree<int> tree;
  vector<int> values{0, 2, -2, -4, -1};
  for (const auto v : values) {
    tree.insert(v);
  }
  EXPECT_EQ(tree.pre_order(), "0 -2 -4 -1 2");
}

TEST(Tree, 12_test_public_in_order) {
  RecordProperty("expression",
    "Check that in_order produces in-order traversal string.");
  Tree<int> tree;
  vector<int> values{0, 2, -2, -4, -1};
  for (const auto v : values) {
    tree.insert(v);
  }
  EXPECT_EQ(tree.in_order(), "-4 -2 -1 0 2");
}

TEST(Tree, 13_test_public_post_order) {
  RecordProperty("expression",
    "Check that post_order produces post-order traversal string.");
  Tree<int> tree;
  vector<int> values{0, 2, -2, -4, -1};
  for (const auto v : values) {
    tree.insert(v);
  }
  EXPECT_EQ(tree.post_order(), "-4 -1 -2 2 0");
}

TEST(Tree, 14_test_public_successor_not_in_tree) {
  RecordProperty("expression",
    "Check that successor returns the next largest value in the tree even when "
    "the query value is not in the tree.");
  Tree<int> tree;
  vector<int> values{-17, -76, 52, 21, -35, 66, 93, 83, 28, -68, 99, -27,
      -59, 23, 19, 100, 0};
  for (const auto v : values) {
    tree.insert(v);
  }
  EXPECT_EQ(tree.successor(42), 52);
}