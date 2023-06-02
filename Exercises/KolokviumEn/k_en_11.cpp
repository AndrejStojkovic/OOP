// En - 11

#include <iostream>
#include <cstring>
using namespace std;

class InvalidDiscount {
    int discount;

public:
    InvalidDiscount(int discount) {
        this->discount = discount;
    }

    void message() {
        cout << "Invalid discount value: " << discount << "\n";
    }
};

class IceCream {
    char* name;
    char ingr[100];
    float price;
    int discount;

public:
    IceCream() {
        this->name = new char[2];
        strcpy(this->name, " ");
        strcpy(this->ingr, " ");
        this->price = 0;
        this->discount = 0;
    }

    IceCream(char* name, char* ingr, float price, int discount=0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingr, ingr);
        this->price = price;
        this->discount = discount;
    }

    IceCream(const IceCream& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->ingr, other.ingr);
        this->price = other.price;
        this->discount = other.discount;
    }

    IceCream& operator=(const IceCream& other) {
        if(this == &other) return *this;

        delete [] this->name;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->ingr, other.ingr);
        this->price = other.price;
        this->discount = other.discount;

        return *this;
    }

    friend ostream& operator<<(ostream& os, const IceCream& obj) {
        os << obj.name << ": " << obj.ingr << " " << obj.price << " ";
        if(obj.discount != 0)
            os << "(" << obj.price - ((obj.discount / 100.0) * obj.price) << ")";
        return os;
    }

    IceCream& operator++() {
        discount += 5;
        return *this;
    }

    IceCream operator+(const char* add) {
        char* tmp = new char[strlen(name) + strlen(add) + 1];
        strcat(tmp, name);
        strcat(tmp, " + ");
        strcat(tmp, add);
        strcpy(this->name, tmp);
        price += 10;
        return *this;
    }

    void setName(char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void setDiscount(int discount) {
        if(discount < 0 || discount > 100) {
            throw InvalidDiscount(discount);
        }
        this->discount = discount;
    }

    ~IceCream() {
        delete [] name;
    }
};

class IceCreamShop {
    char name[50];
    IceCream* iceCreams;
    int num;

public:
    IceCreamShop() {
        strcpy(this->name, " ");
        iceCreams = new IceCream[0];
        this->num = 0;
    }

    IceCreamShop(char* name) {
        strcpy(this->name, name);
        iceCreams = new IceCream[0];
        this->num = 0;
    }

    IceCreamShop(char* name, int num) {
        strcpy(this->name, name);
        iceCreams = new IceCream[num];
        this->num = num;
    }

    IceCreamShop(const IceCreamShop& other) {
        strcpy(this->name, other.name);
        iceCreams = new IceCream[other.num];
        for(int i = 0; i < other.num; i++) this->iceCreams[i] = other.iceCreams[i];
        this->num = other.num;
    }

    IceCreamShop& operator=(const IceCreamShop& other) {
        if(this == &other) return *this;

        strcpy(this->name, other.name);
        delete [] this->iceCreams;
        this->iceCreams = new IceCream[other.num];
        for(int i = 0; i < other.num; i++) this->iceCreams[i] = other.iceCreams[i];
        this->num = other.num;

        return *this;
    }

    IceCreamShop& operator+=(const IceCream& obj) {
        IceCream* tmp = new IceCream[num + 1];
        for(int i = 0; i < num; i++) tmp[i] = this->iceCreams[i];
        tmp[num++] = obj;

        delete [] iceCreams;
        iceCreams = new IceCream[num];
        for(int i = 0; i < num; i++) iceCreams[i] = tmp[i];

        return *this;
    }

    friend ostream& operator<<(ostream& os, const IceCreamShop& obj) {
        os << obj.name << "\n";
        for(int i = 0; i < obj.num; i++) os << obj.iceCreams[i] << "\n";
        return os;
    }

    ~IceCreamShop() {
        delete [] iceCreams;
    }
};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR &lt;&lt;" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "TESTING EXCEPTION" << endl;

        // your exception handling code

        cin >> discount;

        try {
            ic1.setDiscount(discount);
        } catch(InvalidDiscount& e) {
            e.message();
        }

    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}

