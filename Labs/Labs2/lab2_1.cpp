// 2 - 1

#include <iostream>
#include <cstring>
using namespace std;

class BasketballPlayer {
    char name[20];
    char surname[20];
    int num;
    int points[3];

public:
    BasketballPlayer() {
        strcpy(this->name, " ");
        strcpy(this->surname, " ");
        num = 0;
        for(int i = 0; i < 3; i++) points[i] = 0;
    }

    BasketballPlayer(char* name, char* surname, int num, int points[3]) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->num = num;
        for(int i = 0; i < 3; i++) this->points[i] = points[i];
    }

    char* getName() {
        return name;
    }

    void setName(char* name) {
        strcpy(this->name, name);
    }

    char* getSurname() {
        return surname;
    }

    void setSurname(char* surname) {
        strcpy(this->surname, surname);
    }

    int getNum() {
        return num;
    }

    void setNum(int num) {
        this->num = num;
    }

    int* getPoints() {
        return points;
    }

    void setPoints(int* points) {
        for(int i = 0; i < 3; i++) this->points[i] = points[i];
    }

    float avg_pts() {
        return (points[0] + points[1] + points[2]) / 3.0;
    }

    void print() {
        cout << "Player: " << name << " " << surname << " with number: " << num << " ";
        cout << "has " << avg_pts() << " points on average\n";
    }

    ~BasketballPlayer() { }
};

int main() {
    char name[20], surname[20];
    int num, points[3];

    cin >> name >> surname >> num;
    for(int i = 0; i < 3; i++) cin >> points[i];

    BasketballPlayer player = BasketballPlayer(name, surname, num, points);
    player.print();

    return 0;
}