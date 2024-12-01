#pragma once
#include <iostream>

class String
{
public:
	String();
	String(const char* array);
	String(const String& other);
	String& operator=(const String& other);
	void operator+=(const String& other);
	String operator+(const String& other) const;
	~String();

	void erase();
	int getStringSize() const;

	char& operator[](const int& n);
	const char& operator[](const int& n) const;

	friend std::ostream& operator<<(std::ostream& stream, const String& str);

private:
	char* string;
	unsigned size;

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
		free();
		size = other.size;
		string = new char[size + 1];

		for (int i = 0; i < size + 1; i++)
		{
			string[i] = other.string[i];
		}
	}
	return *this;
}

void String::operator+=(const String& other)
{
	//TODo here should be the main object and operator+ should call it
	*this = *this + other;
}

String::~String()
{
	free();
}

int String::getStringSize() const
{
	return size;
}

void String::erase()
{
	size = 0;
	free();
}

String String::operator+(const String& other) const
{
	char* arr = new char[getStringSize() + other.getStringSize() + 1];

	for (int i = 0; i < getStringSize(); i++)
	{
		arr[i] = string[i];
	}
	for (int i = 0; i < other.getStringSize() + 1; i++)
	{
		arr[getStringSize() + i] = other.string[i];
	}
	String result(arr);
	delete[] arr;

	return result;
}

const char& String::operator[](const int& n) const
{
	if (n > getStringSize()) throw std::out_of_range("index out of range");
	return string[n];
}

char& String::operator[](const int& n)
{
	if (n > getStringSize()) throw std::out_of_range("index out of range");
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


// TEMP VECTOR
#include <stdexcept>
template <typename T>
class Vector
{
public:
	Vector() = default;
	Vector(const Vector<T>& other);
	Vector& operator=(const Vector<T>& other);
	~Vector();

	T& operator[](unsigned index);
	const T& operator[](unsigned index) const;
	void push(const T& value);

	void clear();
	bool empty() const;

	void resize(unsigned newcapacity);
	void copy(const Vector<T>& other);

	unsigned getSize() const;
	unsigned getCapacity() const;

private:
	unsigned capacity = 0;
	unsigned size = 0;
	T* arrData = nullptr;
};

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copy(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] arrData;
}

template <typename T>
void Vector<T>::clear()
{
	delete[] arrData;
	arrData = nullptr;
	capacity = 0;
	size = 0;
}

template <typename T>
T& Vector<T>::operator[](unsigned index)
{
	if (index >= size) throw std::out_of_range("index error");
	return arrData[index];
}

template <typename T>
const T& Vector<T>::operator[](unsigned index) const
{
	if (index >= size) throw std::out_of_range("index error");
	return arrData[index];
}

template <typename T>
void Vector<T>::push(const T& value)
{
	if (size == capacity)
	{
		this->capacity += 1;
		this->capacity *= 2;
		resize(capacity);
	}
	arrData[size++] = value;
}

template <typename T>
bool Vector<T>::empty() const
{
	return !size;
}

template <typename T>
unsigned Vector<T>::getSize() const
{
	return size;
}

template <typename T>
unsigned Vector<T>::getCapacity() const
{
	return capacity;
}

template <typename T>
void Vector<T>::resize(unsigned newCapacity)
{
	T* newData = new T[newCapacity];
	for (int i = 0; i < getSize(); i++)
	{
		newData[i] = arrData[i];
	}
	delete[] arrData;;

	arrData = newData;
	capacity = newCapacity;
}

template <typename T>
void Vector<T>::copy(const Vector<T>& other)
{
	arrData = new T[other.capacity];
	size = other.size;
	capacity = other.capacity;
	for (int i = 0; i < other.size; i++)
	{
		arrData[i] = other.arrData[i];
	}
}
