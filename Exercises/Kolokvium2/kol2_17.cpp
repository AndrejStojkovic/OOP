// 2 - 17

#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa {
protected:
    char coach[100];
    int goals[10];

private:
    void copy_ekipa(const FudbalskaEkipa& other) {
        strcpy(this->coach, other.coach);
        for(int i = 0; i < 10; i++) this->goals[i] = other.goals[i];
    }
    
public:
    FudbalskaEkipa() {
        strcpy(this->coach, "abc");
        for(int i = 0; i < 10; i++) this->goals[i] = 0;
    }

    FudbalskaEkipa(char* coach, int* goals) {
        strcpy(this->coach, coach);
        for(int i = 0; i < 10; i++) this->goals[i] = goals[i];
    }

    FudbalskaEkipa(const FudbalskaEkipa& other) {
        copy_ekipa(other);
    }

    FudbalskaEkipa& operator=(const FudbalskaEkipa& other) {
        if(this == &other) return *this;
        copy_ekipa(other);
        return *this;
    }

    FudbalskaEkipa& operator+=(int lastMatchGoals) {
        for(int i = 0; i < 9; i++) this->goals[i] = this->goals[i + 1];
        this->goals[9] = lastMatchGoals;
    }

    bool operator>(FudbalskaEkipa& other) {
        return uspeh() > other.uspeh();
    }

    int getTotalGoals() {
        int s = 0;
        for(int i = 0; i < 10; i++) s += goals[i];
        return s;
    }

    virtual int uspeh() = 0;

    char* getCoach() { return coach; }
    void setCoach(char* coach) { strcpy(this->coach, coach); }

    int* getGoals() { return goals; }
    void setGoals(int* goals) { for(int i = 0; i < 10; i++) this->goals[i] = goals[i]; }

    ~FudbalskaEkipa() { }
};

class Klub : public FudbalskaEkipa {
    char* name;
    int titles;

    void copy_klub(const Klub& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->titles = other.titles;
    }

public:
    Klub() : FudbalskaEkipa() {
        this->name = new char[0];
        this->titles = 0;
    }

    Klub(char* coach, int* goals, char* name, int titles) : FudbalskaEkipa(coach, goals) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->titles = titles;
    }

    Klub(const FudbalskaEkipa& f, char* name, int titles) : FudbalskaEkipa(f) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->titles = titles;
    }

    Klub(const Klub& other) {
        copy_klub(other);
    }

    Klub& operator=(const Klub& other) {
        if(this == &other) return *this;
        FudbalskaEkipa::operator=(other);
        copy_klub(other);
        return *this;
    }

    int uspeh() { return getTotalGoals() * 3 + titles * 1000; }

    char* getName() { return name; }

    ~Klub() {
        delete [] name;
    }
};

class Reprezentacija : public FudbalskaEkipa {
    char* country;
    int matches;

    void copy_reprezentacija(const Reprezentacija& other) {
        this->country = new char[strlen(other.country) + 1];
        strcpy(this->country, other.country);
        this->matches = other.matches;
    }

public:
    Reprezentacija() : FudbalskaEkipa() {
        this->country = new char[0];
        this->matches = 0;
    }

    Reprezentacija(char* coach, int* goals, char* country, int matches) : FudbalskaEkipa(coach, goals) {
        this->country = new char[strlen(country) + 1];
        strcpy(this->country, country);
        this->matches = matches;
    }

    Reprezentacija(const FudbalskaEkipa& f, char* country, int matches) : FudbalskaEkipa(f) {
        this->country = new char[strlen(country) + 1];
        strcpy(this->country, country);
        this->matches = matches;
    }

    Reprezentacija(const Reprezentacija& other) {
        copy_reprezentacija(other);
    }

    Reprezentacija& operator=(const Reprezentacija& other) {
        if(this == &other) return *this;
        FudbalskaEkipa::operator=(other);
        copy_reprezentacija(other);
        return *this;
    }

    int uspeh() { return getTotalGoals() * 3 + matches * 50; }

    char* getCountry() { return country; }

    ~Reprezentacija() {
        delete [] country;
    }
};

ostream& operator<<(ostream& out, FudbalskaEkipa& k) {
    if(dynamic_cast<Klub*>(&k)) out << dynamic_cast<Klub*>(&k)->getName();
    else if(dynamic_cast<Reprezentacija*>(&k)) out << dynamic_cast<Reprezentacija*>(&k)->getCountry();
    out << "\n" << k.getCoach() << "\n" << k.uspeh() << "\n";
    return out;
}

void najdobarTrener(FudbalskaEkipa** ekipi, int n) {
    int idx = 0;
    for(int i = 0; i < n; i++) if(ekipi[i]->uspeh() > ekipi[idx]->uspeh()) idx = i;
    cout << *ekipi[idx];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}