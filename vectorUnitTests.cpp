#define CATCH_CONFIG_MAIN 
#include <catch2/catch_all.hpp>
#include "vector.h"

TEST_CASE("Vector constructors & Rule of Five", "[Vector]") {
    SECTION("Default constructor") {
        Vector<int> v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 1);
        REQUIRE(v.empty());
    }

     SECTION("List constructor") {
        Vector<int> v = {6, 7, 8, 10, 8};
        int arr[] = {6, 7, 8, 10, 8};
        REQUIRE(v.size() == 5);
        for (int i = 0; i < v.size(); ++i) {
            REQUIRE(v.at(i) == arr[i]);
        }
    }

    SECTION("Array constructor") {
        int arr[] = {10, 20, 30};
        int n = sizeof(arr) / sizeof(arr[0]);
        Vector<int> v(arr, n);
        REQUIRE(v.size() == 3);
        for (int i = 0; i < v.size(); ++i) {
            REQUIRE(v.at(i) == arr[i]);
        }
    }

    SECTION("Copy constructor") {
        Vector<int> original = {1, 2, 3, 4};
        Vector<int> copy(original);

        REQUIRE(copy.size() == original.size());
        REQUIRE(copy.capacity() == original.capacity());

        for (size_t i = 0; i < original.size(); ++i) {
            REQUIRE(copy.at(i) == original.at(i));
        }

        copy.at(0) = 99;
        REQUIRE(original.at(0) == 1);
        REQUIRE(copy.at(0) == 99);
    }

    SECTION("Copy assignment operator") {
        Vector<int> original = {5, 6, 7};
        Vector<int> copy;
        copy = original;

        REQUIRE(copy.size() == original.size());
        REQUIRE(copy.capacity() == original.capacity());

        for (size_t i = 0; i < original.size(); ++i) {
            REQUIRE(copy.at(i) == original.at(i));
        }

        copy.at(1) = 42;
        REQUIRE(original.at(1) == 6);
        REQUIRE(copy.at(1) == 42);
    }

    SECTION("Move constructor") {
        Vector<int> source = {10, 20, 30};
        Vector<int> moved(std::move(source));

        REQUIRE(moved.size() == 3);
        REQUIRE(moved.at(0) == 10);
        REQUIRE(moved.at(1) == 20);
        REQUIRE(moved.at(2) == 30);

        REQUIRE(source.size() == 0);
    }

    SECTION("Move assignment operator") {
        Vector<int> source = {7, 8, 9};
        Vector<int> target;
        target = std::move(source);

        REQUIRE(target.size() == 3);
        REQUIRE(target.at(0) == 7);
        REQUIRE(target.at(1) == 8);
        REQUIRE(target.at(2) == 9);
        REQUIRE(source.size() == 0);
    }

    SECTION("Assign"){
        Vector<int> intVec;
        intVec.push_back(1);
        intVec.push_back(2);
        
        REQUIRE(intVec.size() == 2);
        REQUIRE(intVec[0] == 1);
        REQUIRE(intVec[1] == 2);
        
        intVec.assign(5, 10);
        
        REQUIRE(intVec.size() == 5);
        for (size_t i = 0; i < intVec.size(); ++i) {
            REQUIRE(intVec[i] == 10);
        }
    }
}

TEST_CASE("Element access", "[vector]"){
    Vector<int> v = {10, 20, 30, 40, 50};

    SECTION("at()") {
        REQUIRE(v.at(0) == 10);
        REQUIRE(v.at(4) == 50);
        REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(100), std::out_of_range);
    }

    SECTION("operator[]") {
        REQUIRE(v[1] == 20);
        REQUIRE(v[3] == 40);
        REQUIRE_THROWS_AS(v[5], std::out_of_range);
    }

    SECTION("front()") {
        REQUIRE(v.front() == 10);

        const Vector<int> constV = v;
        REQUIRE(constV.front() == 10);
    }

    SECTION("back()") {
        REQUIRE(v.back() == 50);
        const Vector<int> constV = v;
        REQUIRE(constV.back() == 50);
    }

    SECTION("data()") {
        int* ptr = v.data();
        REQUIRE(ptr[0] == 10);
        REQUIRE(ptr[4] == 50);

        const Vector<int> constV = v;
        const int* ptrV = constV.data();
        REQUIRE(ptrV[0] == 10);
        REQUIRE(ptrV[4] == 50);
    }
}


TEST_CASE("Capacity", "[Vector]"){
    Vector<int> v;

    SECTION("empty()") {
        REQUIRE(v.empty());
        REQUIRE(v.size() == 0);
    }

    SECTION("size() and capacity()") {
        v.push_back(1);
        v.push_back(2);

        REQUIRE_FALSE(v.empty());
        REQUIRE(v.size() == 2);
        REQUIRE(v.capacity() >= 2);  
    }

    SECTION("max_size()") {
        REQUIRE(v.max_size() > 100000);  
    }

    SECTION("reserve()") {
        size_t oldCap = v.capacity();
        v.reserve(oldCap + 10);
        REQUIRE(v.capacity() == oldCap + 10);
    }

    SECTION("reserve()") {
        v.reserve(100);
        size_t cap = v.capacity();
        v.reserve(50);  
        REQUIRE(v.capacity() == cap);
    }

    SECTION("shrink_to_fit()") {
        for (int i = 0; i < 5; ++i) {
            v.push_back(i);
        }
        v.reserve(100);
        REQUIRE(v.capacity() >= 100);
        v.shrink_to_fit();
        REQUIRE(v.capacity() == v.size());
    }
}

TEST_CASE("Modifiers", "[Vector]"){
    SECTION("clear()"){
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.clear();

        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 0);
    }

    SECTION("insert()"){
        Vector<int> v;
        v.push_back(1);
        v.push_back(3);

        auto it = v.insert(v.begin() + 1, 2);  

        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 3);
        REQUIRE(*it == 2);

        Vector<int> v2;
        REQUIRE_THROWS_AS(v.insert(v2.begin() + 1, 10), std::out_of_range);
    }

    SECTION("erase() (single element)"){
         Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);

        auto it = v.erase(v.begin() + 1); 

        REQUIRE(v.size() == 2);
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 3);
        REQUIRE(*it == 3);
    }

    SECTION("erase() (range)"){
        Vector<int> v;
        for (int i = 1; i <= 5; ++i){
            v.push_back(i);
        }

        auto it = v.erase(v.begin() + 1, v.begin() + 4); 

        REQUIRE(v.size() == 2);
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 5);
        REQUIRE(*it == 5);
    }

    SECTION("push_back()"){
        Vector<int> v;
        v.push_back(42);

        REQUIRE(v.size() == 1);
        REQUIRE(v.at(0) == 42);
    }

     SECTION("pop_back()"){
        Vector<int> v;
        v.push_back(10);
        v.push_back(20);
        v.pop_back();

        REQUIRE(v.size() == 1);
        REQUIRE(v.at(0) == 10);
    }

    SECTION("resize()"){
        Vector<int> v;
        v.reserve(2);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3); 

        REQUIRE(v.size() == 3);
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 3);
        REQUIRE(v.capacity() >= 3);
    }

    SECTION("swap()"){
        Vector<int> a, b;
        a.push_back(1);
        a.push_back(2);
        b.push_back(10);

        a.swap(b);

        REQUIRE(a.size() == 1);
        REQUIRE(a.at(0) == 10);
        REQUIRE(b.size() == 2);
        REQUIRE(b.at(0) == 1);
        REQUIRE(b.at(1) == 2);
    }
}

TEST_CASE("Operators", "[Vector]"){

    SECTION("== operator"){
        Vector<int> a = {1,2,3,4,5};
        Vector<int> b = {1,2,3,4,5};
        REQUIRE(a==b);
    }

    SECTION("!= operator"){
        Vector<int> a = {1,2,3,4,5};
        Vector<int> b = {3,2,3,4,5};
        REQUIRE(a!=b);
    }
}

