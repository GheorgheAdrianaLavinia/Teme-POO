#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Bilet {
protected:
    char* eveniment;
    float pret;

public:
    Bilet() {
        const char* def = "necunoscut";
        eveniment = new char[strlen(def) + 1];
        strcpy_s(eveniment, strlen(def) + 1, def);
        pret = 0;
    }

    Bilet(const char* eveniment, float pret) {
        const char* def = "necunoscut";

        if (eveniment == nullptr || strlen(eveniment) == 0) {
            this->eveniment = new char[strlen(def) + 1];
            strcpy_s(this->eveniment, strlen(def) + 1, def);
        }
        else {
            this->eveniment = new char[strlen(eveniment) + 1];
            strcpy_s(this->eveniment, strlen(eveniment) + 1, eveniment);
        }

        this->pret = (pret >= 0) ? pret : 0;
    }

    Bilet(const Bilet& b) {
        eveniment = new char[strlen(b.eveniment) + 1];
        strcpy_s(eveniment, strlen(b.eveniment) + 1, b.eveniment);
        pret = b.pret;
    }

    Bilet& operator=(const Bilet& b) {
        if (this == &b) return *this;

        if (eveniment != nullptr) {
            delete[] eveniment;
            eveniment = nullptr;
        }

        eveniment = new char[strlen(b.eveniment) + 1];
        strcpy_s(eveniment, strlen(b.eveniment) + 1, b.eveniment);
        pret = b.pret;

        return *this;
    }

    ~Bilet() {
        if (eveniment != nullptr) {
            delete[] eveniment;
            eveniment = nullptr;
        }
    }

    void afisare() const {
        cout << "Bilet: eveniment=" << eveniment << ", pret=" << pret;
    }
};

class BiletVIP : public Bilet {
private:
    char* zona;
    float taxaVIP;

public:
    BiletVIP() : Bilet() {
        const char* def = "standard";
        zona = new char[strlen(def) + 1];
        strcpy_s(zona, strlen(def) + 1, def);
        taxaVIP = 0;
    }

    BiletVIP(const char* eveniment, float pret, const char* zona, float taxaVIP)
        : Bilet(eveniment, pret) {

        const char* def = "standard";
        if (zona == nullptr || strlen(zona) == 0) {
            this->zona = new char[strlen(def) + 1];
            strcpy_s(this->zona, strlen(def) + 1, def);
        }
        else {
            this->zona = new char[strlen(zona) + 1];
            strcpy_s(this->zona, strlen(zona) + 1, zona);
        }

        this->taxaVIP = (taxaVIP >= 0) ? taxaVIP : 0;
    }

    BiletVIP(const BiletVIP& v) : Bilet(v) {
        zona = new char[strlen(v.zona) + 1];
        strcpy_s(zona, strlen(v.zona) + 1, v.zona);
        taxaVIP = v.taxaVIP;
    }

    BiletVIP& operator=(const BiletVIP& v) {
        if (this == &v) return *this;

        Bilet::operator=(v);

        if (zona != nullptr) {
            delete[] zona;
            zona = nullptr;
        }

        zona = new char[strlen(v.zona) + 1];
        strcpy_s(zona, strlen(v.zona) + 1, v.zona);
        taxaVIP = v.taxaVIP;

        return *this;
    }

    ~BiletVIP() {
        if (zona != nullptr) {
            delete[] zona;
            zona = nullptr;
        }
    }

    float pretFinal() const {
        return pret + taxaVIP;
    }

    void afisare() const {
        cout << "BiletVIP: eveniment=" << eveniment
            << ", pret baza=" << pret
            << ", zona=" << zona
            << ", taxaVIP=" << taxaVIP
            << ", pret final=" << pretFinal();
    }

    void scrieBinar(ofstream& out) const {
        int lenE = (eveniment != nullptr) ? (int)strlen(eveniment) : 0;
        out.write((char*)&lenE, sizeof(lenE));
        if (lenE > 0) out.write(eveniment, lenE);

        out.write((char*)&pret, sizeof(pret));

        int lenZ = (zona != nullptr) ? (int)strlen(zona) : 0;
        out.write((char*)&lenZ, sizeof(lenZ));
        if (lenZ > 0) out.write(zona, lenZ);

        out.write((char*)&taxaVIP, sizeof(taxaVIP));
    }

    void citesteBinar(ifstream& in) {
        int lenE = 0;
        in.read((char*)&lenE, sizeof(lenE));

        char* bufE = nullptr;
        if (lenE > 0) {
            bufE = new char[lenE + 1];
            in.read(bufE, lenE);
            bufE[lenE] = '\0';
        }
        else {
            const char* def = "necunoscut";
            bufE = new char[strlen(def) + 1];
            strcpy_s(bufE, strlen(def) + 1, def);
        }

        if (eveniment != nullptr) { delete[] eveniment; eveniment = nullptr; }
        eveniment = bufE;

        in.read((char*)&pret, sizeof(pret));

        int lenZ = 0;
        in.read((char*)&lenZ, sizeof(lenZ));

        char* bufZ = nullptr;
        if (lenZ > 0) {
            bufZ = new char[lenZ + 1];
            in.read(bufZ, lenZ);
            bufZ[lenZ] = '\0';
        }
        else {
            const char* def = "standard";
            bufZ = new char[strlen(def) + 1];
            strcpy_s(bufZ, strlen(def) + 1, def);
        }

        if (zona != nullptr) { delete[] zona; zona = nullptr; }
        zona = bufZ;

        in.read((char*)&taxaVIP, sizeof(taxaVIP));

        // validari
        if (pret < 0) pret = 0;
        if (taxaVIP < 0) taxaVIP = 0;
    }
};

void salveaza(const char* fisier, BiletVIP* v, int n) {
    ofstream out(fisier, ios::binary);
    out.write((char*)&n, sizeof(n));
    for (int i = 0; i < n; i++) v[i].scrieBinar(out);
    out.close();
}

BiletVIP* incarca(const char* fisier, int& n) {
    ifstream in(fisier, ios::binary);
    if (!in.is_open()) { n = 0; return nullptr; }

    in.read((char*)&n, sizeof(n));
    if (n <= 0) { n = 0; return nullptr; }

    BiletVIP* v = new BiletVIP[n];
    for (int i = 0; i < n; i++) v[i].citesteBinar(in);

    in.close();
    return v;
}

int main() {
    BiletVIP v[3] = {
        BiletVIP("Concert Rock", 150.0f, "VIP", 50.0f),
        BiletVIP("Teatru", 80.0f, "Loja", 30.0f),
        BiletVIP("Meci Fotbal", 120.0f, "A", 20.0f)
    };

    salveaza("bilete.dat", v, 3);

    int n = 0;
    BiletVIP* citite = incarca("bilete.dat", n);

    cout << "Citite din fisier (" << n << "):\n";
    for (int i = 0; i < n; i++) {
        citite[i].afisare();
        cout << "\n";
    }

    delete[] citite;
    return 0;
}
