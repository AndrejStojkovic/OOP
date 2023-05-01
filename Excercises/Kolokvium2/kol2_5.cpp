// 2 - 5

#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;

enum typeC { standard, loyal, vip };

class Customer {
    char name[50];
    char email[50];
    typeC type;
    int baseDiscount;
    int additionalDiscount;
    int items;

    void copy(const Customer& other) {
        strcpy(this->name, other.name);
        strcpy(this->email, other.email);
        this->type = other.type;
        this->baseDiscount = other.baseDiscount;
        this->items = other.items;
    }
public:
    Customer() {
        strcpy(this->name, " ");
        strcpy(this->email, " ");
        this->type = standard;
        this->baseDiscount = 10;
        this->additionalDiscount = 20;
        this->items = 0;
    }

    Customer(char* name, char* email, typeC type, int items) {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->type = type;
        this->baseDiscount = 10;
        this->additionalDiscount = 20;
        this->items = items;
    }

    Customer(const Customer& other) {
        copy(other);
    }

    Customer& operator=(const Customer& other) {
        if(this == &other) return *this;
        copy(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Customer& c) {
        out << c.name << "\n";
        out << c.email << "\n";
        out << c.items << "\n";

        switch(c.type) {
            case standard:
                out << "standard 0"; break;
            case loyal:
                out << "loyal " << c.baseDiscount; break;
            case vip:
                out << "vip " << c.baseDiscount + c.additionalDiscount; break;
        }

        out << "\n";
        return out;
    }

    char* getEmail() { return email; }
    int getItemCount() { return items; }

    typeC getType() { return type; }
    void setType(typeC type) { this->type = type; }

    void setDiscount1(int baseDiscount) { this->baseDiscount = baseDiscount; }
    void setDiscount2(int additionalDiscount) { this->additionalDiscount = additionalDiscount; }

    ~Customer() { }
};

class UserExistsException {
public:
    void message() const {
        cout << "The user already exists in the list!\n";
    }
};


class FINKI_bookstore {
    Customer* customers;
    int n;

    void copy(const FINKI_bookstore& other) {
        this->n = other.n;
        this->customers = new Customer[other.n];
        for(int i = 0; i < other.n; i++) this->customers[i] = other.customers[i];
    }
public:
    FINKI_bookstore() {
        this->n = 0;
        this->customers = new Customer[0];
    }

    FINKI_bookstore(Customer* customers, int n) {
        this->n = n;
        this->customers = new Customer[n];
        for(int i = 0; i < n; i++) this->customers[i] = customers[i];
    }

    FINKI_bookstore(const FINKI_bookstore& other) {
        copy(other);
    }

    FINKI_bookstore& operator=(const FINKI_bookstore& other) {
        if(this == &other) return *this;
        delete [] customers;
        copy(other);
        return *this;
    }

    FINKI_bookstore& operator+=(Customer& customer) {
        for(int i = 0; i < n; i++) {
            if(!strcmp(this->customers[i].getEmail(), customer.getEmail()))
                throw UserExistsException();
        }

        Customer* tmp = new Customer[n + 1];
        for(int i = 0; i < n; i++) tmp[i] = this->customers[i];
        tmp[n++] = customer;

        delete [] customers;
        this->customers = new Customer[n];
        for(int i = 0; i < n; i++) this->customers[i] = tmp[i];
        delete [] tmp;
    }

    friend ostream& operator<<(ostream& out, const FINKI_bookstore& f) {
        for(int i = 0; i < f.n; i++) {
            out << f.customers[i];
        }
        return out;
    }

    void update() {
        for(int i = 0; i < n; i++) {
            if(customers[i].getItemCount() > 5 && customers[i].getType() == standard) customers[i].setType(loyal);
            else if(customers[i].getItemCount() > 10 && customers[i].getType() == loyal) customers[i].setType(vip);
        }
    }

    void setCustomers(Customer* customers, int n) {
        this->n = n;
        this->customers = new Customer[n];
        for(int i = 0; i < n; i++) this->customers[i] = customers[i];
    }

    ~FINKI_bookstore() {
        delete [] customers;
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;

        try {
            Customer c(name, email, (typeC) tC, numProducts);
            fc+=c;
        } catch(UserExistsException &e) { e.message(); }


        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
