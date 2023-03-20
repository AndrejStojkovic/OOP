// 2 - 2

#include <iostream>
#include <cstring>
using namespace std;

class Film {
    char name[100];
    float rating;
    float revenue;

public:
    Film() {
        strcpy(name, " ");
        rating = revenue = 0;
    }

    Film(char* name, float rating, float revenue) {
        strcpy(this->name, name);
        this->rating = rating;
        this->revenue = revenue;
    }

    char* getName() {
        return name;
    }

    void setName(char* name) {
        strcpy(this->name, name);
    }

    float getRating() {
        return rating;
    }

    void setRating(float rating) {
        this->rating = rating;
    }

    float getRevenue() {
        return revenue;
    }

    void setRevenue(float revenue) {
        this->revenue = revenue;
    }

    void display() {
        cout << "Name of film: " << name << "\n";
        cout << "Rating: " << rating << "\n";
        cout << "Revenue: " << revenue << "\n";
    }

    ~Film() { }
};

void printMostPopularFilm(Film* films, int n) {
    int idx = -1, max_revenue = -1;

    for(int i = 0; i < n; i++) {
        if(films[i].getRevenue() > max_revenue) {
            max_revenue = films[i].getRevenue();
            idx = i;
        }
    }

    films[idx].display();
}

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> rating;
    cin >> revenue;
    films[n-1].setName(name);
    films[n-1].setRating(rating);
    films[n-1].setRevenue(revenue);

    cout<<"-->Testing set methods and display()"<<endl;
    films[n-1].display();
    cout<<endl;

    cout<<"-->Testing printMostPopularFilm()"<<endl;
    printMostPopularFilm(films , n);
    return 0;
}