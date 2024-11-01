#include "../include/figure.h"

template <typename T>
Figure<T>::operator double() const {
    return area();
}

template <typename T>
bool Figure<T>::operator<(const Figure<T>& other) const {
    return area() < other.area();
}

template <typename T>
bool Figure<T>::operator>(const Figure<T>& other) const {
    return area() > other.area();
}

template class Figure<int>;
template class Figure<double>;
