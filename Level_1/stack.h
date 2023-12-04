// stack.h
#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& value);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;
};

// Include the implementation file
#include "stack.cpp"

#endif // STACK_H

