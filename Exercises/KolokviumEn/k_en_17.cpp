// En - 17

#include <iostream>
#include <cstring>
using namespace std;

class Piano {
    char serial[25];
    float price;
    int year;

    void copy_piano(const Piano& other) {
        strcpy(this->serial, other.serial);
        this->price = other.price;
        this->year = other.year;
    }

public:
    Piano() {
        strcpy(this->serial, "serial");
        this->price = 0;
        this->year = 0;
    }

    Piano(char* serial) {
        strcpy(this->serial, serial);
        this->price = 0;
        this->year = 0;
    }

    Piano(char* serial, float price, int year) {
        strcpy(this->serial, serial);
        this->price = price;
        this->year = year;
    }

    Piano(const Piano& other) {
        copy_piano(other);
    }

    Piano& operator=(const Piano& other) {
        if(this == &other) {
            return *this;
        }
        copy_piano(other);
        return *this;
    }

    bool equals(const Piano& p) {
        return !strcmp(serial, p.serial);
    }

    void print() {
        cout << serial << " " << year << " " << price << "\n";
    }

    char* getSerial() {
        return serial;
    }

    void setSerial(char* serial) {
        strcpy(this->serial, serial);
    }

    float getPrice() {
        return price;
    }

    ~Piano() { }
};

class PShop {
    char name[50];
    Piano* arr;
    int n;

    void copy_shop(const PShop& other) {
        strcpy(this->name, other.name);
        this->arr = new Piano[other.n];
        for(int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
        this->n = other.n;
    }

public:
    PShop() {
        strcpy(this->name, "name");
        this->arr = nullptr;
        this->n = 0;
    }

    PShop(char* name) {
        strcpy(this->name, name);
        this->arr = nullptr;
        this->n = 0;
    }

    PShop(const PShop& other) {
        copy_shop(other);
    }

    PShop& operator=(const PShop& other) {
        if(this == &other) {
            return *this;
        }
        delete [] arr;
        copy_shop(other);
        return *this;
    }

    double value() {
        double s = 0;
        for(int i = 0; i < n; i++) {
            s += arr[i].getPrice();
        }
        return s;
    }

    void add(Piano p) {
        Piano* tmp = new Piano[n + 1];
        for(int i = 0; i < n; i++) {
            tmp[i] = arr[i];
        }
        tmp[n++] = p;

        delete [] arr;
        this->arr = new Piano[n];
        for(int i = 0; i < n; i++) {
            this->arr[i] = tmp[i];
        }
        delete [] tmp;
    }

    void sell(Piano p) {
        int ct = 0;

        for(int i = 0; i < n; i++) {
            if(p.equals(arr[i])) {
                ct++;
            }
        }

        if(ct <= 0) {
            return;
        }

        Piano* tmp = new Piano[n - ct];

        int curr = 0;
        for(int i = 0; i < n; i++) {
            if(p.equals(arr[i])) {
                continue;
            }
            tmp[curr++] = arr[i];
        }

        delete [] arr;
        this->arr = new Piano[curr];
        for(int i = 0; i < curr; i++) {
            this->arr[i] = tmp[i];
        }
        this->n = curr;
        delete [] tmp;
    }

    void print() {
        cout << name << "\n";
        for(int i = 0; i < n; i++) {
            cout << (i + 1) << ". ";
            arr[i].print();
        }
    }

    Piano getP(int idx) {
        if(idx < 0 || idx >= n) {
            return Piano();
        }

        return arr[idx];
    }

    ~PShop() {
        delete [] arr;
    }
};

int main() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << "---Class Piano---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p(serialNo,price,pYear);
        p.print();
    } else if(n == 2) {
        cout << "---Equals---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        Piano p2(p1);
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
        p2.setSerial("12344");
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
    }  else if(n == 3) {
        cout << "---Class PShop---" << endl;
        char name[50];
        cin >> name;
        PShop ps(name);
        ps.print();
    } else if(n == 4) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();
    } else if(n == 5) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

    } else if(n == 6) {
        cout << "---value method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        cout<<"Total price: "<<ps.value()<<endl;
    }
    else if(n == 7) {
        cout << "---sell method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        int d;
        cin>>d;
        Piano p1(ps.getP(d).getSerial());
        ps.sell(p1);
        ps.print();
    } else if(n == 8) {
        cout << "---Full Test---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();

        cout<<endl;

        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

        cout<<endl;

        cout<<"Total price: "<<ps.value()<<endl;

        cout<<endl;

        int d;
        cin>>d;
        Piano p3(ps.getP(d).getSerial());
        ps.sell(p3);
        ps.print();

        cout<<"Total price: "<<ps.value()<<endl;
    }
    return 0;
}
