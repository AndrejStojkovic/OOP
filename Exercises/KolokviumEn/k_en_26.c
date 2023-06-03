// En - 26

// bez 'struct'
#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    int ct = 1, total = 0;

    for(int i = 0; i < n; i++) {
        int day, month, year, amount;
        char currency[5];

        scanf("%s %d %d/%d/%d", currency, &amount, &day, &month, &year);

        if(strcmp(currency, "USD") || amount > 5000 || month < 1 || month > 3) {
            continue;
        }

        total += amount;
        printf("%d. %02d/%02d/%d %d USD\n", ct++, day, month, year, amount);
    }

    printf("Total: %d USD", total);

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
        scanf("%s %d %d/%d/%d", t[i].currency, &t[i].amount, &t[i].day, &t[i].month, &t[i].year);
    }

    for(i = 0; i < n; i++) {
        if(strcmp(t[i].currency, "USD") || t[i].amount > 5000 || t[i].month < 1 || t[i].month > 3) {
            continue;
        }

        total += t[i].amount;
        printf("%d. %02d/%02d/%d %d USD\n", ct++, t[i].day, t[i].month, t[i].year, t[i].amount);
    }

    printf("Total: %d USD", total);

    return 0;
}