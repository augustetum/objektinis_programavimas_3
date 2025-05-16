#ifndef MANO_LIB_H
#define MANO_LIB_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <numeric>
#include <ctime>
#include <sstream>
#include <chrono>
#include <unordered_set>
#include <limits>
#include <ios>
#include "timer.h"
#include "humanClass.h"
#include "vector.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::accumulate;
using std::ifstream;
using std::istringstream;

class Studentas : public Zmogus {
    private:
        int egzaminas_;
        double galutinisMed_;
        double galutinisVid_;
        double pazymiuVidurkis_;
        Vector<int> pazymiai_;
    
    public:
        Studentas(string var, string pav, Vector<int> paz, int egz) :  
        Zmogus(var, pav), pazymiai_{paz}, egzaminas_{egz} {
            skaiciuotiGalutiniSuMed();
            skaiciuotiGalutiniSuVid();
        }

        Studentas(string var, string pav) : Zmogus(var, pav), egzaminas_(0) {
        }
        Studentas() : Zmogus(), egzaminas_(0) {} 
        Studentas(std::istream& is);

        //copy konstruktorius
        Studentas(const Studentas &s)
        : Zmogus(s.vardas(), s.pavarde()), egzaminas_{s.egzaminas_}, 
        galutinisMed_{s.galutinisMed_}, galutinisVid_{s.galutinisVid_}, pazymiuVidurkis_{s.pazymiuVidurkis_},
        pazymiai_{s.pazymiai_}{}

        //move konstruktorius
        Studentas(Studentas&& s)
        : Zmogus(s.vardas(), s.pavarde()), egzaminas_{s.egzaminas_}, 
        galutinisMed_{s.galutinisMed_}, galutinisVid_{s.galutinisVid_}, pazymiuVidurkis_{s.pazymiuVidurkis_},
        pazymiai_{std::move(s.pazymiai_)}{
            s.clearStud();
        }

        //destruktorius
        ~Studentas() override{
            clearStud();
        };

        //get'eriai
        inline double galutinisMed() const { return galutinisMed_;}
        inline double galutinisVid() const { return galutinisVid_;}
        inline const Vector<int>& pazymiai() const { return pazymiai_; }
        inline int egzaminas() const { return egzaminas_; }

        //set'eriai
        inline void setGalutinisV(double galutVid) { galutinisVid_ = galutVid; }
        inline void setGalutinisM(double galutMed) { galutinisMed_ = galutMed; }
        inline void setEgzaminas(int egz) {egzaminas_ = egz; }
        inline void setPazymiai(Vector<int> paz) {pazymiai_ = paz;}

        //member funkcijos
        void skaiciuotiGalutiniSuVid();
        void skaiciuotiGalutiniSuMed();

        //copy assignment operatorius 
        Studentas& operator=(const Studentas& s){
            if (this == &s) return *this;

            setVardas(s.vardas());
            setPavarde(s.pavarde());
            egzaminas_ = s.egzaminas_;
            galutinisMed_ = s.galutinisMed_;
            galutinisVid_ = s.galutinisVid_;
            pazymiuVidurkis_ = s.pazymiuVidurkis_;
            pazymiai_ = s.pazymiai_;
            
            return *this;
        }

        //move assignment operatorius
        Studentas& operator =(Studentas&& s){
            if (this == &s) return *this;

            setVardas(s.vardas());
            setPavarde(s.pavarde());
            egzaminas_ = s.egzaminas_;
            galutinisMed_ = s.galutinisMed_;
            galutinisVid_ = s.galutinisVid_;
            pazymiuVidurkis_ = s.pazymiuVidurkis_;
            pazymiai_ = std::move(s.pazymiai_);
            s.clearStud();
            
            return *this;
        }
        
        //palyginimo operatorius
        bool operator== (const Studentas& s) const{
            if(vardas_ == s.vardas_ && pavarde_ == s.pavarde_ && egzaminas_ == s.egzaminas_
            && pazymiai_ == s.pazymiai_){
                return true;
            } else {
                return false;
            }
        }
        
         bool operator!= (const Studentas& s) const{
            if(vardas_ != s.vardas_ && pavarde_ != s.pavarde_ && egzaminas_ != s.egzaminas_
            && pazymiai_ != s.pazymiai_){
                return true;
            } else {
                return false;
            }
        }

        //output operatorius
        friend std::ostream& operator<<(std::ostream& out, const Studentas &s);

        //input operatorius
        friend std::istream& operator>>(std::istream& cin, Studentas& s);
        
        void printInfo() const override {
            cout << "Vardas: " << vardas() << ", Pavarde: " << pavarde() << endl;
        }

        void clearStud (){
            this->vardas_.clear();
            this->pavarde_.clear();
            egzaminas_ = 0;
            galutinisMed_ = 0;
            galutinisVid_ = 0;
            pazymiuVidurkis_ = 0;
            pazymiai_.clear();
        }

        bool isClear(){
            if(this->vardas_.empty() && this -> pavarde_.empty() && pazymiai_.empty() && egzaminas_ == 0 && galutinisMed_ == 0 && galutinisVid_ == 0 && 
            pazymiuVidurkis_ == 0) {
                return true;
            } else {
                return false;
            }
        }
};

bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalEgza(const Studentas&, const Studentas&);

void rodytiRezultatus(Vector<Studentas> studentuSarasas);
void generuotiPazymius(Vector<Studentas> &studentuSarasas);
void generuotiStudentus(Vector<Studentas> &studentuSarasas);
void generuotiFailus(int studentuSkaicius);
string pasirinktiFaila();
void nuskaitytiFaila(string fail, Vector<Studentas> &studentuSarasas);
void rodytiVisusRezultatus(Vector<Studentas> studentuSarasas);
void testuotiFailuNuskaityma(Vector<Studentas> studentuSarasas, int kartai);

//rikiavimo funkcijos
void rikiuotiPagalVarda(Vector<Studentas> &studentuSarasas);
void rikiuotiPagalPavarde(Vector<Studentas> &studentuSarasas);
void rikiuotiPagalGalutiniMed(Vector<Studentas> &studentuSarasas);
void rikiuotiPagalGalutiniVid(Vector<Studentas> &studentuSarasas);

void pasirinktiRikiavima(Vector<Studentas> studentuSarasas);
void skirstytiStudentus(Vector<Studentas> &studentuSarasas);

bool vardoTikrinimas(const string &vard);
void isvestiDuFailus(Vector<Studentas> grupe1, Vector<Studentas> grupe2);
void rikiavimasIrIrasymasVargsiukamsIrKietekams(Vector<Studentas> vargsiukai, Vector<Studentas> kietekai);
void testuotiDestruktoriu();

#endif