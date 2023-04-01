// 3 - 3

#include <iostream>
#include <cstring>
using namespace std;

class FoodProduct {
    char name[50];
    int amount;
    int price;

public:
    FoodProduct() {
        strcpy(this->name, " ");
        amount = price = 0;
    }

    FoodProduct(char* name, int amount, int price) {
        strcpy(this->name, name);
        this->amount = amount;
        this->price = price;
    }

    FoodProduct(const FoodProduct& other) {
        strcpy(this->name, other.name);
        this->amount = other.amount;
        this->price = other.price;
    }

    int getAmount() { return amount; }
    void setAmount(int amount) { this->amount = amount; }

    int getPrice() { return price; }
    void setPrice(int price) { this->price = price; }

    void print() {
        cout << "Name: " << name << "\n";
        cout << "Amount available: " << amount << "\n";
        cout << "Price: " << price << "\n";
    }

    ~FoodProduct() { }
};

class Menu {
    char name[50];
    int n;
    FoodProduct food[50];

public:
    Menu() {
        strcpy(this->name, "");
        n = 0;
    }

    Menu(char* name) {
        strcpy(this->name, name);
        n = 0;
    }

    Menu(char* name, int n, FoodProduct* food) {
        strcpy(this->name, name);
        this->n = n;
        for(int i = 0; i < n; i++) this->food[i] = food[i];
    }

    Menu(const Menu& other) {
        strcpy(this->name, other.name);
        this->n = other.n;
        for(int i = 0; i < n; i++) this->food[i] = other.food[i];
    }

    char* getName() { return name; }
    void setName(char* name) { strcpy(this->name, name); }

    int getNumberOfProducts() { return n; }
    void setNumberOfProducts(int n) { this->n = n; }

    void addProduct(FoodProduct p) {
        if(n >= 50) return;
        this->food[n++] = p;
    }

    void print() {
        cout << "Name: " << name << "\n";
        cout << "Products:\n";
        for(int i = 0; i < n; i++) food[i].print();
    }

    int totalIncome() {
        int s = 0;
        for(int i = 0; i < n; i++)
            s += (food[i].getAmount() * food[i].getPrice());

        return s;
    }

    ~Menu() { }
};

void printWorstMenu(Menu* menus, int n) {
    int idx = 0, r = menus[0].totalIncome();

    for(int i = 1; i < n; i++) {
        if(menus[i].totalIncome() < r) {
            r = menus[i].totalIncome();
            idx = i;
        }
    }

    menus[idx].print();
}

//DO NOT CHANGE main() FUNCTION
int main() {
    int n;
    cin >> n;

    /// BASIC INPUT & ADD PRODUCT
    Menu menus[n];

    for(int i = 0; i < n; i++) {
        int m;
        char name[50];

        cin >> name >> m;
        menus[i] = Menu(name);

        for(int j = 0; j < m; j++) {
            char itemName[50];
            int amount, price;

            cin >> itemName >> amount >> price;

            FoodProduct product(itemName, amount, price);
            menus[i].addProduct(product);
        }
    }

    /// TESTING ADD PRODUCT

    cout << "-- Testing add product & getNumberOfProducts() --\n\n";

    char tempName[50] = "test";
    Menu temp(tempName);

    cout << "Number of products before adding: " << temp.getNumberOfProducts() << '\n';

    temp.addProduct(FoodProduct(tempName, 0, 0));

    cout << "Number of products after adding: " << temp.getNumberOfProducts() << '\n';
    temp.print();

    /// TESTING COPY CONSTRUCTOR

    Menu tester(menus[0]);
    std::strcpy(tempName, "Tester Name");
    tester.setName(tempName);

    cout << "\n-- Testing copy constructor & setName() --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    menus[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    tester.print();

    /// TESTING WORST PRODUCT

    cout << "\n-- Testing printWorstMenu() --\n";
    printWorstMenu(menus, n);
    return 0;
}