#include "../include/rectangle.h"

template <typename T>
bool Rectangle<T>::isValidRectangle(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) const {
    auto vector = [](const Point<T>& p1, const Point<T>& p2) {
        return std::make_pair(p2.x - p1.x, p2.y - p1.y);
    };

    auto dotProduct = [](const std::pair<T, T>& v1, const std::pair<T, T>& v2) {
        return v1.first * v2.first + v1.second * v2.second;
    };

    auto vecAB = vector(a, b);
    auto vecBC = vector(b, c);
    auto vecCD = vector(c, d);
    auto vecDA = vector(d, a);

    bool rightAngles = (dotProduct(vecAB, vecBC) == 0) &&
                       (dotProduct(vecBC, vecCD) == 0) &&
                       (dotProduct(vecCD, vecDA) == 0) &&
                       (dotProduct(vecDA, vecAB) == 0);

    auto lengthSquared = [](const std::pair<T, T>& v) {
        return v.first * v.first + v.second * v.second;
    };

    bool oppositeSidesEqual = (lengthSquared(vecAB) == lengthSquared(vecCD)) &&
                              (lengthSquared(vecBC) == lengthSquared(vecDA));

    return rightAngles && oppositeSidesEqual;
}

template <typename T>
Rectangle<T>::Rectangle(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
    if (!isValidRectangle(a, b, c, d)) {
        throw std::invalid_argument("Введённые точки не образуют прямоугольник");
    }
    p1 = std::make_unique<Point<T>>(a);
    p2 = std::make_unique<Point<T>>(b);
    p3 = std::make_unique<Point<T>>(c);
    p4 = std::make_unique<Point<T>>(d);
}
    
template <typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& other)
    : p1(std::make_unique<Point<T>>(*other.p1)), p2(std::make_unique<Point<T>>(*other.p2)),
      p3(std::make_unique<Point<T>>(*other.p3)), p4(std::make_unique<Point<T>>(*other.p4)) {}

template <typename T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& other) {
    if (this != &other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
    }
    return *this;
}

template <typename T>
double Rectangle<T>::area() const {
    double width = std::sqrt((p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y));
    double height = std::sqrt((p4->x - p1->x) * (p4->x - p1->x) + (p4->y - p1->y) * (p4->y - p1->y));
    return width * height;
}

template <typename T>
Point<double> Rectangle<T>::center() const {
    double centerX = (p1->x + p2->x + p3->x + p4->x) / 4;
    double centerY = (p1->y + p2->y + p3->y + p4->y) / 4;
    return Point<double>(centerX, centerY);
}

template <typename T>
void Rectangle<T>::print() const {
    std::cout << "Rectangle: ";
    p1->print(); std::cout << ", ";
    p2->print(); std::cout << ", ";
    p3->print(); std::cout << ", ";
    p4->print(); std::cout << " Area: " << area() << std::endl;
}


template class Rectangle<double>;
template class Rectangle<int>;