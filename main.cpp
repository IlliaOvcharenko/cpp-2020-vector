#include<iostream>
#include <algorithm>
#include <string>

#include "src/dyn_array.h"

template<typename T>
void print_dyn_array(dyn_array<T>& arr) {
    for (auto& el: arr) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    std::cout << "test string array" << std::endl;
    dyn_array<std::string> da_1(10, "value");
    print_dyn_array(da_1);
    std::cout << std::endl;

    std::cout << "test array change/increase" << std::endl;
    dyn_array<int> da_2(10, 17);
    for (int i = 0; i < 5; ++i) {
        da_2.push_back(23);
    }
    da_2[0] = 99;
    da_2[10] = 99;
    print_dyn_array(da_2);
    std::cout << "visible array size: " << da_2.size() << std::endl;
    std::cout << "internal array size: " << da_2.get_memory_size() << std::endl;
    std::cout << std::endl;

    std::cout << "test copy constructor" << std::endl;
    dyn_array da_3 = da_2;
    print_dyn_array(da_3);

    return 0;
}