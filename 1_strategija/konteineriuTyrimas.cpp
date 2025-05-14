#include "../studentClass.h"
#include "strategijos_bibl.h"

int main(){
    vector<Studentas> studentuSarasasV;
    deque<Studentas> studentuSarasasD;
    list<Studentas> studentuSarasasL;

    string failas;
    failas = pasirinktiFaila();

    Timer v, d, l; //bendram laikui
    Timer nV, nD, nL; //nuskaitymui
    Timer rV, rD, rL; //rikiavimui
    Timer sV, sD, sL; //skirstymui

    double trukmeV = 0.0;
    double trukmeD = 0.0;
    double trukmeL = 0.0;

    double nuskaitymoTrukmeV = 0.0;
    double nuskaitymoTrukmeD = 0.0;
    double nuskaitymoTrukmeL = 0.0;

    double rikiavimoTrukmeV = 0.0;
    double rikiavimoTrukmeD = 0.0;
    double rikiavimoTrukmeL = 0.0;

    double skirstymoTrukmeV = 0.0;
    double skirstymoTrukmeD = 0.0;
    double skirstymoTrukmeL = 0.0;

    cout << "Tyrimas | Konteinerių skirtumai | Failas: " << failas << endl;
    cout << endl;

    //Tyrimo tikslumui praleidžiama pirma iteracija
    nuskaitytiFailaT(failas, studentuSarasasV);
    rikiuotiPagalGalutiniVidT(studentuSarasasV);
    skirstytiStudentusT(studentuSarasasV);

    nuskaitytiFailaT(failas, studentuSarasasD);
    rikiuotiPagalGalutiniVidT(studentuSarasasD);
    skirstytiStudentusT(studentuSarasasD);

    nuskaitytiFailaT(failas, studentuSarasasL);
    rikiuotiPagalGalutiniVidT(studentuSarasasL);
    skirstytiStudentusT(studentuSarasasL);
 

    for (int i = 0; i < 3; i++){
        //------------------------VEKTORIAI-------------------------
        v.reset();

        nV.reset();
        nuskaitytiFailaT(failas, studentuSarasasV);
        nuskaitymoTrukmeV += nV.elapsed();

        rV.reset();
        rikiuotiPagalGalutiniVidT(studentuSarasasV);
        rikiavimoTrukmeV += rV.elapsed();

        sV.reset();
        skirstytiStudentusT(studentuSarasasV);
        skirstymoTrukmeV += sV.elapsed();

        trukmeV += v.elapsed();

        //--------------------------DEQUE---------------------------
        d.reset();
        nD.reset();
        nuskaitytiFailaT(failas, studentuSarasasD);
        nuskaitymoTrukmeD += nD.elapsed();

        rD.reset();
        rikiuotiPagalGalutiniVidT(studentuSarasasD);
        rikiavimoTrukmeD += rD.elapsed();

        sD.reset();
        skirstytiStudentusT(studentuSarasasD);
        skirstymoTrukmeD += sD.elapsed();

        trukmeD += d.elapsed();

        //--------------------------LIST---------------------------
        l.reset();
        nL.reset();
        nuskaitytiFailaT(failas, studentuSarasasL);
        nuskaitymoTrukmeL += nL.elapsed();

        rL.reset();
        rikiuotiPagalGalutiniVidT(studentuSarasasL);
        rikiavimoTrukmeL += rL.elapsed();

        sL.reset();
        skirstytiStudentusT(studentuSarasasL);
        skirstymoTrukmeL += sL.elapsed();

        trukmeL += l.elapsed();
    }


    cout << "----------- Vektoriai (vectors) -----------" << endl;
    cout << "Failo nuskaitymas: " << nuskaitymoTrukmeV / 3.0 << "s\n";
    cout << "Rikiavimas: " << rikiavimoTrukmeV / 3.0 << "s\n";
    cout << "Skirstymas: " << skirstymoTrukmeV / 3.0 << "s\n";
    cout << "Iš viso: " << trukmeV / 3.0 << "s\n";
    cout << endl;

    cout << "----------- Dvipusė eilė (deque) -----------" << endl;
    cout << "Failo nuskaitymas: " << nuskaitymoTrukmeD / 3.0 << "s\n";
    cout << "Rikiavimas: " << rikiavimoTrukmeD / 3.0 << "s\n";
    cout << "Skirstymas: " << skirstymoTrukmeD / 3.0 << "s\n";
    cout << "Iš viso: " << trukmeD / 3.0 << "s\n";
    cout << endl;

    cout << "----------- Sąrašai (list) -----------" << endl;
    cout << "Failo nuskaitymas: " << nuskaitymoTrukmeL / 3.0 << "s\n";
    cout << "Rikiavimas: " << rikiavimoTrukmeL / 3.0 << "s\n";
    cout << "Skirstymas: " << skirstymoTrukmeL / 3.0 << "s\n";
    cout << "Iš viso: " << trukmeL / 3.0 << "s\n";
     


}