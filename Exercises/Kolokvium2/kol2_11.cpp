// 2 - 11

#include <iostream>
#include <cstring>
using namespace std;

class Delo {
    char name[50];
    int year;
    char country[50];

    void copy_delo(const Delo& other) {
        strcpy(this->name, other.name);
        this->year = other.year;
        strcpy(this->country, other.country);
    }
public:
    Delo() {
        strcpy(this->name, "name");
        this->year = 0;
        strcpy(this->country, "country");
    }

    Delo(char* name, int year, char* country) {
        strcpy(this->name, name);
        this->year = year;
        strcpy(this->country, country);
    }

    Delo(const Delo& other) {
        copy_delo(other);
    }

    Delo& operator=(const Delo& other) {
        if(this == &other) {
            return *this;
        }
        copy_delo(other);
        return *this;
    }

    bool operator==(const Delo& other) {
        return !strcmp(name, other.name);
    }

    char* getIme() {
        return name;
    }

    int getYear() {
        return year;
    }

    char* getCountry() {
        return country;
    }

    ~Delo() { }
};

class Pretstava {
    Delo d;
    int n;
    char* date;

    void copy_pretstava(const Pretstava& other) {
        this->d = other.d;
        this->n = other.n;
        this->date = new char[strlen(other.date) + 1];
        strcpy(this->date, other.date);
    }
public:
    Pretstava() {
        this->d = Delo();
        this->n = 0;
        this->date = new char[5];
        strcpy(this->date, "date");
    }

    Pretstava(Delo d, int n, char* date) {
        this->d = d;
        this->n = n;
        this->date = new char[strlen(date) + 1];
        strcpy(this->date, date);
    }

    Pretstava(const Pretstava& other) {
        copy_pretstava(other);
    }

    Pretstava& operator=(const Pretstava& other) {
        if(this == &other) {
            return *this;
        }
        delete [] date;
        copy_pretstava(other);
        return *this;
    }

    Delo getDelo() {
        return d;
    }

    int getN() {
        return n;
    }

    virtual int cena() {
        int n = d.getYear() > 1900 ? 50 : d.getYear() > 1800 ? 75 : 100;
        int m = !strcmp(d.getCountry(), "Italija") ? 100 : !strcmp(d.getCountry(), "Rusija") ? 150 : 80;
        return n + m;
    }

    ~Pretstava() {
        delete [] date;
    }
};

class Balet : public Pretstava {
    static int b_price;

public:
    Balet() : Pretstava() { }

    Balet(Delo d, int tickets, char* date) : Pretstava(d, tickets, date) { }

    int cena() {
        return Pretstava::cena() + b_price;
    }

    static void setCenaBalet(int _price) {
        b_price = _price;
    }

    ~Balet() { }
};

class Opera : public Pretstava {
public:
    Opera() : Pretstava() { }

    Opera(Delo d, int tickets, char* date) : Pretstava(d, tickets, date) { }

    ~Opera() { }
};

int Balet::b_price = 150;

int prihod(Pretstava** p, int n) {
    int s = 0;
    for(int i = 0; i < n; i++) {
        s += p[i]->cena() * p[i]->getN();
    }
    return s;
}

int brojPretstaviNaDelo(Pretstava** p, int n, Delo d) {
    int s = 0;
    for(int i = 0; i < n; i++) {
        if(p[i]->getDelo() == d) {
            s++;
        }
    }
    return s;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}