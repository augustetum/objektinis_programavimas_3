#define CATCH_CONFIG_MAIN 
#include <catch2/catch_all.hpp>
#include "vector.h"

TEST_CASE("Vector constructors & Rule of Five", "[vector]") {
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
    
}