<h2>Programos aprašymas</h2>
<p>Programa yra skirta apdoroti studentus ir jų akademinių pasiekimų duomenis, tęsinyje iš objektinis_programavimas_2 realizuotas paveldimumas bei Rule of Five, sugeneruota projekto dokumentacija, realizuoti testai naudojantis Catch2. </p>
<h4><b> Pradinės programos funkcijos: </b> </h4>

<ol>
    <li>Įvesti visus studentų duomenis ranka</li>
    <li>Įvesti studentų vardus, pavardes, atsitiktine tvarka generuoti pažymius</li>
    <li>Atsitiktinai generuoti studentų vardus, pavardes ir pažymius</li>
    <li>Nuskaityti duomenis iš failo</li>
    <li>Atsitiktinai generuoti failą su studentų duomenimis</li>
</ol>

<p>Programoje taip pat pateiktos <b>trys strategijos</b>, skirtos testuoti skirtingų programos veikimo laiko priklausomybę nuo naudojamų konteinerių (<i>vector, list, deque</i>) skirstant studentus į pažangius ir nepažangius.  </p>

<h4><b> Strategijų aprašymai: </b> </h4>
<ol>
    <li> Bendro studentų konteinerio (<i>vector, list ir deque tipų</i>) skaidymas (rūšiavimas) į du naujus <b>to paties tipo</b> konteinerius: pažangius ir nepažangius.</li>
    <li> Bendro studentų konteinerio (<i>vector, list ir deque</i>) skaidymas (rūšiavimas) panaudojant tik nepažangių mokinių konteinerį. Tokiu būdu, jei studentas yra nepažangus, jis įkeliamas į nepažangiųjų konteinerį ir ištrinamas iš bendro studentų konteinerio. Atminties atveju ši strategija - efektyvesnė, tačiau dažni trynimai gali būti neefektyvūs tam tikro tipo konteineriams.</li>
    <li>Bendro studentų konteinerio (<i>vector, list ir deque</i>) skaidymas (rūšiavimas) optimizuojant antrąją strategiją naudojant Standard Template Library (STL)</li>
</ol>

<h2>Naudojimosi instrukcija</h2>
<ol>
    <li>Susiinstaliuoti <a href="https://gnuwin32.sourceforge.net/packages/make.htm">MAKE</a></li>
    <li>Atsidaryti terminalą</li>
    <li>Klonuoti programos repozitoriją</li>

    git clone https://github.com/augustetum/objektinis_programavimas_1.git

 <li>Terminale rašyti žemiau esančią komandą, norint paleisti konteinerių tyrimą
 <pre><code>make runT</code></pre>
 Terminale rašyti žemiau esančią komandą, norint paleisti 1 strategiją
 <pre><code>make run1</code></pre></li>
 Terminale rašyti žemiau esančią komandą, norint paleisti 2 strategiją
 <pre><code>make run2</code></pre></li>
  Terminale rašyti žemiau esančią komandą, norint paleisti 3 strategiją
 <pre><code>make run3</code></pre></li>
   Terminale rašyti žemiau esančią komandą, norint paleisti pradinę programą
 <pre><code>make runP</code></pre></li>
    Terminale rašyti žemiau esančią komandą, norint paleisti testavimą (v2.0)
 <pre><code>make test</code></pre></li>
</ol>


<h2>v2.0</h2>

<p>v2.0 sukurta dokumentacija ir atlikti unit testai naudojantis Catch2 testavimo framework. Testai gali būti matomi faile "catchTests.cpp". Pagal žemiau pateiktą kodo iškarpą matoma, jog visi Rule of Five metodai, realizuoti Studento klasėje, veikia korektiškai. </p>

````cpp
Randomness seeded to: 3603547871
===============================================================================
All tests passed (7 assertions in 1 test case)
````


<h2>v1.5</h2>

<p>v1.5 šakoje pridėta nauja klasė - Žmogus. Studento klasė dabar paveldi Žmogaus klasę, todėl atitinkamai buvo pakeisti ir konstruktoriai / destruktoriai. Nauja Žmogaus bei Studento klasė ištestuota su v1.2 versijoje sukurtu testavimo metodu. Rezultatai parodė, jog nauja klasė veikia su anksčiau implementuotais metodais, t.y. testo rezultatai sutampa su žemiau 1.2 versijoje aprašytais to pačio testo rezultatais.</p>

<p>Žemiau pridedamas testo kodas, leidžiantis geriau suprasti testo rezultatus: </p>

```cpp
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
                    cout << "—— Žmogaus konstuktorius ——" << endl;
                    Zmogus z("Pranas", "Pranaitis");
                    cout << z.vardas() << " " << z.pavarde() << endl;
```
<p>Kaip matoma iš žemiau pridėtos ekrano nuotraukos, testo rezultatai nuo v1.2 nepasikeitė: </p>
<img width="659" alt="Screenshot 2025-05-07 at 18 29 18" src="https://github.com/user-attachments/assets/b74cb5c9-7950-4a78-99c4-2e5087e991f2" />

<p>Tačiau, neleidžiama sukurti žmogaus objekto, dėl jo abstraktumo: </p>

```cpp
augustetumaite@Augustes-Air objektinis_programavimas_2 % make runP
g++  -std=c++17 -I/opt/homebrew/Cellar/catch2/3.8.1/include    -c -o programaFunkcijos.o programaFunkcijos.cpp
g++  -std=c++17 -I/opt/homebrew/Cellar/catch2/3.8.1/include  -c programa.cpp -o programa.o
programa.cpp:321:28: error: variable type 'Zmogus' is an abstract class
                    Zmogus z("Pranas", "Pranaitis");
                           ^
./humanClass.h:23:22: note: unimplemented pure virtual method 'printInfo' in 'Zmogus'
        virtual void printInfo() const = 0;
                     ^
1 error generated.
make: *** [programa.o] Error 1
```

<h2>v1.2</h2>

<p>Ankstesnėje v1.2 šakoje implementuoti ir testuoti "Rule of five" metodai bei perdengti įvesties ir išvesties operatoriai. Jų veikimas pritaikytas anksčiau naudotose programos dalyse, tokiose kaip: nuskaitymas iš failo, studentų įvedimas ranka, studentų rezultatų išvedimas. </p>

<p> Žemiau pateikiamos kodo iškarpos, rodančios "Rule of five" bei operatorių perdengimą. </p>

```cpp
//copy konstruktorius
        Studentas(const Studentas &s)
        : vardas_{s.vardas_}, 
        pavarde_{s.pavarde_}, 
        egzaminas_{s.egzaminas_}, 
        galutinisMed_{s.galutinisMed_}, 
        galutinisVid_{s.galutinisVid_}, 
        pazymiuVidurkis_{s.pazymiuVidurkis_},
        pazymiai_{s.pazymiai_}{}

//move konstruktorius
        Studentas(Studentas&& s)
        : vardas_{std::move(s.vardas_)}, 
        pavarde_{std::move(s.pavarde_)}, 
        egzaminas_{s.egzaminas_}, 
        galutinisMed_{s.galutinisMed_}, 
        galutinisVid_{s.galutinisVid_}, 
        pazymiuVidurkis_{s.pazymiuVidurkis_},
        pazymiai_{std::move(s.pazymiai_)}{}

//copy assignment operatorius 
        Studentas& operator=(const Studentas& s){
            if (this == &s) return *this;

            vardas_ = s.vardas_;
            pavarde_ = s.pavarde_;
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

            vardas_ = std::move(s.vardas_);
            pavarde_ = std::move(s.pavarde_);
            egzaminas_ = s.egzaminas_;
            galutinisMed_ = s.galutinisMed_;
            galutinisVid_ = s.galutinisVid_;
            pazymiuVidurkis_ = s.pazymiuVidurkis_;
            pazymiai_ = std::move(s.pazymiai_);
            
            return *this;
        }

//destruktorius
        ~Studentas(){
            vardas_.clear();
            pavarde_.clear();
            pazymiai_.clear();
        };

//perdengtas įvesties operatorius (panaikintas vardo ir pavardės tikrinimas dėl failuose esančio formatavimo, kur vardas ir pavardė GALI turėti skaičius)
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

//perdengtas išvesties operatorius
std::ostream& operator<<(std::ostream& out, const Studentas &s) {
            out << std::left << std::setw(20) << s.pavarde() << std::setw(20) << s.vardas() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisMed() << endl;
            return out;
        }

```
v1.2 versijoje sukurta klasės testavimo programa leidžia testuoti visas minėtas funkcijas, gaunami rezultatai: 
```cpp
—— Default konstruktorius ——
Egzaminas: 0

—— Vardo, pavardės konstruktorius ——
Vardas: Jonas, pavardė: Jonaitis

—— Pilnas konstruktorius ——
Vardas: Petras, pavardė: Petraitis, egzaminas: 9, galutinis vid: 8.76, galutinis med: 8.6

—— Copy konstruktorius ——
s3 kopija - vardas: Petras, pavardė: Petraitis, egzaminas: 9, galutinis vid: 8.76

Po kopijos pakeitimo - s3.vardas: Petras, s4.vardas: Antanas

—— Move konstruktorius ——
Movint’as iš s4 - vardas: Antanas, pavardė: Petraitis, egzaminas: 9

—— Copy assignment operatorius ——
s6 po s3 kopijavimo - vardas: Petras, pavardė: Petraitis

—— Move assignment operatorius ——
s7 po movinimo iš s6 - vardas: Petras, pavardė: Petraitis

—— Output’o operatorius ——
s3 naudojant operatorių <<: Petraitis           Petras              8.76                8.60                


—— Input’o operatorius ——
s8 po input: Tomauskas           Tomas               8.52                8.60                


—— Destruktorius ——
Destruktorius suveikė
```

<h2>v1.1</h2>
<p>Ankstesnė v1.1 šaka skirta palyginti "class" ir "struct" naudojimą talpinant studento duomenis. Tyrimas ir jo rezultatai pateikiami žemiau, v1.1 implementuota "class" lyginama su v1.0 versijoje naudotu "struct".</p>

<p>Tyrimas vykdytas su 3 strategija (žr. v1.0) bei vektoriaus konteineriu, vykdytos 3 iteracijos.</p>

<h3>"Class" ir "struct" | Tyrimo rezultatai  </h3>

| Programos veikimo laikas su CLASS | Programos veikimo laikas su STRUCT | Studentų kiekis | Optimizavimo vėliava | .exe failo dydis su CLASS (KB)| .exe failo dydis su STRUCT |
| ------ | ----- | --------------- | ------------------------ | ---- | ---- | 
| 0.434467s | 0.418547s | 100 000 | -O3 | 332 | 329
| 0.453639s | 0.428051s | 100 000 | -O2 | 319 | 315
| 0.453065s | 0.427737s | 100 000 | -O1 | 317 | 331
| 1.54309s | 1.32805s | 100 000 | - | 861 | 841 
| 1.95142s | 1.70978s | 1 000 000 | -O3 | 332 | 329
| 1.9155s | 1.73843s | 1 000 000 | -O2 | 319 | 315
| 1.93125s | 1.7828s | 1 000 000 | -O1 | 317 | 331
| 7.94422s | 6.41446s | 1 000 000 | - | 861 | 841




