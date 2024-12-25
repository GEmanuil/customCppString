#pragma once
#include <iostream>

template<typename T>
class LinkedStack
{
	struct Node
	{
		T data = T{};
		Node* next = nullptr;
	};

public:

    LinkedStack() : top(nullptr), size(0) {}

    LinkedStack(const LinkedStack& other)
    {
        copy(other);
    }

    LinkedStack& operator=(const LinkedStack& other) 
    {

        if (this != &other) 
        {
            free();
            copy(other);
        }
        return *this;
    }

    ~LinkedStack() 
    {
        free();
    }

    void push(const T& data) 
    {
        try {
            Node* newNode = new Node{ data, top };
            top = newNode;
            size++;
        }
        catch (const std::bad_alloc&) {
            throw std::runtime_error("Failed to allocate memory for the new node.");
        }
    }

    void pop() 
    {
        if (!top) 
        {
            throw std::out_of_range("stack is empty");
        }

        Node* tmp = top;
        top = top->next;
        delete tmp;

        size--;
    }

    const T& peek() const 
    {
        if (!top) 
        {
            throw std::out_of_range("stack is empty");
        }

        return top->data;
    }

    size_t length() const
    {
        return size;
    }

    bool isEmpty() const 
    {
        return size == 0;
    }

private:


    void free() 
    {
        while (top)
        {
            Node* tmp = top;
            top = top->next;
            delete tmp;
        }
        size = 0;
    }
    
    void copy(const LinkedStack& other)
    {
        if (other.isEmpty())
        {
            size = 0;
            return;
        }

        Node* current = other.top;
        Node* prev = nullptr;
        while (current)
        {
            Node* newNode = new Node{ current->data };
            if (!top) top = newNode;
            if (prev) prev->next = newNode;

            prev = newNode;
            current = current->next;
        }
        size = other.size;
    }

	Node* top = nullptr;
	std::size_t size;
};
