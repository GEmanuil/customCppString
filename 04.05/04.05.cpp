#include <iostream>
#include "String.h"
#include <crtdbg.h>

int main()
{ 
    String string = "I like ";
    string += "pizza";
    String str3;
    std::cout << string;
}
