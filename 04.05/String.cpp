#include "String.h"
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)


String::String()
{
    copy("\0");
}

String::String(const char* arr)
{
	copy(arr);
}

String::String(const String& other)
{
    lenght = other.lenght;
    str = new char[strlen(other.str) + 1];
    strcpy(str, other.str);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {        
        lenght = other.lenght;
        delete[] str;
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }

    return *this;
}

void String::copy(const char* arr)
{
	str = new char [strlen(arr) + 1];
    setLenght(strlen(arr));
	strcpy(str, arr);
}

void String::concat(const char* arr)
{
    char* temp = new char[strlen(str) + 1];
    strcpy(temp, str);

    delete[] str;

    str = new char[lenght + strlen(arr) + 1];

    setLenght(strlen(str)); 
    strcpy(str, temp);      
    strcat(str, arr);       
}

void String::erase()
{
    delete[] str;
    str = nullptr;
    setLenght(0);
}

void String::print()
{
    std::cout << str;
}

size_t String::getLenght()
{
    return lenght;
}

String::~String()
{
	delete[] str;
}

void String::setLenght(size_t lenght)
{
    this->lenght = lenght;
}

