#pragma once
#include <iosfwd>

// Объявляем шаблонный класс заранее
template <typename T>
class Dinamic_arr;

// Объявляем шаблонный оператор вывода
template <typename T>
std::ostream& operator<<(std::ostream& out,const Dinamic_arr<T>& arr);

template <typename T>
class Dinamic_arr{
    private:
        T* pointer_to_data;
        int size;
        static constexpr int MIN=-100;
        static constexpr int MAX=100;
    public:
        Dinamic_arr(const Dinamic_arr& array_copy);
        explicit Dinamic_arr(int size);
        ~Dinamic_arr();

        T getter(int index);
        void setter(int index,const T& num);

        void show()const;
        void push_back(T num);

        void add(const Dinamic_arr & arr);
        void minus(const Dinamic_arr & arr);

        double distance(const Dinamic_arr& arr)const;

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const Dinamic_arr<U>& arr);
};
#include "class.cpp"