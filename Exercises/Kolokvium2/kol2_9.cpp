// 2 - 9

#include <iostream>
#include <cstring>
using namespace std;

class Exception {
public:
    static void message() {
        cout << "Ne moze da se vnese dadeniot trud\n";
    }
};

class Trud {
    char type;
    int year;

    void copy_trud(const Trud& other) {
        this->type = other.type;
        this->year = other.year;
    }
public:
    Trud() {
        this->type = 'A';
        this->year = 0;
    }

    Trud(char type, int year) {
        this->type = type;
        this->year = year;
    }

    Trud(const Trud& other) {
        copy_trud(other);
    }

    Trud& operator=(const Trud& other) {
        if(this == &other) {
            return *this;
        }
        copy_trud(other);
        return *this;
    }

    friend istream& operator>>(istream& in, Trud& t) {
        in >> t.type >> t.year;
        return in;
    }

    char getType() {
        return type;
    }

    int getYear() {
        return year;
    }

    ~Trud() { }
};

class Student {
protected:
    char name[30];
    int index;
    int inYear;
    int* grades;
    int n;

    void copy_student(const Student& other) {
        strcpy(this->name, other.name);
        this->index = other.index;
        this->inYear = other.inYear;
        this->grades = new int[other.n];
        for(int i = 0; i < other.n; i++) this->grades[i] = other.grades[i];
        this->n = other.n;
    }
public:
    Student() {
        strcpy(this->name, "name");
        this->index = this->inYear = this->n = 0;
        this->grades = nullptr;
    }

    Student(char* name, int index, int inYear, int* grades, int n) {
        strcpy(this->name, name);
        this->index = index;
        this->inYear = inYear;
        this->grades = new int[n];
        for(int i = 0; i < n; i++) {
            this->grades[i] = grades[i];
        }
        this->n = n;
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

    friend ostream& operator<<(ostream& out, Student& other) {
        out << other.index << " " << other.name << " " << other.inYear << " " << other.rang() << "\n";
        return out;
    }

    int getIndex() {
        return index;
    }

    virtual double rang() {
        double s = 0;
        for(int i = 0; i < n; i++) {
            s += grades[i];
        }
        return s / n;
    }

    ~Student() {
        delete [] grades;
    }
};

class PhDStudent : public Student {
    Trud* trudovi;
    int t_n;
    static int c;
    static int j;

    void copy_phdstudent(const PhDStudent& other) {
        this->trudovi = new Trud[other.t_n];
        for(int i = 0; i < t_n; i++) {
            this->trudovi[i] = other.trudovi[i];
        }
        this->t_n = other.t_n;
    }
public:
    PhDStudent() : Student() {
        this->trudovi = nullptr;
        this->t_n = 0;
    }

    PhDStudent(char* name, int index, int inYear, int* grades, int n, Trud* t, int t_n) : Student(name, index, inYear, grades, n) {
        this->trudovi = new Trud[t_n];
        for(int i = 0; i < t_n; i++) {
            try {
                t[i].getYear() < inYear ? throw Exception() : this->trudovi[i] = t[i];
            } catch(Exception& e) {
                e.message();
            }
        }
        this->t_n = t_n;
    }

    PhDStudent(const PhDStudent& other) : Student(other) {
        copy_phdstudent(other);
    }

    PhDStudent& operator=(const PhDStudent& other) {
        if(this == &other) {
            return *this;
        }
        Student::operator=(other);
        delete [] trudovi;
        copy_phdstudent(other);
        return *this;
    }

    PhDStudent& operator+=(Trud& trud) {
        if(trud.getYear() < inYear) {
            throw Exception();
        }

        Trud* tmp = new Trud[t_n + 1];
        for(int i = 0; i < t_n; i++) {
            tmp[i] = trudovi[i];
        }
        tmp[t_n++] = trud;

        delete [] trudovi;
        this->trudovi = new Trud[t_n];
        for(int i = 0; i < t_n; i++) {
            trudovi[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }

    static void setC(int _c) {
        c = _c;
    }

    static void setJ(int _j) {
        j = _j;
    }

    double rang() {
        double curr = Student::rang();
        for(int i = 0; i < t_n; i++) {
            if(tolower(trudovi[i].getType()) == 'c') {
                curr += c;
            } else if(tolower(trudovi[i].getType()) == 'j') {
                curr += j;
            }
        }
        return curr;
    }

    ~PhDStudent() {
        delete [] trudovi;
    }
};

int PhDStudent::c = 1;
int PhDStudent::j = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool found = false;

        try {
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                    found = true;
                }
            }
        } catch(Exception& e) {
            e.message();
        }

        if(!found) cout << "Ne postoi PhD student so indeks " << indeks << "\n";

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        try {
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                }
            }
        } catch(Exception& e) {
            e.message();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try {
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                }
            }
        } catch(Exception& e) {
            e.message();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6)
    {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}