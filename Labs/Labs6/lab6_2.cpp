// 6 - 2

// 2.
#include <iostream>
#include <cstring>
using namespace std;

class Book {
    char* name;
    int isbn[5];
    int pages;

    void copy(const Book& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        for(int i = 0; i < 5; i++) this->isbn[i] = other.isbn[i];
        this->pages = other.pages;
    }
public:
    Book() {
        this->name = new char[2];
        strcpy(this->name, "");
        for(int i = 0; i < 5; i++) this->isbn[i] = 0;
        this->pages = 0;
    }

    Book(char* name, int* isbn, int pages) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        for(int i = 0; i < 5; i++) this->isbn[i] = isbn[i];
        this->pages = pages;
    }

    Book(const Book& other) {
        copy(other);
    }

    Book& operator=(const Book& other) {
        if(this == &other) return *this;
        delete [] name;
        copy(other);
        return *this;
    }

    bool operator==(const Book& other) {
        for(int i = 0; i < 5; i++)
            if(this->isbn[i] != other.isbn[i])
                return false;

        return true;
    }

    friend ostream& operator<<(ostream& os, const Book& other) {
        os << "Title: " << other.name << " ISBN: [ ";
        for(int i = 0; i < 5; i++) os << other.isbn[i] << " ";
        os << "]\n";
        return os;
    }

    char* getTitle() { return name; }
    void setTitle(char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    int* getISBN() { return isbn; }
    void setISBN(int* isbn) { for(int i = 0; i < 5; i++) this->isbn[i] = isbn[i]; }

    int getPages() { return pages; }
    void setPages(int pages) { this->pages = pages; }

    ~Book() {
        delete [] name;
    }
};

class BorrowABook {
    char name[100];
    Book* books;
    int n;

    void copy(const BorrowABook& other) {
        strcpy(this->name, other.name);
        this->books = new Book[other.n];
        for(int i = 0; i < other.n; i++) this->books[i] = other.books[i];
        this->n = other.n;
    }
public:
    BorrowABook() {
        strcpy(this->name, "");
        this->books = new Book[0];
        this->n = 0;
    }

    BorrowABook(char* name) {
        strcpy(this->name, name);
        this->books = new Book[0];
        this->n = 0;
    }

    BorrowABook& operator=(const BorrowABook& other) {
        if(this == &other) return *this;

        delete [] books;
        copy(other);
        return *this;
    }

    BorrowABook& operator+=(const Book& book) {
        Book* tmp = new Book[n + 1];
        for(int i = 0; i < n; i++) tmp[i] = this->books[i];
        tmp[n++] = book;

        delete [] this->books;
        this->books = tmp;

        return *this;
    }

    BorrowABook& operator-=(const Book& book) {
        int index = -1;

        for(int i = 0; i < n; i++) {
            if(this->books[i] == book) {
                index = i;
                break;
            }
        }

        if(index == -1) return *this;

        Book* tmp = new Book[n - 1];
        int ct = 0;
        for(int i = 0; i < n; i++) {
            if(this->books[i] == book) continue;
            tmp[ct++] = this->books[i];
        }

        n--;
        delete [] books;
        this->books = tmp;

        return *this;
    }

    void printNumberOfPages(int pages) {
        cout << name << "\n";
        for(int i = 0; i < n; i++) {
            if(this->books[i].getPages() > pages) {
                cout << this->books[i];
            }
        }
    }

    ~BorrowABook() {
        delete [] books;
    }
};

/// Do NOT edit the main() function
int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int j=0;j<5;j++)
            cin>>isbn[j];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;
    }

    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}
