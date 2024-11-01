#include "../include/array.h"
#include "../include/figure.h"
#include <utility>

template <typename T>
Array<T>::Array(size_t capacity) : size(0), capacity(capacity) {
    data = std::shared_ptr<T[]>(new T[capacity]);
}

template <typename T>
void Array<T>::resize(size_t new_capacity) {
    auto new_data = std::shared_ptr<T[]>(new T[new_capacity]);
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = std::move(data[i]);
    }
    data = std::move(new_data);
    capacity = new_capacity;
}

template <typename T>
void Array<T>::add(const T& element) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = element;
}

template <typename T>
T& Array<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
size_t Array<T>::getSize() const {
    return size;
}

template <typename T>
void Array<T>::remove(size_t index) {
    if (index < size) {
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }
}

template class Array<std::shared_ptr<Figure<int>>>;
template class Array<std::shared_ptr<Figure<double>>>;
