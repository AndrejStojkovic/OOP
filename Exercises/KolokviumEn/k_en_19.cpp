// En - 19

#include <iostream>
#include <cstring>
using namespace std;

class Parcel {
protected:
    int id;
    static int price;

public:
    Parcel() {
        this->id = 0;
    }

    Parcel(int id) {
        this->id = id;
    }

    Parcel(const Parcel& other) {
        this->id = other.id;
    }

    Parcel& operator=(const Parcel& other) {
        if(this == &other) {
            return *this;
        }
        this->id = other.id;
        return *this;
    }

    static void setProcessingPrice(int p) {
        price = p;
    }

    int getId() {
        return id;
    }

    ~Parcel() { }
};

class Envelope : public Parcel {
    int width;
    int height;
    char receiver[50];

    void copy_envelope(const Envelope& other) {
        this->width = other.width;
        this->height = other.height;
        strcpy(this->receiver, other.receiver);
    }

public:
    Envelope() : Parcel() {
        this->width = this->height = 0;
        strcpy(this->receiver, "receiver");
    }

    Envelope(int id, char* receiver, int width, int height) : Parcel(id) {
        this->width = width;
        this->height = height;
        strcpy(this->receiver, receiver);
    }

    Envelope(const Envelope& other) : Parcel(other) {
        copy_envelope(other);
    }

    Envelope& operator=(const Envelope& other) {
        if(this == &other) {
            return *this;
        }
        Parcel::operator=(other);
        copy_envelope(other);
        return *this;
    }

    int price() {
        return Parcel::price + width * height * 0.3;
    }

    char* getReceiver() {
        return receiver;
    }

    ~Envelope() { }
};

class PostOffice {
    Envelope e[100];
    int n;

    void copy(const PostOffice& other) {
        for(int i = 0; i < other.n; i++) {
            this->e[i] = other.e[i];
        }
        this->n = other.n;
    }

public:
    PostOffice() {
        this->n = 0;
    }

    PostOffice(const PostOffice& other) {
        copy(other);
    }

    PostOffice& operator=(const PostOffice& other) {
        if(this == &other) {
            return *this;
        }
        copy(other);
        return *this;
    }

    int sendEnvelope(int id, char* receiver, int width, int height) {
        e[n++] = Envelope(id, receiver, width, height);
        return e[n - 1].price();
    }


    void printEnvelopsTo(char* receiver) {
        cout << "For " << receiver << " are envelops with ids: ";
        for(int i = 0; i < n; i++) {
            if(!strcmp(receiver, e[i].getReceiver())) {
                cout << e[i].getId() << " ";
            }
        }
        cout << "\n";
    }

    ~PostOffice() { }
};

int Parcel::price = 150;

int main() {
    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << p2.price() << endl;
        }
    }
    return 0;
}