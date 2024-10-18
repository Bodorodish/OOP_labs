#ifndef RHOMBUS
#define RHOMBUS

#include "figure.h"

class Rhombus : public figure {
    point vertices[4];

public:
    Rhombus() = default;
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;

    bool operator==(const Rhombus& other) const;
    bool operator!=(const Rhombus& other) const;
    
public:
    point mass_center() const override;
    explicit operator double() const override;

protected:
    std::ostream &print(std::ostream &stream) const override;
    std::istream &read(std::istream &stream) override;
};

#endif // RHOMBUS
