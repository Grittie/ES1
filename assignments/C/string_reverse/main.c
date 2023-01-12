#include <stdio.h>
#include <string.h>

int main() {
    char sentence[] = {'h', 'a', 'l', 'l', 'o', '\0'};
    int length = strlen(sentence);

    printf("sentence: %s\n", sentence);

    /*
     * TODO: Draai de string om, de \0 moet achteraan blijven staan.
     * TIP: De lengte van een string kan je krijgen door strlen(sentence).
     */



    printf("sentence reversed: %s\n", sentence);
    return 0;
}
