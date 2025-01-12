#pragma once
#include <iostream>

template<typename T>
class DynamicArray
{
public:
	explicit DynamicArray(int initialCapacity = 16);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);
	~DynamicArray();

	int getSize() const;
	bool isEmpty() const;

	T& operator[](int index);
	const T& operator[](int index) const;

	T get(int index) const;
	void push_back(const T& element);
	void pop_back();

	bool contains(const T& elem) const;
private:
	size_t size, capacity;
	T* data = nullptr;

	void resize();
	void ensureSize(int size);
	int getCapacity() const;

	T* allocateArray(size_t capacity);
	void copyElements(T* destination);
	void finalizeResize(T* tempData, size_t newCapacity);
};

template<typename T>
inline DynamicArray<T>::DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity)
{
	if (initialCapacity <= 0)
	{
		throw std::invalid_argument("Illegal initial size");
	}
	data = allocateArray(capacity);
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity), data(nullptr)
{
	T* temp = allocateArray(capacity);
	try 
	{
		for (int i = 0; i < other.size; i++)
		{
			temp[i] = other.data[i];
		}
	}
	catch (...) 
	{
		delete[] temp;
		throw;
	}
	data = temp;
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (this != &other)
	{
		T* temp = allocateArray(other.capacity);
		try 
		{
			for (size_t i = 0; i < other.size; ++i) 
			{
				temp[i] = other.data[i];
			}
		}
		catch (...) 
		{
			delete[] temp;
			throw;
		}

		delete[] data;
		data = temp;
		size = other.size;
		capacity = other.capacity;
	}
	return *this;
}

template<typename T>
inline DynamicArray<T>::~DynamicArray()
{
	delete[] data;
}

template<typename T>
inline int DynamicArray<T>::getSize() const
{
	return this->size;
}

template<typename T>
inline int DynamicArray<T>::getCapacity() const
{
	return this->capacity;
}

template<typename T>
inline bool DynamicArray<T>::isEmpty() const
{
	return getSize() == 0;
}

template<typename T>
inline T& DynamicArray<T>::operator[](int index)
{
	if (index >= size)
	{
		throw std::invalid_argument("Illigal index");
	}
	return data[index];
}

template<typename T>
inline const T& DynamicArray<T>::operator[](int index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Illigal index");
	}
	return data[index];
}

template<typename T>
inline T DynamicArray<T>::get(int index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Index too big\n");
	}
	
	return data[index];
}

template<typename T>
inline void DynamicArray<T>::push_back(const T& element)
{
	if (size + 1 > capacity)
	{
		resize();
	}
	data[size++] = element;
}

template<typename T>
inline void DynamicArray<T>::pop_back()
{
	if (size == 0)
	{
		throw std::out_of_range("pop_back called on an empty array");
	}
	size--;
}

template<typename T>
inline void DynamicArray<T>::resize()
{
	int newCapacity = capacity * 2;
	T* temp = allocateArray(newCapacity);
	copyElements(temp);
	finalizeResize(temp, newCapacity);
}

template<typename T>
inline void DynamicArray<T>::ensureSize(int size)
{
	if (capacity >= size) return;
	if (size < capacity * 2) 
	{
		resize();
		return;
	}

	T* copy = new T[size];
	for (int i = 0; i < this->size; i++)
	{
		copy[i] = this->data[i];
	}

	this->capacity = size;
	delete[] this->data;
	data = copy;
}

template<typename T>
inline bool DynamicArray<T>::contains(const T& elem) const
{
	for (int i = 0; i < size; i++) 
	{
		if (elem == data[i]) 
		{
			return true;
		}
	}
	return false;
}

template <typename T>
T* DynamicArray<T>::allocateArray(size_t capacity) 
{
	return new T[capacity];
}

template <typename T>
void DynamicArray<T>::copyElements(T* destination) 
{
	for (size_t i = 0; i < size; ++i) 
	{
		destination[i] = data[i];
	}
}

template <typename T>
void DynamicArray<T>::finalizeResize(T* tempData, size_t newCapacity) 
{
	delete[] data;
	data = tempData;
	capacity = newCapacity;
}





class String
{
public:
	String();
	String(const char* array);
	String(const String& other);
	String& operator=(const String& other);
	~String();

	void erase();
	int getStringSize() const;
	void resize(int size);

	const char* getStringPointer() const;

	char& operator[](const int& n);
	const char& operator[](const int& n) const;
	bool operator==(const String& other) const;
	bool operator!=(const String& other) const;

	friend std::ostream& operator<<(std::ostream& stream, const String& str);
	friend std::istream& operator>>(std::istream& stream, String& str);

private:
	char* string = nullptr;
	size_t size;

	void free();
};

#include "String.h"

String::String()
{
	string = new char[1];
	string[0] = '\0';
	size = 0;
}

String::String(const char* arr)
{
	size = strlen(arr);
	string = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		string[i] = arr[i];
	}
	string[size] = '\0';
}

String::String(const String& other) : size(other.size)
{
	this->string = new char[size + 1];
	for (int i = 0; i < size + 1; i++)
	{
		string[i] = other.string[i];
	}
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		char* temp = new char[other.size + 1];
		for (int i = 0; i < other.size + 1; i++) 
		{
			temp[i] = other.string[i];
		}
		free();
		string = temp;
		size = other.size;
	}
	return *this;
}

String::~String()
{
	free();
}

int String::getStringSize() const
{
	return size;
}

void String::resize(int size)
{
	if (size < 0) 
	{
		throw std::invalid_argument("Size cannot be negative");
	}


	char* newString = new char[size + 1]; 
	int copySize = (size < this->size) ? size : this->size;
	for (int i = 0; i < copySize; i++) 
	{
		newString[i] = string[i];
	}


	for (int i = copySize; i < size; i++) 
	{
		newString[i] = '\0';
	}
	newString[size] = '\0';

	delete[] string;
	string = newString;
	this->size = size;
}

const char* String::getStringPointer() const
{
	return this->string;
}

void String::erase()
{
	char* temp = new char[1];
	temp[0] = '\0';
	free();
	string = temp;
	size = 0;
}

const char& String::operator[](const int& n) const
{
	if (n < 0 || n >= getStringSize()) throw std::out_of_range("index out of range");
	return string[n];
}

bool String::operator==(const String& other) const
{
	if (size != other.size) return false;
	for (int i = 0; i < size; i++) 
	{
		if (string[i] != other.string[i]) return false;
	}
	return true;
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

char& String::operator[](const int& n)
{
	if (n < 0 || n >= getStringSize()) throw std::out_of_range("index out of range");
	return string[n];
}

void String::free()
{
	delete[] string;
}

std::ostream& operator<<(std::ostream& stream, const String& str)
{
	stream << str.string;
	return stream;
}

std::istream& operator>>(std::istream& stream, String& str)
{
	char buffer[1024];
	stream >> buffer;

	int newSize = strlen(buffer);
	char* temp = new char[newSize + 1];

	for (int i = 0; buffer[i] != '\0'; i++) 
	{
		temp[i] = buffer[i];
	}
	temp[newSize] = '\0';

	str.free();
	str.string = temp;
	str.size = newSize;

	return stream;
}

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
	void remove_at(size_t pos);

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
inline DoublyLinkedList<T>::DoublyLinkedList() : size(0) {}

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
{
	try
	{
		copy(other);
	}
	catch (std::runtime_error& e)
	{
		free();
		throw e;
	}
}

template<typename T>
inline DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
	if (this != &other)
	{
		free();
		try
		{
			copy(other);
		}
		catch (std::runtime_error& e)
		{
			free();
			throw e;
		}
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
	if (pos + 1 > size) throw std::out_of_range("index out of bound");

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
inline void DoublyLinkedList<T>::remove_at(size_t pos)
{
	if (pos + 1 > size) throw std::out_of_range("index out of bound");

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

	// if result is not the head or the tail
	if (result != head && result != tail)
	{
		result->prev->next = result->next;
		result->next->prev = result->prev;
	}
	// We do that if the result alligns with the head
	if (result == head)
	{
		head = result->next;
		if (head)
		{
			head->prev = nullptr;
		}
	}
	// We do that if the result alligns with the tail
	if (result == tail)
	{
		tail = result->prev;
		if (tail)
		{
			tail->next = nullptr;
		}
	}

	delete result;
	--size;
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
	if (other.head)
	{
		head = new (std::nothrow) Node(*(other.head));
		if (!head)
		{
			throw std::runtime_error("unable to allocate memory for a new node");
		}

		Node* newNode = head;
		while (newNode->next)
		{
			Node* next = new (std::nothrow) Node(*(newNode->next));
			if (!next)
			{
				throw std::runtime_error("unable to allocate memory for a new node");
			}
			newNode->next = next;
			next->prev = newNode;
			newNode = next;
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
template<typename T>
inline PriorityQueue<T>::PriorityQueue(func f) : front(nullptr), rear(nullptr), size(0), f(f) {}

template<typename T>
inline PriorityQueue<T>::PriorityQueue(const PriorityQueue& other)
{
    try
    {
        copy(other);
    }
    catch (std::runtime_error&)
    {
        free();
        throw;
    }
}

template<typename T>
inline PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& other)
{
    if (this != &other)
    {
        try
        {
            copy(other);
        }
        catch (std::runtime_error&)
        {
            free();
            throw;
        }
    }
    return *this;
}

template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
    free();
}

template<typename T>
inline void PriorityQueue<T>::enqueue(const T& data)
{
    Node* newNode = new (std::nothrow) Node(data);
    if (!newNode)
    {
        throw std::runtime_error("unable to allocate new memory of the queue");
    }

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

    // Case 3: Insert in the somewhere in the middle or at the end
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

template<typename T>
inline void PriorityQueue<T>::dequeue()
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

template<typename T>
inline const T& PriorityQueue<T>::peek() const
{
    if (!front)
    {
        throw std::out_of_range("queue is empty");
    }
    return front->data;
}

template<typename T>
inline bool PriorityQueue<T>::isEmpty() const
{
    return size == 0;
}

template<typename T>
inline std::size_t PriorityQueue<T>::length() const
{
    return size;
}

template<typename T>
inline void PriorityQueue<T>::free()
{
    while (front)
    {
        Node* tmp = front;
        front = front->next;
        delete tmp;
    }
    this->size = 0;
}

template<typename T>
inline void PriorityQueue<T>::copy(const PriorityQueue& other)
{
    this->front = nullptr;
    this->rear = nullptr;
    f = other.f;
    Node* current = other.front;
    while (current)
    {
        enqueue(current->data);
        current = current->next;
    }
}

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
