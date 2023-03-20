// 2 - 3

#include <iostream>
#include <cstring>
using namespace std;

class Country {
    char name[100];
    char capital[100];
    float area;
    float population;

public:
    Country() {
        strcpy(name, " ");
        strcpy(capital, " ");
        area = population = 0;
    }

    Country(char* name, char* capital, float area, float population) {
        strcpy(this->name, name);
        strcpy(this->capital, capital);
        this->area = area;
        this->population = population;
    }

    char* getName() {
        return name;
    }

    void setName(char* name) {
        strcpy(this->name, name);
    }

    char* getCapital() {
        return capital;
    }

    void setCapital(char* capital) {
        strcpy(this->capital, capital);
    }

    float getArea() {
        return area;
    }

    void setArea(float area) {
        this->area = area;
    }

    float getPopulation() {
        return population;
    }

    void setPopulation(float population) {
        this->population = population;
    }

    void display() {
        cout << "Country: " << name << "\nCapital: " << capital << "\n";
        cout << "Area: " << area << "\nPopulation: " << population << "\n";
    }

    ~Country() { }
};

void sortCountries(Country* countries, int n) {
    Country temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i; j < n; j++) {
            if(countries[i].getArea() > countries[j].getArea()) {
                temp = countries[i];
                countries[i] = countries[j];
                countries[j] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        countries[i].display();
    }
}

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> capital;
        cin >> area;
        cin>>population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> capital;
    cin >> area;
    cin>>population;
    countries[n-1].setName(name);
    countries[n-1].setCapital(capital);
    countries[n-1].setArea(area);
    countries[n-1].setPopulation(population);

    cout<<"-->Testing set methods and display()"<<endl;
    countries[n-1].display();
    cout<<endl;

    cout<<"-->Testing sortCountries()"<<endl;
    sortCountries(countries,n);
    return 0;
}