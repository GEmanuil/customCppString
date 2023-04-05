#pragma once
class String
{
public:
	String();
	String(const char* arr);
	String(const String& str);
	String& operator=(const String& other);
	~String();

	void setLenght(size_t);
	void copy(const char* arr);
	void concat(const char* arr);
	void erase();
	void print();

	size_t getLenght();
private:
	char* str;
	size_t lenght;
};

