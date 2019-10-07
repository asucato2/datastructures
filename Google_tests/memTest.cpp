//
// Created by ansucato on 9/10/19.
//

#include <iostream>
#include "../DynamicCircularArray_lib/CircularDynamicArray.h"

int main()
{
    CircularDynamicArray<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.addFront(i);
    }
    std::cout << a.quickSelect(9) << std::endl;
    std::cout << a.WCSelect(9) << std::endl;

}
