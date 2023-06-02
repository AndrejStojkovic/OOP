// En - 8

#include <stdio.h>
#include <string.h>

typedef struct Driver {
    char name[100];
    int time;
} Driver;

typedef struct Race {
    char location[100];
    Driver drivers[100];
    int n;
} Race;

void top3(Race* r) {
    for(int i = 0; i < r->n - 1; i++) {
        for(int j = i + 1; j < r->n; j++) {
            if(r->drivers[i].time > r->drivers[j].time) {
                Driver swap = r->drivers[i];
                r->drivers[i] = r->drivers[j];
                r->drivers[j] = swap;
            }
        }
    }

    for(int t = 0; t < 3; t++) {
        printf("%d. %s %2d:%02d\n", t + 1, r->drivers[t].name, r->drivers[t].time / 60, r->drivers[t].time % 60);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Race races[n];
    int i;
    for(i = 0; i < n; ++i) {
        scanf("%s", races[i].location);
        scanf("%d", &races[i].n);
        int j;
        for(j = 0; j < races[i].n; ++j) {
            scanf("%s", races[i].drivers[j].name);
            scanf("%d", &races[i].drivers[j].time);
        }
    }

    for(i = 0; i < n; ++i) {
        printf("%s (%d Drivers)\n", races[i].location, races[i].n);
        top3(&races[i]);
    }

    return 0;
}