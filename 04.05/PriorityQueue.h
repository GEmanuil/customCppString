#pragma once
#include <iostream>

template<typename T>
class PriorityQueue
{
    //typedef bool (*func)(T&, T&);
    using func = bool (*)(T&, T&);

    struct Node
    {
        T data;
        Node* next;

        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

public:
    PriorityQueue(func f);

    PriorityQueue(const PriorityQueue& other);

    PriorityQueue& operator=(const PriorityQueue& other);

    ~PriorityQueue();

    void enqueue(const T& data);

    void dequeue();

    const T& peek() const;

    bool isEmpty() const;

    std::size_t length() const;

private:

    void free();

    void copy(const PriorityQueue& other);

    Node* front = nullptr;
    Node* rear = nullptr;
    std::size_t size;

    func f;
};

#include "PriorityQueue.inl"

