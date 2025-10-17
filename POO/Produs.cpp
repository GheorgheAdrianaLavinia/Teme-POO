#include <iostream>
#include <cstring>

using namespace std;

class Produs {
private:
    char* denumire;
    float pret;
    int cantitate;

public:
    //  Constructor implicit
    Produs() {
        const char* textDefault = "necunoscut";

        denumire = new char[strlen(textDefault) + 1];
        strcpy_s(denumire, strlen(textDefault) + 1, textDefault);

        pret = 0;
        cantitate = 0;
    }

    //  Constructor cu parametri
    Produs(const char* denumire, float pret, int cantitate) {
        const char* textDefault = "necunoscut";

        if (denumire == nullptr || strlen(denumire) == 0) {
            this->denumire = new char[strlen(textDefault) + 1];
            strcpy_s(this->denumire, strlen(textDefault) + 1, textDefault);
        }
        else {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
        }

        this->pret = (pret >= 0) ? pret : 0;
        this->cantitate = (cantitate >= 0) ? cantitate : 0;
    }

    // Constructor de copiere
    Produs(const Produs& copie) {
        denumire = new char[strlen(copie.denumire) + 1];
        strcpy_s(denumire, strlen(copie.denumire) + 1, copie.denumire);

        pret = copie.pret;
        cantitate = copie.cantitate;
    }

    // Operator = 
    Produs& operator=(const Produs& copie) {
        if (this == &copie) {
            return *this;
        }

        if (denumire != nullptr) {
            delete[] denumire;
            denumire = nullptr;
        }

        denumire = new char[strlen(copie.denumire) + 1];
        strcpy_s(denumire, strlen(copie.denumire) + 1, copie.denumire);

        pret = copie.pret;
        cantitate = copie.cantitate;

        return *this;
    }

    //Destructor
    ~Produs() {
        if (denumire != nullptr) {
            delete[] denumire;
            denumire = nullptr;
        }
    }

    //  Getters
    char* getDenumire() {
        return denumire;
    }

    float getPret() {
        return pret;
    }

    int getCantitate() {
        return cantitate;
    }

    // Setters (cu validare + realocare la char*)
    void setDenumire(const char* denumireNoua) {
        const char* textDefault = "necunoscut";

        if (this->denumire != nullptr) {
            delete[] this->denumire;
            this->denumire = nullptr;
        }

        if (denumireNoua == nullptr || strlen(denumireNoua) == 0) {
            this->denumire = new char[strlen(textDefault) + 1];
            strcpy_s(this->denumire, strlen(textDefault) + 1, textDefault);
        }
        else {
            this->denumire = new char[strlen(denumireNoua) + 1];
            strcpy_s(this->denumire, strlen(denumireNoua) + 1, denumireNoua);
        }
    }

    void setPret(float pretNou) {
        this->pret = (pretNou >= 0) ? pretNou : 0;
    }

    void setCantitate(int cantitateNoua) {
        this->cantitate = (cantitateNoua >= 0) ? cantitateNoua : 0;
    }

    //  Afisare
    void afisare() {
        cout << "denumire: " << denumire
            << ", pret: " << pret << " ron"
            << ", cantitate: " << cantitate << endl;
    }
};

int main() {
    // obiect cu constructor implicit
    Produs p0;

    // obiecte cu constructor cu parametri
    Produs p1("Cafea boabe 1kg", 79.90f, 12);
    Produs p2("Lapte 1L", 6.50f, 30);

    // afisare initiala
    p0.afisare();
    p1.afisare();
    p2.afisare();

    // modificare cu setteri
    p0.setDenumire("Ciocolata neagra 90g");
    p0.setPret(8.99f);
    p0.setCantitate(20);

    p0.afisare();

    // getteri
    cout << "Produsul \"" << p1.getDenumire()
        << "\" costa " << p1.getPret()
        << " ron si are cantitatea " << p1.getCantitate()
        << " in stoc." << endl;


    Produs p3 = p1;       // constructor de copiere
    p3.setDenumire("Cafea boabe 1kg (copie)");
    cout << "Dupa modificarea copiei:" << endl;
    p1.afisare();
    p3.afisare();

    return 0;
}
