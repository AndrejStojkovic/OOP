// 1 - 11

#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik {
    char* ime;
    bool pol;
    int vozrast;

    void copy_ucesnik(const Ucesnik& other) {
        this->ime = new char[strlen(other.ime) + 1];
        strcpy(this->ime, other.ime);
        this->pol = other.pol;
        this->vozrast = other.vozrast;
    }

public:
    Ucesnik() {
        this->ime = new char[5];
        strcpy(this->ime, "ime");
        this->pol = false;
        this->vozrast = 0;
    }

    Ucesnik(char* ime, bool pol, int vozrast) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->pol = pol;
        this->vozrast = vozrast;
    }

    Ucesnik(const Ucesnik& other) {
        copy_ucesnik(other);
    }

    Ucesnik& operator=(const Ucesnik& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->ime;
        copy_ucesnik(other);
        return *this;
    }

    bool operator>(const Ucesnik& other) {
        return other.vozrast > this->vozrast;
    }

    friend ostream& operator<<(ostream& os, Ucesnik& other) {
        os << other.ime << "\n" << (other.pol ? "mashki" : "zhenski") << "\n" << other.vozrast << "\n";
        return os;
    }

    int getVozrast() {
        return vozrast;
    }

    ~Ucesnik() {
        delete [] ime;
    }
};

class Maraton {
    char lokacija[100];
    Ucesnik* ucesnici;
    int num;

    void copy_maraton(const Maraton& other) {
        strcpy(this->lokacija, other.lokacija);
        this->ucesnici = new Ucesnik[other.num];
        for(int i = 0; i < other.num; i++) {
            this->ucesnici[i] = other.ucesnici[i];
        }
        this->num = other.num;
    }

public:
    Maraton() {
        strcpy(this->lokacija, "lokacija");
        ucesnici = nullptr;
        num = 0;
    }

    Maraton(char* lokacija) {
        strcpy(this->lokacija, lokacija);
        ucesnici = nullptr;
        num = 0;
    }

    Maraton(const Maraton& other) {
        copy_maraton(other);
    }

    Maraton& operator=(const Maraton& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->ucesnici;
        copy_maraton(other);
        return *this;
    }

    Maraton& operator+=(const Ucesnik& other) {
        Ucesnik* tmp = new Ucesnik[num + 1];
        for(int i = 0; i < num; i++) {
            tmp[i] = this->ucesnici[i];
        }
        tmp[num++] = other;

        delete [] ucesnici;
        this->ucesnici = new Ucesnik[num];
        for(int i = 0; i < num; i++) {
            this->ucesnici[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }

    float prosecnoVozrast() {
        float s = 0;
        for(int i = 0; i < num; i++) {
            s += ucesnici[i].getVozrast();
        }
        return s / (float)num;
    }

    void pecatiPomladi(Ucesnik& u) {
        for(int i = 0; i < num; i++) {
            if(ucesnici[i] > u) {
                cout << ucesnici[i];
            }
        }
    }

    ~Maraton() {
        delete [] ucesnici;
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);

    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}