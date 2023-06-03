// En - 13

#include <iostream>
#include <cstring>
using namespace std;

class Pasta {
    char* name;
    float price;
    int discount;
    int calories;

    void copy_pasta(const Pasta& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->price = other.price;
        this->discount = other.discount;
        this->calories = other.calories;
    }

public:
    Pasta() {
        this->name = new char[5];
        strcpy(this->name, "name");
        this->price = 0;
        this->discount = this->calories = 0;
    }

    Pasta(char* name, float price, int calories) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->price = price;
        this->discount = 0;
        this->calories = calories;
    }

    Pasta(const Pasta& other) {
        copy_pasta(other);
    }

    Pasta& operator=(const Pasta& other) {
        if(this == &other) {
            return *this;
        }
        delete [] name;
        copy_pasta(other);
        return *this;
    }

    void print() {
        cout << name << " " << calories << " " << price;
        if(discount > 0) {
            cout << " (" << price - (price * (discount / 100.0)) << ")";
        }
    }

    void dby5() {
        if(discount < 5) {
            return;
        }
        discount -= 5;
    }

    Pasta light(int cal) {
        char* new_name = new char[strlen(name) + 10];
        strcpy(new_name, this->name);
        strcat(new_name, "Light");
        Pasta p(new_name, price - (price * 0.2), calories - cal);
        return p;
    }

    void setDiscount(int discount) {
        this->discount = discount;
    }

    void setName(char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~Pasta() {
        delete [] name;
    }
};

class ItalianRestaurant {
    char name[50];
    Pasta* arr;
    int n;

    void copy_restaurant(const ItalianRestaurant& other) {
        strcpy(this->name, other.name);
        this->arr = new Pasta[other.n];
        for(int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
        this->n = other.n;
    }

public:
    ItalianRestaurant() {
        strcpy(this->name, "name");
        this->arr = nullptr;
        this->n = 0;
    }

    ItalianRestaurant(char* name) {
        strcpy(this->name, name);
        this->arr = nullptr;
        this->n = 0;
    }

    ItalianRestaurant(const ItalianRestaurant& other) {
        copy_restaurant(other);
    }

    ItalianRestaurant& operator=(const ItalianRestaurant& other) {
        if(this == &other) {
            return *this;
        }
        delete [] arr;
        copy_restaurant(other);
        return *this;
    }

    void add(Pasta& p) {
        Pasta* tmp = new Pasta[n];
        for(int i = 0; i < n; i++) {
            tmp[i] = arr[i];
        }

        delete [] arr;
        this->arr = new Pasta[n + 1];
        for(int i = 0; i < n; i++) {
            this->arr[i] = tmp[i];
        }
        this->arr[n++] = p;
        delete [] tmp;
    }

    void print() {
        cout << name << "\n";
        for(int i = 0; i < n; i++) {
            arr[i].print();
            cout << "\n";
        }
    }

    void setPasta(int i, Pasta& p) {
        if(i < 0 || i >= n) {
            return;
        }

        arr[i] = p;
    }

    ~ItalianRestaurant() {
        delete [] arr;
    }
};

int main() {
    char name[100];
    float price;
    int discount;
    int calories;

    int testCase;

    cin >> testCase;

    if(testCase == 1) {
        cout << "====== TESTING Pasta CLASS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.setDiscount(discount);
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        Pasta c2(name, price, calories);
        c2.setDiscount(discount);
        cout << "Print" << endl;
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "Decrease by 5" << endl;
        c1.dby5();
        c1.print();
        cout << endl;
        cout << "Calories" << endl;
        int ca;
        cin >> ca;
        Pasta c3 = c1.light(ca);
        c3.print();
        cout << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING Pasta CONSTRUCTORS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.print();
        cout << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        Pasta c2(c1);
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "OPERATOR =" << endl;
        c1 = c2;
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;

    } else if(testCase == 3) {
        cout << "====== TESTING Italian Restaurant ======" << endl;
        char csName[50];
        cin >> csName;
        cout << "CONSTRUCTOR" << endl;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        cout << "Add" << endl;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        cs.print();
        cout << endl;

    } else if(testCase == 4) {
        cout << "====== TESTING Italian Restaurant CONSTRUCTORS ======" << endl;
        char csName[50];
        cin >> csName;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        Pasta x("Funghi", 260, 275);
        ItalianRestaurant cp = cs;
        cs.setPasta(0, x);
        cs.print();
        cout << endl;
        cp.print();
        cout << endl;
    }


    return 0;
}
