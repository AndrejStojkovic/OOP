// 1 - 1

#include <iostream>
#include <cstring>
using namespace std;

enum tip { POP = 0, RAP = 1, ROK = 2 };

class Pesna {
    char* name;
    int minutes;
    tip type;

public:
    Pesna() {
        this->name = new char[2];
        strcpy(this->name, " ");
        this->minutes = 0;
        this->type = POP;
    }

    Pesna(char* name, int minutes, enum tip type) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->minutes = minutes;
        this->type = type;
    }

    Pesna(const Pesna& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->minutes = other.minutes;
        this->type = other.type;
    }

    Pesna& operator=(const Pesna& other) {
        if(this == &other) return *this;

        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->minutes = other.minutes;
        this->type = other.type;

        return *this;
    }

    char* getName() { return name; }
    void setName(char* name) { strcpy(this->name, name); }

    int getMinutes() { return minutes; }
    void setMinutes(int minutes) { this->minutes = minutes; }

    enum tip getType() { return type; }
    void setType(enum tip type) { this->type = type; }

    void pecati() {
        cout << "\"" << name << "\"" << "-" << minutes << "min\n";
    }

    ~Pesna() {
        delete [] name;
    }
};

class CD {
    Pesna pesni[10];
    int num;
    int length;

public:
    CD() {
        this->num = 0;
    }

    CD(int vreme) {
        this->num = 0;
        this->length = vreme;
    }

    Pesna getPesna(int idx) { return pesni[idx]; }

    int getNum() { return num; }
    void setNum(int num) { this->num = num; }

    int getLength() { return length; }
    void setLength(int length) { this->length = length; }

    void dodadiPesna(Pesna p) {
        int currMinutes = 0;

        for(int i = 0; i < num; i++) currMinutes += pesni[i].getMinutes();

        if(num < 10 && currMinutes + p.getMinutes() <= length) {
            pesni[num++] = p;
        }
    }

    void pecatiPesniPoTip(enum tip t) {
        for(int i = 0; i < num; i++) {
            if(pesni[i].getType() == t) {
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
        for (int i=0; i<omileno.getNum(); i++)
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
