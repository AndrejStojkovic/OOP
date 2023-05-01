// 2 - 1

#include <iostream>
#include <cstring>
using namespace std;

class Book {
protected:
    char ISBN[20];
    char title[50];
    char author[30];
    float price;

    void copy(const Book& other) {
        strcpy(this->ISBN, other.ISBN);
        strcpy(this->title, other.title);
        strcpy(this->author, other.author);
        this->price = other.price;
    }
public:
    Book() {
        strcpy(this->ISBN, "");
        strcpy(this->title, "");
        strcpy(this->author, "");
        this->price = 0.0;
    }

    Book(char* ISBN, char* title, char* author, float price) {
        strcpy(this->ISBN, ISBN);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price = price;
    }

    Book(const Book& other) {
        copy(other);
    }

    Book& operator=(const Book& other) {
        if(this == &other) return *this;
        copy(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Book& book) {
        out << book.ISBN << ": " << book.title << ", " << book.author << " " << book.bookPrice() << "\n";
        return out;
    }

    virtual float bookPrice() = 0;

    void setISBN(char *ISBN) { strcpy(this->ISBN, ISBN); }

    ~Book() { }
};

class OnlineBook : public Book {
    char* url;
    int size;

    void copy(const OnlineBook& other) {
        strcpy(this->ISBN, other.ISBN);
        strcpy(this->title, other.title);
        strcpy(this->author, other.author);
        this->price = other.price;
        this->url = new char[strlen(other.url) + 1];
        strcpy(this->url, other.url);
        this->size = other.size;
    }

public:
    OnlineBook() : Book() {
        this->url = new char[0];
        strcpy(this->url, "");
        this->size = 0;
    }

    OnlineBook(char* ISBN, char* title, char* author, float price, char* url, int size) : Book(ISBN, title, author, price) {
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
        this->size = size;
    }

    OnlineBook(const OnlineBook& other) {
        copy(other);
    }

    OnlineBook& operator=(const OnlineBook& other) {
        if(this == &other) return *this;
        delete [] url;
        copy(other);
        return *this;
    }

    float bookPrice() {
        return size > 20 ? 1.2f * price : price;
    }

    ~OnlineBook() {
        delete [] url;
    }
};

class PrintBook : public Book {
    float weight;
    bool inStock;

    void copy(const PrintBook& other) {
        strcpy(this->ISBN, other.ISBN);
        strcpy(this->title, other.title);
        strcpy(this->author, other.author);
        this->price = other.price;
        this->weight = other.weight;
        this->inStock = other.inStock;
    }

public:
    PrintBook() : Book() {
        this->weight = 0.0;
        inStock = false;
    }

    PrintBook(char* ISBN, char* title, char* author, float price, float weight, bool inStock) : Book(ISBN, title, author, price) {
        this->weight = weight;
        this->inStock = inStock;
    }

    PrintBook(const PrintBook& other) {
        copy(other);
    }

    PrintBook& operator=(const PrintBook& other) {
        if(this == &other) return *this;
        copy(other);
        return *this;
    }


    float bookPrice() {
        return weight > 0.7 ? 1.15 * price : price;
    }

    ~PrintBook() { }
};

bool operator>(Book& a, Book& b) {
    return a.bookPrice() > b.bookPrice();
}

void mostExpensiveBook(Book** books, int n) {
    int online = 0, printed = 0;

    int idx = -1;

    for(int i = 0; i < n; i++) {
        if(dynamic_cast<OnlineBook*>(books[i])) online++;
        else if(dynamic_cast<PrintBook*>(books[i])) printed++;

        if(idx == -1) { idx = i; continue; }

        if(books[i]->bookPrice() > books[idx]->bookPrice()) idx = i;
    }

    if(idx == -1) return;

    cout << "FINKI-Education\n";
    cout << "Total number of online books: " << online << "\n";
    cout << "Total number of print books: " << printed << "\n";
    cout << "The most expensive book is:\n";
    cout << *books[idx] << "\n";
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
