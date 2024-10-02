#include <iostream>
#include "include/three.h"

int main(){
    Three a("1000");
    Three b("22");

    a -= b;

    a.print();
    return 0;
}