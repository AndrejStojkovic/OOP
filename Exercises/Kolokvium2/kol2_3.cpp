// 2 - 2

#include <iostream>
#include <cstring>
using namespace std;

class Kurs {
    char* name;
    int credits;

    void copy_kurs(const Kurs& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->credits = other.credits;
    }
public:
    Kurs() {
        this->name = new char[5];
        strcpy(this->name, "name");
        this->credits = 0;
    }

    Kurs(char* name, int credits) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->credits = credits;
    }

    Kurs(const Kurs& other) {
        copy_kurs(other);
    }

    Kurs& operator=(const Kurs& other) {
        if(this == &other) {
            return *this;
        }
        delete [] name;
        copy_kurs(other);
        return *this;
    }

    char* getCourseName() const {
        return name;
    }

    int getCourseCredits() const {
        return credits;
    }

    ~Kurs() {
        delete [] name;
    }
};

class NoCourseException {
    int index;

public:
    NoCourseException(int index) {
        this->index = index;
    }

    void message() {
        cout << "Demonstratorot so indeks " << index << " ne drzi laboratoriski vezbi\n";
    }
};

class Student {
    int* grades;
    int n;

    void copy_student(const Student& other) {
        this->index = other.index;
        this->n = other.n;
        this->grades = new int[n];
        for(int i = 0; i < n; i++) {
            this->grades[i] = other.grades[i];
        }
    }

protected:
    int index;

public:
    Student() {
        this->index = this->n = 0;
        this->grades = nullptr;
    }

    Student(int index, int* grades, int n) {
        this->index = index;
        this->n = n;
        this->grades = new int[n];
        for(int i = 0; i < n; i++) {
            this->grades[i] = grades[i];
        }
    }

    Student(const Student& other) {
        copy_student(other);
    }

    Student& operator=(const Student& other) {
        if(this == &other) {
            return *this;
        }
        delete [] grades;
        copy_student(other);
        return *this;
    }

    virtual int getBodovi() {
        float s = 0;
        for(int i = 0; i < n; i++) {
            if(grades[i] > 5) {
                s++;
            }
        }
        return (s / n) * 100;
    }

    virtual void pecati() {
        cout << index;
    }

    ~Student() {
        delete [] grades;
    }
};

class Predavach {
    Kurs* courses;
    int n;

    void copy_predavach(const Predavach& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->n = other.n;
        this->courses = new Kurs[other.n];
        for(int i = 0; i < other.n; i++) {
            this->courses[i] = other.courses[i];
        }
    }

protected:
    char* name;

public:
    Predavach() {
        this->name = new char[5];
        strcpy(this->name, "name");
        this->courses = nullptr;
        this->n = 0;
    }

    Predavach(char* name, Kurs* courses, int n) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->n = n;
        this->courses = new Kurs[n];
        for(int i = 0; i < n; i++) {
            this->courses[i] = courses[i];
        }
    }

    Predavach(const Predavach& other) {
        copy_predavach(other);
    }

    Predavach& operator=(const Predavach& other) {
        if(this == &other) {
            return *this;
        }
        delete [] name;
        delete [] courses;
        copy_predavach(other);
        return *this;
    }

    Kurs* getCourses() const {
        return courses;
    }

    int getNumberOfCourses() const {
        return n;
    }

    virtual void pecati() {
        cout << "(";
        for(int i = 0; i < n; i++) {
            cout << courses[i].getCourseName() << " " << courses[i].getCourseCredits() << "ECTS";
            if(i != n - 1) {
                cout << ", ";
            }
        }
        cout << ")";
    }

    ~Predavach() {
        delete [] name;
        delete [] courses;
    }
};

class Demonstrator : public Student, public Predavach {
    int hours;

public:
    Demonstrator() : Student(), Predavach() {
        this->hours = 0;
    }

    Demonstrator(int index, int* grades, int grades_n, char* name, Kurs* courses, int courses_n, int hours) :
            Student(index, grades, grades_n), Predavach(name, courses, courses_n) {
        this->hours = hours;
    }

    int getBodovi() {
        if(getNumberOfCourses() <= 0) {
            throw NoCourseException(index);
        }
        return Student::getBodovi() + (20 * hours) / getNumberOfCourses();
    }

    void pecati() {
        Student::pecati();
        cout << ": " << name << " ";
        Predavach::pecati();
    }

    ~Demonstrator() { }
};

Student& vratiNajdobroRangiran(Student** studenti, int n) {
    int idx = 0;

    for(int i = 0; i < n; i++) {
        try {
            idx = studenti[i]->getBodovi() > studenti[idx]->getBodovi() ? i : idx;
        } catch(NoCourseException &e) {
            e.message();
        }
    }

    return *studenti[idx];
}

void pecatiDemonstratoriKurs(char* kurs, Student** studenti, int n) {
    for(int i = 0; i < n; i++) {
        if(!dynamic_cast<Demonstrator*>(studenti[i])) {
            continue;
        }

        for(int j = 0; j < dynamic_cast<Demonstrator*>(studenti[i])->getNumberOfCourses(); j++) {
            if(strcmp(kurs, dynamic_cast<Demonstrator*>(studenti[i])->getCourses()[j].getCourseName()) == 0) {
                studenti[i]->pecati();
                cout << "\n";
                break;
            }
        }
    }
}

int main(){

    Kurs kursevi[10];
    int indeks,brojKursevi, ocenki[20],ocenka,brojOcenki,tip,brojCasovi,krediti;
    char ime[20],imeIPrezime[50];

    cin>>tip;

    if (tip==1) //test class Demonstrator
    {
        cout<<"-----TEST Demonstrator-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        cout<<"Objekt od klasata Demonstrator e kreiran";

    } else if (tip==2) //funkcija pecati vo Student
    {
        cout<<"-----TEST pecati-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }

        Student s(indeks,ocenki,brojOcenki);
        s.pecati();

    } else if (tip==3) //funkcija getVkupnaOcenka vo Student
    {
        cout<<"-----TEST getVkupnaOcenka-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        Student s(indeks,ocenki,brojOcenki);
        cout<<"Broj na bodovi: "<<s.getBodovi()<<endl;

    } else if (tip==4) //funkcija getVkupnaOcenka vo Demonstrator
    {
        cout<<"-----TEST getVkupnaOcenka-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        cout<<"Broj na bodovi: "<<d.getBodovi()<<endl;

    } else if (tip==5) //funkcija pecati vo Demonstrator
    {
        cout<<"-----TEST pecati -----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        d.pecati();

    } else if (tip==6) //site klasi
    {
        cout<<"-----TEST Student i Demonstrator-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Student *s=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        s->pecati();
        cout<<"\nBroj na bodovi: "<<s->getBodovi()<<endl;
        delete s;


    } else if (tip==7) //funkcija vratiNajdobroRangiran
    {
        cout<<"-----TEST vratiNajdobroRangiran-----"<<endl;
        int k, opt;
        cin>>k;
        Student **studenti=new Student*[k];
        for (int j=0;j<k;j++){
            cin>>opt; //1 Student 2 Demonstrator
            cin>>indeks>>brojOcenki;
            for (int i=0;i<brojOcenki;i++)
            {
                cin>>ocenka;
                ocenki[i]=ocenka;
            }
            if (opt==1){
                studenti[j]=new Student(indeks,ocenki,brojOcenki);
            }else{
                cin>>imeIPrezime>>brojKursevi;
                for (int i=0;i<brojKursevi;i++){
                    cin>>ime>>krediti;
                    kursevi[i]=Kurs(ime,krediti);
                }
                cin>>brojCasovi;
                studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
            }
        }
        Student& najdobar=vratiNajdobroRangiran(studenti,k);
        cout<<"Maksimalniot broj na bodovi e:"<<najdobar.getBodovi();
        cout<<"\nNajdobro rangiran:";
        najdobar.pecati();

        for (int j=0;j<k;j++) delete studenti[j];
        delete [] studenti;
    } else if (tip==8) //funkcija pecatiDemonstratoriKurs
    {
        cout<<"-----TEST pecatiDemonstratoriKurs-----"<<endl;
        int k, opt;
        cin>>k;
        Student **studenti=new Student*[k];
        for (int j=0;j<k;j++){
            cin>>opt; //1 Student 2 Demonstrator
            cin>>indeks>>brojOcenki;
            for (int i=0;i<brojOcenki;i++)
            {
                cin>>ocenka;
                ocenki[i]=ocenka;
            }
            if (opt==1){
                studenti[j]=new Student(indeks,ocenki,brojOcenki);
            }else{
                cin>>imeIPrezime>>brojKursevi;
                for (int i=0;i<brojKursevi;i++)
                {
                    cin>>ime>>krediti;
                    kursevi[i]=Kurs(ime,krediti);
                }
                cin>>brojCasovi;
                studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
            }
        }
        char kurs[20];
        cin>>kurs;
        cout<<"Demonstratori na "<<kurs<<" se:"<<endl;
        pecatiDemonstratoriKurs (kurs,studenti,k);
        for (int j=0;j<k;j++) delete studenti[j];
        delete [] studenti;

    }


    return 0;
}