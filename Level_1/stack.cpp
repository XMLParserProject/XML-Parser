// stack.cpp
#include "stack.h"

template <typename T>
void Stack<T>::push(const T& value) {
    elements.push_back(value);
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    elements.pop_back();
}

template <typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return elements.back();
}

template <typename T>
bool Stack<T>::empty() const {
    return elements.empty();
}

template <typename T>
size_t Stack<T>::size() const {
    return elements.size();
}
