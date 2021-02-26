#ifndef VECTOR_DYN_ARRAY_H
#define VECTOR_DYN_ARRAY_H

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

    T* p_m;

    explicit dyn_array_iterator(T* p) : p_m(p) { };

    dyn_array_iterator(const dyn_array_iterator& it) : p_m(it.p_m) { }

    dyn_array_iterator& operator++() { ++p_m;return *this; }
    dyn_array_iterator operator++(int) { dyn_array_iterator tmp(*this); operator++(); return tmp; }
    dyn_array_iterator& operator--() { --p_m;return *this; }
    dyn_array_iterator operator--(int) { dyn_array_iterator tmp(*this); operator--(); return tmp; }

//    template<typename B>
//    friend class dyn_array;
//
//    dyn_array_iterator operator+() { ++p_m;return *this; }
//    dyn_array_iterator operator-() { ++p_m;return *this; }
//
//    bool operator>() { ++p_m;return *this; }
//    dyn_array_iterator operator>() { ++p_m;return *this; }

    bool operator==(const dyn_array_iterator& rhs) const { return p_m == rhs.p_m; }
    bool operator!=(const dyn_array_iterator& rhs) const { return p_m != rhs.p_m; }
    typename dyn_array_iterator::reference operator*() { return *p_m; }
};


template<typename T>
class dyn_array {
    T* memory_m;
    size_t memory_size_m{};
    int scaler_m = 2;

    size_t size_m;

public:
    typedef dyn_array_iterator<T, false> iterator;
    typedef dyn_array_iterator<T, true> const_iterator;

    iterator begin() { return iterator(memory_m); }
    iterator end() { return iterator(memory_m + size_m); }

    auto rbegin() { return std::reverse_iterator(end()); }
    auto rend() { return std::reverse_iterator(begin()); }

    const_iterator cbegin() { return const_iterator(memory_m); }
    const_iterator cend() { return const_iterator(memory_m + size_m); }

    auto rcbegin() { return std::reverse_iterator(cend()); }
    auto rcend() { return std::reverse_iterator(cbegin()); }

    T& front() { return memory_m[0]; }
    T& back() {return memory_m[size_m - 1]; }

    explicit dyn_array(size_t size, T value=0) {
        memory_size_m = size * scaler_m;
        memory_m = new T[memory_size_m];
        size_m = size;

        for (int i = 0; i < size_m; ++i) {
            memory_m[i] = value;
        }
    }

    dyn_array(dyn_array&&  other)  noexcept
            : memory_m(other.memory_m)
            , scaler_m(other.scaler_m)
            , size_m(other.size_m)
    {
        other.memory_m = nullptr;
    }

    dyn_array(const dyn_array& other) {
        scaler_m = other.scaler_m;
        size_m = other.size_m;

        memory_m = new T[memory_size_m];
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
        memory_m = new T[memory_size_m];
        for (int i = 0; i < size_m; ++i) {
            memory_m[i] = other.memory_m[i];
        }

        return *this;
    }

    ~dyn_array() {
        delete [] memory_m;
    }

    void push_back(T value) {
        if (size_m >= memory_size_m) {
            resize();
        }

        memory_m[size_m] = value;
        ++size_m;
    }

    size_t size() const {
        return size_m;
    }

    size_t get_memory_size() const {
        return memory_size_m;
    }

    void resize() {
        size_t new_memory_size = memory_size_m * scaler_m;
        T* tmp = new T[new_memory_size];
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

    const T& operator [](size_t idx) const {
        return memory_m[idx];
    }

    T& operator [](int idx) const {
        return memory_m[idx];
    }
};

#endif //VECTOR_DYN_ARRAY_H
