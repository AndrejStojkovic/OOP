// 1 - 1

#include <iostream>
#include <cstring>
using namespace std;

enum tip { POP = 0, RAP = 1, ROK = 2 };

class Pesna {
    char ime[50];
    int minuti;
    enum tip tip;

public:
    Pesna() { }

    Pesna(char *ime, int minuti, enum tip tip) {
        strcpy(this->ime, ime);
        this->minuti = minuti;
        this->tip = tip;
    }

    int getMinuti() { return minuti; }
    enum tip getTip() { return tip; }

    void pecati() {
        cout << "\"" << ime << "\"" << "-" << minuti << "min\n";
    }

    ~Pesna() { }
};

class CD {
    Pesna pesni[10];
    int broj;
    int vreme;

public:
    CD() { }

    CD(int vreme) {
        this->broj = 0;
        this->vreme = vreme;
    }

    Pesna getPesna(int idx) { return pesni[idx]; }
    int getBroj() { return broj; }
    int getVreme() { return vreme; }

    void dodadiPesna(Pesna p) {
        int currMinuti = 0;
        for(int i = 0; i < broj; i++) {
            currMinuti += pesni[i].getMinuti();
        }

        if(broj < 10 && currMinuti + p.getMinuti() <= vreme) {
            pesni[broj++] = p;
        }
    }

    void pecatiPesniPoTip(enum tip t) {
        for(int i = 0; i < broj; i++) {
            if(pesni[i].getTip() == (tip)t) {
                pesni[i].pecati();
            }
        }
    }

    ~CD() { }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}
