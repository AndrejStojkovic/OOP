// 1 - 3

#include<iostream>
#include<cstring>
using namespace std;
#define MAX 25

class StockRecord {
    char id[12];
    char company[50];
    double price;
    double newPrice;
    int shares;

    void copy_stock(const StockRecord& other) {
        strcpy(this->id, other.id);
        strcpy(this->company, other.company);
        this->price = other.price;
        this->newPrice = other.newPrice;
        this->shares = other.shares;
    }

public:
    StockRecord() {
        strcpy(this->id, " ");
        strcpy(this->company, " ");
        this->price = this->newPrice = this->shares = 0;
    }

    StockRecord(char* id, char* company, double price, int shares) {
        strcpy(this->id, id);
        strcpy(this->company, company);
        this->price = price;
        this->shares = shares;
    }

    StockRecord(const StockRecord& other) {
        copy_stock(other);
    }

    StockRecord& operator=(const StockRecord& other) {
        if(this == &other) {
            return *this;
        }
        copy_stock(other);
        return *this;
    }

    friend ostream& operator<<(ostream& os, const StockRecord& s) {
        os << s.company << " " << s.shares << " " << s.price << " " << s.newPrice << " " << s.profit() << "\n";
        return os;
    }

    void setNewPrice(double newPrice) {
        this->newPrice = newPrice;
    }

    double value() const {
        return shares * newPrice;
    }

    double profit() const {
        return shares * (newPrice - price);
    }

    ~StockRecord() { }
};

class Client {
    char name[60];
    int id;
    StockRecord* companies;
    int len;

    void copy_client(const Client& other) {
        strcpy(this->name, other.name);
        this->id = other.id;
        this->companies = new StockRecord[other.len];
        for(int i = 0; i < other.len; i++) {
            this->companies[i] = other.companies[i];
        }
        this->len = other.len;
    }

public:
    Client() {
        strcpy(this->name, " ");
        this->companies = new StockRecord[0];
        this->id = this->len = 0;
    }

    Client(char* name, int id) {
        strcpy(this->name, name);
        this->id = id;
        this->companies = new StockRecord[0];
        this->len = 0;
    }

    Client(const Client& other) {
        copy_client(other);
    }

    Client& operator=(const Client& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->companies;
        copy_client(other);
        return *this;
    }

    Client& operator+=(const StockRecord& that) {
        StockRecord* tmp = new StockRecord[len + 1];
        for(int i = 0; i < len; i++) {
            tmp[i] = this->companies[i];
        }
        tmp[len++] = that;

        delete [] companies;
        this->companies = new StockRecord[len];
        for(int i = 0; i < len; i++) {
            this->companies[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }

    friend ostream& operator<<(ostream& os, const Client& c) {
        os << c.id << " " << c.totalValue() << "\n";
        for(int i = 0; i < c.len; i++) {
            os << c.companies[i];
        }
        return os;
    }

    double totalValue() const {
        double s = 0;
        for(int i = 0; i < len; i++) {
            s += companies[i].value();
        }
        return s;
    }

    ~Client() {
        delete [] companies;
    }
};

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}