#include <gtest/gtest.h>
#include "../include/three.h"

TEST(test_01, zero_constructor){
    Three a;
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    a.print();
    
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "0\n");
}

TEST(test_02, int_constructor){
    Three a(5);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    a.print();
    
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "12\n");
}

TEST(test_03, str_constructor){
    Three a("1202");
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    a.print();
    
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "1202\n");
}

TEST(test_04, bad_str_constructor){
    EXPECT_THROW(Three a("1203"), std::invalid_argument);
}

TEST(test_05, adding){
    Three a("102");
    Three b("202");

    a += b;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    a.print();
    
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "1011\n");
}

TEST(test_06, subtraction){
    Three a("1000");
    Three b("22");

    a -= b;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    a.print();
    
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "201\n");
}

TEST(test_07, bad_subtraction){
    Three a("1");
    Three b("22");
    EXPECT_THROW(a-=b, std::out_of_range);
}

TEST(test_08, equality){
    Three a(8);
    Three b("22");
    EXPECT_TRUE(a==b);
}

TEST(test_09, inequality){
    Three a(9);
    Three b("22");
    EXPECT_TRUE(a!=b);
}

TEST(test_10, greater){
    Three a(100);
    Three b("22");
    EXPECT_TRUE(a>b);
}

TEST(test_11, less){
    Three a(100);
    Three b("22");
    EXPECT_TRUE(b<a);
}

TEST(test_12, copy) {
    Three a("102");
    Three b(a);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    b.print();

    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "102\n");
}
TEST(test_13, assignment_copy) {
    Three a("102");
    Three b("221");

    b = a;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    b.print();

    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "102\n");
}

TEST(test_14, ssignment_move) {
    Three a("12");
    Three b("102");

    a = std::move(b);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    a.print();

    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "102\n");

    EXPECT_EQ(b.get_size(), 0);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

