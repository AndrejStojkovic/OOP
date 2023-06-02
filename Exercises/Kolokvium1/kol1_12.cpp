// 1 - 12

#include <iostream>
#include <cstring>
using namespace std;

class Pica {
    char ime[15];
    int cena;
    char* sostojki;
    int namaluvanje;

    void copy_pica(const Pica& other) {
        strcpy(this->ime, other.ime);
        this->cena = other.cena;
        this->sostojki = new char[strlen(other.sostojki) + 1];
        strcpy(this->sostojki, other.sostojki);
        this->namaluvanje = other.namaluvanje;
    }

public:
    Pica() {
        strcpy(this->ime, "pizaa");
        this->cena = 0;
        this->sostojki = nullptr;
        this->namaluvanje = 0;
    }

    Pica(char* ime, int cena, char* sostojki, int namaluvanje) {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
        this->namaluvanje = namaluvanje;
    }

    Pica(const Pica& other) {
        copy_pica(other);
    }

    Pica& operator=(const Pica& other) {
        if(this == &other) {
            return *this;
        }
        delete [] sostojki;
        copy_pica(other);
        return *this;
    }

    int getCena() {
        return cena;
    }

    int getNamaluvanje() {
        return namaluvanje;
    }

    void pecati() {
        cout << ime << " - " << sostojki << ", " << cena;
    }

    bool istiSe(const Pica& p) {
        return !strcmp(this->sostojki, p.sostojki);
    }

    ~Pica() {
        delete [] sostojki;
    }
};

class Picerija {
    char ime[15];
    Pica* pici;
    int num;

    void copy_picerija(const Picerija& other) {
        strcpy(ime, other.ime);
        num = other.num;
        pici = new Pica[num];
        for (int i = 0; i < num; i++) {
            pici[i] = other.pici[i];
        }
    }

public:
    Picerija() {
        strcpy(this->ime, " ");
        pici = nullptr;
        num = 0;
    }

    Picerija(char* ime) {
        strcpy(this->ime, ime);
        pici = nullptr;
        num = 0;
    }

    Picerija(const Picerija &other) {
        copy_picerija(other);
    }

    Picerija& operator=(const Picerija& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->pici;
        copy_picerija(other);
        return *this;
    }

    Picerija& operator+=(Pica &p) {
        for(int i = 0; i < num; i++) {
            if(pici[i].istiSe(p)) {
                return *this;
            }
        }

        Pica* tmp = new Pica[num + 1];
        for(int i = 0; i < num; i++) {
            tmp[i] = pici[i];
        }
        tmp[num++] = p;

        delete [] this->pici;
        this->pici = new Pica[num];
        for(int i = 0; i < num; i++) {
            pici[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }

    char* getIme() {
        return ime;
    }

    void setIme(const char* ime) {
        strcpy(this->ime, ime);
    }

    void piciNaPromocija() {
        for(int i = 0; i < num; i++) {
            if(pici[i].getNamaluvanje() != 0) {
                pici[i].pecati();
                cout << " " << pici[i].getCena() * (1 - pici[i].getNamaluvanje() / 100.0) << "\n";
            }
        }
    }

    ~Picerija() {
        delete [] pici;
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}