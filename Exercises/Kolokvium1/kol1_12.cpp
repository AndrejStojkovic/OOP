// 1 - 12

#include <iostream>
#include <cstring>
using namespace std;

class Pica {
    char ime[15];
    int cena;
    char* sostojki;
    int namaluvanje;

public:
    Pica() {
        strcpy(this->ime, " ");
        this->cena = 0;
        this->sostojki = new char[1];
        strcpy(this->sostojki, " ");
        namaluvanje = 0;
    }

    Pica(char* ime, int cena, char* sostojki, int namaluvanje) {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
        this->namaluvanje = namaluvanje;
    }

    Pica(const Pica& p) {
        strcpy(this->ime, p.ime);
        this->cena = p.cena;
        this->sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(this->sostojki, p.sostojki);
        this->namaluvanje = p.namaluvanje;
    }

    Pica& operator=(const Pica& p) {
        if(this == &p) return *this;

        strcpy(this->ime, p.ime);
        this->cena = p.cena;

        delete [] this->sostojki;
        this->sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(this->sostojki, p.sostojki);

        this->namaluvanje = p.namaluvanje;

        return *this;
    }

    char* getIme() { return ime; }
    void setIme(const char* ime) { strcpy(this->ime, ime); }

    int getCena() { return cena; }
    void setCena(const int cena) { this->cena = cena; }

    char* getSostojki() { return sostojki; }
    void setSostojki(const char* sostojki) {
        delete [] this->sostojki;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
    }

    int getNamaluvanje() { return namaluvanje; }
    void setNamaluvanje(const int namaluvanje) { this->namaluvanje = namaluvanje; }

    void pecati() {
        cout << ime << " - " << sostojki << ", " << cena;
    }

    bool istiSe(const Pica& p) {
        return strcmp(this->sostojki, p.sostojki) == 0;
    }

    ~Pica() {
        delete [] sostojki;
    }
};

class Picerija {
    char ime[15];
    Pica* pici;
    int num;

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

    Picerija(const char* ime, Pica* pici, const int num) {
        strncpy(this->ime, ime, 14);
        this->ime[14] = 0;
        this->num = num;

        this->pici = new Pica[num];

        for(int i = 0; i < num; i++) {
            this->pici[i] = pici[i];
        }
    }

    Picerija(const Picerija &p) {
        strcpy(ime, p.ime);
        num = p.num;
        pici = new Pica[num];
        for (int i = 0; i < num; i++)
            pici[i] = p.pici[i];
    }

    Picerija& operator=(const Picerija& p) {
        if(this == &p) return *this;

        strcpy(this->ime, p.ime);
        this->num = p.num;

        delete [] this->pici;
        this->pici = new Pica[num];

        for(int i = 0; i < num; i++)
            pici[i] = p.pici[i];

        return *this;
    }

    Picerija& operator+=(Pica &p) {
        bool flag = false;

        for(int i = 0; i < num; i++) {
            if(pici[i].istiSe(p)) flag = true;
        }

        if(flag) return *this;

        Pica* temp = new Pica[num + 1];
        for(int i = 0; i < num; i++) temp[i] = pici[i];
        temp[num++] = p;
        delete [] this->pici;
        this->pici = temp;

        return *this;
    }

    void dodadi(Pica &p) {
        bool flag = false;

        for(int i = 0; i < num; i++) {
            if(pici[i].istiSe(p)) flag = true;
        }

        if(flag) return;

        Pica* temp = new Pica[num + 1];
        for(int i = 0; i < num; i++) temp[i] = pici[i];
        temp[num++] = p;
        delete [] this->pici;
        this->pici = temp;
    }

    char* getIme() {
        return ime;
    }

    void setIme(const char* ime) {
        strcpy(this->ime, ime);
    }

    Pica* getPici() {
        return pici;
    }

    void setPici(Pica* pici) {
        this->pici = pici;
    }

    int getNum() {
        return num;
    }

    void setNum(int num) {
        this->num = num;
    }

    void piciNaPromocija() {
        for(int i = 0; i < num; i++) {
            //cout << "-" << pici[i].getIme() << " - " << pici[i].getCena() << ", " << pici[i].getNamaluvanje() << "\n";
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
