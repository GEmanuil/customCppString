#include <iostream>
#include "String.h"
#include <crtdbg.h>

int main()
{ 
    {
        String string = "I like ";

        String str3 = string + "pizza";
        std::cout << str3;
    }
    _CrtDumpMemoryLeaks();
  
}
