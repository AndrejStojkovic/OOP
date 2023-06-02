// En - 2

#include <iostream>
#include <cstring>
using namespace std;

class ExistingBill {
public:
    void message() {
        cout << "The bill already exists\n";
    }
};

class Bill {
    char* bill_number;
    int expense;
    char date[8];
    bool status;

    void copy_bill(const Bill& other) {
        this->bill_number = new char[strlen(other.bill_number) + 1];
        strcpy(this->bill_number, other.bill_number);
        this->expense = other.expense;
        strcpy(this->date, other.date);
        this->status = other.status;
    }

public:
    Bill() {
        this->bill_number = new char[0];
        this->expense = 0;
        strcpy(this->date, "MM.YYYY");
        this->status = false;
    }

    Bill(char* bill_number, int expense, char* date, bool status) {
        this->bill_number = new char[strlen(bill_number) + 1];
        strcpy(this->bill_number, bill_number);
        this->expense = expense;
        strcpy(this->date, date);
        this->status = status;
    }

    Bill(const Bill& other) {
        copy_bill(other);
    }

    Bill& operator=(const Bill& other) {
        if(this == &other) {
            return *this;
        }

        delete [] bill_number;
        copy_bill(other);
        return *this;
    }

    bool operator==(Bill& other) {
        return !strcmp(bill_number, other.bill_number);
    }

    friend ostream& operator<<(ostream& out, Bill& bill) {
        out << bill.bill_number << "(" << bill.date << ") - " << bill.expense << "\n";
        return out;
    }

    char* getBillNumber() {
        return bill_number;
    }

    char* getDate() {
        return date;
    }

    int getExpense() {
        return expense;
    }

    bool getStatus() {
        return status;
    }

    ~Bill() {
        delete [] bill_number;
    }
};

class UserProfile {
    char username[30];
    Bill arr[30];
    int n;

    void copy_user(const UserProfile& other) {
        strcpy(this->username, other.username);
        for(int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
        this->n = other.n;
    }

public:
    UserProfile() {
        strcpy(this->username, "user");
        this->n = 0;
    }

    UserProfile(char* username) {
        strcpy(this->username, username);
        this->n = 0;
    }

    UserProfile(char* username, Bill* arr, int n) {
        strcpy(this->username, username);
        for(int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
        }
        this->n = n;
    }

    UserProfile(const UserProfile& other) {
        copy_user(other);
    }

    UserProfile& operator=(const UserProfile& other) {
        if(this == &other) {
            return *this;
        }

        copy_user(other);
        return *this;
    }

    UserProfile& operator+=(Bill& b) {
        for(int i = 0; i < n; i++) {
            if(arr[i] == b) {
                throw ExistingBill();
            }
        }

        if(n >= 30) {
            return *this;
        }

        arr[n++] = b;
    }

    friend ostream& operator<<(ostream& out, UserProfile& user) {
        out << "Unpaid bills of user " << user.username << " are:\n";
        for(int i = 0; i < user.n; i++) {
            if(!user.arr[i].getStatus()) {
                out << user.arr[i];
            }
        }
        return out;
    }

    int totalDue(int month, int year) {
        int total = 0;

        char check_date[8];
        check_date[0] = (month / 10) + '0';
        check_date[1] = (month % 10) + '0';
        check_date[2] = '.';
        check_date[3] = (year / 1000) + '0';
        check_date[4] = ((year / 100) % 10) + '0';
        check_date[5] = ((year / 10) % 10) + '0';
        check_date[6] = (year % 10) + '0';
        check_date[7] = '\0';

        for(int i = 0; i < n; i++) {
            if(!strcmp(arr[i].getDate(), check_date)) {
                total += arr[i].getExpense();
            }
        }
        return total;
    }

    ~UserProfile() { }
};

int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try {
                up += s;
            } catch(ExistingBill& e) {
                e.message();
            }
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try {
                up += s;
            } catch(ExistingBill& e) {
                e.message();
            }
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try {
                up += s;
            } catch(ExistingBill& e) {
                e.message();
            }
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}