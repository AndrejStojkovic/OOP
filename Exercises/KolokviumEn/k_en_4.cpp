// En - 4

#include <iostream>
#include <cstring>
using namespace std;

class Cinema {
    char name[20];
    int number;
    static float discount;
    float ticketPrice;

    void copy_cinema(const Cinema& other) {
        strcpy(this->name, other.name);
        this->number = other.number;
        this->ticketPrice = other.ticketPrice;
    }

public:
    Cinema() {
        strcpy(this->name, "cinema");
        this->number = 0;
        this->ticketPrice = 0;
    }

    Cinema(char* name, int number, float ticketPrice) {
        strcpy(this->name, name);
        this->number = number;
        this->ticketPrice = ticketPrice;
    }

    Cinema(const Cinema& other) {
        copy_cinema(other);
    }

    Cinema& operator=(const Cinema& other) {
        if(this == &other) {
            return *this;
        }

        copy_cinema(other);
        return *this;
    }

    static void setStudentDiscount(float _discount) {
        discount = _discount;
    }

    virtual float price(bool isStudent = false) {
        return isStudent ? ticketPrice - (discount * ticketPrice) : ticketPrice;
    }
    
    char* getname() {
        return name;
    }

    float getTicketPrice() {
        return ticketPrice;
    }

    float getStudentDiscount() {
        return discount;
    }

    ~Cinema() { }
};

class ThreeDCinema : public Cinema {
    char* movie;
    float duration;
    bool isPremiere;

    void copy_3d(const ThreeDCinema& other) {
        this->movie = new char[strlen(other.movie) + 1];
        strcpy(this->movie, other.movie);
        this->duration = other.duration;
        this->isPremiere = other.isPremiere;
    }

public:
    ThreeDCinema() : Cinema() {
        this->movie = new char[0];
        this->duration = 0;
        this->isPremiere = false;
    }

    ThreeDCinema(char* name, int number, float ticketPrice, char* movie, float duration, bool isPremiere) : Cinema(name, number, ticketPrice) {
        this->movie = new char[strlen(movie) + 1];
        strcpy(this->movie, movie);
        this->duration = duration;
        this->isPremiere = isPremiere;
    }

    ThreeDCinema(const ThreeDCinema& other) : Cinema(other) {
        copy_3d(other);
    }

    ThreeDCinema& operator=(const ThreeDCinema& other) {
        if(this == &other) {
            return *this;
        }

        Cinema::operator=(other);
        delete [] movie;
        copy_3d(other);
        return *this;
    }

    float price(bool isStudent = false) {
        float s = Cinema::price(isStudent);

        if(duration > 3.0) {
            s += 70;
        } else if(duration > 2.5) {
            s += 50;
        }

        if(isPremiere) {
            s += 60;
        }

        return s;
    }

    ~ThreeDCinema() {
        delete [] movie;
    }
};

float Cinema::discount = 0.17;

bool searchCinema(Cinema** c, int n, char* title, bool premiere, bool isStudent) {
    for(int i = 0; i < n; i++) {
        if(premiere && dynamic_cast<ThreeDCinema*>(c[i])) {
            ThreeDCinema nc = *dynamic_cast<ThreeDCinema*>(c[i]);

            if(!strcmp(nc.getname(), title)) {
                cout << title << " " << nc.price(isStudent) << "\n";
                return true;
            }
        } else {
            if(!strcmp(c[i]->getname(), title)) {
                cout << title << " " << c[i]->price(isStudent) << "\n";
                return true;
            }
        }
    }

    return false;
}

void cheapestCinema(Cinema** halls, int n, bool isStudent) {
    int a = 0, idx = -1;

    for(int i = 0; i < n; i++) {
        if(idx == -1 || halls[i]->price(isStudent) < halls[idx]->price(isStudent)) {
            idx = i;
        }

        if(dynamic_cast<ThreeDCinema*>(halls[i])) {
            a++;
        }
    }

    cout << "Cheapest movie hall: " << halls[idx]->getname() << " " << halls[idx]->price(isStudent) << "\n";
    cout << "3D cinema halls: " << a << " from total " << n << "\n";
}

int main(){

    int tip,n;
    char name[100], movieName[40];
    int no;
    bool premiere;
    float ticketPrice;
    float hours;
    bool isStudent;

    cin>>tip;
    if (tip==1){//Cinema
        cin>>name>>no>>ticketPrice;
        Cinema k1(name,no,ticketPrice);
        cout<<"Cinema created with name: "<<k1.getname()<<endl;
    }
    else if (tip==2){//price - Cinema
        cin>>name>>no>>ticketPrice>>isStudent;
        Cinema k1(name,no,ticketPrice);
        cout<<"Initial price for the cinema with name "<<k1.getname()<< " is: " <<k1.price(isStudent)<<endl;
    }
    else if (tip==3){//3D Cinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"Cinema created with name "<<s.getname()<<" and discount "<<s.getStudentDiscount()<<endl;
    }
    else if (tip==4){//price - 3DCinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere>>isStudent;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"The price for the cinema "<<s.getname()<<" is: "<<s.price(isStudent)<<endl;
    }
    else if (tip==5) {//cheapest Cinema
        Cinema ** halls = new Cinema *[5];
        int n;
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Home",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        cheapestCinema(halls,5,true);
    }
    else if (tip==6){//search
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);

        if(searchCinema(halls,5, "Milenium3D",true,true))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

        if(searchCinema(halls,5, "CinePlexx1",false,false))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

    }
    else if (tip==7){//change price
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Domasno",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        halls[2] -> setStudentDiscount(0.9);
        cheapestCinema(halls,4,true);
    }

    return 0;
}