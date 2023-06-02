#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

struct RabotnaNedela {
    int casovi[DENOVI];
    int broj;
};

typedef struct RabotnaNedela RN;

struct Rabotnik {
    char ime[50];
    struct RabotnaNedela nedeli[NEDELI];
};

typedef struct Rabotnik R;

int maxNedela(R *r) {
    int s = 0, nedela = -1;

    for(int i = 0; i < NEDELI; i++) {
        int d = 0;
        for(int j = 0; j < DENOVI; j++) {
            d += r->nedeli[i].casovi[j];
        }

        if(d > s) {
            s = d;
            nedela = i;
        }
    }

    return nedela + 1;
}

void table(R *r, int n) {
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i = 0; i < n; i++) {
        int vk = 0;

        printf("%s\t", r[i].ime);

        for(int j = 0; j < NEDELI; j++) {
            int d = 0;
            for(int k = 0; k < DENOVI; k++) {
                d += r[i].nedeli[j].casovi[k];
            }
            vk += d;
            printf("%d\t", d);
        }

        printf("%d\n", vk);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
