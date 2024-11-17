#include "../include/trapezoid.h"

template <typename T>
bool Trapezoid<T>::isValid(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) const {
    auto areParallel = [](const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
        T deltaX1 = p2.x - p1.x;
        T deltaY1 = p2.y - p1.y;
        T deltaX2 = p4.x - p3.x;
        T deltaY2 = p4.y - p3.y;

        return (deltaX1 * deltaY2) == (deltaY1 * deltaX2);
    };

    return (areParallel(a, b, c, d) || areParallel(a, d, b, c)) && 
           !areParallel(a, b, b, c) && 
           !areParallel(c, d, d, a);
}

template <typename T>
Trapezoid<T>::Trapezoid(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
    if (!isValid(a, b, c, d)) {
        throw std::invalid_argument("Введённые точки не образуют трапецию");
    }
    p1 = std::make_unique<Point<T>>(a);
    p2 = std::make_unique<Point<T>>(b);
    p3 = std::make_unique<Point<T>>(c);
    p4 = std::make_unique<Point<T>>(d);
}

template <typename T>
Trapezoid<T>::Trapezoid(const Trapezoid<T>& other)
    : p1(std::make_unique<Point<T>>(*other.p1)), p2(std::make_unique<Point<T>>(*other.p2)),
      p3(std::make_unique<Point<T>>(*other.p3)), p4(std::make_unique<Point<T>>(*other.p4)) {}

template <typename T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid<T>& other) {
    if (this != &other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
    }
    return *this;
}

template <typename T>
double Trapezoid<T>::area() const {
    double area = 0.5 * std::abs(
        p1->x * p2->y + p2->x * p3->y + p3->x * p4->y + p4->x * p1->y -
        (p2->x * p1->y + p3->x * p2->y + p4->x * p3->y + p1->x * p4->y)
    );
    return area;
}

template <typename T>
Point<double> Trapezoid<T>::center() const {
    T centerX = (p1->x + p2->x + p3->x + p4->x) / 4;
    T centerY = (p1->y + p2->y + p3->y + p4->y) / 4;
    return Point<double>(centerX, centerY);
}

template <typename T>
void Trapezoid<T>::print() const {
    std::cout << "Trapezoid: ";
    p1->print(); std::cout << ", ";
    p2->print(); std::cout << ", ";
    p3->print(); std::cout << ", ";
    p4->print(); std::cout << " Area: " << area() << std::endl;
}


template class Trapezoid<double>;
template class Trapezoid<int>;