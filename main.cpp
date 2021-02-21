#include<iostream>

// TODO create template
// TODO add iterator
// TODO prevent leakage in case of init error
// TODO make fields private


template<typename T, bool is_const>
class dyn_array_iterator {
public:
    typedef typename std::conditional<is_const, const T, T>::type value_type;
    typedef ptrdiff_t difference_type;
    typedef typename std::conditional<is_const, const T*, T*>::type pointer;
    typedef typename std::conditional<is_const, const T&, T&>::type reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    friend class dyn_array;

    T* p_m;

    explicit dyn_array_iterator(T* p) : p_m(p) { };

    dyn_array_iterator(const dyn_array_iterator& it) : p_m(it.p_m) { }

    dyn_array_iterator& operator++() { ++p_m;return *this; }
    dyn_array_iterator operator++(int) { dyn_array_iterator tmp(*this); operator++(); return tmp; }
    dyn_array_iterator& operator--() { --p_m;return *this; }
    dyn_array_iterator operator--(int) { dyn_array_iterator tmp(*this); operator--(); return tmp; }

//    dyn_array_iterator operator+() { ++p_m;return *this; }
//    dyn_array_iterator operator-() { ++p_m;return *this; }
//
//    bool operator>() { ++p_m;return *this; }
//    dyn_array_iterator operator>() { ++p_m;return *this; }


    bool operator==(const dyn_array_iterator& rhs) const { return p_m == rhs.p_m; }
    bool operator!=(const dyn_array_iterator& rhs) const { return p_m != rhs.p_m; }
    typename dyn_array_iterator::reference operator*() { return *p_m; }
};


class dyn_array {
public:
    int* memory_m;
    size_t memory_size_m;
    int scaler_m = 2;

    size_t size_m;

    typedef dyn_array_iterator<int, false> iterator;
    typedef dyn_array_iterator<int, true> const_iterator;

    iterator begin() { return iterator(memory_m); }
    iterator end() { return iterator(memory_m + size_m); }

    auto rbegin() { return std::reverse_iterator(end()); }
    auto rend() { return std::reverse_iterator(begin()); }

    const_iterator cbegin() { return const_iterator(memory_m); }
    const_iterator cend() { return const_iterator(memory_m + size_m); }

    auto rcbegin() { return std::reverse_iterator(cend()); }
    auto rcend() { return std::reverse_iterator(cbegin()); }

    int& front() { return memory_m[0]; }
    int& back() {return memory_m[size_m - 1]; }

    explicit dyn_array(size_t size, int value=0) {
        memory_size_m = size * scaler_m;
        memory_m = new int[memory_size_m];
        size_m = size;

        for (int i = 0; i < size_m; ++i) {
            memory_m[i] = value;
        }
    }

    dyn_array(const dyn_array& other) {
        memory_size_m = other.memory_size_m;
        scaler_m = other.scaler_m;
        size_m = other.size_m;

        memory_m = new int[memory_size_m];
        for (int i = 0; i < size_m; ++i) {
            memory_m[i] = other.memory_m[i];
        }
    }

    dyn_array& operator =(const dyn_array& other) {
        if (this == &other) {
            return *this;
        }

        memory_size_m = other.memory_size_m;
        scaler_m = other.scaler_m;
        size_m = other.size_m;

        delete [] memory_m;
        memory_m = new int[memory_size_m];
        for (int i = 0; i < size_m; ++i) {
            memory_m[i] = other.memory_m[i];
        }

        return *this;
    }

    ~dyn_array() {
        delete [] memory_m;
    }

    void push_back(int value) {
        if (size_m >= memory_size_m) {
            resize();
        }

        memory_m[size_m] = value;
        ++size_m;
    }

    size_t size() const {
        return size_m;
    }


    void resize() {
        size_t new_memory_size = memory_size_m * scaler_m;
        int* tmp = new int[new_memory_size];
        for (int i = 0; i < memory_size_m; ++i) {
            tmp[i] = memory_m[i];
        }
        memory_size_m = new_memory_size;
        memory_m = tmp;
    }

//    const int& get(size_t idx) const {
//        return memory_m[idx];
//    }
//
//    int& set(size_t idx, int value) {
//        return memory_m[idx] = value;
//    }

    const int& operator [](size_t idx) const {
        return memory_m[idx];
    }

    int& operator [](int idx) const {
        return memory_m[idx];
    }
};

int main(int argc, const char * argv[]) {
    std::cout <<  "Dynamic array test" << std::endl;


    dyn_array da_1(10);
    std::cout << "first array size: " << da_1.size() << std::endl;
    for (int i = 0; i < da_1.size(); ++i) {
        std::cout << da_1[i] << " ";
    }
    std::cout << std::endl;


    dyn_array da_2(20, 17);
    std::cout << "second array size: " << da_2.size() << std::endl;
    for (int i = 0; i < da_2.size(); ++i) {
        std::cout << da_2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "array internal size: " << da_2.memory_size_m << std::endl;
    std::cout << "~~~~~~~~~~~~~~" << std::endl;


    for (int i = 0; i < 100; ++i) {
        da_2.push_back(23);
    }


    std::cout << "second array size: " << da_2.size() << std::endl;
    for (int i = 0; i < da_2.size(); ++i) {
        std::cout << da_2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "array internal size: " << da_2.memory_size_m << std::endl;
    std::cout << "~~~~~~~~~~~~~~" << std::endl;



    da_2[0] = 9999;
    da_2[23] = 9999;

// TODO wtf? why not an out of bound error
    da_2[123] = 9999;
    std::cout << "second array size: " << da_2.size() << std::endl;
    for (int i = 0; i < da_2.size(); ++i) {
        std::cout << da_2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "array internal size: " << da_2.memory_size_m << std::endl;
    std::cout << "~~~~~~~~~~~~~~" << std::endl;


    dyn_array da_3 = da_2;
    std::cout << "second array size: " << da_3.size() << std::endl;
    for (int i = 0; i < da_3.size(); ++i) {
        std::cout << da_3[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "array internal size: " << da_3.memory_size_m << std::endl;
    std::cout << "~~~~~~~~~~~~~~" << std::endl;

    dyn_array da_4 = da_2;
    std::cout << "check forward iterator: before increment" << std::endl;
    for (auto& el: da_4) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    for (auto& el: da_4) {
        el++;
    }
    std::cout << "check forward iterator: after increment" << std::endl;

    for (auto& el: da_4) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    std::cout << "check reverse iterator" << std::endl;

    for (auto it = da_4.rcbegin(); it != da_4.rcend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "array internal size: " << da_3.memory_size_m << std::endl;
    std::cout << "~~~~~~~~~~~~~~" << std::endl;
    std::reverse(da_4.begin(), da_4.end());
    for (auto& el: da_4) {
        std::cout << el << " ";
    }
    std::cout << std::endl;


//    auto it = da_4.cbegin();
//    *it = 1;

    std::cout << "arr front: " << da_4.front() << " arr back: " << da_4.back() << std::endl;
    return 0;
}