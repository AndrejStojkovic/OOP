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

public:
    StockRecord() {
        strcpy(this->id, " ");
        strcpy(this->company, " ");
        price = newPrice = shares = 0;
    }

    StockRecord(char* id, char* company, double price, int shares) {
        strcpy(this->id, id);
        strcpy(this->company, company);
        this->price = price;
        this->shares = shares;
    }

    StockRecord(const StockRecord& s) {
        strcpy(this->id, s.id);
        strcpy(this->company, s.company);
        this->price = s.price;
        this->newPrice = s.newPrice;
        this->shares = s.shares;
    }

    StockRecord& operator=(const StockRecord& that) {
        if(this == &that) return *this;

        strcpy(this->id, that.id);
        strcpy(this->company, that.company);
        this->price = that.price;
        this->newPrice = that.newPrice;
        this->shares = that.shares;

        return *this;
    }

    friend ostream& operator<<(ostream& os, const StockRecord& s) {
        os << s.company << " " << s.shares << " " << s.price << " " << s.newPrice << " " << s.profit() << "\n";
        return os;
    }

    char* getID() {
        return id;
    }

    void setID(char* id) {
        strcpy(this->id, id);
    }

    char* getCompany() {
        return company;
    }

    void setCompany(char* company) {
        strcpy(this->company, company);
    }

    double getPrice() {
        return price;
    }

    void setPrice(double price) {
        this->price = price;
    }

    double getNewPrice() {
        return newPrice;
    }

    void setNewPrice(double newPrice) {
        this->newPrice = newPrice;
    }

    int getShares() {
        return shares;
    }

    void setShares(int shares) {
        this->shares = shares;
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

public:
    Client() {
        strcpy(this->name, " ");
        companies = new StockRecord[MAX];
        id = len = 0;
    }

    Client(char* name, int id) {
        strcpy(this->name, name);
        this->id = id;
        this->companies = new StockRecord[MAX];
        this->len = 0;
    }

    Client(const Client& c) {
        strcpy(this->name, c.name);
        this->id = c.id;
        for(int i = 0; i < c.len; i++)
            this->companies[i] = c.companies[i];
        this->len = c.len;
    }

    Client& operator=(const Client& that) {
        if(this == &that) return *this;

        strcpy(this->name, that.name);
        this->id = that.id;
        for(int i = 0; i < that.len; i++)
            this->companies[i] = that.companies[i];
        this->len = that.len;

        return *this;
    }

    Client& operator+=(const StockRecord& that) {
        this->companies[len++] = that;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Client& c) {
        os << c.id << " " << c.totalValue() << "\n";
        for(int i = 0; i < c.len; i++) {
            os << c.companies[i];
        }
        return os;
    }

    /*
     * char name[60];
    int id;
    StockRecord* companies;
    int len;
     */

    char* getName() {
        return name;
    }

    void setName(char* name) {
        strcpy(this->name, name);
    }

    int getID() {
        return id;
    }

    void setID(int id) {
        this->id = id;
    }

    StockRecord* getCompanies() {
        return companies;
    }

    void setCompanies(StockRecord* companies) {
        this->companies = companies;
    }

    int getLen() {
        return len;
    }

    void setLen(int len) {
        this->len = len;
    }

    double totalValue() const {
        double s = 0;
        for(int i = 0; i < len; i++) s += companies[i].value();
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