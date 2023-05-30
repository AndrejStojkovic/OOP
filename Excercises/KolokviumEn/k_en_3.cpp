// En - 3

#include <iostream>
#include <cstring>
using namespace std;

class Character {
    char c;

public:
    Character() {
        this->c = 0;
    }

    Character(char c) {
        this->c = c;
    }

    Character(const Character& other) {
        this->c = other.c;
    }

    Character& operator=(const Character& other) {
        if(this == &other) {
            return *this;
        }

        this->c = other.c;
        return *this;
    }

    friend ostream& operator<<(ostream& out, Character& ch) {
        return out << ch.c;
    }

    char getCharacter() {
        return c;
    }

    void setCharacter(char c) {
        this->c = c;
    }

    ~Character() { }
};

class CharSequence {
    Character* arr;
    int len;

    void copy_seq(const CharSequence& other) {
        this->arr = new Character[other.len];
        for(int i = 0; i < other.len; i++) {
            this->arr[i] = other.arr[i];
        }
        this->len = other.len;
    }

public:
    CharSequence() {
        this->arr = new Character[0];
        this->len = 0;
    }

    CharSequence(char* str) {
        this->arr = new Character[strlen(str) + 1];
        for(int i = 0; i < strlen(str); i++) {
            this->arr[i].setCharacter(str[i]);
        }
        this->len = strlen(str);
    }

    CharSequence(const CharSequence& other) {
        copy_seq(other);
    }

    CharSequence& operator=(const CharSequence& other) {
        if(this == &other) {
            return *this;
        }

        delete [] arr;
        copy_seq(other);
        return *this;
    }

    Character& operator[](int i) {
        if(i < 0 || i >= len) {
            Character character;
            return character;
        }

        return arr[i];
    }

    CharSequence& operator+=(const Character& c) {
        Character* tmp = new Character[len + 1];
        for(int i = 0; i < len; i++) {
            tmp[i] = arr[i];
        }
        tmp[len++] = c;

        delete [] arr;
        this->arr = new Character[len];
        for(int i = 0; i < len; i++) {
            this->arr[i] = tmp[i];
        }
        delete [] tmp;
    }

    bool operator==(const CharSequence& cs) {
        if(len != cs.len) {
            return false;
        }

        for(int i = 0; i < len; i++) {
            if(arr[i].getCharacter() != cs.arr[i].getCharacter()) {
                return false;
            }
        }

        return true;
    }

    int operator[](char c) {
        int s = 0;
        for(int i = 0; i < len; i++) {
            if(arr[i].getCharacter() == c) {
                s++;
            }
        }
        return s;
    }

    friend ostream& operator<<(ostream& out, const CharSequence& cs) {
        for(int i = 0; i < cs.len; i++) {
            out << cs.arr[i];
        }
        return out;
    }

    CharSequence toUpperCase() {
        CharSequence n;
        for(int i = 0; i < len; i++) {
            n += (char)toupper(arr[i].getCharacter());
        }
        return n;
    }

    ~CharSequence() {
        delete [] arr;
    }
};

int main() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if(n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if(n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for(int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if(n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs['e'] << endl;
    } else if(n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    } else if(n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}