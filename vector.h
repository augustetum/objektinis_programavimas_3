#include <iostream>

template <typename T, typename Allocator = std::allocator<T>>

class Vector{
private:
  size_t size;    
  size_t capacity;    
  T* data;

public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using const_pointer = Allocator::const_pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>
    using const_reverse_iterator = std::reverse_iterator<const_iterator>

//member functions
//constructors
    Vector() : size(0), capacity(1) { data = new T[capacity]};

    Vector(T array[], int n){
        data = new T[n]; //reserves the same space as the array passed
        for(int i = 0; i < n; i++){
            data[i] = array[i];
        }
        size = n;
    }

    Vector(const Vector& other): size(other.size), capacity(other.capacity){
        data = new T[capacity];
        for(size_t i=0; i<size; i++) {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other){
        if(this == &other) return *this;

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for(size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other);

    void push_back(const T& item);
    void pop_back();

    size_type size() const;
    size_type capacity() const;

    T& operator[](size_type index);

    
    ~Vector(){
        size = 0;
        capacity = 0;
        delete[] data;
    }
};

//non-member functions
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs ){}
template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs ){}
template <typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs ){}
template <typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs ){}