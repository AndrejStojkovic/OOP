// 2 - 12

#include <iostream>
#include <cstring>
using namespace std;

enum tip { smartphone, computer };
char Tip[][8] = { "Mobilen", "Laptop" };

class InvalidProductionDate {
public:
    void message() {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
    char model[100];
    tip type;
    static float hours;
    int year;

    void copy_device(const Device& other) {
        strcpy(this->model, other.model);
        this->type = other.type;
        this->year = other.year;
    }
public:
    Device() {
        strcpy(this->model, "model");
        this->type = smartphone;
        this->year = 0;
    }

    Device(char* model, tip type, int year) {
        strcpy(this->model, model);
        this->type = type;
        this->year = year;
    }

    Device(const Device& other) {
        copy_device(other);
    }

    Device& operator=(const Device& other) {
        if(this == &other) {
            return *this;
        }
        copy_device(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Device& device) {
        out << device.model << "\n" << Tip[device.type] << " " << device.proverka() << "\n";
        return out;
    }

    static void setPocetniCasovi(float _hours) {
        Device::hours = _hours;
    }

    float proverka() {
        float s = 0;

        if(year > 2015) {
            s += 2;
        }

        if(type == computer) {
            s += 2;
        }

        return s + Device::hours;
    }

    int getYear() {
        return year;
    }

    ~Device() { }
};

class MobileServis {
    char address[100];
    Device* d;
    int n;

    void copy_mobileservis(const MobileServis& other) {
        strcpy(this->address, other.address);
        this->d = new Device[other.n];
        for(int i = 0; i < other.n; i++) {
            this->d[i] = other.d[i];
        }
        this->n = other.n;
    }
public:
    MobileServis() {
        strcpy(this->address, "address");
        this->d = nullptr;
        this->n = 0;
    }

    MobileServis(char* address) {
        strcpy(this->address, address);
        this->d = nullptr;
        this->n = 0;
    }

    MobileServis(const MobileServis& other) {
        copy_mobileservis(other);
    }

    MobileServis& operator=(const MobileServis& other) {
        if(this == &other) {
            return *this;
        }
        delete [] d;
        copy_mobileservis(other);
        return *this;
    }

    MobileServis& operator+=(Device& device) {
        if(device.getYear() < 2000 || device.getYear() > 2019) {
            throw InvalidProductionDate();
        }

        Device* tmp = new Device[n + 1];
        for(int i = 0; i < n; i++) {
            tmp[i] = this->d[i];
        }
        tmp[n++] = device;

        delete [] d;
        this->d = new Device[n];
        for(int i = 0; i < n; i++) {
            this->d[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }

    void pecatiCasovi() {
        cout << "Ime: " << address << "\n";
        for(int i = 0; i < n; i++) {
            cout << d[i];
        }
    }

    ~MobileServis() {
        delete [] d;
    }
};

float Device::hours = 1;

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try { t+=tmp; }
            catch(InvalidProductionDate& e) { e.message(); }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try { t+=tmp; }
            catch(InvalidProductionDate& e) { e.message(); }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try { t+=tmp; }
            catch(InvalidProductionDate& e) { e.message(); }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try { t+=tmp; }
            catch(InvalidProductionDate& e) { e.message(); }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try { t+=tmp; }
            catch(InvalidProductionDate& e) { e.message(); }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}