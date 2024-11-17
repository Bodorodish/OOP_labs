#include "src/doubleLinkedList.cpp"
#include "src/memoryResource.cpp"
#include <iostream>
#include <string>

struct ComplexType {
    int id;
    double value;
    std::string name;
};

int main() {
    FixedBlockMemoryResource memoryResource(1024);
    DoubleLinkedList<int> intList(&memoryResource);
    
    intList.push(intList.begin(), 10);
    intList.push(intList.begin(), 20);
    intList.push(intList.begin(), 30);

    std::cout << "intList (from front): ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    intList.push(intList.end(), 40);
    intList.push(intList.end(), 50);

    std::cout << "intList (from back): ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    intList.pop(intList.begin());

    std::cout << "intList (after pop front): ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    DoubleLinkedList<ComplexType> complexList(&memoryResource);
    complexList.push(complexList.begin(), {1, 3.14, "example1"});
    complexList.push(complexList.end(), {2, 2.71, "example2"});
    std::cout << "complexList (from front): ";

    for (auto it = complexList.begin(); it != complexList.end(); it++) {
        std::cout << "{" << it->id << ", " << it->value << ", " << it->name << "} ";
    }
    std::cout << std::endl;
    return 0;
}
