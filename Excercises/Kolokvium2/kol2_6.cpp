// 2 - 6

#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame {
public:
    void message() {
        cout << "The game is already in the collection\n";
    }
};

class Game {
protected:
    char name[100];
    float price;
    bool sale;

private:
    void copy(const Game& other) {
        strcpy(this->name, other.name);
        this->price = other.price;
        this->sale = other.sale;
    }

public:
    Game() {
        strcpy(this->name, "unknown");
        this->price = 0.0;
        this->sale = false;
    }

    Game(char* name, float price, bool sale) {
        strcpy(this->name, name);
        this->price = price;
        this->sale = sale;
    }

    Game(const Game& other) {
        copy(other);
    }

    Game& operator=(const Game& other) {
        if(this == &other) return *this;
        copy(other);
        return *this;
    }

    bool operator==(Game& other) {
        return !strcmp(this->name, other.name);
    }

    friend ostream& operator<<(ostream& out, Game& g) {
        // Game: Name, regular price: $price(, bought on sale)
        out << "Game: " << g.name << ", regular price: $" << g.price;
        if(g.sale) out << ", bought on sale";
        return out;
    }

    friend istream& operator>>(istream& in, Game& g) {
        in.get();
        in.getline(g.name, 100);
        in >> g.price >> g.sale;
        return in;
    }

    virtual float get_price() {
        return sale ? price * 0.3 : price;
    }

    char* getName() { return name; }
    void setName(char* name) { strcpy(this->name, name); }

    float getPrice() { return price; }
    void setPrice(float price) { this->price = price; }

    bool onSale() { return sale; }
    void setSale(bool sale) { this->sale = sale; }

    ~Game() { }
};

class SubscriptionGame : public Game {
    float fee;
    int month;
    int year;

public:
    SubscriptionGame() : Game() {
        this->fee = 0.0;
        this->year = this->month = 0;
    }

    SubscriptionGame(char* name, float price, bool sale, float fee, int month, int year) : Game(name, price, sale) {
        this->fee = fee;
        this->month = month;
        this->year = year;
    }

    SubscriptionGame(const SubscriptionGame& other) : Game(other) {
        this->fee = other.fee;
        this->month = other.month;
        this->year = other.year;
    }

    SubscriptionGame& operator=(const SubscriptionGame& other) {
        if(this == &other) return *this;
        Game::operator=(other);
        this->fee = other.fee;
        this->month = other.month;
        this->year = other.year;
        return *this;
    }

    friend ostream& operator<<(ostream& out, SubscriptionGame& g) {
        // Game: World of Warcraft, regular price: $40, monthly fee: $10, purchased: 1-2017
        out << *dynamic_cast<Game*>(&g);
        out << ", monthly fee: $" << g.fee << ", purchased: " << g.month << "-" << g.year;
        return out;
    }

    friend istream& operator>>(istream& in, SubscriptionGame& g) {
        in.get();
        in.getline(g.name, 100);
        in >> g.price >> g.sale >> g.fee >> g.month >> g.year;
        return in;
    }

    float get_price() {
        float s = Game::get_price();
        int m = year < 2018 ? (12 - month) + (2017 - year) * 12 + 5 : 5 - month;
        s += m * fee;
        return s;
    }

    ~SubscriptionGame() { }
};

class User {
    char name[100];
    Game** games;
    int n;

    void copy(const User& other) {
        strcpy(this->name, other.name);
        this->n = other.n;
        this->games = new Game*[this->n];
        for(int i = 0; i < this->n; i++) this->games[i] = new Game(*(other.games[i]));
    }

public:
    User() {
        strcpy(this->name, "unknown");
        this->games = new Game*[0];
        this->n = 0;
    }

    User(char* name) {
        strcpy(this->name, name);
        this->games = new Game*[0];
        this->n = 0;
    }

    User(const User& other) {
        copy(other);
    }

    User& operator=(const User& other) {
        if(this == &other) return *this;
        for(int i = 0; i < n; i++) delete this->games[i];
        delete [] games;
        copy(other);
        return *this;
    }

    User& operator+=(Game& game) {
        for(int i = 0; i < this->n; i++) {
            if(*games[i] == game) throw ExistingGame();
        }

        Game** tmp = new Game*[n + 1];
        for(int i = 0; i < this->n; i++) tmp[i] = games[i];

        SubscriptionGame* s_game = dynamic_cast< SubscriptionGame* >(&game);

        if(s_game) tmp[n] = new SubscriptionGame(*s_game);
        else tmp[n] = new Game(game);

        delete [] this->games;
        this->games = tmp;
        n++;

        return *this;
    }

    friend ostream& operator<<(ostream& out, User& user) {
        out << "\nUser: " << user.name << "\n";
        for(int i = 0; i < user.n; i++) {
            SubscriptionGame* s_game = dynamic_cast<SubscriptionGame*>(user.games[i]);
            out << "- ";
            if(s_game) out << *s_game;
            else out << *user.games[i];
            out << "\n";
        }
        out << "\n";
        return out;
    }

    Game& get_game(int i){
        return *games[i];
    }

    float total_spent(){
        float s = 0.0;
        for (int i = 0; i < this->n; i++) s += games[i]->get_price();
        return s;
    }

    char* get_name() { return name; }
    int get_games_number() { return n; }

    ~User() {
        for(int i = 0; i < n; i++) delete this->games[i];
        delete [] games;
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}