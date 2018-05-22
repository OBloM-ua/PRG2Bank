#ifndef PRG2BANK_PERSON_H
#define PRG2BANK_PERSON_H

#include "Konto.h"

class Konto;

class Person : public enable_shared_from_this<Person> {
    string name;
    vector<shared_ptr<Konto>> konten; //beliebig viele mind. 1
public:

    Person(string name) {
            this->name = name;
            neues_konto('g');
    }

    bool konto_teilen(Konto &k, Person &p) { //можна допилити, а можна хуй забити бо чужі люди можуть можуть давати самі собі доступ до чужих рахунків
        p.addKonto(k);
        k.addPerson(p);
        return true;
    }

    bool neues_konto(char art) {
        if (art == 'g') {
            shared_ptr<Konto> k(new Girokonto(*this));
            konten.push_back(k);
            return true;
        }  else if (art == 'b') {
            shared_ptr<Konto> k(new Businesskonto(*this));
            konten.push_back(k);
            return true;

        } else {
            cerr << "falsche argument";
            return false;
        }
    }


    void kuendigen() {
        for (auto &i:konten) {
            i = nullptr;
            konten.pop_back();
        }
    }

    // My methode

    void addKonto(Konto &k) {
        shared_ptr<Konto> sk = make_shared<Konto>(k);
        konten.push_back(sk);
    }

    vector<shared_ptr<Konto>> getKonten(){
        return konten;
    }

    virtual ostream &print(ostream &o) const {
        o  << name << ", Konten Anzahl= " << konten.size() << endl;
        for (auto k: konten)
            k.get()->print(cout);

        o << endl;
        return o;
    }


};

inline ostream &operator<<(ostream &o, const Person &p) {
    return p.print(o);
}


#endif //PRG2BANK_PERSON_H