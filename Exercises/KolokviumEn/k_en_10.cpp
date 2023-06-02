// En - 10

#include <iostream>
#include <cstring>
using namespace std;

class InvalidTeamName {
    char team[50];

public:
    InvalidTeamName(char* team) {
        strcpy(this->team, team);
    }

    char* what() {
        return team;
    }
};

class Goal {
    char* player;
    int time;
    char team[50];

    void copy_goal(const Goal& other) {
        this->player = new char[strlen(other.player) + 1];
        strcpy(this->player, other.player);
        this->time = other.time;
        strcpy(this->team, other.team);
    }
public:
    Goal() {
        this->player = new char[0];
        strcpy(this->player, "player");
        this->time = 0;
        strcpy(this->team, "team");
    }

    Goal(char* player, int time, char* team) {
        this->player = new char[strlen(player) + 1];
        strcpy(this->player, player);
        this->time = time;
        strcpy(this->team, team);
    }

    Goal(const Goal& other) {
        copy_goal(other);
    }

    Goal& operator=(const Goal& other) {
        if(this == &other) {
            return *this;
        }

        delete [] player;
        copy_goal(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Goal& goal) {
        out << goal.time << " " << goal.player << "\n";
        return out;
    }

    Goal& operator++() {
        time++;
        return *this;
    }

    Goal& operator--() {
        time--;
         return *this;
    }

    char* getTeam() {
        return team;
    }

    ~Goal() {
        delete [] player;
    }
};

class Game {
    Goal* goals;
    int n;
    char team1[50];
    char team2[50];

    void copy_game(const Game& other) {
        this->goals = new Goal[other.n];
        for(int i = 0; i < other.n; i++) {
            this->goals[i] = other.goals[i];
        }
        this->n = other.n;
        strcpy(this->team1, team1);
        strcpy(this->team2, team2);
    }

public:
    Game() {
        this->goals = new Goal[0];
        this->n = 0;
        strcpy(this->team1, "team1");
        strcpy(this->team2, "team2");
    }

    Game(char* team1, char* team2) {
        this->goals = new Goal[0];
        this->n = 0;
        strcpy(this->team1, team1);
        strcpy(this->team2, team2);
    }

    Game(const Game& other) {
        copy_game(other);
    }

    Game& operator=(const Game& other) {
        if(this == &other) {
            return *this;
        }

        delete [] goals;
        copy_game(other);
        return *this;
    }

    Game& operator+=(Goal& goal) {
        if(strcmp(team1, goal.getTeam()) && strcmp(team2, goal.getTeam())) {
            throw InvalidTeamName(goal.getTeam());
        }

        Goal* tmp = new Goal[n + 1];
        for(int i = 0; i < n; i++) {
            tmp[i] = goals[i];
        }
        tmp[n++] = goal;

        delete [] goals;
        this->goals = new Goal[n];
        for(int i = 0; i < n; i++) {
            this->goals[i] = tmp[i];
        }

        delete [] tmp;
    }

    friend ostream& operator<<(ostream& out, Game& game) {
        out << game.team1 << " - " << game.team2 << "\n";
        for(int i = 0; i < game.n; i++) {
            out << game.goals[i];
        }
        return out;
    }

    ~Game() {
        delete [] goals;
    }
};

int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}