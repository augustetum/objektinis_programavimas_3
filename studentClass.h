#ifndef MANO_LIB_H
#define MANO_LIB_H

#include <iostream>
#include <iomanip>
#include <vector>
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

using std::cout;
using std::cin;
using std::string;
using std::vector;
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
        vector<int> pazymiai_;
    
    public:
        Studentas(string var, string pav, vector<int> paz, int egz) :  
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
        inline const vector<int>& pazymiai() const { return pazymiai_; }
        inline int egzaminas() const { return egzaminas_; }

        //set'eriai
        inline void setGalutinisV(double galutVid) { galutinisVid_ = galutVid; }
        inline void setGalutinisM(double galutMed) { galutinisMed_ = galutMed; }
        inline void setEgzaminas(int egz) {egzaminas_ = egz; }
        inline void setPazymiai(vector<int> paz) {pazymiai_ = paz;}

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

void rodytiRezultatus(vector<Studentas> studentuSarasas);
void generuotiPazymius(vector<Studentas> &studentuSarasas);
void generuotiStudentus(vector<Studentas> &studentuSarasas);
void generuotiFailus(int studentuSkaicius);
string pasirinktiFaila();
void nuskaitytiFaila(string fail, vector<Studentas> &studentuSarasas);
void rodytiVisusRezultatus(vector<Studentas> studentuSarasas);
void testuotiFailuNuskaityma(vector<Studentas> studentuSarasas, int kartai);

//rikiavimo funkcijos
void rikiuotiPagalVarda(vector<Studentas> &studentuSarasas);
void rikiuotiPagalPavarde(vector<Studentas> &studentuSarasas);
void rikiuotiPagalGalutiniMed(vector<Studentas> &studentuSarasas);
void rikiuotiPagalGalutiniVid(vector<Studentas> &studentuSarasas);

void pasirinktiRikiavima(vector<Studentas> studentuSarasas);
void skirstytiStudentus(vector<Studentas> &studentuSarasas);

bool vardoTikrinimas(const string &vard);
void isvestiDuFailus(vector<Studentas> grupe1, vector<Studentas> grupe2);
void rikiavimasIrIrasymasVargsiukamsIrKietekams(vector<Studentas> vargsiukai, vector<Studentas> kietekai);
void testuotiDestruktoriu();

#endif