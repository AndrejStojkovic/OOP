// En - 24

#include <iostream>
#include <cstring>
using namespace std;

class InvalidTimeException {
public:
    void message() {
        cout << "Invalid Time\n";
    }
};

class Race {
protected:
    char city[40];
    int year;
    int month;
    float bestTime;
    float km;

private:
    void copy_race(const Race& other) {
        strcpy(this->city, other.city);
        this->year = other.year;
        this->month = other.month;
        this->bestTime = other.bestTime;
        this->km = other.km;
    }

public:
    Race() {
        strcpy(this->city, "city");
        this->month = this->year = 0;
        this->bestTime = this->km = 0;
    }

    Race(char* city, int year, int month, float bestTime, float km) {
        strcpy(this->city, city);
        this->year = year;
        this->month = month;
        this->bestTime = bestTime;
        this->km = km;
    }

    Race(const Race& other) {
        copy_race(other);
    }

    Race& operator=(const Race& other) {
        if(this == &other) {
            return *this;
        }
        copy_race(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Race& r) {
        out << r.city << " " << r.month << "." << r.year << " " << r.complexity() << "\n";
        return out;
    }

    virtual float complexity() {
        return bestTime / km;
    }

    ~Race() { }
};

class MotoGPRace : public Race {
    float* bestTimes;
    int n;
    int laps;
    static float coef;

    void copy_motogp(const MotoGPRace& other) {
        this->bestTimes = new float[other.n];
        for(int i = 0; i < other.n; i++) {
            this->bestTimes[i] = other.bestTimes[i];
        }
        this->n = other.n;
        this->laps = other.laps;
    }

public:
    MotoGPRace() : Race() {
        this->bestTimes = nullptr;
        this->n = 0;
        this->laps = 0;
    }

    MotoGPRace(char* city, int year, int month, float bestTime, float km) : Race(city, year, month, bestTime, km) {
        this->bestTimes = nullptr;
        this->n = 0;
        this->laps = 0;
    }

    MotoGPRace(char* city, int year, int month, float bestTime, float km, float* bestTimes, int n, int laps) : Race(city, year, month, bestTime, km) {
        this->bestTimes = new float[n];
        for(int i = 0; i < n; i++) {
            this->bestTimes[i] = bestTimes[i];
        }
        this->n = n;
        this->laps = laps;
    }

    MotoGPRace(const MotoGPRace& other) : Race(other) {
        copy_motogp(other);
    }

    MotoGPRace& operator=(const MotoGPRace& other) {
        if(this == &other) {
            return *this;
        }
        delete [] bestTimes;
        copy_motogp(other);
        return *this;
    }

    MotoGPRace& operator+=(float newTime) {
        if(newTime < 9.5) {
            throw InvalidTimeException();
        }

        float* tmp = new float[n + 1];
        for(int i = 0; i < n; i++) {
            tmp[i] = bestTimes[i];
        }
        tmp[n++] = newTime;

        delete [] bestTimes;
        this->bestTimes = new float[n];
        for(int i = 0; i < n; i++) {
            this->bestTimes[i] = tmp[i];
        }
        delete [] tmp;
    }

    MotoGPRace& operator++(int) {
        MotoGPRace* p = new MotoGPRace(city, year, month, bestTime, km, bestTimes, n, laps);
        laps++;
        return *p;
    }

    friend ostream& operator<<(ostream& out, MotoGPRace& r) {
        out << r.city << " " << r.month << "." << r.year << " " << r.complexity() << "\n";
        return out;
    }

    float complexity() {
        float s = 0;
        for(int i = 0; i < n; i++) {
            s += bestTimes[i];
        }
        s = (s / n) * coef;
        s += Race::complexity();

        if(laps > 22) {
            s *= 1.2;
        }

        return s;
    }

    static void setK(float k) {
        coef = k;
    }

    void setNumberLaps(int laps) {
        this->laps = laps;
    }

    int getNumberLaps() {
        return laps;
    }

    ~MotoGPRace() {
        delete [] bestTimes;
    }
};

float MotoGPRace::coef = 0.4;

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
    int choice;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing - classes ======" << endl;
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
        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace* nn = dynamic_cast<MotoGPRace*>(rArray[i]);
            if (nn != 0){
                flag = 0;
                try {
                    (*nn) += best;
                } catch(InvalidTimeException& e) {
                    e.message();
                }
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3){
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1,time2;
        cin>>time1>>time2;

        try {
            mgt+=time1;
        } catch(InvalidTimeException& e) {
            e.message();
        }

        try {
            mgt+=time2;
        } catch(InvalidTimeException& e) {
            e.message();
        }

        cout<<mgt;
    }
    if (testCase == 4){
        cout <<"===== Testing - operator++ ======"<<endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes,n,numberLaps);
        float v,koef2;
        cout<<(mgt++).getNumberLaps()<<endl;
        cout<<mgt;
        mgt++;
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6){
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin>>newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin>>newBest;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace * pok= dynamic_cast<MotoGPRace *>(rArray[i]);
            if(pok!=0)
            {
                (*pok)++;
                try {
                    (*pok)+=newBest;
                } catch(InvalidTimeException& e) {
                    e.message();
                }
                if(flag==1)
                {
                    flag = 0;
                    try {
                        *pok+=1.4;
                    } catch(InvalidTimeException& e) {
                        e.message();
                    }

                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}