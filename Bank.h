#include "Person.h"

class Konto;
class Person;

class Bank {
    vector<shared_ptr<Person>> kunden;
public:

    void neuerKunde(string name) {
        shared_ptr<Person> sp(new Person(name));
        kunden.push_back(sp);
    }


    // My methode

    vector<shared_ptr<Person>> getKunden(){
        return kunden;
    }


    virtual ostream &print(ostream &o) const {
        o << "Erste Bank " << ", kundenSize = " << kunden.size() << ": \n\n";
        for (auto k: kunden)
            k.get()->print(cout);

        return o;
    }
};

inline ostream &operator<<(ostream &o, const Bank &p) {
    return p.print(o);
}
