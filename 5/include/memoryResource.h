#ifndef MEM_RES
#define MEM_RES

#include <iostream>
#include <memory_resource>
#include <list>

class FixedBlockMemoryResource : public std::pmr::memory_resource {
private:
    size_t blockSize_;
    size_t allocated_ = 0;
    void* memory_;
    std::list<std::pair<void*, size_t>> allocations_;

public:
    explicit FixedBlockMemoryResource(size_t blockSize);
    ~FixedBlockMemoryResource();

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

#endif
