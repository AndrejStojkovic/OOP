// 2 - 14

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class SMS {
protected:
    char broj[16];
    float price;
    static float ddv;

public:
    SMS() {
        strcpy(this->broj, "0038970000000");
        this->price = 0;
    }

    SMS(char* broj, float price) {
        strcpy(this->broj, broj);
        this->price = price;
    }

    SMS(const SMS& other) {
        strcpy(this->broj, other.broj);
        this->price = other.price;
    }

    SMS& operator=(const SMS& other) {
        if(this == &other) return *this;
        strcpy(this->broj, other.broj);
        this->price = other.price;
        return *this;
    }

    friend ostream& operator<<(ostream& out, SMS& sms) {
        out << "Tel: " << sms.broj << " - cena: " << sms.SMS_cena() << "den.\n";
        return out;
    }

    static void setDanok(float val) { SMS::ddv = val / 100.0; }

    virtual float SMS_cena() = 0;

    ~SMS() { }
};

class RegularSMS : public SMS {
    char message[1000];
    bool roaming;
    static float mult;

public:
    RegularSMS() : SMS() {
        strcpy(this->message, "msg");
        this->roaming = false;
    }

    RegularSMS(char* name, float price, char* message, bool roaming) : SMS(name, price) {
        strcpy(this->message, message);
        this->roaming = roaming;
    }

    float SMS_cena() {
        float x = roaming ? mult : ddv;
        return price * (1.0 + x) * ceil(strlen(message) / 160.0);
    }

    static void set_rProcent(float val) { RegularSMS::mult = val / 100; }

    ~RegularSMS() { }
};

class SpecialSMS : public SMS {
    bool humane;
    static float mult;

public:
    SpecialSMS() : SMS() { this->humane = false; }

    SpecialSMS(char* name, float price, bool humane) : SMS(name, price) { this->humane = humane; }

    static void set_sProcent(float val) { SpecialSMS::mult = val / 100; }

    float SMS_cena() { return humane ? price : price * (1.0 + mult); }

    ~SpecialSMS() { }
};

float RegularSMS::mult = 3.0;
float SpecialSMS::mult = 1.5;
float SMS::ddv = 0.18;

void vkupno_SMS(SMS** s, int n) {
    int reg = 0, sp = 0;
    float reg_price = 0, sp_price = 0;

    for(int i = 0; i < n; i++) {
        if(dynamic_cast<RegularSMS*>(s[i])) {
            reg++;
            reg_price += s[i]->SMS_cena();
        } else {
            sp++;
            sp_price += s[i]->SMS_cena();
        }
    }

    cout << "Vkupno ima " << reg << " regularni SMS poraki i nivnata cena e: " << reg_price << "\n";
    cout << "Vkupno ima " << sp << " specijalni SMS poraki i nivnata cena e: " << sp_price << "\n";
}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
