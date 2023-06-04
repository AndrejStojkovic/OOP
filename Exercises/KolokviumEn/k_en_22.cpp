// En - 22

#include <iostream>
#include <cstring>
using namespace std;

class IndexOutOfBounds {
    int index;
public:
    IndexOutOfBounds(int index) { this->index = index; }
    void message() { cout << "Index \'" << index << "\' is out of bounds\n"; }
};

class String {
    char* str;
    int len;

    void copy_string(const String& other) {
        this->str = new char[other.len + 1];
        strcpy(this->str, other.str);
        this->len = other.len;
    }
public:
    String() {
        this->str = new char[0];
        this->len = 0;
    }

    String(char* str) {
        this->str = new char[strlen(str) + 1];
        strcpy(this->str, str);
        this->len = strlen(str);
    }

    String(const String& other) {
        copy_string(other);
    }

    String& operator=(const String& other) {
        if(this == &other) {
            return *this;
        }
        delete [] str;
        copy_string(other);
        return *this;
    }

    char operator[](int index) {
        if(index < 0 || index >= len) {
            throw IndexOutOfBounds(index);
        }

        return str[index];
    }

    char* getString() { return str; }
    int getLength() { return len; }

    friend class StringBuilder;

    ~String() {
        delete [] str;
    }
};

class StringBuilder {
    char** strings;
    int len;
    int capacity;

public:
    StringBuilder() {
        this->strings = new char*[0];
        this->len = this->capacity = 0;
    }

    StringBuilder(int capacity) {
        this->strings = new char*[0];
        this->len = 0;
        this->capacity = capacity;
    }

    String& operator+=(String& string) {
        if(getSize() + string.getLength() + 2 > capacity) {
            capacity *= 2;
        }

        if(getSize() + string.getLength() + 2 > capacity) {
            capacity = capacity / 2 + string.getLength();
        }

        int newSize = len + 1;
        strings = (char**)realloc(strings, newSize * sizeof(char*));
        strings[len] = (char*)malloc( (strlen(string.getString()) + 1) * sizeof(char));

        strcpy(strings[len], string.getString());
        this->len++;
    }

    friend ostream& operator<<(ostream& out, StringBuilder& other) {
        out << "Capacity: " << other.capacity << "\n";
        out << "Size: " << other.getSize() << "\n";
        out << "Contents: ";
        for(int i = 0; i < other.len; i++) {
            out << other.strings[i];
        }
        out << "\n";
        return out;
    }

    int getSize() {
        int s = 0;
        for(int i = 0; i < len; i++) {
            s += strlen(strings[i]);
        }
        return s;
    }

    friend class String;

    ~StringBuilder() {
        for(int i = 0; i < len; i++) delete strings[i];
        delete [] strings;
    }
};

int main() {
    int n;
    cin >> n;
    StringBuilder sb(n);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        char input[100];
        cin >> input;
        String s(input);
        int x;
        cin >> x;

        try {
            cout << "s[" << x << "] = " << s[x] << endl;
        } catch(IndexOutOfBounds& e) {
            e.message();
        }

        sb += s;
    }
    cout << sb;
    return 0;
}