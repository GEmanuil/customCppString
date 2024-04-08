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


	const int getStringSize() const;

	//using this to access the string when the object String is const
	const char& operator[](const int& n) const;
	//using this as a lvalue
	char& operator[](const int& n);


private:
	char* string;
	size_t stringSize;

	void free();
};

