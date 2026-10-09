#include "class.h"
#include <iostream>
#include <stdexcept> 
#include <string>
#include <type_traits>
#include <typeinfo>
#include <cmath>


//конструктор
template <typename T>
Dinamic_arr<T>::Dinamic_arr(int rec_size):pointer_to_data(nullptr),size(0){
    if (rec_size<0){
        throw std::invalid_argument("Negative array size");
    }
    pointer_to_data=new T[rec_size]{};
    size=rec_size;
};
//деструктор
template <typename T>
Dinamic_arr<T>::~Dinamic_arr(){
    delete[] pointer_to_data;
};
//конструктор копир
template <typename T>
Dinamic_arr<T>::Dinamic_arr(const Dinamic_arr& array_copy): pointer_to_data(nullptr), size(array_copy.size){
    pointer_to_data=new T [size];
    try{
        for(int i=0;i<size;i++){
            pointer_to_data[i]=array_copy.pointer_to_data[i];
        }
    }
    catch(...){
        delete[] pointer_to_data;
        throw;
    }
}
//функция show
template <typename T>
void Dinamic_arr<T>::show()const{
    std::cout << *this;
};
//геттер
template <typename T>
T Dinamic_arr<T>::getter(int index) {
    if (index >= 0 && index < size) {
        return pointer_to_data[index];
    }
    else {
        throw std::out_of_range("Ошибка getter: индекс выходит за границы массива!");
    }
}
//сеттер

template <typename T>
void Dinamic_arr<T>::setter(int index,const T& num) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Ошибка setter: индекс выходит за границы массива!");
    }



    if constexpr (std::is_integral_v<T>) {
        if (static_cast<double>(num)<MIN||static_cast<double>(num)>MAX){
            throw std::invalid_argument("Ошибка setter: число должно быть от -100 до 100!");
        }
    }

    pointer_to_data[index] = num;
}

//добавление в конец

template <typename T>
void Dinamic_arr<T>::push_back(T num){

    if constexpr (std::is_integral_v<T>) {
        if (static_cast<double>(num) < MIN ||static_cast<double>(num) > MAX) {
            throw std::invalid_argument("Integer value outside [-100, 100]");
        }
    }

    T* new_pointer= new T[size+1];
    try{
        for (int i=0; i<size;i++){
            new_pointer[i]=pointer_to_data[i];
        }
        new_pointer[size]=num;
    }
    catch(...){
        delete[] new_pointer;
        throw;
    }
    delete[] pointer_to_data;
    pointer_to_data=new_pointer;
    size++;
}

//Сложение
template <typename T>
void Dinamic_arr<T>::add(const Dinamic_arr& arr){
    if constexpr (std::is_arithmetic_v<T>){
        int limit = size < arr.size ? size : arr.size;

        for (int i = 0; i < limit; i++){
            pointer_to_data[i] += arr.pointer_to_data[i];
        }
    }
    else{
        throw std::bad_typeid();
    }
}
//Вычитание
template <typename T>
void Dinamic_arr<T>::minus(const Dinamic_arr& arr){
    
    if constexpr(std::is_arithmetic_v<T>){

        int limit = size < arr.size ? size : arr.size;

        for (int i = 0; i < limit; i++){
            pointer_to_data[i] -= arr.pointer_to_data[i];
        }
    }
    else{
        throw std::bad_typeid();
    }
}
//оператор
template <typename T>
std::ostream& operator<<(std::ostream& out,const Dinamic_arr<T>& arr) {
    for (int i = 0; i < arr.size; i++) {
        out << arr.pointer_to_data[i] << " ";
    }
    return out;
}
//евклид
template <typename T>
double Dinamic_arr<T>::distance(const Dinamic_arr& arr)const{
    if (size != arr.size) {
        throw std::invalid_argument("Different sizes");
    }
    if constexpr(!std::is_arithmetic_v<T>){
        throw std::bad_typeid();
    }
    else{
        double sum =0.0;
        for (int i=0; i<size;i++){
            double d =static_cast<double>(pointer_to_data[i]) -static_cast<double>(arr.pointer_to_data[i]);
            sum += d * d;
        }
        return std::sqrt(sum);    
    }
}

