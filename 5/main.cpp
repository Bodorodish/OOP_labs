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
    
    intList.push_front(10);
    intList.push_front(20);
    intList.push_front(30);

    std::cout << "intList (from front): ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    intList.push_back(40);
    intList.push_back(50);

    std::cout << "intList (from back): ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    DoubleLinkedList<ComplexType> complexList(&memoryResource);
    complexList.push_front({1, 3.14, "example1"});
    complexList.push_back({2, 2.71, "example2"});

    std::cout << "complexList (from front): ";
    for (auto it = complexList.begin(); it != complexList.end(); ++it) {
        std::cout << "{" << it->id << ", " << it->value << ", " << it->name << "} ";
    }
    std::cout << std::endl;

    std::cout << "complexList (reverse): ";
    for (auto it = --complexList.end(); it != --complexList.begin(); --it) {
        std::cout << "{" << it->id << ", " << it->value << ", " << it->name << "} ";
    }
    std::cout << std::endl;
    
    return 0;
}
