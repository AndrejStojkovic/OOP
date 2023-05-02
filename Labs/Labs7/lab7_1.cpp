// 7 - 1

#include <iostream>
#include <cstring>
using namespace std;

class Kvadrat {
protected:
    double a;

public:
    Kvadrat() { this->a = 0; }
    Kvadrat(double a) { this->a = a; }
    Kvadrat(const Kvadrat& other) { this->a = other.a; }

    double getA() { return a; }
    void setA(double a) { this->a = a; }

    double perimetar() { return 4 * a; }
    double plostina() { return a * a; }

    virtual void pecati() {
        cout << "Kvadrat so dolzina a=" << a << " ima plostina P=" << plostina() << " i perimetar L=" << perimetar() << "\n";
    }
};

class Pravoagolnik : public Kvadrat { //da se vmetni nasleduvanjeto
private:
    double x;
    double y;

public:
    Pravoagolnik() : Kvadrat() { this->x = this->y = 0; }

    Pravoagolnik (Kvadrat &k, double x, double y) : Kvadrat(k) {
        this->x = x;
        this->y = y;
    }

    Pravoagolnik(const Pravoagolnik& other) : Kvadrat(other.a) {
        this->x = other.x;
        this->y = other.y;
    }

    double perimetar() { return 2 * (a + x) + 2 * (a + y); }
    double plostina() { return (a + x) * (a + y); }

    void pecati() {
        if(x == y) {
            this->a += x;
            Kvadrat::pecati();
            return;
        }

        cout << "Pravoagolnik so strani: " << (a + x) << " i " << (a + y);
        cout << " ima plostina P=" << plostina() << " i perimetar L=" << perimetar() << "\n";
    }
};

int main() {
    int n;
    double a,x,y;
    Kvadrat * kvadrati;
    Pravoagolnik * pravoagolnici;

    cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testiranje na klasata Kvadrat==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].pecati();
    }
    else {
        cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].pecati();
    }
}