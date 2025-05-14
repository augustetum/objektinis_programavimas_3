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

    Vector(Vector&& other) noexcept : data(other.data), size(other.size), 
    capacity(other.capacity) {
        other.clear();
    }

    Vector& operator=(Vector&& other){
        if(this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.clear();

        return *this;
    }

    void clear(){
        size = 0;
        capacity = 0;
        delete[] data;
    }

    void resize(){
        capacity *= 2;
        T* new_data = new T[capacity];
        for(size_t i=0; i<size; i++){
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

    void push_back(const T& item){
        if(size == capacity) {
            resize();
        }
        data[size] = item;
        ++size;
    }

    void pop_back(){
        if(size > 0){
            --size;
        }
    }
    
    ~Vector(){
       clear();
    }

    //element access
    T& at(int pos){
        if(pos >= size){
            throw std::out_of_range("Index out of bounds");
        }
        return data[pos];
    }

    T& operator[](size_t index){
        if (index >= size){
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    T& front(){
        return at(0);
    }

    T& back(){
        return at(size-1);
    }

    const T& front() const{
        return at(0);
    }

    const T& back() const{
        return at(size-1);
    }

    T* data(){
        return data;
    }

    const T* data() const {
        return data;
    }

//iterators
    T* begin(){
        return data;
    }

    const T* begin() const {
        return data;
    }

    T* end(){
        return data + size;
    }

    const T* end() const{
        return data + size;
    }

//capacity
    bool empty(){
        return size == 0;
    }

    size_type size() const{ return size; }

    size_type max_size() const{
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    void reserve(size_type new_cap ){
        if (new_cap > capacity){
            capacity = new_cap;
        }
    }

    size_type capacity() const{return capacity; }

    void shrink_to_fit(){
        capacity = size;
    }

//modifiers


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