#include <iostream>

template <typename T, typename Allocator = std::allocator<T>>

class Vector{
private:
  int sz;        
  double *elem;  
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

//member functions
//constructor
    Vector();

    Vector(int s);

    Vector(int s, double val);

//destructor
    ~Vector();

    Vector& operator=( const Vector& other );

    void assign(size_type count, const T& value);

    template <typename InputIt>
    void assign(InputIt first, InputIt last);

    void assign(std::initializer_list<T> ilist);

    template< container-compatible-range<T> R >
    constexpr void assign_range( R&& rg );

    allocator_type get_allocator() const;

};
