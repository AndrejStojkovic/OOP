// En - 27

// Bez 'struct'
#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    int ct = 1, total = 0;

    for(int i = 0; i < n; i++) {
        int day, month, year, amount;
        char currency[5];

        scanf("%d/%d/%d %d %s", &day, &month, &year, &amount, currency);

        if(strcmp(currency, "MKD") || amount <= 1000 || year < 2013 || year > 2015) {
            continue;
        }

        total += amount;
        printf("%d. %02d/%02d/%d %d MKD\n", ct++, day, month, year, amount);
    }

    printf("Total: %d MKD", total);

    return 0;
}

// So 'struct'
#include <stdio.h>
#include <string.h>

typedef struct Transaction {
    int day;
    int month;
    int year;
    int amount;
    char currency[5];
} Transaction;

int main() {
    int n, i;
    scanf("%d", &n);

    Transaction t[n];

    int ct = 1, total = 0;

    for(i = 0; i < n; i++) {
        scanf("%d/%d/%d %d %s", &t[i].day, &t[i].month, &t[i].year, &t[i].amount, t[i].currency);
    }

    for(i = 0; i < n; i++) {
        if(strcmp(t[i].currency, "MKD") || t[i].amount <= 1000 || t[i].year < 2013 || t[i].year > 2015) {
            continue;
        }

        total += t[i].amount;
        printf("%d. %02d/%02d/%d %d MKD\n", ct++, t[i].day, t[i].month, t[i].year, t[i].amount);
    }

    printf("Total: %d MKD", total);

    return 0;
}