#pragma once
#include <iostream>

template<typename T>
class LinkedQueue
{
    struct Node
    {
        T data;
        Node* next;

        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

public:
    LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

    LinkedQueue(const LinkedQueue& other)
    {
        copy(other);
    }

    LinkedQueue& operator=(const LinkedQueue& other)
    {
        if (this != &other)
        {
            free();
            copy(other);
        }
        return *this;
    }

    ~LinkedQueue()
    {
        free();
    }

    void enqueue(const T& data)
    {
        Node* newNode = new Node(data);
        if (rear)
        {
            rear->next = newNode;
        }
        else
        {
            front = newNode;
        }
        rear = newNode;
        size++;
    }

    void dequeue()
    {
        if (!front)
        {
            throw std::out_of_range("queue is empty");
        }

        Node* tmp = front;
        front = front->next;

        if (!front)
        {
            rear = nullptr;
        }

        size--;
        delete tmp;
    }

    const T& peek() const
    {
        if (!front)
        {
            throw std::out_of_range("queue is empty");
        }
        return front->data;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    std::size_t length() const
    {
        return size;
    }

private:

    void free()
    {
        while (front)
        {
            Node* tmp = front;
            front = front->next;
            delete tmp;
        }
        this->size = 0;
    }

    void copy(const LinkedQueue& other)
    {

        Node* current = other.front;
        while (current)
        {
            enqueue(current->data);
            current = current->next;
        }
    }

    Node* front = nullptr;
    Node* rear = nullptr;
    std::size_t size;
};
