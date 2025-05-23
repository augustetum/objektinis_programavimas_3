<h1>v3.0</h1>

<p>v3.0 programoje realizuota Vektoriaus klasė, pakeičianti įprastą std::vector. Programoje panaudotos ankstesnių projektų (objektinis_programavimas_1 ir objektinis_programavimas_2) metu vystytos strategijos bei testai, kurie pritaikyti veikimui su nauja Vector klase.</p>

<p>Žemiau pateikiamos 5 Vektoriaus klasės metodų realizacijos</p>

````cpp
// shrink_fo_fit() metodas
    void shrink_to_fit(){
        if (capacity_ > size_) {
            T* new_data = new T[size_];
            for (size_type i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

// reserve() metodas
    void reserve(size_type new_cap ){
        if (new_cap > capacity_) {
            T* new_data = new T[new_cap];
            for (size_type i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }
    }

// push_back() metodas 
    void push_back(const T& item){
        if(size_ == capacity_) {
            resize();
        }
        data_[size_] = item;
        ++size_;
    }

//erase() metodas
    iterator erase(const_iterator first, const_iterator last ){
            size_t pos_first = std::distance(static_cast<const T*>(begin()), first);
            size_t pos_last = std::distance(static_cast<const T*>(begin()), last);
            size_t count = pos_last - pos_first;
        
            if (count == 0) {
                return begin() + pos_first;
            }
            
            for (size_t i = pos_first; i + count < size_; ++i) {
                data_[i] = data_[i + count];
            }
        
            size_ -= count;
        
            return begin() + pos_first;
        }

// == operatorius
    template <typename T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs ){
        if(lhs.size() != rhs.size()){
            return false;
        }

        for(size_t i = 0; i < lhs.size(); ++i) {
            if(lhs.at(i) != rhs.at(i)){
                return false;
            }
        }

        return true;
    }

`````

<p>Klasės pranašumas prieš std::Vector buvo ištestuotas užpildant tuščius vektorius Studentų objektais. Tyrimo rezultatai matomi žemiau. </p>

<h3>std::vector ir Vector klasės greičio testavimas</h3>

| Vektoriaus elementų (Studentų) kiekis | Programos veikimo laikas std::vector (s) | Programos veikimo laikas Vector klasei (s) | 
| ---- | ----- | ---- | 
| 10000 | 9.4416e-05 | 5.025e-05 |
| 100000 | 0.000603833 | 0.000438167 |
| 1000000 |0.00390825 | 0.00352071 |
| 10000000 | 0.0363332 | 0.0290009 |
|100000000 | 0.203071 |  0.198156 |

<p>Taip pat ištestuotas atminties perskirstymų kiekis, atliekant vektorių užpildymą</p>

| Vektoriaus elementų (Studentų) kiekis | Perskirstymų kiekis std::vector | Perskirstymų kiekis Vector klasei | 
| --- | --- | --- |
|10000 | 14 | 14 |
| 100000 | 17 | 17 |
| 1000000 | 20 | 20 |
| 10000000 | 24 | 24 |
| 100000000 | 27 |  27 |

<p>Atliktas spartos tyrimas. Lyginti 3 strategijos rezultatai su std::vector iš objektinis_programavimas_2 repozitorijoje atlikto tyrimo. Įvykdytos trys iteracijos, visose iteracijose pasirinktas rikiavimas pagal galutinį balą su vidurkiu. </p>

| Studentų kiekis faile | Konteinerio tipas | Programos veikimo laikas |
| --- | --- | --- |
| 100 000 | std::vector | 0.418547s |
| 100 000 | Vector klasė | 0.527548s |
| 1 000 000 | std::vector | 1.70978s |
| 1 000 000 | Vector klasė | 2.66731s |
| 10 000 000 | std::vector | 59.2562s |
| 10 000 000 | Vector klasė | 87.4112s |
