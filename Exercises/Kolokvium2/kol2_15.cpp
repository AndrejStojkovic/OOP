// 2 - 15 (najglupa zadacha)

#include<iostream>
#include<string.h>
using namespace std;

class BadInputException {
public: static void message() { cout << "Greshna opisna ocenka\n"; }
};

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;

private:
    void copy_kurs(const StudentKurs &other) {
        strcpy(this->ime, other.ime);
        this->ocenka = other.ocenka;
        this->daliUsno = other.daliUsno;
    }

public:
    StudentKurs(char* ime, int finalenIspit){
        strcpy(this->ime, ime);
        this->ocenka = finalenIspit;
        this->daliUsno = false;
    }

    StudentKurs(const StudentKurs& other) {
        copy_kurs(other);
    }

    StudentKurs& operator=(const StudentKurs& other) {
        if(this == &other) return *this;
        copy_kurs(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, StudentKurs& kurs) {
        out << kurs.ime << " --- " << kurs.getOcenka() << "\n";
        return out;
    }

    static void setMAX(int val) { MAX = val; }

    char* getIme() { return ime; }
    void setIme(char* ime) { strcpy(this->ime, ime); }

    virtual int getOcenka() { return ocenka; }
    void setOcenka(int ocenka) { this->ocenka = ocenka; }

    bool getDaliUsno() { return daliUsno; }
    void setDaliUsno(bool daliUsno) { this->daliUsno = daliUsno; }

    ~StudentKurs() { }
};

//вметни го кодот за StudentKursUsno
class StudentKursUsno : public StudentKurs {
    char* opisna_ocenka;

public:
    StudentKursUsno(char* ime, int ocenka) : StudentKurs(ime, ocenka) {
        this->opisna_ocenka = new char[10];
        this->daliUsno = true;
    }

    StudentKursUsno(const StudentKursUsno& other) : StudentKurs(other) {
        this->opisna_ocenka = new char[10];
        strcpy(this->opisna_ocenka, other.opisna_ocenka);
        this->daliUsno = true;
    }

    StudentKurs& operator+=(char* oc) {
        for(int i = 0; i < strlen(oc); i++) {
            if(!isalpha(oc[i])) throw BadInputException();
        }

        delete [] opisna_ocenka;
        this->opisna_ocenka = new char[10];
        strcpy(this->opisna_ocenka, oc);
        return *this;
    }

    int getOcenka() {
        int kursOcena = StudentKurs::getOcenka(), add = 0;

        if(!strcmp(opisna_ocenka, "odlicen")) add = 2;
        else if(!strcmp(opisna_ocenka, "dobro")) add = 1;
        else if(!strcmp(opisna_ocenka, "losho")) add = -1;
        else return kursOcena;

        return kursOcena + add < MAX ? kursOcena + add : MAX;
    }

    ~StudentKursUsno() {
        delete [] opisna_ocenka;
    }
};

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    const static int MINOCENKA = 6;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }

    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    void pecatiStudenti() {
        cout << "Kursot " << naziv << " go polozile:\n";
        for(int i = 0; i < broj; i++) {
            if(studenti[i]->getOcenka() >= MINOCENKA) cout << *studenti[i];
        }
    }

    void postaviOpisnaOcenka(char *ime, char *opisnaOcenka) {
        for(int i = 0; i < broj; i++) {
            if(studenti[i]->getDaliUsno() && !strcmp(ime, studenti[i]->getIme()))
                *dynamic_cast<StudentKursUsno*>(studenti[i]) += opisnaOcenka;
        }
    }
};

int StudentKurs::MAX = 10;

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;

        try { programiranje.postaviOpisnaOcenka(ime,opisna); }
        catch(BadInputException) {
            BadInputException::message();
            char nova_opisna[10];
            int ct = 0;

            for(int j = 0; j < strlen(opisna); j++) {
                if(opisna[j] >= '0' && opisna[j] <= '9') continue;
                nova_opisna[ct++] = opisna[j];
            }

            nova_opisna[ct] = '\0';

            programiranje.postaviOpisnaOcenka(ime, nova_opisna);
        }

    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
