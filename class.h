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
        int capacity_;
        static constexpr int MIN=-100;
        static constexpr int MAX=100;
    public:
        int get_size() const;
        int capacity() const;
        void reserve(int new_capacity);
        Dinamic_arr(const Dinamic_arr& array_copy);
        explicit Dinamic_arr(int size);
        ~Dinamic_arr();

        T getter(int index)const;
        void setter(int index,const T& num);

        void show()const;
        void push_back(const T &num);

        void add(const Dinamic_arr & arr);
        void minus(const Dinamic_arr & arr);

        double distance(const Dinamic_arr& arr)const;

        class Proxy{
        private:
            Dinamic_arr<T>*own;
            int index;
        public:
            Proxy (Dinamic_arr<T>*own,int index);
            Proxy& operator=(const T&value);
            Proxy& operator=(const Proxy& other);
            void rebind(Dinamic_arr<T>* own,int index);
            friend std::ostream& operator<<(std::ostream& out, const Proxy & value){
                return out<<static_cast<T>(value);
            }
            operator T()const;
        };
        class Iterator{
        private:
            Dinamic_arr<T>* own;
            int index;
            Proxy cur;
        public:
            Iterator(Dinamic_arr<T>* own,int index);
            Iterator& operator=(const Iterator& oth);
            Proxy&operator*();
            Iterator& operator++();
            bool operator!=(const Iterator&oth)const;
        };
        Proxy operator[](int index);
        const T& operator[](int index) const;

        bool operator ==(const Dinamic_arr&oth)const;
        bool operator !=(const Dinamic_arr&oth)const;

        Dinamic_arr& operator +=(const Dinamic_arr&oth);
        Dinamic_arr& operator -=(const Dinamic_arr&oth);

        Dinamic_arr& operator +=(const T&value);
        Dinamic_arr& operator -=(const T&value);

        Iterator begin();
        Iterator end();

        const T* begin() const;
        const T* end()const;


        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const Dinamic_arr<U>& arr);

        
};  


#include "class.cpp"