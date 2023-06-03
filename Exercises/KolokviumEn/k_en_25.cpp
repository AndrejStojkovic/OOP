// En - 25

#include <iostream>
#include <cstring>
using namespace std;

class Tickets {
protected:
    int id[12];
    char event[100];
    float basePrice;
    static int discount;

private:
    void copy_tickets(const Tickets& other) {
        for(int i = 0; i < 12; i++) {
            this->id[i] = other.id[i];
        }
        strcpy(this->event, other.event);
        this->basePrice = other.basePrice;
    }

public:
    Tickets() {
        for(int i = 0; i < 12; i++) {
            this->id[i] = 0;
        }
        strcpy(this->event, "event");
        this->basePrice = 0;
    }

    Tickets(int* id, char* event, float basePrice) {
        for(int i = 0; i < 12; i++) {
            this->id[i] = id[i];
        }
        strcpy(this->event, event);
        this->basePrice = basePrice;
    }

    Tickets(const Tickets& other) {
        copy_tickets(other);
    }

    Tickets& operator=(const Tickets& other) {
        if(this == &other) {
            return *this;
        }
        copy_tickets(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Tickets& t) {
        for(int i = 0; i < 12; i++) {
            out << t.id[i];
        }
        out << "-" << t.event << "-" << t.presmetajCena();
        return out;
    }

    static void changeDiscount(int _discount) {
        discount = _discount;
    }

    virtual float presmetajCena() {
        return basePrice;
    }

    bool falsifikat(int from, int to) {
        int s = (id[8] * 1000) + (id[9] * 100) + (id[10] * 10) + id[11];
        return from <= s && s <= to;
    }

    ~Tickets() { }
};

class Online : public Tickets {
    bool premium;

public:
    Online() : Tickets() {
        this->premium = false;
    }

    Online(int* id, char* event, float basePrice, bool premium) : Tickets(id, event, basePrice) {
        this->premium = premium;
    }

    Online(const Online& other) : Tickets(other) {
        this->premium = other.premium;
    }

    Online& operator=(const Online& other) {
        if(this == &other) {
            return *this;
        }
        Tickets::operator=(other);
        this->premium = other.premium;
        return *this;
    }

    float presmetajCena() {
        float s = basePrice;

        if(premium) {
            s -= (basePrice * 0.15);
        }

        if(discount > 0) {
            s -= basePrice * (discount / 100.0);
        }

        return s;
    }

    ~Online() { }
};

class Offline : public Tickets {
    bool reservation;

public:
    Offline() : Tickets() {
        this->reservation = false;
    }

    Offline(int* id, char* event, float basePrice, bool reservation) : Tickets(id, event, basePrice) {
        this->reservation = reservation;
    }

    Offline(const Offline& other) : Tickets(other) {
        this->reservation = other.reservation;
    }

    Offline& operator=(const Offline& other) {
        if(this == &other) {
            return *this;
        }
        Tickets::operator=(other);
        this->reservation = other.reservation;
        return *this;
    }

    float presmetajCena() {
        float s = basePrice;

        if(reservation) {
            s += basePrice * 0.1;
        }

        if(discount > 0) {
            s -= basePrice * (discount / 100.0);
        }

        return s;
    }

    ~Offline() { }
};

int Tickets::discount = 0;

void vkupenPrihod(Tickets** t, int n, int from, int to) {
    float s = 0;
    for(int i = 0; i < n; i++) {
        if(t[i]->falsifikat(from, to)) {
            if(dynamic_cast<Online*>(t[i])) {
                s += dynamic_cast<Online*>(t[i])->presmetajCena();
            } else if(dynamic_cast<Offline*>(t[i])) {
                s += dynamic_cast<Offline*>(t[i])->presmetajCena();
            }
        }
    }
    cout << s;
}

int main() {
    int testCase;
    cin >> testCase;
    int ID[12];
    char nastan[100];
    float price;
    bool premium;
    bool rezervacija;
    int od, doo;

    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> premium;
        Online o1(ID, nastan, price, premium);
        cout << o1 << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> rezervacija;
        Offline o2(ID, nastan, price, rezervacija);
        cout << o2 << endl;

    }
    else if (testCase == 2) {
        cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
        int n;
        cin >> n;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; j++)
                cin >> ID[j];
            cin >> nastan;
            cin >> price;

            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        cin >> od;
        cin >> doo;
        vkupenPrihod(t, n, od, doo);
        for (int i = 0; i < n; ++i) {
            delete t[i];
        }
        delete[] t;
    }
    else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        //cout<<n<<endl;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; ++j)
                cin >> ID[j];
            cin >> nastan;
            //cout<<nastan<<endl;
            cin >> price;
            //cout<<price<<endl;
            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                //cout<<rezervacija<<endl;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        int d;
        cin >> d;
        Tickets::changeDiscount(d);
        for (int i = 0; i < n; ++i)
            cout << *t[i] << endl;

    }
}