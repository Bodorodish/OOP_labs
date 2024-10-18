#ifndef RECTANGLE
#define RECTANGLE

#include "figure.h"

class Rectangle : public figure {
private:
    point vertices[4];
public:
    Rectangle() = default;
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    bool operator==(const Rectangle& other) const;
    bool operator!=(const Rectangle& other) const;

public:
    point mass_center() const override;
    explicit operator double() const override;

protected:
    std::ostream &print(std::ostream &stream) const override;
    std::istream &read(std::istream &stream) override;
};

#endif //RECTANGLE
