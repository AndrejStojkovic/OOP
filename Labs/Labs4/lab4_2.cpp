// 4 - 2

#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;

class Student {
    char* name;
    int age;
    char* major;

public:
    Student() {
        this->name = new char[MAX];
        strcpy(this->name, " ");
        this->age = 0;
        this->major = new char[MAX];
        strcpy(this->major, " ");
    }

    Student(char* name, int age, char* major) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
        this->major = new char[strlen(major) + 1];
        strcpy(this->major, major);
    }

    Student(const Student& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->age = other.age;
        this->major = new char[strlen(other.major) + 1];
        strcpy(this->major, other.major);
    }

    Student operator=(const Student& other) {
        if(this == &other) return *this;

        strcpy(this->name, other.name);
        this->age = other.age;
        this->major = new char[strlen(other.major) + 1];
        strcpy(this->major, other.major);

        return *this;
    }

    char* getName() { return name; }
    void setName(char* name) { this->name = name; }

    int getAge() { return age; }
    void setAge(int age) { this->age = age; }

    char* getMajor() { return major; }
    void setMajor(char* major) { this->major = major; }

    void print() {
        cout << name << " (" << age << ", " << major << ")\n";
    }

    ~Student() {
        delete [] name;
        delete [] major;
    }
};

class Classroom {
    Student* students;
    int numStudents;
    int capacity;

public:
    Classroom() {
        this->students = new Student[MAX];
        numStudents = 0;
        capacity = MAX;
    }

    Classroom(Student* students, int numStudents, int capacity) {
        this->students = new Student[numStudents];
        for(int i = 0; i < numStudents; i++) this->students[i] = students[i];
        this->numStudents = numStudents;
        this->capacity = capacity;
    }

    Classroom(const Classroom& other) {
        this->students = new Student[other.numStudents];
        for(int i = 0; i < other.numStudents; i++) this->students[i] = other.students[i];
        this->numStudents = other.numStudents;
        this->capacity = other.capacity;
    }

    Classroom operator=(const Classroom& other) {
        if(this == &other) return *this;

        for(int i = 0; i < other.numStudents; i++) this->students[i] = other.students[i];
        this->numStudents = other.numStudents;
        this->capacity = other.capacity;

        return *this;
    }

    Student* getStudents() { return students; }

    void setNumStudents(int numStudents) { this->numStudents = numStudents; }
    int getNumStudents() { return numStudents; }

    void setCapacity(int capacity) { this->capacity = capacity; }
    int getCapacity() { return capacity; }

    void add(Student student) {
        if(numStudents >= capacity) return;
        students[numStudents++] = student;
    }

    void remove(char* name) {
        int idx = -1;
        for(int i = 0; i < numStudents; i++) {
            if(strcmp(students[i].getName(), name) == 0) {
                idx = i;
                break;
            }
        }

        if(idx == -1) return;

        for(int i = idx; i < numStudents - 1; i++) {
            students[i] = students[i + 1];
        }

        numStudents--;
    }

    void printStudents() {
        for(int i = 0; i < numStudents; i++) students[i].print();
        cout << "\n";
    }

    ~Classroom() {
        delete [] students;
    }
};

double findMedianAge(Classroom classroom) {
    Student* students = classroom.getStudents();
    int mid = classroom.getNumStudents() / 2;
    double median = students[mid].getAge();
    return classroom.getNumStudents() % 2 ? median : (median + students[mid - 1].getAge()) / 2.0;
}

//DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;

    // Testing remove method
    cout << "After removing the elements:\n";
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}

