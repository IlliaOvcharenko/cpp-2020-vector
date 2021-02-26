#include<iostream>
#include <algorithm>
#include <string>

#include "src/dyn_array.h"


int main(int argc, const char * argv[]) {
    std::cout <<  "Dynamic array test" << std::endl;


    dyn_array<std::string> da_1(10, "test");
    std::cout << "first array size: " << da_1.size() << std::endl;
    for (int i = 0; i < da_1.size(); ++i) {
        std::cout << da_1[i] << " ";
    }
    std::cout << std::endl;

//
    dyn_array<int> da_2(20, 17);
    std::cout << "second array size: " << da_2.size() << std::endl;
    for (int i = 0; i < da_2.size(); ++i) {
        std::cout << da_2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "array internal size: " << da_2.get_memory_size() << std::endl;
    std::cout << "~~~~~~~~~~~~~~" << std::endl;
//
//
//    for (int i = 0; i < 100; ++i) {
//        da_2.push_back(23);
//    }

//
//    std::cout << "second array size: " << da_2.size() << std::endl;
//    for (int i = 0; i < da_2.size(); ++i) {
//        std::cout << da_2[i] << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "array internal size: " << da_2.get_memory_size() << std::endl;
//    std::cout << "~~~~~~~~~~~~~~" << std::endl;
//
//
//
//    da_2[0] = 9999;
//    da_2[23] = 9999;
//
//// TODO wtf? why not an out of bound error
//    da_2[123] = 9999;
//    std::cout << "second array size: " << da_2.size() << std::endl;
//    for (int i = 0; i < da_2.size(); ++i) {
//        std::cout << da_2[i] << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "array internal size: " << da_2.get_memory_size() << std::endl;
//    std::cout << "~~~~~~~~~~~~~~" << std::endl;
//
//
//    dyn_array da_3 = da_2;
//    std::cout << "second array size: " << da_3.size() << std::endl;
//    for (int i = 0; i < da_3.size(); ++i) {
//        std::cout << da_3[i] << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "array internal size: " << da_3.get_memory_size() << std::endl;
//    std::cout << "~~~~~~~~~~~~~~" << std::endl;
//
//    dyn_array da_4 = da_2;
//    std::cout << "check forward iterator: before increment" << std::endl;
//    for (auto& el: da_4) {
//        std::cout << el << " ";
//    }
//    std::cout << std::endl;
//
//    for (auto& el: da_4) {
//        el++;
//    }
//    std::cout << "check forward iterator: after increment" << std::endl;
//
//    for (auto& el: da_4) {
//        std::cout << el << " ";
//    }
//    std::cout << std::endl;
//
//    std::cout << "check reverse iterator" << std::endl;
//
//    for (auto it = da_4.rcbegin(); it != da_4.rcend(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "array internal size: " << da_3.get_memory_size() << std::endl;
//    std::cout << "~~~~~~~~~~~~~~" << std::endl;
//    std::reverse(da_4.begin(), da_4.end());
//    for (auto& el: da_4) {
//        std::cout << el << " ";
//    }
//    std::cout << std::endl;


//    auto it = da_4.cbegin();
//    *it = 1;

//    std::cout << "arr front: " << da_4.front() << " arr back: " << da_4.back() << std::endl;
    return 0;
}