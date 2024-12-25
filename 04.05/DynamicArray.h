#pragma once
#include <iostream>

template<typename T>
class DynamicArray
{
public:
	DynamicArray(int initialCapacity = 16);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);
	~DynamicArray();

	int getSize() const;
	int getCapacity() const;
	bool isEmpty() const;

	// ednoto e za const obekti a drugoto za normalni
	T& operator[](int index);
	const T& operator[](int index) const;

	T get(int index) const;

	void resize();
	void ensureSize(int size);

	bool contains(const T& elem) const;
private:
	size_t size, capacity;
	T* data = nullptr;

};

template<typename T>
inline DynamicArray<T>::DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity)
{
	if (initialCapacity <= 0) 
	{
		throw std::invalid_argument("Illegal initial size");
	}

	this->data = new T[capacity];
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity)
{
	this->data = new T[capacity];
	for (int i = 0; i < size; i++)
	{
		this->data[i] = other.data[i];
	}
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (this != &other)
	{
		delete[] data;
		
		this->capacity = other.capacity;
		this->size = other.size;
		this->data = new T[capacity];

		for (int i = 0; i < size; i++)
		{
			this->data[i] = other.data[i];
		}
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
	if (index >= capacity)
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
		throw std::invalid_argument("Illigal index");
	}
	return data[index];
}

template<typename T>
inline T DynamicArray<T>::get(int index) const
{
	if (index < size)
	{
		return data[index];
	}

	// returns default T
	return T();
}

template<typename T>
inline void DynamicArray<T>::resize()
{
	// resizing with a capacity * 2

	T* copy = new T[capacity * 2];
	for (int i = 0; i < this->size; i++)
	{
		copy[i] = this->data[i];
	}

	this->capacity = this->capacity * 2;
	delete[] this->data;
	data = copy;
}

template<typename T>
inline void DynamicArray<T>::ensureSize(int size)
{
	if (capacity >= size) return;
	if (size < capacity * 2) {
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
	for (size_t i = 0; i < size; ++i) {
		if (elem == data[i]) {
			return true;
		}
	}
	return false;
}
