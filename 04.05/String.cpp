#include "String.h"

String::String()
{
	string = new (std::nothrow) char[1];
	if (!string) { std::cout << "memory problem"; exit(EXIT_FAILURE); };
	string[0] = '\0';
	stringSize = 0;

}

String::String(const char* arr)
{
	stringSize = strlen(arr);
	string = new (std::nothrow) char[stringSize + 1];
	if (!string) { std::cout << "memory problem"; exit(EXIT_FAILURE); }
	for (int i = 0; i < stringSize; i++)
	{
		string[i] = arr[i];
	}
	string[stringSize] = '\0';
}

String::String(const String& other) : stringSize(other.stringSize)
{
	this->string = new (std::nothrow) char[stringSize + 1];
	if (!string) { std::cout << "memory problem"; exit(EXIT_FAILURE); }
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
		this->string = new (std::nothrow) char[stringSize + 1];
		if (!string) { std::cout << "memory problem"; exit(EXIT_FAILURE); }
		for (int i = 0; i < stringSize + 1; i++)
		{
			string[i] = other.string[i];
		}
	}
	return *this;
}

void String::operator+=(const String& other)
{
	*this = *this + other;
}

String::~String()
{
	free();
}

const int String::getStringSize() const
{
	return stringSize;
}

String String::operator+(const String& other) const
{
	char* arr = new (std::nothrow) char[getStringSize() + other.getStringSize() + 1];
	if (!arr) { std::cout << "memory problem"; exit(EXIT_FAILURE); }
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
