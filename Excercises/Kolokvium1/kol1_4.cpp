// 1 - 4

#include <iostream>
#include <cstring>
using namespace std;

#define MAX 20

class Patnik {
    char ime[100];
    int klasa;
    bool velosiped;

public:
    Patnik() {
        strcpy(this->ime, " ");
        klasa = 1;
        velosiped = false;
    }

    Patnik(char* ime, int klasa, bool velosiped) {
        strcpy(this->ime, ime);
        this->klasa = klasa;
        this->velosiped = velosiped;
    }

    Patnik(const Patnik& p) {
        strcpy(this->ime, p.ime);
        this->klasa = p.klasa;
        this->velosiped = p.velosiped;
    }

    Patnik& operator=(const Patnik& other) {
        if(this == &other) return *this;

        strcpy(this->ime, other.ime);
        this->klasa = other.klasa;
        this->velosiped = other.velosiped;

        return *this;
    }

    friend ostream& operator<<(ostream& os, const Patnik& p) {
        os << p.ime << "\n" << p.klasa << "\n" << p.velosiped << "\n\n";
        return os;
    }

    char* getIme() {
        return ime;
    }

    void setIme(char* ime) {
        strcpy(this->ime, ime);
    }

    int getKlasa() const {
        return klasa;
    }

    void setKlasa(int klasa) {
        this->klasa = klasa;
    }

    bool getVelosiped() const {
        return velosiped;
    }

    void setVelosiped(bool velosiped) {
        this->velosiped = velosiped;
    }

    ~Patnik() { }
};

class Voz {
    char destinacija[100];
    Patnik* patnici;
    int num;
    int velosipedi;
    int mesto[2];

public:
    Voz() {
        strcpy(this->destinacija, " ");
        patnici = new Patnik[MAX];
        num = 0;
        velosipedi = 0;
        mesto[0] = mesto[1] = 0;
    }

    Voz(char* destinacija, int velosipedi) {
        strcpy(this->destinacija, destinacija);
        patnici = new Patnik[MAX];
        num = 0;
        this->velosipedi = velosipedi;
        mesto[0] = mesto[1] = 0;
    }

    Voz(const Voz& v) {
        strcpy(this->destinacija, v.destinacija);
        this->patnici = v.patnici;
        this->num = v.num;
        this->velosipedi = v.velosipedi;
        for(int i = 0; i < 2; i++) this->mesto[i] = v.mesto[i];
    }

    Voz& operator=(const Voz& other) {
        if(this == &other) return *this;

        strcpy(this->destinacija, other.destinacija);
        this->patnici = other.patnici;
        this->num = other.num;
        this->velosipedi = other.velosipedi;
        for(int i = 0; i < 2; i++) this->mesto[i] = other.mesto[i];

        return *this;
    }

    Voz& operator+=(const Patnik& p) {
        this->patnici[num++] = p;
        return *this;
    }

    friend ostream& operator<<(ostream& os, Voz& other) {
        os << other.destinacija << endl;

        if(other.velosipedi == 0) {
            for(int i = 0; i < other.num; i++) {
                if(!other.patnici[i].getVelosiped()) {
                    os << other.patnici[i];
                }
            }

            return os;
        }

        for(int i = 0; i < other.num; i++) {
            if(other.patnici[i].getVelosiped()) {
                if(other.patnici[i].getKlasa() == 1) {
                    if(other.velosipedi > 0) other.velosipedi--;
                    else other.mesto[0]++;
                }
            }
        }

        for(int i = 0; i < other.num; i++) {
            if(other.patnici[i].getVelosiped()) {
                if(other.patnici[i].getKlasa() == 2) {
                    if(other.velosipedi > 0) other.velosipedi--;
                    else other.mesto[1]++;
                }
            }
        }

        for(int i = 0; i < other.num; i++) {
            os << other.patnici[i];
        }

        return os;
    }

    void patniciNemaMesto() {
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << mesto[0] << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << mesto[1] << endl;
    }

    ~Voz() {
        delete [] patnici;
    }
};

int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}