// En - 15

#include <iostream>
#include <cstring>
using namespace std;

class Pair {
    char* key;
    int value;

    void copy_pair(const Pair& other) {
        this->key = new char[strlen(other.key) + 1];
        strcpy(this->key, other.key);
        this->value = other.value;
    }

public:
    Pair() {
        this->key = new char[4];
        strcpy(this->key, "123");
        this->value = 0;
    }

    Pair(char* key, int value) {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
    }

    Pair(const Pair& other) {
        copy_pair(other);
    }

    Pair& operator=(const Pair& other) {
        if(this == &other) {
            return *this;
        }
        delete [] key;
        copy_pair(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Pair& p) {
        out << "\'" << p.key << "\' -> " << p.value << "\n";
    }

    Pair& operator--() {
        value--;
        return *this;
    }

    Pair& operator--(int) {
        Pair* p = new Pair(key, value);
        value--;
        return *p;
    }

    friend Pair operator*(Pair& a, Pair& b) {
        char* new_key = strlen(a.key) < strlen(b.key) ? a.key : b.key;
        Pair p(new_key, a.value * b.value);
        return p;
    }

    int getValue() {
        return value;
    }

    ~Pair() {
        delete [] key;
    }
};

class Collection {
    Pair* arr;
    int n;

    void copy_collection(const Collection& other) {
        this->arr = new Pair[other.n];
        this->n = other.n;
        for(int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
    }

public:
    Collection() {
        this->arr = nullptr;
        this->n = 0;
    }

    Collection(const Collection& other) {
        copy_collection(other);
    }

    Collection& operator=(const Collection& other) {
        if(this == &other) {
            return *this;
        }
        delete [] arr;
        copy_collection(other);
        return *this;
    }

    Collection& operator+=(const Pair& c) {
        Pair* tmp = new Pair[n];
        for(int i = 0; i < n; i++) {
            tmp[i] = arr[i];
        }

        delete [] arr;

        this->arr = new Pair[n + 1];
        for(int i = 0; i < n; i++) {
            this->arr[i] = tmp[i];
        }
        this->arr[n++] = c;

        delete [] tmp;

        return *this;
    }

    friend ostream& operator<<(ostream& out, Collection& c) {
        out << "Size: " << c.n << "\n";
        for(int i = 0; i < c.n; i++) {
            out << c.arr[i];
        }
        return out;
    }

    bool operator<(Collection& c) {
        return product() < c.product();
    }

    int product() {
        int s = 1;
        for(int i = 0; i < n; i++) {
            s *= arr[i].getValue();
        }
        return s;
    }

    int greater(int value) {
        int ct = 0;
        for(int i = 0; i < n; i++) {
            if(arr[i].getValue() > value) {
                ct++;
            }
        }
        return ct;
    }

    ~Collection() {
        delete [] arr;
    }
};

void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}

int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator --(int) -----" << endl;
    cout << p1--;
    cout << p1;
    cout << "----- operator -- -----" << endl;
    cout << --p2;
    cout << "----- operator * -----" << endl;
    Pair p = p1 * p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator < -----" << endl;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    k2 += p1;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    cout << "----- greater -----" << endl;
    int x;
    cin >> x;
    int pp = k.greater(x);
    cout << pp;
    return 0;
}