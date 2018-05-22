#ifndef PRG2BANK_KONTO_H
#define PRG2BANK_KONTO_H

#include<iostream>
#include<vector>
#include<memory>

using namespace std;

static int counter = 0;// щоб присвоювати номери новим клієнтосам

class Person;

class Konto : public enable_shared_from_this<Konto> {
public:
    string kontonummer;
    int kontostand = 0;
    int disporahmen = 0; // скільки можна зайти в мінус;
    int gebuehren = 1; //oder double
    vector<weak_ptr<Person>> zeichnungsberechtigt;//max 10 mind. 1

    Konto() {
        kontonummer = string("AT") + to_string(counter++);
    }

//    Konto(Person &p) {
//        addPerson(p);
//        kontonummer = string("AT") + to_string(counter++);
//    }

    void einzahlen(unsigned betrag) { kontostand += betrag; }

    virtual bool auszahlen(unsigned betrag) {
        if (kontostand >= betrag) {
            kontostand -= betrag;
            return true;
        } else {
//            cout << "Sie haben nicht genug Geld" << endl;
            return false;
        }
    }

    virtual bool ueberweisen(unsigned betrag, Konto &ziel) {
        if (kontostand >= betrag) {
            kontostand -= betrag; // знімаю гроші
            ziel.kontostand += betrag; // відправляю грошики
            return true;
        } else return false;
    }


    // My methode

    bool addPerson(Person &p) {
        if (zeichnungsberechtigt.size() < 10) {
            weak_ptr<Person> sp = make_shared<Person>(p);
            zeichnungsberechtigt.push_back(sp);
            return true;
        } else return false;
    }

    shared_ptr<Konto> getShared() {
        return shared_from_this();
    }


    virtual ostream &print(ostream &o) const {
        return o << '[' << kontonummer << ", " << kontostand << "€, " << " zeichnungsberechtigt="
                 << zeichnungsberechtigt.size();
    }
};

inline ostream &operator<<(ostream &o, const Konto &p) {
    return p.print(o);
}








class Girokonto : public Konto {
public:
    Girokonto(Person &p) {
        addPerson(p);
        gebuehren = 0; //%gebuehren = 1; //%
        disporahmen = 0;
    }

    bool auszahlen(unsigned betrag) {
        if (this->kontostand < betrag + gebuehren)
            return false;
        kontostand -= betrag + gebuehren;
        return true;
    };

    bool ueberweisen(unsigned betrag, Konto &ziel) {
        if (this->kontostand < betrag + gebuehren)
            return false;
        this->kontostand -= betrag + gebuehren;
        ziel.kontostand += betrag;
        return true;
    };

    ostream &print(ostream &o) const {
        return o << "\t[" << kontonummer << ", " << kontostand << "€, disporahmen= " << disporahmen << ", zeichnBerSize= "
                 << zeichnungsberechtigt.size() << ", gebuehren= " << gebuehren << "€, GIRKONTO] "<< endl;
    }
};

class Businesskonto : public Konto {
public:
    Businesskonto(Person &p) {
        addPerson(p);
        gebuehren = 1; //% вказуємо у процентосах
        disporahmen = 0; //скільки в мінус можна зайти
    }

    bool auszahlen(unsigned betrag) {
        double betragInkGebur = betrag + betrag * gebuehren / 100;
        if (this->kontostand + disporahmen < betragInkGebur)
            return false;
        kontostand -= betragInkGebur;
        return true;
    };

    bool ueberweisen(unsigned betrag, Konto &ziel) {
        double betragInkGebur = betrag + betrag * gebuehren / 100;
        if (this->kontostand < betragInkGebur)
            return false;
        this->kontostand -= betragInkGebur;
        ziel.kontostand += betrag;
        return true;
    };

    ostream &print(ostream &o) const {
        return o << "\t[" << kontonummer << ", " << kontostand << "€, disporahmen= " << disporahmen << ", zeichnBerSize= "
                 << zeichnungsberechtigt.size() << ", gebuehren= " << gebuehren << "%, BISNESSKONTO]" <<endl;
    }
};

#endif
