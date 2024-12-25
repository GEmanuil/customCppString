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
