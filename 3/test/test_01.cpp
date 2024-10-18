#include <gtest/gtest.h>
#include "../include/rectangle.h"
#include "../include/rhombus.h"
#include "../include/trapezoid.h"
#include <sstream>

TEST(FigureTest, rectangle_area) {
    Rectangle rect;
    std::istringstream input("0 0 0 2 3 2 3 0");
    input >> &rect;
    EXPECT_DOUBLE_EQ(static_cast<double>(rect), 6.0);
}

TEST(FigureTest, rectangle_mass_center) {
    Rectangle rect;
    std::istringstream input("0 0 0 2 3 2 3 0");
    input >> &rect;
    auto center = rect.mass_center();
    EXPECT_DOUBLE_EQ(center.x, 1.5);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(FigureTest, rhombus_area) {
    Rhombus rhombus;
    std::istringstream input("0 0 0 4 4 2 -4 2");
    input >> &rhombus;
    EXPECT_DOUBLE_EQ(static_cast<double>(rhombus), 16.0);
}

TEST(FigureTest, rhombus_mass_center) {
    Rhombus rhombus;
    std::istringstream input("0 0 0 4 4 2 -4 2");
    input >> &rhombus;
    auto center = rhombus.mass_center();
    EXPECT_DOUBLE_EQ(center.x, 0.0);
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST(FigureTest, trapezoid_area) {
    Trapezoid trapezoid;
    std::istringstream input("0 0 2 2 4 2 2 0");
    input >> &trapezoid;
    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 4.0);
}

TEST(FigureTest, second_trapezoid_area) {
    Trapezoid trapezoid;
    std::istringstream input("0 0 0 8 3 5 3 2");
    input >> &trapezoid;
    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 16.5);
}

TEST(FigureTest, trapezoid_mass_center) {
    Trapezoid trapezoid;
    std::istringstream input("0 0 2 2 4 2 2 0");
    input >> &trapezoid;
    auto center = trapezoid.mass_center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}
 
TEST(FigureTest, rectangle_print) {
    Rectangle rect;
    std::istringstream input("0 0 0 2 3 2 3 0");
    input >> &rect;
    std::ostringstream output;
    output << &rect;
    EXPECT_EQ(output.str(), "прямоугольник с координатами: (0,0) (0,2) (3,2) (3,0) ");
}

TEST(FigureTest, rhombus_print) {
    Rhombus rhombus;
    std::istringstream input("0 0 0 4 4 2 -4 2");
    input >> &rhombus;
    std::ostringstream output;
    output << &rhombus;
    EXPECT_EQ(output.str(), "ромб с координатами: (0,0) (0,4) (4,2) (-4,2) ");
}

TEST(FigureTest, trapezoid_print) {
    Trapezoid trapezoid;
    std::istringstream input("0 0 2 2 4 2 2 0");
    input >> &trapezoid;
    std::ostringstream output;
    output << &trapezoid;
    EXPECT_EQ(output.str(), "трапеция с координатами: (0,0) (2,2) (4,2) (2,0) ");
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

