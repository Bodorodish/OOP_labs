#include "../include/trapezoid.h"
#include <cmath>
#include <iostream>

figure::point Trapezoid::mass_center() const {
    point center;
    for (const auto& vertex : vertices) {
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= 4;
    center.y /= 4;
    return center;
}

Trapezoid::operator double() const {
    point sorted[4];
    std::copy(std::begin(vertices), std::end(vertices), std::begin(sorted));
    std::sort(std::begin(sorted), std::end(sorted), figure::compare_points);

    double base1 = figure::distance(sorted[0], sorted[1]);
    double base2 = figure::distance(sorted[2], sorted[3]);
    double base3 = figure::distance(sorted[0], sorted[3]);
    double base4 = figure::distance(sorted[1], sorted[2]);
    
    double height1 = std::abs((sorted[0].y + sorted[3].y) / 2 - (sorted[2].y + sorted[1].y) / 2);
    double height2 = std::abs((sorted[0].x + sorted[1].x) / 2 - (sorted[2].x + sorted[3].x) / 2);

    if (sorted[0].y == sorted[3].y){return 0.5 * (base3 + base4) * height1;}

    return 0.5 * (base1 + base2) * height2;
}

std::ostream &Trapezoid::print(std::ostream &stream) const {
    stream << "трапеция с координатами: ";
    for (const auto& vertex : vertices) {
        stream << "(" << vertex.x << "," << vertex.y << ") ";
    }
    return stream;
}

std::istream &Trapezoid::read(std::istream &stream) {
    for (auto& vertex : vertices) {
        stream >> vertex.x >> vertex.y;
    }
    
    point sort_vert[4];
    std::copy(std::begin(vertices), std::end(vertices), std::begin(sort_vert));
    std::sort(std::begin(sort_vert), std::end(sort_vert), figure::compare_points);

    point v1 = {sort_vert[1].x - sort_vert[0].x, sort_vert[1].y - sort_vert[0].y};
    point v2 = {sort_vert[2].x - sort_vert[3].x, sort_vert[2].y - sort_vert[3].y};
    point v3 = {sort_vert[3].x - sort_vert[0].x, sort_vert[3].y - sort_vert[0].y};
    point v4 = {sort_vert[2].x - sort_vert[1].x, sort_vert[2].y - sort_vert[1].y};

    if ((std::abs(v1.x * v2.y - v1.y * v2.x) > 1e-6) && (std::abs(v3.x * v4.y - v3.y * v4.x) > 1e-6)) {
        std::cerr << "ошибка: хотя бы одна пара сторон должна быть параллельной" << std::endl;
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) { 
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) { 
        for (int i = 0; i < 4; i++) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;
}

bool Trapezoid::operator==(const Trapezoid& other) const {
    for (int i = 0; i < 4; i++) {
        if (vertices[i].x != other.vertices[i].x || vertices[i].y != other.vertices[i].y) {
            return false;
        }
    }
    return true;
}

bool Trapezoid::operator!=(const Trapezoid& other) const {
    return !(*this == other);
}