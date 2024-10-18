#ifndef THREE
#define THREE

#include <string>

class Three{
    private:

        unsigned char* digits;
        size_t size;


    public:
        //конструкторы
        Three();
        Three(const std::string &string_representation);
        Three(unsigned int number);

    public:
        //дистркутор
        virtual ~Three() noexcept;    
        //копирования             
        Three(const Three &other)/* = default*/;
        //присваивания копирования
        Three& operator=(Three const &other);
        //перемещения
        Three(Three&& other) noexcept;
        //присваивания перемещения
        Three& operator=(Three &&other) noexcept;

    public:
        //мат. операторы
        Three& operator+=(const Three &other);
        Three& operator-=(const Three &other);

        friend Three operator+(const Three &left, const Three &right);
        friend Three operator-(const Three &left, const Three &right);

        friend bool operator==(const Three &left, const Three &right);
        friend bool operator!=(const Three &left, const Three &right);
        friend bool operator<(const Three &left, const Three &right);
        friend bool operator>(const Three &left, const Three &right);
    
        //выводы
        void print() const;
        size_t get_size() const;
};

#endif //Three