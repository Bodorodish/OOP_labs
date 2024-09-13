#include <iostream>
#include "include/converter.h"

int main(){
    int num;
    std::cin >> num;
    std::cout << "Num: " << num << ", string: " << FromIntToString(num) << '\n';
    return 0;
}