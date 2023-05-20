// 9 - 1

#include <iostream>
#include <cstring>
using namespace std;

class Employee {
protected:
    char* name;
    int age;

private:
    void copy_employee(const Employee& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->age = other.age;
    }

public:
    Employee() {
        this->name = new char[0];
        this->age = 0;
    }

    Employee(char* name, int years) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = years;
    }

    Employee(const Employee& other) {
        copy_employee(other);
    }

    Employee& operator=(const Employee& other) {
        if(this == &other) return *this;
        delete [] name;
        copy_employee(other);
        return *this;
    }

    virtual void displayInfo() = 0;

    virtual ~Employee() {
        delete [] name;
    }
};

class Payable {
protected:
    float salary;

public:
    Payable() {
        this->salary = 0;
    }

    Payable(float pay) {
        this->salary = pay;
    }

    Payable(const Payable& other) {
        this->salary = other.salary;
    }

    Payable& operator=(const Payable& other) {
        if(this == &other) return *this;
        this->salary = other.salary;
        return *this;
    }

    virtual float calculateSalary() = 0;

    virtual ~Payable() { }
};

class Developer : public Employee, public Payable {
    char* lang;

public:
    Developer() : Employee(), Payable() {
        this->lang = new char[0];
    }

    Developer(char* name, int age, float salary, char* lang) : Employee(name, age), Payable(salary) {
        this->lang = new char[strlen(lang) + 1];
        strcpy(this->lang, lang);
    }

    Developer(const Developer& other) : Employee(other), Payable(other) {
        this->lang = new char[strlen(other.lang) + 1];
        strcpy(this->lang, other.lang);
    }

    Developer& operator=(const Developer& other) {
        if(this == &other) return *this;
        Employee::operator=(other);
        Payable::operator=(other);
        delete [] lang;
        this->lang = new char[strlen(other.lang) + 1];
        strcpy(this->lang, other.lang);
        return *this;
    }

    float calculateSalary() {
        return salary - (salary * 0.1);
    }

    void displayInfo() {
        cout << "-- Developer Information --\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Salary: $" << calculateSalary() << "\n";
        cout << "Programming Language: " << lang << "\n";
    }

    ~Developer() {
        delete [] lang;
    }
};

class Manager : public Employee, public Payable {
    int deps;

public:
    Manager() {
        this->deps = 0;
    }

    Manager(char* name, int age, float salary, int deps) : Employee(name, age), Payable(salary) {
        this->deps = deps;
    }

    Manager(const Manager& other) : Employee(other), Payable(other) {
        this->deps = other.deps;
    }

    Manager& operator=(const Manager& other) {
        if(this == &other) return *this;
        Employee::operator=(other);
        Payable::operator=(other);
        this->deps = other.deps;
        return *this;
    }

    float calculateSalary() {
        return salary + ((salary * 0.05) * deps);
    }

    void displayInfo() {
        cout << "-- Manager Information --\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Salary: $" << calculateSalary() << "\n";
        cout << "Number of Departments: " << deps << "\n";
    }

    ~Manager() { }
};

double biggestSalary(Payable* payable[], int n) {
    Payable* maxSalaryEmployee = payable[0];

    for (int i = 1; i < n; i++) {
        if (payable[i]->calculateSalary() > maxSalaryEmployee->calculateSalary()) {
            maxSalaryEmployee = payable[i];
        }
    }

    return maxSalaryEmployee->calculateSalary();
}

int main()
{
    Payable* payable[5];
    Developer developers[5];
    Manager managers[5];
    int j=0, k=0;
    for(int i=0; i<5; i++)
    {
        char name[50];
        int age;
        double salary;
        cin>>name>>age>>salary;
        if(i%2==0)
        {
            char programmingLanguage[50];
            cin>>programmingLanguage;
            developers[j]=Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i]=&developers[j];
            j++;
        }
        else {
            int numberOfDepartments;
            cin>>numberOfDepartments;
            managers[k]=Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i]=&managers[k];
            k++;
        }
    }
    cout<<endl<<"Biggest Salary: "<<biggestSalary(payable, 5);
    return 0;
}
