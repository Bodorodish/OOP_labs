#include "../include/rhombus.h"
#include <cmath>
#include <iostream>

figure::point Rhombus::mass_center() const {
    point center;
    for (const auto& vertex : vertices) {
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= 4;
    center.y /= 4;
    return center;
}

Rhombus::operator double() const {
    double maxDistance = 0;
    int diag1_start = 0, diag1_end = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            double dist = distance(vertices[i], vertices[j]);
            if (dist > maxDistance) {
                maxDistance = dist;
                diag1_start = i;
                diag1_end = j;
            }
        }
    }

    double d1 = maxDistance;

    int remaining1 = -1, remaining2 = -1;
    for (int i = 0; i < 4; ++i) {
        if (i != diag1_start && i != diag1_end) {
            if (remaining1 == -1) {
                remaining1 = i;
            } else {
                remaining2 = i;
            }
        }
    }

    double d2 = distance(vertices[remaining1], vertices[remaining2]);

    return 0.5 * d1 * d2;
}

std::ostream &Rhombus::print(std::ostream &stream) const {
    stream << "ромб с координатами: ";
    for (auto& vertex : vertices) {
        stream << "(" << vertex.x << "," << vertex.y << ") ";
    }
    return stream;
}

std::istream &Rhombus::read(std::istream &stream) {
    for (auto& vertex : vertices) {
        stream >> vertex.x >> vertex.y;
    }
    
    point sort_vert[4];
    std::copy(std::begin(vertices), std::end(vertices), std::begin(sort_vert));

    std::sort(std::begin(sort_vert), std::end(sort_vert), figure::compare_points);

    double side1 = figure::distance(sort_vert[0], sort_vert[1]);
    double side2 = figure::distance(sort_vert[0], sort_vert[2]);
    double side3 = figure::distance(sort_vert[3], sort_vert[1]);
    double side4 = figure::distance(sort_vert[3], sort_vert[2]);
    

    if (!(std::abs(side1 - side2) < 1e-6 && std::abs(side2 - side3) < 1e-6 && std::abs(side3 - side4) < 1e-6)) {
        std::cerr << "Ошибка: введенные точки не образуют ромб, стороны не равны." << std::endl;
        stream.setstate(std::ios::failbit);
        return stream;
    }

    point diag1 = {std::abs(sort_vert[3].x - sort_vert[0].x), std::abs(sort_vert[3].y - sort_vert[0].y)};
    point diag2 = {std::abs(sort_vert[2].x - sort_vert[1].x), std::abs(sort_vert[2].y - sort_vert[1].y)};
    double dot_product = diag1.x * diag2.x + diag1.y * diag2.y;

    if (std::abs(dot_product) > 1e-6) {
        std::cerr << "ошибка: диагонали ромба не пересекаются под прямым углом." << std::endl;
        stream.setstate(std::ios::failbit);
        return stream;
    }

    return stream;
}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) { 
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) { 
        for (int i = 0; i < 4; i++) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;
}

bool Rhombus::operator==(const Rhombus& other) const {
    for (int i = 0; i < 4; i++) {
        if (vertices[i].x != other.vertices[i].x || vertices[i].y != other.vertices[i].y) {
            return false;
        }
    }
    return true;
}

bool Rhombus::operator!=(const Rhombus& other) const {
    return !(*this == other);
}