#include "../include/memoryResource.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <list>

FixedBlockMemoryResource::FixedBlockMemoryResource(size_t blockSize) 
    : blockSize_(blockSize), memory_(nullptr) {
    memory_ = std::pmr::get_default_resource()->allocate(blockSize);
    // Изначально весь блок считается свободным
    freeBlocks_.emplace_back(static_cast<char*>(memory_), blockSize);
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    std::pmr::get_default_resource()->deallocate(memory_, blockSize_);
}

void* FixedBlockMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    // Ищем первый подходящий свободный блок
    auto it = std::find_if(freeBlocks_.begin(), freeBlocks_.end(),
                           [bytes](const Block& block) {
                               return block.size >= bytes;
                           });

    if (it == freeBlocks_.end()) {
        throw std::bad_alloc();
    }

    // Выделяем память из найденного блока
    void* ptr = it->ptr;
    size_t remainingSize = it->size - bytes;

    // Обновляем список свободных блоков
    if (remainingSize > 0) {
        it->ptr = static_cast<char*>(it->ptr) + bytes;
        it->size = remainingSize;
    } else {
        freeBlocks_.erase(it);
    }

    // Запоминаем выделенный блок
    allocations_.emplace_back(ptr, bytes);
    return ptr;
}

void FixedBlockMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    // Проверяем, существует ли выделение
    auto it = std::find_if(allocations_.begin(), allocations_.end(),
                           [p](const std::pair<void*, size_t>& allocation) {
                               return allocation.first == p;
                           });

    if (it != allocations_.end()) {
        // Освобождаем память
        freeBlocks_.emplace_back(p, it->second);
        allocations_.erase(it);

        // Сливаем соседние свободные блоки
        mergeFreeBlocks();
    } else {
        std::cerr << "Ошибка: Попытка деаллокации несуществующего указателя!" << std::endl;
    }
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

void FixedBlockMemoryResource::mergeFreeBlocks() {
    // Сортируем свободные блоки по адресу
    freeBlocks_.sort([](const Block& a, const Block& b) {
        return a.ptr < b.ptr;
    });

    // Сливаем соседние блоки
    for (auto it = freeBlocks_.begin(); it != freeBlocks_.end();) {
        auto next = std::next(it);
        if (next != freeBlocks_.end() &&
            static_cast<char*>(it->ptr) + it->size == next->ptr) {
            it->size += next->size;
            freeBlocks_.erase(next);
        } else {
            ++it;
        }
    }
}
