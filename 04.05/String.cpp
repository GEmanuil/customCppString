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