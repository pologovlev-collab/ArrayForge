#include "class.h"
#include <iostream>

int main(){
    Dinamic_arr a(3);

    a.setter(0,10);
    a.setter(1,20);
    a.setter(2,30);

    std::cout<<"Array a:";
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

    return 0;

}