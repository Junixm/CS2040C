#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <initializer_list>
#include <string>

template <typename T> struct Node {
    T element;
    Node<T>* next;
};

template <typename T> class List {
private:
    size_t m_size;
    Node<T>* m_head;

public:
    List();

    List(std::initializer_list<T> init_list);

    List(const List<T>& other);

    ~List();

    const T& head();

    bool empty() const;

    size_t size() const;

    void push_head(const T& element);

    void pop_head();

    bool contains(const T& element) const;

    T extract_max();

    void reverse();

    template <typename U> std::string convert_string(const U element) const;

    std::string convert_string(const std::string element) const;

    std::string convert_string(const char element) const;

    std::string to_string() const;

};

template <typename T> List<T>::List() : m_size{ 0 }, m_head{ nullptr } {}

template <typename T> List<T>::List(std::initializer_list<T> init_list) : m_size{ 0 }, m_head{ nullptr } {
    auto it = init_list.end();
    while (--it != init_list.begin()) {
        push_head(*it);
    }
    push_head(*it);
}

template <typename T> List<T>::List(const List<T>& other) : m_size{ 0 }, m_head{ nullptr } {
    Node<T>* current = other.m_head;
    while (current != nullptr) {
        push_head(current->element);
        current = current->next;
    }
}

template <typename T> List<T>::~List() {
    Node<T>* current = m_head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

// Returns the contents of the head node
template <typename T> const T& List<T>::head() {
    if (m_size <= 0) {
        throw std::out_of_range("List is empty");
    }
    return m_head->element;
}

// Checks whether the container is empty
template <typename T> bool List<T>::empty() const { return m_size == 0; }

// Returns the number of elements
template <typename T> size_t List<T>::size() const { return m_size; }

// Inserts an element to the head
template <typename T> void List<T>::push_head(const T& element) {
    Node<T>* node = new Node<T>{ element, m_head };
    m_head = node;
    m_size++;
}

// Removes the head element
template <typename T> void List<T>::pop_head() {
    if (m_size <= 0) {
        throw std::out_of_range("List is empty");
    }
    Node<T>* node = m_head;
    m_head = m_head->next;
    delete node;
    m_size--;
}

// Checks whether the container contains the specified element
template <typename T> bool List<T>::contains(const T& element) const {
    for (Node<T>* node = m_head; node != nullptr; node = node->next) {
        if (node->element == element) {
            return true;
        }
    }
    return false;
}

// Extracts the maximum element from the container
template <typename T> T List<T>::extract_max() {
    if (m_head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    Node<T>* node = m_head->next;
    T max = m_head->element;
    while (node != nullptr) {
        if (node->element > max) {
            max = node->element;
        }
        node = node->next;
    }
    return max;
}

// Reverse the container
template <typename T> void List<T>::reverse() {
    Node<T>* current = m_head;
    Node<T>* previous = nullptr;
    Node<T>* next = nullptr;
    while (current != nullptr) {
        //set next node
        next = current->next;
        //point current node to previous node
        current->next = previous;
        //set current node as previous
        previous = current;
        //go to next node
        current = next;
    }
    m_head = previous;
}

template <typename T> template <typename U> std::string List<T>::convert_string(const U element) const {
    return std::to_string(element);
}

template <typename T> std::string List<T>::convert_string(const std::string element) const {
    return "\"" + element + "\"";
}

template <typename T> std::string List<T>::convert_string(const char element) const {
    std::string result = "\"";
    result += element;
    result += "\"";
    return result;
}

// Returns a std::string equivalent of the container
template <typename T> std::string List<T>::to_string() const {
    std::string result = "{";
    for (Node<T>* node = m_head; node != nullptr; node = node->next) {
        result += convert_string(node->element);
        if (node->next != nullptr) {
            result += ", ";
        }
    }
    result += "}";
    return result;
}

#endif