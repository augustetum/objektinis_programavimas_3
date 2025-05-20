#include "../studentClass.h"
#include "strategijos_bibl.h"


void strategija2(){
    cout << "Konteinerių testavimo programa | 2 strategija" << endl;
    cout << "---------------------------------------------" << endl;
    Vector<Studentas> studentaiV;
    deque<Studentas> studentaiD;
    list<Studentas> studentaiL;

    string failas = pasirinktiFaila();

    int rikiavimas;
    cout << "Pasirinkite failo rikiavimo būdą: " << endl;
    cout << "1 | Rikiuoti pagal vardą" << endl;
    cout << "2 | Rikiuoti pagal pavardę" << endl;
    cout << "3 | Rikiuoti pagal galutinį pažymį (su vidurkiu)" << endl;
    cout << "4 | Rikiuoti pagal galutinį pažymį (su mediana)" << endl;
    cin >> rikiavimas;

    int kartai;
    cout << "Kiek kartų norite testuoti programą su skirtingais konteineriais?" << endl;
    cin >> kartai;

    double vektoriuTrukme = 0;
    double dequeTrukme = 0;
    double listTrukme = 0;
    Timer v;
    Timer d;
    Timer l;

    for (int x = 0; x < kartai; x++){

        v.reset();
        nuskaitytiFailaT(failas, studentaiV);
        skirstytiStudentusSuVienuKonteineriuT(studentaiV, rikiavimas);
        vektoriuTrukme += v.elapsed();

        d.reset();
        nuskaitytiFailaT(failas, studentaiD);
        skirstytiStudentusSuVienuKonteineriuT(studentaiD, rikiavimas);
        dequeTrukme += d.elapsed();

        l.reset();
        nuskaitytiFailaT(failas, studentaiL);
        skirstytiStudentusSuVienuKonteineriuT(studentaiL, rikiavimas);
        listTrukme += l.elapsed();
    }
    cout << "----------------------------Rezultatai------------------------------" << endl;
    cout << "Programa su vektoriais (vector) vidutiniškai užtruko: " << vektoriuTrukme / (double)kartai << "s\n";
    cout << "Programa su dėklais (deque) vidutiniškai užtruko: " << dequeTrukme / (double)kartai << "s\n";
    cout << "Programa su sąrašais (list) vidutiniškai užtruko: " << listTrukme / (double)kartai << "s\n";
    cout << "--------------------------------------------------------------------" << endl;
}