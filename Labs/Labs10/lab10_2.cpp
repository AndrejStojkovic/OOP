#include <iostream>
#include <cstring>
using namespace std;

class InvalidTimeException {
public:
    InvalidTimeException() { }
    void print() { cout << "The time is not valid\n"; }
};

class Race {
protected:
    char city[50];
    int year;
    int month;
    float time;
    float km;

private:
    void copy_race(const Race& other) {
        strcpy(this->city, other.city);
        this->year = other.year;
        this->month = other.month;
        this->time = other.time;
        this->km = other.km;
    }

public:
    Race() {
        strcpy(this->city, "city");
        this->year = this->month = 0;
        this->time = this->km = 0;
    }

    Race(char* city, int year, int month, float time, float km) {
        strcpy(this->city, city);
        this->year = year;
        this->month = month;
        this->time = time;
        this->km = km;
    }

    Race(const Race& other) {
        copy_race(other);
    }

    Race& operator=(const Race& other) {
        if(this == &other) return * this;
        copy_race(other);
        return * this;
    }

    friend ostream& operator<<(ostream& out, Race& r) {
        out << r.city << " " << r.month << "." << r.year << " " << r.heaviness() << "\n";
        return out;
    }

    virtual float heaviness() {
        return time / km;
    }

    ~Race() { }
};

class CarRace : public Race {
    float* times;
    int n;
    int laps;
    static float CAR_COEF;

    void copy_carrace(const CarRace& other) {
        this->times = new float[other.n];
        for(int i = 0; i < n; i++) { this->times[i] = other.times[i]; }
        this->n = other.n;
        this->laps = other.laps;
    }

public:
    CarRace() {
        this->times = new float[0];
        this->n = this->laps = 0;
    }

    CarRace(char* city, int year, int month, float time, float km) : Race(city, year, month, time, km) {
        this->times = new float[0];
        this->n = this->laps = 0;
    }

    CarRace(char* city, int year, int month, float time, float km, float* times, int n, int laps) : Race(city, year, month, time, km) {
        this->times = new float[n];
        for(int i = 0; i < n; i++) { this->times[i] = times[i]; }
        this->n = n;
        this->laps = laps;
    }

    CarRace(const CarRace& other) : Race(other) {
        copy_carrace(other);
    }

    CarRace& operator=(const CarRace& other) {
        if(this == &other) return *this;
        Race::operator=(other);
        delete [] times;
        copy_carrace(other);
        return *this;
    }

    CarRace& operator+=(float new_time) {
        if(new_time < 10) throw InvalidTimeException();

        float* tmp = new float[n + 1];
        for(int i = 0; i < n; i++) tmp[i] = times[i];
        tmp[n++] = new_time;

        delete [] times;
        times = new float[n];
        for(int i = 0; i < n; i++) times[i] = tmp[i];
        delete [] tmp;
    }

    friend ostream& operator<<(ostream& out, CarRace& r) {
        out << r.city << " " << r.month << "." << r.year << " " << r.heaviness() << "\n";
        return out;
    }

    static void setKoeficient(float koef) {
        CAR_COEF = koef;
    }

    float heaviness() {
        float s = Race::heaviness() + (avg() * CAR_COEF);
        if(laps > 15) s += (0.1 * s);
        return s;
    }

    float avg() {
        float s = 0;
        for(int i = 0; i < n; i++) s += times[i];
        return s / n;
    }

    void setNumberLaps(int laps) {
        this->laps = laps;
    }

    ~CarRace() {
        delete [] times;
    }
};

float CarRace::CAR_COEF = 0.3;

int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            CarRace* nn = dynamic_cast<CarRace*>(niza[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1,vreme2;
        cin>>vreme1>>vreme2;
        try{
            mgt+=vreme1;
            mgt+=vreme2;
        }
        catch(InvalidTimeException e)
        {
            e.print();
        }
        cout<<mgt;
    }

    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }



    return 0;
}