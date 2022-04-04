#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include <exception>

#define INIT_SIZE 10

/**
 * 顺序队列: 保留一个空单元, 以便判断队列空/满, 即rear所在单元始终为空
 */ 
template <typename T>
class Queue {
public:
    Queue() {
        data = new T[INIT_SIZE];
        queueFront = -1;
        queueRear = -1;
        queueCapacity = INIT_SIZE;
    }

    ~Queue() {
        if (data)
            delete[] data;
        data = nullptr;
    }

    bool empty() { return queueFront == -1; }
    int size() { return (queueRear - queueFront + queueCapacity) % queueCapacity; }
    int capacity() { return queueCapacity; }

    T front() {
        if (this->empty())
            throw "Queue is empty";
        return data[queueFront];
    }

    void clear() {
        queueFront = -1;
        queueRear = -1;
    }

    void push(T value) {
        if (this->size() == queueCapacity)
            throw "Queue is full";
        data[queueRear] = value;
        queueRear = (queueRear + 1) % queueCapacity;
    }

    void pop() {
        if (this->empty())
            throw "Queue is empty";
        queueRear = (queueRear - 1) % queueCapacity;
    }

private:
    T *data;
    int queueFront;
    int queueRear;
    int queueCapacity;
};

/**
 * 链式队列: 空间灵活
 */ 
template <typename T>
class Node {
public:
    Node(T value, Node *next = nullptr): value(value), next(next) {}
    Node *next;
    T value;
};

template <typename T>
class LinkedQueue {
public:
    LinkedQueue() {
        queueFront = nullptr;
        queueRear = nullptr;
    }

    ~LinkedQueue() {
        clear();
    }

    bool empty() { return queueFront == -1; }
    int size() { return queueSize; }

    T front() {
        if (this->empty())
            throw "Queue is empty";
        return queueFront->value;
    }

    void clear() {
        Node<T> *tmp = nullptr;
        while (queueFront != queueRear) {
            tmp = queueFront->next;
            delete queueFront;
        }
        if (queueRear)
            delete queueRear;
        queueFront = nullptr;
        queueRear = nullptr;
    }

    void push(T value) {
        queueRear->next = new Node<T>(value);
        queueRear = queueRear->next;
        ++queueSize;
    }

    void pop() {
        if (this->empty())
            throw "Queue is empty";
        Node<T> *tmp = queueFront;
        queueFront = queueFront->next;
        delete tmp;
        tmp = nullptr;
        --queueSize;
    }

private:
    Node<T> *queueFront;
    Node<T> *queueRear;
    int queueSize;
};

#endif