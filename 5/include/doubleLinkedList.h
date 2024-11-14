#ifndef LIST_H
#define LIST_H

#include <memory_resource>
#include <iterator>

template <typename T>
class DoubleLinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* node);

        T& operator*() const;
        T* operator->();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* current_;
    };

    explicit DoubleLinkedList(std::pmr::memory_resource* mr = std::pmr::get_default_resource());
    ~DoubleLinkedList();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    
    Iterator begin();
    Iterator end();

private:
    std::pmr::polymorphic_allocator<Node> allocator_;
    Node* head_;
    Node* tail_;
};

#endif 
