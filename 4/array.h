#ifndef ARRAY
#define ARRAY

#include <memory>
#include <vector>

template <typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity);

public:
    Array(size_t capacity = 10);
    void add(const T& element);
    T& operator[](size_t index);
    size_t getSize() const;
    void remove(size_t index);
};

#endif // ARRAY
