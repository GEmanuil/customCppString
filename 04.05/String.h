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



