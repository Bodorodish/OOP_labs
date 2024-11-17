#include <gtest/gtest.h>
#include "../src/doubleLinkedList.cpp"
#include "../src/memoryResource.cpp"
#include <stdexcept>
#include <vector>

struct TestType {
    int id;
    std::string name;
};

TEST(DoubleLinkedListTest, PushUsingIterator) {
    FixedBlockMemoryResource memoryResource(1024);
    DoubleLinkedList<int> list(&memoryResource);

    list.push(list.begin(), 1);  // Вставка в начало
    list.push(list.begin(), 0);  // Перед текущим началом
    list.push(list.end(), 2);    // Вставка в конец

    auto it = list.begin();
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(it, list.end());
}

TEST(DoubleLinkedListTest, PopUsingIterator) {
    FixedBlockMemoryResource memoryResource(1024);
    DoubleLinkedList<int> list(&memoryResource);

    list.push(list.begin(), 1);
    list.push(list.begin(), 2);
    list.push(list.begin(), 3);

    list.pop(list.begin());

    EXPECT_EQ(*list.begin(), 2);
    EXPECT_EQ(++list.begin(), list.end());
}

TEST(DoubleLinkedListTest, ComplexTypeWithIterator) {
    FixedBlockMemoryResource memoryResource(1024);
    DoubleLinkedList<TestType> list(&memoryResource);

    list.push(list.end(), {1, "first"});
    list.push(list.begin(), {0, "zero"});

    auto it = list.begin();
    EXPECT_EQ(it->id, 0);
    EXPECT_EQ((++it)->id, 1);
    EXPECT_EQ(it->name, "first");
}

TEST(DoubleLinkedListTest, IteratorTraversal) {
    FixedBlockMemoryResource memoryResource(1024);
    DoubleLinkedList<int> list(&memoryResource);

    list.push(list.begin(), 1);
    list.push(list.begin(), 2);
    list.push(list.end(), 3);

    std::vector<int> result;
    for (auto it = list.begin(); it != list.end(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 3);
}

TEST(FixedBlockMemoryResourceTest, AllocateDeallocate) {
    FixedBlockMemoryResource memoryResource(1024);

    void* ptr1 = memoryResource.allocate(100);
    EXPECT_NE(ptr1, nullptr);
    
    void* ptr2 = memoryResource.allocate(200);
    EXPECT_NE(ptr2, nullptr);

    memoryResource.deallocate(ptr1, 100);
    memoryResource.deallocate(ptr2, 200);
}

TEST(FixedBlockMemoryResourceTest, AllocationExceedsBlockSize) {
    FixedBlockMemoryResource memoryResource(256);
    EXPECT_THROW(memoryResource.allocate(300), std::bad_alloc);
}

TEST(FixedBlockMemoryResourceTest, EqualityTest) {
    FixedBlockMemoryResource memoryResource1(1024);
    FixedBlockMemoryResource memoryResource2(1024);

    EXPECT_TRUE(memoryResource1.is_equal(memoryResource1));
    EXPECT_FALSE(memoryResource1.is_equal(memoryResource2));
}

TEST(FixedBlockMemoryResourceTest, DestructorDeallocatesAll) {
    FixedBlockMemoryResource* memoryResource = new FixedBlockMemoryResource(512);
    
    void* ptr1 = memoryResource->allocate(100);
    void* ptr2 = memoryResource->allocate(200);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);

    delete memoryResource;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
