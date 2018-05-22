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
    kern.neues_konto('g');
    kern.neues_konto('g');
    kern.neues_konto('g');
    kern.neues_konto('b');
    kern.neues_konto('b');
    kern.neues_konto('b');
    Konto& kernKonto = *kern.getKonten()[0];

//    b.neuerKunde("Sebastian Strache");
//    Person& strache = *b.getKunden()[1];
//    Konto& stracheKonto = *strache.getKonten()[0];


    kernKonto.einzahlen(99);

    cout << b;

    kern.kuendigen();
    cout << b;













    return 0;
}