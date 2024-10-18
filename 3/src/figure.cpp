#include "../include/figure.h"
#include <iostream>
#include <cmath>

std::ostream &operator<<(std::ostream &stream, figure const *obj){
    return obj->print(stream);
}

std::istream &operator>>(std::istream &stream, figure *obj){
    return obj->read(stream);
}

double figure::distance(const figure::point& a, const figure::point& b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

bool figure::compare_points(const figure::point& a, const figure::point& b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}