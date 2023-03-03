// 1 - 10

#include <iostream>
using namespace std;

struct Igrac {
    char ime[15];
    int nivo;
    int poeni;
};

struct KompjuterskaLiga {
    char igra[20];
    Igrac igraci[30];
    int n;
};

void najdobarIgrac(KompjuterskaLiga * lista, int n) {
    int idx_liga = -1, idx_igrac = -1, maxPoeni = 0, maxNivo = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < lista[i].n; j++) {
            const int poeni = lista[i].igraci[j].poeni, nivo = lista[i].igraci[j].nivo;

            if(poeni > maxPoeni || (poeni == maxPoeni && nivo > maxNivo)) {
                idx_liga = i;
                idx_igrac = j;
                maxPoeni = poeni;
                maxNivo = nivo;
            }
        }
    }

    cout << "Najdobar igrac e igracot so korisnicko ime " << lista[idx_liga].igraci[idx_igrac].ime << " ";
    cout << "koj ja igra igrata " << lista[idx_liga].igra;
}

int main() {
    int n;
    KompjuterskaLiga liga[100];

    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> liga[i].igra >> liga[i].n;

        for(int j = 0; j < liga[i].n; j++) {
            cin >> liga[i].igraci[j].ime >> liga[i].igraci[j].nivo >> liga[i].igraci[j].poeni;
        }
    }

    najdobarIgrac(liga, n);

    return 0;
}