#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <exception>
using namespace std;

#define INITSIZE 10

// 顺序栈, 数组实现
template <typename T>
class Stack {
public:
    Stack() { 
        stackTop = -1;
        stackCapacity = INITSIZE;
        data = new T[INITSIZE];
    }
    ~Stack() {}
    bool empty() { return stackTop == -1; }
    int size() { return stackTop + 1; }
    int capacity() { return stackCapacity; }

    T top() {
        if (this->empty())
            throw "Stack is empty";
        return data[stackTop];
    }

    void clear() {
        stackTop = -1;
    }

    void push(T value) {
        if (stackTop + 1 == stackCapacity)
            expand();
        data[++stackTop] = value;
    }

    void pop() {
        if (this->empty())
            throw "Stack is empty";
        if (stackTop == stackCapacity / 2)
            shrink();
        --stackTop;
    }

private:
    T *data;
    int stackCapacity;
    int stackTop;

    void expand() {
        T *tmp = data;
        data = new T[stackCapacity * 2];
        for (int i = 0; i <= stackTop; i++)
            data[i] = tmp[i];
        stackCapacity *= 2;
        delete[] tmp;
    }

    void shrink() {
        if (stackCapacity / 2 < INITSIZE)
            return;
        T *tmp = data;
        data = new T[stackCapacity / 2];
        for (int i = 0; i <= stackTop; i++)
            data[i] = tmp[i];
        stackCapacity /= 2;
        delete[] tmp;
    }
};

// 链表栈
template <typename T>
class Node {
public:
    Node(T value, Node *next = nullptr): value(value), next(next) {}
    Node *next;
    T value;
};

template <typename T>
class LinkedStack {
public:
    LinkedStack() { 
        stackTop = nullptr;
    }
    ~LinkedStack() {}
    bool empty() { return stackTop == nullptr; }
    int size() { return stackSize; }

    T top() {
        if (this->empty())
            throw "Stack is empty";
        return stackTop->value;
    }

    void clear() {
        Node<T> *tmp = nullptr;
        while (stackTop != nullptr) {
            tmp = stackTop->next;
            delete stackTop;
            stackTop = tmp;
        }
    }

    void push(T value) {
        Node<T> *front = new Node<T>(value, stackTop);
        stackTop = front;
        ++stackSize;
    }

    void pop() {
        if (this->empty())
            throw "Stack is empty";
        Node<T> *tmp = stackTop;
        stackTop = stackTop->next;
        delete tmp;
        --stackSize;
    }
private:
    Node<T> *stackTop;
    int stackSize;
};

#endif