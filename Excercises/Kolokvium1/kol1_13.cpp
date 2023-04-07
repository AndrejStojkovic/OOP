// 1 - 13

// 1 - 3

#include<iostream>
#include<cstring>
using namespace std;

class Zichara {
    char* mesto;
    int cena;

public:
    Zichara() {
        this->mesto = new char[2];
        strcpy(this->mesto, " ");
        this->cena = 0;
    }

    Zichara(char* mesto, int cena) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
        this->cena = cena;
    }

    Zichara(const Zichara& other) {
        this->mesto = new char[strlen(other.mesto) + 1];
        strcpy(this->mesto, other.mesto);
        this->cena = other.cena;
    }

    Zichara& operator=(const Zichara& other) {
        if(this == &other) return *this;

        this->mesto = new char[strlen(other.mesto) + 1];
        strcpy(this->mesto, other.mesto);
        this->cena = other.cena;

        return *this;
    }

    char* getMesto() { return mesto; }
    void setMesto(char* mesto) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
    }

    int getCena() { return cena; }
    void setCena(int cena) { this->cena = cena; }
};

class PlaninarskiDom {
    char ime[15];
    int ceni[2];
    char klasa;
    bool imaZichara;
    Zichara* zichara;

public:
    PlaninarskiDom() {
        strcpy(this->ime, " ");
        this->ceni[0] = this->ceni[1] = 0;
        klasa = 'F';
        imaZichara = false;
        zichara = nullptr;
    }

    PlaninarskiDom(char* ime, const int* ceni, char klasa) {
        strcpy(this->ime, ime);
        for(int i = 0; i < 2; i++) this->ceni[i] = ceni[i];
        this->klasa = klasa;
        imaZichara = false;
        zichara = nullptr;
    }

    PlaninarskiDom(const PlaninarskiDom& other) {
        strcpy(this->ime, other.ime);
        this->ceni[0] = other.ceni[0];
        this->ceni[1] = other.ceni[1];
        this->klasa = other.klasa;
        imaZichara = other.imaZichara;
        zichara = other.zichara;
    }

    PlaninarskiDom& operator=(const PlaninarskiDom& other) {
        if(this == &other) return *this;

        strcpy(this->ime, other.ime);
        this->ceni[0] = other.ceni[0];
        this->ceni[1] = other.ceni[1];
        this->klasa = other.klasa;
        imaZichara = other.imaZichara;
        zichara = other.zichara;

        return *this;
    }

    PlaninarskiDom& operator--() {
        if(klasa < 'F') klasa++;
        return *this;
    }

    bool operator<=(char c) const {
        return klasa >= c;
    }

    friend ostream& operator<<(ostream& os, const PlaninarskiDom& other) {
        os << other.ime << " klasa:" << other.klasa << (other.imaZichara ? " so Zichara" : "") << "\n";
        return os;
    }

    char* getIme() { return ime; }
    void setIme(char* ime) { strcpy(this->ime, ime); }

    int* getCeni() { return ceni; }
    void setCeni(int* ceni) {
        this->ceni[0] = ceni[0];
        this->ceni[1] = ceni[1];
    }

    char getKlasa() { return klasa; }
    void setKlasa(char klasa) { this->klasa = klasa; }

    bool imaZhichara() { return imaZichara; }

    Zichara getZichara() { return *zichara; }
    void setZichara(Zichara zichara) {
        this->zichara = &zichara;
        imaZichara = true;
    }

    void presmetajDnevenPrestoj(int day, int month, int &s)
    {
        s = 0;

        if(zichara) s += zichara->getCena();

        if(month < 1 || month > 12 || day < 1 || day > 31) throw -1;

        if((month >= 4 && month <= 8) || month == 9 && day == 1) s += ceni[0];
        else s += ceni[1];
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