// 1 - 13

#include<iostream>
#include<cstring>
using namespace std;

class Zichara {
    char* mesto;
    int cena;

    void copy_zichara(const Zichara& other) {
        this->mesto = new char[strlen(other.mesto) + 1];
        strcpy(this->mesto, other.mesto);
        this->cena = other.cena;
    }

public:
    Zichara() {
        this->mesto = new char[6];
        strcpy(this->mesto, "mesto");
        this->cena = 0;
    }

    Zichara(char* mesto, int cena) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
        this->cena = cena;
    }

    Zichara(const Zichara& other) {
        copy_zichara(other);
    }

    Zichara& operator=(const Zichara& other) {
        if(this == &other) {
            return *this;
        }
        delete [] mesto;
        copy_zichara(other);
        return *this;
    }

    int getCena() { return cena; }

    ~Zichara() {
        delete [] mesto;
    }
};

class PlaninarskiDom {
    char ime[15];
    int ceni[2];
    char klasa;
    bool imaZichara;
    Zichara* zichara;

    void copy_dom(const PlaninarskiDom& other) {
        strcpy(this->ime, other.ime);
        this->ceni[0] = other.ceni[0];
        this->ceni[1] = other.ceni[1];
        this->klasa = other.klasa;
        this->imaZichara = other.imaZichara;
        this->zichara = other.zichara;
    }

public:
    PlaninarskiDom() {
        this->ceni[0] = this->ceni[1] = 0;
        strcpy(this->ime, "dom");
        this->klasa = 'F';
        this->imaZichara = false;
        this->zichara = nullptr;
    }

    PlaninarskiDom(char* ime, const int* ceni, char klasa) {
        strcpy(this->ime, ime);
        for(int i = 0; i < 2; i++) {
            this->ceni[i] = ceni[i];
        }
        this->klasa = klasa;
        this->imaZichara = false;
        this->zichara = nullptr;
    }

    PlaninarskiDom(const PlaninarskiDom& other) {
        copy_dom(other);
    }

    PlaninarskiDom& operator=(const PlaninarskiDom& other) {
        if(this == &other) {
            return *this;
        }
        copy_dom(other);
        return *this;
    }

    PlaninarskiDom& operator--() {
        if(klasa < 'F') {
            klasa++;
        }
        return *this;
    }

    bool operator<=(char c) const {
        return klasa >= c;
    }

    friend ostream& operator<<(ostream& os, const PlaninarskiDom& other) {
        os << other.ime << " klasa:" << other.klasa << (other.imaZichara ? " so Zichara" : "") << "\n";
        return os;
    }

    void setZichara(Zichara zichara) {
        this->zichara = &zichara;
        imaZichara = true;
    }

    void presmetajDnevenPrestoj(int day, int month, int &s) {
        s = 0;

        if(zichara) {
            s += zichara->getCena();
        }

        if(month < 1 || month > 12 || day < 1 || day > 31) {
            throw -1;
        }

        s += (month >= 4 && month <= 8) || month == 9 && day == 1 ? ceni[0] : ceni[1];
    }
};

int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}