#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

#define DEFAULTHEAPSIZE 1023

template <class T>
class Heap {
 protected:
  T* _heap;
  int _size;

 public:
  Heap() { 
    _heap = new T[DEFAULTHEAPSIZE];
    _size = 0;
  }

  int size() const {
    return _size;
  }

  bool empty() const {
    return _size == 0;
  }
  void insert(const T&);
  T extractMax();
  T peekMax() const;
  void printHeapArray() const;
  void printTree() const;
  void changeKey(const T& from, const T& to);
  void deleteItem(const T&);
  void bubbleUp(int child);
  void bubbleDown(int parent);
  void swap(int indexA, int indexB);
  int larger(int leftChild, int rightChild);

  ~Heap() { delete[] _heap; };
};

template <class T>
void Heap<T>::swap(int indexA, int indexB){
    T temp = _heap[indexB];
    _heap[indexB] = _heap[indexA];
    _heap[indexA] = temp;
}

template <class T>
void Heap<T>::bubbleUp(int child){
  if(child == 0){
    return;
  }
  int parent = (child - 1) / 2;
  while(child != 0 && _heap[child] > _heap[parent]){
    swap(child, parent);
    child = parent;
    parent = (child - 1) / 2;
  }
}

template <class T>
int Heap<T>::larger(int leftChild, int rightChild){
  if(leftChild >= _size){
    return -1;
  }
  if(rightChild >= _size || _heap[leftChild] > _heap[rightChild]){
    return leftChild;
  }
  return rightChild;
}

template <class T>
void Heap<T>::bubbleDown(int parent){
  int leftChild = (2 * parent) + 1;
  int rightChild = (2 * parent) + 2;
  int largerChild = larger(leftChild, rightChild);
  while(largerChild != -1 && _heap[largerChild] > _heap[parent]){
    swap(largerChild, parent);
    parent = largerChild;
    leftChild = (2 * parent) + 1;
    rightChild = (2 * parent) + 2;
    largerChild = larger(leftChild, rightChild);
  }
}

template <class T>
void Heap<T>::insert(const T& item) {
  if(_size == DEFAULTHEAPSIZE){
    throw std::out_of_range("Array is Full");
  }
  _heap[_size] = item;
  bubbleUp(_size);
  _size++;
}

template <class T>
T Heap<T>::extractMax() {
  if(_size == 0){
    throw std::out_of_range("Array is empty");
  }
  if(_size == 1){
    _size--;
    return _heap[0];
  }
  T max = _heap[0];
  _size--;
  _heap[0] = _heap[_size];
  bubbleDown(0);
  return max;
}

template <class T>
T Heap<T>::peekMax() const {
  if(_size == 0){
    throw std::out_of_range("Array is empty");
  }
  return _heap[0];
}

template <class T>
void Heap<T>::printHeapArray() const {
  for (int i = 0; i < size(); i++) {
    cout << _heap[i] << " ";
  }
  cout << endl;
}

template <class T>
void Heap<T>::changeKey(const T& from, const T& to) {
  int index = -1;
  for(int i = 0; i < _size ; i++){
    if(_heap[i] == from){
      index = i;
    }
  }
  if(index < 0){
    throw std::out_of_range("Not found");
  }

  _heap[index] = to;

  if(from > to){
    bubbleDown(index);
  } else{
    bubbleUp(index);
  }
}

template <class T>
void Heap<T>::deleteItem(const T& x) {
  T max = peekMax();
  changeKey(x, max);
  extractMax();
}

template <class T>
void Heap<T>::printTree() const {
  int parity = 0;
  if (size() == 0) return;
  int space = pow(2, 1 + (int)log2f(size())), i;
  int nLevel = (int)log2f(size()) + 1;
  int index = 0, endIndex;
  int tempIndex;

  for (int l = 0; l < nLevel; l++) {
    index = 1;
    parity = 0;
    for (i = 0; i < l; i++) index *= 2;
    endIndex = index * 2 - 1;
    index--;
    tempIndex = index;
    while (index < size() && index < endIndex) {
      for (i = 0; i < space - 1; i++) cout << " ";
      if (index == 0)
        cout << "|";
      else if (parity)
        cout << "\\";
      else
        cout << "/";
      parity = !parity;
      for (i = 0; i < space; i++) cout << " ";
      index++;
    }
    cout << endl;
    index = tempIndex;
    while (index < size() && index < endIndex) {
      for (i = 0; i < (space - 1 - ((int)log10(_heap[index]))); i++)
        cout << " ";
      cout << _heap[index];
      for (i = 0; i < space; i++) cout << " ";
      index++;
    }

    cout << endl;
    space /= 2;
  }
}

#endif
