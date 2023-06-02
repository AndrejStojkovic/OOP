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

public:
    OperativenSistem() {
        this->ime = new char[0];
        strcpy(this->ime, " ");
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

    OperativenSistem(const OperativenSistem& os) {
        this->ime = new char[strlen(os.ime) + 1];
        strcpy(this->ime, os.ime);
        this->verzija = os.verzija;
        this->tip = os.tip;
        this->golemina = os.golemina;
    }

    OperativenSistem& operator=(const OperativenSistem& os) {
        if(this == &os) return *this;

        delete [] this->ime;
        this->ime = new char[strlen(os.ime) + 1];
        strcpy(this->ime, os.ime);
        this->verzija = os.verzija;
        this->tip = os.tip;
        this->golemina = os.golemina;

        return *this;
    }

    char* getIme() { return ime; }
    void setIme(char* ime) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
    }

    float getVerzija() { return verzija; }
    void setVerzija(float verzija) { this->verzija = verzija; }

    enum Tip getTip() { return tip; }
    void setTip(enum Tip Tip) { this->tip = tip; }

    float getGolemina() { return golemina; }
    void setGolemina(float golemina) { this->golemina = golemina; }

    void pecati() {
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << tip << " Golemina:" << golemina << "GB" << "\n";
    }

    bool ednakviSe(const OperativenSistem& os) {
        return strcmp(ime, os.ime) == 0 && verzija == os.verzija && tip == os.tip && golemina == os.golemina;
    }

    int sporediVerzija(const OperativenSistem& os) {
        return verzija == os.verzija ? 0 : verzija < os.verzija ? -1 : 1;
    }

    bool istaFamilija(const OperativenSistem& sporedba) {
        return strcmp(ime, sporedba.ime) == 0 && tip == sporedba.tip;
    }

    ~OperativenSistem() {
        delete [] ime;
    }
};

class Repozitorium {
    char ime[20];
    OperativenSistem* os;
    int os_n;

public:
    Repozitorium() {
        strcpy(ime, " ");
        os = new OperativenSistem[10];
        os_n = 0;
    }

    Repozitorium(const char* ime) {
        strcpy(this->ime, ime);
        this->os = new OperativenSistem[10];
        os_n = 0;
    }

    Repozitorium(const char* ime, OperativenSistem* os, const int os_n) {
        strcpy(this->ime, ime);
        this->os = os;
        this->os_n = os_n;
    }

    Repozitorium(const Repozitorium& repo) {
        strcpy(this->ime, repo.ime);
        this->os = repo.os;
        this->os_n = repo.os_n;
    }

    Repozitorium& operator=(const Repozitorium& repo) {
        if(this == &repo) return *this;

        strcpy(this->ime, repo.ime);
        delete [] this->os;
        this->os = new OperativenSistem[repo.os_n];
        this->os = repo.os;
        this->os_n = repo.os_n;

        return *this;
    }

    char* getIme() { return ime; }
    void setIme(char* ime) { strcpy(this->ime, ime); }

    OperativenSistem* getOS() { return os; }
    void setOS(OperativenSistem* os, int n) {
        delete [] os;
        this->os = new OperativenSistem[n];
        for(int i = 0; i < n; i++) this->os[i] = os[i];
    }

    int getNum() { return os_n; }
    void setNum(int os_n) { this->os_n = os_n; }

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

        if(idx == -1) return;

        for(int i = idx; i < os_n - 1; i++) os[i] = os[i + 1];
        os_n--;
    }

    void dodadi(const OperativenSistem& nov) {
        for(int i = 0; i < os_n; i++) {
            if(os[i].istaFamilija(nov) && os[i].sporediVerzija(nov) == -1) {
                os[i] = nov;
                return;
            }
        }

        os[os_n++] = nov;
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
