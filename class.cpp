#include "class.h"
#include <iostream>
#include <stdexcept> 

Dinamic_arr::Dinamic_arr(int size){
    this->size=size;
    pointer_to_data = new int[size];
};
Dinamic_arr::~Dinamic_arr(){
    delete[] pointer_to_data;
};
Dinamic_arr::Dinamic_arr(const Dinamic_arr& array_copy){
    this->size=array_copy.size;
    pointer_to_data=new int [size];
    for(int i=0;i<size;i++){
        pointer_to_data[i]=array_copy.pointer_to_data[i];
    }
}
void Dinamic_arr::show(){
    for (int i=0; i<size; i++){
        std::cout<<pointer_to_data[i]<<" ";
    };
};
int Dinamic_arr::getter(int index) {
    if (index >= 0 && index < size) {
        return pointer_to_data[index];
    }
    else {
        throw std::out_of_range(
            "Ошибка getter: индекс выходит за границы массива!"
        );
    }
}
void Dinamic_arr::setter(int index, int num) {
    if (index < 0 || index >= size) {
        throw std::out_of_range(
            "Ошибка setter: индекс выходит за границы массива!"
        );
    }

    if (num < MIN || num > MAX) {
        throw std::invalid_argument(
            "Ошибка setter: число должно быть от -100 до 100!"
        );
    }

    pointer_to_data[index] = num;
}

void Dinamic_arr::push_back(int num){
    if (num < MIN || num > MAX) {
        throw std::invalid_argument("Ошибка push_back: число должно быть от -100 до 100!");
    }
    int* new_pointer= new int[size+1];
    for (int i=0; i<size;i++){
        new_pointer[i]=pointer_to_data[i];
    }
    new_pointer[size]=num;
    delete[] pointer_to_data;
    pointer_to_data=new_pointer;
    size++;
}

void Dinamic_arr::add(const Dinamic_arr& arr){
    int limit = size < arr.size ? size : arr.size;

    for (int i = 0; i < limit; i++){
        pointer_to_data[i] += arr.pointer_to_data[i];
    }
}

void Dinamic_arr::minus(const Dinamic_arr& arr){
    int limit = size < arr.size ? size : arr.size;

    for (int i = 0; i < limit; i++){
        pointer_to_data[i] -= arr.pointer_to_data[i];
    }
}