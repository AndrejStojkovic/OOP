// En - 11

// En - 12 (text not right, needs to be fixed)

#include <iostream>
#include <cstring>
using namespace std;

class InvestmentPlan {
protected:
    char name[80];
    double plan;
    double shares;
    bool currentDay;

private:
    void copy_plan(const InvestmentPlan& other) {
        strcpy(this->name, other.name);
        this->plan = other.plan;
        this->shares = other.shares;
        this->currentDay = other.currentDay;
    }

public:
    InvestmentPlan() {
        strcpy(this->name, "name");
        this->plan = this->shares = 0;
        this->currentDay = 0;
    }

    InvestmentPlan(char* name, double plan, double shares, bool currentDay) {
        strcpy(this->name, name);
        this->plan = plan;
        this->shares = shares;
        this->currentDay = currentDay;
    }

    InvestmentPlan(const InvestmentPlan& other) {
        copy_plan(other);
    }

    InvestmentPlan& operator=(const InvestmentPlan& other) {
        if(this == &other) {
            return *this;
        }
        copy_plan(other);
        return *this;
    }

    double getPlan() {
        return plan;
    }

    double getShares() {
        return shares;
    }

    bool isNew() {
        return currentDay;
    }

    ~InvestmentPlan() { }
};

class InvestmentFund {
    char name[50];
    InvestmentPlan* plans;
    int n;
    double price;

    void copy_fund(const InvestmentFund& other) {
        strcpy(this->name, other.name);
        this->n = other.n;
        this->plans = new InvestmentPlan[other.n];
        for(int i = 0; i < other.n; i++) {
            this->plans[i] = other.plans[i];
        }
        this->price = other.price;
    }

public:
    InvestmentFund() {
        strcpy(this->name, "name");
        this->plans = nullptr;
        this->n = 0;
        this->price = 0;
    }

    InvestmentFund(char* name, InvestmentPlan* plans, int n, double price) {
        strcpy(this->name, name);
        this->plans = new InvestmentPlan[n];
        for(int i = 0; i < n; i++) {
            this->plans[i] = plans[i];
        }
        this->n = n;
        this->price = price;
    }

    InvestmentFund(const InvestmentFund& other) {
        copy_fund(other);
    }

    InvestmentFund& operator=(const InvestmentFund& other) {
        if(this == &other) {
            return *this;
        }
        delete [] plans;
        copy_fund(other);
        return *this;
    }

    double totalSum() {
        long double s = 0;
        for(int i = 0; i < n; i++) {
            s += plans[i].getPlan();
        }
        return s;
    }

    double newTotalSum() {
        double s = 0;
        for(int i = 0; i < n; i++) {
            if(plans[i].isNew()) {
                s += plans[i].getPlan();
            }
        }
        return s;
    }

    virtual double profit() = 0;

    virtual ~InvestmentFund() {
        delete [] plans;
    }
};

class MoneyFund : public InvestmentFund {
    static float provision_year;

public:
    MoneyFund() : InvestmentFund() { }

    MoneyFund(char* name, InvestmentPlan* plans, int n, double price) : InvestmentFund(name, plans, n, price) { }

    MoneyFund(const MoneyFund& other) : InvestmentFund(other) { }

    MoneyFund& operator=(const MoneyFund& other) {
        if(this == &other) {
            return *this;
        }
        InvestmentFund::operator=(other);
        return *this;
    }

    double profit() {
        return (totalSum() * (MoneyFund::provision_year / 100.0)) / 365.0;
    }

    ~MoneyFund() { }
};

class ActionFund : public InvestmentFund {
    static float provision_year;
    static float provision_entry;

public:
    ActionFund() : InvestmentFund() { }

    ActionFund(char* name, InvestmentPlan* plans, int n, double price) : InvestmentFund(name, plans, n, price) { }

    ActionFund(const ActionFund& other) : InvestmentFund(other) { }

    ActionFund& operator=(const ActionFund& other) {
        if(this == &other) {
            return *this;
        }
        InvestmentFund::operator=(other);
        return *this;
    }

    double profit() {
        return (totalSum() * ActionFund::provision_year / 100.0) / 365 + (newTotalSum() * ActionFund::provision_entry / 100.0);
    }

    ~ActionFund() { }
};

float MoneyFund::provision_year = 1;
float ActionFund::provision_year = 1.5;
float ActionFund::provision_entry = 3;

double totalProfit(InvestmentFund** funds, int n) {
    double s = 0;
    for(int i = 0; i < n; i++) {
        s += funds[i]->profit();
    }
    return s;
}

int main(){

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund*[n];
    for(int i = 0; i < n; i++){
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for(int j = 0; j < m; j++){
            cin >> investitor >> plan >> brUdeli;
            if(j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if(i % 2){
            fondovi[i] = new ActionFund(ime, ip, m, udel);
        }
        else{
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}
