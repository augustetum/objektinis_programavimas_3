#include <iostream>
using std::string;

class Zmogus {
    protected:
        string vardas_;
        string pavarde_;
    public:
        Zmogus(){}
        Zmogus(string var, string pav) : vardas_{var}, pavarde_{pav} {}
        //get'eriai
        inline std::string vardas() const { return vardas_; }    
        inline std::string pavarde() const { return pavarde_; } 
        //set'eriai
        inline void setVardas(string var) { vardas_ = var; }
        inline void setPavarde(string pav) { pavarde_ = pav; }

        virtual ~Zmogus() {
            vardas_.clear();
            pavarde_.clear();
        }

        virtual void printInfo() const = 0;
};