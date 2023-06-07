// 2 - 7

#include<iostream>
#include<cstring>
#define MAX_PINOVI 4
#define DEFAULT_LIMIT 7
using namespace std;

class OutOfBoundsException {
public:
    void message() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto\n";
    }
};

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;

private:
    void copy_karticka(const Karticka& other) {
        strcpy(this->smetka, other.smetka);
        this->pin = other.pin;
        this->povekjePin = other.povekjePin;
    }

public:
    Karticka() {
        strcpy(this->smetka, "smetka");
        this->pin = 0;
        this->povekjePin = false;
    }
    Karticka(char* smetka,int pin){
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    Karticka(const Karticka& other) {
        copy_karticka(other);
    }

    Karticka& operator=(const Karticka& other) {
        if(this == &other) {
            return *this;
        }
        copy_karticka(other);
        return *this;
    }

    virtual int tezinaProbivanje() {
        int s = 0, c = pin;
        while(c) {
            s++;
            c /= 10;
        }
        return s;
    }

    friend ostream& operator<<(ostream& out, Karticka& k) {
        out << k.smetka << ": " << k.tezinaProbivanje() << "\n";
        return out;
    }

    char* getSmetka() {
        return smetka;
    }

    bool getDopolnitelenPin() {
        return povekjePin;
    }

    ~Karticka() { }
};

class SpecijalnaKarticka : public Karticka {
    int* pinovi;
    int pinovi_n;

    void copy_special(const SpecijalnaKarticka& other) {
        strcpy(this->smetka, other.smetka);
        this->pin = other.pin;
        this->povekjePin = other.povekjePin;
        this->pinovi = new int[other.pinovi_n];
        for(int i = 0; i < other.pinovi_n; i++) {
            this->pinovi[i] = other.pinovi[i];
        }
        this->pinovi_n = other.pinovi_n;
    }
public:
    SpecijalnaKarticka() : Karticka() {
        this->povekjePin = true;
        this->pinovi = nullptr;
        this->pinovi_n = 0;
    }

    SpecijalnaKarticka(char* smetka, int pin) : Karticka(smetka, pin) {
        this->povekjePin = true;
        this->pinovi = nullptr;
        this->pinovi_n = 0;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka& other) : Karticka(other) {
        copy_special(other);
    }

    SpecijalnaKarticka& operator=(const SpecijalnaKarticka& other) {
        if(this == &other) {
            return *this;
        }
        Karticka::operator=(other);
        delete [] pinovi;
        copy_special(other);
        return *this;
    }

    SpecijalnaKarticka& operator+=(int pin) {
        if(pinovi_n >= MAX_PINOVI) {
            throw OutOfBoundsException();
        }

        int* tmp = new int[pinovi_n + 1];
        for(int i = 0; i < pinovi_n; i++) {
            tmp[i] = this->pinovi[i];
        }
        tmp[pinovi_n++] = pin;

        delete [] pinovi;
        this->pinovi = new int[pinovi_n];
        for(int i = 0; i < pinovi_n; i++) {
            this->pinovi[i] = tmp[i];
        }
        delete [] tmp;
        return *this;
    }

    int tezinaProbivanje() {
        return Karticka::tezinaProbivanje() + pinovi_n;
    }

    ~SpecijalnaKarticka() {
        delete [] pinovi;
    }
};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka() {
        strcpy(this->naziv, "banka");
        this->broj = 0;
    }

    Banka(char* naziv, Karticka** karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++){
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            } else {
                this->karticki[i] = new Karticka(*karticki[i]);
            }
        }
        this->broj = broj;
    }

    static void setLIMIT(int _limit) {
        LIMIT = _limit;
    }

    void dodadiDopolnitelenPin(char* smetka, int pin) {
        for(int i = 0; i < broj; i++) {
            if(karticki[i]->getDopolnitelenPin() && !strcmp(this->karticki[i]->getSmetka(), smetka)) {
                *dynamic_cast<SpecijalnaKarticka*>(karticki[i]) += pin;
            }
        }
    }

    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:\n";
        for(int i = 0; i < broj; i++) {
            if(this->karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i];
            }
        }
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) {
            delete karticki[i];
        }
    }
};

int Banka::LIMIT = DEFAULT_LIMIT;

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        try { komercijalna.dodadiDopolnitelenPin(smetka,pin); }
        catch(OutOfBoundsException& e) { e.message(); }

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
