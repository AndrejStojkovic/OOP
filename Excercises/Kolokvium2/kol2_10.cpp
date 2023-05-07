// 2 - 10

#include <iostream>
#include <cstring>
using namespace std;

class NegativnaVrednost {
public: void message() { cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!\n"; }
};

class Oglas {
    char title[50];
    char category[30];
    char description[100];
    float price;

    void copy_oglas(const Oglas& other) {
        strcpy(this->title, other.title);
        strcpy(this->category, other.category);
        strcpy(this->description, other.description);
        this->price = other.price;
    }
public:
    Oglas() {
        strcpy(this->title, "title");
        strcpy(this->category, "category");
        strcpy(this->description, "description");
        this->price = 0.0;
    }

    Oglas(char* title, char* category, char* description, float price) {
        strcpy(this->title, title);
        strcpy(this->category, category);
        strcpy(this->description, description);
        this->price = price;
    }

    Oglas(const Oglas& other) {
        copy_oglas(other);
    }

    Oglas& operator=(const Oglas& other) {
        if(this == &other) return *this;
        copy_oglas(other);
        return *this;
    }

    bool operator>(const Oglas& other) {
        return price > other.price;
    }

    friend ostream& operator<<(ostream& out, Oglas& other) {
        out << other.title << "\n" << other.description << "\n" << other.price << " evra\n";
        return out;
    }

    char* getNaslov() { return title; }
    void setNaslov(char* title) { strcpy(this->title, title); }

    char* getKategorija() { return category; }
    void setKategorija(char* category) { strcpy(this->category, category); }

    char* getOpis() { return description; }
    void setOpis(char* description) { strcpy(this->description, description); }

    float getCena() { return price; }
    void setCena(float price) { this->price = price; }

    ~Oglas() { }
};

class Oglasnik {
    char name[20];
    Oglas* oglasi;
    int n;

    void copy_oglasnik(const Oglasnik& other) {
        strcpy(this->name, other.name);
        this->oglasi = new Oglas[other.n];
        for(int i = 0; i < n; i++) this->oglasi[i] = other.oglasi[i];
        this->n = other.n;
    }
public:
    Oglasnik() {
        strcpy(this->name, "name");
        this->oglasi = new Oglas[0];
        this->n = 0;
    }

    Oglasnik(char* name) {
        strcpy(this->name, name);
        this->oglasi = new Oglas[0];
        this->n = 0;
    }

    Oglasnik(char* name, Oglas* oglasi, int n) {
        strcpy(this->name, name);
        this->oglasi = new Oglas[n];
        for(int i = 0; i < n; i++) this->oglasi[i] = oglasi[i];
        this->n = n;
    }

    Oglasnik(const Oglasnik& other) {
        copy_oglasnik(other);
    }

    Oglasnik& operator=(const Oglasnik& other) {
        if(this == &other) return *this;
        delete [] oglasi;
        copy_oglasnik(other);
        return *this;
    }

    Oglasnik& operator+=(Oglas& oglas) {
        if(oglas.getCena() < 0) throw NegativnaVrednost();

        Oglas* tmp = new Oglas[n + 1];
        for(int i = 0; i < n; i++) tmp[i] = oglasi[i];
        tmp[n++] = oglas;

        delete [] oglasi;
        this->oglasi = new Oglas[n];
        for(int i = 0; i < n; i++) this->oglasi[i] = tmp[i];
        delete [] tmp;
    }

    friend ostream& operator<<(ostream& out, const Oglasnik& o) {
        out << o.name << "\n";
        for(int i = 0; i < o.n; i++) out << o.oglasi[i]<< "\n";
        return out;
    }

    void oglasiOdKategorija(char* k) {
        for(int i = 0; i < n; i++) {
            if(!strcmp(oglasi[i].getKategorija(), k)) cout << oglasi[i] << "\n";
        }
    }

    void najniskaCena() {
        int idx = 0;
        for(int i = 0; i < n; i++) {
            if(oglasi[i].getCena() < oglasi[idx].getCena()) idx = i;
        }

        cout << oglasi[idx] << "\n";
    }

    ~Oglasnik() {
        delete [] oglasi;
    }
};

int main(){
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
