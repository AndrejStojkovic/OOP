// 1 - 17

#include <iostream>
#include <cstring>
using namespace std;

enum Tip { LINUX, UNIX, WINDOWS };

class OperativenSistem {
    char* ime;
    float verzija;
    Tip tip;
    float golemina;

    void copy_os(const OperativenSistem& other) {
        this->ime = new char[strlen(other.ime) + 1];
        strcpy(this->ime, other.ime);
        this->verzija = other.verzija;
        this->tip = other.tip;
        this->golemina = other.golemina;
    }

public:
    OperativenSistem() {
        this->ime = nullptr;
        this->verzija = 0.1;
        this->tip = LINUX;
        this->golemina = 1.0;
    }

    OperativenSistem(const char* ime, const float verzija, const Tip tip, const float golemina) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->verzija = verzija;
        this->tip = tip;
        this->golemina = golemina;
    }

    OperativenSistem(const OperativenSistem& other) {
        copy_os(other);
    }

    OperativenSistem& operator=(const OperativenSistem& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->ime;
        copy_os(other);
        return *this;
    }

    void pecati() {
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << tip << " Golemina:" << golemina << "GB" << "\n";
    }

    bool ednakviSe(const OperativenSistem& os) {
        return !strcmp(ime, os.ime) && verzija == os.verzija && tip == os.tip && golemina == os.golemina;
    }

    int sporediVerzija(const OperativenSistem& os) {
        return verzija == os.verzija ? 0 : verzija < os.verzija ? -1 : 1;
    }

    bool istaFamilija(const OperativenSistem& sporedba) {
        return !strcmp(ime, sporedba.ime) && tip == sporedba.tip;
    }

    ~OperativenSistem() {
        delete [] ime;
    }
};

class Repozitorium {
    char ime[20];
    OperativenSistem* os;
    int os_n;

    void copy_repo(const Repozitorium& other) {
        strcpy(this->ime, other.ime);
        this->os = new OperativenSistem[other.os_n];
        for(int i = 0; i < other.os_n; i++) {
            this->os[i] = other.os[i];
        }
        this->os_n = other.os_n;
    }

public:
    Repozitorium() {
        os = nullptr;
        os_n = 0;
    }

    Repozitorium(const char* ime) {
        strcpy(this->ime, ime);
        this->os = nullptr;
        os_n = 0;
    }

    Repozitorium(const Repozitorium& other) {
        copy_repo(other);
    }

    Repozitorium& operator=(const Repozitorium& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->os;
        copy_repo(other);
        return *this;
    }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << ime << "\n";
        for(int i = 0; i < os_n; i++) {
            os[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem& operativenSistem) {
        int idx = -1;
        for(int i = 0; i < os_n; i++) {
            if(os[i].ednakviSe(operativenSistem)) {
                idx = i;
                break;
            }
        }

        if(idx == -1) {
            return;
        }

        for(int i = idx; i < os_n - 1; i++) {
            os[i] = os[i + 1];
        }
        os_n--;
    }

    void dodadi(const OperativenSistem& nov) {
        for(int i = 0; i < os_n; i++) {
            if(os[i].istaFamilija(nov) && os[i].sporediVerzija(nov) == -1) {
                os[i] = nov;
                return;
            }
        }

        OperativenSistem* tmp = new OperativenSistem[os_n + 1];
        for(int i = 0; i < os_n; i++) {
            tmp[i] = os[i];
        }
        tmp[os_n++] = nov;

        delete [] os;
        this->os = new OperativenSistem[os_n];
        for(int i = 0; i < os_n; i++) {
            this->os[i] = tmp[i];
        }
        delete [] tmp;
    }

    ~Repozitorium() {
        delete [] os;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}