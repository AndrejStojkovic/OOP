// 1 - 7

#include <stdio.h>

typedef struct vozenje_t {
    char ime[100];
    int vremetraenje;
    float cena;
    int studentski_popust;
} Vozenje;

typedef struct zabavenpark_t {
    char ime[100];
    char lokacija[100];
    Vozenje niza[100];
    int n;
} ZabavenPark;

void pecati(ZabavenPark z) {
    printf("%s %s\n", z.ime, z.lokacija);
    for(int i = 0; i < z.n; i++) {
        printf("%s %d %.2f\n", z.niza[i].ime, z.niza[i].vremetraenje, z.niza[i].cena);
    }
}

void najdobarPark(ZabavenPark * f, int n) {
    int maxCt = -1, maxVreme = -1, idx = 0;
    
    for(int i = 0; i < n; i++) {
        int ct = 0, vreme = 0;
        
        for(int j = 0; j < f[i].n; j++) {
            if(f[i].niza[j].studentski_popust) {
                ct++;
            }
            
            vreme += f[i].niza[j].vremetraenje;
        }
        
        if(ct > maxCt || (ct == maxCt && vreme > maxVreme)) {
            maxCt = ct;
            maxVreme = vreme;
            idx = i;
        }
    }
    
    printf("Najdobar park: %s %s\n", f[idx].ime, f[idx].lokacija);
}

int main() {
    ZabavenPark f[100];
    int n;
    
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        scanf("%s %s %d", f[i].ime, f[i].lokacija, &f[i].n);
        
        for(int j = 0; j < f[i].n; j++) {
            scanf("%s %d %f %d", f[i].niza[j].ime, &f[i].niza[j].vremetraenje, &f[i].niza[j].cena, &f[i].niza[j].studentski_popust);
        }
    }
    
    for(int i = 0; i < n; i++) {
        pecati(f[i]);
    }

    najdobarPark(f, n);

    return 0;
}