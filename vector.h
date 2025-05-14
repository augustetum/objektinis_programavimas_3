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
    Vector(){
        data = NULL;
        size = 0;
    }

    Vector(T array[], int n){
        data = new T[n]; //reserves the same space as the array passed
        for(int i = 0; i < n; i++){
            data[i] = array[i];
        }
        size = n;
    }

    ~Vector();

    void push_back(const T& item){

    }

    void size(){

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