#include "Frunza.h"

// constructor implicit
Frunza::Frunza() {
    tip = nullptr;
    lungime = 0;
    esteVerde = true;
}

// constructor cu parametri
Frunza::Frunza(const char* tip, float lungime, bool esteVerde) {
    this->tip = new char[strlen(tip) + 1];
    strcpy_s(this->tip, strlen(tip) + 1, tip);

    this->lungime = lungime;
    this->esteVerde = esteVerde;
}

// constructor de copiere
Frunza::Frunza(const Frunza& f) {
    if (f.tip != nullptr) {
        tip = new char[strlen(f.tip) + 1];
        strcpy_s(tip, strlen(f.tip) + 1, f.tip);
    }
    else {
        tip = nullptr;
    }

    lungime = f.lungime;
    esteVerde = f.esteVerde;
}

// operator =
Frunza& Frunza::operator=(const Frunza& f) {
    if (this != &f) {
        delete[] tip;

        if (f.tip != nullptr) {
            tip = new char[strlen(f.tip) + 1];
            strcpy_s(tip, strlen(f.tip) + 1, f.tip);
        }
        else {
            tip = nullptr;
        }

        lungime = f.lungime;
        esteVerde = f.esteVerde;
    }
    return *this;
}

// destructor
Frunza::~Frunza() {
    delete[] tip;
}

// getteri
const char* Frunza::getTip() const { return tip; }
float Frunza::getLungime() const { return lungime; }
bool Frunza::getEsteVerde() const { return esteVerde; }

// afisare
void Frunza::afisare() const {
    std::cout << "Tip frunza: " << (tip ? tip : "(necunoscut)")
        << ", Lungime: " << lungime << " cm"
        << ", Stare: " << (esteVerde ? "verde" : "uscata") << "\n";
}
