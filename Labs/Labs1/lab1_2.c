/* 1.2

Да се креира структура Student во која се чуваат податоци за еден студент. За студентот се чуваат информации за името на студентот(низа од карактери), број на индекс на студентот, број на курсеви кои ги слуша, низа од кодови на курсевите кои ги слуша.

Потоа, да се креира структура Course во која се чуваат податоци за името на курсот (низа од карактери), код на курсот(цел број) и број на студенти кои го слушаат.

Да се направи функција: 

int get_most_popular_course(struct course courses[], int num_courses)
кoja што го враќа кодот на најпопуларниот курс.

*/

#include <stdio.h>

typedef struct t_student {
    char ime[100];
    char indeks[20];
    int kodovi[20];
    int num;
} Student;

typedef struct t_course {
    char ime[100];
    int kod;
    int br_studenti;
} Course;

int get_most_popular_course(Course* courses, int num) {
    int idx = -1, max_studenti = -1;

    for(int i = 0; i < num; i++) {
        if(courses[i].br_studenti > max_studenti) {
            max_studenti = courses[i].br_studenti;
            idx = i;
        }
    }

    return idx;
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);

    Course courses[20];
    Student studenti[20];

    for(int i = 0; i < t; i++) {
        scanf("%s %d", courses[i].ime, &courses[i].kod);
        courses[i].br_studenti = 0;
    }

    for(int i = 0; i < n; i++) {
        scanf("%s %s %d", studenti[i].ime, studenti[i].indeks, &studenti[i].num);
        for(int j = 0; j < studenti[i].num; j++) {
            scanf("%d", &studenti[i].kodovi[j]);
            for(int k = 0; k < t; k++) {
                if(studenti[i].kodovi[j] == courses[k].kod)
                    courses[k].br_studenti++;
            }
        }
    }

    int idx = get_most_popular_course(courses, t);

    printf("Najpopularen kurs e: %s", courses[idx].ime);

    return 0;
}
