// 2 - 16

#include <iostream>
#include <cstring>
using namespace std;

class Transport {
protected:
    char* destination;
    int price;
    int km;

    void copy(const Transport& other) {
        this->destination = new char[strlen(other.destination) + 1];
        strcpy(this->destination, other.destination);
        this->price = other.price;
        this->km = other.km;
    }

public:
    Transport() {
        this->destination = new char[0];
        this->price = this->km = 0;
    }

    Transport(char* destination, int price, int km) {
        this->destination = new char[strlen(destination) + 1];
        strcpy(this->destination, destination);
        this->price = price;
        this->km = km;
    }

    Transport(const Transport& other) {
        copy(other);
    }

    Transport& operator=(const Transport& other) {
        if(this == &other) return *this;
        delete [] destination;
        copy(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Transport& t) {
        out << t.destination << " " << t.km << " " << t.price << "\n";
        return out;
    }

    bool operator<(const Transport& other) {
        return km < other.km;
    }

    virtual float cenaTransport() {
        return price;
    }

    char* getDestination() { return destination; }
    void setDestination(char* destination) {
        this->destination = new char[strlen(destination) + 1];
        strcpy(this->destination, destination);
    }

    int getPrice() { return price; }
    void setPrice(int price) { this->price = price; }

    int getKM() { return km; }
    void setKM(int km) { this->km = km; }

    ~Transport() {
        delete [] destination;
    }
};

class AvtomobilTransport : public Transport {
    bool driver;

public:
    AvtomobilTransport() : Transport() {
        this->driver = false;
    }

    AvtomobilTransport(char* destination, int price, int km, bool driver) : Transport(destination, price, km) {
        this->driver = driver;
    }

    AvtomobilTransport(const AvtomobilTransport& other) : Transport(other) {
        this->driver = other.driver;
    }

    AvtomobilTransport& operator=(const AvtomobilTransport& other) {
        if(this == &other) return *this;
        delete [] destination;
        copy(other);
        this->driver = other.driver;
        return *this;
    }

    float cenaTransport() { return driver ? price * 1.2 : price; }

    bool getDriver() { return driver; }
    void setDriver(bool driver) { this->driver = driver; }

    ~AvtomobilTransport() { }
};

class KombeTransport : public Transport {
    int passengers;

public:
    KombeTransport() : Transport() {
        this->passengers = 0;
    }

    KombeTransport(char* destination, int price, int km, int passengers) : Transport(destination, price, km) {
        this->passengers = passengers;
    }

    KombeTransport(const KombeTransport& other) : Transport(other) {
        this->passengers = other.passengers;
    }

    KombeTransport& operator=(const KombeTransport& other) {
        if(this == &other) return *this;
        delete [] destination;
        copy(other);
        this->passengers;
        return *this;
    }

    float cenaTransport() { return price - (passengers * 200); }

    int getPassengers() { return passengers; }
    void setPassengers(int passengers) { this->passengers = passengers; }

    ~KombeTransport() { }
};

void pecatiPoloshiPonudi(Transport** ponudi, int n, AvtomobilTransport t) {
    Transport** tmp = new Transport*[n];
    int k = 0;

    for(int i = 0; i < n; i++) {
        if(ponudi[i]->cenaTransport() > t.cenaTransport()) {
            tmp[k++] = ponudi[i];
        }
    }

    for(int i = 0; i < k - 1; i++) {
        for(int j = 0; j < k - i - 1; j++) {
            if(tmp[j]->getKM() > tmp[j + 1]->getKM()) {
                Transport* temp = tmp[j];
                tmp[j] = tmp[j + 1];
                tmp[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < k; i++) {
        cout << tmp[i]->getDestination() << " " << tmp[i]->getKM() << " " << tmp[i]->cenaTransport() << "\n";
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
