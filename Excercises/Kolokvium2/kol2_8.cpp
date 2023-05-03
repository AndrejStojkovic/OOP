// 2 - 8

#include <iostream>
#include <cstring>
using namespace std;

class Koncert {
protected:
    char name[20];
    char location[20];
    static double discount;
    double price;

    void copy(const Koncert& other) {
        strcpy(this->name, other.name);
        strcpy(this->location, other.location);
        this->price = other.price;
    }
public:
    Koncert() {
        strcpy(this->name, "abc");
        strcpy(this->location, "abc");
        this->price = 0.0;
    }

    Koncert(char* name, char* location, double price) {
        strcpy(this->name, name);
        strcpy(this->location, location);
        this->price = price;
    }

    Koncert(const Koncert& other) {
        copy(other);
    }

    Koncert& operator=(const Koncert& other) {
        if(this == &other) return *this;
        copy(other);
        return *this;
    }

    virtual double cena() { return price * (1.0 - discount); }

    char* getNaziv() { return name; }
    void setName(char* name) { strcpy(this->name, name); }

    char* getLocation() { return location; }
    void setLocation(char* location) { strcpy(this->location, location); }

    double getSezonskiPopust() { return discount; }
    void setSezonskiPopust(double _discount) { discount = _discount; }

    double getPrice() { return price; }
    void setPrice(double price) { this->price = price; }

    ~Koncert() { }
};

class ElektronskiKoncert : public Koncert {
    char* dj;
    float hours;
    bool time; // false - night, true - day

public:
    ElektronskiKoncert() : Koncert() {
        this->dj = new char[0];
        this->hours = 0.0;
        this->time = false;
    }

    ElektronskiKoncert(char* name, char* location, double price, char* dj, float hours, bool time) : Koncert(name, location, price) {
        this->dj = new char[strlen(dj) + 1];
        strcpy(this->dj, dj);
        this->hours = hours;
        this->time = time;
    }

    ElektronskiKoncert(const ElektronskiKoncert& other) : Koncert(other) {
        this->dj = new char[strlen(other.dj) + 1];
        strcpy(this->dj, other.dj);
        this->hours = other.hours;
        this->time = other.time;
    }

    ElektronskiKoncert& operator=(const ElektronskiKoncert& other) {
        if(this == &other) return *this;
        copy(other);
        delete [] dj;
        this->dj = new char[strlen(other.dj) + 1];
        strcpy(this->dj, other.dj);
        this->hours = other.hours;
        this->time = other.time;
        return *this;
    }

    double cena() {
        int s = 0;

        if(hours > 7) s += 360;
        else if(hours > 5) s += 150;

        if(time) s -= 50;
        else s += 100;

        return price * (1.0 - discount) + s;
    }

    ~ElektronskiKoncert() {
        delete [] dj;
    }
};

double Koncert::discount = 0.2;

void najskapKoncert(Koncert** koncerti, int n) {
    int idx = 0, counter = 0;

    for(int i = 0; i < n; i++) {
        if(koncerti[i]->cena() > koncerti[idx]->cena()) idx = i;
        if(dynamic_cast<ElektronskiKoncert*>(koncerti[i])) counter++;
    }

    cout << "Najskap koncert: " << koncerti[idx]->getNaziv() << " " << koncerti[idx]->cena() << "\n";
    cout << "Elektronski koncerti: " << counter << " od vkupno " << n << "\n";
}

bool prebarajKoncert(Koncert** koncerti, int n, char* naziv, bool elektronski) {
    for(int i = 0; i < n; i++) {
        if(!elektronski || dynamic_cast<ElektronskiKoncert*>(koncerti[i])) {
            if(!strcmp(koncerti[i]->getNaziv(), naziv)) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << "\n";
                return true;
            }
        }
    }

    return false;
}

int main()
{

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1)
    {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    }
    else if (tip == 2)
    {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    }
    else if (tip == 3)
    {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust "
             << s.getSezonskiPopust() << endl;
    }
    else if (tip == 4)
    {//cena - ElektronskiKonceFrt
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    }
    else if (tip == 5)
    {//najskapKoncert

    }
    else if (tip == 6)
    {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    }
    else if (tip == 7)
    {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

    }
    else if (tip == 8)
    {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
