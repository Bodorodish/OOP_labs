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
    if (current_) {
        current_ = current_->next;
    }
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
    if (current_) {
        current_ = current_->prev;
    }
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
void DoubleLinkedList<T>::push(const Iterator& it, const T& value) {
    Node* newNode = allocator_.allocate(1);
    new(newNode) Node{value, it.current_, nullptr}; // Создаём новый узел

    if (!it.current_) { // Если итератор указывает на конец
        if (tail_) {
            tail_->next = newNode;
        } else {
            head_ = newNode;
        }
        newNode->prev = tail_;
        tail_ = newNode;
    } else {
        newNode->prev = it.current_->prev;
        newNode->next = it.current_;
        if (it.current_->prev) {
            it.current_->prev->next = newNode;
        } else {
            head_ = newNode;
        }
        it.current_->prev = newNode;
    }
}

template <typename T>
void DoubleLinkedList<T>::pop(const Iterator& it) {
    if (!it.current_) {
        throw std::out_of_range("Invalid iterator");
    }

    Node* nodeToDelete = it.current_;

    if (nodeToDelete->prev) {
        nodeToDelete->prev->next = nodeToDelete->next;
    } else {
        head_ = nodeToDelete->next;
    }

    if (nodeToDelete->next) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    } else {
        tail_ = nodeToDelete->prev;
    }

    nodeToDelete->~Node();
    allocator_.deallocate(nodeToDelete, 1);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() {
    return Iterator(head_);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() {
    return Iterator(nullptr);
}

template class DoubleLinkedList<int>;
