// En - 7

#include <iostream>
#include <cstring>
using namespace std;

class NonDigitIdException {
public:
    void message() {
        cout << "The id number has a non-digit character\n";
    }
};

class InvalidIdFormatException {
public:
    void message() {
        cout << "The id number has more than 9 characters\n";
    }
};

class DonationAction {
    char* name;
    char* id;
    int collected;
    int required;

    void copy_action(const DonationAction& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->id = new char[strlen(other.id) + 1];
        strcpy(this->id, other.id);
        this->collected = other.collected;
        this->required = other.required;
    }

public:
    DonationAction() {
        this->name = new char[0];
        this->id = new char[0];
        this->collected = this->required = 0;
    }

    DonationAction(char* name, char* id, int required) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->id = new char[strlen(id) + 1];
        strcpy(this->id, id);
        this->collected = 0;
        this->required = required;
    }

    DonationAction(const DonationAction& other) {
        copy_action(other);
    }

    DonationAction& operator=(const DonationAction& other) {
        if(this == &other) {
            return *this;
        }

        delete [] name;
        delete [] id;
        copy_action(other);
        return *this;
    }

    int fund() {
        return required - collected;
    }

    friend ostream& operator<<(ostream& out, DonationAction& action) {
        out << action.id << " " << action.name << " ";
        if(action.fund() > 0) {
            out << action.fund() << " more denars are needed";
        } else {
            out << "collected";
        }
        out << "\n";
        return out;
    }

    DonationAction& operator+=(int add) {
        collected += add;
        return *this;
    }

    bool operator<(DonationAction& action) {
        return fund() < action.fund();
    }

    bool operator==(DonationAction& action) {
        return fund() == action.fund();
    }

    char* getId() {
        return id;
    }

    int getCollected() {
        return collected;
    }

    ~DonationAction() {
        delete [] name;
        delete [] id;
    }
};

class DonationSociety {
    char president[30];
    DonationAction* actions;
    int n;

    void copy_society(const DonationSociety& other) {
        strcpy(this->president, other.president);
        this->actions = new DonationAction[other.n];
        for(int i = 0; i < other.n; i++) {
            this->actions[i] = other.actions[i];
        }
        this->n = other.n;
    }

public:
    DonationSociety() {
        strcpy(this->president, "unknown");
        this->actions = new DonationAction[0];
        this->n = 0;
    }

    DonationSociety(char* president) {
        strcpy(this->president, president);
        this->actions = new DonationAction[0];
        this->n = 0;
    }

    DonationSociety(const DonationSociety& other) {
        copy_society(other);
    }

    DonationSociety& operator=(const DonationSociety& other) {
        if(this == &other) {
            return *this;
        }

        delete [] actions;
        copy_society(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, DonationSociety& s) {
        DonationAction* tmp = new DonationAction[s.n];
        for(int i = 0; i < s.n; i++) {
            tmp[i] = s.actions[i];
        }

        for(int i = 0; i < s.n - 1; i++) {
            for(int j = i + 1; j < s.n; j++) {
                bool len = strlen(tmp[i].getId()) > strlen(tmp[j].getId());

                if(tmp[i] < tmp[j] || (tmp[i] == tmp[j] && len)) {
                    DonationAction swap = tmp[i];
                    tmp[i] = tmp[j];
                    tmp[j] = swap;
                }
            }
        }

        for(int i = 0; i < s.n; i++) {
            out << tmp[i];
        }

        out << "President:" << s.president;
        return out;
    }

    DonationSociety& operator+=(DonationAction& action) {
        char* new_id = action.getId();

        if(strlen(new_id) > 10) {
            throw InvalidIdFormatException();
        }

        for(int i = 0; i < strlen(new_id); i++) {
            if(new_id[i] < '0' || new_id[i] > '9') {
                throw NonDigitIdException();
            }
        }

        for(int i = 0; i < n; i++) {
            if(!strcmp(action.getId(), actions[i].getId())) {
                return *this;
            }
        }

        DonationAction* tmp = new DonationAction[n + 1];
        for(int i = 0; i < n; i++) {
            tmp[i] = actions[i];
        }
        tmp[n++] = action;

        delete [] actions;
        this->actions = new DonationAction[n];
        for(int i = 0; i < n; i++) {
            this->actions[i] = tmp[i];
        }
        delete [] tmp;
    }

    bool takeDonation(char* id, int donatedFund) {
        for(int i = 0; i < n; i++) {
            if(!strcmp(id, actions[i].getId())) {
                actions[i] += donatedFund;
                return true;
            }
        }

        return false;
    }

    ~DonationSociety() {
        delete [] actions;
    }
};

int main(){
    DonationSociety donacii("Velko Velkovski");
    int n;
    char naziv[50],id[50];
    int potrebnasuma,doniranasuma;
    cin>>n;

    for (int i=0;i<n;i++){
        cin.get();
        cin.getline(naziv,50);
        cin>>id>>potrebnasuma;

        DonationAction edna(naziv,id,potrebnasuma);

        try {
            donacii+=edna;
        }
        catch(NonDigitIdException& a) { a.message(); }
        catch(InvalidIdFormatException& b) { b.message(); }

    }

    //donation
    cin>>n;
    for (int i=0;i<n;i++){

        cin>>id>>doniranasuma;

        if(!donacii.takeDonation(id,doniranasuma))
            cout<<"The donation is not taken. Wrong ID."<<endl;
    }
    cout<<"==============="<<endl;
    cout<<donacii;

}
