// 3 - 1

#include <iostream>
#include <cstring>
using namespace std;

//YOUR CODE HERE

class MobilePhone {
    char model[20];
    int num;
    int year;

public:
    MobilePhone() {
        strcpy(this->model, " ");
        num = year = 0;
    }

    MobilePhone(char* model, int num, int year) {
        strcpy(this->model, model);
        this->num = num;
        this->year = year;
    }

    MobilePhone(const MobilePhone& other) {
        strcpy(this->model, other.model);
        this->num = other.num;
        this->year = other.year;
    }

    void print() {
        cout << model << " " << num << " release year: " << year << "\n";
    }

    ~MobilePhone() { }
};

class Owner {
    char name[20];
    char surname[20];
    MobilePhone phone;

public:
    Owner() {
        strcpy(this->name, " ");
        strcpy(this->surname, " ");
    }

    Owner(char* name, char* surname, MobilePhone phone) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->phone = phone;
    }

    void print() {
        cout << name << " " << surname << " has a mobile phone:\n";
        phone.print();
    }

    ~Owner() { }
};

//DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }

}
