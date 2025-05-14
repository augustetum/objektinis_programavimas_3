#ifndef STRATEGIJOS1_BIBL_H
#define STRATEGIJOS1_BIBL_H

#include <list>
#include "../studentClass.h"
#include <thread>
#include <functional>

using std::deque;
using std::list;

template <typename Container> 
void nuskaitytiFailaT(string fail, Container &studentuSarasas){
    string eilut;
    int pazymys;
    std::stringstream buferis;
    ifstream failas(fail);
            if (!failas.is_open()){
                throw std::runtime_error("Failo nepavyko atidaryti arba jis neegzistuoja šiame aplankale");
            }

            buferis << failas.rdbuf();
            failas.close();

            getline(buferis, eilut);

            while(getline(buferis, eilut)){
                istringstream eilute(eilut);
                string vardas, pavarde;
                vector<int> pazymiai;
                int egzaminas;

                eilute >> vardas >> pavarde;

                if (eilute.eof()) {
                    throw "Netinkamas failo formatas: faile nėra pažymių";
                }
                
                while(true){
                    eilute >> pazymys;
                    if (eilute.fail()){
                        if (eilute.eof()){
                            break;
                        }
                        eilute.clear();
                        eilute.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw "Netinkamas failo formatas: pažymiai nėra skaitinės reikšmės";
                    }
                    if (pazymys < 1 || pazymys > 10){
                        throw "Netinkamas failo formatas: pažymiai nėra sveiki skaičiai ribose nuo 1 iki 10";
                    }
                    pazymiai.push_back(pazymys);
                }
                if (!pazymiai.empty()) {
                    egzaminas = pazymiai.back();
                    pazymiai.pop_back();
                } else {
                    throw "Netinkamas failo formatas: faile nėra pažymių";
                }
                Studentas stud(vardas, pavarde, pazymiai, egzaminas);
                studentuSarasas.push_back(stud);
                pazymiai.clear();
            }
}

template <typename Container>
void rikiuotiPagalVardaT(Container &studentuSarasas){
    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        studentuSarasas.sort([](const Studentas &a, const Studentas &b) {
            return a.vardas() < b.vardas();
        });
    } else {
        sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas() < b.vardas();
        });

    }
}

template <typename Container>
void rikiuotiPagalPavardeT(Container &studentuSarasas){
    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        studentuSarasas.sort([](const Studentas &a, const Studentas &b) {
            return a.pavarde() < b.pavarde();
        });
    } else {
        sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
            return a.pavarde() < b.pavarde();
        });

    }
}

template <typename Container>
void rikiuotiPagalGalutiniMedT(Container &studentuSarasas){
    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        studentuSarasas.sort([](const Studentas &a, const Studentas &b) {
            return a.galutinisMed() < b.galutinisMed();
        });
    } else {
        sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisMed() < b.galutinisMed();
        });

    }
}

template <typename Container>
void rikiuotiPagalGalutiniVidT(Container &studentuSarasas){
    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        studentuSarasas.sort([](const Studentas &a, const Studentas &b) {
            return a.galutinisVid() > b.galutinisVid();
        });
    } else {
        sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisVid() > b.galutinisVid();
        });

    }
}

template <typename Container>
void skirstytiStudentusSuTaisPaciaisKonteineriaisT(Container &studentuSarasas){
    Container nepazangus;
    Container pazangus;
    for(Studentas s : studentuSarasas){
        if (s.galutinisVid() < 5){
            nepazangus.push_back(s);
        } else if (s.galutinisVid() >= 5){
            pazangus.push_back(s);
        }
    }

    if constexpr(std::is_same_v<Container, vector<Studentas>> || std::is_same_v<Container, deque<Studentas>>){
        nepazangus.shrink_to_fit();
        pazangus.shrink_to_fit();
    }
}

template <typename Container>
void skirstytiStudentusSuVienuKonteineriuT(Container &studentuSarasas, int rikiavimas){
    Container nepazangus;
    rikiuotiPagalGalutiniVidT(studentuSarasas);
    while (studentuSarasas.back().galutinisVid() < 5) {
        nepazangus.push_back(studentuSarasas.back());
        studentuSarasas.pop_back();
    }

    if constexpr(std::is_same_v<Container, vector<Studentas>> || std::is_same_v<Container, deque<Studentas>>){
        studentuSarasas.shrink_to_fit();
        nepazangus.shrink_to_fit();
    }


    if (rikiavimas == 1) {
            rikiuotiPagalVardaT(studentuSarasas);
            rikiuotiPagalVardaT(nepazangus);
    } else if (rikiavimas == 2) {
            rikiuotiPagalPavardeT(studentuSarasas);
            rikiuotiPagalPavardeT(nepazangus);
    } else if (rikiavimas == 3) {
            rikiuotiPagalGalutiniVidT(studentuSarasas);
            rikiuotiPagalGalutiniVidT(nepazangus);
    } else if (rikiavimas == 4) {
            rikiuotiPagalGalutiniMedT(studentuSarasas);
            rikiuotiPagalGalutiniMedT(nepazangus);
    } 

}

template <typename Container>
void skirstytiStudentusT(Container &studentuSarasas){
    Container nepazangus;
    Container pazangus;
    for(Studentas s : studentuSarasas){
        if (s.galutinisVid() < 5){
            nepazangus.push_back(s);
        } else if (s.galutinisVid() >= 5){
            pazangus.push_back(s);
        }
    }

    if constexpr(std::is_same_v<Container, vector<Studentas>> || std::is_same_v<Container, deque<Studentas>>){
        nepazangus.shrink_to_fit();
        pazangus.shrink_to_fit();
    }
    studentuSarasas.clear();
}

template <typename Container>
void studentuSkirstymas3(Container &studentuSarasas, int rikiavimas){
    auto it = std::partition(studentuSarasas.begin(), studentuSarasas.end(), [](const auto &studentas) { return studentas.galutinisVid() >= 5; });
    Container nepazangus;
    nepazangus.assign(it, studentuSarasas.end());
    studentuSarasas.resize(std::distance(studentuSarasas.begin(), it));

    std::thread t1, t2;

    if (rikiavimas == 1) {
        std::thread t1([&studentuSarasas]() { rikiuotiPagalVardaT(studentuSarasas); });
        std::thread t2([&nepazangus]() { rikiuotiPagalVardaT(nepazangus); });
        t1.join();
        t2.join();
    } else if (rikiavimas == 2) {
        std::thread t1([&studentuSarasas]() { rikiuotiPagalPavardeT(studentuSarasas); });
        std::thread t2([&nepazangus]() { rikiuotiPagalPavardeT(nepazangus); });
        t1.join();
        t2.join();
    } else if (rikiavimas == 3) {
        std::thread t1([&studentuSarasas]() { rikiuotiPagalGalutiniVidT(studentuSarasas); });
        std::thread t2([&nepazangus]() { rikiuotiPagalGalutiniVidT(nepazangus); });
        t1.join();
        t2.join();
    } else if (rikiavimas == 4) {
        std::thread t1([&studentuSarasas]() { rikiuotiPagalGalutiniMedT(studentuSarasas); });
        std::thread t2([&nepazangus]() { rikiuotiPagalGalutiniMedT(nepazangus); });
        t1.join();
        t2.join();
    } 
    
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
}
#endif

