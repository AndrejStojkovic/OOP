// 8 - 2

#include <iostream>
#include <cstring>
using namespace std;

class FoodItem {
protected:
    char* type;
    int num;

public:
    FoodItem() {
        this->type = new char[0];
        this->num = 0;
    }

    FoodItem(char* type, int num) {
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
        this->num = num;
    }

    char* getType() { return type; }
    int getNum() { return num; }

    virtual int getPrice() = 0;
    virtual int getTime() = 0;

    virtual ~FoodItem() {
        delete [] type;
    }
};

class Pizza : public FoodItem {
    char* dough;

public:
    Pizza() : FoodItem() {
        this->dough = new char[0];
    }

    Pizza(char* type, int num, char* dough) : FoodItem(type, num) {
        this->dough = new char[strlen(dough) + 1];
        strcpy(this->dough, dough);
    }

    int getPrice() {
        int s = 0;
        if(!strcmp(this->dough, "wholeWheat")) s = 250;
        if(!strcmp(this->dough, "glutenFree")) s = 350;
        return s * num;
    }

    int getTime() {
        return 25;
    }

    ~Pizza() {
        delete [] dough;
    }
};

class Steak : public FoodItem {
    bool cooked;

public:
    Steak() : FoodItem() {
        this->cooked = false;
    }

    Steak(char* type, int num, bool cooked) : FoodItem(type, num) {
        this->cooked = cooked;
    }

    int getPrice() {
        return 1300 * num;
    }

    int getTime() {
        return cooked ? 20 : 15;
    }

    ~Steak() { }
};

FoodItem* getMaxFoodItem(FoodItem* pItem[], int n) {
    int idx = -1;

    for(int i = 0; i < n; i++) {
        if(idx == -1 || pItem[i]->getPrice() > pItem[idx]->getPrice())
            idx = i;
    }

    return pItem[idx];
}

int main() {
    FoodItem *p;
    int n;
    cin>>n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i <n; ++i) {
        cin>>type;
        cin>>size;


        if(strcmp(type, "pizza")==0 ) {
            cin>>dough;
            items[i] = new Pizza(type, size, dough);
        }else{
            cin>>cooked;
            items[i] = new Steak(type, size, cooked);
        }


    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout<<"Type: "<<it->getType()<<endl;
    cout<<"The max price is: "<<it->getPrice()<<endl;
    cout<<"Time to cook: "<<it->getTime();
    return 0;
}