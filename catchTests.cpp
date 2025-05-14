#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "studentClass.h"

TEST_CASE("Studento Rule of Five testai", "[studentas]") {

    SECTION("Copy Konstruktorius") {
        vector<int> pazymiai = {8, 9, 10, 7, 8};
        Studentas originalas("Jonas", "Jonaitis", pazymiai, 9);
        Studentas kopija(originalas);
        
        REQUIRE(kopija == originalas);
    }   

    SECTION("Move konstruktorius") {
        vector<int> pazymiai = {8, 9, 2, 7, 10};
        Studentas original("Petras", "Petraitis", pazymiai, 4);
        Studentas original2("Petras", "Petraitis", pazymiai, 4);
        Studentas movintas(std::move(original));

        REQUIRE(movintas == original2);
        REQUIRE(movintas != original);
    }

    SECTION("Copy assignment operatorius") {
        vector<int> pazymiai = {4, 10, 4, 9, 6};
        Studentas original("Andrius", "Andraitis", pazymiai, 4);
        Studentas kopijuotas;
        kopijuotas = original;

        REQUIRE(kopijuotas == original);
    }

    SECTION("Move assignment operatorius") {
        vector<int> pazymiai = {5, 6, 8, 9, 9};
        Studentas original("Tomas", "Tomaitis", pazymiai, 4);
        Studentas original2("Tomas", "Tomaitis", pazymiai, 4);
        Studentas movintas;
        movintas = std::move(original);

        REQUIRE(movintas == original2);
        REQUIRE(movintas != original);
    }

    SECTION("Destruktorius") {
         Studentas s;
        s.~Studentas();
        
        REQUIRE(s.isClear());
    }
}