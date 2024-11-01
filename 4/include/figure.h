#ifndef FIGURE
#define FIGURE

#include "point.h"
#include <iostream>

template <typename T>
class Figure {
static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type.");

public:
    virtual ~Figure() = default;
    virtual double area() const = 0;
    virtual void print() const = 0;
    virtual Point<double> center() const = 0;

    virtual std::shared_ptr<Figure<T>> clone() const = 0;

    operator double() const;
    bool operator<(const Figure<T>& other) const;
    bool operator>(const Figure<T>& other) const;
    friend std::ostream& operator<<(std::ostream& stream, const Figure<T>* obj) {
        if (obj) {
            obj->print();
        }
        return stream;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Figure<T>* obj) {
    if (obj) {
        obj->print();
    }
    return stream;
}

#endif // FIGURE
