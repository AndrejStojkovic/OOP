// 1 - 20

#include <stdio.h>
#include <string.h>

typedef struct pacient_s {
    char ime[100];
    int zdrastveno;
    int pregledi;
} Pacient;

typedef struct maticendoktor_s {
    char ime[100];
    Pacient niza[200];
    int br_pac;
    float cena;
} MaticenDoktor;

void najuspesen_doktor(MaticenDoktor md[200], int n) {
    char r_ime[100];
    float r_cena = 0;
    int r_pregledi = -1;

    for(int i = 0; i < n; i++) {
        float s = 0;
        int p = 0;
        for(int j = 0; j < md[i].br_pac; j++) {
            if(!md[i].niza[j].zdrastveno) {
                s += (md[i].cena * md[i].niza[j].pregledi);
            }
            p += md[i].niza[j].pregledi;
        }

        if(s >= r_cena && p >= r_pregledi) {
            strcpy(r_ime, md[i].ime);
            r_cena = s;
            r_pregledi = p;
        }
    }

    printf("%s %.2f %d", r_ime, r_cena, r_pregledi);
}

int main()
{
    int i, j, n, broj;
    MaticenDoktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        //ime na doktor
        scanf("%s", md[i].ime);
        //broj na pacienti
        scanf("%d", &md[i].br_pac);
        //cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].br_pac; j++){
            scanf("%s", md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}