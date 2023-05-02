// 7 - 2

#include <iostream>
#include <cstring>

using namespace std;

// YOUR CODE STARTS HERE
class Employee {
protected:
    char* name;
    int salary;
    int bonus;
    int exp;

private:
    void copy(const Employee& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->salary = other.salary;
        this->bonus = other.bonus;
        this->exp = other.exp;
    }

public:
    Employee() {
        this->name = new char[0];
        this->salary = this->bonus = this->exp = 0;
    }

    Employee(char* name, int salary, int bonus, int exp) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->salary = salary;
        this->bonus = bonus;
        this->exp = exp;
    }

    Employee(const Employee& other) {
        copy(other);
    }

    Employee& operator=(const Employee& other) {
        if(this == &other) return *this;
        delete [] name;
        copy(other);
        return *this;
    }

    char* getName() { return name; }
    void setName(char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    int getSalary() { return salary; }
    void setSalary(int salary) { this->salary = salary;}

    int getBonus() { return bonus; }
    void setBonus(int bonus) { this->bonus = bonus; }

    int getExperience() { return exp; }
    void setExperience(int exp) { this->exp = exp; }

    int getTotalSalary() { return salary + (bonus * exp); }

    void print() {
        cout << "Employee name: " << name << "\n";
        cout << "Salary: " << getTotalSalary() << "\n";
        cout << "Experience: " << exp << "\n";
    }

    ~Employee() {
        delete [] name;
    }
};

class Manager : public Employee {
    char* department;
    int managerBonus;

    void copy(const Manager& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->salary = other.salary;
        this->bonus = other.bonus;
        this->exp = other.exp;
        this->department = new char[strlen(other.department) + 1];
        strcpy(this->department, other.department);
        this->managerBonus = other.managerBonus;
    }

public:
    Manager() : Employee() {
        this->department = new char[2];
        strcpy(this->department, "a");
        this->managerBonus = 0;
    }

    Manager(char* name, int salary, int bonus, int exp, char* department, int managerBonus) : Employee(name, salary, bonus, exp) {
        this->department = new char[strlen(department) + 1];
        strcpy(this->department, department);
        this->managerBonus = managerBonus;
    }

    Manager(const Employee& employee, char* department, int managerBonus) : Employee(employee) {
        this->department = new char[strlen(department) + 1];
        strcpy(this->department, department);
        this->managerBonus = managerBonus;
    }

    Manager(const Manager& other) {
        copy(other);
    }

    Manager& operator=(const Manager& other) {
        if(this == &other) return *this;
        delete [] name;
        delete [] department;
        copy(other);
        return *this;
    }

    int getTotalManagerBonus() { return bonus + managerBonus; }
    int getTotalSalary() { return salary + (getTotalManagerBonus() * exp); }

    void print() {
        cout << "Manager name: " << name << "\n";
        cout << "Department: " << department << "\n";
        cout << "Salary: " << getTotalSalary() << "\n";
        cout << "Experience: " << exp << "\n";
    }

    ~Manager() {
        //delete [] name;
        delete [] department;
    }
};

//DO NOT EDIT THE MAIN FUNCTION

int main() {
    char name[20];
    int salary;
    int bonus;
    int experience;
    char department[50];
    int managerBonus;

    Employee * employees = new Employee[5];
    Manager * managers = new Manager[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "EMPLOYEES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> salary >> bonus >> experience;
            employees[i] = Employee(name, salary, bonus, experience);
            employees[i].print();
            cout<<endl;
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> salary >> bonus >> experience;
            cin >> department >> managerBonus;
            employees[i] = Employee(name, salary, bonus, experience);
            managers[i] = Manager(employees[i], department, managerBonus);
        }

        cout << "EMPLOYEES:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i) {
            employees[i].print();
            cout<<endl;
        }


        cout << "MANAGERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i) {
            managers[i].print();
            cout<<endl;
        }

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> salary >> bonus >> experience;
            cin >> department >> managerBonus;
            managers[i] = Manager(name, salary, bonus, experience, department, managerBonus);
        }
        cout << "MANAGERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i) {
            managers[i].print();
            cout<<endl;
        }

    }

    delete [] employees;
    delete [] managers;
}
