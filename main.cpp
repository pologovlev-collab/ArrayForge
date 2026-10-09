#include "class.h"
#include <iostream>
#include <stdexcept>

int main(){
    Dinamic_arr<int> a(3);
    Dinamic_arr<int> x(5);

    a.setter(0,10);
    a.setter(1,20);
    a.setter(2,30);
    x.setter(0,10);
    x.setter(1,20);
    x.setter(2,30);
    x.setter(3,20);
    x.setter(4,30);
    //вывод
    std::cout<<"Array a: "<<a<<"\n";

    //геттер
    std::cout<<"A[1]: "<<a.getter(1)<<"\n";

    //сеттер и копирование
    Dinamic_arr <int> copy(a);
    copy.setter(0, 50);
    std::cout << "Original A: " << a << "\n";
    std::cout << "Copy: " << copy << "\n";

    //проверка пушбека
    copy.push_back(40);
    std::cout << "After push_back: "<<copy << "\n";

    //сложение
    Dinamic_arr<int> b(2);
    b.setter(0, 5);
    b.setter(1, 10);

    a.add(b);

    std::cout << "After add: "<<a << "\n";

    //минус
    a.minus(b);

    std::cout << "After minus: "<<a<< "\n";
    
    //out_of_range
    try{
        std::cout<<a.getter(10);
    }
    catch( const std::out_of_range& error){
        std::cerr<<"out_of_range: "<<error.what()<<std::endl;
    }

    //invalid_argument
    try{
        a.setter(0,500);
    }
    catch( const std::invalid_argument& error){
        std::cerr<<"invalid_argument: "<<error.what()<<std::endl;
    }

    //bad_alloc
    try{
        throw std::bad_alloc();
    }
    catch (const std::bad_alloc& error){
        std::cerr<<"bad_aloc: "<<error.what(); 
    }

    //стрики
    Dinamic_arr<std::string> words(2);

    words.setter(0,"HEllo");
    words.setter(1,"C++");

    words.push_back("Temp");
    std::cout<<"Words :"<<words<<"\n";

    // расстояние между строками
    try {
        Dinamic_arr<std::string> other(3);

        std::cout << words.distance(other);
    }
    catch (const std::bad_typeid& error) {
        std::cerr << "bad_typeid: "<< error.what() << "\n";
    }


    // Ошибка: разные размеры массивов
    try {
        std::cerr << x.distance(a);
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "Different sizes: "<< error.what() << "\n";
    }

    return 0;

}