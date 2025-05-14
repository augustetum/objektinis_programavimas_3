#include "../studentClass.h"
#include "strategijos_bibl.h"


int main(){
    cout << "Konteinerių testavimo programa | 1 strategija" << endl;
    cout << "---------------------------------------------" << endl;
    vector<Studentas> studentaiV;
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

    double vektoriuTrukme;
    double dequeTrukme;
    double listTrukme;
    Timer v;
    Timer d;
    Timer l;

    for (int x = 0; x < kartai; x++){
        //vektoriaus testavimas
        v.reset();
        nuskaitytiFailaT(failas, studentaiV);
        if (rikiavimas == 1) {
            rikiuotiPagalVardaT(studentaiV);
        } else if (rikiavimas == 2) {
            rikiuotiPagalPavardeT(studentaiV);
        } else if (rikiavimas == 3) {
            rikiuotiPagalGalutiniVidT(studentaiV);
        } else if (rikiavimas == 4) {
            rikiuotiPagalGalutiniMedT(studentaiV);
        } 
        skirstytiStudentusSuTaisPaciaisKonteineriaisT(studentaiV);
        vektoriuTrukme += v.elapsed();
        studentaiV.clear();

        d.reset();
        nuskaitytiFailaT(failas, studentaiD);
        if (rikiavimas == 1) {
            rikiuotiPagalVardaT(studentaiD);
        } else if (rikiavimas == 2) {
            rikiuotiPagalPavardeT(studentaiD);
        } else if (rikiavimas == 3) {
            rikiuotiPagalGalutiniVidT(studentaiD);
        } else if (rikiavimas == 4) {
            rikiuotiPagalGalutiniMedT(studentaiD);
        } 
        skirstytiStudentusSuTaisPaciaisKonteineriaisT(studentaiD);
        dequeTrukme += d.elapsed();
        studentaiD.clear();

        l.reset();
        nuskaitytiFailaT(failas, studentaiL);
        if (rikiavimas == 1) {
            rikiuotiPagalVardaT(studentaiL);
        } else if (rikiavimas == 2) {
            rikiuotiPagalPavardeT(studentaiL);
        } else if (rikiavimas == 3) {
            rikiuotiPagalGalutiniVidT(studentaiL);
        } else if (rikiavimas == 4) {
            rikiuotiPagalGalutiniMedT(studentaiL);
        } 
        skirstytiStudentusSuTaisPaciaisKonteineriaisT(studentaiL);
        listTrukme += l.elapsed();
        studentaiL.clear();

    }

    cout << endl;
    cout << "----------------------------Rezultatai------------------------------" << endl;
    cout << "Programa su vektoriais (vector) vidutiniškai užtruko: " << vektoriuTrukme / (double)kartai << "s\n";
    cout << "Programa su dėklais (deque) vidutiniškai užtruko: " << dequeTrukme / (double)kartai << "s\n";
    cout << "Programa su sąrašais (list) vidutiniškai užtruko: " << listTrukme / (double)kartai << "s\n";
    cout << "--------------------------------------------------------------------" << endl;
}

