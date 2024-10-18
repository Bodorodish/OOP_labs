#ifndef TRAPEZOID
#define TRAPEZOID

#include "figure.h"

class Trapezoid : public figure {
    point vertices[4];
public:
    Trapezoid() = default;
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    bool operator==(const Trapezoid& other) const;
    bool operator!=(const Trapezoid& other) const;
    
public:
    point mass_center() const override;
    explicit operator double() const override;

protected:
    std::ostream &print(std::ostream &stream) const override;
    std::istream &read(std::istream &stream) override;
};

#endif //TRAPEZOID
