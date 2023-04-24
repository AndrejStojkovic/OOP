// 6 - 1

#include <iostream>
#include <cstring>
using namespace std;

class DisciplinaryAction {
    char* name;
    int index;
    char* reason;
    int sessions;

    void copy(const DisciplinaryAction& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->index = other.index;
        this->reason = new char[strlen(other.reason) + 1];
        strcpy(this->reason, other.reason);
        this->sessions = other.sessions;
    }
public:
    DisciplinaryAction() {
        this->name = new char[0];
        strcpy(this->name, " ");
        this->index = 0;
        this->reason = new char[0];
        strcpy(this->reason, " ");
        this->sessions = 0;
    }

    DisciplinaryAction(char* name, int index, char* reason, int sessions) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->index = index;
        this->reason = new char[strlen(reason) + 1];
        strcpy(this->reason, reason);
        this->sessions = sessions;
    }

    DisciplinaryAction(const DisciplinaryAction& other) {
        copy(other);
    }

    DisciplinaryAction& operator=(const DisciplinaryAction& other) {
        if(this == &other) return *this;

        delete [] name;
        delete [] reason;
        copy(other);

        return *this;
    }

    friend ostream& operator<<(ostream& os, const DisciplinaryAction& other) {
        os << "Student: " << other.name << "\n";
        os << "Student's index: " << other.index << "\n";
        os << "Reason: " << other.reason << "\n";
        os << "Sessions: " << other.sessions << "\n";
        return os;
    }

    DisciplinaryAction& operator++() {
        this->sessions++;
        return *this;
    }

    bool operator>=(const DisciplinaryAction& other) {
        return this->sessions >= other.sessions;
    }

    int getIndex() { return index; }
    void setIndex(int index) { this->index = index; }

    ~DisciplinaryAction() {
        delete [] name;
        delete [] reason;
    }
};

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}
