#include "studentClass.h"

int main(){
    bool veikimas = true;
    while(veikimas){
        try{
            vector<Studentas> studentuSarasas;
            int menuChoice;
            
            cout << "Pasirinkite programos eigą:" << endl;
            cout << "1 | Įvesti studentus ranka" << endl;
            cout << "2 | Generuoti pažymius" << endl;
            cout << "3 | Generuoti pažymius bei studentų vardus, pavardes" << endl;
            cout << "4 | Nuskaityti duomenis iš failo" << endl;
            cout << "5 | Testuoti failų nuskaitymą" << endl;
            cout << "6 | Generuoti studentų failą" << endl;
            cout << "7 | Atlikti laiko matavimo tyrimą" << endl;
            cout << "8 | Testuoti klasės metodus ir konstruktorius" << endl;
            cout << "9 | Baigti darbą" << endl;
            cin >> menuChoice;

            if(cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Neteisingas meniu pasirinkimas!");
            }

            if (menuChoice < 1 || menuChoice > 9 || menuChoice != static_cast<int>(menuChoice)){
                throw std::runtime_error("Neteisingas meniu pasirinkimas!");
            }

            switch(menuChoice) 
            {
                case 1: {
                    cout << "Pasirinkote studentų įvestį ranka" << endl;
                    cout << "---------------------------------" << endl;
                    cout << "Įveskite studentus šiuo formatu: vardas pavardė pažymiai egzamino pažymys. Baigę rašyti studentus įrašykite stop." << endl;
                    while (true){
                        try {
                          string eilut;
                            std::getline(std::cin >> std::ws, eilut);
                            if (eilut == "stop") {
                                break;
                            }
                            istringstream eilute(eilut);
                            Studentas s;
                            eilute >> s;
                            studentuSarasas.push_back(s);


                        } catch (const std::runtime_error &e){
                            cout << e.what() << endl;
                            continue;
                        }
                    }
                    rodytiRezultatus(studentuSarasas);
                break;
                }

                case 2: {
                    cout << "Pasirinkote generuoti pažymius" << endl;
                    cout << "---------------------------------" << endl;

                    while (true){
                        try {
                            Studentas stud;
                            string vardas, pavarde;
                            cout << "Įveskite studento vardą (įvedę visus norimus studentus ir norėdami užbaigti rašykite stop)" << endl;
                            cin >> vardas;
                            if (vardas == "stop"){
                                break;
                            }
                            if (!vardoTikrinimas(vardas)) {
                                    throw std::runtime_error("Neteisingas vardas! Vardas turi būti sudarytas tik iš raidžių.");
                            }
                            stud.setVardas(vardas);
                            cout << "Įveskite studento pavardę" << endl;
                            cin >> pavarde;
                            if (!vardoTikrinimas(pavarde)) {
                                    throw std::runtime_error("Neteisinga pavardė! Pavardė turi būti sudaryta tik iš raidžių.");
                            }
                            stud.setPavarde(pavarde);
                            studentuSarasas.push_back(stud);
                        } catch (const std::runtime_error &e){
                        cout << e.what() << endl;
                        }
                    }

                    generuotiPazymius(studentuSarasas);
                    rodytiRezultatus(studentuSarasas);

                break;
                }

                case 3: {
                    cout << "Pasirinkote generuoti pažymius, studentų pavardes ir vardus" << endl;
                    cout << "---------------------------------" << endl;
                    generuotiStudentus(studentuSarasas);
                    generuotiPazymius(studentuSarasas);
                    rodytiRezultatus(studentuSarasas);
                break;
                }

                case 4: {
                    cout << "Pasirinkote nuskaityti duomenis iš failo" << endl;
                    cout << "----------------------------------------" << endl;
                    try {
                        string fail = pasirinktiFaila();
                        nuskaitytiFaila(fail, studentuSarasas);
                    } catch (const char* e){
                        cout << "Nuskaitymas nepavyko. " << e << endl;
                        break;
                    } catch (const std::runtime_error e){
                        cout << e.what();
                    }

                    while (true){
                        try {
                            int rikiavimas;
                            cout << "Pasirinkite rikiavimo būdą: " << endl;
                            cout << "1 | Rikiuoti pagal vardą" << endl;
                            cout << "2 | Rikiuoti pagal pavardę" << endl;
                            cout << "3 | Rikiuoti pagal galutinį pažymį (su vidurkiu)" << endl;
                            cout << "4 | Rikiuoti pagal galutinį pažymį (su mediana)" << endl;
                            cout << "5 | Nerikiuoti" << endl;
                            cin >> rikiavimas;

                            if (rikiavimas == 1) {
                                rikiuotiPagalVarda(studentuSarasas);
                                rodytiVisusRezultatus(studentuSarasas);
                            } else if (rikiavimas == 2) {
                                rikiuotiPagalPavarde(studentuSarasas);
                                rodytiVisusRezultatus(studentuSarasas);
                            } else if (rikiavimas == 3) {
                                rikiuotiPagalGalutiniVid(studentuSarasas);
                                rodytiVisusRezultatus(studentuSarasas);
                            } else if (rikiavimas == 4) {
                                rikiuotiPagalGalutiniMed(studentuSarasas);
                                rodytiVisusRezultatus(studentuSarasas);
                            } else if (rikiavimas == 5) {
                                rodytiVisusRezultatus(studentuSarasas);
                                rodytiVisusRezultatus(studentuSarasas);
                            } else {
                                throw std::runtime_error("Neteisingas meniu pasirinkimas!");
                            }
                        } catch (std::runtime_error &e) {
                            cout << e.what() << endl;
                            continue;
                        }
                        break;
                    }
                break;
                }

                case 5: {
                    while(true){
                        try {
                        cout << "Pasirinkote testuoti programą" <<endl;
                        int kartai;
                        cout << "Kiek kartų norite nuskaityti failą?" << endl;
                        cin >> kartai;
                        if (cin.fail() || kartai < 1){
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            throw std::runtime_error("Neteisingas testų skaičiaus pasirinkimas");
                        }
                        testuotiFailuNuskaityma(studentuSarasas, kartai);
                    } catch (std::runtime_error &e){
                        cout << e.what() << endl;
                        continue;
                    }
                    break;
                }
                break;
                }
                    
                case 6: {
                    cout << "Pasirinkote generuoti failus" << endl;
                    int studentuKiekis;
                    cout << "Įveskite norimą studentų kiekį: " << endl;
                    cin >> studentuKiekis;
                    Timer t;
                    generuotiFailus(studentuKiekis);
                    cout << "Failą sukurti užtruko: " << t.elapsed() << " s\n";
                break;
                }

                case 7: {
                    cout << "Pasirinkote atlikti laiko matavimo tyrimą" << endl;
                    cout << "-----------------------------------------" << endl;
                    int kartai;
                    cout << "Kelis kartus norite tirti failą?" << endl;
                    cin >> kartai;

                    
                    string fail = pasirinktiFaila();
                    int rikiavimas;
                    cout << "Pasirinkite failo rikiavimo būdą: " << endl;
                    cout << "1 | Rikiuoti pagal vardą" << endl;
                    cout << "2 | Rikiuoti pagal pavardę" << endl;
                    cout << "3 | Rikiuoti pagal galutinį pažymį (su vidurkiu)" << endl;
                    cout << "4 | Rikiuoti pagal galutinį pažymį (su mediana)" << endl;
                    cout << "5 | Nerikiuoti" << endl;
                    while (true){
                        try{
                            cin >> rikiavimas;
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore();
                                throw std::runtime_error("Neteisingas meniu pasirinkimas");
                            } else if (rikiavimas != 1 && rikiavimas != 2 && rikiavimas != 3 && rikiavimas != 4 && rikiavimas != 5){
                                throw std::runtime_error("Neteisingas meniu pasirinkimas");
                            }
                            break;
                        } catch (const std::runtime_error &e){
                            cout << e.what() << endl;
                            continue;
                        }
                    }
                    Timer p;
                    Timer p2;
                    for (int i = 0; i < kartai; i++){
                        p2.reset();
                    cout << endl;
                    cout << "----------------------------------------------------" << endl;
                    Timer f;
                    nuskaitytiFaila(fail, studentuSarasas);
                    cout << std::left << std::setw(60) << "Failą " + fail + " nuskaityti užtruko: " << std::right << std::setw(10) << std::to_string(f.elapsed()) + "s" << endl;
                    Timer r;
                    if (rikiavimas == 1) {
                        rikiuotiPagalVarda(studentuSarasas);
                        cout << std::left << std::setw(60) << "Rikiavimas užtruko: " << std::right << std::setw(10) << std::to_string(r.elapsed()) + "s" << endl;
                    } else if (rikiavimas == 2) {
                        rikiuotiPagalPavarde(studentuSarasas);
                        cout << std::left << std::setw(60) << "Rikiavimas užtruko: " << std::right << std::setw(10) << std::to_string(r.elapsed()) + "s" << endl;
                    } else if (rikiavimas == 3) {
                        rikiuotiPagalGalutiniVid(studentuSarasas);
                        cout << std::left << std::setw(60) << "Rikiavimas užtruko: " << std::right << std::setw(10) << std::to_string(r.elapsed()) + "s" << endl;
                    } else if (rikiavimas == 4) {
                        rikiuotiPagalGalutiniMed(studentuSarasas);
                        cout << std::left << std::setw(60) << "Rikiavimas užtruko: " << std::right << std::setw(10) << std::to_string(r.elapsed()) + "s" << endl;
                    } else if (rikiavimas == 5) {
                        cout << std::left << std::setw(60) << "Rikiavimas užtruko: 0s" << endl;
                    }
                    skirstytiStudentus(studentuSarasas); //viduje metodo laiko matavimas

                    cout << endl;
                    cout << std::left << std::setw(60) << "Iš viso programa užtruko: " << std::right << std::setw(10) << std::to_string(p2.elapsed()) + "s" << endl;
                    cout << "----------------------------------------------------" << endl;
                    cout << endl;
                }
                double vidutinisLaikas = p.elapsed() / (double)kartai;
                cout << endl;
                cout << std::left << std::setw(60) << "Iš viso vidutiniškai programa užtruko: " << std::right << std::setw(10) << std::to_string(vidutinisLaikas) + "s" << endl;
                cout << endl;
                break;
                }

                case 8: {
                    cout << "Pasirinkote testuoti klasę: " << endl;
                    cout << "—— Default konstruktorius ——" << endl;
                    Studentas s1;
                    cout << "Egzaminas: " << s1.egzaminas() << endl;
                    cout << endl;
                    cout << "—— Vardo, pavardės konstruktorius ——" << endl;
                    Studentas s2("Jonas", "Jonaitis");
                    cout << "Vardas: " << s2.vardas() << ", pavardė: " << s2.pavarde() << endl;
                    cout << endl;
                    cout << "—— Pilnas konstruktorius ——" << endl;
                    vector<int> pazymiai = {8, 9, 10, 7, 8};
                    Studentas s3("Petras", "Petraitis", pazymiai, 9);
                    cout << "Vardas: " << s3.vardas() 
                    << ", pavardė: " << s3.pavarde() 
                    << ", egzaminas: " << s3.egzaminas()
                    << ", galutinis vid: " << s3.galutinisVid()
                    << ", galutinis med: " << s3.galutinisMed() << endl;
                    cout << endl;
                    cout << "—— Copy konstruktorius ——" << endl;
                    Studentas s4(s3);
                    cout << "s3 kopija - vardas: " << s4.vardas() 
                    << ", pavardė: " << s4.pavarde() 
                    << ", egzaminas: " << s4.egzaminas() 
                    << ", galutinis vid: " << s4.galutinisVid() << endl;
                    cout << endl;
                    s4.setVardas("Antanas");
                    cout << "Po kopijos pakeitimo - s3.vardas: " << s3.vardas() 
                    << ", s4.vardas: " << s4.vardas() << endl;
                    cout << endl;
                    cout << "—— Move konstruktorius ——" << endl;
                    Studentas s5(std::move(s4));
                    cout << "Movint’as iš s4 - vardas: " << s5.vardas() 
                    << ", pavardė: " << s5.pavarde() 
                    << ", egzaminas: " << s5.egzaminas() << endl;
                    cout << endl;
                    cout << "—— Copy assignment operatorius ——" << endl;
                    Studentas s6;
                    s6 = s3;
                    cout << "s6 po s3 kopijavimo - vardas: " << s6.vardas() 
                    << ", pavardė: " << s6.pavarde() << endl;
                    cout << endl;

                    cout << "—— Move assignment operatorius ——"  << endl;
                    Studentas s7;
                    s7 = std::move(s6);
                    cout << "s7 po movinimo iš s6 - vardas: " << s7.vardas() 
                    << ", pavardė: " << s7.pavarde() << endl;
                    cout << endl;
                    cout << "—— Output’o operatorius ——" << endl;
                    cout << "s3 naudojant operatorių <<: " << s3 << endl;
                    cout << endl;
                    cout << "—— Input’o operatorius ——" << endl;
                    string testInput = "Tomas Tomauskas 5 8 9 10 7 9";
                    istringstream iss(testInput);
                    Studentas s8;
                    iss >> s8;
                    cout << "s8 po input: " << s8 << endl;
                    cout << endl;
                    cout << "—— Destruktorius ——" << endl;
                    testuotiDestruktoriu();
                    //cout << "—— Žmogaus konstuktorius ——" << endl;
                    //Zmogus z("Pranas", "Pranaitis");
                    //cout << z.vardas() << " " << z.pavarde() << endl;
                    break;
                }

                case 9: {
                    cout << "Programa baigta" << endl;
                    veikimas = false;
                break;
                }
            }
        } catch (const std::runtime_error &e) {
            cout << e.what() << endl;
            continue;
        }
    }
}