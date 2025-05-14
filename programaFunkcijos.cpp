#include "studentClass.h"
//visų programos funkcijų realizacijos

void Studentas::skaiciuotiGalutiniSuVid(){
    vector<int> pazCopy = pazymiai_; 
    double pazymiuVidurkis;
    if(pazymiai().size() == 0){
        pazymiuVidurkis = 0.0;
    } else {
        double sum = accumulate(pazCopy.begin(), pazCopy.end(), 0);
        pazymiuVidurkis = sum / static_cast<double>(pazCopy.size());
    }
    double galutinis = 0.4 * pazymiuVidurkis + 0.6 * egzaminas_;
    setGalutinisV(galutinis);
}

void Studentas::skaiciuotiGalutiniSuMed(){
    vector<int> pazCopy = pazymiai_; 
    int n = pazCopy.size();
    int med;
 if (n == 0) {
        med = 0;
    } else { 
        sort(pazCopy.begin(), pazCopy.end());
        if (n % 2 != 0) {
            med = pazCopy[n/2];
        } else {
            med = (pazCopy[n/2-1] + pazCopy[n/2]) / 2.0;
        }
    }

    double galutinis = 0.4 * med + 0.6 * egzaminas_;
    setGalutinisM(galutinis);
}

void rodytiRezultatus(vector<Studentas> studentuSarasas){
    int choice;
    cout << "Jei norėtumete galutinį balą skaičiuoti su vidurkiu, įrašykite 0, jei su mediana - įrašykite 1" << endl;
    cin >> choice;

    cout << "Štai rezultatai: " << endl;
    cout << endl;

    cout << std::left << std::setw(20) << "Pavardė" << std::setw(20) << "Vardas";

    if (choice == 0){
        cout << std::setw(20) << "Galutinis (Vid.)" << endl;
        cout << "---------------------------------------------------------" << endl;
        for (Studentas s : studentuSarasas){
            cout << std::left << std::setw(20) << s.pavarde() << std::setw(20) << s.vardas() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisVid() << endl;
        }
    } else if (choice == 1){
        cout << std::setw(20) << "Galutinis (Med.)" << endl;
        cout << "---------------------------------------------------------" << endl;
        for (Studentas s : studentuSarasas){
            cout << std::left << std::setw(20) << s.pavarde() << std::setw(20) << s.vardas() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisMed() << endl;
        }
        } else {
            cout << "Neteisingai įvestas pasirinkimas";
        }
}

void rodytiVisusRezultatus(vector<Studentas> studentuSarasas){
    std::ostringstream buferis;
    buferis << std::left << std::setw(20) << "Pavardė" << std::setw(20) << "Vardas" << std::setw(20) << std::fixed << std::setprecision(2) << "Galutinis (Vid.)" << std::setw(20) << std::fixed << std::setprecision(2) << "Galutinis (Med.)" << endl;
    for (Studentas s: studentuSarasas){
        buferis << s;
    }

    int choice;
    cout << "Ar norėtumėte rezultatus matyti:" << endl;
    cout << "1 | Komandinėje eilutėje" << endl;
    cout << "2 | Faile" << endl;
    cin >> choice;

    if (choice == 1){
        cout << buferis.str();
    } else if (choice == 2){
        Timer t;
        std::ofstream failas("studentuRezultatai.txt");
        failas << buferis.str();
        failas.close();
        cout << "Failą išvesti užtruko: " << t.elapsed() << " s\n";
    }

}

void generuotiPazymius(vector<Studentas> &studentuSarasas){
    srand(time(NULL));
    for (Studentas &s : studentuSarasas){
        int pazymiuKiekis = 3 + (rand() % 18);
        vector<int> pazymiai;
        for (int x = 0; x < pazymiuKiekis; x++){
            int pazymys = 1 + (rand() % 10);
            pazymiai.push_back(pazymys);
        }
        int egzPazymys = 1 + (rand() % 10);
        s.setPazymiai(pazymiai);
        s.setEgzaminas(egzPazymys);
        s.skaiciuotiGalutiniSuMed(); 
        s.skaiciuotiGalutiniSuVid();  
    }
}

void generuotiStudentus(vector<Studentas> &studentuSarasas){
    srand(time(NULL));

    vector<string> vardai;
    vector<string> pavardes;
    string name;

    ifstream varduFailas("firstNames.txt");
    while(getline(varduFailas, name)){
        vardai.push_back(name);
    }
    varduFailas.close();

    ifstream pavardziuFailas("lastNames.txt");
    while(getline(pavardziuFailas, name)){
        pavardes.push_back(name);
    }
    pavardziuFailas.close();

    int studentuSkaicius = 4 + (rand()%7);

    for (int i = 0; i < studentuSkaicius; i++){
        string vardas, pavarde;
        vardas = vardai [rand() % vardai.size()];
        pavarde = pavardes [rand() % pavardes.size()];
        Studentas stud(vardas, pavarde);
        studentuSarasas.push_back(stud);
    }

}

void generuotiFailus(int studentuSkaicius){
    int pazymiuKiekis = 3 + (rand() % 18);

    //Failo sukurimas
    string name = "genStudentai" + std::to_string(studentuSkaicius) + ".txt";
    std::ofstream failas(name);

    //Irasymas i faila
    std::ostringstream buferis;
    buferis << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
    for (int x = 1; x <=pazymiuKiekis; x++){
        buferis << std::left << std::setw(20) << "ND" + std::to_string(x);
    }
    buferis << std::left << std::setw(20) << "Egz" << endl;

    //Studentu generavimas
    for(int i = 1; i <= studentuSkaicius; i++){
        string vardas = "Vardas" + std::to_string(i);
        string pavarde = "Pavarde" + std::to_string(i);
        vector<int> pazymiai;
        for (int x = 0; x < pazymiuKiekis; x++){
            int pazymys = 1 + (rand() % 10);
            pazymiai.push_back(pazymys);
        }
        int egzPazymys = 1 + (rand() % 10);
        Studentas stud(vardas, pavarde, pazymiai, egzPazymys);
        pazymiai.clear();
        buferis << std::left << std::setw(20) << stud.vardas() << std::setw(20) << stud.pavarde();
        for(int i : stud.pazymiai()){
            buferis << std::left << std::setw(20) << i;
        }
        buferis << std::left << std::setw(20) << stud.egzaminas() << endl;
    }
    failas << buferis.str();
    failas.close();
}

string pasirinktiFaila(){
    string eilut;
    int pazymys;
    std::stringstream buferis;

    while(true){
        try{
            system("ls *.txt gen_failu_archyvas/*.txt > temp.txt");
            ifstream tempFail("temp.txt");
            vector<string> failuPav;
            std::unordered_set<string> nenorimiFailai = {"studentuRezultatai.txt", "firstNames.txt", "lastNames.txt", "nepazangus.txt", "pazangus.txt"};
            string failoPav;
            while(getline(tempFail, failoPav)){
                if (nenorimiFailai.find(failoPav) == nenorimiFailai.end()) {
                    failuPav.push_back(failoPav);
                }
            }
            tempFail.close();
            system("rm temp.txt");
            string fail;

            cout << "Pasirinkite norimą failą" << endl;
            for(int i = 1; i <= failuPav.size(); i++){
                cout << i << "| " << failuPav[i-1] << endl;
            }
            int choice;
            cin >> choice;
            if (choice < 1 || choice > failuPav.size()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Neteisingas failo pasirinkimas");
            } else {
                 fail = failuPav[choice-1];
            }
            return fail;
            break;
        } catch (const std::runtime_error &e) {
            cout << e.what() << endl;
            continue;
        } catch (const char* e){
            cout << e << endl;
            throw;
        }
    }
}

void nuskaitytiFaila(string fail, vector<Studentas> &studentuSarasas){
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
                Studentas s;
                eilute >> s;
                studentuSarasas.push_back(s);
            }
}
//rikiavimo funkcijos
void rikiuotiPagalVarda(vector<Studentas> &studentuSarasas){
    sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
        return a.vardas() < b.vardas();
    });
}

void rikiuotiPagalPavarde(vector<Studentas> &studentuSarasas){
    sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
        return a.pavarde() < b.pavarde();
    });
}

void rikiuotiPagalGalutiniMed(vector<Studentas> &studentuSarasas){
    sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
        return a.galutinisMed() < b.galutinisMed();
    });
}

void rikiuotiPagalGalutiniVid(vector<Studentas> &studentuSarasas){
    sort(studentuSarasas.begin(), studentuSarasas.end(), [](const Studentas& a, const Studentas& b) {
        return a.galutinisVid() < b.galutinisVid();
    });
}

//failų nuskaitymo testavimas
void testuotiFailuNuskaityma(vector<Studentas> studentuSarasas, int kartai){
    string eilut;
    int pazymys;
    double duration;

    while(true){
        try{
            system("ls *.txt > temp.txt");
            ifstream tempFail("temp.txt");
            vector<string> failuPav;
            std::unordered_set<string> nenorimiFailai = {"studentuRezultatai.txt", "firstNames.txt", "lastNames.txt"};
            string failoPav;
            while(getline(tempFail, failoPav)){
                if (nenorimiFailai.find(failoPav) == nenorimiFailai.end()) {
                    failuPav.push_back(failoPav);
                }
            }
            tempFail.close();
            system("rm temp.txt");
            string fail;

            cout << "Pasirinkite norimą failą" << endl;
            for(int i = 1; i <= failuPav.size(); i++){
                cout << i << "| " << failuPav[i-1] << endl;
            }
            int choice;
            cin >> choice;
            if (choice < 1 || choice > failuPav.size()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Neteisingas failo pasirinkimas");
            } else {
                 fail = failuPav[choice-1];
            }

            ifstream failas(fail);
            if (!failas.is_open()){
                throw std::runtime_error("Failo nepavyko atidaryti arba jis neegzistuoja šiame aplankale");
            }

            Timer t;

            for (int x = 0; x < kartai; x++){
                ifstream failas(fail);
                std::stringstream buferis;
                studentuSarasas.clear();
                t.reset();
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
                if (pazymiai.empty()) {
                    egzaminas = pazymiai.back();
                    pazymiai.pop_back();
                } else {
                    throw "Netinkamas failo formatas: faile nėra pažymių";
                }
                Studentas stud(vardas, pavarde, pazymiai, egzaminas);
                studentuSarasas.push_back(stud);
                pazymiai.clear();
            }
                duration += t.elapsed();
            }

            double durationAvg = duration / (double)kartai;
            std::cout << "Procesas vidutiniškai užtruko: "<< durationAvg << " s\n";
            break;

        } catch (std::runtime_error &e){
            cout << e.what() << endl;
            continue;
        }
    }

}

//vardo tikrinimo funkcija
bool vardoTikrinimas(const string &vard){
    for(char c: vard){
        if (!isalpha(c)){
            return false;
        }
    }
    return true;
}

//studentų skirstymas
void skirstytiStudentus(vector<Studentas> &studentuSarasas){
    Timer t;
    vector<Studentas> nepazangus;
    vector<Studentas> pazangus;
    for(Studentas s : studentuSarasas){
        if (s.galutinisVid() < 5){
            nepazangus.push_back(s);
        } else if (s.galutinisVid() >= 5){
            pazangus.push_back(s);
        }
    }
    pazangus.shrink_to_fit();
    nepazangus.shrink_to_fit();
    
    cout << std::left << std::setw(60) << "Studentų skirstymas į dvi grupes užtruko: " << std::right << std::setw(10) << std::to_string(t.elapsed()) + "s" << endl;
    studentuSarasas.clear();
    isvestiDuFailus(nepazangus, pazangus);
}

//failų išvedimas
void isvestiDuFailus(vector<Studentas> grupe1, vector<Studentas> grupe2){
    Timer v;
    std::ostringstream buferis;
    buferis << std::left << std::setw(20) << "Pavardė" << std::setw(20) << "Vardas" << std::setw(20) << std::fixed << std::setprecision(2) << "Galutinis (Vid.)" << std::setw(20) << std::fixed << std::setprecision(2) << "Galutinis (Med.)" << endl;
    for (Studentas s: grupe1){
        buferis << std::left << std::setw(20) << s.pavarde() << std::setw(20) << s.vardas() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisMed() << endl;
    }
    std::ofstream failas1("nepazangus.txt");
    failas1 << buferis.str();
    failas1.close();
    cout << std::left << std::setw(60) << "Nepažangių mokinių failą išvesti užtruko: " << std::right << std::setw(10) << std::to_string(v.elapsed()) + "s" << endl;

    Timer k;
    std::ostringstream buferis2;
    buferis2 << std::left << std::setw(20) << "Pavardė" << std::setw(20) << "Vardas" << std::setw(20) << std::fixed << std::setprecision(2) << "Galutinis (Vid.)" << std::setw(20) << std::fixed << std::setprecision(2) << "Galutinis (Med.)" << endl;
    for (Studentas s: grupe2){
        buferis2 << std::left << std::setw(20) << s.pavarde() << std::setw(20) << s.vardas() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisMed() << endl;
    }

        std::ofstream failas2("pazangus.txt");
        failas2 << buferis2.str();
        failas2.close();

    cout << std::left << std::setw(60) << "Pažangių mokinių failą išvesti užtruko: " << std::right << std::setw(10) << std::to_string(k.elapsed()) + "s" << endl;

}

//input operatorius
std::istream& operator>>(std::istream& cin, Studentas& s){
            string vardas, pavarde;
            vector<int> pazymiai;
            int egzaminas, pazymys;

            cin >> vardas >> pavarde;

            if (cin.eof()) {
                throw std::runtime_error("Netinkamas failo formatas: faile nėra pažymių");
            }
                
            while (cin >> pazymys){
                if (cin.fail()){
                    if (cin.eof()){
                        break;
                    }
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("Netinkamas failo formatas: pažymiai nėra skaitinės reikšmės");
                }
                    if (pazymys < 1 || pazymys > 10){
                        throw std::runtime_error("Netinkamas failo formatas: pažymiai nėra sveiki skaičiai ribose nuo 1 iki 10");
                    }
                    pazymiai.push_back(pazymys);
                }
                if (!pazymiai.empty()) {
                    egzaminas = pazymiai.back();
                    pazymiai.pop_back();
                } else {
                    throw std::runtime_error("Netinkamas failo formatas: faile nėra pažymių");
                }
                s = Studentas(vardas, pavarde, pazymiai, egzaminas);
            return cin;
}

//output operatorius
std::ostream& operator<<(std::ostream& out, const Studentas &s) {
            out << std::left << std::setw(20) << s.pavarde() << std::setw(20) << s.vardas() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisMed() << endl;
            return out;
        }

//destruktoriaus testavimo klasė
void testuotiDestruktoriu(){
    Studentas s;
    s.~Studentas();
    if (s.isClear()){
        cout << "Destruktorius suveike" << endl;
    } else {
        cout << "Elementas egzistuoja" << endl;
    }
}