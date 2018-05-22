#include "Bank.h"
#include <memory>
#include <iostream>
#include <vector>
#include "Konto.h"
#include "Person.h"
//#include "Bank.h"

using namespace std;


int main() {

    Bank b;
    b.neuerKunde("Alexander Kern"); //автоматично створюю Girokonto
    Person& kern = *b.getKunden()[0];
    kern.neues_konto('b');

    Konto& kernGiroKonto = *kern.getKonten()[0];
    Konto& kernBusinessKonto = *kern.getKonten()[1];



    kernGiroKonto.einzahlen(10000);
    kernBusinessKonto.einzahlen(10000);


    kernBusinessKonto.ueberweisen(1000, kernGiroKonto);


    cout << b;













    return 0;
}