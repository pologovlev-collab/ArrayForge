#include "class.h"
#include <iostream>
#include <stdexcept>

int main(){
    Dinamic_arr a(3);

    a.setter(0,10);
    a.setter(1,20);
    a.setter(2,30);

    std::cout<<"Array a: ";
    a.show();
    std::cout<<"\n";

    Dinamic_arr copy(a);
    std::cout<<"copy: ";
    copy.show();
    std::cout << "\n";

    copy.push_back(40);

    std::cout << "After push_back: ";
    copy.show();
    std::cout << "\n";

    Dinamic_arr b(2);
    b.setter(0, 5);
    b.setter(1, 10);

    a.add(b);

    std::cout << "After add: ";
    a.show();
    std::cout << "\n";

    a.minus(b);

    std::cout << "After minus: ";
    a.show();
    std::cout << "\n";
    
    //out_of_range
    try{
        std::cout<<a.getter(10);
    }
    catch( const std::out_of_range& error){
        std::cout<<"out_of_range: "<<error.what()<<std::endl;
    }

    //invalid_argument
    try{
        a.setter(0,500);
    }
    catch( const std::invalid_argument& error){
        std::cout<<"invalid_argument: "<<error.what()<<std::endl;
    }

    //bad_alloc
    try{
        throw std::bad_alloc();
    }
    catch (const std::bad_alloc& error){
        std::cout<<"bad_aloc: "<<error.what(); 
    }

    return 0;

}