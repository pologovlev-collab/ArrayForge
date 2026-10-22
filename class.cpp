#include "class.h"
#include <iostream>
#include <stdexcept> 
#include <string>
#include <type_traits>
#include <typeinfo>
#include <cmath>


//конструктор
template <typename T>
Dinamic_arr<T>::Dinamic_arr(int rec_size):pointer_to_data(nullptr),size(0),capacity_(0){
    if (rec_size<0){
        throw std::invalid_argument("Negative array size");
    }
    pointer_to_data=new T[rec_size]{};
    capacity_=rec_size;
    size=rec_size;
};

//Доп выделение
template <typename T>
void Dinamic_arr<T>::reserve(int new_capacity){
    if(new_capacity<0){
        throw std::invalid_argument("Negative capacity");
    }
    if (new_capacity<=capacity_){
        return;
    }

    T* new_data =new T[new_capacity]{};

    try{
        for (int i=0;i<size;i++){
            new_data[i]=pointer_to_data[i];
        }
    }
    catch (...){
        delete[] new_data;
        throw;
    }
    delete[] pointer_to_data;
    pointer_to_data=new_data;
    capacity_=new_capacity;
}

//деструктор
template <typename T>
Dinamic_arr<T>::~Dinamic_arr(){
    delete[] pointer_to_data;
};
//конструктор копир
template <typename T>
Dinamic_arr<T>::Dinamic_arr(const Dinamic_arr& array_copy): pointer_to_data(nullptr), size(array_copy.size),capacity_(0){
    T* new_data=new T [array_copy.size]{};
    try{
        for(int i=0;i<array_copy.size;i++){
            new_data[i]=array_copy.pointer_to_data[i];
        }
    }
    catch(...){
        delete[] new_data;
        throw;
    }
    pointer_to_data=new_data;
    size=array_copy.size;
    capacity_=array_copy.size;
}

//конструктор итератора
template <typename T>
Dinamic_arr<T>::Iterator::Iterator(Dinamic_arr<T>* own,int index):own(own),index(index),cur(own,index){}

template <typename T>
typename Dinamic_arr<T>::Proxy&
Dinamic_arr<T>::Iterator::operator*() {

    cur.rebind(own, index);
    return cur;
}

template <typename T>
typename Dinamic_arr<T>::Iterator&
Dinamic_arr<T>::Iterator::operator++() {
    ++index;
    return *this;
}

template <typename T>
bool Dinamic_arr<T>::Iterator::operator!=(const Iterator& other) const {
    return own != other.own ||index != other.index;
}

template <typename T>
void Dinamic_arr<T>::Proxy::rebind(Dinamic_arr<T>* new_owner,int new_index) {
    own = new_owner;
    index = new_index;
}

template <typename T>
typename Dinamic_arr<T>::Iterator&
Dinamic_arr<T>::Iterator::operator=(const Iterator& other) {
    if (this != &other) {
        own = other.own;
        index = other.index;
        cur.rebind(own, index);
    }

    return *this;
}

//end()
template <typename T>
typename Dinamic_arr<T>::Iterator
Dinamic_arr<T>::end(){
    return Iterator(this,size);
}
//begin()
template <typename T>
typename Dinamic_arr<T>::Iterator
Dinamic_arr<T>::begin(){
    return Iterator(this,0);
}

template <typename T>
const T* Dinamic_arr<T>::begin() const {
    return pointer_to_data;
}

template <typename T>
const T* Dinamic_arr<T>::end() const {
    return pointer_to_data + size;
}

//функция show
template <typename T>
void Dinamic_arr<T>::show()const{
    std::cout << *this;
};
//геттер
template <typename T>
T Dinamic_arr<T>::getter(int index) const{
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
//конструктор класса прокладки
template <typename T>
Dinamic_arr<T>::Proxy::Proxy(Dinamic_arr<T>*own,int index):own(own),index(index){}

//перегрузка присваивания
template <typename T>
typename Dinamic_arr<T>::Proxy&
Dinamic_arr<T>::Proxy::operator=(const T&value){
    own->setter(index,value);
    return *this;
}

//перегрузка присваивания 2
template <typename T>
typename Dinamic_arr<T>::Proxy&
Dinamic_arr<T>::Proxy::operator=(const Proxy & value){
    return *this =static_cast<T>(value);
}

//оператор []
template <typename T>
typename Dinamic_arr<T>::Proxy
Dinamic_arr<T>::operator[](int index){
    if (index<0||index>=size){
        throw std::out_of_range("индекс за пределами");
    }
    return Proxy(this, index);
}

//оператор [] для const масивов
template <typename T>
const T&Dinamic_arr<T>::operator[](int index)const{
    if (index<0||index>=size){
        throw std::out_of_range("индекс за пределами");
    }
    return pointer_to_data[index];
}
//сравнение ==
template <typename T>
bool Dinamic_arr<T>::operator==(const Dinamic_arr&oth)const{
    if (size!=oth.size){
        return false;
    }
    for (int i=0;i<size;i++){
        if (!(pointer_to_data[i]==oth.pointer_to_data[i])){
            return false;
        }
    }
    return true;
}

//сравнение !=
template <typename T>
bool Dinamic_arr<T>::operator!=(const Dinamic_arr&oth)const{
    return !(*this==oth);
}

//оператор += массивы
template <typename T>
Dinamic_arr<T>& Dinamic_arr<T>::operator+=(const Dinamic_arr& oth ){
    if constexpr (std::is_arithmetic_v<T>){
        int limit;
        if (size<oth.size){
            limit=size;
        }else{
            limit=oth.size;
        }
        for (int i=0;i<limit;i++){
            pointer_to_data[i]+=oth.pointer_to_data[i];
        }
    }else{
        throw std::bad_typeid();
    }
    return *this;
}

//оператор += числа
template<typename T>
Dinamic_arr<T>& Dinamic_arr<T>::operator+=(const T&value){
    if constexpr(std::is_arithmetic_v<T>){
        for (int i=0;i<size;i++){
            pointer_to_data[i]+=value;
        }
    }else {
        throw std::bad_typeid();
    }

    return *this;
}
//оператор -= числа
template<typename T>
Dinamic_arr<T>& Dinamic_arr<T>::operator-=(const T&value){
    if constexpr(std::is_arithmetic_v<T>){
        for (int i=0;i<size;i++){
            pointer_to_data[i]-=value;
        }
    }else {
        throw std::bad_typeid();
    }

    return *this;
}
//оператор -= массивы
template <typename T>
Dinamic_arr<T>& Dinamic_arr<T>::operator-=(const Dinamic_arr& oth ){
    if constexpr (std::is_arithmetic_v<T>){
        int limit;
        if (size<oth.size){
            limit=size;
        }else{
            limit=oth.size;
        }
        for (int i=0;i<limit;i++){
            pointer_to_data[i]-=oth.pointer_to_data[i];
        }
    }else{
        throw std::bad_typeid();
    }
    return *this;
}

//преоброзование в тип
template <typename T>
Dinamic_arr<T>::Proxy::operator T() const {
    return own->getter(index);
}

//добавление в конец

template <typename T>
void Dinamic_arr<T>::push_back(const T& num){

    if constexpr (std::is_integral_v<T>) {
        if (static_cast<double>(num) < MIN ||static_cast<double>(num) > MAX) {
            throw std::invalid_argument("Integer value outside [-100, 100]");
        }
    }

    T saved =num;
    
    if (size==capacity_){
        int new_capacity;
        if (capacity_==0){
            new_capacity=1;
        }
        else{
            new_capacity=capacity_*2;
        }
        reserve(new_capacity);
    }
    pointer_to_data[size]=saved;
    size++;
}

//гет размера
template <typename T>
int Dinamic_arr<T>::get_size() const {
    return size;
}


//гет capacity
template <typename T>
int Dinamic_arr<T>::capacity() const {
    return capacity_;
}


//Сложение
template <typename T>
void Dinamic_arr<T>::add(const Dinamic_arr& arr){
    *this+=arr;
}
//Вычитание
template <typename T>
void Dinamic_arr<T>::minus(const Dinamic_arr& arr){
    *this-=arr;
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

