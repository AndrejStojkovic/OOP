// En - 23

#include <iostream>
#include <cstring>
using namespace std;

int net(int x) {
    return x >= 0 ? x : 0;
}

class MonthlyInvoice {
protected:
    char user[100];
    int num;
    float basePrice;
    int usedNet;

private:
    void copy_monthly(const MonthlyInvoice& other) {
        strcpy(this->user, other.user);
        this->num = other.num;
        this->basePrice = other.basePrice;
        this->usedNet = other.usedNet;
    }

public:
    MonthlyInvoice() {
        strcpy(this->user, "user");
        this->num = this->usedNet = 0;
        this->basePrice = 0;
    }

    MonthlyInvoice(char* user, int num, float basePrice, int usedNet) {
        strcpy(this->user, user);
        this->num = num;
        this->basePrice = basePrice;
        this->usedNet = usedNet;
    }

    MonthlyInvoice(const MonthlyInvoice& other) {
        copy_monthly(other);
    }

    MonthlyInvoice& operator=(const MonthlyInvoice& other) {
        if(this == &other) {
            return *this;
        }
        copy_monthly(other);
        return *this;
    }

    bool operator>(MonthlyInvoice& other) {
        return total_price() > other.total_price();
    }

    friend ostream& operator<<(ostream& out, MonthlyInvoice& invoice) {
        out << invoice.num << " - " << invoice.user << ", " << invoice.basePrice << "\n";
        return out;
    }

    virtual float total_price() = 0;

    ~MonthlyInvoice() { }
};

class BusinessInvoice : public MonthlyInvoice {
    bool line; // optic - true, cable - false;
    int quantity;

    void copy_business(const BusinessInvoice& other) {
        this->line = other.line;
        this->quantity = other.quantity;
    }

public:
    BusinessInvoice() : MonthlyInvoice() {
        this->line = false;
        this->quantity = 0;
    }

    BusinessInvoice(char* user, int num, float basePrice, int usedNet, bool line, int quantity) : MonthlyInvoice(user, num, basePrice, usedNet) {
        this->line = line;
        this->quantity = quantity;
    }

    BusinessInvoice(const BusinessInvoice& other) : MonthlyInvoice(other) {
        copy_business(other);
    }

    BusinessInvoice& operator=(const BusinessInvoice& other) {
        if(this == &other) {
            return *this;
        }
        MonthlyInvoice::operator=(other);
        copy_business(other);
        return *this;
    }

    BusinessInvoice& operator++(int) {
        BusinessInvoice* b = new BusinessInvoice(user, num, basePrice, usedNet, line, quantity);
        usedNet++;
        return *b;
    }

    friend ostream& operator<<(ostream& out, BusinessInvoice& invoice) {
        out << *dynamic_cast<MonthlyInvoice*>(&invoice);
        out << (invoice.line ? "optical" : "cable") << " link, " << net(invoice.usedNet - invoice.quantity) << "\n";
    }

    float total_price() {
        float s = line ? basePrice * 1.5 : basePrice;
        s += net(usedNet - quantity) * 100.0;
        return s;
    }

    ~BusinessInvoice() { }
};

class PrivateInvoice : public MonthlyInvoice {
    char id[16];
    int* movieSizes;
    int len;

    void copy_private(const PrivateInvoice& other) {
        strcpy(this->id, other.id);
        this->movieSizes = new int[other.len];
        for(int i = 0; i < other.len; i++) {
            this->movieSizes[i] = other.movieSizes[i];
        }
        this->len = other.len;
    }

public:
    PrivateInvoice() : MonthlyInvoice() {
        strcpy(this->id, "id");
        this->movieSizes = nullptr;
        this->len = 0;
    }

    PrivateInvoice(char* user, int num, float basePrice, int usedNet) : MonthlyInvoice(user, num, basePrice, usedNet) {
        strcpy(this->id, "id");
        this->movieSizes = nullptr;
        this->len = 0;
    }

    PrivateInvoice(char* user, int num, float basePrice, int usedNet, char* id, int* movieSizes, int len) : MonthlyInvoice(user, num, basePrice, usedNet) {
        strcpy(this->id, id);
        this->movieSizes = new int[len];
        for(int i = 0; i < len; i++) {
            this->movieSizes[i] = movieSizes[i];
        }
        this->len = len;
    }

    PrivateInvoice(const PrivateInvoice& other) : MonthlyInvoice(other) {
        copy_private(other);
    }

    PrivateInvoice& operator=(const PrivateInvoice& other) {
        if(this == &other) {
            return *this;
        }
        MonthlyInvoice::operator=(other);
        copy_private(other);
        return *this;
    }

    int operator[](int idx) {
        if(idx < 0 || idx >= len) {
            return -1;
        }

        return movieSizes[idx];
    }

    PrivateInvoice& operator+=(int movie) {
        int* tmp = new int[len + 1];
        for(int i = 0; i < len; i++) {
            tmp[i] = movieSizes[i];
        }
        tmp[len++] = movie;

        delete [] movieSizes;
        this->movieSizes = new int[len];
        for(int i = 0; i < len; i++) {
            this->movieSizes[i] = tmp[i];
        }
        delete [] tmp;
    }

    PrivateInvoice& operator++(int) {
        PrivateInvoice* p = new PrivateInvoice(user, num, basePrice, usedNet, id, movieSizes, len);
        usedNet++;
        return *p;
    }

    friend ostream& operator<<(ostream& out, PrivateInvoice& invoice) {
        out << *dynamic_cast<MonthlyInvoice*>(&invoice);
        out << invoice.usedNet << "\n" << invoice.len << ", " << invoice.sum() << "\n";
    }

    int sum() {
        int s = 0;
        for(int i = 0; i < len; i++) {
            s += movieSizes[i];
        }
        return s;
    }

    int getMoviesNo() {
        return len;
    }

    float total_price() {
        return basePrice + usedNet * 50 + sum() * 10;
    }

    ~PrivateInvoice() { }
};

MonthlyInvoice& biggestInvoice(MonthlyInvoice** arr, int n) {
    int idx = -1;

    for(int i = 0; i < n; i++) {
        if(idx == -1 || arr[i]->total_price() > arr[idx]->total_price()) {
            idx = i;
        }
    }

    if(idx == -1) {
        MonthlyInvoice* empty;
        return *empty;
    }

    return *arr[idx];
}

int main(){
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin>>test_case;
    if (test_case == 1){
        // Test Case Business Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;
        cin>>optical>>free_gigabytes;
        BusinessInvoice bi(username, userNumber,basic_price, spent_gigabytes, optical, free_gigabytes);
        cout<<"BusinessInvoice Created:\n";
        cout<<bi;
    }
    else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            bi++;
        }
        cout << bi;
    }
    else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout<<bi.total_price()<<endl;
        bi++;
        cout << bi;
        cout<<bi.total_price()<<endl;
    }
    else if (test_case == 4){
        // Test Case Private Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;

        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<"Private Invoice Created:\n";
        cout<<pi;
    }
    else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            pi++;
        }
        cout << pi;
    }
    else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
    }
    else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i=0; i<pi.getMoviesNo(); ++i){
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    }
    else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<pi;
        cout<< pi.total_price() <<endl;
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i){
            pi++;
        }
        cout << pi;
        cout<< pi.total_price() <<endl;
    }
    else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >>num_invoices;
        MonthlyInvoice ** mi = new MonthlyInvoice*[num_invoices];
        for (int j=0;j<num_invoices; ++j) {

            cin >> invoice_type;
            if (invoice_type == 1){
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice * bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i=0; i<num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout<<bip->total_price()<<endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice* pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice& invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice* m = &invoice;
        BusinessInvoice* bip;
        PrivateInvoice* pip;
        if (dynamic_cast<BusinessInvoice *> (m)){
            bip = dynamic_cast<BusinessInvoice *> (m);
            cout<<*bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *> (m)){
            pip = dynamic_cast<PrivateInvoice *> (m);
            cout<<*pip << pip->total_price();
        }

    }
    return 0;
}