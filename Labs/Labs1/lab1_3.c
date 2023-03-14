/* 1.3

Да се креира структура Item во која што ќе се чуваат податоци за еден производ од продавница. За производот ќе се чуваат информации за име и цена на производот.
Потоа, да се креира структура ShoppingCart во која што ќе  се чуваат податоци за id на кошничката и сите производи кои се дел од таа кошничка за купување.
На почетокот се внесува број N што озналува колку кошнички ќе се читаат од влез.

Да се направат функциите:

void printAveragePriceOfLowestItems(...):
која што ќе ги земе производите со најмала цена од секоја кошничка, ќе ја пресмета нивната средна вредност и ќе ја испечати.


void printHighestPricedItem(...):
кoja што за секоја кошничка ќе го испечати името на производот со најголема цена и id-то на кошничката од кој што доаѓа тој производ.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_item {
    char ime[100];
    int cena;
} Item;

typedef struct t_shoppingcart {
    int id;
    Item items[50];
    int n;
} ShoppingCart;

void printAveragePriceOfLowestItems(ShoppingCart* carts, int num) {
    float s = 0;

    for(int i = 0; i < num; i++) {
        int lowest = carts[i].items[0].cena, idx = 0;
        for(int j = 0; j < carts[i].n; j++) {
            if(carts[i].items[j].cena < lowest) {
                lowest = carts[i].items[j].cena;
                idx = j;
            }
        }

        s += carts[i].items[idx].cena;
    }

    printf("Average: %.2f\n", s / (float)num);
}

void printHighestPricedItem(ShoppingCart* carts, int num) {
    int idx_cart = -1, idx_item = -1, highest = -1;
    for(int i = 0; i < num; i++) {
        for(int j = 0; j < carts[i].n; j++) {
            if(carts[i].items[j].cena > highest) {
                highest = carts[i].items[j].cena;
                idx_cart = i;
                idx_item = j;
            }
        }
    }

    printf("Shopping cart id: %d\n", carts[idx_cart].id);
    printf("Product: %s\n", carts[idx_cart].items[idx_item].ime);
}

int main() {
    int n;
    scanf("%d", &n);

    ShoppingCart carts[10];

    for(int i = 0; i < n; i++) {
        scanf("%d%d", &carts[i].id, &carts[i].n);
        getchar();
        for(int j = 0; j < carts[i].n; j++) {
            fgets(carts[i].items[j].ime, 100, stdin);
            scanf("%d\n", &carts[i].items[j].cena);
            //printf("- %s %d\n", ime, carts[i].items[j].cena);
            getchar();
        }
    }

    printAveragePriceOfLowestItems(carts, n);
    printHighestPricedItem(carts, n);

    return 0;
}
