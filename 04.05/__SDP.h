#pragma once

template<typename T>
class DoublyLinkedList
{
	struct Node
	{
		Node(T data = T{}, Node* next = nullptr, Node* prev = nullptr) : data(data) {}
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& other);
	DoublyLinkedList& operator=(const DoublyLinkedList& other);
	~DoublyLinkedList();

	void push_front(const T& data);
	void remove_front();
	void push_back(const T& data);
	void remove_back();
	T at(size_t pos) const;

	bool isEmpty() const;
	size_t length() const;

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size;

	void copy(const DoublyLinkedList& other);
	void free();
};

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList() : size(0)
{
}

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
{
	copy(other);
}

template<typename T>
inline DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template<typename T>
inline DoublyLinkedList<T>::~DoublyLinkedList()
{
	free();
}

template<typename T>
inline void DoublyLinkedList<T>::push_front(const T& data)
{
	if (head)
	{
		Node* newNode = new Node(data);
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	else
	{
		head = new Node(data);
		tail = head;
	}
	size++;
}

template<typename T>
inline void DoublyLinkedList<T>::remove_front()
{
	if (head)
	{
		Node* h = head;
		head = head->next;
		size--;
		delete h;

		if (head) head->prev = nullptr;
		else tail = nullptr;
	}

	if (!head) tail = nullptr;
	if (!tail) head = nullptr;

}

template<typename T>
inline void DoublyLinkedList<T>::push_back(const T& data)
{
	if (tail)
	{
		Node* newNode = new Node(data);
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	else
	{
		head = new Node(data);
		tail = head;
	}
	size++;
}

template<typename T>
inline void DoublyLinkedList<T>::remove_back()
{
	if (tail)
	{
		Node* h = tail;
		tail = tail->prev;
		size--;
		delete h;

		if (tail) tail->next = nullptr;
		else head = nullptr;
	}

	if (!head) tail = nullptr;
	if (!tail) head = nullptr;
}

template<typename T>
inline T DoublyLinkedList<T>::at(size_t pos) const
{
	if (pos + 1 > size) throw std::out_of_range("bruh");

	Node* result = nullptr;
	if (size / 2 > pos)
	{
		result = head;
		Node* node = head;
		for (int i = 0; i < pos; i++)
		{
			result = node->next;
			node = node->next;
		}
	}
	else
	{
		result = tail;
		Node* node = tail;
		for (int i = size - 1; i > pos; i--)
		{
			result = node->prev;
			node = node->prev;
		}
	}

	return result->data;
}

template<typename T>
inline bool DoublyLinkedList<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
inline size_t DoublyLinkedList<T>::length() const
{
	return size;
}

template<typename T>
inline void DoublyLinkedList<T>::copy(const DoublyLinkedList& other)
{
	this->size = other.size;
	if (other->head)
	{
		head = new Node(*(other.head));
		Node* newNode = head;
		try
		{
			while (newNode->next)
			{
				Node* next = new Node(*(newNode->next));
				newNode->next = next;
				next->prev = newNode;
				newNode = next;
			}
		}
		catch (...)
		{
			free();
			throw;
		}


		tail = newNode;
	}
	
}

template<typename T>
inline void DoublyLinkedList<T>::free()
{
	if (head)
	{
		Node* nd = head;
		while (nd)
		{
			Node* next = nd->next;
			delete nd;
			nd = next;
		}
	}
	head = tail = nullptr;
	size = 0;
}




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

#pragma once
#include <iostream>


template<typename T>
class PriorityQueue
{
    typedef bool (*func)(T&, T&);

    struct Node
    {
        T data;
        Node* next;

        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

public:
    PriorityQueue(func f) : front(nullptr), rear(nullptr), size(0), f(f) {}

    PriorityQueue(const PriorityQueue& other)
    {
        copy(other);
    }

    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this != &other)
        {
            free();
            copy(other);
        }
        return *this;
    }

    ~PriorityQueue()
    {
        free();
    }

    void enqueue(const T& data)
    {
        Node* newNode = new Node(data);

        // Case 1: Empty queue
        if (!front)
        {
            front = rear = newNode;
            size++;
            return;
        }

        // Case 2: Insert at the front (highest priority)
        if (f(newNode->data, front->data))
        {
            newNode->next = front;
            front = newNode;
            size++;
            return;
        }

        // Case 3: Insert in the middle or at the end
        Node* prev = front;
        Node* current = front->next;

        while (current && !f(newNode->data, current->data))
        {
            prev = current;
            current = current->next;
        }

        // Insert the new node
        newNode->next = current;
        prev->next = newNode;

        // Update rear if inserted at the end
        if (!current)
        {
            rear = newNode;
        }

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

    void copy(const PriorityQueue& other)
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

    func f;
};

