#include <iostream>
#include <cstring>

using namespace std;

class Film {
private:
    char* titlu;
    int durata;

public:
    Film() {
        const char* def = "necunoscut";
        titlu = new char[strlen(def) + 1];
        strcpy_s(titlu, strlen(def) + 1, def);
        durata = 0;
    }

    Film(const char* titlu, int durata) {
        const char* def = "necunoscut";

        if (titlu == nullptr || strlen(titlu) == 0) {
            this->titlu = new char[strlen(def) + 1];
            strcpy_s(this->titlu, strlen(def) + 1, def);
        }
        else {
            this->titlu = new char[strlen(titlu) + 1];
            strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
        }

        this->durata = (durata > 0) ? durata : 0;
    }

    Film(const Film& f) {
        titlu = new char[strlen(f.titlu) + 1];
        strcpy_s(titlu, strlen(f.titlu) + 1, f.titlu);
        durata = f.durata;
    }

    Film& operator=(const Film& f) {
        if (this == &f) return *this;

        if (titlu != nullptr) {
            delete[] titlu;
            titlu = nullptr;
        }

        titlu = new char[strlen(f.titlu) + 1];
        strcpy_s(titlu, strlen(f.titlu) + 1, f.titlu);
        durata = f.durata;

        return *this;
    }

    ~Film() {
        if (titlu != nullptr) {
            delete[] titlu;
            titlu = nullptr;
        }
    }

    // get/set
    const char* getTitlu() const { return titlu; }
    int getDurata() const { return durata; }

    void setDurata(int d) {
        durata = (d > 0) ? d : 0;
    }

    // operatori stream
    friend ostream& operator<<(ostream& out, const Film& f) {
        out << "Titlu: " << f.titlu << ", Durata: " << f.durata << " min";
        return out;
    }

    friend istream& operator>>(istream& in, Film& f) {
        char buffer[256];

        cout << "Titlu film: ";
        in.getline(buffer, 256);

        cout << "Durata (minute): ";
        in >> f.durata;
        in.ignore();

        if (f.titlu != nullptr) {
            delete[] f.titlu;
            f.titlu = nullptr;
        }

        if (strlen(buffer) == 0) {
            const char* def = "necunoscut";
            f.titlu = new char[strlen(def) + 1];
            strcpy_s(f.titlu, strlen(def) + 1, def);
        }
        else {
            f.titlu = new char[strlen(buffer) + 1];
            strcpy_s(f.titlu, strlen(buffer) + 1, buffer);
        }

        if (f.durata < 0) f.durata = 0;

        return in;
    }
};

class Cinema {
private:
    Film** filme;
    int nrFilme;

public:
    Cinema() {
        filme = nullptr;
        nrFilme = 0;
    }

    Cinema(const Cinema& c) {
        nrFilme = c.nrFilme;

        if (nrFilme > 0) {
            filme = new Film * [nrFilme];
            for (int i = 0; i < nrFilme; i++) {
                filme[i] = new Film(*c.filme[i]);
            }
        }
        else {
            filme = nullptr;
        }
    }

    Cinema& operator=(const Cinema& c) {
        if (this == &c) return *this;

        if (filme != nullptr) {
            for (int i = 0; i < nrFilme; i++) {
                delete filme[i];
            }
            delete[] filme;
            filme = nullptr;
        }

        nrFilme = c.nrFilme;

        if (nrFilme > 0) {
            filme = new Film * [nrFilme];
            for (int i = 0; i < nrFilme; i++) {
                filme[i] = new Film(*c.filme[i]);
            }
        }

        return *this;
    }

    ~Cinema() {
        if (filme != nullptr) {
            for (int i = 0; i < nrFilme; i++) {
                delete filme[i];
            }
            delete[] filme;
            filme = nullptr;
        }
    }

    // operator+ : adaugare film
    Cinema& operator+(const Film& f) {
        Film** copie = new Film * [nrFilme + 1];

        for (int i = 0; i < nrFilme; i++) {
            copie[i] = filme[i];
        }

        copie[nrFilme] = new Film(f);

        delete[] filme;
        filme = copie;
        nrFilme++;

        return *this;
    }

    // operator[]
    Film& operator[](int index) {
        if (index < 0 || index >= nrFilme) {
            return *filme[0]; // variant? simpl? pt laborator
        }
        return *filme[index];
    }

    void afisare() const {
        cout << "Cinema – " << nrFilme << " filme:" << endl;
        for (int i = 0; i < nrFilme; i++) {
            cout << "  [" << i << "] " << *filme[i] << endl;
        }
    }
};

int main() {
    Film f1("Inception", 148);
    Film f2("Interstellar", 169);

    Film fCitit;
    cin >> fCitit;

    Cinema c;
    c + f1;
    c + f2;
    c + fCitit;

    c.afisare();

    cout << "\nFilm accesat cu operator[]:" << endl;
    cout << c[1] << endl;

    return 0;
}
