// 1 - 5

#include <iostream>
#include <cstring>
using namespace std;

class Gitara {
    char serial_number[25];
    float price;
    int year;
    char type[40];

public:
    Gitara() {
        strcpy(this->serial_number, "serial");
        this->price = 0;
        this->year = 2023;
        strcpy(this->type, "type");
    }

    Gitara(char* type, char* serial_number, int year, float price) {
        strcpy(this->serial_number, serial_number);
        this->price = price;
        this->year = year;
        strcpy(this->type, type);
    }

    Gitara(const Gitara& other) {
        strcpy(this->serial_number, other.serial_number);
        this->price = other.price;
        this->year = other.year;
        strcpy(this->type, other.type);
    }

    Gitara& operator=(const Gitara& other) {
        if(this == &other) return *this;

        strcpy(this->serial_number, other.serial_number);
        this->price = other.price;
        this->year = other.year;
        strcpy(this->type, other.type);

        return *this;
    }

    char* getSerialNumber() { return serial_number; }
    void setSerialNumber(char* serial_number) { strcpy(this->serial_number, serial_number); }

    float getPrice() { return price; }
    void setPrice(float price) { this->price = price; }

    int getYear() { return year; }
    void setYear(int year) { this->year = year; }

    char* getType() { return type; }
    void setType(char* type) { strcpy(this->type, type); }

    bool daliIsti(Gitara g) {
        return strcmp(serial_number, g.serial_number) == 0;
    }

    void pecati() {
        cout << serial_number << " " << type << " " << price << "\n";
    }

    ~Gitara() { }
};

class Magacin {
    char name[30];
    char location[60];
    Gitara* guitars;
    int num;
    int year;

public:
    Magacin() {
        strcpy(this->name, " ");
        strcpy(this->location, " ");
        guitars = new Gitara[0];
        this->num = this->year = 0;
    }

    Magacin(char* name, char* location) {
        strcpy(this->name, name);
        strcpy(this->location, location);
        this->guitars = new Gitara[0];
        this->num = 0;
        this->year = 2023;
    }

    Magacin(char* name, char* location, int year) {
        strcpy(this->name, name);
        strcpy(this->location, location);
        this->guitars = new Gitara[0];
        this->num = 0;
        this->year = year;
    }

    Magacin(char* name, char* location, Gitara* guitars, int num, int year) {
        strcpy(this->name, name);
        strcpy(this->location, location);
        this->num = num;
        this->year = year;
        delete [] this->guitars;
        this->guitars = new Gitara[num];
        for(int i = 0; i < num; i++) this->guitars[i] = guitars[i];
    }

    Magacin(const Magacin& other) {
        strcpy(this->name, other.name);
        strcpy(this->location, other.location);
        this->num = other.num;
        this->year = other.year;
        this->guitars = new Gitara[other.num];
        for(int i = 0; i < other.num; i++) this->guitars[i] = other.guitars[i];
    }

    Magacin& operator=(const Magacin& other) {
        if(this == &other) return *this;

        strcpy(this->name, other.name);
        strcpy(this->location, other.location);
        this->num = other.num;
        this->year = other.year;
        this->guitars = new Gitara[other.num];
        for(int i = 0; i < other.num; i++) this->guitars[i] = other.guitars[i];

        return *this;
    }

    char* getName() { return name; }
    void setName(char* name) { strcpy(this->name, name); }

    char* getLocation() { return location; }
    void setLocation(char* location) { strcpy(this->location, location); }

    int getNum() { return num; }
    void setNum(int num) { this->num = num; }

    int getYear() { return year; }
    void setYear(int year) { this->year = year; }

    Gitara* getGuitars() { return guitars; }
    void setGuitars(Gitara* guitars, int n) {
        delete [] guitars;
        guitars = new Gitara[n];
        for(int i = 0; i < n; i++) this->guitars[i] = guitars[i];
    }

    double vrednost() {
        double s = 0;
        for(int i = 0; i < num; i++) s += guitars[i].getPrice();
        return s;
    }

    void dodadi(Gitara d) {
        Gitara* tmp = new Gitara[num];

        for(int i = 0; i < num; i++) tmp[i] = this->guitars[i];
        delete [] this->guitars;

        this->guitars = new Gitara[num + 1];

        for(int i = 0; i < num; i++) this->guitars[i] = tmp[i];
        delete [] tmp;

        this->guitars[num++] = d;
    }

    void prodadi(Gitara p) {
        int el = 0, ct = 0;

        for(int i = 0; i < num; i++) el += !guitars[i].daliIsti(p);

        if(!el) return;

        Gitara* tmp = new Gitara[el];

        for(int i = 0; i < num; i++) {
            if(guitars[i].daliIsti(p)) continue;
            tmp[ct++] = this->guitars[i];
        }

        delete [] this->guitars;
        this->guitars = new Gitara[ct];
        for(int i = 0; i < ct; i++) this->guitars[i] = tmp[i];
        this->num = ct;

        delete [] tmp;
    }

    void pecati(bool daliNovi) {
        cout << name << " " << location << "\n";
        for(int i = 0; i < num; i++) {
            if(daliNovi && guitars[i].getYear() > year) {
                guitars[i].pecati();
            } else if(!daliNovi) {
                guitars[i].pecati();
            }
        }
    }

    ~Magacin() {
        delete [] guitars;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getType()<<endl;
        cout<<g.getSerialNumber()<<endl;
        cout<<g.getYear()<<endl;
        cout<<g.getPrice()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}