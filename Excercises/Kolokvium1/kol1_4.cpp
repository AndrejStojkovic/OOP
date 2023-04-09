// 1 - 4

#include <iostream>
#include <cstring>
using namespace std;

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

public:
    Voz() {
        strcpy(this->destinacija, " ");
        patnici = new Patnik[0];
        num = velosipedi = 0;
    }

    Voz(char* destinacija, int velosipedi) {
        strcpy(this->destinacija, destinacija);
        patnici = new Patnik[0];
        num = 0;
        this->velosipedi = velosipedi;
    }

    Voz(const Voz& v) {
        strcpy(this->destinacija, v.destinacija);
        this->patnici = new Patnik[v.num];
        for(int i = 0; i < v.num; i++) this->patnici[i] = v.patnici[i];
        this->num = v.num;
        this->velosipedi = v.velosipedi;
    }

    Voz& operator=(const Voz& other) {
        if(this == &other) return *this;

        strcpy(this->destinacija, other.destinacija);
        delete [] this->patnici;
        this->patnici = new Patnik[other.num];
        for(int i = 0; i < other.num; i++) this->patnici[i] = other.patnici[i];
        this->num = other.num;
        this->velosipedi = other.velosipedi;

        return *this;
    }

    Voz& operator+=(const Patnik& p) {
        if(p.getVelosiped() && !velosipedi) return *this;

        Patnik* tmp = new Patnik[num + 1];
        for(int i = 0; i < this->num; i++) tmp[i] = patnici[i];
        tmp[this->num++] = p;

        delete [] patnici;
        this->patnici = new Patnik[num];
        for(int i = 0; i < num; i++) patnici[i] = tmp[i];
        delete [] tmp;

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
            os << other.patnici[i];
        }

        return os;
    }

    void patniciNemaMesto() {
        int mesto1 = 0, mesto2 = 0, bc = velosipedi;
        for(int i = 0; i < num; i++) {
            if(patnici[i].getVelosiped() && patnici[i].getKlasa() == 1) {
                if(bc) bc--;
                else mesto1++;
            }
        }

        for(int i = 0; i < num; i++) {
            if(patnici[i].getVelosiped() && patnici[i].getKlasa() == 2) {
                if(bc) bc--;
                else mesto2++;
            }
        }

        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << mesto1 << "\n";
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << mesto2 << "\n";
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