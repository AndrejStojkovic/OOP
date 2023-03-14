/* 1.1

За програмски јазик да се употреби C.

Да се напише програма во која од стандарден влез се внесува бројот N (бројот на трансакции), а потоа N трансакциски сметки и како резултат ги печати идентификацискиот број и вкупната сума (со провизија) на сите трансакции платени со кредитна картичка. Во случај да нема трансакција платена со кредитна картичка да се испечати "No credit card transaction".

Во структурата Трансакција (Transaction) треба да се чуваат следните информации:
- Идентификациски број (int)
- Платена сума (int)
- Провизија (int)
- Дали е платено со дебитна или кредитна картичка (0 - дебитна, 1 - кредитна)

Ограничување: 0 < N < 100

Структура на влезните податоци:
N
id1 sum1 commission1 type1
...
idn sumn Commissionn typen

*/

#include <stdio.h>

typedef struct t_transaction {
    int id;
    int sum;
    int commision;
    int tip;
} Transaction;

int main() {
    int n, flag = 0;
    scanf("%d", &n);

    Transaction t[100];

    for(int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &t[i].id, &t[i].sum, &t[i].commision, &t[i].tip);
    }

    for(int i = 0; i < n; i++) {
        if(!t[i].tip) continue;

        flag = 1;
        printf("%d %d\n", t[i].id, t[i].sum + t[i].commision);
    }

    if(!flag) {
        printf("No credit card transaction");
    }

    return 0;
}
