#include <gtest/gtest.h>
#include "../include/rectangle.h"
#include "../include/rhombus.h"
#include "../include/trapezoid.h"

TEST(RectangleTest, CreateValidRectangle) {
    EXPECT_NO_THROW({
        Rectangle<int> rect(Point<int>(0, 0), Point<int>(4, 0), Point<int>(4, 3), Point<int>(0, 3));
    });
    EXPECT_NO_THROW({
        Rectangle<double> rect(Point<double>(0.0, 0.0), Point<double>(4.0, 0.0), Point<double>(4.0, 3.0), Point<double>(0.0, 3.0));
    });
}

TEST(RectangleTest, CreateInvalidRectangle) {
    EXPECT_THROW({
        Rectangle<int> rect(Point<int>(0, 0), Point<int>(1, 1), Point<int>(1, 0), Point<int>(0, 1));
    }, std::invalid_argument);
}

TEST(RectangleTest, Area) {
    Rectangle<int> rect(Point<int>(0, 0), Point<int>(4, 0), Point<int>(4, 3), Point<int>(0, 3));
    EXPECT_EQ(rect.area(), 12);
    
    Rectangle<double> rectD(Point<double>(0.0, 0.0), Point<double>(4.0, 0.0), Point<double>(4.0, 3.0), Point<double>(0.0, 3.0));
    EXPECT_DOUBLE_EQ(rectD.area(), 12.0);
}

TEST(RectangleTest, Center) {  
    Rectangle<double> rectD(Point<double>(0.0, 0.0), Point<double>(4.0, 0.0), Point<double>(4.0, 3.0), Point<double>(0.0, 3.0));
    Point<double> centerD = rectD.center();
    EXPECT_DOUBLE_EQ(centerD.x, 2.0);
    EXPECT_DOUBLE_EQ(centerD.y, 1.5);
}

TEST(RhombusTest, CreateValidRhombus) {
    EXPECT_NO_THROW({
        Rhombus<int> rhombus(Point<int>(0, 0), Point<int>(2, 3), Point<int>(4, 0), Point<int>(2, -3));
    });
    EXPECT_NO_THROW({
        Rhombus<double> rhombus(Point<double>(0.0, 0.0), Point<double>(2.0, 3.0), Point<double>(4.0, 0.0), Point<double>(2.0, -3.0));
    });
}

TEST(RhombusTest, CreateInvalidRhombus) {
    EXPECT_THROW({
        Rhombus<int> rhombus(Point<int>(0, 0), Point<int>(1, 1), Point<int>(2, 2), Point<int>(3, 3));
    }, std::invalid_argument);
}

TEST(RhombusTest, Area) {
    Rhombus<int> rhombus(Point<int>(0, 0), Point<int>(2, 3), Point<int>(4, 0), Point<int>(2, -3));
    EXPECT_DOUBLE_EQ(rhombus.area(), 12.0);
    
    Rhombus<double> rhombusD(Point<double>(0.0, 0.0), Point<double>(2.0, 3.0), Point<double>(4.0, 0.0), Point<double>(2.0, -3.0));
    EXPECT_DOUBLE_EQ(rhombusD.area(), 12.0);
}

TEST(RhombusTest, Center) {
    Rhombus<double> rhombusD(Point<double>(0.0, 0.0), Point<double>(2.0, 3.0), Point<double>(4.0, 0.0), Point<double>(2.0, -3.0));
    Point<double> centerD = rhombusD.center();
    EXPECT_DOUBLE_EQ(centerD.x, 2.0);
    EXPECT_DOUBLE_EQ(centerD.y, 0.0);
}

TEST(TrapezoidTest, CreateValidTrapezoid) {
    EXPECT_NO_THROW({
        Trapezoid<int> trapezoid(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2), Point<int>(1, 2));
    });
    EXPECT_NO_THROW({
        Trapezoid<double> trapezoid(Point<double>(0.0, 0.0), Point<double>(2.0, 0.0), Point<double>(3.0, 2.0), Point<double>(1.0, 2.0));
    });
}

TEST(TrapezoidTest, CreateInvalidTrapezoid) {
    EXPECT_THROW({
        Trapezoid<int> trapezoid(Point<int>(0, 0), Point<int>(1, 1), Point<int>(2, 2), Point<int>(3, 3));
    }, std::invalid_argument);
}

TEST(TrapezoidTest, Area) {
    Trapezoid<int> trapezoid(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2), Point<int>(1, 2));
    EXPECT_DOUBLE_EQ(trapezoid.area(), 4.0);
    
    Trapezoid<double> trapezoidD(Point<double>(0.0, 0.0), Point<double>(2.0, 0.0), Point<double>(3.0, 2.0), Point<double>(1.0, 2.0));
    EXPECT_DOUBLE_EQ(trapezoidD.area(), 4.0);
}

TEST(TrapezoidTest, Center) {
    Trapezoid<double> trapezoidD(Point<double>(0.0, 0.0), Point<double>(2.0, 0.0), Point<double>(3.0, 2.0), Point<double>(1.0, 2.0));
    Point<double> centerD = trapezoidD.center();
    EXPECT_DOUBLE_EQ(centerD.x, 1.5);
    EXPECT_DOUBLE_EQ(centerD.y, 1.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
