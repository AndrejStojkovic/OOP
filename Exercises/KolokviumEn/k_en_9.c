// En - 9

#include <stdio.h>
#include <string.h>

typedef struct Film {
    char name[100];
    int time;
    float price;
    int discount;
} Film;

typedef struct FilmFestival {
    char name[100];
    char place[100];
    Film films[100];
    int no;
} FilmFestival;

void print(FilmFestival ff) {
    printf("%s %s\n", ff.name, ff.place);
    for(int i = 0; i < ff.no; i++) {
        printf("%s %d %.2f\n", ff.films[i].name, ff.films[i].time, ff.films[i].price);
    }
}

void bestFestival(FilmFestival* ff, int n) {
    int idx = -1;
    float val = -1;

    for(int i = 0; i < n; i++) {
        float s = 0;
        for(int j = 0; j < ff[i].no; j++) {
            if(!ff[i].films[j].discount) {
                continue;
            }

            s += ff[i].films[j].price;
        }

        if(idx == -1 || s > val) {
            idx = i;
            val = s;
        }
    }

    if(idx == -1) {
        return;
    }

    printf("Najdobar festival: %s %s\n", ff[idx].name, ff[idx].place);
}

int main()
{
    int i, j, n, broj;
    FilmFestival ff[50];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        /* name of the festival */
        scanf("%s", ff[i].name);
        /* place it is held */
        scanf("%s", ff[i].place);
        /* number of movies */
        scanf("%d", &ff[i].no);

        for (j = 0; j < ff[i].no; j++){
            scanf("%s", ff[i].films[j].name);  		/* title of the movie */
            scanf("%d", &ff[i].films[j].time); 		/* duration */
            scanf("%f", &ff[i].films[j].price); 	/* price */
            scanf("%d", &ff[i].films[j].discount);	/* discount */
        }
    }

    for(i=0; i<n; ++i){
        print(ff[i]);
    }

    bestFestival(ff, n);


    return 0;
}