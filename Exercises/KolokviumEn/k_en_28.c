// En - 28

#include <stdio.h>
#include <string.h>
#define WEEKS 4
#define DAYS 5

typedef struct WorkingWeek WW;

struct WorkingWeek {
    int hours[DAYS];
};

typedef struct Worker W;

struct Worker {
    char name[50];
    WW weeks[WEEKS];
};

void table(W* w, int n) {
    printf("Wor\t1\t2\t3\t4\tTotal\n");
    for(int i = 0; i < n; i++) {
        int total = 0;
        printf("%s\t", w[i].name);
        for(int j = 0; j < WEEKS; j++) {
            int s = 0;
            for(int k = 0; k < DAYS; k++) {
                s += w[i].weeks[j].hours[k];
            }
            total += s;
            printf("%d\t", s);
        }
        printf("%d\n", total);
    }
}

int maxWeek(W* w) {
    int week = 0, val = 0;

    for(int i = 0; i < WEEKS; i++) {
        int s = 0;
        for(int j = 0; j < DAYS; j++) {
            s += w->weeks[i].hours[j];
        }

        if(s > val) {
            val = s;
            week = i;
        }
    }

    return week + 1;
}

int main() {
    int n;
    scanf("%d", &n);
    W workers[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", workers[i].name);
        int j;
        for (j = 0; j < WEEKS; ++j) {
            int k;
            for (k = 0; k < DAYS; ++k) {
                scanf("%d", &workers[i].weeks[j].hours[k]);
            }

        }
    }
    printf("TABLE\n");
    table(workers, n);
    printf("MAX WEEK OF WORKER: %s\n", workers[n / 2].name);
    printf("%d\n", maxWeek(&workers[n / 2]));
    return 0;
}
