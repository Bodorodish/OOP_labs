#ifndef RHOMBUS
#define RHOMBUS

#include "figure.h"

template <typename T>
class Rhombus : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4;

    bool isValid(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) const override;

public:
    Rhombus(Point<T> a = Point<T>(), Point<T> b = Point<T>(), Point<T> c = Point<T>(), Point<T> d = Point<T>());
    Rhombus(const Rhombus<T>& other);
    Rhombus<T>& operator=(const Rhombus<T>& other);

    double area() const override;
    Point<double> center() const override;
    void print() const override;

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Rhombus<T>>(*this);
    }

    friend std::istream &operator>>(std::istream &stream, Rhombus<T> *obj) {
        Point<T> a, b, c, d;
        if (!(stream >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y)) {
            throw std::invalid_argument("Некорректный ввод для Rhombus");
        }

        std::vector<Point<T>> points = {a, b, c, d};
        bool valid = false;

        if (obj->isValid(points[0], points[1], points[2], points[3])) {
            valid = true;
        }

        if (!valid) {
            throw std::invalid_argument("Введенные точки не образуют ромб");
        }

        obj->p1 = std::make_unique<Point<T>>(a);
        obj->p2 = std::make_unique<Point<T>>(b);
        obj->p3 = std::make_unique<Point<T>>(c);
        obj->p4 = std::make_unique<Point<T>>(d);
        return stream;
    }

};

#endif // RHOMBUS