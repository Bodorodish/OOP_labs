#include "../include/three.h"
#include <string>
#include <iostream>


//конструкторы
Three::Three() : digits(new unsigned char[1]), size(1) {
    digits[0] = 0;
}

Three::Three(unsigned int number) : digits(nullptr), size(0) {
    if (number == 0) {
        size = 1;
        digits = new unsigned char[1];
        digits[0] = 0;
    } else {
        unsigned int temp = number;
        while (temp > 0) {
            size++;
            temp /= 3;
        }

        digits = new unsigned char[size];
        for (size_t i = 0; i < size; ++i) {
            digits[i] = number % 3;
            number /= 3;
        }
    }
}

Three::Three(const std::string &string_representation) : digits(nullptr), size(0) {
    size = string_representation.length();
    digits = new unsigned char[size];

    for (auto i = 0; i < size; ++i) {
        char c = string_representation[size - i - 1];
        if (c < '0' || c > '2') {
            throw std::invalid_argument("встретилась цифра, которой не должно быть");
        }
        digits[i] = c - '0';
    }
}

//дистркутор
Three::~Three() {
    delete[] digits;
}

//копирования
Three::Three(const Three &other) {
    this->size = other.size;
    this->digits = new unsigned char[this->size];
    std::memcpy(this->digits, other.digits, this->size);
}

//присваивание копирования 
Three& Three::operator=(const Three &other) {
    if (this == &other) {
        return *this;
    }

    delete[] this->digits;
    this->size = other.size;
    this->digits = new unsigned char[this->size];
    std::memcpy(this->digits, other.digits, this->size);

    return *this;
}

//перемещение 
Three::Three(Three &&other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

//присваивание перемещение
Three& Three::operator=(Three &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] this->digits;

    this->digits = other.digits;
    this->size = other.size;

    other.digits = nullptr;
    other.size = 0;

    return *this;
}

//операторы
Three& Three::operator+=(const Three& other) {
    int carry = 0;
    size_t maxSize = std::max(this->size, other.size);

    unsigned char* newDigits = new unsigned char[maxSize + 1];
    std::memset(newDigits, 0, maxSize + 1);
    int sum;
    for (auto i = 0; i < maxSize || carry; i++) {
        sum = carry;
        if (i < this->size) sum += this->digits[i];
        if (i < other.size) sum += other.digits[i];

        newDigits[i] = sum % 3;
        carry = sum / 3;
    }

    delete[] this->digits;
    this->digits = newDigits;
    this->size = maxSize + (sum ? 1 : 0);


    return *this;
}

Three& Three::operator-=(const Three& other) {
    if (this->size < other.size) throw std::out_of_range("отрицательный результат");
    
    int credit = 0;
    for (auto i = 0; i < this->size; i++){
        int diff = this->digits[i] - credit - (other.size > i ? other.digits[i] : 0);
        if (diff < 0){
            credit = 1;
            diff += 3;
        } else {
            credit = 0;
        }
        this->digits[i] = diff;
    }

    while (this->size > 1 && this->digits[this->size - 1] == 0) {
        this->size--;
    }
    
    return *this;
}

Three operator+(const Three& left, const Three& right) {
    Three result = left;
    result += right;
    return result;
}

Three operator-(const Three& left, const Three& right) {
    Three result = left;
    result -= right;
    return result;
}

bool operator==(const Three& left, const Three& right) {
    if (left.size != right.size) return false;
    for (auto i = 0; i < left.size; i++) {
        if (left.digits[i] != right.digits[i]) return false;
    }
    return true;
}

bool operator!=(const Three& left, const Three& right) {
    return !(left==right);
}

bool operator<(const Three& left, const Three& right) {
    if (left.size != right.size) return left.size < right.size;

    for (auto i = left.size - 1; i >= 0; i--) {
        if (left.digits[i] != right.digits[i]) return left.digits[i] < right.digits[i];
    }
    return false;
}

bool operator>(const Three& left, const Three& right) {
    return right < left;
}

void Three::print() const{
    for (int i = this->size - 1; i >= 0; i--){
        std::cout << int(digits[i]);
    }
    std::cout << std::endl;
}

size_t Three::get_size() const{
    return this->size;
}
