#pragma once
class Dinamic_arr{
    private:
        int* pointer_to_data;
        int size;
        const int MIN=-100;
        const int MAX=100;
    public:
        int getter(int index);
        void setter(int index,int num);
        Dinamic_arr(int size);
        ~Dinamic_arr();
        void show();
        Dinamic_arr(const Dinamic_arr& array_copy);
        void push_back(int num);
        void add(const Dinamic_arr & arr);
        void minus(const Dinamic_arr & arr);

};