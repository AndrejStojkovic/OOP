// 9 - 2

#include <iostream>
#include <cstring>
using namespace std;

class Athlete {
protected:
    char* name;
    int age;

private:
    void copy_athlete(const Athlete& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->age = other.age;
    }

public:
    Athlete() {
        this->name = new char[0];
        this->age = 0;
    }

    Athlete(char* name, int age) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
    }

    Athlete(const Athlete& other) {
        copy_athlete(other);
    }

    Athlete& operator=(const Athlete& other) {
        if(this == &other) return *this;
        copy_athlete(other);
        return *this;
    }

    virtual void displayInfo() {
        cout << "Athlete: " << name << "\n";
        cout << "Age: " << age << "\n";
    }

    virtual ~Athlete() {
        delete [] name;
    }
};

class Runner : public Athlete {
protected:
    double speed;

public:
    Runner() : Athlete() {
        this->speed = 0;
    }

    Runner(char* name, int age, double speed) : Athlete(name, age) {
        this->speed = speed;
    }

    Runner(const Runner& other) : Athlete(other) {
        this->speed = other.speed;
    }

    Runner& operator=(const Runner& other) {
        if(this == &other) return *this;
        Athlete::operator=(other);
        this->speed = other.speed;
        return *this;
    }

    double getSpeed() { return speed; }

    void displayInfo() {
        Athlete::displayInfo();
        cout << "Speed: " << speed << " mph" << "\n";
    }

    virtual ~Runner() { }
};

class Jumper : public Athlete {
protected:
    double height;

public:
    Jumper() : Athlete() {
        this->height = 0;
    }

    Jumper(char* name, int age, double height) : Athlete(name, age) {
        this->height = height;
    }

    Jumper(const Jumper& other) : Athlete(other) {
        this->height = other.height;
    }

    Jumper& operator=(const Jumper& other) {
        if(this == &other) return *this;
        Athlete::operator=(other);
        this->height = height;
        return *this;
    }

    double getHeight() { return height; }

    void displayInfo() {
        Athlete::displayInfo();
        cout << "Height: " << height << "m" << "\n";
    }

    virtual ~Jumper() { }
};

class AllRoundAthlete : public Runner, public Jumper {
    int stamina;

public:
    AllRoundAthlete() : Runner(), Jumper() {
        this->stamina = 0;
    }

    AllRoundAthlete(char* name, int age, double speed, double height, int stamina) : Runner(name, age, speed), Jumper(name, age, height) {
        this->stamina = stamina;
    }

    AllRoundAthlete(const AllRoundAthlete& other) : Runner(other), Jumper(other) {
        this->stamina = other.stamina;
    }

    AllRoundAthlete& operator=(const AllRoundAthlete& other) {
        if(this == &other) return *this;
        Runner::operator=(other);
        Jumper::operator=(other);
        this->stamina = other.stamina;
        return *this;
    }

    void displayInfo() {
        Runner::displayInfo();
        cout << "Height: " << height << "m" << "\n";
        cout << "Stamina: " << stamina << "\n";
    }

    ~AllRoundAthlete() { }
};

Athlete* findAthleteWithMaxValue(Athlete** athletes, int n) {
    int idx = -1;
    double max_val = -1;

    for(int i = 0; i < n; i++) {
        double new_val = 0;

        if(dynamic_cast<Runner*>(athletes[i]))
            new_val = dynamic_cast<Runner*>(athletes[i])->getSpeed();
        else if(dynamic_cast<Jumper*>(athletes[i]))
            new_val = dynamic_cast<Jumper*>(athletes[i])->getHeight();

        if(idx == -1 || new_val > max_val) {
            max_val = new_val;
            idx = i;
        }
    }

    if(idx == -1) return nullptr;

    return athletes[idx];
}

int main() {
    char name[50];
    int age;
    double speed;
    double height;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>name;
        cin>>age;
        AllRoundAthlete allRoundAthlete(name, age, 13.6, 1.80, 6);
        allRoundAthlete.displayInfo();
    }
    else {

        cin >> n;

        Athlete **athletes = new Athlete *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> name >> age >> speed;

                athletes[i] = new Runner(name, age, speed);
            } else {
                cin >> name >> age >> height;

                athletes[i] = new Jumper(name, age, height);
            }

        }

        findAthleteWithMaxValue(athletes, n)->displayInfo();

    }


    return 0;
    
}