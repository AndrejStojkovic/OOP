// 3 - 2

#include <iostream>
#include <cstring>

using namespace std;

// your code here
class InvoiceItem {
    char name[100];
    int price;

public:
    InvoiceItem() {
        strcpy(this->name, " ");
        price = 0;
    }

    InvoiceItem(char* name, int price) {
        strcpy(this->name, name);
        this->price = price;
    }

    InvoiceItem(const InvoiceItem& other) {
        strcpy(this->name, other.name);
        this->price, other.price;
    }

    int getPrice() { return price; }

    ~InvoiceItem() { }
};

class Invoice {
    char number[10];
    int n;
    InvoiceItem items[100];

public:
    Invoice() {
        strcpy(this->number, " ");
        n = 0;
    }

    Invoice(char* number, int n, InvoiceItem* items) {
        strcpy(this->number, number);
        this->n = n;
        for(int i = 0; i < n; i++) this->items[i] = items[i];
    }

    Invoice(const Invoice& other) {
        strcpy(this->number, other.number);
        this->n = other.n;
        for(int i = 0; i < other.n; i++) this->items[i] = other.items[i];
    }

    char* getNumber() { return number; }

    int totalPrice() {
        int s = 0;
        for(int i = 0; i < n; i++) s += items[i].getPrice();
        return s;
    }

    ~Invoice() { }
};

// DO NOT CHANGE THE MAIN FUNCTION
int main()
{
    char number[10];
    int n;
    // testing default constructor
    InvoiceItem items[100];
    cin >> number >> n;
    for (int i = 0; i < n; i++) {
        char name[100];
        int price;
        cin >> name;
        cin >> price;

        // testing constructor with parameters
        InvoiceItem item(name, price);

        // testing copy constructor
        items[i] = item;
    }
    // testing constructor with parameters for Invoice
    Invoice invoice(number, n, items);

    // testing totalPrice function
    cout << "Total price for invoice number " << invoice.getNumber() << " is " << invoice.totalPrice() << endl;

    return 0;
}