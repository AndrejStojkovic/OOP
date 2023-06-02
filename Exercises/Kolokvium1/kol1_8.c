// 1 - 8

#include <stdio.h>

typedef struct laptop_t {
    char firma[100];
    float golemina;
    int touch;
    int cena;
} Laptop;

typedef struct itstore_t {
    char ime[100];
    char lokacija[100];
    Laptop niza[100];
    int n;
} ITStore;

int isInteger(float n) {
    return n - (int)n == 0;
}

void print(ITStore it) {
    printf("%s %s\n", it.ime, it.lokacija);
    for(int i = 0; i < it.n; i++) {
        printf("%s ", it.niza[i].firma);

        const float golemina = it.niza[i].golemina;

        if(isInteger(golemina))
            printf("%d ", (int)golemina);
        else
            printf("%.1f ", golemina);

        printf("%d\n", it.niza[i].cena);
    }
}

void najeftina_ponuda(ITStore * it, int n) {
    int najeftina, setVal = 0, idx = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < it[i].n; j++) {
            if(!it[i].niza[j].touch) continue;

            if(!setVal) {
                najeftina = it[i].niza[j].cena; setVal = 1; continue;
            }

            if(it[i].niza[j].cena < najeftina) {
                idx = i;
                najeftina = it[i].niza[j].cena;
            }
        }
    }

    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n", it[idx].ime, it[idx].lokacija);
    printf("Najniskata cena iznesuva: %d\n", najeftina);
}

int main() {
    ITStore s[100];
    int n;
    scanf("%d",&n);

    for(int i = 0; i < n; i++) {
        scanf("%s %s %d", s[i].ime, s[i].lokacija, &s[i].n);

        for(int j = 0; j < s[i].n; j++) {
            scanf("%s %f", s[i].niza[j].firma, &s[i].niza[j].golemina);
            scanf("%d %d", &s[i].niza[j].touch, &s[i].niza[j].cena);
        }
    }

    for(int i = 0; i < n; i++)
        print(s[i]);

    najeftina_ponuda(s, n);

    return 0;
}