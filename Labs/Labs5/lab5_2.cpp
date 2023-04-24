// 5 - 2

#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
    char reg[9];
    char* name;
    int location;
    int passengers;
    int km;

public:
    Vehicle() {
        strcpy(this->reg, "0");
        this->name = new char[2];
        strcpy(this->name, " ");
        this->location = this->passengers = this->km = 0;
    }

    Vehicle(char* reg, char* name, int location, int passengers) {
        strcpy(this->reg, reg);
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->location = location;
        this->passengers = passengers;
        this->km = 0;
    }

    Vehicle(const Vehicle& other) {
        strcpy(this->reg, other.reg);
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->location = other.location;
        this->passengers = other.passengers;
        this->km = other.km;
    }

    Vehicle& operator=(const Vehicle& other) {
        if(this == &other) return* this;

        strcpy(this->reg, other.reg);
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->location = other.location;
        this->passengers = other.passengers;
        this->km = other.km;

        return* this;
    }

    char* getID() { return reg; }
    void setID(char* reg) { strcpy(this->reg, reg); }

    bool sporedi(char* other) const {
        return strcmp(this->reg, other) == 0;
    }

    int distance (int area) const{
        return abs(this->location - area);
    }

    bool compare(Vehicle& other, int area) {
        if (this->distance(area) < other.distance(area)){
            return true;
        } else if (this->distance(area) == other.distance(area)) {
            return this->km < other.km;
        }

        return false;
    }

    void setLocation(int area) {
        this->location = area;
    }

    void addKms(int distance) {
        this->km += distance;
    }

    void print() {
        cout << "ID: " << reg << " ";
        cout << "Driver's name: " << name << " ";
        cout << "Passenger capacity: " << passengers << " ";
        cout << "Location: " << location << " ";
        cout << "kms driven: " << km << "\n";
    }

    ~Vehicle() {
        delete [] name;
    }

    friend class RideApp;
};

class RideApp {
    char name[20];
    Vehicle* vehicles;
    int n;

public:
    RideApp() {
        strcpy(this->name, "abc");
        this->vehicles = new Vehicle[0];
        this->n = 0;
    }

    RideApp(char* name) {
        strcpy(this->name, name);
        this->vehicles = new Vehicle[0];
        this->n = 0;
    }

    RideApp(const RideApp& other) {
        strcpy(this->name, other.name);
        this->vehicles = new Vehicle[other.n];
        for(int i = 0; i < other.n; i++) this->vehicles[i] = other.vehicles[i];
        this->n = other.n;
    }

    RideApp& operator=(const RideApp& other) {
        if(this == &other) return *this;

        strcpy(this->name, other.name);
        this->vehicles = new Vehicle[other.n];
        for(int i = 0; i < other.n; i++) this->vehicles[i] = other.vehicles[i];
        this->n = other.n;

        return *this;
    }

    void signUpVehicle(const Vehicle& vehicle) {
        for(int i = 0; i < n; i++) {
            if(vehicle.sporedi(vehicles[i].getID())) return;
        }

        Vehicle* tmp = new Vehicle[n + 1];

        for(int i = 0; i < n; i++) tmp[i] = vehicles[i];
        tmp[n++] = vehicle;

        delete [] vehicles;

        vehicles = new Vehicle[n];
        for(int i = 0; i < n; i++) vehicles[i] = tmp[i];

        delete [] tmp;
    }

    void addRide (int area, int passengers, int distanceKm) {
        int idx = -1;
        for (int i = 0; i < n; i++){
            if (vehicles[i].passengers >= passengers){
                if (idx == -1 || vehicles[i].compare(vehicles[idx], area)){
                    idx = i;
                }
            }
        }

        vehicles[idx].setLocation(area);
        vehicles[idx].addKms(distanceKm);
    }

    void print() {
        cout << name << "\n";
        if(n <= 0) { cout << "EMPTY\n"; return; }
        for(int i = 0; i < n; i++) vehicles[i].print();
    }

    ~RideApp() {
        delete [] vehicles;
    }
};

int main () {
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "CONSTRUCTOR Vehicle" << endl;
        Vehicle vehicle("NE1234SA", "Stefan", 5, 4);
        vehicle.print();
        cout << "CONSTRUCTOR Vehicle OK" << endl;
    } else if (testCase == 2) {
        cout << "COPY-CONSTRUCTOR Vehicle" << endl;
        Vehicle vehicle = Vehicle("NE1234SA", "Stefan", 5, 4);
        vehicle.print();
        cout << "COPY-CONSTRUCTOR Vehicle OK" << endl;
    } else if (testCase == 3) {
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = Vehicle" << endl;
        Vehicle vehicle;
        Vehicle vehicle2("NE1234SA", "Stefan", 5, 4);
        vehicle = vehicle2;
        vehicle.print();
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = Vehicle OK" << endl;
    } else if (testCase == 4) {
        cout << "CONSTRUCTOR RideApp" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        app.print();
        cout << "CONSTRUCTOR RideApp OK" << endl;
    } else if (testCase == 5) {
        cout << "RideApp signUpVehicle test" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        int n;
        cin >> n;
        char ID[9];
        char name[20];
        int location;
        int capacity;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location >> capacity;
            app.signUpVehicle(Vehicle(ID, name, location, capacity));
        }
        app.print();
    } else if (testCase == 6) {
        cout << "RideApp addRide test" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        int capacity;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location >> capacity;
            app.signUpVehicle(Vehicle(ID, name, location, capacity));
        }
        cin >> n;
        for (int i=0;i<n;i++){
            int area, passengers, kms;
            cin >> area >> passengers >> kms;
            app.addRide(area, passengers, kms);
        }

        app.print();
    }
    return 0;
}
