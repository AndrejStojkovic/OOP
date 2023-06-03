// En - 20

#include <iostream>
#include <cstring>
using namespace std;

class Word {
    char* c;

    void copy_word(const Word& other) {
        this->c = new char[strlen(other.c) + 1];
        strcpy(this->c, other.c);
    }

public:
    Word() {
        this->c = "UNDEFINED";
    }

    Word(char* d) {
        this->c = new char[strlen(c) + 1];
        strcpy(this->c, d);
    }

    Word(const Word& other) {
        copy_word(other);
    }

    Word& operator=(const Word& other) {
        if(this == &other) {
            return *this;
        }
        copy_word(other);
        return *this;
    }

    char* get() {
        return c;
    }
};

class Sentence {
    Word* arr;
    int n;
    int capacity;

    void copy(const Sentence& other) {
        this->arr = new Word[other.n];
        for(int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
        this->n = other.n;
        this->capacity = other.capacity;
    }

public:
    Sentence() {
        this->arr = nullptr;
        this->n = this->capacity = 0;
    }

    Sentence(const Sentence& other) {
        copy(other);
    }

    Sentence& operator=(const Sentence& other) {
        if(this == &other) {
            return *this;
        }
        delete [] arr;
        copy(other);
        return *this;
    }

    void add(Word w) {
        Word* tmp = new Word[n];
        for(int i = 0; i < n; i++) {
            tmp[i] = arr[i];
        }

        if(n >= capacity) {
            capacity += 10;
        }

        if(n > 0) {
            delete [] this->arr;
        }

        this->arr = new Word[n + 1];
        int i = 0;
        for(i = 0; i < n; i++) {
            this->arr[i] = tmp[i];
        }
        this->arr[i++] = w;
        this->n = i;
        delete [] tmp;
    }

    void print() {
        for(int i = 0; i < n; i++) {
            cout << arr[i].get() << " ";
        }
        cout << "\n";
    }

    void swap(int i, int j) {
        if(i < 0 || i >= n || j < 0 || j >= n) {
            return;
        }

        Word tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    ~Sentence() {
        delete [] arr;
    }
};

int main() {
    int n;
    cin >> n;
    cin.get();
    cout << "CONSTRUCTOR" << endl;
    Sentence s;
    cout << "ADD WORD" << endl;
    for (int i = 0; i < n; ++i) {
        char w[100];
        cin.getline(w, 100);
        Word word(w);
        s.add(word);
    }
    cout << "PRINT SENTENCE" << endl;
    s.print();
    cout << "COPY" << endl;
    Sentence x = s;
    cout << "SWAP" << endl;
    x.swap(n / 2, n / 3);
    x.print();
    cout << "ORIGINAL" << endl;
    s.print();
    return 0;
}