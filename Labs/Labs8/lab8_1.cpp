// 8 - 1

#include <iostream>
#include <cstring>
using namespace std;

class Room {
public:
    Room() { }
    virtual void displayRoomInfo() = 0;
    virtual void displayRoomPrice() = 0;
    virtual ~Room() { }
};

class StandardRoom : public Room {
    bool hasBathroom;

public:
    StandardRoom() { this->hasBathroom = false; }

    StandardRoom(bool hasBathroom) { this->hasBathroom = hasBathroom; }

    void displayRoomInfo() {
        cout << "This is a standard room with a queen-sized bed";
        if(hasBathroom) cout << " and a bathroom";
        cout << ".\n";
    }

    void displayRoomPrice() {
        cout << "The price for a standard room is $" << (hasBathroom ? "100" : "80") << " per night.\n";
    }
};

class DeluxeRoom : public Room {
    bool hasBalcony;

public:
    DeluxeRoom() { this->hasBalcony = false; }

    DeluxeRoom(bool hasBalcony) { this->hasBalcony = hasBalcony; }

    void displayRoomInfo() {
        cout << "This is a deluxe room with a king-sized bed, a bathroom, a mini-fridge";
        if(hasBalcony) cout << " and a balcony";
        cout << ".\n";
    }

    void displayRoomPrice() {
        cout << "The price for a deluxe room is $" << (hasBalcony ? "200" : "160") << " per night.\n";
    }
};

int main() {
    Room* rooms[5];

    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "TEST CASE 1: TESTING STANDARD ROOM CLASS" << endl;

        for (int i = 0; i < 5; i++) {
            rooms[i] = new StandardRoom();
            rooms[i]->displayRoomInfo();
            rooms[i]->displayRoomPrice();
        }
    } else if (testCase == 2) {
        cout << "TEST CASE 2: TESTING DELUXE ROOM CLASS" << endl;
        for (int i = 0; i < 5; i++) {
            rooms[i] = new DeluxeRoom();
            rooms[i]->displayRoomInfo();
            rooms[i]->displayRoomPrice();
        }
    } else {
        cout << "TEST CASE 3: TESTING BOTH CLASSES" << endl;
        for (int i = 0; i < 5; i++) {
            if (i % 2) {
                bool hasBalcony;
                cin >> hasBalcony;
                rooms[i] = new DeluxeRoom(hasBalcony);
            }
            else {
                bool hasBathroom;
                cin >> hasBathroom;
                rooms[i] = new StandardRoom(hasBathroom);
            }
            rooms[i]->displayRoomInfo();
            rooms[i]->displayRoomPrice();
        }
    }

    return 0;
}