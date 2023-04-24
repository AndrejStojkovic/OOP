// 5 - 1

#include <stdio.h>
#include <string.h>

typedef struct VideoGame {
    char name[100];
    float rating;
    float price;
} VideoGame;

typedef struct StreamingPlatform {
    char name[50];
    VideoGame games[30];
    int num_games;
} StreamingPlatform;

void print(StreamingPlatform platform) {
    printf("%s\n", platform.name);
    for (int i = 0; i < platform.num_games; i++) {
        printf("%s %.2f\n", platform.games[i].name, platform.games[i].price);
    }
}

void showBestValueService(StreamingPlatform platforms[], int num_platforms, float rating) {
    float min_price = -1.0;
    int best_platform_index = -1;

    for (int i = 0; i < num_platforms; i++) {
        for (int j = 0; j < platforms[i].num_games; j++) {
            if (platforms[i].games[j].rating > rating) {
                if (min_price < 0 || platforms[i].games[j].price <= min_price) {
                    min_price = platforms[i].games[j].price;
                    best_platform_index = i;
                }
            }
        }
    }

    if (best_platform_index >= 0) {
        printf("Best value platform is: %s\n", platforms[best_platform_index].name);
    } else {
        printf("No suitable platform found.\n");
    }
}

int main() {
    int num_platforms;
    scanf("%d", &num_platforms);
    StreamingPlatform platforms[num_platforms];

    for (int i = 0; i < num_platforms; i++) {
        scanf("%s %d", platforms[i].name, &platforms[i].num_games);
        for (int j = 0; j < platforms[i].num_games; j++) {
            scanf("%s %f %f", platforms[i].games[j].name, &platforms[i].games[j].rating, &platforms[i].games[j].price);
        }
    }

    float rating;
    scanf("%f", &rating);

    for (int i = 0; i < num_platforms; i++) {
        print(platforms[i]);
    }

    showBestValueService(platforms, num_platforms, rating);

    return 0;
}
