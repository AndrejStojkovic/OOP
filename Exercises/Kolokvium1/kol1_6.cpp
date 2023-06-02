// 1 - 6

#include <iostream>
#include <cstring>
using namespace std;

struct Voz {
    char relacija[50];
    float km;
    int patnici;
};

struct ZeleznickaStanica {
    char grad[20];
    Voz vozovi[30];
    int vozovi_n;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad) {
    float najkratka;
    char relacija[50];
    int flag = 0;

    for(int i = 0; i < n; i++) {
        if(strcmp(zs[i].grad, grad) != 0) {
            continue;
        }

        for(int j = 0; j < zs[i].vozovi_n; j++) {
            if(!flag) {
                strcpy(relacija, zs[i].vozovi[j].relacija);
                najkratka = zs[i].vozovi[j].km;
                flag = 1;
            }

            if(zs[i].vozovi[j].km > najkratka) {
                continue;
            }

            najkratka = zs[i].vozovi[j].km;
            strcpy(relacija, zs[i].vozovi[j].relacija);
        }
    }

    cout << "Najkratka relacija: " << relacija << " (" << najkratka << " km)\n";
}

int main() {
    int n;
    cin >> n;

    ZeleznickaStanica zStanica[100];
    for(int i = 0; i < n; i++){
        cin >> zStanica[i].grad >> zStanica[i].vozovi_n;

        for(int j = 0; j < zStanica[i].vozovi_n; j++) {
            cin >> zStanica[i].vozovi[j].relacija >> zStanica[i].vozovi[j].km >> zStanica[i].vozovi[j].patnici;
        }
    }

    char grad[25];
    cin >> grad;

    najkratkaRelacija(zStanica, n, grad);

    return 0;
}