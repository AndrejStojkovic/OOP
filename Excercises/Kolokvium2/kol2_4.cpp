#include <iostream>
#include <cstring>
using namespace std;

enum Size { mala, golema, familijarna };
char SizeText[3][8] = { "small", "large", "family" };

class Pizza {
protected:
    char name[20];
    char ingredients[50];
    float basePrice;

    void copy_pizza(const Pizza& other) {
        strcpy(this->name, other.name);
        strcpy(this->ingredients, other.ingredients);
        this->ingredients[49] = '\0';
        this->basePrice = other.basePrice;
    }
public:
    Pizza() {
        strcpy(this->name, " ");
        strcpy(this->ingredients, " ");
        this->basePrice = 0.0;
    }

    Pizza(char* name, char* ingredients, float basePrice) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->ingredients[49] = '\0';
        this->basePrice = basePrice;
    }

    Pizza(const Pizza& other) {
        copy_pizza(other);
    }

    Pizza& operator=(const Pizza& other) {
        if(this == &other) return *this;
        copy_pizza(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Pizza& p);

    bool operator<(Pizza &p) { return price() < p.price(); }

    virtual float price() { return basePrice; }

    ~Pizza() { }
};

class FlatPizza : public Pizza {
protected:
    Size size;

public:
    FlatPizza() : Pizza() {
        this->size = mala;
    }

    FlatPizza(char* name, char* ingredients, float basePrice, Size size = mala) : Pizza(name, ingredients, basePrice) {
        this->size = size;
    }

    FlatPizza(const FlatPizza& other) : Pizza(other) {
        this->size = other.size;
    }

    FlatPizza& operator=(const FlatPizza& other) {
        if(this == &other) return *this;
        Pizza::operator=(other);
        this->size = other.size;
        return *this;
    }

    float price() {
        switch(size) {
            case mala:
                return basePrice * 1.1;
            case golema:
                return basePrice * 1.2;
            case familijarna:
                return basePrice * 1.3;
        }

        return basePrice;
    }

    char* getSize() { return SizeText[size]; }

    ~FlatPizza() { }
};

class FoldedPizza : public Pizza {
    bool whiteFlour;

public:
    FoldedPizza() : Pizza() {
        this->whiteFlour = true;
    }

    FoldedPizza(char* name, char* ingredients, float basePrice) : Pizza(name, ingredients, basePrice) {
        this->whiteFlour = true;
    }

    FoldedPizza(const FoldedPizza& other) : Pizza(other) {
        this->whiteFlour = other.whiteFlour;
    }

    FoldedPizza& operator=(const FoldedPizza& other) {
        if(this == &other) return *this;
        Pizza::operator=(other);
        this->whiteFlour = other.whiteFlour;
        return *this;
    }

    void setWhiteFlour(bool _whiteFlour) { this->whiteFlour = _whiteFlour; }
    bool getWhiteFlour() { return whiteFlour; }

    float price() { return basePrice * (whiteFlour ? 1.1 : 1.3); }

    ~FoldedPizza() { }
};

ostream& operator<<(ostream& out, Pizza& p) {
    out << p.name << ": " << p.ingredients << ", ";

    if(dynamic_cast<FlatPizza*>(&p)) {
        out << dynamic_cast<FlatPizza*>(&p)->getSize();
    } else if(dynamic_cast<FoldedPizza*>(&p)) {
        if(dynamic_cast<FoldedPizza*>(&p)->getWhiteFlour()) out << "wf";
        else out << "nwf";
    }

    out << " - " << p.price() << "\n";

    return out;
}

void expensivePizza(Pizza** pi, int n) {
    int idx = 0;

    for(int i = 0; i < n; i++) {
        if(pi[i]->price() > pi[idx]->price()) idx = i;
    }

    cout << *pi[idx];
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
