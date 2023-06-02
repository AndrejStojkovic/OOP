// 1 - 18

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

    for(int i = 0; i < sc.br_lifts; i++)
        if(sc.niza[i].voUpotreba)
            s += sc.niza[i].max_skijaci;

    return s;
}

void najgolemKapacitet(SkiCenter* sc, int n) {
    int k, v, idx;
    k = v = idx = 0;

    for(int i = 0; i < n; i++) {
        k = kapacitet(sc[i]);
        if((k > v) || (k == v && sc[i].br_lifts > sc[idx].br_lifts)) {
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
        //printf("Ime:");
        scanf("%s", sc[i].ime);
        //printf("\nDrzava:");
        scanf("%s", sc[i].drzava);
        scanf("%d", &sc[i].br_lifts);

        for (j = 0; j < sc[i].br_lifts; j++){
            scanf("%s", sc[i].niza[j].ime);
            scanf("%d", &sc[i].niza[j].max_skijaci);
            scanf("%d", &sc[i].niza[j].voUpotreba);
        }
    }
    najgolemKapacitet(sc, n);

    return 0;
}