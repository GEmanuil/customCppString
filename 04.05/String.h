#pragma once
#include <iostream>

class String
{
public:
	String();
	String(const char* arr);
	String(const String& other);
	String& operator=(const String& other);
	void operator+=(const String& other);
	String operator+(const String& one) const;
	~String();

	int getStringSize() const;
	void erase();

	const char& operator[](const int& n) const;
	char& operator[](const int& n);

	friend std::ostream& operator<<(std::ostream& stream, const String& str);

private:
	char* string;
	unsigned stringSize;

	void free();
};

