// 1 - 22

#include <stdio.h>
#include <string.h>

typedef struct proizvod_t {
    char kod[20];
    int cena;
    int kolicina;
} Proizvod;

typedef struct narachka_t {
    char ime[15];
    Proizvod proizvodi[10];
    int proizvodi_n[10];
    int n;
} Narachka;

void pecatiFaktura(Narachka nc) {
    printf("Faktura za %s\n", nc.ime);

    for(int i = 0; i < nc.n; i++) {
        if(nc.proizvodi_n[i] > nc.proizvodi[i].kolicina) {
            printf("Fakturata ne moze da se izgotvi");
            return;
        }
    }

    int s = 0;

    for(int i = 0; i < nc.n; i++) {
        printf("%s %d %d %d\n", nc.proizvodi[i].kod, nc.proizvodi[i].cena, nc.proizvodi_n[i], nc.proizvodi_n[i] * nc.proizvodi[i].cena);
        s += (nc.proizvodi_n[i] * nc.proizvodi[i].cena);
        nc.proizvodi[i].kolicina -= nc.proizvodi_n[i];
    }

    printf("Vkupnata suma na fakturata e %d", s);
}

int main() {
    Narachka narachka;

    scanf("%s%d", narachka.ime, &narachka.n);

    for(int i = 0; i < narachka.n; i++) {
        char kod[20];
        scanf("%s%d%d", narachka.proizvodi[i].kod, &narachka.proizvodi[i].cena, &narachka.proizvodi[i].kolicina);
    }

    for(int i = 0; i < narachka.n; i++) {
        scanf("%d", &narachka.proizvodi_n[i]);
    }

    pecatiFaktura(narachka);

    return 0;
}