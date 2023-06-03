// En - 21

#include <stdio.h>

typedef struct skilift_t {
    char ime[15];
    int max_skijaci;
    int voUpotreba
} SkiLift;

typedef struct skicenter_t {
    char ime[20];
    char drzava[20];
    SkiLift niza[20];
    int br_lifts;
} SkiCenter;

int kapacitet(SkiCenter sc) {
    int s = 0;
    for(int i = 0; i < sc.br_lifts; i++) {
        if(sc.niza[i].voUpotreba) {
            s += sc.niza[i].max_skijaci;
        }
    }
    return s;
}

void najgolemKapacitet(SkiCenter* sc, int n) {
    int k = 0, v = 0, idx = 0;

    for(int i = 0; i < n; i++) {
        k = kapacitet(sc[i]);
        if(k > v || (k == v && sc[i].br_lifts > sc[idx].br_lifts)) {
            v = k;
            idx = i;
        }
    }

    printf("%s\n%s\n%d\n", sc[idx].ime, sc[idx].drzava, v);
}

int main()
{
    int i, j, n, broj;
    SkiCenter sc[20];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        scanf("%s %s %d", sc[i].ime, sc[i].drzava, &sc[i].br_lifts);

        for (j = 0; j < sc[i].br_lifts; j++){
            scanf("%s %d %d", sc[i].niza[j].ime, &sc[i].niza[j].max_skijaci, &sc[i].niza[j].voUpotreba);
        }
    }
    najgolemKapacitet(sc, n);

    return 0;
}