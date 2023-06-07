// 2 - 2

#include <iostream>
#include <cstring>
using namespace std;

class Vozac {
protected:
    char name[100];
    int age;
    int races;
    bool vet;

    void copy_vozac(const Vozac& other) {
        strcpy(this->name, other.name);
        this->age = other.age;
        this->races = other.races;
        this->vet = other.vet;
    }
public:
    Vozac() {
        strcpy(this->name, "abc");
        this->age = this->races = 0;
        this->vet = false;
    }

    Vozac(char* name, int age, int races, bool vet) {
        strcpy(this->name, name);
        this->age = age;
        this->races = races;
        this->vet = vet;
    }

    Vozac(const Vozac& other) {
        copy_vozac(other);
    }

    Vozac& operator=(const Vozac& other) {
        if(this == &other) {
            return *this;
        }
        copy_vozac(other);
        return *this;
    }

    bool operator==(const Vozac& other) {
        return this->races == other.races;
    }

    friend ostream& operator<<(ostream& out, const Vozac& v) {
        out << v.name << "\n" << v.age << "\n" << v.races << "\n";
        if(v.vet) {
            out << "VETERAN\n";
        }
        return out;
    }

    virtual float zarabotuvacka() = 0;

    virtual float danok() = 0;

    ~Vozac() { }
};

class Avtomobilist : public Vozac {
    float price;

public:
    Avtomobilist() : Vozac() {
        this->price = 0.0;
    }

    Avtomobilist(char* name, int age, int races, bool vet, float price) : Vozac(name, age, races, vet) {
        this->price = price;
    }

    Avtomobilist(const Avtomobilist& other) : Vozac(other) {
        this->price = other.price;
    }

    Avtomobilist& operator=(const Avtomobilist& other) {
        if(this == &other) return *this;
        Vozac::operator=(other);
        this->price = other.price;
        return *this;
    }

    bool operator==(Avtomobilist& other) {
        return zarabotuvacka() == other.zarabotuvacka();
    }

    float zarabotuvacka() {
        return this->price / 5.0;
    }

    float danok() {
        return races > 10 ? zarabotuvacka() * 0.15 : zarabotuvacka() * 0.1;
    }

    ~Avtomobilist() { }
};

class Motociklist : public Vozac {
    int power;

public:
    Motociklist() : Vozac() {
        this->power = 0;
    }

    Motociklist(char* name, int age, int races, bool vet, int power) : Vozac(name, age, races, vet) {
        this->power = power;
    }

    Motociklist(const Motociklist& other) {
        this->power = other.power;
    }

    Motociklist& operator=(const Motociklist& other) {
        if(this == &other) {
            return *this;
        }
        Vozac::operator=(other);
        this->power = other.power;
        return *this;
    }

    bool operator==(Motociklist& other) {
        return zarabotuvacka() == other.zarabotuvacka();
    }

    float zarabotuvacka() {
        return this->power * 20;
    }

    float danok() {
        return vet ? zarabotuvacka() * 0.25 : zarabotuvacka() * 0.2;
    }

    ~Motociklist() { }
};

int soIstaZarabotuvachka(Vozac** arr, int n, Vozac* v) {
    int ct = 0;
    for(int i = 0; i < n; i++) {
        ct += arr[i]->zarabotuvacka() == v->zarabotuvacka() ? 1 : 0;
    }
    return ct;
}

// vashiot kod ovde

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}