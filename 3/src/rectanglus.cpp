#include "../include/rectangle.h"
#include <cmath>
#include <iostream>

figure::point Rectangle::mass_center() const {
    point center;
    for (const auto& vertex : vertices) {
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= 4;
    center.y /= 4;
    return center;
}

Rectangle::operator double() const {
    point sort_vert[4];
    std::copy(std::begin(vertices), std::end(vertices), std::begin(sort_vert));
    std::sort(std::begin(sort_vert), std::end(sort_vert), figure::compare_points);
    double side1 = figure::distance(sort_vert[0], sort_vert[1]);
    double side2 = figure::distance(sort_vert[0], sort_vert[2]);

    return side1 * side2;
}

std::ostream &Rectangle::print(std::ostream &stream) const {
    stream << "прямоугольник с координатами: ";
    for (const auto& vertex : vertices) {
        stream << "(" << vertex.x << "," << vertex.y << ") ";
    }
    return stream;
}

std::istream &Rectangle::read(std::istream &stream) {
    for (auto& vertex : vertices) {
        stream >> vertex.x >> vertex.y;
    }

    point sort_vert[4];
    std::copy(std::begin(vertices), std::end(vertices), std::begin(sort_vert));
    std::sort(std::begin(sort_vert), std::end(sort_vert), figure::compare_points);

    vertices[0] = sort_vert[0];
    vertices[1] = sort_vert[1];
    vertices[2] = sort_vert[3];
    vertices[3] = sort_vert[2];

    double side1 = figure::distance(vertices[0], vertices[1]);
    double side2 = figure::distance(vertices[1], vertices[2]);
    double side3 = figure::distance(vertices[2], vertices[3]);
    double side4 = figure::distance(vertices[3], vertices[0]);

    if (!(std::abs(side1 - side3) < 1e-6 && std::abs(side2 - side4) < 1e-6)) {
        std::cerr << "ошибка: противоположные стороны прямоугольника должны быть равны" << std::endl;
        stream.setstate(std::ios::failbit);
        return stream;
    }

    point v1 = {vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y};
    point v2 = {vertices[2].x - vertices[1].x, vertices[2].y - vertices[1].y};
    point v3 = {vertices[3].x - vertices[2].x, vertices[3].y - vertices[2].y};
    point v4 = {vertices[0].x - vertices[3].x, vertices[0].y - vertices[3].y};

    if (std::abs(v1.x * v2.x + v1.y * v2.y) > 1e-6 || 
        std::abs(v2.x * v3.x + v2.y * v3.y) > 1e-6 || 
        std::abs(v3.x * v4.x + v3.y * v4.y) > 1e-6 || 
        std::abs(v4.x * v1.x + v4.y * v1.y) > 1e-6) {
        std::cerr << "ошибка: углы прямоугольника должны быть прямыми" << std::endl;
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) { 
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) { 
        for (int i = 0; i < 4; i++) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;
}

bool Rectangle::operator==(const Rectangle& other) const {
    for (int i = 0; i < 4; i++) {
        if (vertices[i].x != other.vertices[i].x || vertices[i].y != other.vertices[i].y) {
            return false;
        }
    }
    return true;
}

bool Rectangle::operator!=(const Rectangle& other) const {
    return !(*this == other);
}