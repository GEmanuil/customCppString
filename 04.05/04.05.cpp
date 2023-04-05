#include <iostream>
#include "String.h"

int main()
{ 
    String strin = "I like ";
    strin.concat(" hotdogs");
    strin.erase();
    std::cout << strin.getLenght();
}
