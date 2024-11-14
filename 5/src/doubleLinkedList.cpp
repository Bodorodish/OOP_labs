#include "../include/doubleLinkedList.h"

template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(Node* node) : current_(node) {}

template <typename T>
T& DoubleLinkedList<T>::Iterator::operator*() const {
    return current_->data;
}

template <typename T>
T* DoubleLinkedList<T>::Iterator::operator->() {
    return &current_->data;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator++() {
    current_ = current_->next;
    return *this;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator--() {
    current_ = current_->prev;
    return *this;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool DoubleLinkedList<T>::Iterator::operator==(const Iterator& other) const {
    return current_ == other.current_;
}

template <typename T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current_ != other.current_;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(std::pmr::memory_resource* mr)
    : allocator_(mr), head_(nullptr), tail_(nullptr) {}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    while (head_) {
        Node* tmp = head_;
        head_ = head_->next;
        tmp->~Node();
        allocator_.deallocate(tmp, 1);  // Освобождаем один элемент
    }
    tail_ = nullptr;
}

template <typename T>
void DoubleLinkedList<T>::push_front(const T& value) {
    Node* newNode = allocator_.allocate(1);
    new(newNode) Node{value, head_, nullptr};  // Конструируем узел на выделенной памяти
    if (head_) {
        head_->prev = newNode;
    } else {
        tail_ = newNode;
    }
    head_ = newNode;
}

template <typename T>
void DoubleLinkedList<T>::push_back(const T& value) {
    Node* newNode = allocator_.allocate(1);
    new(newNode) Node{value, nullptr, tail_};  // Конструируем узел на выделенной памяти
    if (tail_) {
        tail_->next = newNode;
    } else {
        head_ = newNode;
    }
    tail_ = newNode;
}

template <typename T>
void DoubleLinkedList<T>::pop_front(){
    if (!head_) {
        throw std::out_of_range("List is empty");
    }

    Node* temp = head_;
    head_ = head_->next;
    if (head_) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }

    temp->~Node();                // Вызываем деструктор явно
    allocator_.deallocate(temp, 1);  // Освобождаем один элемент
}

template <typename T>
void DoubleLinkedList<T>::pop_back(){
    if (!tail_) {
        throw std::out_of_range("List is empty");
    }

    Node* temp = tail_;
    tail_ = tail_->prev;
    if (tail_) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }

    temp->~Node();                // Вызываем деструктор явно
    allocator_.deallocate(temp, 1);  // Освобождаем один элемент
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() {
    return Iterator(head_);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() {
    return Iterator(nullptr);
}

// Эксплицитные инстанцирования
template class DoubleLinkedList<int>;
