#include "../include/memoryResource.h"
#include <stdexcept>
#include <algorithm>

FixedBlockMemoryResource::FixedBlockMemoryResource(size_t blockSize) 
    : blockSize_(blockSize), memory_(nullptr) {
    memory_ = std::pmr::get_default_resource()->allocate(blockSize);  // Выделяем блок
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    // Освобождаем всю память, выделенную под `memory_`
    std::pmr::get_default_resource()->deallocate(memory_, blockSize_);
}

void* FixedBlockMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    if (allocated_ + bytes > blockSize_) {
        throw std::bad_alloc();  // Недостаточно памяти
    }

    void* ptr = static_cast<char*>(memory_) + allocated_;  // Смещаем указатель на выделяемую область
    allocated_ += bytes;

    // Добавляем запись о выделении памяти в список
    allocations_.emplace_back(ptr, bytes);
    return ptr;
}

void FixedBlockMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    // Находим запись в `allocations_` и удаляем её
    auto it = std::find_if(allocations_.begin(), allocations_.end(),
                           [p](const std::pair<void*, size_t>& allocation) {
                               return allocation.first == p;
                           });

    if (it != allocations_.end()) {
        allocated_ -= it->second;  // Обновляем количество выделенной памяти
        allocations_.erase(it);    // Удаляем запись о выделении
    } else {
        std::cerr << "Ошибка: Попытка деаллокации несуществующего указателя!" << std::endl;
    }
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
