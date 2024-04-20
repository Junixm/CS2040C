#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>

template <typename T>
std::string my_to_string(const T& t) {
  return std::to_string(t);
}

template <>
std::string my_to_string(const std::string& t) {
  return "\"" + t + "\"";
}

template <typename T> struct Node {
  T element;
  int height;
  Node<T> *left;
  Node<T> *right;

  Node(T element)
      : element{element}, height{0}, left{nullptr}, right{nullptr} {}
  Node(T element, int height)
      : element{element}, height{height}, left{nullptr}, right{nullptr} {}
};

template <typename T> class Tree {
private:
  size_t m_size;
  Node<T> *m_root;
public:
  Tree(); // Constructor
  ~Tree(); // Destructor
  Node<T> *root(); // Returns a pointer to the root
  bool empty() const; // Checks whether the tree is empty
  size_t size() const; // Returns the number of elements
  int height() const;  // Returns the height of the tree
  void insert(T element);  // Inserts the specified element
  bool contains(T element) const; // Checks whether the container contains the specified element
  T max() const; // Returns the maximum element
  T min() const; // Returns the minimum element
  T successor(T element);  // Returns the successor of the specified element
  std::string pre_order(); // Convert each element in the tree to string in pre-order.
  std::string in_order(); // Convert each element in the tree to string in order.
  std::string post_order(); // Convert each element in the tree to string in post-order.
  std::string to_string(bool with_height = true) const { // Returns a string equivalent of the tree
    return m_to_string(with_height, m_root, 0);
  }
private:
  std::string m_to_string(bool with_height, Node<T> *node, int ident) const {
    std::string res;
    if (node == nullptr) {
      return res;
    }
    if (node->right != nullptr) {
      res += m_to_string(with_height, node->right, ident + 2);
    }
    for (int i = 0; i < ident; i++) {
      res += " ";
    }
    res += my_to_string(node->element);
    if (with_height) {
      res += "(h=" + my_to_string(node->height) + ")";
    }
    res += "\n";
    if (node->left != nullptr) {
      res += m_to_string(with_height, node->left, ident + 2);
    }
    return res;
  }
  // Feel free to declare helper functions here, if necessary
  int height(Node<T>* node) const;
  Node<T> *insert(T element, Node<T>* parent);  // Inserts the specified element recursive
  void updateHeight(Node<T>* node); // Update height of the root
  int balanceDifference(Node<T>* parent); // Returns balance difference
  void destroyTree(Node<T>* node); // Destroy tree recursive
  void balance(Node<T>*& root); // Balance Tree
  Node<T>* rotateRight(Node<T>* node); // Rotate right
  Node<T>* rotateLeft(Node<T>* node); // Rotate left
  };
// Constructor
template <typename T> Tree<T>::Tree() : m_root(nullptr), m_size(0) {}
// Destructor
template <typename T> Tree<T>::~Tree() {
  destroyTree(m_root);
}
// Destroy tree recursive
template <typename T> void Tree<T>::destroyTree(Node<T>* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
// Returns a pointer to the root
template <typename T> Node<T> *Tree<T>::root() {
  return m_root;
}
// Checks whether the tree is empty
template <typename T> bool Tree<T>::empty() const {
  return (m_root == nullptr);
}
// Returns the number of elements
template <typename T> size_t Tree<T>::size() const {
  return m_size;
}
// Returns the height of the tree
template <typename T> int Tree<T>::height() const {
  if(m_root == nullptr){
    return -1;
  }
  return m_root->height;
}
// Returns the height of a node
template <typename T> int Tree<T>::height(Node<T>* node) const {
  if(node == nullptr){
    return -1;
  }
  return node->height;
}
// Inserts an element
template <typename T> void Tree<T>::insert(T element) {
  m_root = insert(element, m_root);
  m_size++;
  balance(m_root);
}
// Insert recursive
template <typename T> Node<T>* Tree<T>::insert(T element, Node<T>* parent) {
  if(parent == nullptr){
    return new Node<T>(element);
  }
  if(element < parent->element){
    parent->left = insert(element, parent->left);
  } else{
    parent->right = insert(element, parent->right);
  }
  updateHeight(parent);
  return parent;
}
// Update height of a node
template<typename T> void Tree<T>::updateHeight(Node<T>* parent) {
  if(parent == nullptr){
    return;
  }
  int leftHeight = height(parent->left);
  int rightHeight = height(parent->right);
  parent->height = 1 + std::max(leftHeight, rightHeight);
}
// Balance the tree
template<typename T> void Tree<T>::balance(Node<T>*& root){
  if(root == nullptr){
    return;
  }
  int diff = balanceDifference(root);
  if(diff > 1){
    // Left heavy
    if(balanceDifference(root->left) < 0){
      // Left heavy with right subtree
      root->left = rotateLeft(root->left);
    }
    // Left heavy with no right subtree
    root = rotateRight(root);
  } else if(diff < -1){
    // Right heavy
    if(balanceDifference(root->right) > 0){
      // Right heavy with left subtree
      root->right = rotateRight(root->right);
    }
    // Right heavy with no left subtree
    root = rotateLeft(root);
  }
  balance(root->left);
  balance(root->right);
  updateHeight(root);
}
// Rotate right
template<typename T> Node<T>* Tree<T>::rotateRight(Node<T>* node){
  Node<T>* newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}
// Rotate left
template<typename T> Node<T>* Tree<T>::rotateLeft(Node<T>* node){
  Node<T>* newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}
// Returns balance difference
template<typename T> int Tree<T>::balanceDifference(Node<T>* parent){
  if(parent == nullptr){
    return 0;
  }
  int leftHeight = height(parent->left);
  int rightHeight = height(parent->right);
  
  return leftHeight - rightHeight;
}
// Checks whether the container contains the specified element
template <typename T> bool Tree<T>::contains(T element) const {
  if(m_root == nullptr){
    throw std::logic_error("Tree is empty");
  }
  Node<T>* parent = m_root;
  while(parent != nullptr){
    if(element == parent->element){
      return true;
    }
    if(element < parent->element){
      parent = parent->left;
    } else{
      parent = parent->right;
    }
  }
  return false;
}
// Returns the maximum element
template <typename T> T Tree<T>::max() const {
  if(m_root == nullptr){
    throw std::logic_error("Tree is empty");
  }
  Node<T>* current = m_root;
  while(current->right != nullptr){
    current = current->right;
  }
  return current->element;
}
// Returns the minimum element
template <typename T> T Tree<T>::min() const {
  if(m_root == nullptr){
    throw std::logic_error("Tree is empty");
  }
  Node<T>* current = m_root;
  while(current->left != nullptr){
    current = current->left;
  }
  return current->element;
}
// Returns the successor of the specified element
template <typename T> T Tree<T>::successor(T element) {
  if(m_root == nullptr){
    throw std::logic_error("Tree is empty");
  }
  Node<T>* next = m_root;
  Node<T>* parent = nullptr;
  //find element node
  while(next != nullptr && next->element != element){
    if(element < next->element){
      parent = next;
      next = next->left;
    } else{
      next = next->right;
    }
  }
  //if successor no right subtree or not in tree
  //return parent
  if(next == nullptr || next->right == nullptr){
    if(parent == nullptr){
      throw std::out_of_range("No successor found");
    }
    return parent->element;
  }
    
  //if successor node have right subtree,
  //go right, then left all the way down
  next = next->right;
  while(next->left != nullptr){
    next = next->left;
  }
  return next->element; 
}
template <typename T>
std::string _pre_order(Node<T> *node) {
  return my_to_string(node->element)
    + (node->left == nullptr ? "" : " " + _pre_order(node->left))
    + (node->right == nullptr ? "" : " " + _pre_order(node->right));
}
template <typename T>
std::string Tree<T>::pre_order() {
  if (m_root == nullptr) {
    return "";
  }
  return _pre_order(m_root);
}
template <typename T>
std::string Tree<T>::in_order() {
  if (m_root == nullptr) {
    return "";
  }
  return _in_order(m_root);
}
template <typename T>
std::string _in_order(Node<T> *node) {
  if(node == nullptr){
    return "";
  }
  std::string order = _in_order(node->left);
  if(!order.empty()){
    order += " ";
  }
  order += my_to_string(node->element);
  if(node->right != nullptr){
    order += " ";
  }
  order += _in_order(node->right);
  return order;
}
template <typename T>
std::string Tree<T>::post_order() {
  if (m_root == nullptr) {
    return "";
  }
  return _post_order(m_root);
}
template <typename T>
std::string _post_order(Node<T> *node) {
  if(node == nullptr){
    return "";
  }
  std::string order = _post_order(node->left);
  if(!order.empty()){
    order += " ";
  }
  order += _post_order(node->right);
  if(node->right != nullptr){
    order += " ";
  }
  order += my_to_string(node->element);
  return order;
}
