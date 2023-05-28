// En - 1

#include <iostream>
#include <cstring>
using namespace std;

class AlcoholicDrink {
protected:
    char name[100];
    char country[100];
    float alcohol;
    float price;
    static int discount;

public:
    AlcoholicDrink() {
        strcpy(this->name, " ");
        strcpy(this->country, " ");
        this->alcohol = this->price = 0;
    }

    AlcoholicDrink(char* name, char* country, float price, float alcohol) {
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->alcohol = alcohol;
        this->price = price;
    }

    AlcoholicDrink(const AlcoholicDrink& other) {
        strcpy(this->name, other.name);
        strcpy(this->country, other.country);
        this->alcohol = other.alcohol;
        this->price = other.price;
    }

    AlcoholicDrink& operator=(const AlcoholicDrink& other) {
        if(this == &other) return *this;

        strcpy(this->name, other.name);
        strcpy(this->country, other.country);
        this->alcohol = other.alcohol;
        this->price = other.price;

        return *this;
    }

    friend ostream& operator<<(ostream& os, AlcoholicDrink& other) {
        os << other.name << " " << other.country << " " << other.computePrice();
        return os;
    }

    bool operator<(const AlcoholicDrink& other) const {
        return price < other.price;
    }

    virtual float computePrice() {
        return price;
    }

    static void changeDiscount(int);
    static void total(AlcoholicDrink**, int);

    char* getName() { return name; }
    void setName(char* name) { strcpy(this->name, name); }

    char* getCountry() { return country; }
    void setCountry(char* country) { strcpy(this->country, country); }

    float getAlcohol() { return alcohol; }
    void setAlcohol(float alcohol) { this->alcohol = alcohol; }

    float getPrice() { return price; }
    void setPrice(float price) { this->price = price; }

    ~AlcoholicDrink() { }
};

int AlcoholicDrink::discount = 5;

class Beer : public AlcoholicDrink {
    bool ingredient; // 1 - barley, 0 - wheat

public:
    Beer() {
        ingredient = false;
    }

    Beer(float alcohol, char* name, char* country, float price, bool ingredient) {
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->price = price;
        this->alcohol = alcohol;
        this->ingredient = ingredient;
    }

    Beer(const Beer& other) {
        strcpy(this->name, other.name);
        strcpy(this->country, other.country);
        this->price = other.price;
        this->alcohol = other.alcohol;
        this->ingredient = other.ingredient;
    }

    Beer& operator=(const Beer& other) {
        if(this == &other) return *this;

        strcpy(this->name, other.name);
        strcpy(this->country, other.country);
        this->price = other.price;
        this->alcohol = other.alcohol;
        this->ingredient = other.ingredient;

        return *this;
    }

    float computePrice() {
        float s = 0;
        if(strcmp(country, "Germany") == 0) s += 0.05 * price;
        if(!ingredient) s += 0.1 * price;
        return price + s;
    }

    bool getIngredient() { return ingredient; }
    void setIngredient(bool ingredient) { this->ingredient = ingredient; }

    ~Beer() { }
};

class Wine : public AlcoholicDrink {
    int year;
    char grape[20];

public:
    Wine() {
        this->year = 0;
        strcpy(this->grape, " ");
    }
    // p, name, country, price, year, grape
    Wine(float alcohol, char* name, char* country, float price, int year, char* grape) {
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->price = price;
        this->alcohol = alcohol;
        this->year = year;
        strcpy(this->grape, grape);
    }

    Wine(const Wine& other) {
        strcpy(this->name, other.name);
        strcpy(this->country, other.country);
        this->price = other.price;
        this->alcohol = other.alcohol;
        this->year = other.year;
        strcpy(this->grape, other.grape);
    }

    Wine& operator=(const Wine& other) {
        if(this == &other) return *this;

        strcpy(this->name, other.name);
        strcpy(this->country, other.country);
        this->price = other.price;
        this->alcohol = other.alcohol;
        this->year = other.year;
        strcpy(this->grape, other.grape);

        return *this;
    }

    float computePrice() {
        float s = 0;
        if(strcmp(country, "Italy") == 0) s += 0.05 * price;
        if(year < 2005) s += 0.15 * price;
        return price + s;
    }

    int getYear() { return year; }
    void setYear(int year) { this->year = year; }

    char* getGrape() { return grape; }
    void setGrape(char* grape) { strcpy(this->grape, grape); }

    ~Wine() { }
};

void AlcoholicDrink::changeDiscount(int d) { AlcoholicDrink::discount = d; }

void AlcoholicDrink::total(AlcoholicDrink **ad, int n) {
    if(n <= 0) return;

    double s = 0, d = 0;
    for(int i = 0; i < n; i++) {
        double price = ad[i]->computePrice();
        s += price;
        d += (price * (AlcoholicDrink::discount / 100.0));
    }

    cout << "Total price: " << s << "\n";
    cout << "Total price with discount: " << s - d << "\n";
}

void lowestPrice(AlcoholicDrink** a, int n) {
    if(n <= 0) return;

    int idx = 0, flag = 0;
    float lowest = a[0]->computePrice();

    for(int i = 0; i < n; i++) {
        if(a[i]->computePrice() < lowest) {
            idx = i;
            lowest = a[i]->computePrice();
        }
    }

    cout << *a[idx];
}

int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape [20];
    if(testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if(testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    } else if(testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }

}