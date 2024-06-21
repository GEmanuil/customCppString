#include "String.h"

String::String()
{
	string = new char[1];
	string[0] = '\0';
	stringSize = 0;
}

String::String(const char* arr)
{
	stringSize = strlen(arr);
	string = new char[stringSize + 1];
	for (int i = 0; i < stringSize; i++)
	{
		string[i] = arr[i];
	}
	string[stringSize] = '\0';
}

String::String(const String& other) : stringSize(other.stringSize)
{
	this->string = new char[stringSize + 1];
	for (int i = 0; i < stringSize + 1; i++)
	{
		string[i] = other.string[i];
	}
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		this->stringSize = other.stringSize;
		this->string = new char[stringSize + 1];

		for (int i = 0; i < stringSize + 1; i++)
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
	return stringSize;
}

void String::erase()
{
	free();
	stringSize = 0;
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

	return String(arr);
}

const char& String::operator[](const int& n) const
{
	return string[n];
}

char& String::operator[](const int& n)
{
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