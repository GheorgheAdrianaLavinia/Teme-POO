#include <iostream>
#include <cstring>

using namespace std;

class Angajat {
private:
    char* nume;
    char* functie;
    float salariu;

public:
    // Constructor implicit
    Angajat() {
        const char* defaultNume = "necunoscut";
        const char* defaultFunctie = "necunoscuta";

        nume = new char[strlen(defaultNume) + 1];
        strcpy_s(nume, strlen(defaultNume) + 1, defaultNume);

        functie = new char[strlen(defaultFunctie) + 1];
        strcpy_s(functie, strlen(defaultFunctie) + 1, defaultFunctie);

        salariu = 0;
    }

    // Constructor cu parametri
    Angajat(const char* nume, const char* functie, float salariu) {
        const char* defaultNume = "necunoscut";
        const char* defaultFunctie = "necunoscuta";

        if (nume == nullptr || strlen(nume) == 0) {
            this->nume = new char[strlen(defaultNume) + 1];
            strcpy_s(this->nume, strlen(defaultNume) + 1, defaultNume);
        }
        else {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }

        if (functie == nullptr || strlen(functie) == 0) {
            this->functie = new char[strlen(defaultFunctie) + 1];
            strcpy_s(this->functie, strlen(defaultFunctie) + 1, defaultFunctie);
        }
        else {
            this->functie = new char[strlen(functie) + 1];
            strcpy_s(this->functie, strlen(functie) + 1, functie);
        }

        this->salariu = (salariu >= 0) ? salariu : 0;
    }

    // Constructor de copiere
    Angajat(const Angajat& a) {
        nume = new char[strlen(a.nume) + 1];
        strcpy_s(nume, strlen(a.nume) + 1, a.nume);

        functie = new char[strlen(a.functie) + 1];
        strcpy_s(functie, strlen(a.functie) + 1, a.functie);

        salariu = a.salariu;
    }

    // Operator =
    Angajat& operator=(const Angajat& a) {
        if (this == &a) {
            return *this;
        }

        if (nume != nullptr) {
            delete[] nume;
            nume = nullptr;
        }

        if (functie != nullptr) {
            delete[] functie;
            functie = nullptr;
        }

        nume = new char[strlen(a.nume) + 1];
        strcpy_s(nume, strlen(a.nume) + 1, a.nume);

        functie = new char[strlen(a.functie) + 1];
        strcpy_s(functie, strlen(a.functie) + 1, a.functie);

        salariu = a.salariu;

        return *this;
    }

    // Destructor
    ~Angajat() {
        if (nume != nullptr) {
            delete[] nume;
            nume = nullptr;
        }
        if (functie != nullptr) {
            delete[] functie;
            functie = nullptr;
        }
    }

    // Getteri
    char* getNume() {
        return nume;
    }

    char* getFunctie() {
        return functie;
    }

    float getSalariu() {
        return salariu;
    }

    // Setteri
    void setNume(const char* numeNou) {
        if (nume != nullptr) {
            delete[] nume;
            nume = nullptr;
        }

        const char* def = "necunoscut";
        if (numeNou == nullptr || strlen(numeNou) == 0) {
            nume = new char[strlen(def) + 1];
            strcpy_s(nume, strlen(def) + 1, def);
        }
        else {
            nume = new char[strlen(numeNou) + 1];
            strcpy_s(nume, strlen(numeNou) + 1, numeNou);
        }
    }

    void setFunctie(const char* functieNoua) {
        if (functie != nullptr) {
            delete[] functie;
            functie = nullptr;
        }

        const char* def = "necunoscuta";
        if (functieNoua == nullptr || strlen(functieNoua) == 0) {
            functie = new char[strlen(def) + 1];
            strcpy_s(functie, strlen(def) + 1, def);
        }
        else {
            functie = new char[strlen(functieNoua) + 1];
            strcpy_s(functie, strlen(functieNoua) + 1, functieNoua);
        }
    }

    void setSalariu(float salariuNou) {
        salariu = (salariuNou >= 0) ? salariuNou : 0;
    }

    // Afisare
    void afisare() {
        cout << "nume: " << nume
            << ", functie: " << functie
            << ", salariu: " << salariu << " lei" << endl;
    }
};

int main() {
    Angajat a1;
    Angajat a2("Popescu Ion", "Programator", 7500);
    Angajat a3("Ionescu Ana", "Tester", 5200);

    a1.afisare();
    a2.afisare();
    a3.afisare();

    a1.setNume("Marin Elena");
    a1.setFunctie("Manager");
    a1.setSalariu(9000);

    a1.afisare();

    cout << "Angajatul " << a2.getNume()
        << " lucreaza ca " << a2.getFunctie()
        << " si are salariul " << a2.getSalariu() << " lei." << endl;

    return 0;
}

