#include <stdio.h>

int main() {
    int w = 20;
    int h = 5;

//    Creates a filled in square
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            printf("x");
        }
        printf("\n");
    }

    printf("\n");

//    Creates an empty square
    for (int i = 0; i < w; ++i) {
        printf("x");
    }

    printf("\n");

    for (int i = 0; i < h-2; ++i) {
        printf("x");
        for (int j = 0; j <w-2; ++j) {
            printf(" ");
        }
        printf("x\n");
    }

    for (int i = 0; i < w; ++i) {
        printf("x");
    }

    printf("\n");

    printf("\n");

//    Creates half a pyramid
    for(int i = h; i >= 1; i--){
        for(int j = i;j >= 2; j--){
            printf(" ");
        }
        for(int k = 1; k <= h-i + 1; k++){
            printf("x");
        }
        printf("\n");
    }


}
