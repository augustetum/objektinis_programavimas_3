#include <iostream>

template <typename T, typename Allocator = std::allocator<T>>
class Vector{
private:
  size_t size_;    
  size_t capacity_;    
  T* data_;

public:
    using value_type = T;
    using pointer = T*;
    using iterator = pointer;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using const_pointer = typename Allocator::const_pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;

//member functions
//constructors
    //default constructor
    Vector() : size_(0), capacity_(1) { data_ = new T[capacity_];}

    //array constructor
    Vector(T array[], int n){
        data_ = new T[n]; //reserves the same space as the array passed
        for(int i = 0; i < n; i++){
            data_[i] = array[i];
        }
        size_ = n;
    }

    //list constructor
    Vector(std::initializer_list<T> init) {
        size_ = init.size();
        capacity_ = size_;
        data_ = new T[capacity_];

        size_t i = 0;
        for (const T& value : init) {
            data_[i] = value;
            i++;
        }
    }

    //copy constructor
    Vector(const Vector& other): size_(other.size_), capacity_(other.capacity_){
        data_ = new T[capacity_];
        for(size_t i=0; i<size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    //copy assignment operator
    Vector& operator=(const Vector& other){
        if(this == &other) return *this;

        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for(size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    //move constructor
    Vector(Vector&& other) noexcept 
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr; 
        other.size_ = 0;
        other.capacity_ = 0;
    }

    //move assignment operator
    Vector& operator=(Vector&& other) noexcept{
        if(this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }
    
    ~Vector(){
       clear();
    }

    void assign(size_type count, const T& value) {
        clear();
        if (count > capacity_) {
            delete[] data_;
            capacity_ = count;
            data_ = new T[capacity_];
        } else {
            if (data_ == nullptr) {
                data_ = new T[capacity_];
            }
        }
        
        for (size_type i = 0; i < count; ++i) {
            data_[i] = value;
        }
        size_ = count;
    }

template <typename InputIt>
void assign(InputIt first, InputIt last) {
    size_type count = std::distance(first, last);
    clear();
    
    if (count > capacity_) {
        if (data_ != nullptr) {
            delete[] data_;
        }
        capacity_ = count;
        data_ = new T[capacity_];
    } else if (data_ == nullptr) {
        capacity_ = count > 0 ? count : 1; 
        data_ = new T[capacity_];
    }
    
    size_ = 0; 
    for (; first != last; ++first) {
        if (size_ < capacity_) {
            data_[size_++] = *first;
        }
    }
}

    //element access
    T& at(int pos){
        if(pos >= size_){
            throw std::out_of_range("Index out of bounds");
        }
        return data_[pos];
    }

    const T& at(int pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[pos];
    }

    T& operator[](size_t index){
        if (index >= size_){
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }

    T& front(){
        return at(0);
    }

    T& back(){
        return at(size_-1);
    }

    const T& front() const{
        return at(0);
    }

    const T& back() const{
        return at(size_-1);
    }

    T* data(){
        return data_;
    }

    const T* data() const {
        return data_;
    }

//iterators
    T* begin(){
        return data_;
    }

    const T* begin() const {
        return data_;
    }

    T* end(){
        return data_ + size_;
    }

    const T* end() const{
        return data_ + size_;
    }

//capacity
    bool empty(){
        return size_ == 0;
    }

    size_type size() const{ return size_; }

    size_type max_size() const{
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    void reserve(size_type new_cap ){
        if (new_cap > capacity_) {
            T* new_data = new T[new_cap];
            for (size_type i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }
    }

    size_type capacity() const{return capacity_; }

    void shrink_to_fit(){
        if (capacity_ > size_) {
            T* new_data = new T[size_];
            for (size_type i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

//modifiers
    void clear(){
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
        data_ = nullptr;
    }

    iterator insert(iterator pos, const T& value){
        size_t index = pos - begin();

        if(index > size_){
            throw std::out_of_range("Invalid position");
        }
        if(size_ == capacity_){
            resize();
        } 
        size_++;
        for(size_t i = size_-1; i > index; --i){
            data_[i]=data_[i-1];
        }
        data_[index]=value;
        ++size_;

        return begin() + index; 
    }

   iterator erase(const_iterator pos) {
        if(pos < begin() || pos >= end()) {
            throw std::out_of_range("Invalid position");
        }
    
        size_t index = std::distance(static_cast<const T*>(begin()), pos);
    
        for(size_t i = index; i < size_ - 1; i++) {
            data_[i] = data_[i+1];
        }
    --size_;

    return begin() + index;
    }   
    
    iterator erase(const_iterator first, const_iterator last ){
        size_t pos_first = std::distance(static_cast<const T*>(begin()), first);
        size_t pos_last = std::distance(static_cast<const T*>(begin()), last);
        size_t count = pos_last - pos_first;
    
        if (count == 0) {
            return begin() + pos_first;
        }
        
        for (size_t i = pos_first; i + count < size_; ++i) {
            data_[i] = data_[i + count];
        }
    
        size_ -= count;
    
        return begin() + pos_first;
    }
    
    void push_back(const T& item){
        if(size_ == capacity_) {
            resize();
        }
        data_[size_] = item;
        ++size_;
    }

    void append_range(){

    }

    void pop_back(){
        if(size_ > 0){
            --size_;
        }
    }

    void resize(){
        capacity_ *= 2;
        T* new_data = new T[capacity_];
        for(size_t i=0; i<size_; i++){
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }

    void resize(size_t newSize) {
    
    if (newSize > capacity_) {
   
        size_t newCapacity = std::max(newSize, capacity_ * 2);
        
  
        T* new_data = new T[newCapacity];
        
      
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        
        for (size_t i = size_; i < newSize; i++) {
            new_data[i] = T(); 
        }
        
        delete[] data_;
        data_ = new_data;
        capacity_ = newCapacity;
    }
   
    else if (newSize > size_) {
        for (size_t i = size_; i < newSize; i++) {
            data_[i] = T(); 
        }
    }
    size_ = newSize;
}

    void swap(Vector& other){
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }
};

//non-member functions
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs ){
    if(lhs.size() != rhs.size()){
        return false;
    }

    for(size_t i = 0; i < lhs.size(); ++i) {
        if(lhs.at(i) != rhs.at(i)){
            return false;
        }
    }

    return true;
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs ){
    if(lhs.size() != rhs.size()){
        return true;
    }

    for(size_t i = 0; i < lhs.size(); ++i) {
        if(lhs.at(i) != rhs.at(i)){
            return true;
        }
    }

    return false;
}
