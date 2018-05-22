#ifndef PRG2BANK_KONTO_H
#define PRG2BANK_KONTO_H

#include<iostream>
#include<vector>
#include<memory>

using namespace std;

static int counter = 0;// щоб присвоювати номери новим клієнтосам

class Person;

class Konto : public enable_shared_from_this<Konto> {
    string kontonummer;
    int kontostand = 0;
    int disporahmen = 0; // скільки можна зайти в мінус;
    int gebuehren = 1; //oder double
    vector<weak_ptr<Person>> zeichnungsberechtigt;//max 10 mind. 1
public:

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
        } else {
            cout << "mehr als 10 zeichnungsberechtigt";
            return false;
        }
    }

    string getKontonummer() const { return kontonummer; }
    int getKontostand()const { return kontostand;}
    void setKontostand(int i) { kontostand = i;}
    int getDisporahmen()const { return disporahmen;}
    void setDisporahmen(int i) { disporahmen = i;}
    int getGebuehren()const { return gebuehren;}
    void setGebuehren(int i) {gebuehren = i;}
    size_t getZeichSize() const { return zeichnungsberechtigt.size();}

    virtual ostream &print(ostream &o) const {
        return o << '[' << getKontonummer() << ", " << getKontostand() << "€, " << " zeichnungsberechtigt="
                 << getZeichSize();
    }
};

class Girokonto : public Konto {
public:
    Girokonto(Person &p) {
        addPerson(p);
        setGebuehren(1);// fix gebuehr in Euro fuer transaktion
        setDisporahmen(0);
    }

    bool auszahlen(unsigned betrag) {
        if (this->getKontostand() < betrag + getGebuehren())
            return false;
        setKontostand(getKontostand() - (betrag + getGebuehren())) ;
        return true;
    };

    bool ueberweisen(unsigned betrag, Konto &ziel) {
        if (this->getKontostand() < betrag + getGebuehren())
            return false;
        setKontostand(getKontostand() - (betrag+getGebuehren()));
        ziel.setKontostand(ziel.getKontostand()+ betrag);
        return true;
    };

    ostream &print(ostream &o) const {
        return o << "\t[" << getKontonummer() << ", " << getKontostand() << "€, disporahmen= " << getDisporahmen()
                 << ", zeichnBerSize= "
                 << getZeichSize() << ", gebuehren= " << getGebuehren() << "€, GIROKONTO] " << endl;
    }
};


class Businesskonto : public Konto {
public:
    Businesskonto(Person &p) {
        addPerson(p);
        setGebuehren(1); //% вказуємо у процентосах
        setDisporahmen(0); //скільки в мінус можна зайти
    }

    bool auszahlen(unsigned betrag) {
        double betragInkGebur = betrag + betrag * getGebuehren() / 100;
        if (getKontostand() + getDisporahmen() < betragInkGebur)
            return false;
        setKontostand(getKontostand() - betragInkGebur);
        return true;
    };

    bool ueberweisen(unsigned betrag, Konto &ziel) {
        double betragInkGebur = betrag + betrag * getGebuehren() / 100;
        if (getKontostand() < betragInkGebur)
            return false;
        setKontostand(getKontostand() - betragInkGebur);
        ziel.setKontostand(ziel.getKontostand() + betrag);
        return true;
    };

    ostream &print(ostream &o) const {
        return o << "\t[" << getKontonummer() << ", " << getKontostand() << "€, disporahmen= " << getDisporahmen()
                 << ", zeichnBerSize= "
                 << getZeichSize() << ", gebuehren= " << getGebuehren() << "%, BUSINESSKONTO]" << endl;
    }
};

inline ostream &operator<<(ostream &o, const Konto &p) {
    return p.print(o);
}

#endif
