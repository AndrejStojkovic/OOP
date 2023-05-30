// En - 5

#include <iostream>
#include <cstring>
using namespace std;

struct Player {
    char korisnickoIme[15];
    int nivo;
    int poeni;
};

struct ComputerGame {
    char ime[20];
    Player lista[30];
    int n;
};

void bestPlayer(ComputerGame* igri, int n) {
    int best_game = -1;

    for(int i = 0; i < n; i++) {
        if(best_game == -1 || igri[i].n > igri[best_game].n) {
            best_game = i;
        }
    }

    int idx = -1;

    for(int i = 0; i < igri[best_game].n; i++) {
        if(idx == -1 || igri[best_game].lista[i].poeni > igri[best_game].lista[idx].poeni) {
            idx = i;
        }
    }

    cout << "Najdobar igrac e igracot so korisnicko ime " << igri[best_game].lista[idx].korisnickoIme;
    cout <<" koj ja igra igrata " << igri[best_game].ime << "\n";
}

int main() {
    int n,m;
    char ime[20];
    cin>>n;
    //create an array of max 100 computer games;
    ComputerGame poleigri[100];
    for (int i=0; i<n; i++) {
        ComputerGame nova;
        cin>>nova.ime>>nova.n;
        Player pole[30];
        for (int j=0; j<nova.n; j++) {
            Player nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    bestPlayer(poleigri,n);
    return 0;
}